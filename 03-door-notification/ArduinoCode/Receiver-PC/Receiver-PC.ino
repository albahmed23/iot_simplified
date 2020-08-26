#include <VirtualWire.h>

const int rec_pin = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  vw_set_rx_pin(rec_pin);
  //vw_set_ptt_inverted(true);
  vw_setup(50);   // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
  //pinMode(12,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //Serial.println(digitalRead(12));
  if (vw_get_message(buf, &buflen)) // Non-blocking
    { 
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      //Serial.println((char*)buf);
      if(strcmp((char*)buf,"0") == 0)
      {
        Serial.println("Someone is knocking your door!");
      } else if(strcmp((char*)buf,"1") == 0)
      {
        Serial.println("Someone just opened your door!");
      }
    }
}
