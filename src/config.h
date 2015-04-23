/*
----------------------------------------------------------
File			: config.h
Description		: microQuestMaker64 base config header
Copyright		: (c) 2004 - 2008 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "file.h"
	
typedef struct
{
  short ssBorderColor;
  short ssBackgroundColor;
  short ssTextColor;  
  short ssMaxConditions;
  short ssMaxObjects;
  short ssMaxRooms;
  ST_FILE stRoomFile;
  ST_FILE stObjectFile;
  ST_FILE stConditionFile;
  ST_FILE stConfigurationFile;
} ST_CONFIG;

#endif