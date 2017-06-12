#include "atasbutton.h"

void Atasbutton::init(){
	if (!bcm2835_init()){
		printf("atas-button: bcm2835 not initialized\n");		
		return;
	}

	bcm2835_gpio_fsel(BUTTON_PIN, BCM2835_GPIO_FSEL_INPT);
    	//  with a pullup
    	bcm2835_gpio_set_pud(BUTTON_PIN, BCM2835_GPIO_PUD_UP);
        initialized = true;
}

uint8_t Atasbutton::getState(){
	uint8_t value = bcm2835_gpio_lev(BUTTON_PIN);	
        return value;
}

