/*
----------------------------------------------------------
File			: level.c
Description		: microQuestMaker64 level management module
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "adv.h"
#include "level.h"
#include "toolfuncs.h"

#ifndef __RUNTIME__
unsigned short usCreateLevel(ST_ROOM *pstLevel, ST_FILE *pstFile)
{
   int  ssRoomNo = 0;
   char szTemp[MAX_ROOM_TEXT];
   unsigned char  ucChoice;
   char ssCount=0;
      
   clrscr();

   fflush(stdin);

   do
   {
      cprintf("edit room no.: ");
      ssRoomNo = atoi(gets(szTemp));
   } while ((ssRoomNo < 0) || (ssRoomNo > MAX_ROOM_NO));

   pstLevel->ssRoomNo = ssRoomNo;
   
   ssReadFile(pstFile, pstLevel, sizeof(ST_ROOM), ssRoomNo);
   pstLevel->ssRoomNo = ssRoomNo;

   /* enter connections */
   cprintf(NEWLINE);
   chline(40);
   cprintf("North      [%u]: ", pstLevel->ssNorth );
   pstLevel->ssNorth = atoi(gets(szTemp));
   cprintf("\n\rSouth      [%u]: ", pstLevel->ssSouth );
   pstLevel->ssSouth = atoi(gets(szTemp));
   cprintf("\n\rEast       [%u]: ", pstLevel->ssEast  );
   pstLevel->ssEast = atoi(gets(szTemp));
   cprintf("\n\rWest       [%u]: ", pstLevel->ssWest  );
   pstLevel->ssWest = atoi(gets(szTemp));
   cprintf("\n\rUp         [%u]: ", pstLevel->ssUp    );
   pstLevel->ssUp = atoi(gets(szTemp));   
   cprintf("\n\rDown       [%u]: ", pstLevel->ssDown  );
   pstLevel->ssDown = atoi(gets(szTemp));

   /* enter codes for groom graph */
   cursor(1);

   cprintf(NEWLINE);
   
   pstLevel->scCharUp = DEFAULT_ROOM_CHAR_UP;
   cprintf("\n\rstairs up  [%c]: ", pstLevel->scCharUp );
   ((ucChoice = cgetc()) != 0x0d) ? pstLevel->scCharUp = ucChoice : pstLevel->scCharUp = DEFAULT_ROOM_CHAR_UP;

   pstLevel->scCharDown = DEFAULT_ROOM_CHAR_DOWN;
   cprintf("\n\rstairs dwn [%c]: ", pstLevel->scCharDown );
   ((ucChoice = cgetc()) != 0x0d) ? pstLevel->scCharDown = ucChoice : pstLevel->scCharDown = DEFAULT_ROOM_CHAR_DOWN;

   pstLevel->scCharFloor = DEFAULT_ROOM_CHAR_FLOOR;
   cprintf("\n\rfloor      [%c]: ", pstLevel->scCharFloor );
   ((ucChoice = cgetc()) != 0x0d) ? pstLevel->scCharFloor = ucChoice : pstLevel->scCharFloor = DEFAULT_ROOM_CHAR_FLOOR;

   pstLevel->scCharWall = DEFAULT_ROOM_CHAR_WALL;
   cprintf("\n\rwall       [%c]: ", pstLevel->scCharWall  );
   ((ucChoice = cgetc()) != 0x0d) ? pstLevel->scCharWall = ucChoice : pstLevel->scCharWall = DEFAULT_ROOM_CHAR_WALL;

   pstLevel->scCharDoor = DEFAULT_ROOM_CHAR_DOOR;
   cprintf("\n\rdoor       [%c]: ", pstLevel->scCharDoor  );  
   ((ucChoice = cgetc()) != 0x0d) ? pstLevel->scCharDoor = ucChoice : pstLevel->scCharDoor = DEFAULT_ROOM_CHAR_DOOR;

   cursor(0);

   /* enter room description*/
   /*cprintf(NEWLINE);*/
   clrscr();
   cprintf("\n\r* Enter text \n\r  (%d lines, max. %d chars each line):\n\r", MAX_TEXT_LINES, MAX_ROOM_TEXT);
   
   chline(40);
   
   for (ssCount = 0; ssCount < MAX_TEXT_LINES; ssCount++)
   {
     memset(szTemp, 0, sizeof(szTemp));
     cgets(szTemp, MAX_ROOM_TEXT);

     if ((strlen(szTemp) > 0))
     {
        if(strlen(szTemp) >= MAX_ROOM_TEXT)
        {
           szTemp[MAX_ROOM_TEXT]='\0';
        }
        strcpy((pstLevel->szRoomText[ssCount]), szTemp);
     }

     cprintf("\n\r");
   }
   
   clrscr();
   cprintf("* Set your room colors:\n\r\n\r");

   cprintf("Border color      [%d]: ", pstLevel->ssBorderColor);
   pstLevel->ssBorderColor = atoi(gets(szTemp));
   bordercolor(pstLevel->ssBorderColor);
 
   cprintf(NEWLINE);  
   cprintf("Background color  [%d]: ", pstLevel->ssBackgroundColor);
   pstLevel->ssBackgroundColor = atoi(gets(szTemp));
   bgcolor(pstLevel->ssBackgroundColor);
 
   cprintf(NEWLINE);  
   cprintf("Text color        [%d]: ", pstLevel->ssTextColor);
   pstLevel->ssTextColor = atoi(gets(szTemp));
   textcolor(pstLevel->ssTextColor);
 
   ssWriteFile(pstFile, pstLevel, sizeof(ST_ROOM), pstLevel->ssRoomNo);
   
   cputsxy(0, 24, "Return: Back to Menu");

   do
   {
      ucChoice=cgetc();     
   } while (ucChoice!=0x0d);
   
   return pstLevel->ssRoomNo;
}
#endif

unsigned short usDrawLevel(ST_ROOM *pstLevel, enum display_mode level_display, short ssRunMode)
{

      unsigned int  uiCountX;
      unsigned int  uiCountY;
      char          scChar;
      char          ssCount=0;
      unsigned char  ucChoice;

      bordercolor(pstLevel->ssBorderColor);
      bgcolor(pstLevel->ssBackgroundColor);
      textcolor(pstLevel->ssTextColor);

      do
      {
         clrscr();

         if (level_display == map || level_display == text)
         {
            cprintf("Room No.: %d\n\r", pstLevel->ssRoomNo);
            cprintf(NEWLINE);

            if (ssRunMode == RUNMODE_EDIT)
            {
               cprintf("North: %d  South: %d  East: %d  West: %d", pstLevel->ssNorth, pstLevel->ssSouth
                                                                 , pstLevel->ssEast, pstLevel->ssWest);
               cprintf("\n\rUp   : %d  Down : %d\n\r", pstLevel->ssUp, pstLevel->ssDown);
            }

            chline(40);

            for (ssCount = 0; ssCount < MAX_TEXT_LINES; ssCount++)
            {
                cprintf("%s", (pstLevel->szRoomText[ssCount]));
                cprintf(NEWLINE);   
            }
         }

         cprintf(NEWLINE);

         if (level_display == map)
         {
  	       for(uiCountY = 0 ; uiCountY < MAX_ROOM_HEIGHT ; uiCountY++)
  	       {
               for(uiCountX = 0 ; uiCountX < MAX_ROOM_WIDTH ; uiCountX++)
        	     {
        	     /* draw northern doorway */
        	     if ((uiCountX > 2 && uiCountX < 5) && (pstLevel->ssNorth > 0 && uiCountY == 0))
        	        {
                     	   scChar = pstLevel->scCharDoor;
        	        }
        	     else
        	     /* draw southern doorway */
        	     if ((uiCountX > 2 && uiCountX < 5) && (pstLevel->ssSouth > 0 && uiCountY == MAX_ROOM_HEIGHT - 1))
        	        {
                   	   scChar = pstLevel->scCharDoor;
        	        }
        	     else
        	     /* draw eastern doorway */
        	     if ((uiCountY > 2 && uiCountY < 5) && (pstLevel->ssEast > 0 && uiCountX == MAX_ROOM_WIDTH - 1))
        	        {
                 	   scChar = pstLevel->scCharDoor;
        	        }
        	     else
        	     /* draw western doorway */
        	     if ((uiCountY > 2 && uiCountY < 5) && (pstLevel->ssWest > 0 && uiCountX == 0))
        	        {
                  	   scChar = pstLevel->scCharDoor;
        	        }
        	     else
        	     /* draw walls / cornerstones */
        	     if ((uiCountY == 0 || uiCountY == MAX_ROOM_HEIGHT - 1 ) || (uiCountX == 0 || uiCountX == MAX_ROOM_WIDTH - 1))
        	        {
  			           scChar = pstLevel->scCharWall;
        	        }
        	     else
        	     /* draw stairways */
        	     if (uiCountY == 3 && uiCountX == 3)
        	        {
                	   if (pstLevel->ssUp > 0)
                	      {
                	         scChar = pstLevel->scCharUp;
                	      }
                	   else if (pstLevel->ssDown > 0)
                	      {
                           scChar = pstLevel->scCharDown;
                	      }
                     else
                        {
  			                   scChar = pstLevel->scCharFloor;
  			                }
        	        }
        	     /* default */
        	     else
        	        {
                	   scChar = pstLevel->scCharFloor;
        	        }
        	     putchar(scChar);
        	     }
  	        putchar('\n');
  	        }
         }

         /* toggle grapics mode */

         if (ssRunMode == RUNMODE_EDIT)
            {
               cputsxy(ScreenPosX, ScreenPosY+10, "Up     : Toggle Map");
               cputsxy(ScreenPosX, ScreenPosY+11, "Return : Back to Menu");

               ucChoice=cgetc();

               if (ucChoice==0x91)
                  if (level_display == text)
                     level_display = map;
                  else
                  if (level_display == map)
                     level_display = text;
            }       
      } while (ucChoice !=0x0d && ssRunMode==RUNMODE_EDIT );
}
