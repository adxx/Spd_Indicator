/*

*/
#define ON 0
#define OFF 1

#define MinDim 5
#define MinLight 70

char inp_01;
char inp_02;
char inp_03;
char inp_04;
char inp_05;
char inp_06;
char inp_07;
char inp_08;
char inp_09;
char inp_10;
int dimmer = 0;
char sync = 85;
char spd = 0;
char dim = 128;
char inv_spd;
char inv_dim;



void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
}

void loop() {
  // print the string when a newline arrives:
      InputRead();
      inv_spd = ~ spd;
      inv_dim = ~ dim;
      Serial.print(sync);
      Serial.print(spd);
      Serial.print(dim);
      Serial.print(inv_spd);
      Serial.print(inv_dim);
     
      delay(100);
      
    
}

void InputRead() {
    spd = 0;
    inp_01 = digitalRead(11); //S1
    inp_02 = digitalRead(9);  //S2
    inp_03 = digitalRead(7);  //S3
    inp_04 = digitalRead(5);  //S4
    inp_05 = digitalRead(4);  //SLU
    inp_06 = digitalRead(12); //резерв
    dimmer = analogRead(A0); //читаем значение 10 бит
    dimmer = (dimmer)/4; //приводим к 8бит
    dimmer = 255 - dimmer; //
    if (dimmer < MinLight) {
      dim = MinDim;
    }
    if (dimmer > MinLight) {
      dim = dimmer;
    }
    if(inp_01 == OFF & inp_02 == OFF & inp_03 == OFF & inp_04 == OFF) {
      spd = 0;
    }
    if(inp_01 == OFF & inp_02 == ON & inp_03 == ON & inp_04 == ON) {
      spd = 1;
    }
    if(inp_01 == ON & inp_02 == ON & inp_03 == ON & inp_04 == ON) {
      spd = 2;
    }
    if(inp_01 == ON & inp_02 == OFF & inp_03 == ON & inp_04 == ON) {
      spd = 3;
    }
    if(inp_01 == ON & inp_02 == OFF & inp_03 == OFF & inp_04 == ON) {
      spd = 4;
    }
    if(inp_01 == ON & inp_02 == OFF & inp_03 == OFF & inp_04 == OFF) {
      spd = 5;
    }
    if(inp_01 == ON & inp_02 == ON & inp_03 == OFF & inp_04 == OFF) {
      spd = 6;
    }
    if(inp_05 == ON) { //добавляем индикатор Lock-UP если включен. 
      spd = spd + 10;
    }
    
}
