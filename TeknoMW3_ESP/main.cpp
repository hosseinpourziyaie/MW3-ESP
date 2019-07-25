// =======================================================================
// Retards Project (ahah)
//
// Component: TeknoMW3_ESP
// Purpose: Draw Red Boxes so nub hacker wont get flagged as noob looser
//                                     by other players in server anymore
//
// Initial author : Astro
// Developed by   : Hosseinpourziyaie
// Started        : who cares?
// Note           : this source code released on educational purpose
//                            please refuse to ruining games using this                                                  
// =======================================================================

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include "IW5Engine.h"

using namespace std;

#pragma region :)
#define MAGIC_NUMBER_PATTERN    "\xa1\x00\x00\x00\x00\x8d\x94\x24\x04\x08\x00\x00\x52\x56\x50\x68\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x8b\x8c\x24\x18\x0c\x00\x00\x50\x51\xe8\x00\x00\x00\x00\x83\xc4\x18"
#define MAGIC_NUMBER_MASK        "x????xxxxxxxxxxx????x????xxxxxxxxxx????xxx" // +1 

typedef int(*__cdecl SendCmdToCon_0x4EB8F0)(int, int, char*);
SendCmdToCon_0x4EB8F0 SendCmd = (SendCmdToCon_0x4EB8F0)0x4EB8F0;

bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

DWORD FindPattern(DWORD baseAddress, DWORD sizeOfModule, BYTE *bMask, char* szMask)
{
	for (DWORD i = 0; i < sizeOfModule; i++)
		if (bDataCompare((BYTE*)(baseAddress + i), bMask, szMask))
			return (DWORD)(baseAddress + i);
	return NULL;
}

//Make Sure Module is injected into the right process or do nothing.
bool IsModuleReady()
{
	if (GetModuleHandleA("iw5mp.exe") != NULL)
		return true;

	return false;
}

DWORD WINAPI GetMagicNumberAddress()
{
	while (!IsModuleReady()) Sleep(50);
	DWORD *MagicNumber = (DWORD*)*(DWORD*)(FindPattern((DWORD)GetModuleHandleA("iw5mp.exe"), 0xFFFFFFFF, (BYTE*)MAGIC_NUMBER_PATTERN, MAGIC_NUMBER_MASK) + 1);
	return *MagicNumber;
}
#pragma endregion thx EO

HANDLE tekno = GetCurrentProcess(); //store our process

//bools
bool redBoxes = false, Laser = false, Chrome = false, UAV = false, Spam = false;

#pragma region BYTES
//byte values for when we write to process memory
BYTE bName[] =		{ 0xC3 };
BYTE boxesON[] =	{ 0x90, 0x90 };
BYTE boxesOFF[] =	{ 0x74, 0x09 };
BYTE laserON[] =	{ 0 };
BYTE laserOFF[] =	{ 0x25 };
BYTE chromeON[] =	{ 0x90, 0x90, 0x90, 0x90, 0x90 };
BYTE chromeON2[] =	{ 1 };
BYTE chromeOFF[] =	{ 0xA2, 0xC0, 0xCC, 0xF9, 0x05 };
BYTE chromeOFF2[] = { 0 };
BYTE uavON[] =		{ 1 };
BYTE uavOFF[] =		{ 0 };
#pragma endregion


void PopupHUDNotify(char * Message);

DWORD WINAPI LoopFunction( LPVOID lpParam )
{
	while (true)
	{

#pragma region redboxes
		if (GetAsyncKeyState(VK_F1)) // "& 1" is so we can click it and not get rekt
		{
			if (redBoxes == false)
			{
				redBoxes = true;
				WriteProcessMemory(tekno, (void*)(0x430568), &boxesON, 2, 0);
				PopupHUDNotify("^2ESP Enabled");
			}
			else
			{
				redBoxes = false;
				WriteProcessMemory(tekno, (void*)(0x430568), &boxesOFF, 2, 0);
				PopupHUDNotify("^1ESP Disabled");
			}
		}
#pragma endregion 

#pragma region laser
		if(GetAsyncKeyState(VK_F2))
		{
			if(Laser == false)
			{
				Laser = true;
				WriteProcessMemory(tekno, (void*)(0x4D14B7), &laserON, 1, 0);
				PopupHUDNotify("^2Laser Enabled");
			}
			else
			{
				Laser = false;
				WriteProcessMemory(tekno, (void*)(0x4D14B7), &laserOFF, 1, 0);
				PopupHUDNotify("^1Laser Disabled");
			}
		}
#pragma endregion 

#pragma region chrome
		if(GetAsyncKeyState(VK_F3))
		{
			if (Chrome == false)
			{
				Chrome = true;
				PopupHUDNotify("^2Chrome Bodies Enabled");
				while (Chrome == true)
				{
					WriteProcessMemory(tekno, (void*)(0x4C1E34), &chromeON, 5, 0);
					WriteProcessMemory(tekno, (void*)(0x5F9CCC0), &chromeON2, 1, 0);

					if(GetAsyncKeyState(VK_F3))
						break;

					Sleep(500);
				}
			}
			else
			{
				Chrome = false;
				PopupHUDNotify("^1Chrome Bodies Disabled");
				WriteProcessMemory(tekno, (void*)(0x4C1E34), &chromeOFF, 5, 0);
				WriteProcessMemory(tekno, (void*)(0x5F9CCC0), &chromeOFF2, 1, 0);
			}
		}
#pragma endregion 

#pragma region Jugg
		if (GetAsyncKeyState(VK_F4))
		{
			char buff[32];
			sprintf_s(buff, "cmd mr %d 9 axis", (DWORD)GetMagicNumberAddress()); //this is basically cbuf_addtext :)
			SendCmd(0, 0, buff);
			PopupHUDNotify("^3Juggernaut ACTIVATED");
		}
#pragma endregion

#pragma region Disconnect(Good for Zom Rage Quit)
		/*if(GetAsyncKeyState(VK_END))//TODO : Fix This
		{
			char Buff[256];
			sprintf_s(Buff, "disconnect");
			PopupHUDNotify("^1PLATFORM_DISCONNECTED_FROM_SERVER");
			SendCmd(0, 0, Buff);
		}*/
#pragma endregion

		Sleep(100); //give your cpu a break (you can make it higher if you like)
	}	
}

void* MakeDirectJUMP(void* from, void* to, size_t bytestosave);

void Init()
{
	IW5Engine::CEngine::CG_InitDrawBranding = (char(__cdecl*)(int))MakeDirectJUMP((void*)OFFSET_CG_INIT_DRAW_CONSOLE, &IW5Engine::CEngine::OnCG_InitDrawBranding, 0x0);
}

BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
	)

{
	if (fdwReason == DLL_PROCESS_ATTACH)
		if (CreateThread(NULL, 0x0, (LPTHREAD_START_ROUTINE)Init, (PVOID)NULL, 0x0, NULL) && CreateThread(NULL, NULL, &LoopFunction, NULL, NULL, NULL))
			return TRUE;

	return FALSE;
}