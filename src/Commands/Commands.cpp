#include "Commands.h"

// include other commands like this
#include "AIControl.h"
#include "MapSnapshot.h"
//include "FrameByFrame.h"
#include "AIBasePlan.h"
#include "DumpTypes.h"
#include "DumpMemory.h"
//#include "Debugging.h"
//include "Logging.h"
#include "FPSCounter.h"
#include "TogglePower.h"

void Ares::RegisterCommands()
{
	if(bAllowAIControl) {
		MakeCommand<AIControlCommandClass>();
	}
	MakeCommand<MapSnapshotCommandClass>();
	//MakeCommand<TestSomethingCommandClass>();
	MakeCommand<DumperTypesCommandClass>();
	MakeCommand<MemoryDumperCommandClass>();
	//MakeCommand<DebuggingCommandClass>();
	MakeCommand<AIBasePlanCommandClass>();
	MakeCommand<FPSCounterCommandClass>();
	MakeCommand<TogglePowerCommandClass>();
}

DEFINE_HOOK(533058, CommandClassCallback_Register, 7)
{
	Ares::RegisterCommands();

	DWORD* D = GameCreate<DWORD>();
	R->EAX(D);	//Allocate SetUnitTabCommandClass
	return 0x533062;
}
