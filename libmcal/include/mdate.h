#ifndef _LIB_MDATE_H_
#define _LIB_MDATE_H_

//#include <ctype.h>
#include "../../libc/include/ctype.h"

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

boolean mdate_Set(mdate* date, int dayOfMonth, int month, int year) ;
void mdate_Normalize(const mdate* src, mdate* dest) ;
int mdate_GetDaysInMonth(const mdate* date) ;
int mdate_GetDaysInMonth_1(int month, int year) ;
boolean mdate_IsValidDayOfWeek(int dayOfWeek) ;
boolean mdate_IsValidDayOfMonth(const mdate* date) ;
boolean mdate_IsValidMonth(int month) ;
boolean mdate_IsValidYear(int year) ;
boolean mdate_IsValid(const mdate* date) ;

boolean mdate_AddDays(mdate* date, int days) ;
boolean mdate_AddWeeks(mdate* date, int days) ;
boolean mdate_AddMonths(mdate* date, int months) ;
boolean mdate_AddYears(mdate* date, int years) ;

boolean mdate_SubtractDays(mdate* date, int days) ;
boolean mdate_SubtractWeeks(mdate* date, int days) ;
boolean mdate_SubtractMonths(mdate* date, int months) ;
boolean mdate_SubtractYears(mdate* date, int years) ;

boolean mdate_IsGreater(const mdate* a, const mdate* b) ;
boolean mdate_IsLesser(const mdate* a, const mdate* b) ;
boolean mdate_IsEqual(const mdate* a, const mdate* b) ;
boolean mdate_IsNotEqual(const mdate* a, const mdate* b) ;

int mdate_SameYearDateDifference(const mdate* a, const mdate* b) ;
int mdate_DateDifference(const mdate* a, const mdate* b) ;

boolean mdate_SetDayOfWeek(mdate* date) ;

const char* mdate_GetMonthName(const mdate* date) ;
const char* mdate_GetDayName(const mdate* date) ;

boolean mdate_SeedDateDifference(const mdate* dt, int* days) ;
#endif
