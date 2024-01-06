// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DevLopBeatEmUp : ModuleRules
{
	public DevLopBeatEmUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { });
		// PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG", "Slate", "SlateCore"});
	}
}
