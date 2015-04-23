/*
----------------------------------------------------------
File			: file.h
Description	    : microQuestMaker64 file object header file
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/


#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>
#include <cbm.h>

#define MAX_FILENAME 16

typedef struct
{
	char szFileName[MAX_FILENAME];
	unsigned char ucDeviceNo;
} ST_FILE;

int ssInitFile(ST_FILE *pstFile, void *pvBuffer, unsigned int uiBuffSize, unsigned int uiRecCount);
int ssWriteFile(ST_FILE *pstFile, void *pvBuffer, unsigned int uiBuffSize, unsigned int uiRecNo);
int ssReadFile(ST_FILE *pstFile, void *pvBuffer, unsigned int uiBuffSize, unsigned int uiRecNo);
unsigned char ucCheckDeviceNo(unsigned char *ucDeviceNo);

#endif
