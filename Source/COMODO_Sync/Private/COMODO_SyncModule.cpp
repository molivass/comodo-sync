#include "COMODO_SyncModule.h"
#include "OPCUAClient.h"

#define LOCTEXT_NAMESPACE "FCOMODO_SyncModule"

void FCOMODO_SyncModule::StartupModule() {
    // Startup logic
}

void FCOMODO_SyncModule::ShutdownModule() {
    // Shutdown logic
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FCOMODO_SyncModule, COMODO_Sync)