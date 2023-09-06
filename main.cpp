#include "minisyr.h"
// https://github.com/Ares-Developers/Ares/blob/master/src/Misc/CopyProtection.cpp

DEFINE_HOOK(0x4790E0, CD_AlwaysAvailable, 7)
{
	R->_EAX=1;
	return 0x479109;
}

DEFINE_HOOK(0x479110, CD_NeverAsk, 5)
{
	R->_EAX=1;
	return 0x4791EA;
}

DEFINE_HOOK(0x6BB9DD,Skip_LauncherRunningCheck,0)
{
    return 0x6BBE56;
}

DEFINE_HOOK(0x6BDD11,Skip_LauncherNotification,0)
{
    return 0x6BDD2E;
}

// this douchebag blows your base up when it thinks you're cheating
DEFINE_HOOK(0x55CFDF, BlowMeUp, 0)
{
    return 0x55D059;
}
