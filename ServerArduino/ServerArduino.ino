#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(A5, 8);
const byte address[6] = "00001";

int En0 = 7; 
int En1 = 6;
int S0  = 5;
int S1  = 4;
int S2  = 3;
int S3  = 2;

char F_L_LED = 'a';
char F_R_LED = 'b';
char B_L_LED = 'g';
char B_R_LED = 'h';
char M_L_L_LED = 'c';
char M_L_R_LED = 'd';
char M_R_L_LED = 'e';
char M_R_R_LED = 'f';

 
SoftwareSerial BTSerial(9, 10);    
int SIG_pin = A3;

void setup() {
  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_MIN);

  radio.stopListening();
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(En0, OUTPUT);
  pinMode(En1, OUTPUT);
 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

}
 
 
int readMux(int channel){
  int controlPin[] = {S0,S1,S2,S3,En0,En1};
 
  int muxChannel[32][6]={
    {0,0,0,0,0,1}, //channel 0
    {0,0,0,1,0,1}, //channel 1
    {0,0,1,0,0,1}, //channel 2
    {0,0,1,1,0,1}, //channel 3
    {0,1,0,0,0,1}, //channel 4
    {0,1,0,1,0,1}, //channel 5
    {0,1,1,0,0,1}, //channel 6
    {0,1,1,1,0,1}, //channel 7
    {1,0,0,0,0,1}, //channel 8
    {1,0,0,1,0,1}, //channel 9
    {1,0,1,0,0,1}, //channel 10
    {1,0,1,1,0,1}, //channel 11
    {1,1,0,0,0,1}, //channel 12
    {1,1,0,1,0,1}, //channel 13
    {1,1,1,0,0,1}, //channel 14
    {1,1,1,1,0,1}, //channel 15
    {0,0,0,0,1,0}, //channel 16
    {0,0,0,1,1,0}, //channel 17
    {0,0,1,0,1,0}, //channel 18
    {0,0,1,1,1,0}, //channel 19
    {0,1,0,0,1,0}, //channel 20
    {0,1,0,1,1,0}, //channel 21
    {0,1,1,0,1,0}, //channel 22
    {0,1,1,1,1,0}, //channel 23
    {1,0,0,0,1,0}, //channel 24
    {1,0,0,1,1,0}, //channel 25
    {1,0,1,0,1,0}, //channel 26
    {1,0,1,1,1,0}, //channel 27
    {1,1,0,0,1,0}, //channel 28
    {1,1,0,1,1,0}, //channel 29
    {1,1,1,0,1,0}, //channel 30
    {1,1,1,1,1,0}  //channel 31
  };
 
  //loop through the 6 sig
  for(int i = 0; i < 6; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
 
  //read the value at the SIG pin
  int val = analogRead(SIG_pin);
 
  //return the value
  return val;
}


void TurnLED(int value)
{
  if(value==10 || value==12 || value==14)
  {
    radio.write(&F_L_LED, sizeof(F_L_LED));
    }
  if(value==16 || value==18 || value==20)
  {
    radio.write(&F_R_LED, sizeof(F_R_LED));
    }
  if(value==5 || value==6 || value==7)
  {
    radio.write(&M_L_L_LED, sizeof(M_L_L_LED));
    }
  if(value==8 || value==9 || value==11)
  {
    radio.write(&M_L_R_LED, sizeof(M_L_R_LED));
    }
  if(value==19 || value==21 || value==22)
  {
    radio.write(&M_R_L_LED, sizeof(M_R_L_LED));
    }
  if(value==23 || value==24 || value==25)
  {
    radio.write(&M_R_R_LED, sizeof(M_R_R_LED));
    }
  if(value==2 || value==3 || value==4)
  {
    radio.write(&B_L_LED, sizeof(B_L_LED));
    }
  if(value==26 || value==27 || value==28)
  {
    radio.write(&B_R_LED, sizeof(B_R_LED));
    }
  
}


void OffLED(int value)
{
  char text;
  
  if(value==0)
  {
    text = 'i';
    radio.write(&text, sizeof(text));
    }
  if(value==1)
  {
    text = 'j';
    radio.write(&text, sizeof(text));
    }
  if(value==2)
  {
    text = 'k';
    radio.write(&text, sizeof(text));
    }
  if(value==3)
  {
    text = 'l';
    radio.write(&text, sizeof(text));
    }
  if(value==4)
  {
    text = 'm';
    radio.write(&text, sizeof(text));
    }
  if(value==5)
  {
    text = 'n';
    radio.write(&text, sizeof(text));
    }
  if(value==6)
  {
    text = 'o';
    radio.write(&text, sizeof(text));
    }
  if(value==7)
  {
    text = 'p';
    radio.write(&text, sizeof(text));
    }
}


int MAX = 0;
int check[32];
int DeskLED[8];

void loop() { 

  for(int i = 0; i < 32; i ++){ 
    Serial.print(readMux(i));

    if(readMux(i)>200)
    {
      TurnLED(i);
      check[i]=1;
      }

    if((readMux(i)>200)&&readMux(i)>MAX)
    {
       MAX = i;
    }
     
    Serial.print(",");  
  }  
  Serial.println(" ");

  DeskLED[0]=check[10]+check[12]+check[14];
  DeskLED[1]=check[16]+check[18]+check[20];
  DeskLED[2]=check[5]+check[6]+check[7];
  DeskLED[3]=check[8]+check[9]+check[11];
  DeskLED[4]=check[19]+check[21]+check[22];
  DeskLED[5]=check[23]+check[24]+check[25];
  DeskLED[6]=check[2]+check[3]+check[4];
  DeskLED[7]=check[26]+check[27]+check[28];
    
  for(int i =0; i<8; i++)
  {
    if(DeskLED[i]==0)
    {
      if(i==0){OffLED(0);}
      if(i==1){OffLED(1);}
      if(i==2){OffLED(2);}
      if(i==3){OffLED(3);}
      if(i==4){OffLED(4);}
      if(i==5){OffLED(5);}
      if(i==6){OffLED(6);}
      if(i==7){OffLED(7);}
    }
    DeskLED[i]=0;
    }
    
  for(int i =0; i<32; i++)
  {
    check[i]=0;
    }  

  if(MAX==0){BTSerial.write('0');}
  if(MAX==1){BTSerial.write('1');}
  if(MAX==2){BTSerial.write('2');}
  if(MAX==3){BTSerial.write('3');}
  if(MAX==4){BTSerial.write('4');}
  if(MAX==5){BTSerial.write('5');}
  if(MAX==6){BTSerial.write('6');}
  if(MAX==7){BTSerial.write('7');}
  if(MAX==8){BTSerial.write('8');}
  if(MAX==9){BTSerial.write('9');}
  if(MAX==10){BTSerial.write("10");}
  if(MAX==11){BTSerial.write("11");}
  if(MAX==12){BTSerial.write("12");}
  if(MAX==13){BTSerial.write("13");}
  if(MAX==14){BTSerial.write("14");}
  if(MAX==15){BTSerial.write("15");}
  if(MAX==16){BTSerial.write("16");}
  if(MAX==17){BTSerial.write("17");}
  if(MAX==18){BTSerial.write("18");}
  if(MAX==19){BTSerial.write("19");}
  if(MAX==20){BTSerial.write("20");}
  if(MAX==21){BTSerial.write("21");}
  if(MAX==22){BTSerial.write("22");}
  if(MAX==23){BTSerial.write("23");}
  if(MAX==24){BTSerial.write("24");}
  if(MAX==25){BTSerial.write("25");}
  if(MAX==26){BTSerial.write("26");}
  if(MAX==27){BTSerial.write("27");}
  if(MAX==28){BTSerial.write("28");}
  if(MAX==29){BTSerial.write("29");}
  if(MAX==30){BTSerial.write("30");}
  if(MAX==31){BTSerial.write("31");}
  
  MAX = 0;
  
  delay(1000);


}
