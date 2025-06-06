#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <pspdisplay.h>
#include <pspiofilemgr.h>
#include <pspopenpsid.h>
#include <string.h>

PSP_MODULE_INFO("Homebrew", PSP_MODULE_USER, 1, 0);

int exit_callback(int arg1, int agr2, void* common)
{
    sceKernelExitGame();
    return 0;
}

int Callback(SceSize args, void* argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int SetupCallbacks(void)
{
    int thid = 0;
    thid = sceKernelCreateThread("update_thread", Callback, 0x10, 0xFA, 0, NULL);

    if (thid >= 0)
    {
        sceKernelStartThread(thid, 0, 0);
    }

    return thid;
}

int main(void)
{
    pspDebugScreenInit();
    SetupCallbacks();

    PspOpenPSID PSID;
    sceOpenPSIDGetOpenPSID(&PSID);

    pspDebugScreenPrintf("Your PSP's PSID is %X", PSID);

    SceUID pFile = sceIoOpen("ms0:/PSID.txt", PSP_O_WRONLY | PSP_O_CREAT, 0777);
    if (pFile != NULL)
    {
        char buffer[16];
        strcat(buffer, PSID.data);
        sceIoWrite(pFile, buffer, sizeof(PSID));
        sceIoClose(pFile);
    }

    pspDebugScreenPrintf("\nAnd it has been saved in the file PSID.txt");

    sceKernelSleepThreadCB();
    return 0;
}
