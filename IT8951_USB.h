#include "IT8951_CMD.h"

#ifndef Include_Main

#define Include_Main

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#define _Test_SW_

void show_sense_buffer(SG_IO_HDR *);

void IT8951_Cmd_Inquiry(void);
void IT8951_Cmd_SysInfo(SystemInfo *);
void IT8951_Cmd_MemRead(DWord, Word, Byte *);
void IT8951_Cmd_MemWrite(DWord, Word, Byte *);
void IT8951_Cmd_RegRead(DWord, DWord *);
void IT8951_Cmd_RegWrite(DWord, DWord *);
void IT8951_Cmd_DisplayArea(DWord, DWord, DWord, DWord, DWord, DWord,
			    DWord);
void IT8951_Cmd_LoadImageArea(Byte *, DWord, DWord, DWord, DWord, DWord);
void IT8951_Cmd_SetTemp(TempArg);
void int1(SystemInfo *, Byte *, int, int);
void int2(SystemInfo *, Byte *, int, int);
void int3(SystemInfo *, Byte *, int, int);
void int4(SystemInfo *, Byte *, int, int);
void int5(SystemInfo *, Byte *, int, int);
void int6(SystemInfo *, Byte *, int, int);
void int7(SystemInfo *, Byte *, int, int);
void int8(SystemInfo *, Byte *, int, int);
void int9(SystemInfo *, Byte *, int, int);
void int0(SystemInfo *, Byte *, int, int);
