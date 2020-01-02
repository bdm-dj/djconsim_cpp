#pragma once

namespace DJCon
{

struct SensorInfo {
    signed turntable_speed_left : 32;
    signed turntable_speed_right : 32;
    bool sampler_0 : 1;
    bool sampler_1 : 1;
    bool sampler_2 : 1;
    bool sampler_3 : 1;
    bool sampler_4 : 1;
    bool sampler_5 : 1;
    bool sampler_6 : 1;
    bool sampler_7 : 1;
    bool sampler_8 : 1;
    bool sampler_9 : 1;
    unsigned : 0;  // padding
    unsigned slide_left_0 : 16;
    unsigned slide_left_1 : 16;
    unsigned slide_left_2 : 16;
    unsigned slide_right_2 : 16;
    unsigned slide_right_2 : 16;
    unsigned slide_right_2 : 16;
    unsigned slide_center : 16;
    unsigned potentiometer_left_0 : 16;
    unsigned potentiometer_left_1 : 16;
    unsigned potentiometer_left_2 : 16;
    unsigned potentiometer_right_0 : 16;
    unsigned potentiometer_right_1 : 16;
    unsigned potentiometer_right_2 : 16;
};

}  // namespace DJCon
