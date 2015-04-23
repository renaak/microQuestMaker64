/*
----------------------------------------------------------
File			: movement.c
Description		: microQuestMaker64 player movement module
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#include "adv.h"
#include "advfuncs.h"

signed short ssMovePlayer(signed short ssRoomNo, ST_ROOM *pstRoomRecord, signed short ssAction)
{
  signed short ssNewRoomNo = 0;
  signed short ssCount= 0;

  if (ssAction == ACT_MOVE_N && pstRoomRecord->ssNorth != 0)
     {
        ssNewRoomNo = pstRoomRecord->ssNorth;
     }
  else
  if (ssAction == ACT_MOVE_S && pstRoomRecord->ssSouth != 0)
     {
        ssNewRoomNo = pstRoomRecord->ssSouth;
     }
  else
  if (ssAction == ACT_MOVE_E && pstRoomRecord->ssEast != 0)
     {
        ssNewRoomNo = pstRoomRecord->ssEast;
     }
  else
  if (ssAction == ACT_MOVE_W && pstRoomRecord->ssWest != 0)
     {
        ssNewRoomNo = pstRoomRecord->ssWest;
     }
  else
  if (ssAction == ACT_MOVE_U && pstRoomRecord->ssUp != 0)
     {
        ssNewRoomNo = pstRoomRecord->ssUp;
     }
  else
  if (ssAction == ACT_MOVE_D && pstRoomRecord->ssDown != 0)
     {
        ssNewRoomNo = pstRoomRecord->ssDown;
     }
  else
     {
        #ifdef DEBUG
           cprintf("\n\runknown destination: action: %d - room: %d ", ssAction, ssRoomNo);
        #endif

         cprintf(MSG_NO_DIRECTION);
         for(ssCount = 0; ssCount < SLEEPTIME; ssCount++);

        ssNewRoomNo = ssRoomNo;
     }

   return ssNewRoomNo;
}


