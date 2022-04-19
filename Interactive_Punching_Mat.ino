/*//////////////////////////////////////////////////////////////
//Project name: Interactive Punching mat                       /
//Author: Alex Inthavong                                       /
//Class: PROJ 222                                              /
//Advisor: Shaun Nanan                                         /
//Date of Submission: April 15th, 2022                         /                                                             /
//////////////////////////////////////////////////////////////*/

/*Source Code Citation
Title: Force Sensor: Code and Wiring
Author: Baskin, S
Date: June 4th, 2016
Code Version: 1.0
Availbility: http://samsneatprojectblogcode.blogspot.com/2016/06/force-sensor-code-and-wiring.html

Title: Interface I2C 16x2 LCD with Arduino Uno
Author: Joseph, A
Date: May 5th, 2020
Code Version: 1.0
Availbility: https://create.arduino.cc/projecthub/akshayjoseph666/interface-i2c-16x2-lcd-with-arduino-uno-just-4-wires-273b24

Title: Play a Melody using the tone() function
Author: Igoe, T
Date: January 21st, 2010
Code Version: 1.0
Availbility: https://docs.arduino.cc/built-in-examples/digital/toneMelody
*/
//imported libraries
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <Wire.h> // Library for I2C communication // Wiring: SDA pin is connected to A4 and SCL pin to A5.
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20,4);
#include "pitches.h" // Library for speaker
int score = 0; // player's score initialized to 0

//define LED pins
int led1 = 12; 
int led2 = 11;
int led3 = 10;
int led4 = 9;
int led5 = 8;
int led6 = 7;

//define button pins
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;

// define number of tries before program is restarted
int lives = 3;

//define note sounds
int note1 = NOTE_C4;
int note2 = NOTE_F5;
int note3 = NOTE_DS8;
int note4 = NOTE_G6;

//Function runs after an incorrect input from user
//leds will blink at the same time a tone is played from the speaker
void tryAgain(){
  tone(6, note1); // play NOTE_C4
  digitalWrite(led1, HIGH); 
  digitalWrite(led2, HIGH); 
  digitalWrite(led3, HIGH); 
  digitalWrite(led4, HIGH); 
  digitalWrite(led5, HIGH); 
  digitalWrite(led6, HIGH); 
  delay(300); // 300 ms delay
  noTone(6); // stop tone from pin 6
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  delay(300); // 300 ms delay
  tone(6, note1);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  delay(300); // 300 ms delay
  noTone(6); // stop tone from pin 6
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  delay(300); // 300 ms delay
  tone(6, note1);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  delay(300); // 300 ms delay
  noTone(6); // stop tone from pin 6
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  delay(300); // 300 ms delay
  lcd.setCursor(2, 1);
  lcd.print("Incorrect Combo..");
  lcd.setCursor(2, 2);
  lcd.print("Try Again!   ");
  delay(2000); // 2000 ms delay
  lcd.clear();   
}

void easyMode(){ // one punch difficulty mode
  //max number of lights in pattern
  int maxCombo = 1;
  //LCD display during game
  lcd.setCursor(2, 1);
  lcd.print("Combo Counter: ");
  lcd.print(score);
  lcd.setCursor(2, 2);
  lcd.print("Tries Left: ");
  lcd.print(lives);
  //define light pattern
  String ledPattern = "";
  int X = 0;
  //create  LED pattern. while X is less than 1
  while(X < maxCombo){
    // random light selection
    int light = round(random(1,7));
    //remember the pattern
    ledPattern = ledPattern + String(light);
    //blink the target LED
    if (light == 1) {
      digitalWrite(led1, HIGH);   // turn LED1 on
      delay(500); // 500 ms delay
      digitalWrite(led1, LOW);   // turn LED1 off
    }
    if (light == 2) {
      digitalWrite(led2, HIGH);   // turn LED2 on
      delay(500); // 500 ms delay
      digitalWrite(led2, LOW);   // turn LED2 off
    }
    if (light == 3) {
      digitalWrite(led3, HIGH);   // turn LED3 on
      delay(500); // 500 ms delay
      digitalWrite(led3, LOW);   // turn LED3 off
    }
    if (light == 4) {
      digitalWrite(led4, HIGH);   // turn LED4 on
      delay(500); // 500 ms delay
      digitalWrite(led4, LOW);   // turn LED4 off
    }
    if (light == 5) {
      digitalWrite(led5, HIGH);   // turn LED5 on
      delay(500); // 500 ms delay
      digitalWrite(led5, LOW);   // turn LED5 off
    }
    if (light == 6) {
      digitalWrite(led6, HIGH);   // turn LED6 on
      delay(500); // 500 ms delay
      digitalWrite(led6, LOW);   // turn LED6 off
    }
    delay(500); // 500 ms delay
    X++;
  }
// replicate LED pattern on sensors
  String sensorPattern = "";
  int punches = 0;
  // one punch combo detection
  while (punches < maxCombo) {
    if (analogRead(sensor1) > 800) {
      sensorPattern = sensorPattern + "1";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor2) > 800) {
      sensorPattern = sensorPattern + "2";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor3) > 800) {
      sensorPattern = sensorPattern + "3";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor4) > 800) {
      sensorPattern = sensorPattern + "4";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor5) > 800) {
      sensorPattern = sensorPattern + "5";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor6) > 800) {
      sensorPattern = sensorPattern + "6";
      punches++;
      delay(400); // 400 ms delay
    }        
  }
// If combo matches LED pattern
  if (sensorPattern == ledPattern) 
  {
    tone(6, note2); //play sound on speaker
    delay(100); // delay for 100 ms
    noTone(6); // stop tone from pin 6
    score++; // add +1 to score
    delay(1000); // delay for 1000 ms
    easyMode(); // return to start of loop and output another light pattern
  }
// If combo is incorrect
while(lives != 1){ // while lives is not equal to one.
  if (sensorPattern != ledPattern) // when the sensor input does not match the LED output
  {
    lives--; // -1 to lives
    tryAgain();
    easyMode(); // Output another LED pattern
  }
}
  tone(6, note3);
  delay(200); // 200 ms delay
  noTone(6); // stop tone from pin 6
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("Game Over");
  delay(300); // 300 ms delay
  return;
}

void mediumMode(){ // two punch difficulty mode
  int maxCombo = 2; //max number of lights in pattern
  //LCD display during game
  lcd.setCursor(2, 1);
  lcd.print("Combo Counter: ");
  lcd.print(score);
  lcd.setCursor(2, 2);
  lcd.print("Tries Left: ");
  lcd.print(lives);
  String ledPattern = ""; //define light pattern
  int X = 0;
  //create  LED pattern. while X is less than 2
  while(X < maxCombo){
    int light = round(random(1,7)); //random light selection
    ledPattern = ledPattern + String(light); //remember the pattern
    if (light == 1) {
      digitalWrite(led1, HIGH);   // turn the LED1 on
      delay(500); // 500 ms delay
      digitalWrite(led1, LOW);   // turn the LED1 off
    }
    if (light == 2) {
      digitalWrite(led2, HIGH);   // turn the LED2 on
      delay(500); // 500 ms delay
      digitalWrite(led2, LOW);   // turn the LED2 off
    }
    if (light == 3) {
      digitalWrite(led3, HIGH);   // turn the LED3 on
      delay(500); // 500 ms delay
      digitalWrite(led3, LOW);   // turn the LED3 off
    }
    if (light == 4) {
      digitalWrite(led4, HIGH);   // turn the LED4 on
      delay(500); // 500 ms delay
      digitalWrite(led4, LOW);   // turn the LED4 off
    }
    if (light == 5) {
      digitalWrite(led5, HIGH);   // turn the LED5 on
      delay(500); // 500 ms delay
      digitalWrite(led5, LOW);   // turn the LED5 off
    }
    if (light == 6) {
      digitalWrite(led6, HIGH);   // turn the LED6 on
      delay(500); // 500 ms delay
      digitalWrite(led6, LOW);   // turn the LED6 off
    }
    delay(500); // 500 ms delay
    X++;
  }
  String sensorPattern = ""; // replicate LED pattern on sensors
  int punches = 0;
  // two punch combo detection
  while (punches < maxCombo) {
    if (analogRead(sensor1) > 800) {
      sensorPattern = sensorPattern + "1";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor2) > 800) {
      sensorPattern = sensorPattern + "2";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor3) > 800) {
      sensorPattern = sensorPattern + "3";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor4) > 800) {
      sensorPattern = sensorPattern + "4";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor5) > 800) {
      sensorPattern = sensorPattern + "5";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor6) > 800) {
      sensorPattern = sensorPattern + "6";
      punches++;
      delay(400); // 400 ms delay
    }
  }
// If combo matches LED pattern
  if (sensorPattern == ledPattern) 
  {
    tone(6, note2);
    delay(100); // 100 ms delay
    noTone(6); // stop tone from pin 6
    score++; // add +1 to score
    delay(1000); // 1 s delay
    mediumMode(); // return to start of loop and output another light pattern
  }
// If combo is incorrect
while(lives != 1){
  if (sensorPattern != ledPattern)// when the sensor input does not match the LED output
  {
    lives--; // -1 to lives
    tryAgain();
    mediumMode(); // Output another LED pattern
  }
}
  tone(6, note3);
  delay(200); // 200 ms delay
  noTone(6); // stop tone from pin 6
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("Game Over");
  delay(300); // 300 ms delay
  return;
}

void hardMode(){ // three punch difficulty mode
  int maxCombo = 3; //max number of lights in pattern
  //LCD display during game
  lcd.setCursor(2, 1);
  lcd.print("Combo Counter: ");
  lcd.print(score);
  lcd.setCursor(2, 2);
  lcd.print("Tries Left: ");
  lcd.print(lives);
  String ledPattern = ""; //define light pattern
  int X = 0;
  //create  LED pattern. while X is less than 3
  while(X < maxCombo){
    int light = round(random(1,7)); //random light selection
    ledPattern = ledPattern + String(light); //remember the pattern
    if (light == 1) {
      digitalWrite(led1, HIGH);   // turn the LED1 on
      delay(500); // 500 ms delay
      digitalWrite(led1, LOW);   // turn the LED1 off
    }
    if (light == 2) {
      digitalWrite(led2, HIGH);   // turn the LED2 on
      delay(500); // 500 ms delay
      digitalWrite(led2, LOW);   // turn the LED2 off
    }
    if (light == 3) {
      digitalWrite(led3, HIGH);   // turn the LED3 on
      delay(500); // 500 ms delay
      digitalWrite(led3, LOW);   // turn the LED3 off
    }
    if (light == 4) {
      digitalWrite(led4, HIGH);   // turn the LED4 on
      delay(500); // 500 ms delay
      digitalWrite(led4, LOW);   // turn the LED4 off
    }
    if (light == 5) {
      digitalWrite(led5, HIGH);   // turn the LED5 on
      delay(500); // 500 ms delay
      digitalWrite(led5, LOW);   // turn the LED5 off
    }
    if (light == 6) {
      digitalWrite(led6, HIGH);   // turn the LED6 on
      delay(500); // 500 ms delay
      digitalWrite(led6, LOW);   // turn the LED6 off
    }
    delay(500); // 500 ms delay
    X++;
  }
// check if combo is correct
  String sensorPattern = ""; // replicate LED pattern on sensors
  int punches = 0;
  while (punches < maxCombo) {
    if (analogRead(sensor1) > 800) {
      sensorPattern = sensorPattern + "1";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor2) > 800) {
      sensorPattern = sensorPattern + "2";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor3) > 800) {
      sensorPattern = sensorPattern + "3";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor4) > 800) {
      sensorPattern = sensorPattern + "4";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor5) > 800) {
      sensorPattern = sensorPattern + "5";
      punches++;
      delay(400); // 400 ms delay
    }
    if (analogRead(sensor6) > 800) {
      sensorPattern = sensorPattern + "6";
      punches++;
      delay(400); // 400 ms delay
    }    
  }
// If combo matches LED pattern
  if (sensorPattern == ledPattern) 
  {
    tone(6, note2);
    delay(100); // 100 ms delay
    noTone(6); // stop tone from pin 6
    score++;
    delay(1000); // 1000 ms delay
    hardMode(); // return to start of loop and output another light pattern
  }
// If combo is incorrect
while(lives != 1){
  if (sensorPattern != ledPattern) // when the sensor input does not match the LED output
  {
    lives--; // -1 to lives
    tryAgain();
    hardMode(); // Output another LED pattern
  }
}
  tone(6, note3);
  delay(200); // 200 ms delay
  noTone(6); // stop tone from pin 6
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("Game Over");
  delay(300); // 300 ms delay
  return;
}
// function to show on LCD during difficulty selection
void difficulty(){
  lcd.setCursor(0, 0);
  lcd.print("Select a Difficulty:");
  lcd.setCursor(0, 1);
  lcd.print("1 hit combo:Target 1");
  lcd.setCursor(0, 2);
  lcd.print("2 hit combo:Target 2");
  lcd.setCursor(0, 3);
  lcd.print("3 hit combo:Target 3");
}
void setup(){                
  // initialize the LED pins as outputs
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT); 
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  
  // Turn on LCD
  lcd.init();
  lcd.backlight();
  Serial.begin(9600); //communicate with serial monitor
  Serial.println(sensor1); //print data to serial port
}

// main function
void loop(){
  difficulty(); //display difficulty
  lives = 3; // set tries to 3
  score = 0; // combo counter starts at zero
  digitalWrite(led1, HIGH); // for easy mode selection
  digitalWrite(led2, HIGH); // for medium mode selection
  digitalWrite(led3, HIGH); // for hard mode selection
// start easy mode after sensor 1 has been triggered
if (analogRead(sensor1) >800)
{ 
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  tone(6, note2);
  delay(100); // 100 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Easy mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 3");
  tone(6, note4);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.setCursor(2, 0);
  lcd.print("Easy mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 2");
  tone(6, note4);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.setCursor(2, 0);
  lcd.print("Easy mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 1");
  tone(6, note4);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.clear();
  easyMode();
}
// start medium mode after sensor 2 has been triggered
if (analogRead(sensor2) >800)
{ 
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  tone(6, note2);
  delay(100); // 100 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Medium mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 3");
  tone(6, note4);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000);
  lcd.setCursor(2, 0);
  lcd.print("Medium mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 2");
  tone(6, note4);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.setCursor(2, 0);
  lcd.print("Medium mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 1");
  tone(6, note4);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.clear();
  mediumMode();
}
// start hard mode after sensor 3 has been triggered
if (analogRead(sensor3) >800)
{ 
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  tone(6, note2);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Hard mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 3");
  tone(6, note4);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000); // 1000 ms delay
  lcd.setCursor(2, 0);
  lcd.print("Hard mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 2");
  tone(6, note4);
  delay(50);
  noTone(6); // stop tone from pin 6
  delay(1000);
  lcd.setCursor(2, 0);
  lcd.print("Hard mode");
  lcd.setCursor(2, 1);
  lcd.print("Starting in: 1");
  tone(6, note4);
  delay(50); // 50 ms delay
  noTone(6); // stop tone from pin 6
  delay(1000);
  lcd.clear();
  hardMode();
}
}
