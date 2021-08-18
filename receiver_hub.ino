#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif 

RH_ASK rf_driver(2000, 5, 9, 10); // Receive from Pin 5

String str_hum;
String str_temp;
String str_cap;
String str_dataout;

void setup()
{
  rf_driver.init();
  Serial.begin(9600);
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    
    if (rf_driver.recv(buf, &buflen))
    {
      str_dataout = String((char*)buf);
      
      //for (int i = 0; i < str_dataout.length(); i++) {
      //if (str_dataout.substring(i, i+1) == ",") {
      //str_hum = str_dataout.substring(0, i);
      //str_temp = str_dataout.substring(i+1);
      //str_cap = str_dataout.substring(i+1);
      //break;
      Serial.println(str_dataout);
      //Serial.print(output);
      str_dataout = "";
      }
  
}
