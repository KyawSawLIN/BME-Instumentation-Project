#include "Mouse.h"
#include "Keyboard.h"

// set pin numbers for switch, joystick axes, and LED:
const int switchPin = 12;    // switch to turn on and off mouse control
const int mouseButton = 3;  // input pin for the mouse pushButton
const int deleteButton = 2;  // backspace button
const int special = 4;
const int xAxis = A0;       // joystick X axis
const int yAxis = A1;       // joystick Y axis
const int ledPin = 13;       // Mouse control LED

// parameters for reading the joystick:
int range = 3;             // output range of X or Y movement
int responseDelay = 2;      // response delay of the mouse, in ms
int threshold = range / 4;  // resting threshold
int center = range / 2;     // resting position value

bool mouseIsActive = false;  // whether or not to control the mouse
int lastSwitchState = LOW;   // previous switch state
char backspace = KEY_BACKSPACE;


void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);  // the switch pin
  pinMode(mouseButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // take control of the mouse:
  Mouse.begin();
  Keyboard.begin();

}

void loop() {
  int switchState = digitalRead(switchPin);
  if (switchState != lastSwitchState) {
    if (switchState == LOW) {
      mouseIsActive = !mouseIsActive;
      digitalWrite(ledPin, mouseIsActive);
    }
  }
  lastSwitchState = switchState;


  int xReading = readAxis(A0);
  int yReading = readAxis(A1);


  if (mouseIsActive) {
    Mouse.move(xReading, -yReading, 0);
  }

  if (digitalRead(mouseButton) == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  if (digitalRead(special) == LOW)
  {
    delay(500);
    Serial.println("a");
  }

  if (Serial.available())
  {
    char mesg = Serial.read();

     if (mesg == 'a')
     {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }

     }
}


  if ( digitalRead(deleteButton) == LOW)
  {
    delay(200);
    Keyboard.press(backspace);
    Keyboard.release(backspace);
    delay(10);
  }


  delay(responseDelay);
}

int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}