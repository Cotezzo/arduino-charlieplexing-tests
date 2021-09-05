const int CH_1 = 5;
const int CH_2 = 6;
const int CH_3 = 7;

uint8_t charliePins[] = { CH_1, CH_2, CH_3 };

byte lights[6];
// byte lights[] = { HIGH, HIGH, LOW, LOW, LOW, LOW };  // Initial LEDs state
const byte sz = sizeof(lights) / sizeof(lights[0]);

byte slwnss = 15;

// SETUP
void setup() {
  Serial.begin(9600);  
}

// LOOP
void loop(){
  updateLights(HIGH, LOW, LOW, LOW, LOW, LOW);
  draw();
  
  updateLights(LOW, HIGH, LOW, LOW, LOW, LOW);
  draw();
  
  updateLights(LOW, LOW, HIGH, LOW, LOW, LOW);
  draw();
  
  updateLights(LOW, LOW, LOW, HIGH, LOW, LOW);
  draw();
  
  updateLights(LOW, LOW, LOW, LOW, HIGH, LOW);
  draw();
  
  updateLights(LOW, LOW, LOW, LOW, LOW, HIGH);
  draw();
}

// MAP OF THE LEDS AND THE PINS THEY ARE CONNECTED TO

// CH1 can power: 1, 2 aka 0, 1 : 0
// CH2 can power: 3, 4     2, 3 : 1
// CH3 can power: 5, 6     4, 5 : 2
//
//     CH3    CH1    CH2   CH3
//
//      |      |      |     |
//
//  - - • 6 ⇥ • 2 ⇥ • 4 ⇥ • - -
//
//      |      |     |      |
//
//  - - • 1 ⇤ • 3 ⇤ • 5 ⇤ • - -

void updateLights(byte l1, byte l2, byte l3, byte l4, byte l5, byte l6){
  lights[0] = l1;
  lights[1] = l2;
  lights[2] = l3;
  lights[3] = l4;
  lights[4] = l5;
  lights[5] = l6;
}

void draw(){
  byte a  = 0;
  while(a < sz * slwnss){
    byte j = a % sz;
    if(lights[j] == HIGH){
      const byte h = j / 2;             // HighIndex
      const byte inc = a % 2 ? 1 : 2;
      const byte l = (h + inc) % 3;     // LowIndex
      const byte i = (l + inc) % 3;     // InputIndex
      setCharlie(h, l, i);
      delay(50);
    }
    a++;
  }  
}

// SET CHARLIE PINS
void setCharlie(byte HighIndex, byte LowIndex, byte InputIndex){
  // [ CH1, CH2, CH3 ];
  pinMode(charliePins[HighIndex], OUTPUT);
  digitalWrite(charliePins[HighIndex], HIGH);
  
  pinMode(charliePins[LowIndex], OUTPUT);
  digitalWrite(charliePins[LowIndex], LOW);
  
  pinMode(charliePins[InputIndex], INPUT);
  digitalWrite(charliePins[InputIndex], LOW);
}
