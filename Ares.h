#ifndef ARES_H
#define ARES_H

//ifndef str
#define str(x) str_(x)
#define str_(x) #x
//endif

#include <xcompile.h>
//include <YRPP.h>
#include <Helpers/Macro.h>

#include <CCINIClass.h>

#include "Misc/Debug.h"

#include <AircraftTypeClass.h>
#include <CellClass.h>
#include <HouseClass.h>
#include <InfantryTypeClass.h>
#include <UnitTypeClass.h>

#define GFX_DX_HW 0x01l
#define GFX_DX_EM 0x02l

#define GFX_SU_VRAM 0x00l
#define GFX_SU_SYSTEM 0x01l

#define GFX_SU_NF3D 0x00l
#define GFX_SU_F3D 0x01l

class Ares
{
public:
	//Global Options
	static HANDLE	hInstance;

	static bool bNoLogo;
	static bool bNoCD;

	static bool bTestingRun;

	static bool bLog;
	static FILE* pLogFile;

	static int TrackIndex;

	static DWORD readLength;
	static char readBuffer[BUFLEN];
	static const char readDelims[4];
	static const char readDefval[4];

	//Callbacks
	static void __stdcall CmdLineParse(char**,int);

	static void __stdcall ExeRun();
	static void __stdcall ExeTerminate();

	static void __stdcall PostGameInit();

	static void __stdcall RegisterCommands();

	//General functions
	static void SendPDPlane(
		HouseClass* pOwner,
		CellClass* pDestination,
		AircraftTypeClass* pPlaneType,
		TypeList<TechnoTypeClass*>* pTypes,
		TypeList<int>* pNums);

	class GlobalControls {
	private:
		GlobalControls() {};
	public:
		static CCINIClass * INI;

		static void OpenConfig();
		static void CloseConfig();
		static void LoadConfig();

		static void Load(CCINIClass *pINI);

		static bool Initialized;
		static bool AllowParallelAIQueues;

		static byte GFX_DX_Force;

		class SurfaceConfig {
		public:
			byte Force3D;
			byte Memory;
		};

		static SurfaceConfig GFX_S_Alternate;
		static SurfaceConfig GFX_S_Composite;
		static SurfaceConfig GFX_S_Hidden;
		static SurfaceConfig GFX_S_Hidden_2;
		static SurfaceConfig GFX_S_Primary;
		static SurfaceConfig GFX_S_Sidebar;
		static SurfaceConfig GFX_S_Tile;
	};

	static bool RunningOnWindows7OrVista();

};

class MemMap {
public:
	typedef hash_map <DWORD, size_t> memmap;
	static hash_map <DWORD, size_t> AllocMap;
	static size_t Total;

	static void Add(void * _addr, size_t amount) {
		DWORD addr = (DWORD)_addr;
		memmap::iterator i = AllocMap.find(addr);
		if(i != AllocMap.end()) {
#ifdef MEMORY_LOGGING
			Debug::Log("Reallocated a used block of 0x%X bytes @ 0x%X!\n", amount, addr);
#endif
		}
		AllocMap[addr] = amount;
		Total += amount;
	}

	static size_t Remove(void * _addr) {
		DWORD addr = (DWORD)_addr;
		memmap::iterator i = AllocMap.find(addr);
		if(i == AllocMap.end()) {
#ifdef MEMORY_LOGGING
			Debug::Log("Deallocated a dud block @ 0x%X!\n", addr);
#endif
			return 0;
		} else {
			size_t amount = AllocMap[addr];
			Total -= amount;
			AllocMap.erase(addr);
			return amount;
		}
	}
};

#endif
