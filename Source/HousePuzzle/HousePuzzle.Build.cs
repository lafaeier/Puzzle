// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HousePuzzle : ModuleRules
{
	public HousePuzzle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HousePuzzle",
			"HousePuzzle/Core",
			"HousePuzzle/Interaction",
			"HousePuzzle/Puzzle",
			"HousePuzzle/Puzzles/Bedroom",
			"HousePuzzle/Puzzles/Balcony",
			"HousePuzzle/Puzzles/LivingRoom",
			"HousePuzzle/Puzzles/Study",
			"HousePuzzle/Misc",
			"HousePuzzle/UI",
			"HousePuzzle/Variant_Horror",
			"HousePuzzle/Variant_Horror/UI",
			"HousePuzzle/Variant_Shooter",
			"HousePuzzle/Variant_Shooter/AI",
			"HousePuzzle/Variant_Shooter/UI",
			"HousePuzzle/Variant_Shooter/Weapons"
		});
	}
}
