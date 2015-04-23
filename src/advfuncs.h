/*
----------------------------------------------------------
File			: advfuncs.h
Description		: microQuestMaker64 core routines header file
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/


#ifndef ADVFUNCS_H
#define ADVFUNCS_H

#include "parser.h"
#include "movement.h"
#include "level.h"
#include "object.h"
#include "condition.h"
#include "config.h"

void vInit(char border, char bg, char text);
signed short ssTestLevel(signed short ssRoomNo, ST_FILE *pstRoomFile, ST_FILE *pstObjectFile, ST_FILE *pstConditionFile, ST_FILE *pstConfigurationFile);
void vShowHelp(void);

#endif
