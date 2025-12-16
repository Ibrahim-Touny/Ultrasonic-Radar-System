#include <Servo.h>

#define SERVO_PIN  10
#define BUZZER_PIN 7

Servo myServo;

/* ---------- UART BUFFER ---------- */
#define BUF_SIZE 32
char rxBuffer[BUF_SIZE];
byte rxIndex = 0;

/* ---------- DATA ---------- */
int angle = 90;
int distance = -1;
int mode = 0; // 0 = AUTO, 1 = MANUAL

void setup() {
  Serial.begin(115200);   // UART from Mega
  myServo.attach(SERVO_PIN);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  readSerial();
}

/* ---------- SERIAL READER ---------- */
void readSerial() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '.') {
      rxBuffer[rxIndex] = '\0';   // terminate string
      parsePacket(rxBuffer);
      rxIndex = 0;                // reset buffer
    }
    else {
      if (rxIndex < BUF_SIZE - 1) {
        rxBuffer[rxIndex++] = c;
      } else {
        // buffer overflow → reset safely
        rxIndex = 0;
      }
    }
  }
}

/* ---------- PACKET PARSER ---------- */
void parsePacket(char *packet) {

  // Expected format: angle,distance,mode.
  char *comma1 = strchr(packet, ',');
  if (!comma1) return;

  *comma1 = '\0';  // split at first comma
  
  char *comma2 = strchr(comma1 + 1, ',');
  if (!comma2) return;
  
  *comma2 = '\0';  // split at second comma

  int newAngle = atoi(packet);
  int newDistance = atoi(comma1 + 1);
  int newMode = atoi(comma2 + 1);

  // -------- VALIDATION --------
  if (newAngle < 15 || newAngle > 165) return;

  // -------- APPLY --------
  angle = newAngle;
  distance = newDistance;
  mode = newMode;

  myServo.write(angle);

  bool buzzerActive = false;
  if (distance > 0 && distance < 30) {
    tone(BUZZER_PIN, 2000);
    buzzerActive = true;
  } else {
    noTone(BUZZER_PIN);
    buzzerActive = false;
  }

  // -------- SEND TO PYTHON LOGGER --------
  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(",");
  Serial.print(mode);
  Serial.print(",");
  Serial.print(buzzerActive ? 1 : 0);
  Serial.println();  // newline for Python parsing
}
