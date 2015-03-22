#include <stdio.h>

#include "include/mdate.h"
#include "include/mcal.h"

void display(mdate* date)
{
	printf("\nDate: %d-%d-%d\n", date->dayOfMonth, date->month, date->year) ;
}

void displayf(mdate* date)
{
	printf("\nDate: %d %s %s %d \n", date->dayOfMonth, mdate_GetDayName(date), mdate_GetMonthName(date), date->year) ;
}

void test_AddDays()
{
	mdate date ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 0) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 10) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 30) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 58) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 59) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 60) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 365) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 366) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 424) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddDays(&date, 425) ;
	display(&date) ;
}

void test_AddWeeks()
{
	mdate date ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddWeeks(&date, 0) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddWeeks(&date, 2) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddWeeks(&date, 4) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddWeeks(&date, 8) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddWeeks(&date, 9) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddWeeks(&date, 52) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddWeeks(&date, 53) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddWeeks(&date, 60) ;
	display(&date) ;
}

void test_AddMonths()
{
	mdate date ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddMonths(&date, 0) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddMonths(&date, 2) ;
	display(&date) ;

	mdate_Set(&date, 28, 1, 2008) ;
	mdate_AddMonths(&date, 1) ;
	display(&date) ;

	mdate_Set(&date, 29, 1, 2008) ;
	mdate_AddMonths(&date, 1) ;
	display(&date) ;

	mdate_Set(&date, 30, 1, 2008) ;
	mdate_AddMonths(&date, 1) ;
	display(&date) ;

	mdate_Set(&date, 29, 1, 2009) ;
	mdate_AddMonths(&date, 1) ;
	display(&date) ;

	mdate_Set(&date, 30, 1, 2009) ;
	mdate_AddMonths(&date, 1) ;
	display(&date) ;

	mdate_Set(&date, 28, 2, 2008) ;
	mdate_AddMonths(&date, 12) ;
	display(&date) ;

	mdate_Set(&date, 28, 2, 2007) ;
	mdate_AddMonths(&date, 12) ;
	display(&date) ;

	mdate_Set(&date, 29, 2, 2008) ;
	mdate_AddMonths(&date, 12) ;
	display(&date) ;

	mdate_Set(&date, 30, 4, 2007) ;
	mdate_AddMonths(&date, 1) ;
	display(&date) ;
}

void test_AddYears()
{
	mdate date ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddYears(&date, 0) ;
	display(&date) ;

	mdate_Set(&date, 1, 1, 2008) ;
	mdate_AddYears(&date, 10) ;
	display(&date) ;

	mdate_Set(&date, 28, 2, 2008) ;
	mdate_AddYears(&date, 1) ;
	display(&date) ;

	mdate_Set(&date, 29, 2, 2008) ;
	mdate_AddYears(&date, 1) ;
	display(&date) ;

	mdate_Set(&date, 29, 2, 2008) ;
	mdate_AddYears(&date, 2) ;
	display(&date) ;
}

void testCal()
{
	mdate d ;
	mdate_Set(&d, 1, 1, 2000) ;
	mdate_SetDayOfWeek(&d) ;
	displayf(&d) ;

	mdate_Set(&d, 14, 8, 1947) ;
	mdate_SetDayOfWeek(&d) ;
	displayf(&d) ;

	mdate_Set(&d, 14, 8, 1940) ;
	mdate_SetDayOfWeek(&d) ;
	displayf(&d) ;

	mdate_Set(&d, 15, 8, 1947) ;
	mdate_SetDayOfWeek(&d) ;
	displayf(&d) ;

	mdate_Set(&d, 28, 4, 1983) ;
	mdate_SetDayOfWeek(&d) ;
	displayf(&d) ;

	mdate_Set(&d, 28, 4, 2008) ;
	mdate_SetDayOfWeek(&d) ;
	displayf(&d) ;
}

int main()
{
		printf("\n Test Add Days\n") ;
		test_AddDays() ;
		printf("\n Test Add Weeks\n") ;
		test_AddWeeks() ;
		printf("\n Test Add Months\n") ;
		test_AddMonths() ;
		printf("\n Test Add Years\n") ;
		test_AddYears() ;

		printf("\n Test Calendar\n") ;
		testCal() ;

		mdate d ;
		int days ;
		mdate_Set(&d, 13, 5, 2008) ;
		mdate_SeedDateDifference(&d, &days) ;
		printf("\n Res = %d\n", days) ;
}

