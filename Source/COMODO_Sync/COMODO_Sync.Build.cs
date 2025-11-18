
using System.IO;
using UnrealBuildTool;

public class COMODO_Sync : ModuleRules
{
	public COMODO_Sync(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		// bEnableUndefinedIdentifierWarnings = false;
		// ShadowVariableWarningLevel = WarningLevel.Off;
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
		PublicIncludePaths.Add(Path.Combine(open62541Path, "Public"));
		PrivateIncludePaths.Add(Path.Combine(open62541Path, "Private"));
		
	}
}
