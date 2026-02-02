
using System.IO;
using UnrealBuildTool;

public class COMODO_Sync : ModuleRules {
	public COMODO_Sync(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;
		
		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
			}
		);
		
		PublicIncludePaths.Add(ModuleDirectory);
		
		string ThirdParties = Path.Combine(ModuleDirectory, "..", "ThirdParty");
		string open62541Path = Path.Combine(ThirdParties, "open62541");
		PublicIncludePaths.Add(open62541Path);
		
		PublicAdditionalLibraries.Add(Path.Combine(open62541Path,"open62541.lib"));

		string dllPath = Path.Combine(open62541Path, "open62541.dll");
		RuntimeDependencies.Add("$(BinaryOutputDir)/open62541.dll", dllPath);
	}
}