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
			if (ESPDEBUG.启动绘制对象)
				ESPDEBUG.ESP_Debug(ESPDEBUG.ESP绘制距离, ImVec4(255, 255, 255, 255));
		//if (Rader.drawRadar)
		//	{
		//		Rader.DrawRadarPanel();
		//		Rader.DrawRadar();
		//	}
			if(GameLoop.显示自瞄范围)
			GameLoop.DrawCircle(Vec2(1920 / 2, 1080 / 2), GameLoop.自瞄FOV, White, 80);
			GameLoop.MainLoop(ESPDEBUG.ESP绘制距离);
			FPSUnlock.RunFPSUlock();
	}
}
UAIBlueprintHelperLibrary;
AAIController;