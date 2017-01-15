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

#ifndef OS_HAL_PULSE_H_
#define OS_HAL_PULSE_H_


#include <dots-core/common.h>
#include <dots-hal/system_timer.h>

namespace os {
namespace hal {



OS_INLINE uint32_t get_pulse_width(pioreg_t input, byte_t bit, bool state, uint32_t max_loops) {
    uint32_t width = 0;
    while (os::get_bit(*input, bit) == state)
        if (--max_loops == 0)
            return 0;

    while (os::get_bit(*input, bit) != state)
        if (--max_loops == 0)
            return 0;

    while (os::get_bit(*input, bit) == state) {
        if (++width == max_loops)
            return 0;
    }
    return width;
}

template <class _pin>
uint32_t read_pulse(uint32_t timeout, bool state) {

    uint32_t max = os::hal::system_timer::us_to_clk(timeout) / 16;

    _pin::set_mode(os::pin_mode::input);
    uint32_t len = get_pulse_width(OS_PIOREG(_pin::pin), _pin::pin_bit, state, max);

    if (!len) {
        return 0;
    }

    return os::hal::system_timer::clk_to_us(len * 16 + 16);
}



}
}



#endif // OS_HAL_PULSE_H_
