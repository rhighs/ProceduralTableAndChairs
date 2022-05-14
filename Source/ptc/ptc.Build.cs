using UnrealBuildTool;

public class ptc : ModuleRules
{
	public ptc(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "ProceduralMeshComponent"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
