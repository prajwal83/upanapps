#ifndef _LIB_MDATE_H_
#define _LIB_MDATE_H_

#include <ctype.h>
#include <dtime.h>

/* Day of Month is the only one which is 1 based index */

typedef struct
{
	int dayOfMonth ;
	int month ;
	int year ;

	int dayOfWeek ;
} mdate ;

//Days
#define DAYS_PER_NLYEAR 365
#define DAYS_PER_LYEAR 366

//Time
#define SEC_PER_MIN 60
#define MIN_PER_HOUR 60
#define SEC_PER_HOUR 3600
#define SEC_PER_DAY 86400
#define HOURS_PER_DAY 24

typedef enum
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
	MONTHS_PER_YEAR = DECEMBER,
	MONTHS_PER_YEAR_SIZE
} MONTHS ;

typedef enum
{
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
	DAYS_PER_WEEK
} DAYS ;

#define IS_LEAP_YEAR(year) ( (year % 4) == 0 )

bool mdate_Set(mdate* date, int dayOfMonth, int month, int year) ;
void mdate_Normalize(const mdate* src, mdate* dest) ;
int mdate_GetDaysInMonth(const mdate* date) ;
int mdate_GetDaysInMonth_1(int month, int year) ;
bool mdate_IsValidDayOfWeek(int dayOfWeek) ;
bool mdate_IsValidDayOfMonth(const mdate* date) ;
bool mdate_IsValidMonth(int month) ;
bool mdate_IsValidYear(int year) ;
bool mdate_IsValid(const mdate* date) ;

bool mdate_AddDays(mdate* date, int days) ;
bool mdate_AddWeeks(mdate* date, int days) ;
bool mdate_AddMonths(mdate* date, int months) ;
bool mdate_AddYears(mdate* date, int years) ;

bool mdate_SubtractDays(mdate* date, int days) ;
bool mdate_SubtractWeeks(mdate* date, int days) ;
bool mdate_SubtractMonths(mdate* date, int months) ;
bool mdate_SubtractYears(mdate* date, int years) ;

bool mdate_IsGreater(const mdate* a, const mdate* b) ;
bool mdate_IsLesser(const mdate* a, const mdate* b) ;
bool mdate_IsEqual(const mdate* a, const mdate* b) ;
bool mdate_IsNotEqual(const mdate* a, const mdate* b) ;

int mdate_SameYearDateDifference(const mdate* a, const mdate* b) ;
int mdate_DateDifference(const mdate* a, const mdate* b) ;

bool mdate_SetDayOfWeek(mdate* date) ;

const char* mdate_GetMonthName(const mdate* date) ;
const char* mdate_GetDayName(const mdate* date) ;

bool mdate_SeedDateDifference(const mdate* dt, int* days) ;
void mdate_GetSeedDate(mdate* d1);
int localtime(struct tm* t, const time_t* time);

#endif
