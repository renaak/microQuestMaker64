/*
----------------------------------------------------------
File            : adv.h
Description	    : microQuestMaker64 general header file
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#ifndef ADV_H
#define ADV_H

#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <cbm.h>

#define  ScreenPosX 0
#define  ScreenPosY 11

#define NEWLINE "\n\r"
#define STRING_SIZE 40

#define RUNMODE_GAME 1
#define RUNMODE_EDIT 0

#define SLEEPTIME 5500

#define PROGRAMSTRING "        microQuestMaker64 v0.1.6.1\n\r      (c) 2004-2009 by N. Haedecke\n\r         licensed under GNU GPL\n\r    Maze code (c) 1991 by Mark Howell\n\r"

enum display_mode {text, map, both, debug};

#endif
