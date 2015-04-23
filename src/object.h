/*
----------------------------------------------------------
File			: object.h
Description		: microQuestMaker64 object management header
Copyright		: (c) 2004 - 2008 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#ifndef OBJECT_H
#define OBJECT_H

#include "file.h"

#define MAX_OBJECT_SHORT_TEXT 20
#define MAX_OBJECT_TEXT 40
#define MAX_OBJECT_NO   30

#define OBJ_ATTR_KEY 		1
#define OBJ_ATTR_LOCKED		2
#define OBJ_ATTR_OPEN		4
#define OBJ_ATTR_MOVE		8
#define OBJ_ATTR_POISON		16
#define OBJ_ATTR_WEAPON		32
#define OBJ_ATTR_SHIELD		64
#define OBJ_ATTR_CONTAINER	128
	
typedef struct
{
  /* object values */
  char  ssObjectNo;
  char  ssCurrentRoom;
  char  scParentObjectNo;
  char  scUnlockObjectNo;
  char  ssWeaponHit;
  char  ssShieldBlock;
  
  /* object attributes */
  unsigned short usFlag;

  /* object description*/    
  char  szObjectShortText[MAX_OBJECT_SHORT_TEXT];  
  char  szObjectText[MAX_OBJECT_TEXT];

  /* Player/NPC Attributes */
  short ssInitialRoom;
  short ssHitpoints;
  short ssScore;
} ST_OBJECT;

int ssInitObjects(ST_FILE *pstFile);
void vListInventory(ST_OBJECT *pstObject);
signed short ssCheckObjectByRoom(signed short ssActRoomNo, ST_OBJECT *pstObject);
signed short ssCheckObjectByName(char *pcObjectName, ST_OBJECT *pstObject);
short ssWriteObject(short ssActObjNo, ST_OBJECT *pstObject, ST_FILE *pstFile);
short ssReadObject(short ssActObjNo, ST_OBJECT *pstObject, ST_FILE *pstFile);
unsigned short usCreateObject(ST_OBJECT *pstObject, ST_FILE *pstFile);
unsigned short usDrawObject(ST_OBJECT *pstObject, enum display_mode level_display, short ssRunMode);
signed short ssGetYesNo(void);

#endif
