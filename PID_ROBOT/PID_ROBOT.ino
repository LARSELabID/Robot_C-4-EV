#define ENCODER_AC 12 // Pin for Encoder A
#define ENCODER_BC 14 // Pin for Encoder B
#define ENCODER_AH 27 // Pin for Encoder A
#define ENCODER_BH 26 // Pin for Encoder B
#define ENCODER_ACO 16 // Pin for Encoder A
#define ENCODER_BCO 17 // Pin for Encoder B
#define ENCODER_AM 33 // Pin for Encoder A
#define ENCODER_BM 32 // Pin for Encoder B
volatile int encoderc_value = 0;
volatile int encoderh_value = 0;
volatile int encoderco_value = 0;
volatile int encoderm_value = 0;
const int dirc=22;
const int pinstepc = 23;
const int dirh=19;
const int pinsteph = 18;
const int dirco=5;
const int pinstepco = 0;
const int dirm1=4;
const int pinstepm1 = 25;
const int dirm2=15;
const int pinstepm2 = 13;
const int dire=21;
const int pinstepe = 2;
float dtc = 0.000001;
float kpSc =8;
float kiSc = 3.5;
float kdSc = 0;
float Nc = 50;
float  errorc;
float  x1c = 0;  // Inicialización de x1
float  x2c = 0;  // Inicialización de x2
float SP_C=0,SP_H=0,SP_CO=0,SP_M=0;
float k1c, k2c, derrorc, ierrorc, cvc;
float dth = 0.000001;
float kpSh =5;
float kiSh = 2;
float kdSh = 0;
float Nh = 40;
float  errorh;
float  x1h = 0;  // Inicialización de x1
float  x2h = 0;  // Inicialización de x2
float k1h, k2h, derrorh, ierrorh, cvh;
float dtco = 0.000001;
float kpSco =5;
float kiSco = 2;
float kdSco = 0;
float Nco = 40;
float  errorco;
float  x1co = 0;  // Inicialización de x1
float  x2co = 0;  // Inicialización de x2
float k1co, k2co, derrorco, ierrorco, cvco;
float dtm = 0.000001;
float kpSm =5;
float kiSm = 2;
float kdSm = 0;
float Nm = 40;
float  errorm;
float  x1m = 0;  // Inicialización de x1
float  x2m = 0;  // Inicialización de x2
float k1m, k2m, derrorm, ierrorm, cvm;
int stepdelay =750;
int fm=0;
int giro,giro2;
int efector,efector2;
int paro=0; 
void IRAM_ATTR encoder_cadera() {
  int Ac = digitalRead(ENCODER_AC);
  int Bc = digitalRead(ENCODER_BC);
    if ((Ac == HIGH) != (Bc == LOW)) {
      encoderc_value--;
    } else {
        encoderc_value++;
      }
}
void IRAM_ATTR encoder_hombro() {
  int Ah = digitalRead(ENCODER_AH);
  int Bh = digitalRead(ENCODER_BH);
    if ((Ah == HIGH) != (Bh == LOW)) {
      encoderh_value--;
    } else {
      encoderh_value++;
      }
}
void  IRAM_ATTR encoder_codo() {
  int Aco = digitalRead(ENCODER_ACO);
  int Bco = digitalRead(ENCODER_BCO);
  if ((Aco == HIGH) != (Bco == LOW)) {
    encoderco_value++;
  } else {
    encoderco_value--;
  }
}
void IRAM_ATTR encoder_muneca() {
  if(fm==0){
  int Am = digitalRead(ENCODER_AM);
  int Bm = digitalRead(ENCODER_BM);
  if ((Am == HIGH) != (Bm == LOW)) {
    encoderm_value--;
  } else {
    encoderm_value++;
  }
}}
void setup() {
Serial.begin(115200);
//xTaskCreatePinnedToCore(loop2, "Task_2", 10000, NULL, 1, NULL,  1); 
//delay(500);
//miServo.attach(pinServo);
//pinMode(pinServo,OUTPUT);
pinMode(dirc,OUTPUT);
pinMode(pinstepc,OUTPUT);
pinMode(dirh,OUTPUT);
pinMode(pinsteph,OUTPUT);
pinMode(dirco,OUTPUT);
pinMode(pinstepco,OUTPUT);
pinMode(dirm1,OUTPUT);
pinMode(pinstepm1,OUTPUT);
pinMode(dirm2,OUTPUT);
pinMode(pinstepm2,OUTPUT);
pinMode(dire,OUTPUT);
pinMode(pinstepe,OUTPUT);
pinMode(ENCODER_AC, INPUT_PULLUP);
pinMode(ENCODER_BC, INPUT_PULLUP);
pinMode(ENCODER_AH, INPUT_PULLUP);
pinMode(ENCODER_BH, INPUT_PULLUP);
pinMode(ENCODER_ACO, INPUT_PULLUP);
pinMode(ENCODER_BCO, INPUT_PULLUP);
pinMode(ENCODER_AM, INPUT_PULLUP);
pinMode(ENCODER_BM, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(ENCODER_AC), encoder_cadera, CHANGE);
attachInterrupt(digitalPinToInterrupt(ENCODER_AH), encoder_hombro, CHANGE);
attachInterrupt(digitalPinToInterrupt(ENCODER_ACO), encoder_codo, CHANGE);
attachInterrupt(digitalPinToInterrupt(ENCODER_AM), encoder_muneca, CHANGE);
}

void loop() {
  if (Serial.available() > 0){
    if(Serial.read() == 'e'){
    paro=1;
    SP_C=encoderc_value*0.3;
    SP_H=encoderh_value*0.3;
    SP_CO=encoderco_value*0.3; 
    SP_M=encoderm_value*0.3;
    giro=giro2; 
    efector=efector2; 
    }
    if (Serial.read() == 'r') {
    paro=0;
    SP_C = Serial.parseInt();
    SP_H = Serial.parseInt();
    SP_CO = Serial.parseInt();
    SP_M = Serial.parseInt();
    giro = Serial.parseInt();
    efector = Serial.parseInt();
    }
  } 
  if(paro == 0 ){
  PID_cadera();
  PID_hombro();
  PID_codo();
  PID_muneca();
    if ((errorco<2.4 && errorco>-2.4) && (errorh<2.4&&errorh>-2.4) && (errorc<2.4&& errorc>-2.4)&&(errorm<2.4 && errorm>-2.4)){
      if(giro>giro2){
      fm=1;
      digitalWrite(dirm1,HIGH);
      digitalWrite(pinstepm1,HIGH);
      delayMicroseconds(stepdelay);
      digitalWrite(pinstepm1,LOW);
      delayMicroseconds(stepdelay);
      digitalWrite(dirm2,LOW);
      digitalWrite(pinstepm2,HIGH);
      delayMicroseconds(stepdelay);
      digitalWrite(pinstepm2,LOW);
      delayMicroseconds(stepdelay);
      giro2=giro2+1;
      }
    fm=0;
      if(giro<giro2){
      fm=1;
      digitalWrite(dirm1,LOW);
      digitalWrite(pinstepm1,HIGH);
      delayMicroseconds(stepdelay);
      digitalWrite(pinstepm1,LOW);
      delayMicroseconds(stepdelay);
      digitalWrite(dirm2,HIGH);
      digitalWrite(pinstepm2,HIGH);
      delayMicroseconds(stepdelay);
      digitalWrite(pinstepm2,LOW);
      delayMicroseconds(stepdelay);
      giro2=giro2-1;
      }
fm=0;
if(efector>efector2){
  digitalWrite(dire,HIGH);
  digitalWrite(pinstepe,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinstepe,LOW);
  delayMicroseconds(stepdelay);
  efector2=efector2+1;
}
if(efector<efector2){
  digitalWrite(dire,LOW);
  digitalWrite(pinstepe,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinstepe,LOW);
  delayMicroseconds(stepdelay);
  efector2=efector2-1;
}
  }
}}
/*
void loop2(void * parameter){
  for(;;){
  miServo.write(mano); 
}}*/
void PID_muneca(){
    errorm= SP_M - encoderm_value*0.3;
  if (errorm>2.4|| errorm<-2.4){
 k1m = Nm * (-x1m + errorm);
  derrorm = k1m;
  x1m = x1m + k1m * dtm;

  // Calcular k2
  k2m = errorm;
  ierrorm = x2m;
  x2m = x2m + k2m * dtm;

  // Calcular control proporcional, integral y derivativo
  cvm = kpSm * errorm + kiSm * ierrorm + kdSm * derrorm;
  }
if(cvm<0){
  digitalWrite(dirm1,LOW);
  digitalWrite(pinstepm1,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinstepm1,LOW);
  delayMicroseconds(stepdelay);
  digitalWrite(dirm2,LOW);
  digitalWrite(pinstepm2,HIGH);
  delayMicroseconds(800);
  digitalWrite(pinstepm2,LOW);
  delayMicroseconds(800);
}
if(cvm>0){
  digitalWrite(dirm1,HIGH);
  digitalWrite(pinstepm1,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinstepm1,LOW);
  delayMicroseconds(stepdelay);
  digitalWrite(dirm2,HIGH);
  digitalWrite(pinstepm2,HIGH);
  delayMicroseconds(800);
  digitalWrite(pinstepm2,LOW);
  delayMicroseconds(800);
}
cvm=0;
}
void PID_codo(){
  errorco= SP_CO - encoderco_value*0.3;
  if (errorco>2.4|| errorco<-2.4){
 k1co = Nco * (-x1co + errorco);
  derrorco = k1co;
  x1co = x1co + k1co * dtco;

  // Calcular k2
  k2co = errorco;
  ierrorco = x2co;
  x2co = x2co + k2co * dtco;

  // Calcular control proporcional, integral y derivativo
  cvco = kpSco * errorco + kiSco * ierrorco + kdSco * derrorco;
    }
if(cvco>0){
  digitalWrite(dirco,LOW);
  digitalWrite(pinstepco,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinstepco,LOW);
  delayMicroseconds(stepdelay);
}
if(cvco<0){
 digitalWrite(dirco,HIGH);
  digitalWrite(pinstepco,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinstepco,LOW);
 delayMicroseconds(stepdelay);
}
cvco=0;
}
void PID_hombro(){
  errorh= SP_H - encoderh_value*0.3;
  if (errorh>2.4|| errorh<-2.4){
 k1h = Nh * (-x1h + errorh);
  derrorh = k1h;
  x1h = x1h + k1h * dth;

  // Calcular k2
  k2h = errorh;
  ierrorh = x2h;
  x2h = x2h + k2h * dth;

  // Calcular control proporcional, integral y derivativo
  cvh =  kpSh * errorh + kiSh * ierrorh + kdSh * derrorh;
  }
if(cvh<0){
  digitalWrite(dirh,LOW);
  digitalWrite(pinsteph,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinsteph,LOW);
  delayMicroseconds(stepdelay);
}
if(cvh>0){
 digitalWrite(dirh,HIGH);
  digitalWrite(pinsteph,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinsteph,LOW);
 delayMicroseconds(stepdelay);
}
cvh=0;
}
void PID_cadera(){
  errorc= SP_C - encoderc_value*0.3;
  if (errorc>2.4|| errorc<-2.4){
  // Calcular k1
  k1c = Nc * (-x1c + errorc);
  derrorc = k1c;
  x1c = x1c + k1c * dtc;

  // Calcular k2
  k2c = errorc;
  ierrorc = x2c;
  x2c = x2c + k2c * dtc;

  // Calcular control proporcional, integral y derivativo
  cvc = kpSc * errorc + kiSc * ierrorc + kdSc * derrorc;
  }
  
if(cvc<0){
  digitalWrite(dirc,LOW);
  digitalWrite(pinstepc,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinstepc,LOW);
  delayMicroseconds(stepdelay);
}
if(cvc>0){
 digitalWrite(dirc,HIGH);
 digitalWrite(pinstepc,HIGH);
  delayMicroseconds(stepdelay);
  digitalWrite(pinstepc,LOW);
 delayMicroseconds(stepdelay);
}
cvc=0;
}