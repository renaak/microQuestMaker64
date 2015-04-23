/*
----------------------------------------------------------
File			: toolfuncs.h
Description		: microQuestMaker64 help routines header
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#ifndef TOOLFUNCS_H
#define TOOLFUNCS_H

#define poke(A,X) (*(unsigned char *)A) = (X)
#define peek(A) (*(unsigned char *)A)
#define SLEEP 1000

char *cgets(char *pcBuffer, unsigned int uiLen);
void vSleep(short ssSleep);

#endif
