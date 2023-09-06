#pragma once
#include <windows.h>

struct REGISTERS
{
    DWORD origin;
    DWORD flags;

    DWORD _EDI;
    DWORD _ESI;
    DWORD _EBP;
    DWORD _ESP;
    DWORD _EBX;
    DWORD _EDX;
    DWORD _ECX;
    DWORD _EAX;
};
#pragma pack(push, 16)
#pragma warning(push)
#pragma warning(disable : 4324)

#ifdef __MINGW32__
__attribute__((aligned(16)))
#elif defined(_MSC_VER)
__declspec(align(16))
#endif
struct hookdecl
{
    unsigned int hookAddr;
    unsigned int hookSize;
    const char *hookName;

    constexpr hookdecl(int add, int size, const char *name) : hookAddr(add), hookSize(size), hookName(name) {}
};
#pragma warning(pop)
#pragma pack(pop)

#pragma section(".syhks00", read, write)
#ifdef __MINGW32__
#define SYHKSECTION __attribute__((section(".syhks00")))
#elif defined(_MSC_VER)
#define SYHKSECTION __declspec(allocate(".syhks00"))
#endif

#define DEFINE_HOOK(hook, funcname, size)                                 \
    SYHKSECTION hookdecl _hk__##funcname##hook = {hook, size, #funcname}; \
    EXTERN_C __declspec(dllexport) DWORD __cdecl funcname(REGISTERS *R)
