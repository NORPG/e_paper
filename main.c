#include "IT8951_USB.h"
#include <math.h>
#include <stdio.h>

unsigned char sense_buffer[SENSE_LEN];
unsigned char data_buffer[BLOCK_LEN * 256];

DWord gulPanelW, gulPanelH;

Byte src[(1600 * 1200)];

char *path;
int evpd, page_code;

int main(int argc, char *argv[])
{

    SystemInfo *Sys_info;	// SystemInfo structure

    path = argv[1];		// arg1: sg path of device
    evpd = page_code = 0;

    // 0x80: get system info
    Sys_info = (SystemInfo *) malloc(sizeof(SystemInfo));
    IT8951_Cmd_SysInfo(Sys_info);

    // set full white
    //*******************************************************************************************

    Byte srcW[(gulPanelW * gulPanelH)];
    memset((srcW), 0xF0, (gulPanelW * gulPanelH));	//All white
    IT8951_Cmd_LoadImageArea(srcW, (Sys_info->uiImageBufBase), 0, 0,
			     gulPanelW, gulPanelH);


    for (int times = 0; times <= 99; times++) {
	memset((src), 0xF0, (50 * 100));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 800, 600, 50, 100);	//_

	int timea = 0, timeb = 0;
	timea = times / 10;
	timeb = times % 10;


	if (timea == 0)
	    int0(Sys_info, src, 800, 600);
	else if (timea == 1)
	    int1(Sys_info, src, 800, 600);
	else if (timea == 2)
	    int2(Sys_info, src, 800, 600);
	else if (timea == 3)
	    int3(Sys_info, src, 800, 600);
	else if (timea == 4)
	    int4(Sys_info, src, 800, 600);
	else if (timea == 5)
	    int5(Sys_info, src, 800, 600);
	else if (timea == 6)
	    int6(Sys_info, src, 800, 600);
	else if (timea == 7)
	    int7(Sys_info, src, 800, 600);
	else if (timea == 8)
	    int8(Sys_info, src, 800, 600);
	else if (timea == 9)
	    int9(Sys_info, src, 800, 600);

	if (timeb == 0)
	    int0(Sys_info, src, 800, 650);
	else if (timeb == 1)
	    int1(Sys_info, src, 800, 650);
	else if (timeb == 2)
	    int2(Sys_info, src, 800, 650);
	else if (timeb == 3)
	    int3(Sys_info, src, 800, 650);
	else if (timeb == 4)
	    int4(Sys_info, src, 800, 650);
	else if (timeb == 5)
	    int5(Sys_info, src, 800, 650);
	else if (timeb == 6)
	    int6(Sys_info, src, 800, 650);
	else if (timeb == 7)
	    int7(Sys_info, src, 800, 650);
	else if (timeb == 8)
	    int8(Sys_info, src, 800, 650);
	else if (timeb == 9)
	    int9(Sys_info, src, 800, 650);
	IT8951_Cmd_DisplayArea(800, 600, 50, 100, 2,
			       (Sys_info->uiImageBufBase), 1);
    }




    IT8951_Cmd_DisplayArea(0, 0, gulPanelW, gulPanelH, 2,
			   (Sys_info->uiImageBufBase), 1);
    //*********************************************************************************************/

    // 0xA4: temperature
    TempArg TempTest;
    TempTest.ucSetTemp = 0;	// 0: read, 1: write
    TempTest.ucTempVal = 126;	// set value if wanna write
    IT8951_Cmd_SetTemp(TempTest);

    free(Sys_info);
    return EXIT_SUCCESS;
}
