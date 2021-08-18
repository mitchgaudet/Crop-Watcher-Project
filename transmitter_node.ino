#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif
#include <LowPower.h>
#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;
#include "DHT.h"

#define DHTPIN 11
#define DHTTYPE DHT11

RH_ASK rf_driver(2000, 9, 5, 10); // Transmit on Pin 5

float hum;
float temp;

String str_hum;
String str_temp;
String str_dataout;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  rf_driver.init();
  Serial.begin(9600);
}


void loop()
{
    delay(2000);
    dht.begin();
    ss.begin(0x36);
    char str_cap[4];

    int hum = dht.readHumidity();
    temp = dht.readTemperature();
    uint16_t capread = ss.touchRead(0);

    str_hum = String(hum);
    str_temp = String(temp);
    sprintf(str_cap, "%u", capread);
    
    str_dataout = str_hum + "," + str_temp + "," + str_cap;

    static char *msg = str_dataout.c_str();

    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    
    for (int i = 0; i < 2; i++) {
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
            SPI_OFF, USART0_OFF, TWI_OFF);
    }
}
