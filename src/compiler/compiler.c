#include "compiler.h"

bool istd_is_compiler_msvc(void) {
	#if defined(_MSC_VER)
	return true;
	#else
	return false;
	#endif
}

bool istd_is_compiler_clang(void) {
	#if defined(__clang__)
	return true;
	#else
	return false;
	#endif
}

bool istd_is_compiler_gcc(void) {
	#if defined(__MINGW32__) || defined(__GNUC__) 
	return true;
	#else
	return false;
	#endif
}

bool istd_is_compiler_intel(void) {
#if defined(__INTEL_COMPILER)
	return true;
	#else
	return false;
#endif
}

bool istd_is_compiler_ibm_llvm(void) {
	#if defined(__ibmxl__) && defined(__clang__)
	return true;
	#else
	return false;
	#endif
}

bool istd_is_compiler_ibm_legacy(void) {
	#if defined(__xlC__)
	return true;
	#else
	return false;
	#endif
}
