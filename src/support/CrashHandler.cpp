// NOTE: Not in the original. Writes a symbolized stack trace and a minidump
// when the game crashes, so test runs can report where it happened.
//
// Output goes to the folder in `IWD2RE_CRASH_DIR`, or the current directory:
//   iwd2re-crash.txt  exception code, address and stack with file:line
//   iwd2re-crash.dmp  minidump for a debugger

#include "CrashHandler.h"

#include <windows.h>

#include <dbghelp.h>
#include <stdio.h>

#pragma comment(lib, "dbghelp.lib")

static char gCrashDir[MAX_PATH];

static void CrashPath(char* buffer, size_t size, const char* fileName)
{
    _snprintf(buffer, size, "%s\\%s", gCrashDir, fileName);
    buffer[size - 1] = '\0';
}

static void WriteStack(FILE* stream, CONTEXT* pContext)
{
    HANDLE hProcess = GetCurrentProcess();
    HANDLE hThread = GetCurrentThread();

    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
    SymInitialize(hProcess, NULL, TRUE);

    CONTEXT context = *pContext;
    STACKFRAME64 frame = { 0 };
    frame.AddrPC.Offset = context.Eip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context.Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context.Esp;
    frame.AddrStack.Mode = AddrModeFlat;

    char symbolBuffer[sizeof(SYMBOL_INFO) + 256];
    for (int index = 0; index < 64; index++) {
        if (!StackWalk64(IMAGE_FILE_MACHINE_I386, hProcess, hThread, &frame, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL)) {
            break;
        }

        DWORD64 address = frame.AddrPC.Offset;
        if (address == 0) {
            break;
        }

        SYMBOL_INFO* pSymbol = reinterpret_cast<SYMBOL_INFO*>(symbolBuffer);
        memset(symbolBuffer, 0, sizeof(symbolBuffer));
        pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        pSymbol->MaxNameLen = 255;

        DWORD64 displacement = 0;
        const char* name = SymFromAddr(hProcess, address, &displacement, pSymbol) ? pSymbol->Name : "?";

        IMAGEHLP_LINE64 line = { 0 };
        line.SizeOfStruct = sizeof(line);
        DWORD lineDisplacement = 0;
        if (SymGetLineFromAddr64(hProcess, address, &lineDisplacement, &line)) {
            fprintf(stream, "  #%02d %08llX %s+0x%llX  %s:%lu\n", index, address, name, displacement, line.FileName, line.LineNumber);
        } else {
            fprintf(stream, "  #%02d %08llX %s+0x%llX\n", index, address, name, displacement);
        }
    }

    SymCleanup(hProcess);
}

static LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo)
{
    char path[MAX_PATH];

    CrashPath(path, sizeof(path), "iwd2re-crash.txt");
    FILE* stream = fopen(path, "w");
    if (stream != NULL) {
        EXCEPTION_RECORD* pRecord = pExceptionInfo->ExceptionRecord;
        fprintf(stream, "exception %08lX at %p", pRecord->ExceptionCode, pRecord->ExceptionAddress);
        if (pRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && pRecord->NumberParameters >= 2) {
            fprintf(stream, " (%s %p)", pRecord->ExceptionInformation[0] ? "write" : "read", reinterpret_cast<void*>(pRecord->ExceptionInformation[1]));
        }
        fprintf(stream, "\nstack:\n");
        WriteStack(stream, pExceptionInfo->ContextRecord);
        fclose(stream);
    }

    CrashPath(path, sizeof(path), "iwd2re-crash.dmp");
    HANDLE hFile = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        MINIDUMP_EXCEPTION_INFORMATION info;
        info.ThreadId = GetCurrentThreadId();
        info.ExceptionPointers = pExceptionInfo;
        info.ClientPointers = FALSE;
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &info, NULL, NULL);
        CloseHandle(hFile);
    }

    return EXCEPTION_EXECUTE_HANDLER;
}

void InstallCrashHandler()
{
    DWORD length = GetEnvironmentVariableA("IWD2RE_CRASH_DIR", gCrashDir, sizeof(gCrashDir));
    if (length == 0 || length >= sizeof(gCrashDir)) {
        GetCurrentDirectoryA(sizeof(gCrashDir), gCrashDir);
    }

    SetUnhandledExceptionFilter(UnhandledExceptionHandler);
}
