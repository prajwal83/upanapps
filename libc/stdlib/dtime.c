/*
 *  Mother Operating System - An x86 based Operating System
 *  Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
 *                                                                          
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *                                                                          
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *                                                                          
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/
 */
# include <dtime.h>
# include <mdate.h>

time_t time(time_t * t)
{
	time_t result;
	struct timeval tv;

	if (gettimeofday(&tv) ) //, (struct timezone *) NULL)) 
	{
		result = (time_t) - 1;
	}
   	else
   	{
		result = (time_t) tv.tSec;
	}

	if (t != NULL) 
	{
		*t = result;
	}
	return result;
}

int localtime(struct tm* t, const time_t* time)
{
	if(*time == NULL || t == NULL)
		return -1 ;

    mdate d1 ;
    mdate_GetSeedDate(&d1) ;

    int days = *time / (HRS_IN_DAY) ;
    mdate_AddDays(&d1, days) ;

    t->tm_mday = d1.dayOfMonth ;
    t->tm_mon = d1.month ;
    t->tm_year = d1.year - 1900;// % 100 ;

    int resi = *time % HRS_IN_DAY ;
    t->tm_hour = resi / 3600 ;

    int resh = resi % 3600 ;
    t->tm_min = resh / 60 ;
    t->tm_sec = resh % 60 ;

	return 0 ;
}

clock_t clock()
{
	//stub
	return 0 ;
}

