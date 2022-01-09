/* original sketch by Nicu FLORICA (niq_ro)
 * https://nicuflorica.blogspot.com/
 * http://arduinotehniq.blogspot.com/
 * https://www.arduinotehniq.com/ 
 * control for 2 leds using PWM
 * ver.1.1 - button1 slow increase led1 light, button2 slow increase led2 light, button3 stop the light
 */

#define buton1 2
#define buton2 3
#define buton3 4

#define led1 5
#define led2 6

byte stare = 0;
byte stare0 = 7;
unsigned long tp0 = 0;
byte piviem1 = 0;
byte piviem2 = 0;
byte pwmmax = 255;
byte deltapwm = 1;
int pauzamica = 250;
byte pwmmin = 2;

void setup() {
 Serial.begin(9600);
 Serial.println(" ");
 Serial.println("control test");
 pinMode(buton1, INPUT);
 pinMode(buton2, INPUT);
 pinMode(buton3, INPUT);
  
/*
digitalWrite(buton1, HIGH);
digitalWrite(buton2, HIGH);
digitalWrite(buton3, HIGH);
*/

 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);

 analogWrite(led1, 0);
 analogWrite(led2, 0);

Serial.println("-----------");
}

void loop() {

if ((digitalRead(buton1) == LOW) and (stare0 == 0))
{
  tp0 = millis()/1000;
  stare = 1;
  piviem2 = 0;
  Serial.println("Button 1 is push !");
  delay(pauzamica);
}

if ((digitalRead(buton2) == LOW) and (stare0 == 0))
{
  tp0 = millis()/1000;
  stare = 2; 
  piviem1 = 0;
  Serial.println("Button 2 is push !");
  delay(pauzamica);
}

if ((digitalRead(buton1) == LOW) and (stare0 == 2))
{
  tp0 = millis()/1000;
  stare = 3;
  Serial.println("Button 1 is push !");
  delay(pauzamica);
}

if ((digitalRead(buton2) == LOW) and (stare0 == 1))
{
  tp0 = millis()/1000;
  stare = 4;
  Serial.println("Button 2 is push !");
  delay(pauzamica);
}
/*
if (digitalRead(buton3) == LOW)
{
  tp0 = millis()/1000;
  stare = 0; 
  Serial.println("Button 3 was push !");
  piviem1 = 0;
  piviem2 = 0;
  Serial.println("LEDs OFF!");
  delay(pauzamica);
}
*/

if ((digitalRead(buton3) == LOW) and (stare0 == 1))
{
  tp0 = millis()/1000;
  stare = 5;
  Serial.println("Button 1 is push !");
  delay(pauzamica);
}

if ((digitalRead(buton3) == LOW) and (stare0 == 2))
{
  tp0 = millis()/1000;
  stare = 6;
  Serial.println("Button 2 is push !");
  delay(pauzamica);
}


if ((millis()/1000-tp0)%2 == 0) 
{
  
if ((stare == 1) and (piviem1 < pwmmax)) 
{
  Serial.print("LED1 increase! ");
  piviem1 = piviem1 + deltapwm; 
  Serial.println(piviem1);
  if (piviem1 > pwmmax)
  {
    piviem1 = pwmmax;
    Serial.println("LED1 is at maximum!");
  }
}

if ((stare == 2) and (piviem2 < pwmmax)) 
{
  Serial.print("LED2 increase! ");
  piviem2 = piviem2 + deltapwm; 
  Serial.println(piviem2);
  if (piviem2 > pwmmax) 
  {
    piviem2 = pwmmax;
    Serial.println("LED2 is at maximum!");
  }
}

if ((stare == 3) and (piviem2 > pwmmin-1)) 
{
  Serial.print("LED2 decrease! ");
  piviem2 = piviem2 - deltapwm; 
  Serial.println(piviem2);
  if (piviem2 < pwmmin)
  {
    piviem2 = 0;
    piviem1 = 0;
    Serial.println("LED2 is at minimum!");
    stare = 1;
    tp0 = millis()/1000;
  }
}

if ((stare == 4) and (piviem1 > pwmmin-1)) 
{
  Serial.print("LED1 decrease! ");
  piviem1 = piviem1 - deltapwm; 
  Serial.println(piviem1);
  if (piviem1 < pwmmin)
  {
    piviem1 = 0;
    piviem2 = 0;
    Serial.println("LED1 is at minimum!");
    stare = 2;
    tp0 = millis()/1000;
  }
}

if ((stare == 5) and (piviem1 > pwmmin-1)) 
{
  Serial.print("LED1 decrease! ");
  piviem1 = piviem1 - deltapwm; 
  Serial.println(piviem1);
  if (piviem1 < pwmmin)
  {
    piviem1 = 0;
    piviem2 = 0;
    Serial.println("LED1 is at minimum!");
    stare = 0;
    tp0 = millis()/1000;
  }
}

if ((stare == 6) and (piviem2 > pwmmin-1)) 
{
  Serial.print("LED2 decrease! ");
  piviem2 = piviem2 - deltapwm; 
  Serial.println(piviem2);
  if (piviem2 < pwmmin)
  {
    piviem1 = 0;
    piviem2 = 0;
    Serial.println("LED2 is at minimum!");
    stare = 0;
    tp0 = millis()/1000;
  }
}

}

 analogWrite(led1, piviem1);
 analogWrite(led2, piviem2);

stare0 = stare;
} // end main loop
