// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PocketWorldsUI : ModuleRules
{
	public PocketWorldsUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CommonUI"
		});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"DeveloperSettings",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"ChaosVehicles",
			"PhysicsCore",
			"SlateCore",
			"Slate"
		});
	}
}
