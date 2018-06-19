// Some copyright should be here...

using UnrealBuildTool;

public class UVVisualizer : ModuleRules
{
	public UVVisualizer(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        DefineIncludesAndDependencies();
    }

    void DefineIncludesAndDependencies()
    {
        PublicIncludePaths.AddRange(
            new string[] {
                "UVVisualizer/Public",
                "UVVisualizer/Public/UVViewport",
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "UVVisualizer/Private",
                "UVVisualizer/Private/UVViewport"
				// ... add other private include paths required here ...
			}
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "RPRCompatibility",
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "InputCore",
                "EditorStyle",
                "RenderCore",
                "RHI",
                "ShaderCore",
                "RawMesh",
                "RPREditorTools"
				// ... add private dependencies that you statically link with here ...	
			}
        );
    }
    
}
