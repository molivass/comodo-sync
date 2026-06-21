#include "OPCUAClient.h"
#include <string>
#include "Async/Async.h"

AOPCUAClient::AOPCUAClient() {
	PrimaryActorTick.bCanEverTick = true;
	bIsConnected = false;
	Client = nullptr;
}

void AOPCUAClient::BeginPlay() {
	Super::BeginPlay();
}

void AOPCUAClient::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Disconnect();
	Super::EndPlay(EndPlayReason);
}

void AOPCUAClient::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
    
	if (bIsConnected && Client) {
		ProcessClientEvents();
	}
}

//////////////////////////////////////
/// CONNECTION
//////////////////////////////////////

bool AOPCUAClient::ConnectAnon(const FString URL) {
	if (bIsConnected) Disconnect();
	
	Client = UA_Client_new();
	UA_ClientConfig_setDefault(UA_Client_getConfig(Client));
	
	UA_StatusCode status = UA_Client_connect(Client, TCHAR_TO_UTF8(*URL));

	if (status != UA_STATUSCODE_GOOD) {
		UA_Client_delete(Client);
		Client = nullptr;
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server. Status code: %s"), UTF8_TO_TCHAR(UA_StatusCode_name(status)));
		return false;
	}

	bIsConnected = true;
	UE_LOG(LogTemp, Log, TEXT("Successfully connected to server"));
	return true;
}

bool AOPCUAClient::ConnectUser(const FString URL, const FString Username, const FString Password) {
	Client = UA_Client_new();
	UA_ClientConfig *ClientConfig = UA_Client_getConfig(Client);
	ClientConfig->securityMode = UA_MESSAGESECURITYMODE_INVALID;
	ClientConfig->securityPolicyUri = UA_STRING_NULL;
	UA_ClientConfig_setDefault(ClientConfig);
	
	UA_StatusCode status = UA_Client_connectUsername(Client, TCHAR_TO_UTF8(*URL), TCHAR_TO_UTF8(*Username), TCHAR_TO_UTF8(*Password));

	if (status != UA_STATUSCODE_GOOD) {
		UA_Client_delete(Client);
		Client = nullptr;
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server. Status code: %s"), UTF8_TO_TCHAR(UA_StatusCode_name(status)));
		return false;
	}
	
	bIsConnected = true;
	UE_LOG(LogTemp, Log, TEXT("Successfully connected to server with user: %s"), *Username);
	return true;
}


void AOPCUAClient::Disconnect() {
	StopAllMonitoring();
	
	if (Client) {
		UA_Client_delete(Client);
		Client = nullptr;
	}
	
	bIsConnected = false;
	UE_LOG(LogTemp, Log, TEXT("Disconnected from server"));
}

void AOPCUAClient::ProcessClientEvents() {
	if (!Client) return;
	
	UA_Client_run_iterate(Client, 0);
}



//////////////////////////////////////
/// READ
//////////////////////////////////////

bool AOPCUAClient::ReadNodeValue(const FString& NodeId, int32 Namespace, int32& OutValue) {
	checkNoEntry();
	return false;
}

DEFINE_FUNCTION(AOPCUAClient::execReadNodeValue) {
	P_GET_PROPERTY(FStrProperty, NodeId);
	P_GET_PROPERTY(FUInt32Property, Namespace);
	
	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	
	Stack.StepCompiledIn<FProperty>(nullptr);
	
	FProperty* OutputProperty = Stack.MostRecentProperty;
	void* OutputValueAddress = Stack.MostRecentPropertyAddress;
	P_FINISH;
	
	bool bSuccess = false;
    
	if (OutputProperty && OutputValueAddress) {
		AOPCUAClient* This = Cast<AOPCUAClient>(Stack.Object);
		if (This) bSuccess = This->ReadNodeValueInternal(NodeId, Namespace, OutputValueAddress, OutputProperty);
	}
	
	*static_cast<bool*>(RESULT_PARAM) = bSuccess;
}

bool AOPCUAClient::ReadNodeValueInternal(const FString& NodeIdString, int32 Namespace, void* OutValue, FProperty* OutputProperty) {
    if (!IsConnected()) {
        UE_LOG(LogTemp, Warning, TEXT("Client is not connected to an OPC UA Server"));
        return false;
    }
    
    UA_NodeId NodeId = GetNodeId(NodeIdString,Namespace);
    
    UA_Variant value;
    UA_Variant_init(&value);
    
    UA_StatusCode readStatus = UA_Client_readValueAttribute(Client, NodeId, &value);
    
    bool bSuccess = false;
    
    if (readStatus == UA_STATUSCODE_GOOD) {
        if (value.type == &UA_TYPES[UA_TYPES_BOOLEAN]) {
        	if (OutputProperty->IsA<FBoolProperty>()) {
        		*static_cast<bool*>(OutValue) = *(UA_Boolean*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_SBYTE]) {
        	if (OutputProperty->IsA<FByteProperty>()) {
        		*static_cast<byte*>(OutValue) = *(UA_SByte*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_BYTE]) {
        	if (OutputProperty->IsA<FByteProperty>()) {
        		*static_cast<byte*>(OutValue) = *(UA_Byte*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_INT16] ) {
        	if (OutputProperty->IsA<FIntProperty>()) {
        		*static_cast<int32*>(OutValue) = *(UA_Int16*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_UINT16]) {
        	if (OutputProperty->IsA<FIntProperty>()) {
        		*static_cast<int32*>(OutValue) = *(UA_UInt16*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_INT32]) {
        	if (OutputProperty->IsA<FIntProperty>()) {
        		*static_cast<int32*>(OutValue) = *(UA_Int32*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_UINT32]) {
        	if (OutputProperty->IsA<FIntProperty>()) {
        		*static_cast<int32*>(OutValue) = *(UA_UInt32*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_INT64]) {
        	if (OutputProperty->IsA<FInt64Property>()) {
        		*static_cast<int64*>(OutValue) = *(UA_Int64*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_UINT64]) {
        	if (OutputProperty->IsA<FInt64Property>()) {
        		*static_cast<int64*>(OutValue) = *(UA_UInt64*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_FLOAT]) {
        	if (OutputProperty->IsA<FFloatProperty>()) {
        		*static_cast<float*>(OutValue) = *(UA_Float*)value.data;
        		bSuccess = true;
        	}
        	if (OutputProperty->IsA<FDoubleProperty>()) {
        		*static_cast<double*>(OutValue) = *(UA_Float*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_DOUBLE]) {
        	if (OutputProperty->IsA<FDoubleProperty>()) {
        		*static_cast<double*>(OutValue) = *(UA_Double*)value.data;
        		bSuccess = true;
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_STRING]) {
        	if (OutputProperty->IsA<FStrProperty>()) {
				UA_String* stringVal = (UA_String*)value.data;
				*static_cast<FString*>(OutValue) = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(stringVal->data)));
				bSuccess = true;
        	} else {
        		UE_LOG(LogTemp, Error, TEXT("Type mismatch for node: %s. UA Type: %s, Expected Unreal Type: %s"), 
					*NodeIdString, 
					UTF8_TO_TCHAR(value.type->typeName), 
					*OutputProperty->GetClass()->GetName());
        	}
        } else if (value.type == &UA_TYPES[UA_TYPES_DATETIME]) {
            // UA_DateTime* dateTimeVal = (UA_DateTime*)value.data;
        	if (OutputProperty->IsA<FStrProperty>()) {
				FString DateTimeStr = FString::Printf(TEXT("%lld"), *(UA_DateTime*)value.data);
				*static_cast<FString*>(OutValue) = DateTimeStr;
				bSuccess = true;
        	} else {
        		UE_LOG(LogTemp, Error, TEXT("Type mismatch for node: %s. UA Type: %s, Expected Unreal Type: %s"), 
                	*NodeIdString, 
                	UTF8_TO_TCHAR(value.type->typeName), 
                	*OutputProperty->GetClass()->GetName());
        	}
        } else {
            UE_LOG(LogTemp, Warning, TEXT("Unsupported OPC UA type in node: %s"), *NodeIdString);
        }
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Failed to read node value for node: %s. Error: %s"), 
            *NodeIdString, UTF8_TO_TCHAR(UA_StatusCode_name(readStatus)));
    }
    
    UA_Variant_clear(&value);
    UA_NodeId_clear(&NodeId);
    
    return bSuccess;
}


//////////////////////////////////////
/// WRITE
//////////////////////////////////////

bool AOPCUAClient::WriteNodeValue(const FString& NodeId, int32 Namespace, int32 InValue){
	checkNoEntry();
	return false;
}


DEFINE_FUNCTION(AOPCUAClient::execWriteNodeValue) {
	P_GET_PROPERTY(FStrProperty, NodeId);
	P_GET_PROPERTY(FUInt32Property, Namespace);
	
	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	
	Stack.StepCompiledIn<FProperty>(nullptr);
	
	FProperty* InputProperty = Stack.MostRecentProperty;
	void* InputValueAddress = Stack.MostRecentPropertyAddress;
	P_FINISH;
	
	bool bSuccess = false;
    
	if (InputProperty && InputValueAddress) {
		AOPCUAClient* This = Cast<AOPCUAClient>(Stack.Object);
		if (This) bSuccess = This->WriteNodeValueInternal(NodeId, Namespace, InputValueAddress, InputProperty);
	}
	
	*static_cast<bool*>(RESULT_PARAM) = bSuccess;
}

bool AOPCUAClient::WriteNodeValueInternal(const FString& NodeIdString, int32 Namespace, void* InValue, FProperty* InputProperty) {
	if (!IsConnected()) {
		UE_LOG(LogTemp, Warning, TEXT("Client is not connected to an OPC UA Server"));
		return false;
	}
	
	bool bSuccess = false;

	UA_NodeId NodeId = GetNodeId(NodeIdString, Namespace);
	
	UA_Variant value;
	UA_Variant_init(&value);
	
	if (InputProperty->IsA<FBoolProperty>()) {
		bool* UnrealValue = static_cast<bool*>(InValue);
		UA_Boolean UAValue = *UnrealValue;
		UA_Variant_setScalarCopy(&value, &UAValue, &UA_TYPES[UA_TYPES_BOOLEAN]);
		bSuccess = true;
	} else if (InputProperty->IsA<FIntProperty>()) {
		int32* UnrealValue = static_cast<int32*>(InValue);
		UA_Int32 UAValue = *UnrealValue;
		UA_Variant_setScalarCopy(&value, &UAValue, &UA_TYPES[UA_TYPES_INT32]);
		bSuccess = true;
	} else if (InputProperty->IsA<FFloatProperty>()) {
		float* UnrealValue = static_cast<float*>(InValue);
		UA_Float UAValue = *UnrealValue;
		UA_Variant_setScalarCopy(&value, &UAValue, &UA_TYPES[UA_TYPES_FLOAT]);
		bSuccess = true;
	} else if (InputProperty->IsA<FDoubleProperty>()) {
		double* UnrealValue = static_cast<double*>(InValue);
		UA_Double UAValue = *UnrealValue;
		UA_Variant_setScalarCopy(&value, &UAValue, &UA_TYPES[UA_TYPES_DOUBLE]);
		bSuccess = true;
	} else if (InputProperty->IsA<FStrProperty>()) {
		FString* StringValue = static_cast<FString*>(InValue);
		std::string StringStd = TCHAR_TO_UTF8(**StringValue);
        
		UA_String UAString = UA_STRING_ALLOC(StringStd.c_str());
		UA_Variant_setScalarCopy(&value, &UAString, &UA_TYPES[UA_TYPES_STRING]);
		bSuccess = true;
	}
	
	if (bSuccess) {
		UA_StatusCode writeStatus = UA_Client_writeValueAttribute(Client, NodeId, &value);
        if (writeStatus != UA_STATUSCODE_GOOD) {
            bSuccess = false;
            UE_LOG(LogTemp, Error, TEXT("Failed to write value to node: %s. Error: %s"), 
                *NodeIdString, UTF8_TO_TCHAR(UA_StatusCode_name(writeStatus)));
        }
	}
	
	UA_Variant_clear(&value);
	UA_NodeId_clear(&NodeId);
	
	return bSuccess;
}


//////////////////////////////////////
/// MONITORING
//////////////////////////////////////

bool AOPCUAClient::StartMonitoringNode(const FString& NodeId, int32 Namespace, 
	float SamplingInterval, int32& VariableToUpdate, FOPCUAOnValueChanged Callback) {
	checkNoEntry();
	return false;
}

DEFINE_FUNCTION(AOPCUAClient::execStartMonitoringNode) {
	P_GET_PROPERTY(FStrProperty, NodeId);
	P_GET_PROPERTY(FUInt32Property, Namespace);
	P_GET_PROPERTY(FFloatProperty, SamplingInterval);
	
	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FProperty>(nullptr);
	
	FProperty* InputProperty = Stack.MostRecentProperty;
	void* InputValueAddress = Stack.MostRecentPropertyAddress;
	
	P_GET_STRUCT(FOPCUAOnValueChanged, Callback);
	P_FINISH;
	
	bool bSuccess = false;
    
	if (InputProperty && InputValueAddress) {
		AOPCUAClient* This = Cast<AOPCUAClient>(Stack.Object);
		if (This) bSuccess = This->StartMonitoringNodeInternal(NodeId, Namespace, SamplingInterval,
			InputValueAddress, InputProperty, Callback);
	}
	
	*static_cast<bool*>(RESULT_PARAM) = bSuccess;
}

bool AOPCUAClient::StartMonitoringNodeInternal(const FString& NodeIdString, int32 Namespace, 
	float SamplingInterval, void* InValue, FProperty* InputProperty, FOPCUAOnValueChanged Callback) {
	
	if (!IsConnected()) {
		UE_LOG(LogTemp, Warning, TEXT("Client is not connected to an OPC UA Server"));
		return false;
	}
	
	FString NodeKey = FString::Printf(TEXT("%s:%d"), *NodeIdString, Namespace);
	
	if (MonitoredItems.Contains(NodeKey)) {
		UE_LOG(LogTemp, Warning, TEXT("Already monitoring node: %s"), *NodeIdString);
		return true;
	}
	
	FMonitoredItem NewItem(InValue);
	NewItem.NodeIdString = NodeIdString;
	NewItem.Namespace = Namespace;
	NewItem.DataType = GetNodeDataType(NodeIdString, Namespace);
	NewItem.VarName = InputProperty->GetFName();
	NewItem.Callback = Callback;
	// NewItem.VarRef = InValue;
	
	UA_CreateSubscriptionRequest SubRequest;
	UA_CreateSubscriptionRequest_init(&SubRequest);
	SubRequest.requestedPublishingInterval = SamplingInterval;
	SubRequest.requestedLifetimeCount = 10000;
	SubRequest.requestedMaxKeepAliveCount = 1000;
	SubRequest.maxNotificationsPerPublish = 1000;
	SubRequest.publishingEnabled = true;
	SubRequest.priority = 0;
	
	UA_CreateSubscriptionResponse SubResponse = UA_Client_Subscriptions_create(Client, SubRequest,
		this, NULL, NULL);
    
	if (SubResponse.responseHeader.serviceResult != UA_STATUSCODE_GOOD) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create subscription for node: %s"), *NodeIdString);
		UA_CreateSubscriptionResponse_clear(&SubResponse);
		return false;
	}
	
	NewItem.SubscriptionId = SubResponse.subscriptionId;
	
	UA_NodeId NodeId = GetNodeId(NodeIdString, Namespace);
    
	UA_MonitoredItemCreateRequest MonitorRequest;
	UA_MonitoredItemCreateRequest_init(&MonitorRequest);
	MonitorRequest.itemToMonitor.nodeId = NodeId;
	MonitorRequest.itemToMonitor.attributeId = UA_ATTRIBUTEID_VALUE;
	MonitorRequest.monitoringMode = UA_MONITORINGMODE_REPORTING;
	MonitorRequest.requestedParameters.samplingInterval = SamplingInterval;
	MonitorRequest.requestedParameters.queueSize = 1;
	MonitorRequest.requestedParameters.discardOldest = true;
	
	UA_MonitoredItemCreateResult MonitorResult = UA_Client_MonitoredItems_createDataChange(
		Client, 
		SubResponse.subscriptionId, 
		UA_TIMESTAMPSTORETURN_BOTH, 
		MonitorRequest, 
		this,
		&AOPCUAClient::DataChangeNotificationCallback, 
		NULL
	);
    
	if (MonitorResult.statusCode != UA_STATUSCODE_GOOD) {
		UE_LOG(LogTemp, Error, TEXT("Failed to create monitored item for node: %s"), *NodeIdString);
		// UA_NodeId_clear(&NodeId);
		UA_MonitoredItemCreateRequest_clear(&MonitorRequest);
		UA_MonitoredItemCreateResult_clear(&MonitorResult);
		UA_CreateSubscriptionResponse_clear(&SubResponse);
		return false;
	}
    
	NewItem.MonitoredItemId = MonitorResult.monitoredItemId;
	
	UA_MonitoredItemCreateRequest_clear(&MonitorRequest);
	UA_MonitoredItemCreateResult_clear(&MonitorResult);
	UA_CreateSubscriptionResponse_clear(&SubResponse);
	// UA_NodeId_clear(&NodeId);
    
	MonitoredItems.Add(NodeKey, NewItem);
	UE_LOG(LogTemp, Display, TEXT("Started monitoring node: %s"), *NodeIdString);
	
	return true;
}

void AOPCUAClient::DataChangeNotificationCallback(UA_Client* ua_client, UA_UInt32 subId, void* subContext,
												  UA_UInt32 monId, void* monContext, UA_DataValue* value) {
	if (!subContext || !value) return;
    
	AOPCUAClient* This = static_cast<AOPCUAClient*>(subContext);
	if (!This) return;
	
	for (auto& ItemPair : This->MonitoredItems) {
		if (ItemPair.Value.SubscriptionId == subId && ItemPair.Value.MonitoredItemId == monId) {
			if (ItemPair.Value.DataType == &UA_TYPES[UA_TYPES_BOOLEAN]) {
				bool* OutPtr = static_cast<bool*>(ItemPair.Value.VarRef);
				bool Value = *(UA_Boolean*)value->value.data;
				*OutPtr = Value;
			} else if (ItemPair.Value.DataType == &UA_TYPES[UA_TYPES_DOUBLE]) {
				double* OutPtr = static_cast<double*>(ItemPair.Value.VarRef);
				double Value = *(UA_Double*)value->value.data;
				*OutPtr = Value;
			} else if (ItemPair.Value.DataType == &UA_TYPES[UA_TYPES_INT32]) {
				int32* OutPtr = static_cast<int32*>(ItemPair.Value.VarRef);
				int32 Value = *(UA_Int32*)value->value.data;
				*OutPtr = Value;
			} else if (ItemPair.Value.DataType == &UA_TYPES[UA_TYPES_STRING]) {
				FString* OutPtr = static_cast<FString*>(ItemPair.Value.VarRef);
				UA_String* stringVal = (UA_String*)value->value.data;
				*OutPtr = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(stringVal->data)));
			}
			
			ItemPair.Value.Callback.ExecuteIfBound();
			break;
		}
	}
}

bool AOPCUAClient::StopMonitoringNode(const FString& NodeId, int32 Namespace) {
	FString NodeKey = FString::Printf(TEXT("%s:%d"), *NodeId, Namespace);
    
	if (!MonitoredItems.Contains(NodeKey)) {
		return false;
	}
    
	FMonitoredItem& Item = MonitoredItems[NodeKey];
	
	UA_StatusCode status = UA_Client_MonitoredItems_deleteSingle(Client, Item.SubscriptionId, Item.MonitoredItemId);
    
	if (status != UA_STATUSCODE_GOOD) {
		UE_LOG(LogTemp, Error, TEXT("Failed to delete monitored item for node: %s"), *NodeId);
		return false;
	}
	
	bool OtherItemsUsingSubscription = false;
	for (auto& OtherItem : MonitoredItems) {
		if (OtherItem.Value.SubscriptionId == Item.SubscriptionId && OtherItem.Key != NodeKey) {
			OtherItemsUsingSubscription = true;
			break;
		}
	}
    
	if (!OtherItemsUsingSubscription) {
		UA_Client_Subscriptions_deleteSingle(Client, Item.SubscriptionId);
	}
    
	MonitoredItems.Remove(NodeKey);
    
	UE_LOG(LogTemp, Log, TEXT("Stopped monitoring node: %s"), *NodeId);
	return true;
}

void AOPCUAClient::StopAllMonitoring() {
	for (auto It = MonitoredItems.CreateIterator(); It; ++It) {
		FString NodeId;
		int32 Namespace;
		if (It.Key().Split(TEXT(":"), &NodeId, nullptr)) {
			Namespace = FCString::Atoi(*It.Key().RightChop(NodeId.Len() + 1));
			StopMonitoringNode(NodeId, Namespace);
		}
	}
}

//////////////////////////////////////
/// HELPERS
//////////////////////////////////////
const UA_NodeId AOPCUAClient::GetNodeId(const FString& NodeIdString, int32 Namespace) {
	if (!Client) return UA_NODEID_NULL;
	
	std::string NodeIdStd = TCHAR_TO_UTF8(*NodeIdString);
	UA_NodeId NodeId = UA_NODEID_STRING_ALLOC(Namespace, NodeIdStd.c_str());
	
	return NodeId;
}

const UA_DataType* AOPCUAClient::GetNodeDataType(const FString& NodeIdString, int32 Namespace) {
	if (!IsConnected()) return nullptr;
	
	UA_NodeId nodeId = GetNodeId(NodeIdString, Namespace);
    
	UA_NodeId dataTypeAttributeId = UA_NODEID_NULL;
	UA_StatusCode status = UA_Client_readDataTypeAttribute(Client, nodeId, &dataTypeAttributeId);
    
	if (status != UA_STATUSCODE_GOOD) {
		UE_LOG(LogTemp, Error, TEXT("Failed to read data type attribute for node: %s"), *NodeIdString);
		UA_NodeId_clear(&nodeId);
		return nullptr;
	}
    
	const UA_DataType* DataType = UA_Client_findDataType(Client, &dataTypeAttributeId);
    
	UA_NodeId_clear(&nodeId);
	UA_NodeId_clear(&dataTypeAttributeId);
    
	return DataType;
}