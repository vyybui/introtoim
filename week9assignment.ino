//the red & yellow LEDs are connected to digital pins ~9 and ~10 respectively
int red = 9;
int yellow = 10;

int buttonPin = A0;
int sensorPin = A2;
int brightness = 0;

//default is 1 which is not yet clicked when the program just got started
int prevButtonState = 1;

//I want to start with red, so yLed default is false. when the light switches to yellow, yLed will be changed to true
bool yLed = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //the leds are the output
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  //a0 is the input (click)
  pinMode(buttonPin,INPUT);

}

void loop() {
  //read the data from the photocell and constrain & map it to a value between 0 and 255 for the LED, this is the brightness
  int sensorValue = analogRead(sensorPin);
  sensorValue = constrain(sensorValue,20,850);
  brightness = map(sensorValue,850,20,0,255);

  //if buttonState is 0 that means it's pressed
  int buttonState = digitalRead(buttonPin);
  //change color when button is JUST pressed, if buttonState is going from 1 (HIGH) to 0 (LOW)
  //this avoids the flickering of the lights when button is hold
  if (prevButtonState == 1 && buttonState == 0) {
    //changes the status of yLed (whether yellow is in use)
    //if it is currently true, change it to false (so now red is in used)
    //vice versa: if it is false (yellow not used, red is used), change it to true (yellow is used)
    yLed= !yLed;
  }

  //update previous button state
  prevButtonState = buttonState;

  if (yLed) {
    //yellow light on, red off
    analogWrite(red, 0);
    analogWrite(yellow, brightness);
  } else {
    //yellow off, red on
    analogWrite(red, brightness);
    analogWrite(yellow, 0);
  }
  Serial.println(sensorValue);
  delay(30);
  
}
