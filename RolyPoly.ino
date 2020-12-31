

#include <Wire.h> // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"
//#include <SFE_MMA8452Q.h> // Includes the SFE_MMA8452Q library

MMA8452Q accel; // Default MMA8452Q object create. (Address = 0x1D)

int rows[] = {2, 3, 4, 5, 6, 7, 8};
int cols[] = {9, 10, 11, 12, 13};

float x, y, z;
bool pixels[7][5];
double lilY, lilX;
double bigY, bigX;
const double pspeed = .34;
bool predBlink = 1;

int preyScore = 0;
int predScore = 0;

unsigned long delta = 125;
unsigned long nextTime = 0;
unsigned long gameLength = 15000;
unsigned long gameEndTime = 0;
unsigned long gameStartTime = 0;


void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();

  randomizePos();
  
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
}

void loop() {
  
    if (accel.available()&& millis()>nextTime) {
    x = accel.getCalculatedX();
    y = accel.getCalculatedY();

    checkGameEnd();
    checkPreyPos();
    checkPredPos();
    for(int i = 0; i<7; i++){
      for(int j = 0; j<5; j++){
        pixels[i][j] = 0;
      }
    }
    
    //sets prey pixel
    pixels[(int)lilY][(int)lilX] = 1;

    //sets pred pixels
    pixels[(int)bigY][(int)bigX] = predBlink;
    pixels[(int)bigY +1][(int)bigX] = predBlink;
    pixels[(int)bigY][(int)bigX +1] = predBlink;
    pixels[(int)bigY+1][(int)bigX+1] = predBlink;
    predBlink = !predBlink;
    
    nextTime+= delta;
  }
  
  setScreen();
  
}


//x: -.6 max left, .6 max right
//y: -.6 max down, .6 max up


void setScreen(){
  for(int j = 0; j<5; j++){
    digitalWrite(cols[j], LOW);
    for(int i= 0; i<7; i++){
      if(pixels[i][j]){
        digitalWrite(rows[i], HIGH);
      }
    }
    delay(2);
    digitalWrite(cols[j], HIGH);
    for(int i= 0; i<7; i++){
      digitalWrite(rows[i], LOW);
    }
  }
}

void checkPreyPos(){
  //sets x pos
    if(-pspeed<x&&x<pspeed){
    }
    else if(x<=-pspeed&& lilX>pspeed){
      lilX-=pspeed;
    }
    else if(x>=pspeed&& lilX<5-pspeed){
      lilX+=pspeed;
    }
    //sets y pos
    if(-pspeed<y&&y<pspeed){
    }
    else if(y<-pspeed&& lilY<7-pspeed){
      lilY+=pspeed;
    }
    else if(y>=pspeed && lilY>pspeed){
      lilY-=pspeed;
    }
}

void checkPredPos(){
  if(Serial.available()){
    byte mover = Serial.read();
    if(mover==1&&bigY>0)
    bigY-=1;
    else if(mover==2&&bigY<5)
    bigY+=1;
    else if(mover==3&&bigX>0)
    bigX-=1;
    else if(mover==4&&bigX<3)
    bigX+=1;
  }
  
}

void checkGameEnd(){
  //if prey won:
  if(millis()-gameStartTime>gameLength)
  {
    gameEndTime = millis();
    preyScore ++;
    for(int i = 0; i<7; i++){
        for(int j = 0; j<5; j++){
          pixels[i][j] = 0;
        }
      }
      pixels[3][2] = 1;
      //scores equal
      if(predScore == preyScore){
        pixels[6][2] = 1;
      }
      // if prey ahead
      else if(preyScore-predScore<=2){
        pixels[6][3] = 1;
        pixels[6][2] = 1;
      }
      else if(preyScore-predScore>2){
        pixels[6][2] = 1;
        pixels[6][3] = 1;
        pixels[6][4] = 1;
      }

      //prey behind
      else if(predScore-preyScore<=2){
        pixels[6][2] = 1;
        pixels[6][1] = 1;
      }
      else if(predScore-preyScore>2){
        pixels[6][2] = 1;
        pixels[6][1] = 1;
        pixels[6][0] = 1;
      }
      
      
      while(millis()<gameEndTime + 4000){
        setScreen();
      }
      randomizePos();
    
    gameStartTime=millis();
  }


  
  //if predator won:
  if(((int)lilY==(int)bigY || (int)lilY==(int)bigY+1) && ((int)lilX==(int)bigX || (int)lilX ==(int)bigX+1)){
      gameEndTime = millis();
      predScore ++;
      for(int i = 0; i<7; i++){
        for(int j = 0; j<5; j++){
          pixels[i][j] = 0;
        }
      }
      pixels[3][2] = 1; pixels[3][3] = 1; pixels[4][2] = 1; pixels[4][3] = 1;
      //scores equal
      if(predScore == preyScore){
        pixels[6][2] = 1;
      }
      //pred ahead
      else if(predScore-preyScore<=2){
        pixels[6][3] = 1;
        pixels[6][2] = 1;
      }
      else if(predScore-preyScore>2){
        pixels[6][2] = 1;
        pixels[6][3] = 1;
        pixels[6][4] = 1;
      }

      //pred behind
      else if(preyScore-predScore<=2){
        pixels[6][2] = 1;
        pixels[6][1] = 1;
      }
      else if(preyScore-predScore>2){
        pixels[6][2] = 1;
        pixels[6][1] = 1;
        pixels[6][0] = 1;
      }
      
      
      while(millis()<gameEndTime + 4000){
        setScreen();
      }
      randomizePos();
      gameStartTime = millis();
  }
}

void randomizePos(){
  randomSeed(A0);
  bigX = random(0, 4) /1.0;
  bigY = random(0, 6) /1.0;

  randomSeed(A1);
  lilX = random(0, 5) /1.0;
  lilY = random(0, 7) /1.0;
  while(((int)lilY==(int)bigY || (int)lilY==(int)bigY+1) && ((int)lilX==(int)bigX || (int)lilX ==(int)bigX+1)){
    lilX = random(0, 5) /1.0;
    lilY = random(0, 7) /1.0;
  }
}
