
#define TOUCH_PIN T1
#define LED_PIN 2

int threshold = 500;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int value = touchRead(TOUCH_PIN);

  Serial.println(value);

  if (value < threshold) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(50);
}