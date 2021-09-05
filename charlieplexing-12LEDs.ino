//                 LEDS MAP AND PINS THEY ARE CONNECTED TO
//
//     CH1    CH2   CH3    CH4    CH1         CH1   CH3      CH2   CH4
//
//      |      |     |      |      |           |     |        |     |
//
//  - - • 1 ⇥ • 2 ⇥ • 3 ⇥ • 4 ⇥ • - -       • 5 ⇥ •       • 6 ⇥ •
//
//      |      |     |      |      |           |     |        |     |
//
//  - - • 7 ⇤ • 8 ⇤ • 9 ⇤ • 10⇤ • - -       • 11⇤ •       • 12⇤ •

// CHARLIE PINS DECLARATION, LEDS DECLARATION
const int CH_1 = 2;
const int CH_2 = 3;
const int CH_3 = 4;
const int CH_4 = 5;

uint8_t charliePins[] = { CH_1, CH_2, CH_3, CH_4 };
const byte charliePinsSize = sizeof(charliePins)/sizeof(charliePins[0]);
  
byte lights[12];
const byte lightsSize = sizeof(lights) / sizeof(lights[0]);

byte slowness = 25;                                                       // Parameter for "frame" speed / frequency


void setup() {}

void loop(){
  const byte d[] = { 0, 2, 4, 7, 9, 11 };
  draw(d, sizeof(d)/sizeof(d[0]));
 
  const byte d2[] = { 1, 3, 5, 6, 8, 10 };
  draw(d2, sizeof(d2)/sizeof(d2[0]));
}

void draw(byte lightLEDs[], byte s){
  byte count = 0;
  do{                                                                     // Light the LEDs up slowness times (wait more before changing set of LEDs)
    count++;
    for(int i = 0; i < s; i++){                                           // For every light up LED, set Charlieplex properly
      const byte LED_ID = lightLEDs[i];                                   // Get the LED_ID from the lighted LEDs array
      const byte t = LED_ID % 6;                                          // Normalize (get two endpoints of the LED, flow direction is handled here: --| )
      const byte Vcc = t % 4;                                             // Get the first CH pin                                                       |
      const byte GND = (Vcc + (t > 3 ? 2 : 1)) % 4;                       // Get the second CH pin                                                     \ /
      if(LED_ID < 6)                                                      // Every connection has two possible flows, handled as 2 rows here. Based on the index, choose the row.
        setCharlies(Vcc, GND);
      else
        setCharlies(GND, Vcc);
      delay(2);
    }
  }while(count < slowness);
}

// SET CHARLIE PINS
void setCharlies(byte HighIndex, byte LowIndex){
  // [ CH1, CH2, CH3, CH4 ];
  byte i = 0;
  while(i < charliePinsSize){
    if(i == HighIndex)
      setCharlie(i, OUTPUT, HIGH);
    else if(i == LowIndex)
      setCharlie(i, OUTPUT, LOW);
    else
      setCharlie(i, INPUT, LOW);
    i++;
  }
}

void setCharlie(byte i, byte IO, byte HL){
  pinMode(charliePins[i], IO);
  digitalWrite(charliePins[i], HL);
}


//void updateLights(byte states[]){
//  byte i = 0;
//  const byte s = sizeof(states)/sizeof(states[0]);
//  while(i < 12){
//    lights[i] = states[i];
//    i++;
//  }
//}

//void oldDraw(){
//  byte a  = 0;
//  
//  while(a < lightsSize * slwnss){
//    const byte j = a % lightsSize;
//    if(lights[j] == HIGH){
//      const byte t = j % 6;
//      const byte high = t % 4;
//      const byte low = (high + (t > 3 ? 2 : 1)) % 4;
//      if(j < 6)
//        setCharlies(high, low);
//      else
//        setCharlies(low, high);
//    }
//    a++;
//    delay(200);
//  }
//}
