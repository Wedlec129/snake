#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
//wedlec
//gcc snake.c -lncurses
int main(){
	int snake_len = 6;
	int x = snake_len, y = 0, ch = 0;
	int x_apple = 0, y_apple = 0;
	enum direction{
		NONE,
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
	enum direction dir = NONE;

	if (NULL == initscr()) {return __LINE__ ; }
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	int field[LINES][COLS];

	for(int i = 0; i < LINES; i++){
		for(int j = 0; j < COLS; j++){
			field[i][j] = 0;
		}
	}

	for(int i = 1; i <= snake_len; i++){
		field[0][i] = i;
		mvaddch(0, i, '*');
	}
	field[0][snake_len] = snake_len;
	
	do {	
		if(rand()%20 == 0){
			while(field[y_apple=rand()%LINES][x_apple=rand()%COLS] != 0);
			field[y_apple][x_apple] = 999999;
			mvaddch(y_apple, x_apple, '@');
		}

		switch(ch) {
			case KEY_UP:
				dir=UP;
				//y = (y + LINES - 1) % LINES;
				break;
			case KEY_DOWN:
				dir=DOWN;
				//y = (y + 1) % LINES;
				break;
			case KEY_LEFT:
				dir=LEFT;
				//x = (x + COLS - 1) % COLS;
				break;
			case KEY_RIGHT:
				dir=RIGHT;
				//x = (x + 1) % COLS;
				break;
			}
		if(dir==UP){
            		y = (y + LINES - 1) % LINES;
        	}
        	if(dir==DOWN){
            		y = (y + 1) % LINES;
        	}
        	if(dir==RIGHT){
           		x = (x + 1) % COLS;
        	}
        	if(dir==LEFT){
           		x = (x + COLS - 1) % COLS;
        	}
		usleep(100000);
		if(field[y][x] == 999999){
			snake_len += 1;
			field[y][x] = snake_len;
		}
		else if((field[y][x] != 0)&(field[y][x] != 999999)&(field[y][x] != snake_len)&(dir!=NONE)){
			printf("GAME OWER");
			endwin();
			return 0;
		}
		else{
			field[y][x] = snake_len;
			for(int i = 0; i < LINES; i++){
				for(int j = 0; j < COLS; j++){
					if((field[i][j] > 1)&(field[i][j]!=999999)&(dir!=NONE)){
						field[i][j] -= 1;
					}
					else if(field[i][j] == 1){
						mvaddch(i, j, ' ');
						field[i][j] = 0;
					}
				}
			}	
		}	
		mvaddch(y, x, '*');
		refresh();
	}
	while('q' != (ch = getch()));
	endwin();
	return 0;
}
