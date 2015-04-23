/*
----------------------------------------------------------
File			: file.c
Description		: microQuestMaker64 file object source file
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "file.h"

int ssInitFile(ST_FILE *pstFile, void *pvBuffer, unsigned int uiBuffSize, unsigned int uiRecCount)
{
  char command[40];
  char cbm_filename[40];  
  int siRet=0;
  int siCount=0;
  
  int channel, hi, lo;
  
  channel=3+96;

  sprintf(cbm_filename,"0:%s,l,%c", pstFile->szFileName, uiBuffSize);
  
  siRet = cbm_open( 15, pstFile->ucDeviceNo, 15, NULL);
  siRet = cbm_open( 2, pstFile->ucDeviceNo,  3, cbm_filename);

  for (siCount = uiRecCount; siCount >= 1; siCount--)
  {
     hi=(siCount/256);
     lo=siCount-(hi*256);
    
     sprintf(command, "p%c%c%c", channel, lo, hi);    
     siRet=cbm_write( 15, command, strlen(command));
     siRet = cbm_write( 2, pvBuffer, uiBuffSize); 
  }

  cbm_close(15);  
  cbm_close(2);	
}

int ssWriteFile(ST_FILE *pstFile, void *pvBuffer, unsigned int uiBuffSize, unsigned int uiRecNo)
{
  char command[40];
  char cbm_filename[40];
  int siRet=0;
  
  int channel, hi, lo;
  
  channel=3+96;
  
  sprintf(cbm_filename,"0:%s,l,%c", pstFile->szFileName, uiBuffSize);
  
  siRet = cbm_open( 15, pstFile->ucDeviceNo, 15, NULL);
  siRet = cbm_open( 2, pstFile->ucDeviceNo,  3, cbm_filename);    

  hi=(uiRecNo/256);
  lo=uiRecNo-(hi*256);
  
  sprintf(command, "p%c%c%c", channel, lo, hi);    
  siRet=cbm_write( 15, command, strlen(command));

  siRet = cbm_write( 2, pvBuffer, uiBuffSize);

  cbm_close(15);  
  cbm_close(2);
    
  return siRet;
}

int ssReadFile(ST_FILE *pstFile, void *pvBuffer, unsigned int uiBuffSize, unsigned int uiRecNo)
{
  char command[40];
  char cbm_filename[40];
  int siRet=0;
  
  int channel, hi, lo;
  
  channel=3+96;

  sprintf(cbm_filename,"0:%s,l,%c", pstFile->szFileName, uiBuffSize);

  siRet = cbm_open( 15, pstFile->ucDeviceNo, 15, NULL);
  siRet = cbm_open( 2, pstFile->ucDeviceNo,  3, cbm_filename);    

  hi=(uiRecNo/256);
  lo=uiRecNo-(hi*256);
    
  sprintf(command, "p%c%c%c", channel, lo, hi);    
  siRet=cbm_write( 15, command, strlen(command));
  
  siRet = cbm_read( 2, pvBuffer, uiBuffSize);
  
  cbm_close(15);  
  cbm_close(2); 
       
  return siRet;
}

unsigned char ucCheckDeviceNo(unsigned char *ucDeviceNo)
{
   if (*ucDeviceNo < 8 || *ucDeviceNo > 11)
      return 8;
   else 
   	  return *ucDeviceNo;
}
