#pragma once
#include "CheatNeed.h"
void static Cheat()
{
	if (GetCharacter() && GetPawn() && GetActor()&&GetGameStateBase()->HasBegunPlay())
	{
			Player.PlayerCheatStar();
			WorldLoop.WorldCheat();
			AnotherWindowLoop.AnotherWindowCheatStar();
			PeopleLoop.PeopleLoop();
			if (ESPDEBUG.�������ƶ���)
				ESPDEBUG.ESP_Debug(ESPDEBUG.ESP���ƾ���, ImVec4(255, 255, 255, 255));
		//if (Rader.drawRadar)
		//	{
		//		Rader.DrawRadarPanel();
		//		Rader.DrawRadar();
		//	}
			if(GameLoop.��ʾ���鷶Χ)
			GameLoop.DrawCircle(Vec2(1920 / 2, 1080 / 2), GameLoop.����FOV, White, 80);
			GameLoop.MainLoop(ESPDEBUG.ESP���ƾ���);
			FPSUnlock.RunFPSUlock();
	}
}
UAIBlueprintHelperLibrary;
AAIController;