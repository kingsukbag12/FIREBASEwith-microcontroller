#include <TM1637Display.h>
 

#include <dht.h>

#include <Servo.h> 
#define pin A5
#define CLK 9 //can be any digital pin
#define DIO 8 //can be any digital pin
TM1637Display display(CLK, DIO);

dht DHT;
Servo myservo;
const int servo_pin = 2;
const int trig_pin = 3;
const int echo_pin = 4;
const int inter_time = 200;
int time = 0;
int c=0;
void setup() 
{
  Serial.begin(9600);
  myservo.attach(servo_pin, 500, 2400);
  display.setBrightness(0x0a); //set the diplay to maximum brightness
  myservo.write(90);
  pinMode (trig_pin, OUTPUT);
  pinMode (echo_pin, INPUT);
  delay(3000);
} 

void loop() 
{ 
  DHT.read11(pin);
  float duration, distance;
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn (echo_pin, HIGH);
  distance = (duration/2)/29;
  Serial.print(distance);
  Serial.println("cm  ");
  Serial.println("The temperatue is");
  Serial.println(DHT.temperature);
  //Serial.print(DHT.temperature);
  display.showNumberDec(DHT.temperature,false,2,0);
  //display.showNumberDec(10,false,2,0);
  time = time + inter_time;
  delay(inter_time);
  if (distance < 15)
  { c++;
    for(int i = 2000; i >= 1100; i-=25){
      myservo.writeMicroseconds(i);
      Serial.println("2");
      delay(50);
    }
    delay(1500);
    for(int i = 1100; i <= 2000; i+=25){
      myservo.writeMicroseconds(i);
      Serial.println("1");
      delay(50);
    }
  }
  display.showNumberDec(c);
  if(c>100000)
  exit(0);
 
}
