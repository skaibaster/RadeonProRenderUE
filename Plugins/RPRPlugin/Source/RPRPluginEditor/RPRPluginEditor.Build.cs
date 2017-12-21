// Some copyright should be here...

using UnrealBuildTool;

public class RPRPluginEditor : ModuleRules
{
	public RPRPluginEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        DefineIncludesAndDependencies();
    }

    void DefineIncludesAndDependencies()
    {
        PublicIncludePaths.AddRange(
            new string[] {
                "RPRPluginEditor/Public",
                "RPRPlugin/Public"				
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "RPRPluginEditor/Private",
                "RPRPlugin/Private"
				// ... add other private include paths required here ...
			}
            );

        IncludeRPR_SDK();

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "RPRPlugin"
				
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
                "Slate",
                "LevelEditor",
                "Settings",
                "StaticMeshEditor",
                "PropertyEditor"
				// ... add private dependencies that you statically link with here ...	
			}
        );
    }

    void IncludeRPR_SDK()
    {
        string pluginRoot = ModuleDirectory + "/../..";
        pluginRoot = System.IO.Path.GetFullPath(pluginRoot);
        pluginRoot = Utils.CleanDirectorySeparators(pluginRoot, '/') + "/";

        string SDKRoot = pluginRoot + "/ProRenderSDK/";

        PrivateIncludePaths.AddRange(
            new string[] {
                "RPRPlugin/Private",
                SDKRoot + "RadeonProRender",
                SDKRoot + "RadeonProRender/inc",
                SDKRoot + "RadeonProRenderInterchange/include"
            }
        );

        // TODO: Modify this so it is multi platform or throw errors on non supported platforms
        PublicAdditionalLibraries.AddRange(new string[]
        {
            SDKRoot + "RadeonProRender/libWin64/RadeonProRender64.lib",
            SDKRoot + "RadeonProRender/libWin64/RprLoadStore64.lib",
            SDKRoot + "RadeonProRender/libWin64/RprSupport64.lib",
            SDKRoot + "RadeonProRender/libWin64/Tahoe64.lib",
            SDKRoot + "RadeonProRenderInterchange/libWin64/RadeonProRenderInterchange64.lib"
        });
    }
}