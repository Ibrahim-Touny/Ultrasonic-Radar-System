// ===== ARDUINO MEGA =====

const int trigPin = 8;
const int echoPin = 9;

const int joyX = A0;
const int joySW = 4;

int angle = 90;
int dir = 1;
bool manualMode = false;
bool lastSW = HIGH;

long duration;
int distance;

// to fix manual mode
unsigned long lastManualSend = 0;
const unsigned long MANUAL_INTERVAL = 20; // 20 ms = servo-safe


int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(joySW, INPUT_PULLUP);

  Serial.begin(9600);     // → Processing
  Serial1.begin(115200);  // → Arduino UNO
}

void loop() {

  bool sw = digitalRead(joySW);
  if (lastSW == HIGH && sw == LOW) {
    manualMode = !manualMode;
    delay(200);
  }
  lastSW = sw;

  if (manualMode) {
    int x = analogRead(joyX);
    angle = map(x, 0, 1023, 15, 165);
  } else {
    angle += dir;
    if (angle >= 165 || angle <= 15) dir = -dir;
  }

  distance = calculateDistance();

  // → Processing
  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");

  /* ---------- SEND TO UNO (CONTROLLED) ---------- */
  if (!manualMode) {
    // AUTO mode → same behavior as before
    Serial1.print(angle);
    Serial1.print(",");
    Serial1.print(distance);
    Serial1.print(",");
    Serial1.print("0");  // AUTO = 0
    Serial1.print(".");
    delay(30);  // unchanged AUTO speed
  } 
  else {
    // MANUAL mode → rate limited
    unsigned long now = millis();
    if (now - lastManualSend >= MANUAL_INTERVAL) {
      lastManualSend = now;

      Serial1.print(angle);
      Serial1.print(",");
      Serial1.print(distance);
      Serial1.print(",");
      Serial1.print("1");  // MANUAL = 1
      Serial1.print(".");
    }
  }
  
  if(!manualMode)
    delay(30);
}
