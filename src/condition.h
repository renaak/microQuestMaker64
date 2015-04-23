/*
----------------------------------------------------------
File			: condition.h
Description		: microQuestMaker64 game logic headers
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#ifndef COND_H
#define COND_H

#include "file.h"
#include "level.h"
#include "object.h"

#define MAX_COND_NO     10
#define MAX_COND_TYPE    2
#define MAX_COND_TEXT   10

#define COND_TYPE_OBJONLY    1 
#define COND_TYPE_OBJOBJ     2 

#define COND_OPR_EQ    1
#define COND_OPR_AND   2
#define COND_OPR_OR    4
#define COND_OPR_NOT   8
#define COND_OPR_GT    16
#define COND_OPR_LT    32

typedef struct
{
   short  ssCondNo;   
   short  ssCondType;
   short  ssCondStatus;
   short  ssSObj;
   short  ssSAttr;
   short  ssSVal;
   short  ssOper;
   short  ssDObj;
   short  ssDAttr;
   short  ssDVal;
} ST_COND;

short ssCheckCondition(short ssId, ST_OBJECT *pstObjectArr, ST_COND *pstCondition);
short ssCreateCondition(ST_COND *pstCondition, ST_FILE *pstFile);
short ssDrawCondition(ST_COND *pstCondition);
short ssCreateConditionString(ST_COND *pstCondition);

#endif