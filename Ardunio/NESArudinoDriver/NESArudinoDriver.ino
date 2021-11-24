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


#define NES_A       B00000001
#define NES_B       B00000010
#define NES_SELECT  B00000100
#define NES_START   B00001000
#define NES_UP      B00010000
#define NES_DOWN    B00100000
#define NES_LEFT    B01000000
#define NES_RIGHT   B10000000

  /* A button gets marked as true as soon as it is pressed. That way
  we know to not "press" it again */
  boolean a = false;; //A Button
  boolean b = false;; //B Button
  boolean u = false;; //Up Button
  boolean d = false;; //Down Button
  boolean l = false;; //Left Button
  boolean r = false;; //Right Button
  boolean s = false;; //Start Button
  boolean e = false;; //Select Button
int keysReleased[8];
boolean isReleased = false;

void test_keys(byte state) {
  
/*  genius
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
*/

      // A
    if (state & NES_A){
      if(!a){
        a = true; //Make sure the button is only pressed once
        Serial.println('A'); //Print the button to be picked up by our robot
      }
    }
    //Key might have been released so we check and if so change the
    //value in our released array
    else if (a == true){
      a = false;
      keysReleased[0] = 1;
      isReleased = true;
    }
    
    // B
    if (state & NES_B){
      if(!b){
        b = true; //Make sure the button is only pressed once
        Serial.println('B'); //Print the button to be picked up by our robot
      }
    }
    //Key might have been released so we check and if so change the
    //value in our released array
    else if (b == true){
      b = false;
      keysReleased[1] = 1;
      isReleased = true;
    }
    
    // Up
    if (state & NES_UP){
      if(!u){
        u = true; //Make sure the button is only pressed once
        Serial.println('U'); //Print the button to be picked up by our robot
      }
    }
    //Key might have been released so we check and if so change the
    //value in our released array
    else if (u == true){
      u = false;
      keysReleased[2] = 1;
      isReleased = true;
    }
    
    // Down
    if (state & NES_DOWN){
      if(!d){
        d = true; //Make sure the button is only pressed once
        Serial.println('D'); //Print the button to be picked up by our robot
      }
    }
    //Key might have been released so we check and if so change the
    //value in our released array
    else if (d == true){
      d = false;
      keysReleased[3] = 1;
      isReleased = true;
    }
    
    // Left
    if (state & NES_LEFT){
      if(!l){
        l = true; //Make sure the button is only pressed once
        Serial.println('L'); //Print the button to be picked up by our robot
      }
    }
    //Key might have been released so we check and if so change the
    //value in our released array
    else if (l == true){
      l = false;
      keysReleased[4] = 1;
      isReleased = true;
    }
    
    //Right
    if (state & NES_RIGHT){
      if(!r){
        r = true; //Make sure the button is only pressed once
        Serial.println('R'); //Print the button to be picked up by our robot
      }
    }
    //Key might have been released so we check and if so change the
    //value in our released array
    else if (r == true){
      r = false;
      keysReleased[5] = 1;
      isReleased = true;
    }
    
    //Start
    if (state & NES_START){
    if(!s){
      s = true; //Make sure the button is only pressed once
      Serial.println('S'); //Print the button to be picked up by our robot
      }
    }
    //Key might have been released so we check and if so change the
    //value in our released array
    else if (s == true){
      s = false;
      keysReleased[6] = 1;
      isReleased = true;
    }

    //Select
    if (state & NES_SELECT){
      if(!e){
        e = true; //Make sure the button is only pressed once
        Serial.println('E'); //Print the button to be picked up by our robot
      }
    }
    //Key might have been released so we check and if so change the
    //value in our released array
    else if (e == true){
      e = false;
      keysReleased[7] = 1;
      isReleased = true;
    }
    /* If a key has been released then our java robot needs to know about it. So what we
    are going to do is to iterate over our array if a key has been released and print out the
    position in the array of that key. So for example if "Up" has been released we will
    see that our array looks like this [0,0,1,0, 0,0,0,0]. So then we will print 2 to the java robot
    so it knows that "Up" has been released. Likewise we would print 7 for the start button on release. */
    if(isReleased){
      isReleased = false; //Reset the boolean
      for(int i=0; i < 8; i++){
        if(keysReleased[i] == 1){
          keysReleased[i] = 0; //Reset the button listener
          Serial.println(i);
        }
      }
    }
}
#endif

void loop()
{

  //https://web.archive.org/web/20160809054212/http://www.mit.edu/~tarvizo/nes-controller.html
  // 16666ms/2 - 204us = 8129 - http://www.mit.edu/~tarvizo/nes-controller.html
  //delayMicroseconds(8129);//;16462);//8129);//4064);//16666);
  //delayMicroseconds(1000000-deltaTime);   // do key test every 60hz
  //delayMicroseconds(16462);

  delay(16);

  byte buttons_pressed = strobe_buttons();

#ifdef TEST
  test_keys(buttons_pressed);
#else
  Serial.write(buttons_pressed);
#endif
}
