// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionAssetPlugin : ModuleRules
{
	public ActionAssetPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                // ... add other public dependencies that you statically link with here ...
			}
			);

        PrivateDependencyModuleNames.Add("Projects");
        PrivateDependencyModuleNames.Add("InputCore");
        PrivateDependencyModuleNames.Add("EditorFramework");
        PrivateDependencyModuleNames.Add("ToolMenus");

        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");
        PrivateDependencyModuleNames.Add("Slate");
        PrivateDependencyModuleNames.Add("SlateCore");

        PrivateDependencyModuleNames.Add("UnrealEd");
        PrivateDependencyModuleNames.Add("EditorStyle");

        PublicDependencyModuleNames.Add("Niagara");
    }
}
