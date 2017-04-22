#include <lmic/lmic.h>
#include <hal/hal.h>
#include <string>

using namespace std;

// TTN AppEUI, little-endian format
static const u1_t PROGMEM APPEUI[8]={ 0x4A, 0x40, 0x00, 0xF0, 0x7E, 0xD5, 0xB3, 0x70 };

// TTN DeviceEUI, little-endian format
static const u1_t PROGMEM DEVEUI[8]={ 0x00, 0x04, 0xA7, 0x4E, 0x8A, 0xEB, 0x27, 0xB8 };

// TTN Appkey,  big-endian format
static const u1_t PROGMEM APPKEY[16] = { 0xB3, 0x73, 0xC0, 0x31, 0xA0, 0x69, 0xF0, 0x1E, 0x59, 0xB8, 0x60, 0xE4, 0x23, 0x45, 0x1F, 0xD4 };

// Dragino Raspberry PI hat (no onboard led)
// see https://github.com/dragino/Lora
#define RF_CS_PIN  RPI_V2_GPIO_P1_22 // Slave Select on GPIO25 so P1 connector pin #22
#define RF_IRQ_PIN RPI_V2_GPIO_P1_07 // IRQ on GPIO4 so P1 connector pin #7
#define RF_RST_PIN RPI_V2_GPIO_P1_11 // Reset on GPIO17 so P1 connector pin #11


#ifndef RF_LED_PIN
#define RF_LED_PIN NOT_A_PIN  
#endif

class Ataslora
{
        private:
		// 0; ok; 1; error
		int state = 0;
        public:
		void setState(int state);
		int getState();
		void setData(osjob_t* job, string message);
		int init();
};
