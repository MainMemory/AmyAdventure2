#include "stdafx.h"
#include "SA2ModLoader.h"
#include "BossTitles.h"

enum BossTitleLetterIDs
{
	space,
	_A = 1000000,
	_C,
	_D,
	dot,
	_E,
	_G,
	_H,
	_I,
	_L,
	_M,
	_N,
	_O,
	_R,
	_S,
	_T,
	_U,
	_W,
	_Y,
	_K = 1000030
};

NJS_TEXNAME AmyBossTitleTexName[3];

NJS_TEXLIST AmyBossTitleTex{ arrayptrandlengthT(AmyBossTitleTexName, Uint32) };

BossTitleLetterData AmyBossTitleLetters[]
{
	{ _A, 18, 16, 0, 32, 16, 0 },
	{ _M, 22, 16, 0, 32, 16, 0 },
	{ _Y, 16, 16, 0, 16, 16, 0 },
};

BossTitleData AmyBossTitle{ arrayptrandlengthT(AmyBossTitleLetters, short), 0xC, 0x14, 0, 0x30000, 480, &AmyBossTitleTex, 320, 240, 2, 0xFFFFFF };

void LoadBossTitle(char id)
{
	BossTitleData* title = &AmyBossTitle;
	switch (CurrentLevel)
	{
	case LevelIDs_SonicVsShadow1:
	case LevelIDs_TailsVsEggman1:
	case LevelIDs_SonicVsShadow2:
		title->DisplayTime = 360;
		break;
	case LevelIDs_TailsVsEggman2:
	case LevelIDs_KnucklesVsRouge:
		title->DisplayTime = 480;
		break;
	}
	LoadBossTitleExec(nullptr, title);
}

const void* const loc_4C8142 = (void*)0x4C8142;
__declspec(naked) void LoadShadow2BossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_4C8142
	}
}

const void* const loc_619D4C = (void*)0x619D4C;
__declspec(naked) void LoadShadow1BossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_619D4C
	}
}

const void* const loc_6273E7 = (void*)0x6273E7;
__declspec(naked) void LoadEggman1BossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_6273E7
	}
}

const void* const loc_649C91 = (void*)0x649C91;
__declspec(naked) void LoadRougeBossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_649C91
	}
}

const void* const loc_662A7B = (void*)0x662A7B;
__declspec(naked) void LoadEggman2BossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_662A7B
	}
}

FunctionPointer(void, ReleaseTextureList, (NJS_TEXLIST* a1), 0x77F9F0);
void FreeAmyBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(AmyBossTitle.TexList);
}

void LoadBossTitleTex(ObjectMaster* obj, char id)
{
	LoadTextureList((char*)"TITLETEX_AMY", AmyBossTitle.TexList);
	obj->DeleteSub = FreeAmyBossTitleTex;
}

const void* const loc_4C909C = (void*)0x4C909C;
__declspec(naked) void LoadShadow2BossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_4C909C
	}
}

const void* const loc_61A383 = (void*)0x61A383;
__declspec(naked) void LoadShadow1BossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_61A383
	}
}

const void* const loc_627D02 = (void*)0x627D02;
__declspec(naked) void LoadEggman1BossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_627D02
	}
}

const void* const loc_64B7A0 = (void*)0x64B7A0;
__declspec(naked) void LoadRougeBossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_64B7A0
	}
}

const void* const loc_6639D9 = (void*)0x6639D9;
__declspec(naked) void LoadEggman2BossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_6639D9
	}
}

void InitBossTitles()
{
	WriteJump((void*)0x4C8124, LoadShadow2BossTitle);
	WriteJump((void*)0x4C9061, LoadShadow2BossTitleTex);
	WriteJump((void*)0x619D2E, LoadShadow1BossTitle);
	WriteJump((void*)0x61A348, LoadShadow1BossTitleTex);
	WriteJump((void*)0x6273C9, LoadEggman1BossTitle);
	WriteJump((void*)0x627CC7, LoadEggman1BossTitleTex);
	WriteJump((void*)0x649C73, LoadRougeBossTitle);
	WriteJump((void*)0x64B765, LoadRougeBossTitleTex);
	WriteJump((void*)0x662A5D, LoadEggman2BossTitle);
	WriteJump((void*)0x66399E, LoadEggman2BossTitleTex);
}