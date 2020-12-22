#include <mdate.h>

static const mdate seedDate = { 15, 8, 1947, FRIDAY } ;
//static const mdate seedDate = { 31, 12, 1999, FRIDAY } ;

/* Day of Month is the only one which is 1 based index */

//No. of days in Months - Non Leap Year
static const int mdate_NoOfDaysInMonth_NLY[MONTHS_PER_YEAR_SIZE] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ;

//No. of days in Months - Leap Year
static const int mdate_NoOfDaysInMonth_LY[MONTHS_PER_YEAR_SIZE] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ;

static const char mdate_szMonths[MONTHS_PER_YEAR_SIZE][12] = { 
	"NA",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
} ;

static const char mdate_szDays[DAYS_PER_WEEK + 1][12] = {
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday",
	"NA"
} ;

boolean mdate_Set(mdate* date, int dayOfMonth, int month, int year)
{
	date->dayOfMonth = dayOfMonth ;
	date->month = month ;
	date->year = year ;

	return mdate_IsValid(date) ;
}

void mdate_Normalize(const mdate* src, mdate* dest)
{
	dest->dayOfMonth = src->dayOfMonth ;
	dest->month = src->month - 1 ;
	dest->year = src->year ;
}

int mdate_GetDaysInMonth(const mdate* date)
{
	if(IS_LEAP_YEAR(date->year))
		return mdate_NoOfDaysInMonth_LY[date->month] ;
	else
		return mdate_NoOfDaysInMonth_NLY[date->month] ;
}

int mdate_GetDaysInMonth_1(int month, int year)
{
	if(IS_LEAP_YEAR(year))
		return mdate_NoOfDaysInMonth_LY[month] ;
	else
		return mdate_NoOfDaysInMonth_NLY[month] ;
}

boolean mdate_IsValidMonth(int month)
{
	return (month >= JANUARY && month <= DECEMBER) ;
}

boolean mdate_IsValidYear(int year)
{
	return (year > 0 && year < 10000) ;
}

boolean mdate_IsValidDayOfMonth(const mdate* date)
{
	if(date->dayOfMonth < 1)
		return FALSE ;
		
	if(date->dayOfMonth > mdate_GetDaysInMonth(date))
		return FALSE ;

	return TRUE ;
}

boolean mdate_IsValidDayOfWeek(int dayOfWeek)
{
	return (dayOfWeek >= MONDAY && dayOfWeek <= SUNDAY) ;
}

boolean mdate_IsValid(const mdate* date)
{
	if(mdate_IsValidYear(date->year))
		if(mdate_IsValidMonth(date->month))
			if(mdate_IsValidDayOfMonth(date))
				return TRUE ;
	
	return FALSE ;
}

/* Date Add Functions */
boolean mdate_AddDays(mdate* date, int days)
{
	if(!mdate_IsValid(date))
		return FALSE ;

	if(days < 0)
		return FALSE ;

	if(days == 0)
		return TRUE ;

//	int dayOfWeek = (date->dayOfWeek + days) % DAYS_PER_WEEK ;
	int dayOfMonth = date->dayOfMonth ;
	int month = date->month ;
	int year = date->year ;

	for( ; days > 0; )
	{
		int daysInMonth = mdate_GetDaysInMonth_1(month, year) ;

		if( dayOfMonth + days > daysInMonth )
		{
			days -= ( daysInMonth - dayOfMonth ) ;

			dayOfMonth = 0 ;

			month++ ;
			if( month > DECEMBER )
			{
				month = JANUARY ;
				year++ ;
			}
		}
		else
		{
			dayOfMonth += days ;
			break ;
		}
	}

	date->dayOfMonth = dayOfMonth ;
	date->month = month ;
	date->year = year ;

	return TRUE ;
}

boolean mdate_AddWeeks(mdate* date, int weeks)
{
	int days = weeks * DAYS_PER_WEEK ;
	return mdate_AddDays(date, days) ;
}

boolean mdate_AddMonths(mdate* date, int months)
{
	if(!mdate_IsValid(date))
		return FALSE ;

	if(months < 0)
		return FALSE ;

	if(months == 0)
		return TRUE ;

	int dayOfMonth = date->dayOfMonth ;
	int month = date->month ;
	int year = date->year ;

	year = year + (month + months - 1) / MONTHS_PER_YEAR ;
	month = ((month + months - 1) % MONTHS_PER_YEAR) ;
	month += 1 ;

	int daysInMonth = mdate_GetDaysInMonth_1(month, year) ;
	if(dayOfMonth > daysInMonth)
		dayOfMonth = daysInMonth ;

	date->dayOfMonth = dayOfMonth ;
	date->month = month ;
	date->year = year ;

	return TRUE ;
}

boolean mdate_AddYears(mdate* date, int years)
{
	if(!mdate_IsValid(date))
		return FALSE ;

	if(years < 0)
		return FALSE ;

	if(years == 0)
		return TRUE ;
	
	int year = date->year + years ;

	if(date->month == FEBRUARY)
	{
		int daysInMonth = mdate_GetDaysInMonth_1(date->month, year) ;
		if(date->dayOfMonth > daysInMonth)
			date->dayOfMonth = daysInMonth ;		
	}

	date->year = year ;

	return TRUE ;
}
/* End of Date Add Functions */


/* Date Subtract Functions */
boolean mdate_SubtractDays(mdate* date, int days)
{
	if(!mdate_IsValid(date))
		return FALSE ;

	if(days < 0)
		return FALSE ;

	if(days == 0)
		return TRUE ;

//	int dayOfWeek = (date->dayOfWeek + days) % DAYS_PER_WEEK ;
	int dayOfMonth = date->dayOfMonth ;
	int month = date->month ;
	int year = date->year ;

	for( ; days > 0; )
	{

		if( days >= dayOfMonth )
		{
			days -= dayOfMonth ;

			month-- ;
			if( month < JANUARY )
			{
				month = DECEMBER ;
				year-- ;
			}

			dayOfMonth = mdate_GetDaysInMonth_1(month, year) ;
		}
		else
		{
			dayOfMonth -= days ;
			break ;
		}
	}

	date->dayOfMonth = dayOfMonth ;
	date->month = month ;
	date->year = year ;

	return TRUE ;
}

boolean mdate_SubtractWeeks(mdate* date, int weeks)
{
	int days = weeks * DAYS_PER_WEEK ;
	return mdate_SubtractDays(date, days) ;
}

boolean mdate_SubtractMonths(mdate* date, int months)
{
	if(!mdate_IsValid(date))
		return FALSE ;

	if(months < 0)
		return FALSE ;

	if(months == 0)
		return TRUE ;

	int dayOfMonth = date->dayOfMonth ;
	int month = date->month ;
	int year = date->year ;

	int norMonths = months % MONTHS_PER_YEAR ;

	month = 12 - norMonths + month ;
	if(month == 0)
		month = DECEMBER ;

	year = year - (months / MONTHS_PER_YEAR) ;
	if((month - norMonths) < 1)
		year-- ;

	int daysInMonth = mdate_GetDaysInMonth_1(month, year) ;
	if(dayOfMonth > daysInMonth)
		dayOfMonth = daysInMonth ;

	date->dayOfMonth = dayOfMonth ;
	date->month = month ;
	date->year = year ;

	return TRUE ;
}

boolean mdate_SubtractYears(mdate* date, int years)
{
	if(!mdate_IsValid(date))
		return FALSE ;

	if(years < 0)
		return FALSE ;

	if(years == 0)
		return TRUE ;
	
	int year = date->year - years ;

	if(year <= 0)
		return FALSE ;

	if(date->month == FEBRUARY)
	{
		int daysInMonth = mdate_GetDaysInMonth_1(date->month, year) ;
		if(date->dayOfMonth > daysInMonth)
			date->dayOfMonth = daysInMonth ;		
	}

	date->year = year ;

	return TRUE ;
}
/* End of Date Subtract Functions */

/* Logical Comparison on Dates */
boolean mdate_IsGreater(const mdate* a, const mdate* b)
{
	if(a->year > b->year)
		return TRUE ;
	else if(a->year < b->year)
		return FALSE ;
	else
	{
		if(a->month > b->month)
			return TRUE ;
		else if(a->month < b->month)
			return FALSE ;
		else
		{
			if(a->dayOfMonth > b->dayOfMonth)
				return TRUE ;
			return FALSE ;
		}
	}

	return FALSE ;
}

boolean mdate_IsLesser(const mdate* a, const mdate* b)
{
	if(a->year < b->year)
		return TRUE ;
	else if(a->year > b->year)
		return FALSE ;
	else
	{
		if(a->month < b->month)
			return TRUE ;
		else if(a->month > b->month)
			return FALSE ;
		else
		{
			if(a->dayOfMonth < b->dayOfMonth)
				return TRUE ;
			return FALSE ;
		}
	}

	return FALSE ;
}

boolean mdate_IsEqual(const mdate* a, const mdate* b)
{
	return (a->year == b->year) && (a->month == b->month) && (a->dayOfMonth == b->dayOfMonth) ;
}

boolean mdate_IsNotEqual(const mdate* a, const mdate* b)
{
	return (a->year != b->year) || (a->month != b->month) || (a->dayOfMonth != b->dayOfMonth) ;
}
/* End of Logical Comparison on Dates */

// A should be greater than B
int mdate_SameYearDateDifference(const mdate* a, const mdate* b)
{
	if(mdate_IsEqual(a, b))
		return 0 ;

	if(a->year != b->year)
		return -1 ; // error
	
	int res = (mdate_GetDaysInMonth(b) - b->dayOfMonth) ;
	
	int m ;
	for(m = b->month + 1; m != a->month; m++ )
	{
		res += mdate_GetDaysInMonth_1(m, b->year) ;
	}
	
	res += a->dayOfMonth ;
	return res ;
}

int mdate_DateDifference(const mdate* a, const mdate* b)
{
	if(mdate_IsEqual(a, b))
		return 0 ;
	
	const mdate* date1 = a ;
	const mdate* date2 = b ;

	int switchSign = 1 ;
	if(mdate_IsLesser(a, b))
	{
		switchSign = -1 ;
		date1 = b ;
		date2 = a ;
	}

	int res = 0 ;

	// date1 - date2
	
	if(date1->year == date2->year)
	{
		if(date1->month == date2->month)
		{
			res = date1->dayOfMonth - date2->dayOfMonth ;
		}
		else
		{
			res = mdate_SameYearDateDifference(date1, date2) ;
		}
	}
	else
	{
		int y ;

		for(y = date2->year + 1; y != date1->year; y++)
		{
			if(IS_LEAP_YEAR(y))
				res += 366 ;
			else
				res += 365 ;
		}

		mdate d ;
		
		mdate_Set(&d, 31, 12, date2->year) ;
		res += mdate_SameYearDateDifference(&d, date2) ;
		
		mdate_Set(&d, 1, 1, date1->year) ;
		res += mdate_SameYearDateDifference(date1, &d) ;
		res++ ;
	}

	return res * switchSign ;
}

boolean mdate_SetDayOfWeek(mdate* date)
{
	if(!mdate_IsValid(date))
		return FALSE ;

	if(mdate_IsEqual(date, &seedDate))
	{
		date->dayOfWeek = seedDate.dayOfWeek ;
		return TRUE ;
	}

	int days = mdate_DateDifference(date, &seedDate) ;
	int res ;
	
	if(days >= 0)
	{
		res = (seedDate.dayOfWeek + days) % DAYS_PER_WEEK ;
	}
	else
	{
		days *= -1 ;
		res = days % DAYS_PER_WEEK ;
		if(res <= seedDate.dayOfWeek)
			res = seedDate.dayOfWeek - res ;
		else
			res = DAYS_PER_WEEK - (res - seedDate.dayOfWeek) ;
	}

	date->dayOfWeek = res ;
	return TRUE ;
}

const char* mdate_GetMonthName(const mdate* date)
{
	if(date->month >= JANUARY && date->month <= DECEMBER)
		return mdate_szMonths[date->month] ;
	return mdate_szMonths[0] ;
}

const char* mdate_GetDayName(const mdate* date)
{
	if(date->dayOfWeek >= MONDAY && date->dayOfWeek <= SUNDAY)
		return mdate_szDays[date->dayOfWeek] ;
	return mdate_szDays[DAYS_PER_WEEK] ;
}

boolean mdate_SeedDateDifference(const mdate* dt, int* days)
{
	*days = 0 ;

	if(!mdate_IsValid(dt))
		return FALSE ;

	if(mdate_IsEqual(dt, &seedDate))
		return TRUE ;

	*days = mdate_DateDifference(dt, &seedDate) ;
	return TRUE ;
}
