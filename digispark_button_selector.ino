#include "DigiKeyboard.h"

//Pin 2 and Pin 0 appear to have the least amount of issues for button input
//Pin 1 is used for output to the led
//Pin 4 is largely usable as well, although for the first few seconds
//after plugging in, the LED can be seen to flash repeatedly before
//working as expected.
//Pin 5 will cause the USB to not even be recognized properly
//Pin 3 appears to be used for something else, as the LED will
//flash repeatedly indefinitely

const int buttonPin1 = 0;     // the number of the pushbutton pin to send the keystrokes
const int buttonPin2 = 2;     // the number of the pushbutton pin to toggle which keystrokes to send
const int ledPin =  1;      // the number of the LED pin

int sendkeys = 0;         // variable for reading the pushbutton status

int toggling = 0;
int toggle = 0;

void setup() {
  //You wanna send a blank keystroke upon startup, otherwise the computer will freak out after a few seconds and won't recognize the usb input
  //Sending a blank keystroke at startup gets the HID interfacing out of the way right off the bat and then you don't have to worry about it
  DigiKeyboard.sendKeyStroke(0);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
}

void loop() {
  
  // read the state of the pushbutton value:
  sendkeys = digitalRead(buttonPin1);
  toggling = digitalRead(buttonPin2);

  if (toggling == HIGH){
    toggle++;
    //Wait a little bit so it doesn't increment more than once per button push
    delay(200);
  }

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (sendkeys == HIGH){
    digitalWrite(ledPin, HIGH);

    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.delay(500);

    DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
    DigiKeyboard.delay(500);

    DigiKeyboard.print("chrome");
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(3000);
    switch (toggle) {
      //Never Gonna Give You Up
      case 0:
        DigiKeyboard.print("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
        DigiKeyboard.sendKeyStroke(KEY_ENTER);
        break;
      //Take Me Home, Country Roads
      case 1:
        DigiKeyboard.print("https://www.youtube.com/watch?v=1vrEljMfXYo");
        DigiKeyboard.sendKeyStroke(KEY_ENTER);
        break;
      //Crab Rave
      case 2:
        DigiKeyboard.print("https://www.youtube.com/watch?v=LDU_Txk06tM");
        DigiKeyboard.sendKeyStroke(KEY_ENTER);
        break;
      //Runnin in the 90s
      default:
        DigiKeyboard.print("https://www.youtube.com/watch?v=BJ0xBCwkg3E");
        DigiKeyboard.sendKeyStroke(KEY_ENTER);
        break;
    }
    toggle = 0;
    sendkeys = 0;
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
