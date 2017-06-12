#include "atassound.h"

void Atassound::init(){
	bcm2835_gpio_fsel(PWM_PIN, BCM2835_GPIO_FSEL_ALT5);
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
	bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
	bcm2835_pwm_set_range(0,PWM_RANGE);
	initialized = true;
}

void Atassound::mute(){
	printf("atassound: mute\n");
        enabled = false;
	bcm2835_pwm_set_data(PWM_CHANNEL, 0);
}

void Atassound::enable(){
	printf("atassound: enable\n");
	if(initialized == false){ return; }
        enabled = true;
	bcm2835_pwm_set_data(PWM_CHANNEL, 512);
}

bool Atassound::getState(){
	return enabled;
}
