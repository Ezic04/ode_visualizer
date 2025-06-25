#pragma once
#include <cassert>

#define assertm(exp, msg) assert((void(msg), exp))

using FloatType = float;
