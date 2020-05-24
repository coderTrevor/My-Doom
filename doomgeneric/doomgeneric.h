#ifndef DOOM_GENERIC
#define DOOM_GENERIC

#include "../../MyOS_1/Console_VGA.h"
#include "../../MyOS_1/Interrupts/System_Calls.h"
#include "../../MyOS_1/paging.h"
#include "../../MyOS_1/misc.h"
#include "../../MyOS_1/printf.h"
#include <stdint.h>

#define DOOMGENERIC_RESX 800
#define DOOMGENERIC_RESY 480


extern uint32_t* DG_ScreenBuffer;


void DG_Init();
void DG_DrawFrame();
void DG_SleepMs(uint32_t ms);
uint32_t DG_GetTicksMs();
int DG_GetKey(int* pressed, unsigned char* key);
void DG_SetWindowTitle(const char * title);

#endif //DOOM_GENERIC
