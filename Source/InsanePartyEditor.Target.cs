using UnrealBuildTool;
using System.Collections.Generic;

public class InsanePartyEditorTarget : TargetRules
{
	public InsanePartyEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("InsaneParty");
	}
}
