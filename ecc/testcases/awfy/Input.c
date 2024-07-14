/*
* Copyright 2021 Rochus Keller <mailto:me@rochus-keller.ch>
*
* This file is part of the Oberon+ parser/compiler library.
*
* The following is the license that applies to this copy of the
* file. For a license to use the file under conditions
* other than those described here, please email to me@rochus-keller.ch.
*
* This file may be used under the terms of the GNU Lesser
* General Public License version 2.1 or version 3 as published by the Free
* Software Foundation and appearing in the file LICENSE.LGPLv21 and
* LICENSE.LGPLv3 included in the packaging of this file. Please review the
* following information to ensure the GNU Lesser General Public License
* requirements will be met: https://www.gnu.org/licenses/lgpl.html and
* http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*
* Alternatively this file may be used under the terms of the Mozilla 
* Public License. If a copy of the MPL was not distributed with this
* file, You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#include "Input.h"
#include "XYplane.h"
#include <time.h>

#if defined(_WIN32) && !defined(__GNUC__)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Source: https://stackoverflow.com/questions/10905892/equivalent-of-gettimeday-for-windows/26085827

// MSVC defines this in winsock2.h!?
typedef struct timeval {
    long tv_sec;
    long tv_usec;
} timeval;

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}
#else
#include <time.h>
#endif

static struct timespec start;

int32_t Input$Time()
{
#ifndef __ECS_C__
    static struct timeval now;
    gettimeofday(&now, 0);
    const long seconds = now.tv_sec - start.tv_sec;
    const long microseconds = now.tv_usec - start.tv_usec;
    return seconds*1000000 + microseconds;
#else
    struct timespec now;
    timespec_get(&now,0);
    const long seconds = now.tv_sec - start.tv_sec;
    const long nanoseconds = now.tv_nsec - start.tv_nsec;
    return seconds*1000000 + nanoseconds / 1000;
#endif
}

int Input$Available()
{
	return XYplane$Available();
}

void Input$Read(char* ch)
{
	*ch = XYplane$Dequeue();
}

static int _w = 0, _h = 0;

void Input$SetMouseLimits(int32_t w, int32_t h)
{
	_w = w;
	_h = h;
}

void Input$Mouse( int32_t* keys, int32_t* x, int32_t* y)
{
	XYplane$GetMouseState(keys, x, y);
	if( *x < 0 )
		*x = 0;
	else if( _w != 0 && *x > _w )
		*x = _w;
	if( *y < 0 )
		*y = 0;
	else if( _h != 0 && *y > _h )
		*y = _h;
}

void Input$init$()
{
#ifndef __ECS_C__
    gettimeofday(&start, 0);
#else
    timespec_get(&start,0);
#endif
}

OBX$Cmd Input$cmd$(const char* name)
{
	if( name == 0 ) return Input$init$;
	return 0;
}
