#ifndef COMMON_H_
#define COMMON_H_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"

// #include "okapi/api.hpp"
// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

#ifdef __cplusplus
    #include <iostream>
#endif

inline pros::Controller G_MAIN_CONTROLLER(pros::E_CONTROLLER_MASTER);
inline constexpr uint32_t G_MAIN_UPDATE_DELAY{20};

#endif