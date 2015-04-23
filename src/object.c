/*
----------------------------------------------------------
File			: object.c
Description		: microQuestMaker64 object management module
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "adv.h"
#include "object.h"
#include "toolfuncs.h"

#ifndef __RUNTIME__
unsigned short usCreateObject(ST_OBJECT *pstObject, ST_FILE *pstFile)
{
   short ssObjectNo = 0;
   char  szTemp[MAX_OBJECT_TEXT];
   char ucChoice;
   
   clrscr();
   
   fflush(stdin);
   
   do {
        cprintf("\n\redit object no.    : "); 
        ssObjectNo = atoi(gets(szTemp));
        fflush(stdin);
   } while ((ssObjectNo < 0) || (ssObjectNo > MAX_OBJECT_NO));   
   
   pstObject->ssObjectNo=ssObjectNo;

   /* enter object attributes */
   cprintf(NEWLINE);
   chline(40);
   
   cprintf("initial room no.   [%02d] :", pstObject->ssCurrentRoom);
   pstObject->ssCurrentRoom = atoi(gets(szTemp));
   
   cprintf("\n\rcontainer           [%c] :", (pstObject->usFlag & OBJ_ATTR_CONTAINER) ? 'Y' : 'N');
   if (ssGetYesNo())
      pstObject->usFlag |= OBJ_ATTR_CONTAINER;
 
   if ( ! (pstObject->usFlag & OBJ_ATTR_CONTAINER) )
   {
         cprintf("\n\rparent obj. no.    [%02d] :", pstObject->scParentObjectNo);
         pstObject->scParentObjectNo = (char) atoi(gets(szTemp));
      
      /* if an object has a parent object, it is "hidden inside" that parent
      object and not visible in the room, e.g. piece of paper in a box 
      in a room. Thus the room number for this "hidden" object is set to 0 */
      if (pstObject->scParentObjectNo != 0)
      {
         pstObject->ssCurrentRoom = 0;
      }
      else
      {
      	 pstObject->scParentObjectNo = 0; 
      } 
   }
     
   cprintf("\n\rmovable             [%c] :", (pstObject->usFlag & OBJ_ATTR_MOVE) ? 'Y' : 'N');
   if (ssGetYesNo())
      pstObject->usFlag |= OBJ_ATTR_MOVE;

   cprintf("\n\ropen                [%c] :", (pstObject->usFlag & OBJ_ATTR_OPEN) ? 'Y' : 'N');
   if (ssGetYesNo())
      pstObject->usFlag |= OBJ_ATTR_OPEN;      

   cprintf("\n\rlocked              [%c] :", (pstObject->usFlag & OBJ_ATTR_LOCKED) ? 'Y' : 'N');
   if (ssGetYesNo())
      pstObject->usFlag |= OBJ_ATTR_LOCKED;  
   
   cprintf("\n\rkey                 [%c] :", (pstObject->usFlag & OBJ_ATTR_KEY) ? 'Y' : 'N');
   if (ssGetYesNo())
      pstObject->usFlag |= OBJ_ATTR_KEY;
   
   if (pstObject->usFlag & OBJ_ATTR_KEY)
   {
      cprintf("\n\rkey obj. no.    [%02d] :", pstObject->scUnlockObjectNo);
      pstObject->scUnlockObjectNo = (char) atoi(gets(szTemp));
   }

   cprintf("\n\rpoison              [%c] :", (pstObject->usFlag & OBJ_ATTR_POISON) ? 'Y' : 'N');
   if (ssGetYesNo())
      pstObject->usFlag |= OBJ_ATTR_POISON;   

   cprintf("\n\rweapon              [%c] :", (pstObject->usFlag & OBJ_ATTR_WEAPON) ? 'Y' : 'N');
   if (ssGetYesNo())
      pstObject->usFlag |= OBJ_ATTR_WEAPON;

   if (pstObject->usFlag & OBJ_ATTR_WEAPON)
   {
      cprintf("\n\rweapon HP       [%02d] :", pstObject->ssWeaponHit);
      pstObject->ssWeaponHit = atoi(gets(szTemp));
   }

   cprintf("\n\rshield              [%c] :", (pstObject->usFlag & OBJ_ATTR_SHIELD) ? 'Y' : 'N');
   if (ssGetYesNo())
      pstObject->usFlag |= OBJ_ATTR_SHIELD;

   if (pstObject->usFlag & OBJ_ATTR_SHIELD)
   {
      cprintf("\n\rshield SP       [%02d] :", pstObject->ssShieldBlock);
      pstObject->ssShieldBlock = (char) atoi(gets(szTemp));
   }

   /* enter object short description*/
   cprintf(NEWLINE);
   cprintf("\n\rname (max. %d chars):\n\r", MAX_OBJECT_SHORT_TEXT);
   chline(40);
   cgets(szTemp, MAX_OBJECT_SHORT_TEXT);
   cprintf(NEWLINE);

   if ((strlen(szTemp) > 0))
      {
         strcpy(pstObject->szObjectShortText, szTemp);
      }
   
   /* enter object description*/
   cprintf(NEWLINE);
   cprintf("\n\rdescription (max. %d chars):\n\r", MAX_OBJECT_TEXT);
   chline(40);
   cgets(szTemp, MAX_OBJECT_TEXT);
 
   if ((strlen(szTemp) > 0))
      {
         strcpy(pstObject->szObjectText, szTemp);
      }

   ssWriteFile(pstFile, pstObject, sizeof(ST_OBJECT), pstObject->ssObjectNo);  

   cputsxy(0, 24, "Enter: Back to Menu");

   do
   {
      ucChoice=cgetc();     
   } while (ucChoice!=0x0d);

   return pstObject->ssObjectNo;
}

unsigned short usDrawObject(ST_OBJECT *pstObject, enum display_mode level_display, short ssRunMode)
{
      char ucChoice;
      char *pcJoyMem=(char*) 0xdc00;
      
      do
      {
         clrscr();
         
         if (level_display == map || level_display == text)
         {
            cprintf("object No.: %d\n\r", pstObject->ssObjectNo);
            cprintf(NEWLINE);

            cprintf("\n\robject No.       : %d", pstObject->ssObjectNo);
            cprintf(NEWLINE);
            cprintf("\n\rinitial room no. : %d", pstObject->ssCurrentRoom);
            cprintf("\n\rcontainer        : %c", (pstObject->usFlag & OBJ_ATTR_CONTAINER) ? 'Y' : 'N');            
            cprintf("\n\rcont. parent obj.: %d", pstObject->scParentObjectNo);
            cprintf("\n\rmovable          : %c", (pstObject->usFlag & OBJ_ATTR_MOVE) ? 'Y' : 'N'); 
            cprintf("\n\ropen             : %c", (pstObject->usFlag & OBJ_ATTR_OPEN) ? 'Y' : 'N');
            cprintf("\n\rlocked           : %c", (pstObject->usFlag & OBJ_ATTR_LOCKED) ? 'Y' : 'N');                                   
            cprintf("\n\rkey              : %c", (pstObject->usFlag & OBJ_ATTR_KEY) ? 'Y' : 'N');
            cprintf("\n\rkey obj. no.     : %d", pstObject->scUnlockObjectNo);
            cprintf("\n\rpoison           : %c", (pstObject->usFlag & OBJ_ATTR_POISON) ? 'Y' : 'N');            
            cprintf("\n\rweapon           : %c", (pstObject->usFlag & OBJ_ATTR_WEAPON) ? 'Y' : 'N');
            cprintf("\n\rweapon HP        : %d", pstObject->ssWeaponHit);
            cprintf("\n\rshield           : %c", (pstObject->usFlag & OBJ_ATTR_SHIELD) ? 'Y' : 'N');
            cprintf("\n\rshield SP        : %d", pstObject->ssShieldBlock);
            cprintf("\n\r\n\rShort Text       : \"%s\"", pstObject->szObjectShortText);

            cprintf(NEWLINE);
            chline(40);
            if (ssRunMode == RUNMODE_EDIT)
            {
               cprintf("\n\rDesc. [%d]       : \"%s", strlen(pstObject->szObjectText), pstObject->szObjectText);
               cprintf("\"");               
            }
            else
            {
               cprintf("\n\r%s", strlen(pstObject->szObjectText), pstObject->szObjectText);
            }
         }

         /* toggle grapics mode */
         cputsxy(ScreenPosX, ScreenPosY+13, "Return: Back to Menu");
         
         if (ssRunMode == RUNMODE_EDIT)
            {
               ucChoice=cgetc();
            }

      } while (ucChoice!=0x0d && ssRunMode == RUNMODE_EDIT );
}
#endif

void vListInventory(ST_OBJECT *pstObjectArray)
{
    signed short ssCount = 0;
    signed short ssHitFlag = 0;

    clrscr();
    cprintf("You are carrying:\n\r\n\r");

    for (ssCount = 0; ssCount < MAX_OBJECT_NO; ssCount++)
    {
       if ((pstObjectArray[ssCount].ssCurrentRoom == -1))
       {
          cprintf("[%s]\n\r%s\n\r\n\r", pstObjectArray[ssCount].szObjectShortText, pstObjectArray[ssCount].szObjectText);
          ssHitFlag = 1;
       }
    }

    if (!ssHitFlag)
    {
      cprintf("nothing.");
    }

    cprintf("\n\r\n\rReturn: back");
    while (cgetc() != 0x0d);
    fflush(stdin);
}

signed short ssCheckObjectByRoom(signed short ssActRoomNo, ST_OBJECT *pstObjectArray)
{
    signed short ssCount = 0;
    signed short ssHitFlag = 0;

    cprintf("\n\rYou can see: ");

    for (ssCount = 1; ssCount < MAX_OBJECT_NO; ssCount++)
    { 
       if ((pstObjectArray[ssCount].ssCurrentRoom == ssActRoomNo))
       {
          cprintf("\n\r%s", pstObjectArray[ssCount].szObjectShortText);
          
          /*if (pstObjectArray[ssCount].scIsOpen != 0)*/
          if (pstObjectArray[ssCount].usFlag & OBJ_ATTR_OPEN)
          {	
             cprintf(" (open)");
          }
          
          ssHitFlag = 1;  
       }
    }

    if (!ssHitFlag)
    {
      cprintf("\n\rnothing of interest.\n\r");
      return 0;
    }
    else
    {
      cprintf("\n\r");
    }

    return ssHitFlag;
}

signed short ssCheckObjectByName(char *pcObjectName, ST_OBJECT *pstObject)
{
    signed short ssCount = 0;
    signed short ssHitFlag = 0;

    for (ssCount = 0; ssCount < MAX_OBJECT_NO; ssCount++)
    {
       if (!strcmp(pcObjectName, pstObject[ssCount].szObjectShortText))
       {
          return ssCount;
       }
    }

    return 0;
}

signed short ssGetYesNo(void)
{
      unsigned char ucChoice;

      fflush(stdin); 	     
      ucChoice = cgetc(); 
      cprintf("%c", ucChoice);
      return (ucChoice == 'y' || ucChoice == 'Y') ? 1 : 0;
}