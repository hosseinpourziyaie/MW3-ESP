#include<Windows.h>
#include "IW5Engine.h"
#include "Colors.h"

#define OFFSET_DRAW_STRETCHPIC 0x4DF3C0
#define OFFSET_REGISTER_SHADER 0x41B6B0
#define OFFSET_DRAW_TEXT 0x42C970
#define OFFSET_DRAW_SHADER 0x4EE060
#define OFFSET_LOAD_SHADER 0x41B6B0
#define OFFSET_GET_TEXT_WIDTH 0x548A70
#define OFFSET_GET_FONT_HEIGHT_BY_SCALE_ONE 0x779000


typedef int (*DrawStretchPic_)(float x, float y, float w, float h, float s1, float t1, float s2, float t2, Vec4 color, int hShader); 
DrawStretchPic_ DrawStretchPic = (DrawStretchPic_)OFFSET_DRAW_STRETCHPIC;

void DrawPic(float x, float y, float h, float w, /*float * Color,*/ int Shader)
{
	DrawStretchPic(x, y, h, w, 0.0f, 0.0f, 1.0f, 1.0f, /*Color*/cRed, Shader);
}

int (__cdecl*IW5Engine::CEngine::LoadShader)(char* name) = (int(__cdecl*)(char*))OFFSET_LOAD_SHADER;

char*(__cdecl*IW5Engine::CEngine::CDraw::CDrawText)(char* text, size_t len, int Font, float x, float y, float sizex, float sizey, float rotate, Color_t* color, int zero) = (char*(__cdecl*)(char*, size_t, int, float, float, float, float, float, Color_t*, int))OFFSET_DRAW_TEXT;
char(__cdecl*IW5Engine::CEngine::CDraw::CDrawShader)(float x, float y, float sizex, float sizey, float unk0, float unk1, float unk2, float unk3, Color_t* color, int Shader) = (char(__cdecl*)(float, float, float, float, float, float, float, float, Color_t*, int))OFFSET_DRAW_SHADER;

int(__cdecl*IW5Engine::CEngine::GetTextWidth)(char* txt, int len, int font) = (int(__cdecl*)(char*, int, int))OFFSET_GET_TEXT_WIDTH;
int(__cdecl*IW5Engine::CEngine::GetFontHeightByScaleOne)(int font) = (int(__cdecl*)(int))OFFSET_GET_FONT_HEIGHT_BY_SCALE_ONE;


void HUDCall();

char(__cdecl*IW5Engine::CEngine::CG_InitDrawBranding)(int);

char IW5Engine::CEngine::OnCG_InitDrawBranding(int local)
{
	HUDCall();
	return CG_InitDrawBranding(local);
}

Color_t::Color_t(int R, int G, int B, int A)
{
	DWORD oldprotect = 0x0;

	VirtualProtect(this, 0x10, PAGE_EXECUTE_READWRITE, &oldprotect); // fk default memory protection, fast solution k...

	this->R = ((float)R / 255.0f); // 1.0f max to 255 -> so le formule math:  f(target) = 1.0f * target / 255, i've done this pFormula myself, idk if it's fine... i'm so lazy k...
	this->G = ((float)G / 255.0f);
	this->B = ((float)B / 255.0f);
	this->A = ((float)A / 255.0f);

	VirtualProtect(this, 0x10, oldprotect, NULL);
}

