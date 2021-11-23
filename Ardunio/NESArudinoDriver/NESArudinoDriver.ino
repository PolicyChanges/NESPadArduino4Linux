#include "Arduino.h"
#include <inttypes.h>

const byte strobe_pin = 3;
const byte clock_pin = 2;
const byte data_pin = 4;

static byte nes_controller_data;
#define TEST
#ifdef TEST
boolean button_state[8];
#endif
void setup()
{
#ifdef TEST
  button_state[0] = false;
  button_state[1] = false;
  button_state[2] = false;
  button_state[3] = false;
  button_state[4] = false;
  button_state[5] = false;
  button_state[6] = false;
  button_state[7] = false;
#endif
  pinMode(strobe_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.write(0x0);
}

byte strobe_buttons(void)
{
  byte ret = 0;
  byte i;
  latch();
  for (i = 0; i < 8; i++)
  {
    ret |= shiftin() << i;
  }
  return ~ret;
}

// Send 12 usecond high signal to latch/stobe pin
void latch(void)
{
  // Tell nes controller we're about to get button states
  digitalWrite(strobe_pin, HIGH);
  delayMicroseconds(12);
  digitalWrite(strobe_pin, LOW);
  // Wait 6 useconds -- doesn't work
  //delayMicroseconds(6);
}

// Send high pulse/clock to controller
byte shiftin(void)
{
  /* doesn't work
    digitalWrite(clock_pin, HIGH);
    delayMicroseconds(6);

    // sample data mid cycle?
    byte ret = digitalRead(data_pin);

    digitalWrite(clock_pin, LOW);
    delayMicroseconds(6);

  */
  // sample data mid cycle?
  byte ret = digitalRead(data_pin);

  delayMicroseconds(12);
  digitalWrite(clock_pin, HIGH);
  delayMicroseconds(12);
  digitalWrite(clock_pin, LOW);
  return ret;
}

#ifdef TEST

const char button_name[8] = {'A', 'B', 'E', 'S', 'U', 'D', 'L', 'R'};  //'U', 'D', 'L', 'R', 'S', 'E'};
const char button_depressed_name[8] = { '0', '1', '2', '3', '4', '5', '6', '7'};
byte previous_state = 0;



void test_keys(byte state) {

  byte buttons_pressed = ~previous_state & state;
  byte buttons_released = previous_state & ~state;
  
  for (byte i = 0; i < 8; i++) {
    if ((buttons_pressed >> i) & 0x1)
    {
      if ((state >> i) & 0x1)
        Serial.write(button_name[i]);
    }
    if ((buttons_released >> i) & 0x1)
    {
      if ((state >> i) == 0x0)
        Serial.write(button_depressed_name[i]);
    }
  }
  previous_state = state;

  
}
#endif

void loop()
{

  //https://web.archive.org/web/20160809054212/http://www.mit.edu/~tarvizo/nes-controller.html
  // 16666ms/2 - 204us = 8129 - http://www.mit.edu/~tarvizo/nes-controller.html
  //delayMicroseconds(8129);//;16462);//8129);//4064);//16666);
  //delayMicroseconds(1000000-deltaTime);   // do key test every 60hz
  //delayMicroseconds(16462);

  delay(12);

  byte buttons_pressed = strobe_buttons();

#ifdef TEST
  test_keys(buttons_pressed);
#else
  Serial.write(buttons_pressed);
#endif
}
