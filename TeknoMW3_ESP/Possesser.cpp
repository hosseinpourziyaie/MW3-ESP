#include <windows.h>

void MakeDirectJUMP(void* from, void* to)
{
	DWORD Difference = ((DWORD)to - (DWORD)from - 0x5);
	
	DWORD DefaultProtection = 0x0;

	VirtualProtect(from, 0x5, PAGE_EXECUTE_READWRITE, &DefaultProtection);
	
	// near jump
	*(BYTE*)from = 0xE9; 

	*(DWORD*)&(((BYTE*)from)[1]) = Difference;

	VirtualProtect(from, 0x5, DefaultProtection, NULL);
}


void* MakeDirectJUMP(void* from, void* to, size_t bytestosave)
{
	size_t len = bytestosave + 0x5 + 0x5; // bytes apart of new jump + new jump

	void* memory = malloc(len);

	memset(memory, 0x0, len);

	DWORD memusedsize = bytestosave + 0x5;

	DWORD newaddr = ((DWORD)from + memusedsize);

	memcpy(memory, from, memusedsize);

	((BYTE*)memory)[memusedsize] = 0xE9;

	DWORD Difference = (newaddr - (DWORD)(&((BYTE*)memory)[memusedsize]) - 0x5);

	*(DWORD*)&(((BYTE*)memory)[memusedsize + 1]) = Difference;

	Difference = ((DWORD)to - (DWORD)from - 0x5);

	DWORD DefaultProtection = 0x0;

	VirtualProtect(from, 0x5, PAGE_EXECUTE_READWRITE, &DefaultProtection);

	// near jump
	*(BYTE*)from = 0xE9;

	*(DWORD*)&(((BYTE*)from)[1]) = Difference;

	VirtualProtect(from, 0x5, DefaultProtection, NULL);

	// set same protection
	VirtualProtect(memory, len, DefaultProtection, NULL);

	return memory;
}


void PatchNOP(DWORD addr, size_t len)
{
	memset((void*)addr, 0x90, len);
}
