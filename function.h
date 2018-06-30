#include <termios.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include "init.h"

int scanKeyboard();
int randint(int, int);

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

int randint(int a, int b) {
	float temp = (float)rand() / INT_MAX;
	return (int)(temp * (b - a) + a);
}