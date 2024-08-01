	// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JHP : ModuleRules
{
    public JHP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate", "SlateCore"
        });

    PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "MotionWarping", "EnhancedInput",
			"UMG", "ActionAssetPlugin"
        });
	}
}
