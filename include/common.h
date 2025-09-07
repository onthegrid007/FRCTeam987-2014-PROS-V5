#ifndef COMMON_H_
#define COMMON_H_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
// #include <liblvgl\lvgl.h>

// #include "okapi/api.hpp"
// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

#ifdef __cplusplus
    #include <iostream>
#endif

#include "../vendor/stb/stb_image.h"

inline lv_image_dsc_t* load_png_from_array(const unsigned char* data, size_t length) {
    int width, height, channels;
    unsigned char* decoded{stbi_load_from_memory(data, length, &width, &height, &channels, 4)};
    if (!decoded) {
        std::cout << "Failed to decode image from array" << std::endl;
        return nullptr;
    }
    lv_image_dsc_t* img_dsc{new lv_image_dsc_t};
    img_dsc->header.w = width;
    img_dsc->header.h = height;
    img_dsc->header.cf = LV_COLOR_FORMAT_ARGB8888;
    img_dsc->data_size = width * height * 4;
    img_dsc->data = decoded;
    return img_dsc;
}

inline bool G_ESTOP{false};
inline bool G_IS_ROBOT_ENABLED{false};
inline pros::Controller G_MAIN_CONTROLLER(pros::E_CONTROLLER_MASTER);
inline constexpr uint32_t G_MAIN_UPDATE_DELAY{20};
inline constexpr uint32_t G_DT_DEADBAND{1};

inline pros::adi::Motor G_LEFT_DT_FRONT('a'); // DRIVETRAIN 4
inline pros::adi::Motor G_LEFT_DT_BACK('e'); // DRIVETRAIN 3
inline pros::adi::Motor G_RIGHT_DT_FRONT('b'); // DRIVETRAIN 1
inline pros::adi::Motor G_RIGHT_DT_BACK('f'); // DRIVETRAIN 2

inline pros::adi::Motor G_INTAKE_MOTOR('d');
inline pros::adi::Motor G_STEPH_1('g');
inline pros::adi::Motor G_STEPH_2('c');

inline pros::Motor G_FINGER_PNU(5);
inline pros::Motor G_INTAKE_PNU(6);
inline pros::Motor G_WHEELY_BAR_PNU(7);

template<typename T0, typename T1, typename T2, typename T3, typename T4>
inline double mapval(T0 value, T1 minIn, T2 maxIn, T3 minOut, T4 maxOut ) { return (((double)value - (double)minIn) / ((double)maxIn - (double)minIn)) * ((double)maxOut - (double)minOut) + (double)minOut; }

#endif