	// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JHP : ModuleRules
{
	public JHP(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "MotionWarping", "EnhancedInput",
			"ActionAssetPlugin"
        });
	}
}
