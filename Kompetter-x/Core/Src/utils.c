// utils.c
#include "utils.h"
#include <stdlib.h>

#define ALPHA_SMOOTHING 0.4

// Static variables are initialized to 0 by default in C
static int32_t encoderAccumulator = 0;
static int32_t smoothedAccumulator = 0;
static int32_t lastSmoothedAccumulator = 0;

