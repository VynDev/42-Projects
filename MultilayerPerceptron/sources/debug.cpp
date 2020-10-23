/*
* @Author: Vyn
* @Date:   2019-03-04 15:48:05
* @Last Modified by:   Vyn
* @Last Modified time: 2019-03-04 16:04:14
*/

#include <cstdio>
#include <cstdarg>

#include "functions.h"

static bool	isEnabled = false;

void	EnableDebug(bool newValue)
{
	isEnabled = newValue;
}

void	PrintDebug(const char *szFormat, ...)
{
	if (!isEnabled)
		return ;
	va_list args;
    va_start(args, szFormat);
    vprintf(szFormat, args);
    va_end(args);
}