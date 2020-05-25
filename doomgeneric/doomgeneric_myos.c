//doomgeneric for My OS

#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"

/*#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>*/

//#include <sosousdk.h>
//#include "../kernel/termios.h"

#include "../../MyOS_1/Interrupts/System_Calls.h"

static int FrameBufferFd = -1;
static int* FrameBuffer = 0;

static int KeyboardFd = -1;

SDL_Rect frameBufferInfo;

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned int s_PositionX = 0;
static unsigned int s_PositionY = 0;

static unsigned char convertToDoomKey(unsigned char scancode)
{
    unsigned char key = 0;

    switch (scancode)
    {
    case 0x9C:
    case 0x1C:
        key = KEY_ENTER;
        break;
    case 0x01:
        key = KEY_ESCAPE;
        break;
    case 0xCB:
    case 0x4B:
        key = KEY_LEFTARROW;
        break;
    case 0xCD:
    case 0x4D:
        key = KEY_RIGHTARROW;
        break;
    case 0xC8:
    case 0x48:
        key = KEY_UPARROW;
        break;
    case 0xD0:
    case 0x50:
        key = KEY_DOWNARROW;
        break;
    case 0x1D:
        key = KEY_FIRE;
        break;
    case 0x39:
        key = KEY_USE;
        break;
    case 0x2A:
    case 0x36:
        key = KEY_RSHIFT;
        break;
    case 0x15:
        key = 'y';
        break;
    default:
        break;
    }

    return key;
}

static void addKeyToQueue(int pressed, unsigned char keyCode)
{
	//printf("key hex %x decimal %d\n", keyCode, keyCode);

        unsigned char key = convertToDoomKey(keyCode);

        unsigned short keyData = (pressed << 8) | key;

        s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
        s_KeyQueueWriteIndex++;
        s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}


void DG_Init()
{
    printf("DG_Init()\n");

    bool graphicsPresent = false;
    int width, height;

    getGraphicsInfo(&graphicsPresent, &width, &height);

    if (!graphicsPresent)
    {
        printf("You need to be running in gfx mode!\n");
        exit(-1);
    }

    printf("Graphics subsystem detected, %d x %d\n", width, height);
    frameBufferInfo.x = 0;
    frameBufferInfo.y = 0;
    frameBufferInfo.w = width;
    frameBufferInfo.h = height;

    //FrameBuffer = malloc(width * height * 4);
    
    /*FrameBufferFd = open("/dev/fb0", 0);

    if (FrameBufferFd >= 0)
    {
        FrameBuffer = mmap(NULL, DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4, 0, FrameBufferFd, 0);

        if (FrameBuffer != (int*)-1)
        {
            printf("mmap success\n");
        }
        else
        {
            printf("mmap failed\n");
        }
    }
    else
    {
        printf("opening device failed!\n");
    }

    enableRawMode();

    KeyboardFd = open("/dev/keyboard", 0);

    if (KeyboardFd >= 0)
    {
        //enter non-blocking mode
        syscall_ioctl(KeyboardFd, 1, (void*)1);
    }

    int argPosX = 0;
    int argPosY = 0;

    argPosX = M_CheckParmWithArgs("-posx", 1);
    if (argPosX > 0)
    {
        sscanf(myargv[argPosX + 1], "%d", &s_PositionX);
    }

    argPosY = M_CheckParmWithArgs("-posy", 1);
    if (argPosY > 0)
    {
        sscanf(myargv[argPosY + 1], "%d", &s_PositionY);
    }*/
}

static void handleKeyInput()
{
    //printf("handleKeyInput()\n");
    uint16_t sc = 0;
    unsigned char scancode;

    while(readFromKeyboard(&sc))
    {
        scancode = sc & 0xff;

        unsigned char keyRelease = (0x80 & scancode);

        scancode = (0x7F & scancode);

        //printf("scancode:%x pressed:%d\n", scancode, 0 == keyRelease);
        //timeDelayMS(200);

        if (0 == keyRelease)
        {
            addKeyToQueue(1, scancode);
        }
        else
        {
            addKeyToQueue(0, scancode);
        }
    }
}

void DG_DrawFrame()
{
    //GraphicsBlit(0, 0, DG_ScreenBuffer, DOOMGENERIC_RESX, DOOMGENERIC_RESY);
    graphicsBlit(&frameBufferInfo, DG_ScreenBuffer);
    handleKeyInput();
    //timeDelayMS(10000);

    //printf(".");
    /*if (FrameBuffer)
    {
        //memcpy(FrameBuffer, DG_ScreenBuffer, DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);

        const int screenWidth = 1024;

        for (int i = 0; i < DOOMGENERIC_RESY; ++i)
        {
            memcpy(FrameBuffer + s_PositionX + (i + s_PositionY) * screenWidth, DG_ScreenBuffer + i * DOOMGENERIC_RESX, DOOMGENERIC_RESX * 4);
        }
    }

    */
}

void DG_SleepMs(uint32_t ms)
{
    //timeDelayMS(ms);
}

//uint32_t faketicks = 0;
uint32_t DG_GetTicksMs()
{
    return timeGetUptimeMS();
    //return ++faketicks;
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
    if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
    {
        //key queue is empty

        return 0;
    }
    else
    {
        unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
        s_KeyQueueReadIndex++;
        s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

        *pressed = keyData >> 8;
        *doomKey = keyData & 0xFF;

        return 1;
    }
}

void DG_SetWindowTitle(const char * title)
{
}

bool is_digit(char *str)
{
    if (*str >= '0' && *str <= '9')
        return true;

    return false;
}

unsigned int atoi(const char* str)
{
    unsigned int i = 0U;
    while (is_digit(*str)) {
        i = i * 10U + (unsigned int)(*((str)++) - '0');
    }
    return i;
}