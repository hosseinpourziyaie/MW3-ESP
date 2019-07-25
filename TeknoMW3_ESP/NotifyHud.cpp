#include<Windows.h>
#include "IW5Engine.h"
#include <stdio.h>

Color_t TestColor(0, 255, 255, 255);
Color_t BackgroundColor(0, 0, 0, 100);

bool ShowHUD = false;
char* HudMessage;

void PopupHUDNotify(char * Message)
{
	HudMessage = Message;
	ShowHUD = true;
	Sleep(1000);
	ShowHUD = false;
}

void DisplayMessage(char * Message)
{
	HudMessage = Message;
	ShowHUD = true;
	Sleep(1000);
	ShowHUD = false;
}

void HUDCall()
{
	if(ShowHUD)
	{
		IW5Engine::CEngine::CDraw::CDrawShader(0, (ScreenSize.y/9)*8, IW5Engine::CEngine::GetTextWidth(HudMessage, strlen(HudMessage) + 15, GetHudSmallFont()), IW5Engine::CEngine::GetFontHeightByScaleOne(GetHudSmallFont()) + 1, 0.0f, 0.0f, 0.0f, 0.0f, &BackgroundColor, GetWhiteShader());
		IW5Engine::CEngine::CDraw::CDrawText(HudMessage, strlen(HudMessage), GetHudSmallFont(), 5, (ScreenSize.y/9)*8 + IW5Engine::CEngine::GetFontHeightByScaleOne(GetHudSmallFont()), 1.0f, 1.0f, 0.0f, &TestColor, 0);
	}
}