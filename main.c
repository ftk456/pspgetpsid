#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <pspdisplay.h>
#include <pspiofilemgr.h>
#include <pspopenpsid.h>

PSP_MODULE_INFO("Homebrew", PSP_MODULE_USER, 1, 0);

int exit_callback(int arg1, int arg2, void* common)
{
    sceKernelExitGame();
    return 0;
}

int exit_thread(SceSize args, void* argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, 0);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int SetupCallback(void)
{
    int thid = sceKernelCreateThread("exit_thread", exit_thread, 0x10, 0xFA, 0, NULL);

    if (thid >= 0)
    {
        sceKernelStartThread(thid, 0, 0);
    }

    return thid;
}

int main()
{
    pspDebugScreenInit();
    SetupCallback();

    PspOpenPSID PSID;
    //sceOpenPSIDGetOpenPSID(&PSID); gives unidefed reference error while compiling
    pspDebugScreenPrintf("The PSID of your PSP is", PSID);

    SceUID pFile = sceIoOpen("ms0:", PSP_O_WRONLY | PSP_O_CREAT, 0777);
    if (pFile != 0)
    {
        sceIoWrite(pFile, &PSID, sizeof(PSID));
        sceIoClose(pFile);
    }

    pspDebugScreenPrintf("\n And it has been wrote to the file PSID.txt");

    sceKernelSleepThread();

    return 0;
}
