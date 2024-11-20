#include <dht11.h>
#include <Versalino.h>

dht11 DHT11;
int celciusTemp;

#define trigPin 8
#define echoPin 7
long duration, distance, c;            //c is the speed of sound


void setup(){
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 DHT11.attach(3);
 Serial.begin(9600);
}

void loop(){
 int check = DHT11.read();
 switch(check){                    
  case 0: Serial.println("DHT11 OK"); break;
  case -1: Serial.println("DHT11 Checksum error"); break;
  case -2: Serial.println("DHT11 Time out error"); break;
  default: Serial.println("DHT11 unknown error"); break; 
 }
 
 //fire the ultrasonic and get the time interval between send/receive
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  //get the temp in celcius (default)
  celciusTemp = (int)DHT11.temperature;
  
  //calculate the speed of sound based on value from temp sensor
  c = 331.3 + celciusTemp * 0.606;
  
  //calculate the distance from duration and speed of sound
  distance = c * duration;
  
 Serial.println("Temperature = " + celciusTemp);
 Serial.println("Speed of sound = " + c);
 Serial.println("Distance = " + distance);
 Serial.println();
  
 delay(2000);            //this is slow because the DHT11 can't be clocked over 1 reading per 2 seconds 
}

