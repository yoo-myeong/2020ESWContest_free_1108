#include <SPI.h> 
#include <SoftwareSerial.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); 
const byte address[6] = "00001"; 

int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4 = 5;
int LED5 = 6;
int LED6 = 9;
int LED7 = 10;
int LED8 = A0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN); 

  radio.startListening();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  
}



void loop() {
  if (radio.available()) {
    char text;
    radio.read(&text, sizeof(text));
    Serial.println(text);

    if(text=='a'){analogWrite(LED1, 255);}
    if(text=='b'){analogWrite(LED2, 255);}
    if(text=='c'){analogWrite(LED3, 255);}
    if(text=='d'){analogWrite(LED4, 255);}
    if(text=='e'){analogWrite(LED5, 255);}
    if(text=='f'){analogWrite(LED6, 255);}
    if(text=='g'){analogWrite(LED7, 255);}
    if(text=='h'){analogWrite(LED8, 255);}

    if(text=='i'){digitalWrite(LED1, LOW);}
    if(text=='j'){digitalWrite(LED2, LOW);}
    if(text=='k'){digitalWrite(LED3, LOW);}
    if(text=='l'){digitalWrite(LED4, LOW);}
    if(text=='m'){digitalWrite(LED5, LOW);}
    if(text=='n'){digitalWrite(LED6, LOW);}
    if(text=='o'){digitalWrite(LED7, LOW);}
    if(text=='p'){digitalWrite(LED8, LOW);}
  }
  
}
