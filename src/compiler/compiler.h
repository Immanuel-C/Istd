#pragma once

#include "core.h"
#include <stdbool.h>

ISTD_EXTERN_C

/**
* The compiler is Microsoft Visual C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_msvc(void);
/**
* The compiler is clang C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_clang(void);
/**
* The compiler is gcc or mingw C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_gcc(void);
/**
* The compiler is intel C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_intel(void);
/**
* The compiler is ibm C/C++ compiler based on llvm.
*/
istd_api bool istd_stdcall istd_is_compiler_ibm_llvm(void);
/**
* The compiler is ibm legacy C/C++ compiler.
*/
istd_api bool istd_stdcall istd_is_compiler_ibm_legacy(void);

ISTD_END_EXTERN_C