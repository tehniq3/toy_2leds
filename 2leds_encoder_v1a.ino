/* based on Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 * adapted for DC motor control in PWM (sense, stop, etc) by Nicu FLORICA (niq_ro)
 * https://nicuflorica.blogspot.com/
 * http://arduinotehniq.blogspot.com/
 * https://www.arduinotehniq.com/ 
 */
 
#define CLK 2
#define DT 3
#define SW 4
#define led1 5
#define led2 6
#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(DT, CLK);
//   avoid using pins with LEDs attached

int pauzamica = 250;
long oldPosition  = -999;
byte piviem1 = 0;
byte piviem2 = 0;
byte pwmmax = 255;
float k = 2.5;
long posmax = (long)(pwmmax/k);

void setup() {
  Serial.begin(9600);
  Serial.println(" ");
  Serial.println("PWM control 2 outputs using Encoder !");
  Serial.begin(9600);

 pinMode(SW, INPUT);
 digitalWrite(SW, HIGH);

 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);

 analogWrite(led1, 0);
 analogWrite(led2, 0);
}



void loop() {
  long newPosition = myEnc.read();
if (newPosition > posmax)
{
  newPosition = posmax;
  myEnc.write(posmax);
}

if (newPosition < -posmax)
{
  myEnc.write(-posmax);
  newPosition = -posmax;
}  
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.print(newPosition);
    Serial.print(" ---> ");

if (newPosition > 0)
{
  piviem1 = k*newPosition;
  piviem2 = 0;
  Serial.println(piviem1);
}

if (newPosition < 0)
{
  piviem1 = 0;
  piviem2 = -k*newPosition; 
  Serial.println(piviem2);
}

if (digitalRead(SW) == LOW)
{
  Serial.println("STOP button was push !");
  piviem1 = 0;
  piviem2 = 0;
  Serial.println("STOP!");
  myEnc.write(0);  // set encoder in 0
  delay(pauzamica);
}
  }
if (digitalRead(SW) == LOW)
{
  Serial.println("STOP button was push !");
  piviem1 = 0;
  piviem2 = 0;
  Serial.println("STOP!");
  myEnc.write(0);  // set encoder in 0
  delay(pauzamica);
}
  
analogWrite(led1, piviem1);
analogWrite(led2, piviem2);

  
}  // end main loop
