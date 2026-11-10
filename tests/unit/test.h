// Common include for unit tests: MFC first (like game code), then doctest
// with the Windows min/max macros hidden.
#ifndef IWD2RE_TEST_H_
#define IWD2RE_TEST_H_

#include "mfc.h"

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#include "doctest.h"
#pragma pop_macro("max")
#pragma pop_macro("min")

#endif /* IWD2RE_TEST_H_ */
