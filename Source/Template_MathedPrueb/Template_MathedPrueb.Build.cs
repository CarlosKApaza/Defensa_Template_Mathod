// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Template_MathedPrueb : ModuleRules
{
	public Template_MathedPrueb(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
