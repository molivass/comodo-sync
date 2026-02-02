#pragma once

#include "GameFramework/Actor.h"
#include "open62541.h"
// #include "OPCUATypes.h"
#include "OPCUAClient.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOPCUAOnValueChanged);

struct FMonitoredItem {
    uint32 MonitoredItemId;
    uint32 SubscriptionId;
    const struct UA_DataType* DataType;
    FString NodeIdString;
    int32 Namespace;
    void* VarRef;
    FName VarName;
    FOPCUAOnValueChanged Callback;
    
    FMonitoredItem(void*& InRef):
        MonitoredItemId(0),
        SubscriptionId(0),
        DataType(nullptr),
        NodeIdString(""),
        Namespace(0),
        VarRef(InRef),
        VarName(""),
        Callback()
    {}
};


UCLASS(Blueprintable, Category = "OPC UA")
class AOPCUAClient : public AActor {
	GENERATED_BODY()

public:
	AOPCUAClient();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

public:
	
	/**
	* Connect to an OPC UA Server
	* @param URL Endpoint Url of the server
	* @return	true if connection is successful
	*/
	UFUNCTION(BlueprintCallable, Category = "OPC UA|Connection", meta=(DisplayName = "Connect to Server - Anonymous"))
	bool ConnectAnon(const FString URL);
	
	/**
	* Connect to an OPC UA Server 
	* @param URL Endpoint Url of the server
	* @param Username Name of a user defined in the server
	* @param Password Password for the specified user
	* @return	true if connection is successful
	*/
	UFUNCTION(BlueprintCallable, Category = "OPC UA|Connection", meta=(DisplayName = "Connect to Server - User"))
	bool ConnectUser(const FString URL, const FString Username, const FString Password);
	
	/**
	* Disconnects the client from an existing OPC UA server connection
	*/
	UFUNCTION(BlueprintCallable, Category = "OPC UA|Connection", meta=(DisplayName = "Disconnect From Server"))
	void Disconnect();
	
	/**
	 * Checks if the client is currently connected to a server
	 */
	UFUNCTION(BlueprintCallable, Category = "OPC UA|Connection")
	bool IsConnected() { return bIsConnected && Client; }
	
	/**
	 * Reads the value of a node from the connected OPC UA server
	 * @param NodeId The name of the variable in the server
	 * @param Namespace Number of the Namespace that the node is stored in
	 * @param OutValue Outputs the value read from the node
	 * @return true if the operation succeeds
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "OPC UA|IO", meta = (CustomStructureParam = "OutValue"))
	bool ReadNodeValue(const FString& NodeId, int32 Namespace, int32& OutValue);
	DECLARE_FUNCTION(execReadNodeValue);
	
	/**
	 * Writes data to the specified node from the connected OPC UA server
	 * @param NodeId The name of the variable in the server
	 * @param Namespace Number of the Namespace that the node is stored in
	 * @param InValue The data to be sent to the server
	 * @return true if the operation succeeds
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "OPC UA|IO", meta = (CustomStructureParam = "InValue"))
	bool WriteNodeValue(const FString& NodeId, int32 Namespace, int32 InValue);
	DECLARE_FUNCTION(execWriteNodeValue);
	
	/**
	 * Polls the node periodically. If there is a change in the node, the function updates the variable passed by reference.
	 * @param NodeId The name of the variable in the server
	 * @param Namespace Number of the Namespace that the node is stored in
	 * @param SamplingInterval Time between polling, in milliseconds
	 * @param VariableToUpdate Variable that updates when the node value changes
	 * @param Callback Event that executes when the variable changes
	 * @return true if the operation succeeds
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "OPC UA|Monitor", meta = (CustomStructureParam = "VariableToUpdate"))
	bool StartMonitoringNode(const FString& NodeId, int32 Namespace, float SamplingInterval,
		UPARAM(Ref) int32& VariableToUpdate, UPARAM(DisplayName="On Value Changed") FOPCUAOnValueChanged  Callback);
	DECLARE_FUNCTION(execStartMonitoringNode);
	
	/**
	 * Stops the monitorization for the selected node
	 * @param NodeId The name of the variable in the server
	 * @param Namespace Number of the Namespace that the node is stored in
	 */
	UFUNCTION(BlueprintCallable, Category = "OPC UA|Monitor")
	bool StopMonitoringNode(const FString& NodeId, int32 Namespace);

	/**
	 * Stops the monitorization for all nodes
	 */
	UFUNCTION(BlueprintCallable, Category = "OPC UA|Monitor")
	void StopAllMonitoring();
	
private:
	bool bIsConnected;
	UA_Client* Client;
	TMap<FString, FMonitoredItem> MonitoredItems;
	
	// Helper function to get the UA_Type of a given Node from the server
	const UA_DataType* GetNodeDataType(const FString& NodeIdString, int32 Namespace);
	// Helper function to get the NodeId of a Node by its name
	const UA_NodeId GetNodeId(const FString& NodeIdString, int32 Namespace);
	
	// Actual implementation for all CustomThunk functions
	bool ReadNodeValueInternal(const FString& NodeIdString, int32 Namespace, void* OutValue, FProperty* OutputProperty);
	bool WriteNodeValueInternal(const FString& NodeIdString, int32 Namespace, void* InValue, FProperty* InputProperty);
	bool StartMonitoringNodeInternal(const FString& NodeIdString, int32 Namespace, 
		float SamplingInterval, void* InValue, FProperty* InputProperty, FOPCUAOnValueChanged Callback);
	
	// Callback that fires whenever a MonitoredItem changes its value
	static void __cdecl DataChangeNotificationCallback(UA_Client* client, UA_UInt32 subId, void* subContext, 
													   UA_UInt32 monId, void* monContext, UA_DataValue* value);
	
	// Runs on tick and processes arriving asynchronous responses from the network
	void ProcessClientEvents();
};
