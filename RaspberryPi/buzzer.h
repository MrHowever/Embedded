//
// Created by mrhowever on 19.03.2020.
//

#ifndef RASPBERRYPI_BUZZER_H
#define RASPBERRYPI_BUZZER_H

#define EXPANDER_CHANNEL 15

void buzzer_on();
void buzzer_on_for(u_int32_t);
void buzzer_off();
void buzzer_off_for(u_int32_t);

#endif //RASPBERRYPI_BUZZER_H
