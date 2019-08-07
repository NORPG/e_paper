#include "IT8951_USB.h"
#include <math.h>
#include <stdio.h>

unsigned char sense_buffer[SENSE_LEN];
unsigned char data_buffer[BLOCK_LEN * 256];

DWord gulPanelW, gulPanelH;

//Byte srcW[(gulPanelW*gulPanelH)];
Byte src[(1600 * 1200)];

char *path;
int evpd, page_code;

int main(int argc, char *argv[])
{

    SystemInfo *Sys_info;	// SystemInfo structure

    path = argv[1];		// arg1: sg path of device
    evpd = page_code = 0;

    // 0x12: get device name
    //IT8951_Cmd_Inquiry();


    // 0x80: get system info
    Sys_info = (SystemInfo *) malloc(sizeof(SystemInfo));
    IT8951_Cmd_SysInfo(Sys_info);


    // 0x81: read memory
    /*
       Byte *revBuf = (Byte*)malloc(sizeof(Byte)*16);
       IT8951_Cmd_MemRead(Sys_info->uiImageBufBase, 16, revBuf);
       for(int i=0; i<16; i++){
       printf("%d, %X\n", i, revBuf[i]);    
       }
     */


    // 0x83: read register
    /*
       DWord revVal;
       IT8951_Cmd_RegRead(0x1800110C, &revVal);     // panel width
       printf("0x%X\n", revVal);    
     */


    // 0xA2 & 0x94: load & display

    // Mode 0: initial
    //IT8951_Cmd_DisplayArea(0, 0, gulPanelW, gulPanelH, 0, (Sys_info->uiImageBufBase), 1);

    // set full white
    //*******************************************************************************************

    Byte srcW[(gulPanelW * gulPanelH)];
    memset((srcW), 0xF0, (gulPanelW * gulPanelH));	//All white
    IT8951_Cmd_LoadImageArea(srcW, (Sys_info->uiImageBufBase), 0, 0,
			     gulPanelW, gulPanelH);


    //partial load(200x200, 4 times) & display(400x400)
    //Byte src[(1600*1200)];

    /*
       memset((src), 0x30, (50*50)); //0x30=>BLACK // a char 80x80
       IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 0, 0, 50, 50);//0,0=>start location
     */
    //int1(0,0);
    for (int times = 0; times <= 99; times++) {
	memset((src), 0xF0, (50 * 100));
	IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 800, 600, 50, 100);	//_

	int timea = 0, timeb = 0;
	timea = times / 10;
	timeb = times % 10;


	if (timea == 0)
	    int0(Sys_info, 800, 600);
	else if (timea == 1)
	    int1(Sys_info, 800, 600);
	else if (timea == 2)
	    int2(Sys_info, 800, 600);
	else if (timea == 3)
	    int3(Sys_info, 800, 600);
	else if (timea == 4)
	    int4(Sys_info, 800, 600);
	else if (timea == 5)
	    int5(Sys_info, 800, 600);
	else if (timea == 6)
	    int6(Sys_info, 800, 600);
	else if (timea == 7)
	    int7(Sys_info, 800, 600);
	else if (timea == 8)
	    int8(Sys_info, 800, 600);
	else if (timea == 9)
	    int9(Sys_info, 800, 600);

	if (timeb == 0)
	    int0(Sys_info, 800, 650);
	else if (timeb == 1)
	    int1(Sys_info, 800, 650);
	else if (timeb == 2)
	    int2(Sys_info, 800, 650);
	else if (timeb == 3)
	    int3(Sys_info, 800, 650);
	else if (timeb == 4)
	    int4(Sys_info, 800, 650);
	else if (timeb == 5)
	    int5(Sys_info, 800, 650);
	else if (timeb == 6)
	    int6(Sys_info, 800, 650);
	else if (timeb == 7)
	    int7(Sys_info, 800, 650);
	else if (timeb == 8)
	    int8(Sys_info, 800, 650);
	else if (timeb == 9)
	    int9(Sys_info, 800, 650);
	IT8951_Cmd_DisplayArea(800, 600, 50, 100, 2,
			       (Sys_info->uiImageBufBase), 1);
    }




    //IT8951_Cmd_LoadImageArea(srcW, (Sys_info->uiImageBufBase), 0, 0, gulPanelW, gulPanelH); 
    IT8951_Cmd_DisplayArea(0, 0, gulPanelW, gulPanelH, 2,
			   (Sys_info->uiImageBufBase), 1);
    //*********************************************************************************************/


    // partial load(200x200, 4 times) & display(400x400)
    //Byte src[(200*200)];
    //memset((src), 0xF0, (200*200));
    //IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 0, 0, 200, 200);

    //memset((src), 0x00, (200*200));
    //IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 200, 200, 200, 200);

    //memset((src), 0x30, (200*200));
    //IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 0, 200, 200, 200);

    //memset((src), 0x80, (200*200));
    //IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), 200, 0, 200, 200);

    //IT8951_Cmd_DisplayArea(0, 0, 400, 400, 2, (Sys_info->uiImageBufBase), 1);

    // 0xA4: temperature
    TempArg TempTest;
    TempTest.ucSetTemp = 0;	// 0: read, 1: write
    TempTest.ucTempVal = 126;	// set value if wanna write
    IT8951_Cmd_SetTemp(TempTest);

    free(Sys_info);
    return EXIT_SUCCESS;
}

void int1(SystemInfo * Sys_info, int x, int y)
{
    // Byte src[(1600*1200)];
    memset((src), 0x00, (30 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10,
			     y + 23, 30, 4);
}

void int2(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 10));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 10));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

    memset((src), 0x00, (15 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 15, 4);	//|

    memset((src), 0x00, (15 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 36, 15, 4);	//|
}

void int3(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

    memset((src), 0x00, (19 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 15, 4);	//|

    memset((src), 0x00, (15 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 36, 15, 4);	//|
}

void int4(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

    memset((src), 0x00, (19 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 19, 4);	//|

    memset((src), 0x00, (3 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 34, 4);	//|
}

void int5(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

    memset((src), 0x00, (19 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 15, 4);	//|

    memset((src), 0x00, (15 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 15, 4);	//|
}

void int6(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

    memset((src), 0x00, (34 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 34, 4);	//|

    memset((src), 0x00, (15 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 15, 4);	//|
}

void int7(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

    memset((src), 0x00, (19 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 15, 4);	//|

    memset((src), 0x00, (30 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 30, 4);	//|
}

void int8(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 30);	//_

    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 30);	//-

    memset((src), 0x00, (30 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 30, 4);	//|

    memset((src), 0x00, (30 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 36, 30, 4);	//|
}

void int9(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 26);	//_

    memset((src), 0x00, (4 * 30));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 4, 26);	//-

    memset((src), 0x00, (15 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 25, y + 10, 15, 4);	//|

    memset((src), 0x00, (30 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 32, 30, 4);	//|
}

void int0(SystemInfo * Sys_info, int x, int y)
{
    memset((src), 0x00, (4 * 26));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 4, 26);	//_

    memset((src), 0x00, (4 * 26));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 40, y + 10, 4, 26);	//_

    memset((src), 0x00, (30 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 10, 30, 4);	//|

    memset((src), 0x00, (30 * 4));
    IT8951_Cmd_LoadImageArea(src, (Sys_info->uiImageBufBase), x + 10, y + 32, 30, 4);	//|
}

void show_sense_buffer(struct sg_io_hdr *hdr)
{
    unsigned char *buffer = hdr->sbp;

    for (int i = 0; i < hdr->mx_sb_len; ++i) {
	putchar(buffer[i]);
    }
}

void IT8951_Cmd_Inquiry(void)
{

    struct sg_io_hdr *p_hdr = init_io_hdr();

    set_xfer_data(p_hdr, data_buffer, BLOCK_LEN * 256);
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Inquiry\n");

	status = IT8951_CMD_INQ(fd, page_code, evpd, p_hdr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
#if defined(_TEST_SW_)
	    for (int i = 8; i < 36; i++) {
		printf("%c", data_buffer[i]);
	    }
	    printf("\n");
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_SysInfo(SystemInfo * Sys_info)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    set_xfer_data(p_hdr, Sys_info, (sizeof(SystemInfo) / sizeof(DWord)));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Get device information\n");

	status = IT8951_CMD_SYSTEM_INFO(fd, page_code, evpd, p_hdr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
	    SystemInfo *temp = p_hdr->dxferp;

	    Sys_info->uiStandardCmdNo = SWAP_32(temp->uiStandardCmdNo);
	    Sys_info->uiExtendCmdNo = SWAP_32(temp->uiExtendCmdNo);
	    Sys_info->uiSignature = SWAP_32(temp->uiSignature);
	    Sys_info->uiVersion = SWAP_32(temp->uiVersion);
	    Sys_info->uiWidth = SWAP_32(temp->uiWidth);
	    Sys_info->uiHeight = SWAP_32(temp->uiHeight);
	    Sys_info->uiUpdateBufBase = SWAP_32(temp->uiUpdateBufBase);
	    Sys_info->uiImageBufBase = SWAP_32(temp->uiImageBufBase);
	    Sys_info->uiTemperatureNo = SWAP_32(temp->uiTemperatureNo);
	    Sys_info->uiModeNo = SWAP_32(temp->uiModeNo);

	    for (int i = 0; i < 8; i++) {
		Sys_info->uiFrameCount[i] = SWAP_32(temp->uiFrameCount[i]);
	    }

	    Sys_info->uiNumImgBuf = SWAP_32(temp->uiNumImgBuf);

	    Sys_info->uiWbfSFIAddr = SWAP_32(temp->uiWbfSFIAddr);

	    for (int i = 0; i < 9; i++) {
		Sys_info->uiReserved[i] = SWAP_32(temp->uiReserved[i]);
	    }

	    gulPanelW = Sys_info->uiWidth;
	    gulPanelH = Sys_info->uiHeight;

	    //#if defined(_TEST_SW_)
	    printf("Panel Width: %d\n", Sys_info->uiWidth);
	    printf("Panel Height: %d\n", Sys_info->uiHeight);
	    printf("Image buffer address: %X\n", Sys_info->uiImageBufBase);
	    printf("Update buffer address: %X\n",
		   Sys_info->uiUpdateBufBase);
	    //#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_MemRead(DWord memAddr, Word length, Byte * revBuf)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    //Byte *rev = (Byte*)malloc(sizeof(Byte)*length);

    set_xfer_data(p_hdr, revBuf, length);
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Read memory\n");

	// Notice that the memAddr should be 0x format
	status =
	    IT8951_CMD_READ_MEM(fd, page_code, evpd, p_hdr, memAddr,
				length);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
#if defined(_Test_SW_)
	    printf("Read memory 0x%X: \r\n", memAddr);
	    for (int i = 0; i < length; i++) {
		printf("%X \r", revBuf[i]);
	    }
	    printf("\n");
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_MemWrite(DWord memAddr, Word length, Byte * srcBuf)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    set_xfer_data(p_hdr, srcBuf, length);
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Write memory\n");

	status =
	    IT8951_CMD_WRITE_MEM(fd, page_code, evpd, p_hdr, memAddr,
				 length);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
#if defined(_TEST_SW_)
	    printf("Write memory 0x%X: \r\n", memAddr);

	    for (int i = 0; i < length; i++) {
		printf("%X \r", srcBuf[i]);
	    }
	    printf("\n");
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_RegRead(DWord regAddr, DWord * rev)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    set_xfer_data(p_hdr, rev, sizeof(DWord));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Read register\n");

	status = IT8951_CMD_READ_REG(fd, page_code, evpd, p_hdr, regAddr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
	    *rev = SWAP_32(*rev);

#if defined(_Test_SW_)
	    printf("Read register 0x%X: \r\n", regAddr);
	    printf("%X \r", *rev);
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_RegWrite(DWord regAddr, DWord * src)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    DWord srcIn = SWAP_32(*src);

    set_xfer_data(p_hdr, &srcIn, sizeof(DWord));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Write register\n");

	status = IT8951_CMD_WRITE_REG(fd, page_code, evpd, p_hdr, regAddr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
#if defined(_TEST_SW_)
	    printf("Write register 0x%X: \r\n", regAddr);
#endif
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_DisplayArea(DWord dpyX, DWord dpyY, DWord dpyW, DWord dpyH,
			    DWord dpyMode, DWord memAddr, DWord enWaitRdy)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    DisplayArg displayArg;

    displayArg.iPosX = SWAP_32(dpyX);	//Conver Little to Big for IT8951/61
    displayArg.iPosY = SWAP_32(dpyY);
    displayArg.iWidth = SWAP_32(dpyW);
    displayArg.iHeight = SWAP_32(dpyH);
    displayArg.iEngineIndex = SWAP_32(enWaitRdy);
    displayArg.iMemAddr = SWAP_32(memAddr);
    displayArg.iWavMode = SWAP_32(dpyMode);

    set_xfer_data(p_hdr, &displayArg, sizeof(DisplayArg));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);

    if (fd > 0) {
	printf("\nCommand: Display\n");

	status = IT8951_CMD_DPY_AREA(fd, page_code, evpd, p_hdr);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
	    printf("Refreshing (%d, %d, %d, %d) with mode %d ... \r\n",
		   dpyX, dpyY, dpyW, dpyH, dpyMode);
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}

void IT8951_Cmd_LoadImageArea(Byte * srcImg, DWord memAddr, DWord ldX,
			      DWord ldY, DWord ldW, DWord ldH)
{

    printf("\nCommand: Load image\n");

    if (ldW <= 2048 && ldW != gulPanelW) {
	SG_IO_HDR *p_hdr = init_io_hdr();

	//Using IT8951 New USB Command for Loading Image - it Needs IT8951 F/W support
	DWord counter = (SPT_BUF_SIZE / ldW);
	LoadArg loadArg;

	int status = 0;
	int fd = open(path, O_RDWR);

	for (DWord i = 0; i < ldH; i += counter) {
	    if (counter > (ldH - i)) {
		counter = (ldH - i);
	    }

	    Byte *tempBuf =
		(Byte *) malloc((sizeof(LoadArg) + (ldW * counter)));

	    loadArg.iX = SWAP_32(ldX);
	    loadArg.iY = SWAP_32((ldY + i));
	    loadArg.iW = SWAP_32(ldW);
	    loadArg.iH = SWAP_32(counter);

	    //Set Image Buffer Start Address
	    loadArg.iAddress = SWAP_32(memAddr);

	    memcpy(tempBuf, &loadArg, sizeof(LoadArg));
	    memcpy((tempBuf + sizeof(LoadArg)), (srcImg + (i * ldW)),
		   (ldW * counter));

	    set_xfer_data(p_hdr, tempBuf,
			  (sizeof(LoadArg) + (ldW * counter)));
	    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

	    if (fd > 0) {
		status = IT8951_CMD_LOAD_IMG(fd, page_code, evpd, p_hdr);
		if (status != 0) {
		    show_sense_buffer(p_hdr);
		} else {
		    // Show some information of loaded data?
		}
	    } else {
		printf("failed to open sg file %s\n", path);
	    }
	    free(tempBuf);
	}

	close(fd);
	destroy_io_hdr(p_hdr);
    } else {
	//Full Image - Fast Method => Send Multi Lines for each transfer
	DWord counter = (SPT_BUF_SIZE / ldW);

	for (DWord i = 0; i < ldH; i += counter) {
	    if (counter > (ldH - i)) {
		counter = (ldH - i);
	    }
	    //We Send Multi Lines for each Bulk Transfer
	    IT8951_Cmd_MemWrite((memAddr + ldX + ((ldY + i) * gulPanelW)),
				(Word) (ldW * counter),
				(srcImg + (i * ldW)));
	}
    }
}

void IT8951_Cmd_SetTemp(TempArg SetTemp)
{

    SG_IO_HDR *p_hdr = init_io_hdr();

    Byte flag = SetTemp.ucSetTemp;
    Byte value = SetTemp.ucTempVal;

    set_xfer_data(p_hdr, &SetTemp, sizeof(TempArg) / sizeof(Byte));
    set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

    int status = 0;
    int fd = open(path, O_RDWR);
    char swap_temp = 0;

    if (fd > 0) {
	printf("\nCommand: Set temperature\n");

	status =
	    IT8951_CMD_SET_TEMP(fd, page_code, evpd, p_hdr,
				SetTemp.ucSetTemp, SetTemp.ucTempVal);
	if (status != 0) {
	    show_sense_buffer(p_hdr);
	} else {
	    if ((flag) == 0x00) {
		TempArg *temp = (p_hdr->dxferp);

		// will return a word , swap it because it8951 is big endian.
		swap_temp = temp->ucTempVal;
		temp->ucTempVal = temp->ucSetTemp;
		temp->ucSetTemp = swap_temp;
		printf("Get temperature: %X\n", temp->ucTempVal);
	    } else {
		printf("Set temperature, now forced as %d\n", value);
		printf("Please read temperature again to check it.\n");
	    }
	}
    } else {
	printf("failed to open sg file %s\n", path);
    }

    close(fd);
    destroy_io_hdr(p_hdr);
}
