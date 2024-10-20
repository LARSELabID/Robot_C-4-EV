#include <SPI.h>
#include <FS.h>
#include <Math.h>
#include <Ticker.h>
// ********** SD card **********
//#define SD_CS 5  //SD CS to PIN 5 --> if different should specifed in SD.begin(PIN)
//#include <SD.h>
//bool existSD = true;


// ********** TFT_eSPI screen **********
#define TFT_CS 15  //TFT CS to PIN 15
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
//#include <JPEGDecoder.h> // ********** JPEG decoder  ********** in case JPG images used


// ********** TFT_eSPI touch **********
#define TOUCH_CS 21  //Touch CS to PIN 21
#define CALIBRATION_FILE "/TouchCalData2" // Calibration file stored in SPIFFS
#define REPEAT_CAL false // if true calibration is requested after reboot
#define totalButtonNumber 4
#define totalButtonNumber0 4



#define LABEL1_FONT &FreeSansOblique12pt7b // Key label font 1
#define LABEL2_FONT &FreeSansBold12pt7b    // Key label font 2
TFT_eSPI_Button key[totalButtonNumber];  // TFT_eSPI button class
//variables loop 2
TFT_eSPI_Button key0[totalButtonNumber0];
#define paro 12

const float pi = 3.14159;
int a1=24.75;
int a2=19.5;
int a3=19.5;
int a4=18;
float thetaf1,thetaf2,thetaf3,thetaf4;
int theta1,theta2,theta3,theta4;
float xf,yf,zf,xf1,yf1,zf1;
int x1=34,y_1=35,z1=32,v1=33;

float rutina1[150],rutina2[150],rutina3[150],rutina4[150];

int T=0;
int J=0;
int f2=0;
int f1=2;
int f0=0;

int cerrar=27;
int abrir=14;
int efector=0;
int giro=0;
int fA;
int com;
Ticker automatic;
//TaskHandle_t Task2;
//####################################################################################################
// Setup
//####################################################################################################
void IRAM_ATTR PARO_EMERGENCIA() {
    Serial.println("e");
    f1=2;
    f0=0;
}
void FuncionContar() {
 if(f1==1){
  if(fA==1){
J=J+6;
 }
}}
void setup() {
attachInterrupt(digitalPinToInterrupt(paro), PARO_EMERGENCIA, FALLING);
automatic.attach(5, FuncionContar);
pinMode(paro,INPUT_PULLDOWN);
pinMode(abrir,INPUT);
pinMode(cerrar,INPUT);
pinMode(x1,INPUT);
pinMode(z1,INPUT);
pinMode(y_1,INPUT);
pinMode(v1,INPUT);
xf= cos(thetaf1) * (a3 * cos(thetaf2 + thetaf3) + a2 * cos(thetaf2) + a4 * cos(thetaf2 + thetaf3 + thetaf4));
yf= sin(thetaf1) * (a3 * cos(thetaf2 + thetaf3) + a2 * cos(thetaf2) + a4 * cos(thetaf2 + thetaf3 + thetaf4));
zf= a1 + a3 * sin(thetaf2 + thetaf3) + a2 * sin(thetaf2) + a4 * sin(thetaf2 + thetaf3 + thetaf4);
//xTaskCreatePinnedToCore(loop2, "Task_2", 10000, NULL, 1, NULL,  0); 
  // Set all chip selects high to avoid bus contention during initialisation of each peripheral
  digitalWrite(TOUCH_CS, HIGH); // ********** TFT_eSPI touch **********
  digitalWrite(TFT_CS, HIGH); // ********** TFT_eSPI screen library **********
 // digitalWrite(SD_CS, HIGH); // ********** SD card **********

  Serial.begin(115200);
  delay (2000);
  // ********** SD card **********
 /* if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    existSD = false;
    //return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    existSD = false;
    //return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

*/
  // ********** TFT_eSPI screen library **********
  tft.begin();
  tft.invertDisplay(false); // I don't know why but it is required for my TFT to color correction
  tft.setRotation(1);  // Landscape
  touch_calibrate();  // Calibrate the touch screen and retrieve the scaling factors recorded in SD/SPIFFS


  // ********** General **********
  Serial.println("initialisation done...");


  // ********** First print **********
  int defcolor = ConvertRGBto565(131, 131, 131);
 // buttons0();
}
void loop() {
  uint16_t t_x = 0, t_y = 0; // coordenadas pulsacion
  bool pressed = tft.getTouch(&t_x, &t_y);  // true al pulsar
  if(f0==0){
    tft.fillRect(0, 0, 100, 100, TFT_WHITE);
    buttons0();
    f0=f0+1;
  }
  if(f0==2){
    tft.fillRect(0, 0, 100, 100, TFT_WHITE);
    buttons();
    f0=f0+1;
  }
  if(f0==1){
  // Comprueba si pulsas en zona de botón
  for (uint8_t b = 0; b < totalButtonNumber0; b++) {
    if (pressed && key0[b].contains(t_x, t_y)) {
      key0[b].press(true);
     // Serial.print(t_x);
     // Serial.print(",");
    //  Serial.println(t_y);
    } else {
      key0[b].press(false);
    }
  }

  // Accion si se pulsa boton
  for (uint8_t b = 0; b < totalButtonNumber0; b++) {

    if (key0[b].justReleased()) {
      key0[b].drawButton(); // redibuja al solta
      switch (b) {
        case 0:
          f0=2;
          f2=1;
          break;
        case 1:
           f0=2;
           f2=2;
          break;
           case 2:
           f0=2;
           f2=3;
          break;
           case 3:
           f0=2;
           f2=4;
          break;
        default:
          delay(1);
          // statements
      }
    }

    if (key0[b].justPressed()) {
      key0[b].drawButton(true);  // cambia color del botón al pulsar
      delay(10); // UI debouncing
    }
  }  
  }
  if(f0==3){
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(80, 175);
  tft.setTextSize(1.5);
  tft.fillRect(94, 155, 82, 30, TFT_WHITE);
  tft.print("X:");
  tft.print(xf);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(180, 175);
  tft.setTextSize(1.5);
  tft.fillRect(194, 155, 82, 30, TFT_WHITE);
  tft.print("Y:");
  tft.print(yf);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(280, 175);
  tft.setTextSize(1.5);
  tft.fillRect(294, 155, 82, 30, TFT_WHITE);
  tft.print("Z:");
  tft.print(zf);
      for (uint8_t b = 0; b < totalButtonNumber; b++) {
    if (pressed && key[b].contains(t_x, t_y)) {
      key[b].press(true);
     // Serial.print(t_x);
     // Serial.print(",");
     // Serial.println(t_y);
    } else {
      key[b].press(false);
    }
  }

  // Accion si se pulsa boton
  for (uint8_t b = 0; b < totalButtonNumber; b++) {

    if (key[b].justReleased()) {
      key[b].drawButton(); // redibuja al soltar

      switch (b) {
        case 0:
          home();
          T=0;
          status("Sistema en modo manual       ");
          f1=0;
          fA=0;
          break;
        case 1: 
        status("Sistema en modo automatico");
           f1=1;
           fA=0;
           J=0;
          break;
          case 2:
          home();
           f1=3;
           f0=0;
           fA=0;
          break;
          case 3:
           T=T+6;
           guardar();
          break;
        default:
          delay(1);
          // statements
      }
    }

    if (key[b].justPressed()) {
      key[b].drawButton(true);  // cambia color del botón al pulsar
      delay(10); // UI debouncing
    }
  }  
  }

  manual();
  automatico();
if(paro==HIGH){
Serial.print("r "+ String(theta1));
Serial.print(" "+ String(theta2));
Serial.print(" "+ String(theta3));
Serial.print(" "+ String(theta4));
Serial.print(" "+ String(giro));
Serial.println(" "+ String(efector));
} else{
 Serial.println("e");
    f1=2;
    f0=0;
}

}
void manual(){
     if(f1==0){
 if (analogRead(x1)>=2500){
 theta2=theta2+2;
 delay(50);
  }
   if (analogRead(x1)<=1200){
 theta2=theta2-2;
  delay(50);
  }
  if (analogRead(y_1)>=2400){
 theta1=theta1+2;
 delay(25);
  }
   if (analogRead(y_1)<=1500){
 theta1=theta1-2;
 delay(25);
  }
    if (analogRead(z1)>=3100){
 theta3=theta3+2;
 delay(50);
  }
   if (analogRead(z1)<=1000){
 theta3=theta3-2;
 delay(50);
  }
  if (digitalRead(27)==0){
  efector=efector+10;
  delay(50);
  }
  if (digitalRead(14)==0){
 efector=efector-10;
  delay(50);
  }
    if (digitalRead(13)==0){
  giro=giro+10;
  delay(50);
  }
  if (digitalRead(16)==0){
 giro=giro-10;
  delay(50);
  }
  if (analogRead(v1)>=3100){
 theta4=theta4+2;
 delay(50);
  }
   if (analogRead(v1)<=1000){
 theta4=theta4-2;
  delay(50);
  }
  thetaf1=theta1*pi/180;
  thetaf2=theta2*pi/180;
  thetaf3=theta3*pi/180;
  thetaf4=theta4*pi/180;
xf1=xf;
yf1=yf;
zf1=zf;
xf= cos(thetaf1) * (a3 * cos(thetaf2 + thetaf3) + a2 * cos(thetaf2) + a4 * cos(thetaf2 + thetaf3 + thetaf4));
yf= sin(thetaf1) * (a3 * cos(thetaf2 + thetaf3) + a2 * cos(thetaf2) + a4 * cos(thetaf2 + thetaf3 + thetaf4));
zf= a1 + a3 * sin(thetaf2 + thetaf3) + a2 * sin(thetaf2) + a4 * sin(thetaf2 + thetaf3 + thetaf4);
if(xf1!=xf){
 tft.fillRect(94, 155, 82, 30, TFT_WHITE);
}
if(yf1!=yf){
 tft.fillRect(194, 155, 82, 30, TFT_WHITE);
}
if(zf1!=zf){
 tft.fillRect(294, 155, 82, 30, TFT_WHITE);
}
  }
}
void guardar(){
  if (f1==0){
  if(f2==1){
    rutina1[T-6]=theta1;
    rutina1[T-5]=theta2;
    rutina1[T-4]=theta3;
    rutina1[T-3]=theta4;
    rutina1[T-2]=giro;
    rutina1[T-1]=efector;
  }
    if(f2==2){
    rutina2[T-6]=theta1;
    rutina2[T-5]=theta2;
    rutina2[T-4]=theta3;
    rutina2[T-3]=theta4;
    rutina2[T-2]=giro;
    rutina2[T-1]=efector;

  }
    if(f2==3){
    rutina3[T-6]=theta1;
    rutina3[T-5]=theta2;
    rutina3[T-4]=theta3;
    rutina3[T-3]=theta4;
    rutina3[T-2]=giro;
    rutina3[T-1]=efector;

  }
    if(f2==4){
    rutina4[T-6]=theta1;
    rutina4[T-5]=theta2;
    rutina4[T-4]=theta3;
    rutina4[T-3]=theta4;
    rutina4[T-2]=giro;
    rutina4[T-1]=efector;

  }
}
}
void automatico(){
if(f1==1){
  //com=0;
     if(f2==1){
    theta1=rutina1[J];
    theta2=rutina1[J+1];
    theta3=rutina1[J+2];
    theta4=rutina1[J+3];
    giro=rutina1[J+4];
    efector=rutina1[J+5];
    delay(10);
  }
    if(f2==2){
    theta1=rutina2[J];
    theta2=rutina2[J+1];
    theta3=rutina2[J+2];
    theta4=rutina2[J+3];
    giro=rutina2[J+4];
    efector=rutina2[J+5];
    delay(10);
  }
    if(f2==3){
    theta1=rutina3[J];
    theta2=rutina3[J+1];
    theta3=rutina3[J+2];
    theta4=rutina3[J+3];
    giro=rutina3[J+4];
    efector=rutina3[J+5];
    delay(10);
  }
    if(f2==4){
    theta1=rutina4[J];
    theta2=rutina4[J+1];
    theta3=rutina4[J+2];
    theta4=rutina4[J+3];
    giro=rutina4[J+4];
    efector=rutina4[J+5];
    delay(10);
  }
  thetaf1=theta1*pi/180;
  thetaf2=theta2*pi/180;
  thetaf3=theta3*pi/180;
  thetaf4=theta4*pi/180;
xf1=xf;
yf1=yf;
zf1=zf;
xf= cos(thetaf1) * (a3 * cos(thetaf2 + thetaf3) + a2 * cos(thetaf2) + a4 * cos(thetaf2 + thetaf3 + thetaf4));
yf= sin(thetaf1) * (a3 * cos(thetaf2 + thetaf3) + a2 * cos(thetaf2) + a4 * cos(thetaf2 + thetaf3 + thetaf4));
zf= a1 + a3 * sin(thetaf2 + thetaf3) + a2 * sin(thetaf2) + a4 * sin(thetaf2 + thetaf3 + thetaf4);
    Serial.print("r "+ String(theta1));
Serial.print(" "+ String(theta2));
Serial.print(" "+ String(theta3));
Serial.print(" "+ String(theta4));
Serial.print(" "+ String(giro));
Serial.println(" "+ String(efector));
/*if (Serial.available() > 0) {
     com=Serial.parseInt();
}
if (Serial.available() > 0) {
         com=Serial.parseInt();
}
    */ 
     fA=1;
if(J>=T){
  J=0;
}
}
}
void home(){
  if(f0==3){/*
  float D = (xf * xf + yf * yf + (zf - d1) * (zf - d1) - a2 * a2 - a3 * a3) / (2 * a2 * a3);
  if((D>1)&&(D<1.1)){
  D=0.9999999;
}
  theta1 = atan2(yf, xf);
  theta3 = atan2(sqrt(1 - D * D), D);
  theta2 = atan2(zf - d1, sqrt(xf * xf + yf * yf)) - atan2(a3 * sin(theta3), a2 + a3 * cos(theta3));
theta1=theta1*180/pi;
theta2=theta2*180/pi;
theta3=theta3*180/pi;*/
theta1=0;
theta2=0;
theta3=0;
theta4=0;
xf= cos(theta1) * (a3 * cos(theta2 + theta3) + a2 * cos(theta2) + a4 * cos(theta2 + theta3 + theta4));
yf= sin(theta1) * (a3 * cos(theta2 + theta3) + a2 * cos(theta2) + a4 * cos(theta2 + theta3 + theta4));
zf= a1 + a3 * sin(theta2 + theta3) + a2 * sin(theta2) + a4 * sin(theta2 + theta3 + theta4);
efector=0;
giro=0;
}
}
void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;
/*
  if (existSD) {
    // check if calibration file exists and size is correct
    if (SD.exists(CALIBRATION_FILE)) {
      if (REPEAT_CAL)
      {
        // Delete if we want to re-calibrate
        SD.remove(CALIBRATION_FILE);
      }
      else
      {
        File f = SD.open(CALIBRATION_FILE, "r");
        if (f) {
          if (f.readBytes((char *)calData, 14) == 14)
            calDataOK = 1;
          f.close();
        }
      }
    }
  }*/
 // else  // SPIFFS uses
  //{
    // check file system exists
    if (!SPIFFS.begin()) {
      Serial.println("Formating file system");
      SPIFFS.format();
      SPIFFS.begin();
    }

    // check if calibration file exists and size is correct
    if (SPIFFS.exists(CALIBRATION_FILE)) {
      if (REPEAT_CAL)
      {
        // Delete if we want to re-calibrate
        SPIFFS.remove(CALIBRATION_FILE);
      }
      else
      {
        File f = SPIFFS.open(CALIBRATION_FILE, "r");
        if (f) {
          if (f.readBytes((char *)calData, 14) == 14)
            calDataOK = 1;
          f.close();
        }
      }
    }
  //}

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
    Serial.print(calData[1]);
    Serial.print(",");
    Serial.print(calData[2]);
    Serial.print(",  ");
    Serial.print(calData[3]);
    Serial.print(",");
    Serial.print(calData[4]);
    Serial.print(",  ");
    Serial.print(calData[5]);
    Serial.print(",");
    Serial.print(calData[6]);
    Serial.print(",  ");
    Serial.print(calData[7]);
    Serial.print(",");
    Serial.println(calData[8]);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
  /*  if (existSD) {
      File f = SD.open(CALIBRATION_FILE, "w");
      if (f) {
        f.write((const unsigned char *)calData, 14);
        f.close();
      }
    }*/
   // else {
      File f = SPIFFS.open(CALIBRATION_FILE, "w");
      if (f) {
        f.write((const unsigned char *)calData, 14);
        f.close();
      }
    }

  }
//}


//####################################################################################################
// button ********** TFT_eSPI touch **********
//####################################################################################################
void buttons()
{
  int defcolor = ConvertRGBto565(255, 255,255);
  tft.setRotation(1);
  tft.fillScreen(defcolor);
  // Draw the keys
  tft.setFreeFont(LABEL1_FONT);
  char keyLabel[totalButtonNumber][10] = {"M.", "A.","<"," "};
  key[0].initButton(&tft, 180, 280, 120, 60, TFT_BLACK, TFT_WHITE, TFT_RED, keyLabel[0] ,0.5 ); // x, y, w, h, outline, fill, color, label, text_Size
  key[0].drawButton();
  key[1].initButton(&tft, 335, 280, 120, 60, TFT_BLACK, TFT_WHITE, TFT_BLUE, keyLabel[1] , 0.5 );
  key[1].drawButton();
  key[2].initButton(&tft, 30, 160, 50, 300, TFT_WHITE, TFT_WHITE, 0x989596, keyLabel[2] , 2);
  key[2].drawButton();
  key[3].initButton(&tft, 430, 160, 35, 35, TFT_BLACK, TFT_WHITE, TFT_GREEN, keyLabel[3] , 0.5);
  key[3].drawButton();
}
void buttons0()
{
  int defcolor = ConvertRGBto565(255, 255,255);
  tft.setRotation(1);
  tft.fillScreen(defcolor);
  // Draw the keys
  tft.setFreeFont(LABEL1_FONT);
  char key0Label[totalButtonNumber0][33] = {"RUTINA 1","RUTINA 2","RUTINA 3","RUTINA 4"};
  key0[0].initButton(&tft, 240, 40, 400, 60, TFT_BLACK, TFT_WHITE, TFT_BLACK, key0Label[0] ,0.5 ); // x, y, w, h, outline, fill, color, label, text_Size
  key0[0].drawButton();
  key0[1].initButton(&tft, 240, 120, 400, 60, TFT_BLACK, TFT_WHITE, TFT_BLACK, key0Label[1] , 0.5 );
  key0[1].drawButton();
  key0[2].initButton(&tft, 240, 200, 400, 60, TFT_BLACK, TFT_WHITE, TFT_BLACK, key0Label[2] , 0.5 );
  key0[2].drawButton();
  key0[3].initButton(&tft, 240, 280, 400, 60, TFT_BLACK, TFT_WHITE, TFT_BLACK, key0Label[3] , 0.5 );
  key0[3].drawButton();
}

//####################################################################################################
// Print status text
//####################################################################################################
void status(const char *msg) {
  int defcolor = ConvertRGBto565(255, 255, 255);
  tft.setTextPadding(80);
  tft.setTextColor(TFT_BLACK, defcolor);
tft.drawString(msg, 80, 20);
}
int ConvertRGBto565(byte rr, byte gg, byte bb)
{
  //reduz para 5 bits significativos
  byte r = (byte) (rr >> 3);
  //reduz para 6 bits significativos
  byte g = (byte)(gg >> 2);
  //reduz para 5 bits significativos
  byte b = (byte)(bb >> 3);

  //Junta
  return (int)((r << 11) | (g << 5) | b);
}
/*
void loop2(void *pvParameters){
  for(;;){
   //if(f1==0){

//}
  }}*/