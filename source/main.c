#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <switch.h>
#include "util.h"
#include "ini.h"

// Config //

#define TEXT_COLOR COLOR_PURPLE

///////////

char const *asciiart =
"\n\n\n\n\n\n"
"       ######\n"
"     ####  ####\n"
"    #####  #####\n"
"   ## ##    ## ##\n"
"   ##          ##\n"
"  ####        ####\n"
"  ####  ####  ####\n"
"  #### ###### ####\n"
"  #### ###### ####\n"
"  ###  ######  ###\n"
"  #     ####     #\n"
"  #  ##########  #\n"
"  ####  #  #  ####\n"
"   ##   #  #   ## \n"
"    #          #\n"
"    ##        ##\n"
"     ##########\n";

void printPos(char* string, int x, int y) {

	printf("%c[%d;%df",0x1B,y,x);

	printf(string);

	return 0;

}

void printLine(char* string1, char* string2, int x, int y) {

	printf(TEXT_COLOR); printPos(string1, x, y); printf(COLOR_CLEAR); printf(string2);

	return 0;

}

int main(int argc, char **argv)
{


    ini_t *config = ini_load("config.ini");

    const char *username =		ini_get(config, "config", "username");
    const char *hostname =		ini_get(config, "config", "hostname");
    const char *os =			ini_get(config, "config", "os");
    const char *firmware =		ini_get(config, "config", "firmware");
    const char *packages =		ini_get(config, "config", "packages");
    const char *shell = 		ini_get(config, "config", "shell");
    const char *resolution =	ini_get(config, "config", "resolution");
    const char *cpu =			ini_get(config, "config", "cpu");
    const char *memory =		ini_get(config, "config", "memory");
    const char *gpu =			ini_get(config, "config", "gpu");

    gfxInitDefault();
    consoleInit(NULL);

    int x = 20;
    printf(asciiart, 0, 0);

    // Main loop
    while(appletMainLoop())
    {
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        printLine(username, hostname, x, 6); // username@hostname

        printLine("OS: ", os, x, 8); // Don't have a better name for this

        printLine("Firmware: ", firmware, x, 10); // Detect it somehow?

        printLine("Packages: ", packages, x, 12); // Maybe get number of homebrew somehow?

        printLine("Shell: ", shell, x, 14); // 3DS can't really have a shell but whatever

        printLine("Resolution: ", resolution, x, 16); // Needs changed for 2DS

        printLine("CPU: ", cpu, x, 18); // This also needs changed for 2DS

        printLine("Memory: ", memory, x, 20); // Maybe get RAM usage somehow?

        printLine("GPU: ", gpu, x, 22);

        printf("\nPorted by Kneesox.", x, 24);
        printf("\nPress + too exit.", x, 26);

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }

    gfxExit();
    return 0;
}
