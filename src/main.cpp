#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = 14;

IRrecv irrecv(kRecvPin);

decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Recieved: ");
    serialPrintUint64(results.value, HEX);
    Serial.print(" - with Protocol: ");
    switch (results.decode_type){
      case NEC: Serial.println("NEC"); break;
      case SONY: Serial.println("SONY"); break;
      case RC5: Serial.println("RC5"); break;
      case RC6: Serial.println("RC6"); break;
      case DISH: Serial.println("DISH"); break;
      case SHARP: Serial.println("SHARP"); break;
      case JVC: Serial.println("JVC"); break;
      case SANYO: Serial.println("SANYO"); break;
      case MITSUBISHI: Serial.println("MITSUBISHI"); break;
      case SAMSUNG: Serial.println("SAMSUNG"); break;
      case LG: Serial.println("LG"); break;
      case WHYNTER: Serial.println("WHYNTER"); break;
      case AIWA_RC_T501: Serial.println("AIWA_RC_T501"); break;
      case PANASONIC: Serial.println("PANASONIC"); break;
      case DENON: Serial.println("DENON"); break;
    default:
      case UNKNOWN: Serial.println("UNKNOWN"); break;
    }
    irrecv.resume();  // Receive the next value
  }
  delay(100);
}