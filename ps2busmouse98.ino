#include <MsTimer2.h>

#define PS2DATA A4
#define PS2CLK A5
#define LED PD0
#define XA PD2
#define XB PD3
#define YA PD4
#define YB PD5
#define LB PD6
#define RB PD7
#define ERROR_NUM 3

#define DEBUG

int error_f = 0;
int error_cnt = 0;

void watchdog() {
  if (error_cnt >= ERROR_NUM) {
    error_f = 1;
    error_cnt = 0;
#ifdef DEBUG
    Serial.println("Watch Dog Error!");
#endif
  }
  else {
    error_cnt++;
  }
}

void sendData(char tdata) {
  int clk_val = 0;
  int tbit = 0;
  int tparity = 0;

  digitalWrite(PS2CLK, LOW);
  digitalWrite(PS2DATA, LOW);
  pinMode(PS2CLK, OUTPUT);

  delayMicroseconds(200);
  pinMode(PS2DATA, OUTPUT);

  delayMicroseconds(200);
  pinMode(PS2CLK, INPUT);

  // Data
  for (int i=0; i<8; i++) {
    clk_val = digitalRead(PS2CLK);
    while (clk_val) {
      clk_val = digitalRead(PS2CLK);
      delayMicroseconds(5);
      if (error_f) {
        break;
      }
    }
    tbit = tdata & 0x01;
    tparity = tparity ^ tbit;
    if (tbit) {
      pinMode(PS2DATA, INPUT);
    }
    else {
      pinMode(PS2DATA, OUTPUT);
    }
    tdata = (tdata >> 1);
    while (!clk_val) {
      clk_val = digitalRead(PS2CLK);
      delayMicroseconds(5);
      if (error_f) {
        break;
      }
    }
  }

  // Parity
  clk_val = digitalRead(PS2CLK);
  while (clk_val) {
    clk_val = digitalRead(PS2CLK);
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }
  if (tparity) {
    pinMode(PS2DATA, OUTPUT);
  }
  else {
    pinMode(PS2DATA, INPUT); // odd parity
  }
  while (!clk_val) {
    clk_val = digitalRead(PS2CLK);    
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }

  // Stop
  clk_val = digitalRead(PS2CLK);
  while (clk_val) {
    clk_val = digitalRead(PS2CLK);
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }
  pinMode(PS2DATA, INPUT);
  while (!clk_val) {
    clk_val = digitalRead(PS2CLK);    
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }

  // Ack
  clk_val = digitalRead(PS2CLK);
  while (clk_val) {
    clk_val = digitalRead(PS2CLK);
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }
  while (!clk_val) {
    clk_val = digitalRead(PS2CLK);    
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(PS2DATA, INPUT);
  pinMode(PS2CLK, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(XA, INPUT);
  pinMode(XB, INPUT);
  pinMode(YA, INPUT);
  pinMode(YB, INPUT);
  pinMode(LB, INPUT);
  pinMode(RB, INPUT);
  digitalWrite(XA, LOW);
  digitalWrite(XB, LOW);
  digitalWrite(YA, LOW);
  digitalWrite(YB, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(RB, LOW);
  MsTimer2::set(1, watchdog);
  sendData(0xF4);
  delay(10);
}

int receiveData(void) {
  int data = 0;
  int clk_val = 0;
  int data_val[8];
  int parity = 0;

  // Start
  clk_val = digitalRead(PS2CLK);
  while (clk_val) {
    clk_val = digitalRead(PS2CLK);
    delayMicroseconds(5);
  }

  MsTimer2::start();

  // Data
  for (int i=0; i<8; i++) {
    clk_val = digitalRead(PS2CLK);
    while (!clk_val) {
      clk_val = digitalRead(PS2CLK);
      delayMicroseconds(5);
      if (error_f) {
        break;
      }
    }
    while (clk_val) {
      clk_val = digitalRead(PS2CLK);
      delayMicroseconds(5);
      if (error_f) {
        break;
      }
    }
    data_val[i] = digitalRead(PS2DATA);
  }

  // Parity
  clk_val = digitalRead(PS2CLK);
  while (!clk_val) {
    clk_val = digitalRead(PS2CLK);
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }
  while (clk_val) {
    clk_val = digitalRead(PS2CLK);    
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }
  parity = digitalRead(PS2DATA);
  digitalWrite(LED, HIGH);
  delayMicroseconds(5);
  digitalWrite(LED, LOW);

  // Stop
  clk_val = digitalRead(PS2CLK);
  while (!clk_val) {
    clk_val = digitalRead(PS2CLK);
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }
  while (clk_val) {
    clk_val = digitalRead(PS2CLK);    
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }
  digitalWrite(LED, HIGH);
  delayMicroseconds(5);
  digitalWrite(LED, LOW);  
  while (!clk_val) {
    clk_val = digitalRead(PS2CLK);
    delayMicroseconds(5);
    if (error_f) {
      break;
    }
  }

  for (int i=0; i<8; i++) {
    data = data |(data_val[i] << i);
  }

  return data;
}

void loop() {
  int data = 0;
  static int data_cnt = 0;
  static int stateX = 0;
  static int stateY = 0;
  static int stateB = 0;
  static int dataX = 0;
  static int dataY = 0;

  data = receiveData();

  MsTimer2::stop();
  error_f = 0;
  error_cnt = 0;

  if (data_cnt == 0) {
    if (data & 0x01) {
      stateB = stateB | 0x01;
    }
    else {
      stateB = stateB & 0xFE;
    }
    if (data & 0x02) {
      stateB = stateB | 0x02;
    }
    else {
      stateB = stateB & 0xFD;
    }
    if (data & 0x10) {
      stateX = stateX | 0x10;
    }
    else {
      stateX = stateX & 0xEF;
    }
    if (data & 0x20) {
      stateY = stateY | 0x20;
    }
    else {
      stateY = stateY & 0xDF;
    }
    data_cnt++;
  }
  else if (data_cnt == 1) {

    if ((stateX & 0x10) && data) {
      dataX = 256 - data;
    }
    else {
      dataX = data;
    }
    data_cnt++;
  }
  else if (data_cnt == 2) {

    if ((stateY & 0x20) && data) {
      dataY = 256 - data;
    }
    else {
      dataY = data;
    }

#ifdef DEBUG
    Serial.print("X:");
    Serial.print(dataX, HEX);
    Serial.print("Y:");
    Serial.println(dataY, HEX);
#endif

    switch (stateB) {
      case 0x00:
        pinMode(LB, INPUT);
        pinMode(RB, INPUT);
        break;
      case 0x01:
        pinMode(LB, OUTPUT);
        pinMode(RB, INPUT);
        break;
      case 0x02:
        pinMode(LB, INPUT);
        pinMode(RB, OUTPUT);
        break;
      case 0x03:
        pinMode(LB, OUTPUT);
        pinMode(RB, OUTPUT);
        break;
    }

    while (dataX) {
      switch (stateX) {
        case 0x00:
          stateX = 0x01;
          pinMode(XA, OUTPUT);
          pinMode(XB, INPUT);
          break;
        case 0x01:
          stateX = 0x03;
          pinMode(XA, OUTPUT);
          pinMode(XB, OUTPUT);
          break;
        case 0x03:
          stateX = 0x02;
          pinMode(XA, INPUT);
          pinMode(XB, OUTPUT);
          break;
        case 0x02:
          stateX = 0x00;
          pinMode(XA, INPUT);
          pinMode(XB, INPUT);
          break;
        case 0x10:
          stateX = 0x12;
          pinMode(XA, INPUT);
          pinMode(XB, OUTPUT);
          break;
        case 0x12:
          stateX = 0x13;
          pinMode(XA, INPUT);
          pinMode(XB, OUTPUT);
          break;
        case 0x13:
          stateX = 0x11;
          pinMode(XA, OUTPUT);
          pinMode(XB, INPUT);
          break;
        case 0x11:
          stateX = 0x00;
          pinMode(XA, OUTPUT);
          pinMode(XB, OUTPUT);
          break;
        default:
          stateX = 0x00;
      }
      dataX--;   
      //delayMicroseconds(5);
    }

    while (dataY) {
      switch (stateY) {
        case 0x00:
          stateY = 0x01;
          pinMode(YA, OUTPUT);
          pinMode(YB, INPUT);
          break;
        case 0x01:
          stateY = 0x03;
          pinMode(YA, OUTPUT);
          pinMode(YB, OUTPUT);
          break;
        case 0x03:
          stateY = 0x02;
          pinMode(YA, INPUT);
          pinMode(YB, OUTPUT);
          break;
        case 0x02:
          stateY = 0x00;
          pinMode(YA, INPUT);
          pinMode(YB, INPUT);
          break;
        case 0x10:
          stateY = 0x12;
          pinMode(YA, INPUT);
          pinMode(YB, OUTPUT);
          break;
        case 0x12:
          stateY = 0x13;
          pinMode(YA, OUTPUT);
          pinMode(YB, OUTPUT);
          break;
        case 0x13:
          stateY = 0x11;
          pinMode(YA, OUTPUT);
          pinMode(YB, INPUT);
          break;
        case 0x11:
          stateY = 0x00;
          pinMode(YA, INPUT);
          pinMode(YB, INPUT);
          break;
        default:
          stateY = 0x00;
      }
      dataY--;
      //delayMicroseconds(5);
    }
    data_cnt = 0;
  } 
  delayMicroseconds(5);

}

