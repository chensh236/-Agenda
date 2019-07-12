#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h" 
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>

static struct termios ori_attr, cur_attr;

static __inline 
int tty_reset(void)
{
        if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
                return -1;

        return 0;
}


static __inline
int tty_set(void)
{
        
        if ( tcgetattr(STDIN_FILENO, &ori_attr) )
                return -1;
        
        memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
        cur_attr.c_lflag &= ~ICANON;
//        cur_attr.c_lflag |= ECHO;
        cur_attr.c_lflag &= ~ECHO;
        cur_attr.c_cc[VMIN] = 1;
        cur_attr.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
                return -1;

        return 0;
}

static __inline
int kbhit(void) 
{
                   
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec  = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */

        if (retval == -1) {
                perror("select()");
                return 0;
        } else if (retval)
                return 1;
        /* FD_ISSET(0, &rfds) will be true. */
        else
                return 1;
        return 0;
}


int inputchar()
{
        int tty_set_flag;
        tty_set_flag = tty_set();
        int inputjudge=1; 
        while(inputjudge==1) {

                if( kbhit() ) {
                        int key = getchar();
                        return key;
                } 
				}

        if(tty_set_flag == 0) 
                tty_reset();
        return 0;
}





void put_money(void){
	srand(time(NULL));
	int moneyX=1+rand()%10;
	int moneyY=1+rand()%10;
	if(map[moneyY][moneyX]!='X' && map[moneyY][moneyX]!='H')
	map[moneyY][moneyX]='$';
	else put_money();
	return;
}


void output(void){
	for (int i = 0; i < 12; ++i)
	{
		printf("%s", map[i]);
		printf("\n");
	}
	return;
}

void gameover(void){
	printf("Game Over!\n");
	return;
}
void snakeMove(int snakeheadX,int snakeheadY){
	int judge=1;
	char input;
	while(judge==1){
		input=inputchar();
		switch(input){
			case 'W': if(map[snakeheadY-1][snakeheadX]=='*' || map[snakeheadY-1][snakeheadX]=='X') judge=0;
					else if(map[snakeheadY-1][snakeheadX]=='$'){
						snakeLength++;
						snakeheadY=snakeY[snakeLength-1]=snakeY[snakeLength-2]-1;
						snakeheadX=snakeX[snakeLength-1]=snakeX[snakeLength-2];
						map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
						map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]='X';
						put_money();
					}
					else {
						map[snakeY[0]][snakeX[0]]=' ';
						for (int i = 0; i < snakeLength-1; ++i)
						{
							snakeX[i]=snakeX[i+1];
							snakeY[i]=snakeY[i+1];
						}
						snakeY[snakeLength-1]--;
						snakeheadY--;
						map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
						map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]='X';
						
					}break;
			case 'D': if(map[snakeheadY][snakeheadX+1]=='*' || map[snakeheadY][snakeheadX+1]=='X') judge=0;
					else if(map[snakeheadY][snakeheadX+1]=='$'){
						snakeLength++;
						snakeheadY=snakeY[snakeLength-1]=snakeY[snakeLength-2];
						snakeheadX=snakeX[snakeLength-1]=snakeX[snakeLength-2]+1;
						map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
						put_money();
					}
					else {
						map[snakeY[0]][snakeX[0]]=' ';
						for (int i = 0; i < snakeLength-1; ++i)
						{
							snakeX[i]=snakeX[i+1];
							snakeY[i]=snakeY[i+1];
						}
						snakeX[snakeLength-1]++;
						snakeheadX++;
						map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
						map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]='X';
					}break;
			case 'A':	if(map[snakeheadY][snakeheadX-1]=='*' || map[snakeheadY][snakeheadX-1]=='X') judge=0;
					else if(map[snakeheadY][snakeheadX-1]=='$'){
						snakeLength++;
						snakeheadY=snakeY[snakeLength-1]=snakeY[snakeLength-2];
						snakeheadX=snakeX[snakeLength-1]=snakeX[snakeLength-2]-1;
						map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
						map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]='X';
						put_money();
					}
					else {
						map[snakeY[0]][snakeX[0]]=' ';
						for (int i = 0; i < snakeLength-1; ++i)
						{
							snakeX[i]=snakeX[i+1];
							snakeY[i]=snakeY[i+1];
						}
						snakeX[snakeLength-1]--;
						snakeheadX--;
						map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
						map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]='X';
					}break;
			case 'S':	if(map[snakeheadY+1][snakeheadX]=='*' || map[snakeheadY+1][snakeheadX]=='X') judge=0;
					else if(map[snakeheadY+1][snakeheadX]=='$'){
						snakeLength++;
						snakeheadY=snakeY[snakeLength-1]=snakeY[snakeLength-2]+1;
						snakeheadX=snakeX[snakeLength-1]=snakeX[snakeLength-2];
						map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
						map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]='X';
						put_money();
					}
					else {
						map[snakeY[0]][snakeX[0]]=' ';
						for (int i = 0; i < snakeLength-1; ++i)
						{
							snakeX[i]=snakeX[i+1];
							snakeY[i]=snakeY[i+1];
						}
						snakeY[snakeLength-1]++;
						snakeheadY++;
						map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
						map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]='X';
					}break;
		}
		printf("\033[2J");
		if(judge==1) output();
	}
	gameover();
}

int play(){
	int snakeheadX=5,snakeheadY=1;
	output();
	printf("\033[2J");
	put_money();
	output();
	snakeMove(snakeheadX,snakeheadY);
	printf("You mush have interest in trying again...\npress 'Q' to exit\n\n\n\n\n\n\n");
	char c = getchar();
	char junk = getchar();
	if(c=='Q')return 0;
}
