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

#include <dots-hal/system_timer.h>

#include <dots-core/util.h>

namespace os {
namespace hal {


volatile uint32_t system_timer::millis = 0;
volatile byte_t system_timer::fraction = 0;


void system_timer::init() {
    // Fast PWM
    os::set_bit(_MMIO_BYTE(_timer_type::tccra), _timer_type::wgm1);
    os::set_bit(_MMIO_BYTE(_timer_type::tccra), _timer_type::wgm0);

    // CLK/64
    os::set_bit(_MMIO_BYTE(_timer_type::tccrb), _timer_type::cs1);
    os::set_bit(_MMIO_BYTE(_timer_type::tccrb), _timer_type::cs0);

    // Enable interrupt
    os::set_bit(_MMIO_BYTE(_timer_type::timsk), _timer_type::toie);
}


void system_timer::tick() {
    uint32_t ms = millis;
    uint8_t frac = fraction;

    ms += ms_per_interrupt;
    ++frac;
    if(frac >= max_frac) {
        ++ms;
        frac -= max_frac;
    }

    millis = ms;
    fraction = frac;
}

uint32_t system_timer::get_millis() {
    return millis;
}

uint32_t system_timer::get_micros() {
    return millis * 1000 + fraction * frac_per_interrupt;
}


uint32_t system_timer::get_current_micros() {
    os::util::keep_interrupt_flag keep;
    uint32_t ms = millis;
    uint8_t ticks = _MMIO_BYTE(_timer_type::tcnt);

    if(os::get_bit(_MMIO_BYTE(_timer_type::tifr), _timer_type::tov) && (ticks < 255)) {
        ++ms;
    }

    return ((ms << 8) + ticks) * (prescaler_factor / clk_per_us);
}


ISR(TIMER0_OVF_vect) {
    system_timer::tick();
}


}
}


