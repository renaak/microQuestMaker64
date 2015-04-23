/*
----------------------------------------------------------
File			: condition.c
Description		: microQuestMaker64 game logic module
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "adv.h"
#include "condition.h"
#include "toolfuncs.h"

#ifndef __RUNTIME__
short ssCreateCondition(ST_COND *pstCondition, ST_FILE *pstFile)
{
   unsigned char ucChoice;
   char szTemp[MAX_COND_TEXT];
   char ssCount=0; 
       
   /* enter conditions */
   do
   {
   
      clrscr();
                           
      cprintf(NEWLINE);
      chline(40);

      do                                                                               
      {                                                                                
        cprintf("\n\redit condition no.: ");                                          
        pstCondition->ssCondNo = atoi(gets(szTemp));                              
      } while ((pstCondition->ssCondNo < 0) || (pstCondition->ssCondNo > MAX_COND_NO));  	
   	        
      do
      {
        cprintf("\n\rcondition type    : ");
        pstCondition->ssCondType = atoi(gets(szTemp));
      } while ((pstCondition->ssCondType < 0) || (pstCondition->ssCondType > MAX_COND_TYPE));         
              
      switch (pstCondition->ssCondType)
      {   
         case 1:
               {
               cprintf("\n\robject no.        : ");
               pstCondition->ssSObj = atoi(gets(szTemp));  
         
               cprintf("\n\rattribute no.     : ");
               pstCondition->ssSAttr = atoi(gets(szTemp));    

               cprintf("\n\roperator          : ");
          
               gets(szTemp);
               ucChoice=szTemp[0];

               switch (ucChoice)
               {
                  case '=' :
                           {
            	           pstCondition->ssOper |= COND_OPR_EQ;            	           
            	           break;	            	     
            	           }

                  case 'a' :
                           {
                           pstCondition->ssOper |= COND_OPR_AND; 
                	       break;
            	           }
            	     	            	     
                  case 'o' :
                           {
                           pstCondition->ssOper |= COND_OPR_OR;
                	       break;
            	           }        	     

                  case 'n' :
                           {
                           pstCondition->ssOper |= COND_OPR_NOT;
            	           break;
            	           }

                  case '>' :
                           {
                           pstCondition->ssOper |= COND_OPR_GT;
                	       break;
                	       }
            	     
                  case '<' :
                           {
                           pstCondition->ssOper |= COND_OPR_LT;
                	       break;
                	       }
            	     
                  default: break;
               }

              cprintf("\n\rvalue             : ");
              pstCondition->ssSVal = atoi(gets(szTemp));     
            
              cprintf(NEWLINE);
         
              ssCreateConditionString(pstCondition); 
              cprintf(NEWLINE);          
              cprintf("* is the above syntax correct [y/n]?");
             
              break;
              }
            
     break;
     }
   
   fflush(stdin);
   
   } while (cgetc() != 'y');
   
  ssWriteFile(pstFile, pstCondition, sizeof(ST_COND), pstCondition->ssCondNo);

  cputsxy(0, 24, "Return: Back to Menu");
       
   do
   {    
      ucChoice=cgetc();
      
   } while (ucChoice!=0x0d);                  
                         
   return 0;	         
}                        
                         
short ssDrawCondition(ST_COND *pstCondition)
{
   int  ssCondNo = 0;
   char scJoyDir=0;
   unsigned char ucChoice;
   
   clrscr();
   cprintf("info on condition #%d:", pstCondition->ssCondNo);
   cprintf(NEWLINE);
   cprintf(NEWLINE);
   
   ssCreateConditionString(pstCondition);
   
   cprintf(NEWLINE);  
   chline(40);
   cprintf(NEWLINE);
   
   cputsxy(0, 24, "Return: Back to Menu");
   
   do
   {
      ucChoice=cgetc();
   } while (ucChoice!=0x0d);
   
   return 0;	
}

short ssCreateConditionString(ST_COND *pstCondition)
{  
   cprintf("\n\r  condition type is: ");
   if (pstCondition->ssCondType == COND_TYPE_OBJONLY) 
      cprintf("single object");
   else
      cprintf("object <-> object");
   
   cprintf("\n\r\n\r  formula: object #%d -> ", pstCondition->ssSObj);
   
   if (pstCondition->ssSAttr == 1)
      cprintf("current room");
 
   if (pstCondition->ssSAttr == 2)
      cprintf("obj. locked");

   if (pstCondition->ssSAttr == 3)
      cprintf("object open");

   /* operators */
   if (pstCondition->ssOper & COND_OPR_EQ)
   {  
      cprintf(" = ");
   }
   
   if (pstCondition->ssOper & COND_OPR_AND)
      cprintf(" and ");

   if (pstCondition->ssOper & COND_OPR_OR)
      cprintf(" or ");  

   if (pstCondition->ssOper & COND_OPR_NOT)
      cprintf(" not ");  
 
   if (pstCondition->ssOper & COND_OPR_GT)
      cprintf(" > ");

   if (pstCondition->ssOper & COND_OPR_LT)
      cprintf(" < ");
   
   switch (pstCondition->ssSAttr)
   {
      case 1:
          {
          cprintf("%u", pstCondition->ssSVal);
          break;
          }
          
      case 2:
          {
          cprintf("%s", (pstCondition->ssSVal & OBJ_ATTR_LOCKED) ? "true" : "false");
          break;   
          }
          
      case 3:
          {
          cprintf("%s", (pstCondition->ssSVal & OBJ_ATTR_OPEN) ? "true" : "false");
          break;
          }
   }	
}
#endif

short ssCheckCondition(short ssId, ST_OBJECT *pstObjectArr, ST_COND *pstCondition)
{   
   switch (pstCondition->ssSAttr)
   {
      case 1:
              switch (pstCondition->ssOper)
              {
                     case COND_OPR_EQ:
                     	              if (pstObjectArr[pstCondition->ssSObj].ssCurrentRoom == pstCondition->ssSVal)
                     	              	 return 1;
                     	              else
                     	              	 return 0;
                     	              break;
                     	              
                     case COND_OPR_NOT:
                     	              if (pstObjectArr[pstCondition->ssSObj].ssCurrentRoom != pstCondition->ssSVal)
                     	              	 return 1;
                     	              else
                     	              	 return 0;
                     	              break;
                     	              
                     case COND_OPR_GT:
                     	              if (pstObjectArr[pstCondition->ssSObj].ssCurrentRoom > pstCondition->ssSVal)
                     	              	 return 1;
                     	              else
                     	              	 return 0;
                     	              break;
                     	              
                     case COND_OPR_LT:
                     	              if (pstObjectArr[pstCondition->ssSObj].ssCurrentRoom < pstCondition->ssSVal)
                     	              	 return 1;
                     	              else
                     	              	 return 0;
                     	              break;
                     default:
                     	              return 0;
                     	              break;                   	                     	                            	
              }
      	      break;

      case 2:
      	      if (pstCondition->ssSVal != 0)
      	      {
      	      	 if (pstObjectArr[pstCondition->ssSObj].usFlag & OBJ_ATTR_LOCKED)
      	      	    return 1;
      	      	 else
      	      	    return 0;
      	      }

      	      if (pstCondition->ssSVal == 0)
      	      {
      	      	 if (! (pstObjectArr[pstCondition->ssSObj].usFlag & OBJ_ATTR_LOCKED))
      	      	    return 1;
      	      	 else
      	      	    return 0;
      	      }     	            	      	       	
      	      break;
      	      
      case 3: 
      	      if (pstCondition->ssSVal != 0)
      	      {
      	      	 if (pstObjectArr[pstCondition->ssSObj].usFlag & OBJ_ATTR_OPEN)
      	      	    return 1;
      	      	 else
      	      	    return 0;
      	      }

      	      if (pstCondition->ssSVal == 0)
      	      {
      	      	 if (! (pstObjectArr[pstCondition->ssSObj].usFlag & OBJ_ATTR_OPEN))
      	      	    return 1;
      	      	 else
      	      	    return 0;
      	      }	           	        	
      	      break;
   
      default:
      	      return 0;
      	      break;	
   	
   }

   return ssId;	
}
