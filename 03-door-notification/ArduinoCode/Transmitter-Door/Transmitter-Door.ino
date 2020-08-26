
// Includes needed
#include <VirtualWire.h>

// Pin Allocations
const int transmit_pin = 1;
const int hallsen_pin = 2;
const int piezo_pin = 2;
const int led_pin = 0;

// Package Messages
const char *knock_msg = "0";
const char *open_msg = "1";


// the setup routine runs once when you press reset:
void setup() {                
  // initialize IO and transmitter
  vw_set_tx_pin(transmit_pin);
  vw_set_ptt_inverted(true);
  vw_setup(50); // Bits per sec

  // IO
  pinMode(led_pin,OUTPUT);
  pinMode(hallsen_pin,INPUT);

}

// the loop routine runs over and over again forever:
void loop() {

  // Check piezo for any vibrations
  if(analogRead(piezo_pin) > 10)
  { 
    digitalWrite(led_pin,HIGH); // Indicate we are sending something
    vw_send((uint8_t *)knock_msg,sizeof(knock_msg));
    vw_wait_tx();
    digitalWrite(led_pin,LOW);
    delay(1000);
  }else if(digitalRead(hallsen_pin) == HIGH)
  {
    digitalWrite(led_pin,HIGH); // Indicate we are sending something
    vw_send((uint8_t *)open_msg,sizeof(open_msg));
    vw_wait_tx();
    digitalWrite(led_pin,LOW);
    delay(1000);
  }
  
}
