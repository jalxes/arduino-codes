#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define MIN 400
#define MAX 690
#define B_YELLOW 3    // the pin that the pushbutton is attached to
#define L_YELLOW 2       // the pin that the LED is attached to
#define B_ORANGE 6
#define L_ORANGE 5
#define B_GREEN 9
#define L_GREEN 8
#define B_BLUE 12
#define L_BLUE 11

int lastYellowButton =LOW;
bool yellow = false;         // current state of the button

int lastOrangeButton = LOW;
int lastGreenButton = LOW;
int lastBlueButton = LOW;
bool orange = false;
bool green = false;
bool blue = false;

int lastPedal;

void setup() {
  // initialize the button pin as a input:
  pinMode(B_YELLOW, INPUT);
  // initialize the LED as an output:
  pinMode(L_YELLOW, OUTPUT);

  //start serial connection
  MIDI.begin(4);              // Launch MIDI with default options
  Serial.begin(115200);
}


// the loop routine runs over and over again forever:
void loop() {
  lastYellowButton = commandLed(B_YELLOW, lastYellowButton, L_YELLOW, &yellow);
lastOrangeButton = commandLed(B_ORANGE, lastOrangeButton, L_ORANGE, &orange);
lastGreenButton = commandLed(B_GREEN, lastGreenButton, L_GREEN, &green);
lastBlueButton = commandLed(B_BLUE, lastBlueButton, L_BLUE, &blue);
  
  /*
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  if (lastPedal != sensorValue) {
    int midiValue = 0;
    if (sensorValue < MIN) {
      sensorValue = MIN;
    }
    if (sensorValue > MAX) {
      sensorValue = MAX;
    }
    sensorValue = sensorValue - MIN;

    // print out the value you read:
    midiValue = (sensorValue * 127) / (MAX - MIN);
    if (midiValue < 0) {
      midiValue = 0;
    }
    if (midiValue > 127) {
      midiValue = 127;
    }
     MIDI.sendControlChange(1, midiValue, 1);
  }
  
  lastPedal = sensorValue;
  */
  delay(1);        // delay in between reads for stability
}
int commandLed(int buttonPin, int lastButton, int ledPin, bool *led) {
  int button = digitalRead(buttonPin);
  if (button != lastButton & lastButton == LOW) {
    *led = !*led;
    digitalWrite(ledPin, *led ? HIGH : LOW);
    MIDI.sendControlChange(buttonPin, *led ? 127 : 0, 1);
  }
  return button;
}
