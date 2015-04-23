/*
----------------------------------------------------------
File                    : main.c
Description             : microQuestMaker64 main routine
Copyright               : (c) 2004 - 2009 by Niels Haedecke
License	                : licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "adv.h"
#include "advfuncs.h"
#include "toolfuncs.h"
#include "menu.h"

#define MAX_MENU_COUNT 5
#define MAX_SUBMENU_COUNT 3
#define MAX_MENU 6
#define MAX_SUBMENU 4
#define MENU_YPOS 10
#define MENU_XPOS 12

static char *label[6]   = { "* MAIN MENU        ", "* FILE SETUP      ", "* PREFERENCES     ", "* ROOM EDITOR     ", "* OBJECT EDITOR   ", "* CONDITION EDITOR"};

static char *menu[6][4] = { {"Test Game      ", "Init Datafiles ", "               ", "Quit           "}, \
                            {"Room File      ", "Object File    ", "Condition File ", "               "}, \
                            {"Init Config.   ", "Edit max. Cond.", "Edit Colors    ", "               "}, \
                            {"Init Rooms     ", "Edit Room      ", "View Room      ", "               "}, \
                            {"Init Objects   ", "Edit Objects   ", "View Objects   ", "               "}, \
                            {"Init Conditions", "Edit Condition ", "View Condition ", "Help           "} };
 
                    
void main(void)
{
   short ssMenu=0;
   short ucCount1=0;
   short ucCount2=0;
   short ssHelp=0;
   short ssRet=0;
   short ssRoomNo = 1;
   short ssOldRoomNo = 0;
   short ssObjectNo = 0;
   unsigned char szTemp[STRING_SIZE];
   unsigned char ucChoice;
   
   ST_FILE stConfigurationFile;
   ST_ROOM stRoomRecord;
   ST_OBJECT stObjectRecord;
   ST_COND stConditionRecord;
   ST_CONFIG stConfigurationRecord;

   memset(&stRoomRecord, 0, sizeof(stRoomRecord));
   memset(&stObjectRecord, 0, sizeof(stObjectRecord));
   memset(&stConditionRecord, 0, sizeof(stConditionRecord));
   memset(&stConfigurationFile, 0, sizeof(stConfigurationFile)); 
   
   strcpy(stConfigurationRecord.stRoomFile.szFileName, "rooms");
   strcpy(stConfigurationRecord.stObjectFile.szFileName, "objects");
   strcpy(stConfigurationRecord.stConditionFile.szFileName, "conditions");
   strcpy(stConfigurationFile.szFileName, "config");
   
   stConfigurationRecord.stRoomFile.ucDeviceNo = 8;
   stConfigurationRecord.stObjectFile.ucDeviceNo = 8;
   stConfigurationRecord.stConditionFile.ucDeviceNo = 8;
   stConfigurationRecord.stConfigurationFile.ucDeviceNo = 8;
   stConfigurationRecord.ssMaxConditions = MAX_COND_NO;
   stConfigurationRecord.ssBorderColor = 6;
   stConfigurationRecord.ssBackgroundColor = 6;
   stConfigurationRecord.ssTextColor = 1;
  
   stConfigurationFile.ucDeviceNo = 8; 
   
   vInit(6,6,1);
   

   clrscr();
   chline(40);
   cprintf(PROGRAMSTRING);
   chline(40);
   cprintf(NEWLINE);

   for(ucCount1=0; ucCount1 < MAX_SUBMENU; ucCount1++)
      cputsxy(MENU_XPOS, MENU_YPOS+ucCount1, menu[ucCount2][ucCount1]);
   
   ucCount1=0;
   gotoxy(MENU_XPOS,MENU_YPOS-2);
   cprintf("%s", label[ucCount2]);
   
   revers(1);
   cputsxy(MENU_XPOS, MENU_YPOS+ucCount1, menu[ucCount2][ucCount1]);
   revers(0);
  
   do {
      gotoxy(0,0);
      chline(40);
      cprintf(PROGRAMSTRING);
      chline(40);
      cprintf(NEWLINE);
  
      if (ucChoice=cgetc())
      {
         gotoxy(MENU_XPOS, MENU_YPOS+ucCount1);
         cprintf("%s", menu[ucCount2][ucCount1]);
         
         if (ucChoice==0x91)
            ucCount1--;

         if (ucChoice==0x11)
            ucCount1++;
         
         if (ucCount1<0)
            ucCount1=MAX_SUBMENU_COUNT;
         
         if (ucCount1>MAX_SUBMENU_COUNT)
            ucCount1=0;

         if (ucChoice==0x9d)
         {
            ucCount2--;
            
            if (ucCount2<0)
               ucCount2=MAX_MENU_COUNT;
            
            for(ucCount1=0; ucCount1 < MAX_SUBMENU; ucCount1++)
               cputsxy(MENU_XPOS, MENU_YPOS+ucCount1, menu[ucCount2][ucCount1]);
            ucCount1=0;
         }

         if (ucChoice==0x1d)
         {
            ucCount2++;
            
            if (ucCount2>MAX_MENU_COUNT)
               ucCount2=0;
            
            for(ucCount1=0; ucCount1 < MAX_SUBMENU; ucCount1++)
               cputsxy(MENU_XPOS, MENU_YPOS+ucCount1, menu[ucCount2][ucCount1]);           
            ucCount1=0;
         }
         
         
         if (ucChoice==0x0d)
         {
         
            clrscr();
         
            switch (ssMenu)
            {
               case 00:
                       ssRoomNo=1;
                       ssTestLevel(ssRoomNo, &stConfigurationRecord.stRoomFile, &stConfigurationRecord.stObjectFile, &stConfigurationRecord.stConditionFile, &stConfigurationFile);
                       break;
            
               case 01:
                       vEraseWarning();      
                       ucChoice = cgetc();
            
                       if (ucChoice == 'y')
                       {                         
                          memset(&stRoomRecord, 0, sizeof(stRoomRecord));        
                          cprintf("\n\r\n\r* initializing...");          
                          ssInitFile(&stConfigurationRecord.stRoomFile, &stRoomRecord, sizeof(stRoomRecord), MAX_ROOM_NO);
            
                          memset(&stObjectRecord, 0, sizeof(stObjectRecord));
                          ssInitFile(&stConfigurationRecord.stObjectFile, &stRoomRecord, sizeof(stObjectRecord), MAX_OBJECT_NO);
            
                          memset(&stConditionRecord, 0, sizeof(stConditionRecord));            
                          ssInitFile(&stConfigurationRecord.stConditionFile, &stConditionRecord, sizeof(stConditionRecord), MAX_COND_NO);

                          memset(&stConfigurationRecord, 0, sizeof(stConfigurationRecord));
                          ssInitFile(&stConfigurationFile, &stConfigurationRecord, sizeof(stConfigurationRecord), 1);
                          cprintf(" done.\n\r");
                       }  
                       break;
               
               case 03:
                       return;
                       break;
            
               case 10:
                       cprintf("\n\rRoom File   : %s (%d byte)", stConfigurationRecord.stRoomFile.szFileName, (int)sizeof(ST_ROOM));
                       cprintf("\n\rData Drive# : %u", stConfigurationRecord.stRoomFile.ucDeviceNo);
                       cprintf("\n\r\n\rRoom File   : ");
                       cgets(stConfigurationRecord.stRoomFile.szFileName, sizeof(stConfigurationRecord.stRoomFile.szFileName));
                       cprintf("\n\rData Drive #: ");
                       stConfigurationRecord.stRoomFile.ucDeviceNo = (unsigned char) atoi(gets(szTemp));  
                       break;

               case 11:
                       cprintf("\n\rObject File   : %s (%d byte)", stConfigurationRecord.stObjectFile.szFileName, (int)sizeof(ST_OBJECT));
                       cprintf("\n\rData Drive# : %u", stConfigurationRecord.stObjectFile.ucDeviceNo);
                       cprintf("\n\r\n\rObject File   : ");
                       cgets(stConfigurationRecord.stObjectFile.szFileName, sizeof(stConfigurationRecord.stObjectFile.szFileName));
                       cprintf("\n\rData Drive #: ");
                       stConfigurationRecord.stObjectFile.ucDeviceNo = (unsigned char) atoi(gets(szTemp));  
                       break;

               case 12:
                       cprintf("\n\rCondition File   : %s (%d byte)", stConfigurationRecord.stConditionFile.szFileName, (int)sizeof(ST_COND));
                       cprintf("\n\rData Drive# : %u", stConfigurationRecord.stConditionFile.ucDeviceNo);
                       cprintf("\n\r\n\rCondition File   : ");
                       cgets(stConfigurationRecord.stConditionFile.szFileName, sizeof(stConfigurationRecord.stConditionFile.szFileName));
                       cprintf("\n\rData Drive #: ");
                       stConfigurationRecord.stConditionFile.ucDeviceNo = (unsigned char) atoi(gets(szTemp));  
                       break;

               case 20:
              	       vEraseWarning();      
                       ucChoice = cgetc();
            
                       if (ucChoice == 'y')
                       {
                          cprintf("\n\r\n\r* initializing...");
                          ssInitFile(&stConfigurationFile, &stConfigurationRecord, sizeof(stConfigurationRecord), 1);
                          cprintf(" done.\n\r");
                       }
                       break;
                       
               case 21:
                       ssReadFile(&stConfigurationFile, &stConfigurationRecord, sizeof(ST_CONFIG), 1);
                       cprintf("\n\rmax. conditions [%d]: ", stConfigurationRecord.ssMaxConditions);
              	       stConfigurationRecord.ssMaxConditions = atoi(gets(szTemp));
              	       ssWriteFile(&stConfigurationFile, &stConfigurationRecord, sizeof(ST_CONFIG), 1);
                       break;

               case 22:
                       ssReadFile(&stConfigurationFile, &stConfigurationRecord, sizeof(ST_CONFIG), 1);
                       cprintf("\n\rborder color    : ");
                       stConfigurationRecord.ssBorderColor = atoi(gets(szTemp));
                       bordercolor(stConfigurationRecord.ssBorderColor); 
                       
                       cprintf("\n\rbackground color: ");
                       stConfigurationRecord.ssBackgroundColor = atoi(gets(szTemp));                                       
                       bgcolor(stConfigurationRecord.ssBackgroundColor);
                    
                       cprintf("\n\rtext color      : ");
                       stConfigurationRecord.ssTextColor = atoi(gets(szTemp));
                       textcolor(stConfigurationRecord.ssTextColor);
                       ssWriteFile(&stConfigurationFile, &stConfigurationRecord, sizeof(ST_CONFIG), 1);
                       break;
  
               case 30:
                       vEraseWarning();      
                       ucChoice = cgetc();
            
                       if (ucChoice == 'y')
                       {                         
                          memset(&stRoomRecord, 0, sizeof(stRoomRecord));        
                          cprintf("\n\r\n\r* initializing...");          
                          ssInitFile(&stConfigurationRecord.stRoomFile, &stRoomRecord, sizeof(stRoomRecord), MAX_ROOM_NO);
                          cprintf(" done.\n\r");
                       }
                       break;
                       
               case 31:
              	       memset(&stRoomRecord, 0, sizeof(stRoomRecord));
              	       fflush(stdin);
                       ssRet = usCreateLevel(&stRoomRecord, &stConfigurationRecord.stRoomFile);
                       break;                   
                       
               case 32:
                       cprintf("\n\rview room no.: ");
                       fflush(stdin);
                       ssRoomNo = atoi(gets(szTemp));
                       memset(&stRoomRecord, 0, sizeof(stRoomRecord));
                       ssRet = ssReadFile(&stConfigurationRecord.stRoomFile, &stRoomRecord, sizeof(stRoomRecord), ssRoomNo);
                       ssRet = usDrawLevel(&stRoomRecord, map, RUNMODE_EDIT);               
                       break;
                       
               case 40:
                       vEraseWarning();      
                       ucChoice = cgetc();
            
                       if (ucChoice == 'y')
                       {            
                          cprintf("\n\r\n\r* init. object data file...");
                          memset(&stObjectRecord, 0, sizeof(stObjectRecord));
                          ssInitFile(&stConfigurationRecord.stObjectFile, &stRoomRecord, sizeof(stObjectRecord), MAX_OBJECT_NO);
                          cprintf(" done.");
                       }               
                       break;

               case 41:
                       memset(&stObjectRecord, 0, sizeof(stObjectRecord));
			                 fflush(stdin);
                       usCreateObject(&stObjectRecord, &stConfigurationRecord.stObjectFile);
                       break;  
                       
               case 42:  
                       do {
        	  	            clrscr();
        	  	            cprintf("\n\rview object no.: "); 
                          ssObjectNo = atoi(gets(szTemp));
			                    fflush(stdin);
			           } while ((ssObjectNo < 0) || (ssObjectNo > MAX_OBJECT_NO));
			     
                       memset(&stObjectRecord, 0, sizeof(stObjectRecord));                  
                       ssRet = ssReadFile(&stConfigurationRecord.stObjectFile, &stObjectRecord, sizeof(stObjectRecord), ssObjectNo);
                       usDrawObject(&stObjectRecord, map, RUNMODE_EDIT);
                       break;
                
               case 50:
                       vEraseWarning();      
                       ucChoice = cgetc();
            
                       if (ucChoice == 'y')
                       {                  
                          cprintf("\n\r\n\r* init. condition data file...");
                          memset(&stConditionRecord, 0, sizeof(stConditionRecord));
                          ssInitFile(&stConfigurationRecord.stConditionFile, &stConditionRecord, sizeof(stConditionRecord), MAX_OBJECT_NO);
                          cprintf(" done.");
                      }
                      break;                       
 
               case 51:
			                 memset(&stConditionRecord, 0, sizeof(stConditionRecord));   
                       ssCreateCondition(&stConditionRecord, &stConfigurationRecord.stConditionFile);
                       break;
               
               
               case 52:               
        	  	       do {
        	  	          clrscr();
        	  	          cprintf("\n\rview condition no.: ");
                        ssObjectNo = atoi(gets(szTemp));
			           } while ((ssObjectNo < 0) || (ssObjectNo > MAX_COND_NO));
			         			     
                 memset(&stConditionRecord, 0, sizeof(stConditionRecord));
			           ssRet = ssReadFile(&stConfigurationRecord.stConditionFile, &stConditionRecord, sizeof(stConditionRecord), ssObjectNo);
			           ssDrawCondition(&stConditionRecord);
			           break;

               case 53:  
        	  	       clrscr();
        	  	       vShowConditionHelp();
        	  	       cputsxy(0, 24, "Return: Back to Menu");
        	  	       ucChoice = cgetc();
        	  	       while( ucChoice != 0x0d);
                     break;
			          
               default:
                       break;
            }
            
            vInit(6,6,1);
            clrscr();
            ssHelp=ucCount1;
            
            for(ucCount1=0; ucCount1 < MAX_SUBMENU; ucCount1++)
               cputsxy(MENU_XPOS, MENU_YPOS+ucCount1, menu[ucCount2][ucCount1]);
            ucCount1=ssHelp;
            
         }
         
         gotoxy(MENU_XPOS,MENU_YPOS-2);
         cprintf("%s", label[ucCount2]);

         revers(1);
         cputsxy(MENU_XPOS, MENU_YPOS+ucCount1, menu[ucCount2][ucCount1]);
         revers(0);
      
         gotoxy(10,23);
         ssMenu=(10*ucCount2)+ucCount1;  
     }     
   } while( ! (ucChoice==0x0d && ssMenu==3));
}