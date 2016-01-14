#include "pitches.h"

int melody[] = {
  NOTE_G4, NOTE_G4, NOTE_B4, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_D5
};

// note durations: 4 = quarter note, 8 = eighth note, etc...
int noteDurations[] = {
  8, 4, 4, 2, 8, 8, 8, 8, 8, 2
};

long distance;
long time;

void score() {
  for (int thisNote = 0; thisNote < 10; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDurationWin = 1000 / noteDurations[thisNote];
    tone(9, melody[thisNote], noteDurationWin);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDurationWin * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(9);
  }
}

void setup() {
  pinMode(7, OUTPUT); // ultrasonic pulse
  pinMode(6, INPUT); // ultrasonic rebound
}

void loop() {
  digitalWrite(7, LOW);
  delayMicroseconds(5);
  digitalWrite(7, HIGH); // send ultrasonic pulse
  delayMicroseconds(10);
  time = pulseIn(6, HIGH);
  distance = int(0.017 * time);
  if (distance < 5) {
    score();
  }
  delay(50);
}
