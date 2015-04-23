/*
----------------------------------------------------------
File			: parser.c
Description		: microQuestMaker64 2+2 word parser module
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "parser.h"
#include "movement.h"

signed short ssReadCommand(char *pcCommandString)
{
    printf("\n\r>");
    gets(pcCommandString);
    return 0;
}

/* simple four-word parser (e.g. 'take knife', 'put paper into box') */
signed short ssParseCommand(char *pcCommandString, signed short ssRoomNo, ST_OBJECT *pstObject)
{
   signed short ssObjectNo = 0;
   signed short ssCount=0; 
   signed short ssObjectDestNo = 0;

   char szWords[MAX_WORDS][MAX_OBJECT_SHORT_TEXT];
   char *pcPos=NULL;

   memset(szWords, '\0', sizeof(szWords));

   while ( (pcPos = strstr(pcCommandString, " ")) && (ssCount < strlen(pcCommandString)-1) )
   {
      *pcPos = '\0';
      strcpy(szWords[ssCount], pcCommandString);
      strcpy(pcCommandString, (pcPos+1));
      ++ssCount;
   }
   
   if (strlen(pcCommandString))
   {
      strcpy(szWords[ssCount], pcCommandString);	
   }

   ssObjectNo = ssCheckObjectByName(szWords[1], pstObject);
   ssObjectDestNo = ssCheckObjectByName(szWords[3], pstObject);
    
   if (strlen(szWords[0]) == 1)
   {
      if (!strcmp(szWords[0], "n"))
      {
         return ACT_MOVE_N;
      }

      if (!strcmp(szWords[0], "s"))
      {
         return ACT_MOVE_S;
      }

      if (!strcmp(szWords[0], "e"))
      {
         return ACT_MOVE_E;
      }

      if (!strcmp(szWords[0], "w"))
      {
         return ACT_MOVE_W;
      }

      if (!strcmp(szWords[0], "u"))
      {
         return ACT_MOVE_U;
      }

      if (!strcmp(szWords[0], "d"))
      {
         return ACT_MOVE_D;
      }
   }

   if (!strcmp(szWords[0], "text"))
   {
      return ACT_CMD_NOMAP;
   }

   if (!strcmp(szWords[0], "map"))
   {
      return ACT_CMD_MAP;
   }

   if (!strcmp(szWords[0], "quit"))
   {
      return ACT_CMD_QUIT;
   }

   if (!strcmp(szWords[0], "help"))
   {
      return ACT_CMD_HELP;
   }

   if (!strcmp(szWords[0], "inv"))
   {
      vListInventory(pstObject);
      return ACT_CMD_NOP;
   }

   if (!strcmp(szWords[0], "take"))
   {
      if (ssObjectNo)
      {
         if ((pstObject[ssObjectNo].ssCurrentRoom == ssRoomNo))
         {
            if( (pstObject[ssObjectNo].usFlag & OBJ_ATTR_MOVE) )
            {
               pstObject[ssObjectNo].ssCurrentRoom = -1;
               
               if (pstObject[ssObjectNo].scParentObjectNo != 0)
               {
                  pstObject[ssObjectNo].scParentObjectNo = 0;
               }
               
               return ACT_CMD_NOP;
            }
            else
               return ACT_CMD_NOT_TAKE;
         }
      }
      else
         return ACT_CMD_NOT_THERE;
      
   }

   if ( (!strcmp(szWords[0], "drop")) || (!strcmp(szWords[0], "put")) )
   {         
      if ( (strstr(szWords[2], "into")) && (szWords[3] != NULL) )
      {      	
      	 if ( ! (pstObject[ssObjectDestNo].usFlag & OBJ_ATTR_OPEN) )
            return ACT_CMD_CLOSED;

         if (ssObjectNo != 0 && ssObjectDestNo != 0 && (pstObject[ssObjectDestNo].usFlag & OBJ_ATTR_OPEN) )
         {
            if ((pstObject[ssObjectNo].ssCurrentRoom == -1))
            {
               pstObject[ssObjectNo].ssCurrentRoom = ssRoomNo;
               pstObject[ssObjectNo].scParentObjectNo = ssObjectDestNo;         
               return ACT_CMD_NOP;
            }
            else
               return ACT_CMD_NOT_CARRY;
         }         
      } // end put into
      else
      {
      	 ssObjectNo = ssCheckObjectByName(szWords[1], pstObject); 
      	
         if (ssObjectNo != 0)
         {
            if ((pstObject[ssObjectNo].ssCurrentRoom == -1))
            {
               pstObject[ssObjectNo].ssCurrentRoom = ssRoomNo;
                        
               return ACT_CMD_NOP;
            }
            else
               return ACT_CMD_NOT_CARRY;
         } // end if
      } // end put
   }
   
   if (!strcmp(szWords[0], "open"))
   {
      if (ssObjectNo)
      {
         if ((pstObject[ssObjectNo].ssCurrentRoom == ssRoomNo))
         {   
              if (! (pstObject[ssObjectNo].usFlag & OBJ_ATTR_CONTAINER) )
                 return ACT_CMD_NOT_OPEN;
                 
              if ( (pstObject[ssObjectNo].usFlag & OBJ_ATTR_LOCKED) )
                 return ACT_CMD_IS_LOCKED;
  
              if ( (pstObject[ssObjectNo].usFlag & OBJ_ATTR_OPEN) )
            	 return ACT_ALREADY_OPEN;
         
            if ( ! (pstObject[ssObjectNo].usFlag & OBJ_ATTR_OPEN) )
            {
               pstObject[ssObjectNo].usFlag |= OBJ_ATTR_OPEN;
               
               for (ssCount = 1; ssCount < MAX_OBJECT_NO; ssCount++) 
               {
                   if (pstObject[ssCount].scParentObjectNo == pstObject[ssObjectNo].ssObjectNo)
                   {
                   	  pstObject[ssCount].ssCurrentRoom = ssRoomNo;
                   }
               }
               return ACT_CMD_NOP;
            }
         }
      }
      else
         return ACT_CMD_NOT_THERE;
   }

   if (!strcmp(szWords[0], "close"))
   {
      if (ssObjectNo)
      {
         if ((pstObject[ssObjectNo].ssCurrentRoom == ssRoomNo))
         {
            if (! (pstObject[ssObjectNo].usFlag & OBJ_ATTR_CONTAINER) )
               return ACT_CMD_NOT_CLOSE;         	
         	
            if ( ! (pstObject[ssObjectNo].usFlag & OBJ_ATTR_OPEN) )
               return ACT_ALREADY_CLOSED;

            if ( (pstObject[ssObjectNo].usFlag & OBJ_ATTR_OPEN) )
            {
               pstObject[ssObjectNo].usFlag ^= OBJ_ATTR_OPEN;
               
               for (ssCount = 1; ssCount < MAX_OBJECT_NO; ssCount++) 
               {               	
                   if (pstObject[ssCount].scParentObjectNo == pstObject[ssObjectNo].ssObjectNo)
                   {
                   	  pstObject[ssCount].ssCurrentRoom = 0;
                   }
               }              
               return ACT_CMD_NOP;
            }
            else
               return ACT_CMD_NOT_CLOSE;
         }
      }
      else
         return ACT_CMD_NOT_THERE;      
   }

   if (!strcmp(szWords[0], "lock") )
   {  
      if (ssObjectNo == 0)
      	 return ACT_CMD_NOT_THERE;
   	    	    	        
      if ( (!strcmp(szWords[2], "with")) && (szWords[3] != NULL) )
      {    	   	
         if (! (pstObject[ssObjectNo].usFlag & OBJ_ATTR_CONTAINER) )
            return ACT_CMD_NOT_LOCK;
      	
         if (pstObject[ssObjectNo].usFlag & OBJ_ATTR_OPEN)
            return ACT_CLOSE_FIRST;            

         if (pstObject[ssObjectNo].usFlag & OBJ_ATTR_LOCKED)
            return ACT_ALREADY_LOCKED;      
      	
         if (ssObjectNo != 0 && ssObjectDestNo != 0 && pstObject[ssObjectDestNo].scUnlockObjectNo == ssObjectNo && ( ! (pstObject[ssObjectNo].usFlag & OBJ_ATTR_LOCKED)) && (pstObject[ssObjectDestNo].usFlag & OBJ_ATTR_KEY) )
         {      	
             pstObject[ssObjectNo].usFlag |= OBJ_ATTR_LOCKED;
             return ACT_CMD_IS_LOCKED;
         }
         else
            return ACT_CMD_NOT_LOCK;
      } // end unlock with
      else
         return ACT_CMD_INVALID;
   }

   if (!strcmp(szWords[0], "unlock") )
   {
      if (ssObjectNo == 0)
      	 return ACT_CMD_NOT_THERE;   	
   	
      if ( (!strcmp(szWords[2], "with")) && (szWords[3] != NULL) )
      { 
         if (! (pstObject[ssObjectNo].usFlag & OBJ_ATTR_CONTAINER) )
            return ACT_CMD_NOT_UNLOCK;
      	
         if (pstObject[ssObjectNo].usFlag & OBJ_ATTR_OPEN)
            return ACT_ALREADY_OPEN;            
    
         if ( ! (pstObject[ssObjectNo].usFlag & OBJ_ATTR_LOCKED) )
            return ACT_ALREADY_UNLOCKED;
      	 
         if (ssObjectNo != 0 && ssObjectDestNo != 0 && pstObject[ssObjectDestNo].scUnlockObjectNo == ssObjectNo && (pstObject[ssObjectDestNo].usFlag & OBJ_ATTR_KEY) )
         {
             pstObject[ssObjectNo].usFlag ^= OBJ_ATTR_LOCKED;
             return ACT_CMD_IS_UNLOCKED;
         }
         else
            return ACT_CMD_NOT_UNLOCK;
      } // end unlock with
      else
         return ACT_CMD_INVALID;
   }

   /* default response, if none of the above applied */
   return ACT_CMD_INVALID;
}
