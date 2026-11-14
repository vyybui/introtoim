
#include "pitches.h"

int potpin = A0;
int buzzpin = 8;
int val;
int pitch = 0;
int buttons[5] = { 2, 3, 4, 5, 6 };
int octaves[3][5] = {
  {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5} , // 2: High
  {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4}, // 1: Middle
  {NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3} // 0: Low
};
// int oct_curr = octaves[pitch];

void setup() {
  pinMode(buzzpin, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
}

void loop() {
  val = analogRead(potpin);
  pitch = map(val, 0, 1023, 0, 3);
  if (pitch == 3) {
    pitch = 2;
  }

  bool pressed = false;

  for (int i = 0; i < 5; i++) {
    int btn = digitalRead(buttons[i]);

    if (btn == HIGH) {
      int sound = octaves[pitch][i];
      tone(buzzpin, sound);
      pressed = true;
      break;
    }
  }

  if (pressed == false) {
    noTone(buzzpin);
  }

  delay(15);
}
