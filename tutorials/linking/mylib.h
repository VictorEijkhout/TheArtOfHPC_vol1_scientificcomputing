#pragma once

#ifdef _WIN32
    #ifdef BUILD_MYLIB
        #define EXPORT_SYMBOL __declspec(dllexport)
    #else
        #define EXPORT_SYMBOL __declspec(dllimport)
    #endif
#else
    #define EXPORT_SYMBOL
#endif


#ifdef __cplusplus
extern "C" {
#endif

EXPORT_SYMBOL void test_empty(void);
EXPORT_SYMBOL float test_add(float x, float y);
EXPORT_SYMBOL void test_passing_array(int *data, int len);

#undef EXPORT_SYMBOL
#ifdef __cplusplus
}
#endif
