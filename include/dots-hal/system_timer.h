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

struct system_timer : public os::timer::timer0 {
    typedef os::timer::timer0 _timer_type;

    static void init();
    static void tick();

    static uint32_t get_millis();
    static uint32_t get_micros();
    static uint32_t get_current_micros();

private:
    static volatile uint32_t millis;
    static volatile byte_t fraction;
};


}
}



#endif // OS_HAL_SYSTEM_TIMER_H_
