/*
----------------------------------------------------------
File			: advfuncs.c
Description  	: microQuestMaker64 core routines
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "adv.h"
#include "advfuncs.h"
#include "toolfuncs.h"

char szTemp[STRING_SIZE];


void vInit(char border, char bg, char text)
{
   textcolor(text);
   bgcolor(bg);
   bordercolor(border);
}

#ifndef __RUNTIME__
signed short ssTestLevel(signed short ssRoomNo, ST_FILE *pstRoomFile, ST_FILE *pstObjectFile, ST_FILE *pstConditionFile, ST_FILE *pstConfigurationFile)
{
   signed short ssRet = 0;
   signed short ssAction = 0;
   signed short ssOldRoomNo = 0;
   signed short ssCount = 0;
   signed short ssViewMode = map;
   signed short ssCondCount=0;
   
   char buff[15];
   char szCommand[STRING_SIZE];

   ST_ROOM stRoomRecord;
   ST_OBJECT stObjectArray[MAX_OBJECT_NO];
   ST_OBJECT stPlayer;
   ST_COND stConditionArray[MAX_COND_NO];
   ST_CONFIG stConfiguration;

   memset(&stRoomRecord, 0, sizeof(stRoomRecord));
   memset(&stObjectArray, 0, sizeof(stObjectArray));
   memset(&stConditionArray, 0, sizeof(stConditionArray));
   
   ssReadFile(pstConfigurationFile, &stConfiguration, sizeof(ST_CONFIG), 1);

   bordercolor(stConfiguration.ssBorderColor);
   bgcolor(stConfiguration.ssBackgroundColor);
   textcolor(stConfiguration.ssTextColor);   

   clrscr();
   cprintf("initializing...\n\r");
   
   cprintf("\n\r* loading game data   : ");

   for (ssCount = 1; ssCount <= MAX_OBJECT_NO; ssCount++)
   {
     ssRet = ssReadFile(pstObjectFile, &stObjectArray[ssCount], sizeof(ST_OBJECT), ssCount);
     sprintf(buff, "%3d%% done.", ((100 * ssCount) / MAX_OBJECT_NO));
     cputsxy(25, 2, buff);
   }   
   cputsxy(25, 2, "100% done.");

   cprintf("\n\r* loading game logic  : ");
 
   for (ssCount = 1; ssCount <= MAX_COND_NO; ssCount++)
   {
     ssRet = ssReadFile(pstConditionFile, &stConditionArray[ssCount], sizeof(ST_COND), ssCount);
     sprintf(buff, "%3d%% done.", ((100 * ssCount) / MAX_COND_NO));
     cputsxy(25, 3, buff);
   }   
   cputsxy(25, 3, "100% done."); 
 
   ssRet = ssReadFile(pstRoomFile, &stRoomRecord, sizeof(ST_ROOM), ssRoomNo);
 
   stPlayer.ssInitialRoom = 1;
   stPlayer.ssCurrentRoom = 1;

   do
   {
      for (ssCount = 1; ssCount <= stConfiguration.ssMaxConditions; ssCount++)
      {

         if (stConditionArray[ssCount].ssCondStatus == 1)
            continue;
     	
         ssRet = ssCheckCondition(ssCount, stObjectArray, &stConditionArray[ssCount]);
         
         if (ssRet == 1)
         {
            stConditionArray[ssCount].ssCondStatus=1;
            ssCondCount++;           
         }        
      }
             
      if (ssCondCount == stConfiguration.ssMaxConditions)
      {
         clrscr();
         cprintf("\n\r\n\r       *** CONGRATULATIONS! ***");
         cprintf("\n\r      You have solved this quest");
         cprintf("\n\r\n\r           Hit 'q' to quit!");
         
         while (cgetc() != 'q');   
      	 return 1;
      }
      
      vInit(stRoomRecord.ssBorderColor,stRoomRecord.ssBackgroundColor,stRoomRecord.ssTextColor);
      usDrawLevel(&stRoomRecord, ssViewMode, RUNMODE_GAME);
      ssCheckObjectByRoom(stPlayer.ssCurrentRoom, stObjectArray);
           
      ssReadCommand(szCommand);
      ssAction = ssParseCommand(szCommand, stPlayer.ssCurrentRoom, stObjectArray);

      if (ssAction > 9 && ssAction < 20)
      {
         stPlayer.ssCurrentRoom = ssMovePlayer(stPlayer.ssCurrentRoom, &stRoomRecord, ssAction);
         memset(&stRoomRecord, '\0', sizeof(ST_ROOM));
         ssRet = ssReadFile(pstRoomFile, &stRoomRecord, sizeof(ST_ROOM), stPlayer.ssCurrentRoom);
      }

      if (ssAction == ACT_CMD_NOT_THERE)
      {
         cprintf(NEWLINE);      
         cprintf(MSG_NOT_THERE);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_INVALID)
      {
         cprintf(NEWLINE);
         cprintf(MSG_NOT_UNDERSTAND);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_NOT_CARRY)
      {
         cprintf(NEWLINE);     
         cprintf(MSG_NOT_CARRY);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_NOT_TAKE)
      {
         cprintf(NEWLINE);
         cprintf(MSG_NOT_TAKE);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_NOT_OPEN)
      {
         cprintf(NEWLINE);
         cprintf(MSG_NOT_OPEN);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_NOT_CLOSE)
      {
         cprintf(NEWLINE);
         cprintf(MSG_NOT_CLOSE);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_CLOSED)
      {
         cprintf(NEWLINE);
         cprintf(MSG_ITEM_CLOSED);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CLOSE_FIRST)
      {
         cprintf(NEWLINE);
         cprintf(MSG_ITEM_NEED_CLOSE);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_NOT_LOCK)
      {
         cprintf(NEWLINE);
         cprintf(MSG_NOT_LOCK);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_NOT_UNLOCK)
      {
         cprintf(NEWLINE);
         cprintf(MSG_NOT_UNLOCK);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_IS_LOCKED)
      {
         cprintf(NEWLINE);
         cprintf(MSG_ITEM_IS_LOCKED);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_CMD_IS_UNLOCKED)
      {
         cprintf(NEWLINE);
         cprintf(MSG_ITEM_IS_UNLOCKED);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_ALREADY_OPEN)
      {
         cprintf(NEWLINE);
         cprintf(MSG_ITEM_ALREADY_OPEN);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }

      if (ssAction == ACT_ALREADY_CLOSED)
      {
         cprintf(NEWLINE);
         cprintf(MSG_ITEM_ALREADY_CLOSED);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }
  
      if (ssAction == ACT_ALREADY_LOCKED)
      {
         cprintf(NEWLINE);
         cprintf(MSG_ITEM_ALREADY_LOCKED);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      }      
      
      if (ssAction == ACT_ALREADY_UNLOCKED)
      {
         cprintf(NEWLINE);
         cprintf(MSG_ITEM_ALREADY_UNLOCKED);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);
      } 
      
      if (ssAction == ACT_CMD_HELP)
      {
         vShowHelp();
      }

      if (ssAction == ACT_CMD_NOMAP)
      {
         ssViewMode = text;
      }

      if (ssAction == ACT_CMD_MAP)
      {
         ssViewMode = map;
      }

   } while (ssAction != ACT_CMD_QUIT);
   
   vInit(6,6,1);
   
   return 0;
}
#endif

void vShowHelp(void)
{
    clrscr();
    chline(40);
    cprintf(PROGRAMSTRING);
    chline(40);
    cprintf(NEWLINE);
    cprintf("* online help");
    cprintf(NEWLINE);
    cprintf("\n\rwalk        : n, s, e, w, u, d");
    cprintf("\n\rtoggle map  : map, text");
    cprintf("\n\rtake   item : take <itm>");
    cprintf("\n\rdrop   item : drop <itm> [into <itm>]");
    cprintf("\n\ropen   item : open <itm>");
    cprintf("\n\rclose  item : close <itm>");
    cprintf("\n\rlock   item : lock <itm> with <key>");
    cprintf("\n\runlock item : unlock <itm> with <key>");      
    cprintf("\n\rinventory   : inv");
    cprintf("\n\rthis help   : help");
    cprintf("\n\rend game    : quit ");
    cprintf(NEWLINE);
    cprintf("\n\rReturn: exit help");

    while (cgetc() != 0x0d);
}
