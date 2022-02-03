#define _CRT_SECURE_NO_WARNINGS

// time.h 를 이용하 현재 시간 출력 연습문

#include<stdio.h>
#include<time.h>



/*struct tm {
	int tm_sec;		//*seconds
	int tm_min;		// minutes
	int tm_hour;	//hour(0_23)
	int tm_mday;	//day of month(1_31)
	int tm_mon;		//month(0_11)
	int tm_year;	//(calendar year minus 1900
	int tm_wday;	//weekday (0-6, sunady = 0)
	int tm_yday;	// day of year (0-365)
	int tm_isdst;	// 0 iif daylight savings time is not in effect
};*/

int main_clock(void) {
	time_t nowtimer, beforetimer;
	nowtimer = beforetimer = time(0);			//현재 시각을 초 단위로 얻기
	
	struct tm t;
	localtime_s(&t, &nowtimer);		//지역 시간을 구함

	int hour = t.tm_hour;
	int min = t.tm_min;
	int sec = t.tm_sec;
	int year = t.tm_year + 1900;		// tm_year은 121의 값 즉 이전 1900년 의 값을 기록해서 1900을 더해줌
	int mont = t.tm_mon+1;				//달은 0~11이라 +1
	int day = t.tm_mday;				//day는 1_31의 값이므로 그냥 사용
	
	printf("%d년 %d월 %d일\n", year, mont, day);
	//printf("%d시 %d분 %d초\n", hour,min,sec);

	while (kbhit() == 1) {
		nowtimer = time(0);

		if (nowtimer != beforetimer) {
			beforetimer = nowtimer;
			localtime_s(&t, &nowtimer);
			printf("%d시 %d분 %d초", hour, min, sec);
			printf("\n");
		}
	}


	return 0;
}
