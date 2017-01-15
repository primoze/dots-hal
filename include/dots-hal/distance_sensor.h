/*
 * Copyright 2017 Primoz Erjavec
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OS_HAL_DISTANCE_SENSOR_H_
#define OS_HAL_DISTANCE_SENSOR_H_


#include <dots-core/common.h>
#include <dots-core/pins.h>
#include <dots-core/util.h>
#include <dots-hal/pulse.h>


namespace os {
namespace hal {


template <class _trig_pin, class _echo_pin>
struct distance_sensor {

    static uint32_t get_distance() {
        // Short pulse first
        _trig_pin::set_mode(os::pin_mode::output);
        _trig_pin::set_state(false);
        os::util::delay_us(3);
        // At least 2 us pulse
        _trig_pin::set_state(true);
        os::util::delay_us(5);
        // End
        _trig_pin::set_state(false);

        uint32_t us = read_pulse<_echo_pin>(500000, true);
        return us_to_cm(us);
    }

private:
    static uint32_t us_to_cm(uint32_t us) {
        return us / 29 / 2;
    }
};


}
}


#endif // OS_HAL_DISTANCE_SENSOR_H_
