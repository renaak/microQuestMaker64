/*
----------------------------------------------------------
File			: level.h
Description		: microQuestMaker64 level management header
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#ifndef LEVEL_H
#define LEVEL_H

#include "file.h"

#define MAX_ROOM_TEXT   40
#define MAX_TEXT_LINES   5
#define MAX_ROOM_NO    100

#define  DEFAULT_ROOM_CHAR_UP '<'
#define  DEFAULT_ROOM_CHAR_DOWN '>'
#define  DEFAULT_ROOM_CHAR_FLOOR '.'
#define  DEFAULT_ROOM_CHAR_WALL 0xa6
#define  DEFAULT_ROOM_CHAR_DOOR ' '

#define  MAX_ROOM_WIDTH  8
#define  MAX_ROOM_HEIGHT 8

typedef struct
{
   char  ssRoomNo;
   char  ssNorth;
   char  ssSouth;
   char  ssEast;
   char  ssWest;
   char  ssUp;
   char  ssDown;
   char  scCharUp;
   char  scCharDown;
   char  scCharFloor;
   char  scCharWall;
   char  scCharDoor;
   char  ssBorderColor;
   char  ssBackgroundColor;
   char  ssTextColor;
   char  szRoomText[MAX_TEXT_LINES][MAX_ROOM_TEXT];
} ST_ROOM;

int ssInitLevel(ST_FILE *pstFile);
short ssWriteLevel(int ssActRoomNo, ST_ROOM *pstLevel, ST_FILE *pstFile);
short ssReadLevel(int ssActRoomNo, ST_ROOM *pstLevel, ST_FILE *pstFile);
unsigned short usCreateLevel(ST_ROOM *pstLevel, ST_FILE *pstFile);
unsigned short usDrawLevel(ST_ROOM *pstLevel, enum display_mode level_display, short ssRunMode);

#endif
