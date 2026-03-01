// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RiseOfSunTarget : TargetRules
{
	public RiseOfSunTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("RiseOfSun");
	}
}


// 1. 인덱스를 통해서 인벤토리 컴포넌트에 있는 아이템 슬롯을 가져온다.
// 2. 아이템 슬롯에서 아이템 아이디를 가져온다.
// 3. 아이템 아이디가 Name_None이 아니면 데이터 테이블에 있는 아이템을 가져온다.(아이템 아이디를 통해)
// 4. 데이터 테이블 안에 RSBaseItem 클래스가 존재.
// 5. 결국 아이템 아이디를 통해 RSBaseItem을 가져오고
// RSBaseItem를 사용한다.