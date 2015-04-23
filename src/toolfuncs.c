/*
----------------------------------------------------------
File			: toolfuncs.c
Description		: microQuestMaker64 help routines
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "adv.h"
#include "toolfuncs.h"

char *cgets(char *pcBuffer, unsigned int uiLen)
{
   char iCount = 0;
   char ucTemp;

   short ssCurX;
   short ssCurY;
   short ssCurXOrig;
   short ssCurYOrig;
   unsigned char SavedCursor = cursor(1);
  
   /* save initial cursor position */
   ssCurXOrig = ssCurX = wherex();
   ssCurYOrig = ssCurY = wherey();

   gotoxy(39, ssCurY);
   cputc('<');
   gotoxy(ssCurX, ssCurY);

   while (iCount < uiLen)
   {
       ucTemp = cgetc();
       
       gotoxy(39, ssCurY);
       cputc('<');
       gotoxy(ssCurX, ssCurY);

       ssCurY = wherey();

       if (ucTemp == '\n')
       {
         break;
       }
       else
       {         
         if (ucTemp == 0x14)
         {
         
           if (iCount == 0)
              continue;
         
           if (ssCurX < 0)
           {
              ssCurX = 0;
           }
           
           if (iCount >= STRING_SIZE-1)
           {
              ssCurX--;
              iCount--;
              
              gotox(ssCurX);
              cputc(' ');           
              gotox(ssCurX); 

              continue;
           }

           if (iCount < 1)
           {
              iCount = 0;
              pcBuffer[iCount] = '\0';
           }  

           ssCurX--;
           iCount--;

           gotox(ssCurX);
           cputc(' ');           
           gotox(ssCurX); 

           gotoxy(39, ssCurY);
           cputc('<');
           gotoxy(ssCurX, ssCurY);   
   
           continue;
         } // if 0x14 (backspace)

         if (iCount >= STRING_SIZE-1)
         {
            pcBuffer[iCount] = ucTemp;

            ssCurX = 0;
            iCount = 0;

            pcBuffer[STRING_SIZE] = '\0';
            gotoxy(ssCurX, ssCurY);
            cclear(40);

            gotoxy(39, ssCurY);
            cputc('<');
            gotoxy(ssCurX, ssCurY);

            continue;
         } // if len >= 39 chars

       } // else

       pcBuffer[iCount] = ucTemp;
       cputc(pcBuffer[iCount]);
       ssCurX++;
       iCount++;
   } // while

   pcBuffer[iCount] = '\0';
   cursor (SavedCursor);
   gotoxy(0, wherey());
   
   return pcBuffer;
}

void vSleep(short ssSleep)
{
   do { ssSleep--; } while (ssSleep > 0);
}