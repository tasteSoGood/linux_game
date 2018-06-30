#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define SIZE 20
#define CLEAR_ALL "\033[2J\033[?25l" // 清屏，隐藏光标food.

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	point body[(SIZE - 1) * (SIZE - 1)];
	int length;
} list;

point food;
list snake;
bool table[SIZE][SIZE];
int direction = 0;

void setBufferedInput(bool);
void init_table();
void print_table();
void gen_food();
int randint(int, int);
int scanKeyboard();

/*******************************************/

void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		// set the new state
		enabled = true;
	} else if (!enable && enabled) {
		// get the terminal settings for standard input
		tcgetattr(STDIN_FILENO,&new);
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &=(~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		// set the new state
		enabled = false;
	}
} // 控制输出流

void init_table() {
	memset(table, 0, SIZE * SIZE);
	memset(table[0], 1, SIZE);
	memset(table[SIZE - 1], 1, SIZE);
	int i;
	for(i = 0; i < SIZE; i++)
		table[i][0] = table[i][SIZE - 1] = 1;
}

void print_table() {
	int x = 0, y = 0;
	int i, j;
	printf(CLEAR_ALL);
	printf("\033[%d;%dH", x, y * 2);
	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++)
			printf("%s", table[i][j] ? "■ " : "□ ");
		printf("\n");
	}
}

void init_snake() {
	snake.body[0].x = randint(1, SIZE - 1);
	snake.body[0].y = randint(1, SIZE - 1);
	snake.length = 1;
	table[snake.body[0].x][snake.body[0].y] = 1;
}

void move() {
	switch(direction) {
		case 0:snake.body[0].x += 1; break;//上
		case 1:snake.body[0].x -= 1; break;//下
		case 2:snake.body[0].y += 1; break;//左
		case 3:snake.body[0].y -= 1; break;//右
		default: break;
	}
	snake.body[0].x = snake.body[0].x % (SIZE - 1);
	snake.body[0].y = snake.body[0].y % (SIZE - 1);
	init_table();
	table[food.x][food.y] = 1;
	int i;
	for(i = 0; i < snake.length; i++) {
		table[snake.body[i].x][snake.body[i].y] = 1;
	}
}

void gen_food() {
	food.x = randint(1, SIZE - 1);
	food.y = randint(1, SIZE - 1);
	table[food.x][food.y] = 1;
}

/**************功能函数***********************/
int randint(int a, int b) {
	float temp = (float)rand() / INT_MAX;
	return (int)(temp * (b - a) + a);
}

int scanKeyboard() {
	int in;
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
	in = getchar();
	tcsetattr(0,TCSANOW,&stored_settings);
	return in;
}

int main(){
	srand((unsigned int)time(NULL));
	init_table();
	init_snake();
	gen_food();
	print_table();
	setBufferedInput(false);
	while(true) {
		// char c = getchar();
		// switch(c) {
		// 	case 65: direction = 0; break;
		// 	case 66: direction = 1; break;
		// 	case 68: direction = 2; break;
		// 	case 67: direction = 3; break;
		// 	default: break;
		// }
		move();
		print_table();
		sleep(1.);
	}
	setBufferedInput(true);
	return 0;
}