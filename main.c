#include "IT8951_USB.h"
#include <math.h>
#include <stdio.h>

unsigned char sense_buffer[SENSE_LEN];
unsigned char data_buffer[BLOCK_LEN * 256];

DWord gulPanelW, gulPanelH;


char *path;
int evpd, page_code;

int main(int argc, char *argv[])
{

    Byte src[(1600 * 1200)];
    SystemInfo *Sys_info;	// SystemInfo structure

    path = argv[1];		// arg1: sg path of device
    evpd = page_code = 0;

    /*
     * 0x80: get system info
     */
    Sys_info = (SystemInfo *) malloc(sizeof(SystemInfo));
    IT8951_Cmd_SysInfo(Sys_info);

    /* 
     * set full white
     */
    memset((src), 0xF0, (gulPanelW * gulPanelH));	//All white
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 0, 0,
			     gulPanelW, gulPanelH);

    for (int times = 0; times <= 99; times++) {
	memset((src), 0xF0, (50 * 100));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 800, 600, 50, 100);	//_

	int timea = 0, timeb = 0;
	timea = times / 10;
	timeb = times % 10;

	dis_num(Sys_info, src, timea, 800, 600);
	dis_num(Sys_info, src, timeb, 800, 650);

	IT8951_Cmd_DisplayArea(800, 600, 50, 100, 2,
			       (Sys_info->uiImageBufBase), 1);
    }

    IT8951_Cmd_DisplayArea(0, 0, gulPanelW, gulPanelH, 2,
			   (Sys_info->uiImageBufBase), 1);

    free(Sys_info);
    return EXIT_SUCCESS;
}
