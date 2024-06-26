#pragma once

/*
 * WARN:
 * including this header does not make a lot of sense.
 * You should just #include all necessary headers from Windows SDK,
 * and then #include <src/util/system/win_undef.h> in order to undefine some common macros.
 */

#include <ydb-cpp-sdk/util/system/platform.h>

#if defined(_win_)
    #include <windows.h>
#endif

#include <ydb-cpp-sdk/util/system/win_undef.h>
