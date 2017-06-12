#include "atasbutton.h"

void Atasbutton::init(){
	bcm2835_gpio_fsel(BUTTON_PIN, BCM2835_GPIO_FSEL_INPT);
    	//  with a pullup
    	bcm2835_gpio_set_pud(BUTTON_PIN, BCM2835_GPIO_PUD_UP);
        initialized = true;
}

bool Atasbutton::getState(){
        return enabled;
}
