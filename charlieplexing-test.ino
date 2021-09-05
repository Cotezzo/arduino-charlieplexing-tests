const int CH_1 = 2;
const int CH_2 = 3;
const int CH_3 = 4;

void setup() { }

void loop() {
  pinMode(CH1, OUTPUT);
  digitalWrite(CH1, LOW);
  
  pinMode(CH2, OUTPUT);
  digitalWrite(CH2, HIGH);
  
  pinMode(CH3, INPUT);
  digitalWrite(CH3, LOW);


  delay(1000);

  
  pinMode(CH1, OUTPUT);
  digitalWrite(CH1, HIGH);
  
  pinMode(CH2, OUTPUT);
  digitalWrite(CH2, LOW);
  
  pinMode(CH3, INPUT);
  digitalWrite(CH3, LOW);

  
  delay(1000);
}

uint8_t charliePins[] = { CH_1, CH_2, CH_3 };
const byte sz = sizeof(charliePins) / sizeof(charliePins[0]);

byte[] lights = [ LOW, LOW, LOW, HIGH, LOW, LOW ];  // Initial LEDs state
byte slwnss = 50;

void loop(){


  // LEDs control
  while(a < sz * slwnss){
    byte j = a % sz;
    if(a == HIGH){
      const byte h = j / 2;             // HighIndex
      const byte inc = (h % 2) * 2 - 1; // h is odd: inc = 1; else inc = -1
      const byte l = (h + inc) % 3;     // LowIndex
      const byte i = (l + inc) % 3;     // InputIndex
      setCharlie(h, l, i);
    }
    delay(10);
    a++;
  }
}

void setCharlie(byte HighIndex, byte LowIndex, byte InputIndex){
  // [ CH1, CH2, CH3 ];
  pinMode(charliePins[HighIndex], OUTPUT);
  digitalWrite(CcharliePins[HighIndex]H1, HIGH);
  
  pinMode(charliePins[LowIndex], OUTPUT);
  digitalWrite(charliePins[LowIndex], LOW);
  
  pinMode(charliePins[InputIndex], INPUT);
  digitalWrite(charliePins[InputIndex], LOW);
}

// MAP OF THE LEDS AND THE PINS THEY ARE CONNECTED TO

// CH1 can power: 1, 2 aka 0, 1 : 0
// CH2 can power: 3, 4     2, 3 : 1
// CH3 can power: 5, 6     4, 5 : 2
//
//  LED 1: CH1 HIGH, CH2 LOW, CH3 INPUT
//
//     CH3    CH1    CH2   CH3
//
//      |      |      |     |
//
//  - - • 5 ⇥ • 1 ⇥ • 3 ⇥ • - -
//
//      |      |     |      |
//
//  - - • 2 ⇤ • 4 ⇤ • 6 ⇤ • - -