// AmyAdventure2.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "IniFile.hpp"
#include "SA2ModLoader.h"
#include "AnimationFile.h"
#include "ModelInfo.h"
#include "BossTitles.h"

const int battlechars[] = { 0, 1, 4, 5, 7, 8, 9 };
char savedtheme;
const char nopjmp[] = { 0x90, 0xE9 };
const char btlmenunamepatch[] = { 0xB8, 6, 0, 0, 0, 0x90 };
void (*SetWindowTitle)(const wchar_t* title) = nullptr;

extern "C"
{
	__declspec(dllexport) void OnFrame()
	{
		CurrentTheme = 7;
		if (SetWindowTitle)
		{
			SetWindowTitle(L"AMY ADVENTURE 2");
			SetWindowTitle = nullptr;
		}
	}

	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		// 2P Battle Menu
		HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));
		CharaObjectData *cod = (CharaObjectData *)GetProcAddress(hmodule, "_charaObject");
		for (int i = 0; i < 12; i++)
			cod[i].TextBackTexture = cod[6].TextBackTexture;
		for (int i : battlechars)
		{
			cod[i].MainModel = cod[6].MainModel;
			if (i == 5)
			{
				cod[i].Animation1 = cod[6].Animation1;
				cod[i].Animation2 = cod[6].Animation2;
				cod[i].Animation3 = cod[6].Animation3;
			}
			cod[i].AccessoryModel = cod[6].AccessoryModel;
			cod[i].AccessoryAttachNode = cod[6].AccessoryAttachNode;
			if (cod[i].SuperModel)
				cod[i].SuperModel = cod[6].MainModel;
		}
		cod[1].Animation1 = (new AnimationFile(std::string(path) + "\\ShadowMenu\\Animation1.saanim"))->getmotion();
		cod[1].Animation2 = (new AnimationFile(std::string(path) + "\\ShadowMenu\\Animation2.saanim"))->getmotion();
		cod[1].Animation3 = (new AnimationFile(std::string(path) + "\\ShadowMenu\\Animation3.saanim"))->getmotion();
		ModelInfo* mdlinf = new ModelInfo(std::string(path) + "\\Battle Menu\\Tails.sa2mdl");
		cod[2].MainModel = mdlinf->getmodel();
		mdlinf = new ModelInfo(std::string(path) + "\\Battle Menu\\Eggman.sa2mdl");
		cod[3].MainModel = mdlinf->getmodel();
		cod[3].AccessoryAttachNode = (NJS_OBJECT*)mdlinf->getdata("object_0033E884");
		mdlinf = new ModelInfo(std::string(path) + "\\Battle Menu\\Chao Walker.sa2mdl");
		cod[10].MainModel = mdlinf->getmodel();
		cod[10].AccessoryAttachNode = (NJS_OBJECT*)mdlinf->getdata("object_003C52F4");
		mdlinf = new ModelInfo(std::string(path) + "\\Battle Menu\\Dark Chao Walker.sa2mdl");
		cod[11].MainModel = mdlinf->getmodel();
		cod[11].AccessoryAttachNode = (NJS_OBJECT*)mdlinf->getdata("object_003D2E84");
		mdlinf = new ModelInfo(std::string(path) + "\\Battle Menu\\Neutral Chao.sa2mdl");
		cod[12].MainModel = mdlinf->getmodel();
		mdlinf = new ModelInfo(std::string(path) + "\\Battle Menu\\Hero Chao.sa2mdl");
		cod[13].MainModel = mdlinf->getmodel();
		mdlinf = new ModelInfo(std::string(path) + "\\Battle Menu\\Dark Chao.sa2mdl");
		cod[14].MainModel = mdlinf->getmodel();
		WriteData((void*)0x68098E, btlmenunamepatch);
		// Rouge
		WriteData<char>((char*)0x72876E, 0xEBu); // disable head jiggle
		WriteJump((void*)0x730FEF, (void*)0x73112A); // hide upgrades
		// Chaos
		WriteJump((void*)0x731F06, (void*)0x731FAA);
		WriteData<5>((void*)0x732661, 0x90u);
		WriteJump((void*)0x732579, (void*)0x73261F);
		WriteData<char>((char*)0x7326B4, 0x59);
		WriteJump((void*)0x7326B5, (void*)0x7326EC);
		WriteData<char>((char*)0x7326D6, 0x59);
		WriteJump((void*)0x7326D7, (void*)0x7326EC);
		// Title Card
		WriteData((const char **)0x472AD6, "MISSIONTEX_AM");
		WriteData((const char **)0x472AF7, "MISSIONTEX_AM2");
		// Life Icons
		for (int i = 0; i < LifeIconTexs_Length; i++)
			LifeIconTexs[i] = LifeIconTexs[Characters_Amy];
		WriteData<char>((char*)0x44E5EC, 0xEBu);
		WriteData<2>((void*)0x44E631, 0x90u);
		WriteData<2>((void*)0x44E636, 0x90u);
		WriteData<2>((void*)0x44E63B, 0x90u);
		WriteData<2>((void*)0x44E646, 0x90u);
		WriteData((NJS_TEXLIST**)0x727E84, &TexList_AmyLife);
		WriteData((NJS_TEXLIST**)0x727E8B, &TexList_AmyLife);
		WriteData((NJS_TEXLIST**)0x727E99, &TexList_AmyLife);
		// Disable theme select
		WriteData<char>((char*)0x66DF08, 0xEBu);
		// Save selected theme
		WriteData((char**)0x4438CA, &savedtheme);
		WriteData((char**)0x44526E, &savedtheme);
		WriteData((char**)0x446619, &savedtheme);
		WriteData((char**)0x446756, &savedtheme);
		WriteData((char**)0x446900, &savedtheme);
		// Title Screen
		WriteData((void*)0x667F27, nopjmp);
		WriteData<6>((void*)0x66F8DD, 0x90u);
		WriteData((void*)0x66FEB4, nopjmp);
		WriteData<6>((void*)0x670449, 0x90u);
		// Chao
		NJS_OBJECT** AL_RootObject = (NJS_OBJECT**)GetProcAddress(hmodule, "AL_RootObject");
		for (size_t i = 0; i < 138; i++)
			AL_RootObject[i] = AL_RootObject[138];
		WriteJump((void*)0x54FFCD, (void*)0x54FFDD);
		// Omochao
		mdlinf = new ModelInfo(std::string(path) + "\\amyomohead.sa2mdl");
		WriteData((NJS_CNK_MODEL**)0xB5C8A4, mdlinf->getmodel()->chunkmodel);
		WriteData((short*)0x6C0112, (short)0xA190);
		WriteCall((void*)0x6C0118, (void*)0x42E6C0);
		// Boss Titles
		InitBossTitles();
		// Settings
		const IniFile *settings = new IniFile(std::string(path) + "\\config.ini");
		// Rouge's wings
		if (settings->getBool("", "RemoveWings"))
			WriteData<char>((char*)0x730F62, 0xEBu);
		// Alternate Costumes
		if (helperFunctions.Version >= 7 && settings->getBool("", "UseAltCostumes"))
		{
			WriteJump((void*)0x716F25, (void*)0x716F3F); // Sonic
			WriteJump((void*)0x717485, (void*)0x71749F); // Shadow
		}
		delete settings;
		if (helperFunctions.Version >= 7)
			SetWindowTitle = helperFunctions.SetWindowTitle;
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}