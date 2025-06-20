#include <IRremote.hpp>

constexpr int pinIrSend = 3;
constexpr int pinCmdAmpPower = 4;
constexpr int pinCmdAmpVolUp = 5;
constexpr int pinCmdAmpVolDn = 6;
constexpr int pinCmdTvPower = 7;

constexpr int DELAY_AFTER_SEND = 2000;
constexpr int FREQ_KHZ = 38;

constexpr int AMP_ADDR = 0x1D00;
constexpr int AMP_POWER = 0xB9;
constexpr int AMP_VOLUP = 0xD9;
constexpr int AMP_VOLDN = 0x59;

constexpr int TV_ADDR = 0x20DF;
constexpr int TV_POWER = 0x10;

int lastAmpPower = 0;
int lastVolUp = 0;
int lastVolDown = 0;
int lastTvPower = 0;

void setup() {

  pinMode(pinIrSend, OUTPUT);

  IrSender.begin(pinIrSend);
  IrSender.enableIROut(FREQ_KHZ);

  pinMode(pinCmdAmpPower, INPUT);
  pinMode(pinCmdAmpVolUp, INPUT);
  pinMode(pinCmdAmpVolDn, INPUT);
  pinMode(pinCmdTvPower, INPUT);

  Serial.begin(115200);
  Serial.println("Start");
}

int last=0;

void loop() {
    //last = !last;
    //digitalWrite(pinIrSend, last);

    int valAmpPower = 1;// digitalRead(pinCmdAmpPower);
    int valVolUp = digitalRead(pinCmdAmpVolUp);
    int valVolDown = digitalRead(pinCmdAmpVolDn);
    int valTvPower = digitalRead(pinCmdTvPower);

    if(valAmpPower == 1 && valAmpPower != lastAmpPower) {
      Serial.println("AMP_POWER");
      IrSender.sendNEC(AMP_ADDR, AMP_POWER, 1);
      delay(DELAY_AFTER_SEND);    
    }

    if(valVolUp == 1 && valVolUp != lastVolUp) {
      Serial.println("AMP_VOLUP");
      IrSender.sendNEC(AMP_ADDR, AMP_VOLUP, 1);
      delay(DELAY_AFTER_SEND);    
    }

    if(valVolDown == 1 && valVolDown != lastVolDown) {
      Serial.println("AMP_VOLDN");
      IrSender.sendNEC(AMP_ADDR, AMP_VOLDN, 1);
      delay(DELAY_AFTER_SEND);    
    }

    if(valTvPower == 1 && valTvPower != lastTvPower) {
      Serial.println("TV_POWER");
      IrSender.sendNEC(AMP_ADDR, TV_POWER, 1);
      delay(DELAY_AFTER_SEND);    
    }

    lastAmpPower = valAmpPower;
    lastVolUp = valVolUp;
    lastVolDown = valVolDown;
    lastTvPower = valTvPower;
    
}
