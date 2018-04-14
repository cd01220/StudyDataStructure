// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#include <stdio.h>
#include <tchar.h>
#include <assert.h>
#include <math.h>

#include <memory>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <bitset>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

template<class T>
inline int Compare(T const& left, T const& right)
{
    if (left == right)
        return 0;
    if (left < right)
        return -1;

    return 1;
}
