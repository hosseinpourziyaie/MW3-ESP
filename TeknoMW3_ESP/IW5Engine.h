//#include "Colors.h"

#define OFFSET_CONSOLE_FONT 0xFB457C
#define OFFSET_HUD_SMALL_FONT 0x58DD3D0
#define OFFSET_OBJECTIVE_FONT 0x58DD3C8
#define OFFSET_WHITE_SHADER 0xFB4574
#define OFFSET_CG_INIT_DRAW_CONSOLE 0x4D6280
#define OFFSET_SCREEN_SIZE 0x1338050
#define ScreenSize (*(IW5Engine::CEngine::ScreenSize_t*)OFFSET_SCREEN_SIZE)

#define GetConsoleFont() (*(DWORD*)OFFSET_CONSOLE_FONT)
#define GetHudSmallFont() (*(DWORD*)OFFSET_HUD_SMALL_FONT)
#define GetObjectiveFont() (*(DWORD*)OFFSET_OBJECTIVE_FONT)
#define GetWhiteShader() (*(DWORD*)OFFSET_WHITE_SHADER)

struct Color_t
{
	float R;
	float G;
	float B;
	float A;
	Color_t();
	Color_t(int R, int G, int B, int A);
};

class IW5Engine
{
public:

	static void Init();

	struct CEngine
	{
		static int(*R_RegisterShader)(char *ShaderName);

		static char __cdecl OnCG_InitDrawBranding(int local);
		static char(__cdecl*CG_InitDrawBranding)(int local);

		static int(__cdecl*LoadShader)(char* name);

		static int(__cdecl*GetTextWidth)(char* text, int len, int font);
		static int(__cdecl*GetFontHeightByScaleOne)(int font);

		typedef struct
		{
			float x;
			float y;

		} ScreenSize_t;

		struct CDraw
		{
			static Color_t TestColor;

			static char*(__cdecl*CDrawText)(char* text, size_t len, int Font, float x, float y, float sizex, float sizey, float rotate, Color_t* color, int zero);
			static char(__cdecl*CDrawShader)(float x, float y, float sizex, float sizey, float unk0, float unk1, float unk2, float unk3, Color_t* color, int Shader);
		};
	};
};