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

#ifndef OS_HAL_SYSTEM_TIMER_H_
#define OS_HAL_SYSTEM_TIMER_H_


#include <dots-core/timer.h>



namespace os {
namespace hal {

struct system_timer : public os::timer::timer0_regs {
    typedef os::timer::timer0_regs _timer_type;

    static void init();
    static void tick();

    static uint32_t get_millis();
    static uint32_t get_micros();
    static uint32_t get_current_micros();

    static constexpr uint32_t prescaler_factor = 64;
    static constexpr uint32_t ticks_per_interrupt = 256;

    static constexpr uint32_t clk_per_us = F_CPU / 1000000l;

    static constexpr uint32_t clk_to_us(uint32_t cycles) {
        return cycles / clk_per_us;
    }

    static constexpr uint32_t us_to_clk(uint32_t us) {
        return us * clk_per_us;
    }

    static constexpr uint32_t us_per_interrupt = (prescaler_factor * ticks_per_interrupt) / clk_per_us;
    static constexpr uint32_t ms_per_interrupt = us_per_interrupt / 1000;
    static constexpr uint32_t frac_per_interrupt = us_per_interrupt % 1000;
    static constexpr byte_t max_frac = 1000 / frac_per_interrupt;

private:
    static volatile uint32_t millis;
    static volatile byte_t fraction;
};


}
}



#endif // OS_HAL_SYSTEM_TIMER_H_
