/**********************************************************************
* Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
********************************************************************/

using UnrealBuildTool;
using System.IO;

public class RPRGLTFImporter : ModuleRules
{
    public RPRGLTFImporter(ReadOnlyTargetRules TargetRules) : base(TargetRules)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
        PrivateIncludePaths.AddRange(
            new string[] {
                "RPRImporters/RPRGLTFImporter/Private",
                "RPRImporters/RPRGLTFImporter/Private/Slate",
                "RPRImporters/RPRGLTFImporter/Private/Factories",
                "RPRImporters/RPRGLTFImporter/Private/Factories/Setters",

                "RPRImporters/RPRGLTFImporter/Public",
                "RPRImporters/RPRGLTFImporter/Public/Slate",
                "RPRImporters/RPRGLTFImporter/Public/Factories",
                "RPRImporters/RPRGLTFImporter/Public/Factories/Setters",
        });

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "RPRCore",
                "RPR_SDK",
                "RPR_GLTF",
                "RPRGraphParser",
                "RPRPlugin",
                "RPRTools",
                "RPR_Json",
                "RPRImporterTools",
                "RPRMaterialEditor",
                "RPREditorTools",
        });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "AssetRegistry",
                "EditorStyle",
                "Engine",
                "InputCore",
                "MainFrame",
                "Slate",
                "SlateCore",
                "PropertyEditor",
                "RenderCore",
                "RawMesh",
                "AssetTools",
                "UnrealEd",
                "RawMesh",
        });
		
		//string PluginDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", ".."));
		//string ThirdPartyDir = Path.Combine(PluginDir, "ThirdParty");
		//string SDKDir = Path.Combine(ThirdPartyDir, "ProRenderSDK");
		
		//PublicIncludePaths.AddRange(
		//	new string[] {
		//		Path.Combine(SDKDir, "RadeonProRender", "inc"),
		//});		

        //MinFilesUsingPrecompiledHeaderOverride = 1;
    }
}