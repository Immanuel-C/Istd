#pragma once

#include "../core.h"
#include <stdbool.h>

ISTD_EXTERN_C

/**
* The compiler is Microsoft Visual C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_msvc();
/**
* The compiler is clang C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_clang();
/**
* The compiler is gcc or mingw C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_gcc();
/**
* The compiler is intel C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_intel();
/**
* The compiler is ibm C/C++ compiler based on llvm.
*/
istd_api bool istd_stdcall istd_is_compiler_ibm_llvm();
/**
* The compiler is ibm legacy C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_ibm_legacy();

ISTD_END_EXTERN_C