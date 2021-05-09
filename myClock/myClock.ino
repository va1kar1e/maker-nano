//
// Siwanont Sittinam
// Alarm Clock
//

// Prothread
#include "pt.h"

// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Time
#include "DS1302.h"
// pin 9-11
// DS1302 rtc([CE/RST], [I/O], [CLOCK]);
DS1302 rtc(11, 10, 9);
Time t;

// Temp&Humidity
#include <DHT.h>
DHT dht(3, DHT11);

// Melody
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

const int harryMelody[] = {

  // Hedwig's theme fromn the Harry Potter Movies
  // Socre from https://musescore.com/user/3811306/scores/4906610
  
  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1, 
  NOTE_D4, 4,

  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_B4, 4,
  NOTE_G4, -1,
  NOTE_AS4, 4,
     
  NOTE_D5, 2, NOTE_AS4, 4,//18
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_DS5, 2, NOTE_D5, 4,
  NOTE_CS5, 2, NOTE_A4, 4,
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_D4, 4,
  NOTE_D5, -1, 
  REST,4, NOTE_AS4,4,  

  NOTE_D5, 2, NOTE_AS4, 4,//26
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_AS4, 4,
  NOTE_G4, -1, 
  
};

const int harryMelodyLen = 62;
const int harryMelodyTempo = 144;

const int nokiaMelody[] = {

  // Nokia Ringtone 
  // Score available at https://musescore.com/user/29944637/scores/5266155
  
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
};

const int nokiaMelodyLen = 13;
const int nokiaMelodyTempo = 180;

const int starwarMelody[] = {
  
  // Dart Vader theme (Imperial March) - Star wars 
  // Score available at https://musescore.com/user/202909/scores/1141521
  // The tenor saxophone part was used
  
  NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,//1
  NOTE_F5,2, NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
  NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,8, NOTE_C5,8, NOTE_C5,8,
  NOTE_F5,2, NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
  
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, //8  
  NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,-8, NOTE_C5,16, 
  NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C5,-8, NOTE_C5,16,
  NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  
  NOTE_C6,-8, NOTE_G5,16, NOTE_G5,2, REST,8, NOTE_C5,8,//13
  NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C6,-8, NOTE_C6,16,
  NOTE_F6,4, NOTE_DS6,8, NOTE_CS6,4, NOTE_C6,8, NOTE_AS5,4, NOTE_GS5,8, NOTE_G5,4, NOTE_F5,8,
  NOTE_C6,1
  
};

const int starwarMelodyLen = 88;
const int starwarMelodyTempo = 108;

// change this to whichever pin you want to use
const int buzzer = 8;
const int led[] = {4,5,6,7};

const int button = 2;

bool showDisplay = true;
int displayStatus = 0;

void playMelody(int melody[], int notes, int tempo) {
  // tempo : change this to make the song slower or faster

  
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  // int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  
  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  } 
}

void initScreen() {
  // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.begin(16,2);     
  lcd.display();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, Va1kar1e!");
  lcd.setCursor(0,1);
  lcd.print("My Clock");
//  lcd.scrollDisplayLeft();
  delay(2000);
}

void initClock() {
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // The following lines can be commented out to use the values already stored in the DS1302
  // Upload in 18:10:52 
//  rtc.setDOW(SUNDAY);      // Set Day-of-Week to WEDNESDAY
//  rtc.setTime(18, 11, 0);     // Set the time to 17:30:00 (24hr format)
//  rtc.setDate(9, 5, 2021);   // Set the date to May 9th, 2021
  
}

void checkDisplay() {
  if (displayStatus == 1) {
    lcd.display();
    lcd.backlight();
    digitalWrite(led[3], LOW);
  } else if (displayStatus == 2) {
    lcd.display();
    lcd.noBacklight();
    digitalWrite(led[3], LOW);
  } else {
    lcd.noDisplay();
    lcd.noBacklight();
    digitalWrite(led[3], HIGH);
  }  
}

void alarm() {
    displayStatus = true;
    digitalWrite(led[0], HIGH);
    playMelody(nokiaMelody, nokiaMelodyLen, nokiaMelodyTempo);
    delay(1000);
    digitalWrite(led[1], HIGH);
    playMelody(harryMelody, harryMelodyLen, harryMelodyTempo);
    delay(1000);
    digitalWrite(led[1], HIGH);
    playMelody(starwarMelody, starwarMelodyLen, starwarMelodyTempo);
    delay(250);
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
}

static struct pt pt1, pt2, pt3, pt4;

static int checkAlarm(struct pt *pt) {
  t = rtc.getTime();
  PT_BEGIN(pt);
  while(1) {
    PT_WAIT_UNTIL(pt, (t.hour == 8 && (t.min >= 30 || t.min % 5 == 0)) || (t.hour >= 9 && t.hour <= 22 && t.min == 0));
    alarm();
  }
  PT_END(pt);
}

static int displaySwitch(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    PT_WAIT_UNTIL(pt, digitalRead(button) == HIGH);
    checkDisplay();
    PT_WAIT_UNTIL(pt, digitalRead(button) == LOW);
    if (displayStatus < 3) {
      displayStatus += 1;
    } else {
      displayStatus = 0;
    }
  }
  PT_END(pt);
}

static int printDateAndTime(struct pt *pt) {
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while(1) {
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 1000);
    lcd.setCursor(0,0);
    lcd.print("Date: ");
    lcd.print(rtc.getDateStr());
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 1000);
    lcd.setCursor(0,0);
    lcd.print("Time: ");
    lcd.print(rtc.getTimeStr());
    lcd.print("   ");
  }
  PT_END(pt);
}

static int printTempHumidity(struct pt *pt) {
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while(1) {
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 1000);
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(dht.readTemperature());
    lcd.print(" Cel ");
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 1000);
    lcd.setCursor(0,1);
    lcd.print("Hum: ");
    lcd.print(dht.readHumidity());
    lcd.print(" %    ");
  }
  PT_END(pt);
}

void setup() {
  // change this to whichever pin you want to use
  // initialize the LED pin as an output:
  for (int i = 0; i < 4; i++) {
    pinMode(led[i], OUTPUT);
  }
  
  // initialize the pushbutton pin as an input:
  pinMode(button, INPUT_PULLUP);

  dht.begin();
  
  initClock();
  initScreen();

  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
  PT_INIT(&pt4);
}

void loop() {
  printDateAndTime(&pt1);
  printTempHumidity(&pt2);
  displaySwitch(&pt3);
  checkAlarm(&pt4);  
}
