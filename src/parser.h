/*
----------------------------------------------------------
File			: parser.h
Description		: microQuestMaker64 parser module header
Copyright		: (c) 2004 - 2009 by Niels Haedecke
License			: licensed under GNU GPL 2
----------------------------------------------------------
*/

#ifndef INPUT_H
#define INPUT_H

#include "level.h"
#include "object.h"

#define MAX_WORDS 4
#define UNKONWN_DEST -1

#define ACT_MOVE_N 10
#define ACT_MOVE_S 11
#define ACT_MOVE_E 12
#define ACT_MOVE_W 13
#define ACT_MOVE_U 14
#define ACT_MOVE_D 15


#define ACT_CMD_NOP          -1
#define ACT_CMD_INVALID       0
#define ACT_ALREADY_OPEN     70
#define ACT_ALREADY_CLOSED   71
#define ACT_ALREADY_LOCKED   72
#define ACT_ALREADY_UNLOCKED 73
#define ACT_CMD_NOT_THERE    80
#define ACT_CMD_NOT_CARRY    81
#define ACT_CMD_NOT_TAKE     82
#define ACT_CMD_NOT_OPEN     83
#define ACT_CMD_NOT_CLOSE    84
#define ACT_CMD_NOT_LOCK     85
#define ACT_CMD_NOT_UNLOCK   86
#define ACT_CMD_IS_LOCKED    87
#define ACT_CMD_IS_UNLOCKED  88
#define ACT_CMD_HELP         90
#define ACT_CMD_NOMAP        91
#define ACT_CMD_MAP          92
#define ACT_CLOSE_FIRST      93
#define ACT_CMD_CLOSED       95
#define ACT_CMD_QUIT         99

#define MSG_NOT_UNDERSTAND        "You can't do that!!"
#define MSG_NO_DIRECTION          "You can't go that way!"
#define MSG_NOT_CARRY             "You don't carry that item!"
#define MSG_NOT_TAKE              "You can't take that item!"
#define MSG_NOT_THERE             "There is no such object."
#define MSG_NOT_OPEN              "You can't open this item."
#define MSG_NOT_CLOSE             "You can't close this item."
#define MSG_NOT_LOCK              "You can't lock this item."
#define MSG_NOT_UNLOCK            "You can't unlock this item."
#define MSG_ITEM_NEED_CLOSE       "You must close it first!"
#define MSG_ITEM_ALREADY_OPEN     "It's already open!"
#define MSG_ITEM_ALREADY_CLOSED   "It's already closed!"
#define MSG_ITEM_ALREADY_LOCKED   "It's already locked!"
#define MSG_ITEM_ALREADY_UNLOCKED "It's already unlocked!"
#define MSG_ITEM_IS_LOCKED        "It's locked!"
#define MSG_ITEM_IS_UNLOCKED      "It's unlocked!"
#define MSG_ITEM_CLOSED           "You must open it first!"

signed short ssReadCommand(char *pcCommand);
signed short ssParseCommand(char *pcCommandString, signed short ssRoomNo, ST_OBJECT *pstObject);

#endif
