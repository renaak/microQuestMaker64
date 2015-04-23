/*
----------------------------------------------------------
File			: menu.c
Description		: microQuestMaker64 main menu routines
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "menu.h"

void vShowConditionHelp(void)
{   
   cprintf("* CONDITION HELP");  
   cprintf(NEWLINE); 
              /*1234567890123456789012345678901234567890*/
   cprintf("\n\rCondition types: single obj. or obj->obj");        
   cprintf("\n\rYou can either check an object attribute");
   cprintf("for a given value (single obj.) or check");                  
   cprintf("an obj. attr. for a given value and set");
   cprintf("\n\ranother object's attribute accordingly ");
   cprintf("\n\r(eg. obj#1=open -> obj#2=closed)       ");
   cprintf("\n\r\n\rOperators for evaluating attributes:");
   cprintf("\n\r\n\r[A]nd, [O]r, [N]ot, [E]qual,           ");
   cprintf("\n\rgreater than (>) or lighter than (<).  ");      
   cprintf("\n\r\n\rAttributes to be checked or changed:");
   cprintf("\n\r\n\r[1] object room #     [2] object locked");
   cprintf("\n\r[3] object open");         
}

void vEraseWarning(void)
{
      cprintf(NEWLINE);
      cprintf("\n\r* This will ERASE ALL DATA");
      cprintf("\n\r* Are you sure [y/n]?");
}