#define SEND_PWM_BY_TIMER
//#define IR_SEND_PIN 3
//#define IR_USE_AVR_TIMER2
#include <IRremote.hpp> 
#include <ir_NEC.hpp>

constexpr int pinIrSend = 3;

constexpr int DELAY_AFTER_SEND = 10;
constexpr int FREQ_KHZ = 38;

void setup() {

  pinMode(pinIrSend, OUTPUT);

  //IrSender.begin(pinIrSend);
  IrSender.enableIROut(FREQ_KHZ);

  Serial.begin(115200);
  Serial.println("IRblaster");
}

int last=0;

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

void loop() {
    auto line =  Serial.readStringUntil('\n');
    auto colon = line.indexOf(':');
    auto dot = line.indexOf('.');
    if(colon != 4 || dot != 9) return;

    uint16_t addr = strtol(line.substring(0,colon).c_str(),0,16);
    uint16_t cmd = strtol(line.substring(colon+1,dot).c_str(),0,16);

    // somehow we need to revers the bit order... (compared to LIRC keys)
    uint8_t addr_lo = addr & 0xFF;
    uint8_t addr_hi = (addr >> 8) & 0xFF;
    uint8_t cmd_lo = cmd & 0xFF;
    uint8_t cmd_hi = (cmd >> 8) & 0xFF;
    uint16_t addr_rev = (reverse(addr_lo) << 8) | reverse(addr_hi);
    uint16_t cmd_rev = (reverse(cmd_lo) << 8) | reverse(cmd_hi);

    Serial.print("addr = ");
    Serial.print(addr);
    Serial.print("addr_rev = ");
    Serial.print(addr_rev);
    Serial.print(" cmd = ");
    Serial.print(cmd);
    Serial.print(" cmd_rev = ");
    Serial.println(cmd_rev);

    //sendExtendedNEC(pinIrSend, addr_rev, cmd_rev);
    IrSender.sendOnkyo(addr_rev,cmd_rev,0);
    delay(DELAY_AFTER_SEND);    
}
