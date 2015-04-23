/*
 * MazeGen.c -- Mark Howell -- 8 May 1991
 *
 * Usage: MazeGen [width [height [seed]]]
 */

#include "mazegen.h"

int main(void)
{
   short ssRet=0;
   short ssRoomNo = 1;
   
   ST_FILE stConfigurationFile;
   ST_ROOM stRoomRecord;
   ST_CONFIG stConfigurationRecord;

   memset(&stRoomRecord, 0, sizeof(stRoomRecord));
   memset(&stConfigurationFile, 0, sizeof(stConfigurationFile)); 
   
   strcpy(stConfigurationRecord.stRoomFile.szFileName, "rooms");
   strcpy(stConfigurationFile.szFileName, "config");
   stConfigurationRecord.stRoomFile.ucDeviceNo = 8;
   stConfigurationFile.ucDeviceNo = 8;

   stConfigurationRecord.ssMaxConditions = 10;
   stConfigurationRecord.ssBorderColor = 6;
   stConfigurationRecord.ssBackgroundColor = 6;
   stConfigurationRecord.ssTextColor = 1;

   ssReadFile(&stConfigurationFile, &stConfigurationRecord, sizeof(ST_CONFIG), 1);
   
   textcolor(1);
   bgcolor(6);
   bordercolor(6);
   
   clrscr();
   chline(40);
   cprintf(PROGRAMSTRING);
   chline(40);
   cprintf(NEWLINE);
   cprintf("* MAZE GENERATOR");
   
   MazeMain(&stConfigurationRecord.stRoomFile);

   return 0;
}


int MazeMain(ST_FILE *pstFile)
{
    int width = WIDTH;
    int height = HEIGHT;
    int seed = 0;
    char szTemp[15];

    maze_t maze;
	
	cprintf(NEWLINE);
	fflush(stdin);
	
	do {
	     cprintf("\n\rmaze width  (max. %d)         : ", WIDTH);
	     width = atoi(gets(szTemp));
    } while ( width < 1 || width > WIDTH);

	fflush(stdin);

    do {
	     cprintf("\n\rmaze height (max. %d)         : ", HEIGHT);
	     height = atoi(gets(szTemp));
	} while ( height < 1 || height > HEIGHT);

	fflush(stdin);

    do {
	     cprintf("\n\rrandom seed (max. 255, 0=none): ");
	     seed = atoi(gets(szTemp));
	} while ( seed < 0 || seed > 255);    
    
    if (seed==0)
       srand ((int) time ((time_t *) NULL));
       	 
	/* 
    if (argc >= 2)
        width = atoi (argv [1]);

    if (argc >= 3)
        height = atoi (argv [2]);

    if (argc >= 4)
        srand (atoi (argv [3]));
    else
        srand ((int) time ((time_t *) NULL));

    if (width <= 0 || height <= 0) {
        (void) fprintf (stderr, "Illegal width or height value!\n");
        exit (EXIT_FAILURE);
    }
    */
    
    maze = (maze_t) calloc (width * height, sizeof (cell_t));
    
    if (maze == NULL) {
        (void) fprintf (stderr, "Can't allocate memory!\n");
        exit (EXIT_FAILURE);
    }
    
    CreateMaze (maze, width, height);

    /*PrintMaze (maze, width, height);*/

    (void) putchar ('\n');
    (void) putchar ('\n');

    /*SolveMaze (maze, width, height);*/

    PrintMaze (maze, width, height);
        
    SaveMaze(pstFile, maze, width, height);

    free (maze);
    /*exit (EXIT_SUCCESS);*/

    return (0);

} /* main */


void CreateMaze (maze_t maze, int width, int height)
{
    maze_t mp, maze_top;
    char paths [4];
    int visits, directions, loop;

    visits = width * height - 1;
    mp = maze;
    maze_top = mp + (width * height) - 1;
    loop = 1;

    while (visits) {
        directions = 0;

        if ((mp - width) >= maze && cell_empty (mp - width))
            paths [directions++] = UP;
            
        if (mp < maze_top && ((mp - maze + 1) % width) && cell_empty (mp + 1))
            paths [directions++] = RIGHT;
            
        if ((mp + width) <= maze_top && cell_empty (mp + width))
            paths [directions++] = DOWN;     

            
        if (mp > maze && ((mp - maze) % width) && cell_empty (mp - 1))
            paths [directions++] = LEFT;        
            
        if (directions) {
        
            visits--;
            directions = ((unsigned) rand () % directions);

            switch (paths [directions]) {
                case UP:
                    mp->up = TRUE;
                    (mp -= width)->down = TRUE;
                    break;
                case RIGHT:
                    mp->right = TRUE;
                    (++mp)->left = TRUE;
                    break;
                case DOWN:
                    mp->down = TRUE;
                    (mp += width)->up = TRUE;
                    break;
                case LEFT:
                    mp->left = TRUE;
                    (--mp)->right = TRUE;
                    break;
                default:
                    break;
            }
        } else {
            do {
                if (++mp > maze_top)
                    mp = maze;
            } while (cell_empty (mp));
        }
        loop++;
    }
}/* CreateMaze */


void SolveMaze (maze_t maze, int width, int height)
{
    maze_t *stack, mp = maze;
    int sp = 0;

    stack = (maze_t *) calloc (width * height, sizeof (maze_t));
    if (stack == NULL) {
        (void) fprintf (stderr, "Can't allocate memory!\n");
        exit (EXIT_FAILURE);
    }
    (stack [sp++] = mp)->visited = TRUE;

    while (mp != (maze + (width * height) - 1)) {

        if (mp->up && !(mp - width)->visited)
            stack [sp++] = mp - width;
        if (mp->right && !(mp + 1)->visited)
            stack [sp++] = mp + 1;
        if (mp->down && !(mp + width)->visited)
            stack [sp++] = mp + width;
        if (mp->left && !(mp - 1)->visited)
            stack [sp++] = mp - 1;

        if (stack [sp - 1] == mp)
            --sp;

        (mp = stack [sp - 1])->visited = TRUE;
    }
    while (sp--)
        if (stack [sp]->visited)
            stack [sp]->path = TRUE;

    free (stack);

}/* SolveMaze */


void PrintMaze (maze_t maze, int width, int height)
{
    int w, h;
    char *line, *lp;

    line = (char *) calloc ((width + 1) * 2, sizeof (char));
    if (line == NULL) {
        (void) fprintf (stderr, "Can't allocate memory!\n");
        exit (EXIT_FAILURE);
    }
    
    /*
    maze->up = TRUE;
    (maze + (width * height) - 1)->down = TRUE;
    */

    for (lp = line, w = 0; w < width; w++) {
        *lp++ = '+';
        if ((maze + w)->up)
            *lp++ = ((maze + w)->path) ? '.' : ' ';
        else
            *lp++ = '-';
    }
    *lp++ = '+';
    (void) puts (line);
    for (h = 0; h < height; h++) {
        for (lp = line, w = 0; w < width; w++) {
            if ((maze + w)->left)
                *lp++ = ((maze + w)->path && (maze + w - 1)->path) ? '.' : ' ';
            else
                *lp++ = '|';
            *lp++ = ((maze + w)->path) ? '.' : ' ';
        }
        *lp++ = '|';
        (void) puts (line);
        for (lp = line, w = 0; w < width; w++) {
            *lp++ = '+';
            if ((maze + w)->down)
                *lp++ = ((maze + w)->path && (h == height - 1 ||
                         (maze + w + width)->path)) ? '.' : ' ';
            else

                *lp++ = '-';
        }
        *lp++ = '+';
        (void) puts (line);
        maze += width;
    }
    free (line);

}/* PrintMaze */

void SaveMaze (ST_FILE *pstFile, maze_t maze, int width, int height)
{
   maze_t mp,hp;
   maze_t maze_top;
   ST_ROOM room;
   char count=1;
   char szTemp[15];

   fflush(stdin);

   cprintf("\n\rroom data filename: ");
   cgets(pstFile->szFileName, sizeof(pstFile->szFileName));

   fflush(stdin);
   
   cprintf("\n\rroom data drive # : ");
   pstFile->ucDeviceNo = atoi(gets(szTemp));
   pstFile->ucDeviceNo = ucCheckDeviceNo( &(pstFile->ucDeviceNo));

   memset(&room, 0, sizeof(room));        
   cprintf("\n\r\n\r* initializing");          
   ssInitFile(pstFile, &room, sizeof(room), MAX_ROOM_NO);
       
   mp=maze;
   maze_top = mp + (width * height) - 1;
 
   do
   {
      mp->id=count;      
      ++count;
      ++mp;
   } while (mp <= maze_top);
   
   mp=maze;
   count=1;
 
   cprintf(", saving maze...");
 
   do
   {
      hp=mp;
      
      if (mp->up == TRUE)
      {
         (hp - width)->down = count;
         mp->up = (hp - width)->id;
      }

      if (mp->right == TRUE)
      {
         (hp+1)->left = count;
         mp->right = (hp+1)->id;
      }

      if (mp->down == TRUE)
      {
         (hp + width)->up = count;
         mp->down = (hp + width)->id;
      }

      if (mp->left == TRUE)
      {
         (hp-1)->right = count;
         mp->left = (hp-1)->id;
      }
      
      room.ssRoomNo = mp->id;
      room.ssNorth  = mp->up;
      room.ssSouth  = mp->down;
      room.ssEast   = mp->right;
      room.ssWest   = mp->left;
      
      room.scCharUp    = DEFAULT_ROOM_CHAR_UP;
      room.scCharDown  = DEFAULT_ROOM_CHAR_DOWN;
      room.scCharFloor = DEFAULT_ROOM_CHAR_FLOOR;
      room.scCharWall  = DEFAULT_ROOM_CHAR_WALL;
      room.scCharDoor  = DEFAULT_ROOM_CHAR_DOOR;
      
      room.ssBackgroundColor=6;
      room.ssBorderColor=6;
      room.ssTextColor=1;
      
      ssWriteFile(pstFile, &room, sizeof(ST_ROOM), count);
      ++count;
      ++mp;
   } while (mp <= maze_top);
   
   cprintf(" done.");

}
