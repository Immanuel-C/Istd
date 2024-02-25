#include "compiler.h"

bool istd_is_compiler_msvc() {
	#if defined(_MSC_VER)
	return true;
	#endif
	return false;
}

bool istd_is_compiler_clang() {
	#if defined(__clang__)
	return true;
	#endif
	return false;
}

bool istd_is_compiler_gcc() {
	#if defined(__MINGW32__) || defined(__GNUC__) 
	return true;
	#endif
	return false;
}

bool istd_is_compiler_intel() {
#if defined(__INTEL_COMPILER)
	return true;
#endif
	return false;
}

bool istd_is_compiler_ibm_llvm() {
	#if defined(__ibmxl__) && defined(__clang__)
	return true;
	#endif
	return false;
}

bool istd_is_compiler_ibm_legacy() {
	#if defined(__xlC__)
	return true;
	#endif
	return false;
}
