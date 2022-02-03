#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<time.h>

int main(void) {
	time_t now;
	now = time(0);
	struct tm t;
	localtime_s(&t, &now);

	printf("%d : %d : %d\n", t.tm_hour, t.tm_min, t.tm_sec);
	
	return 0;
}