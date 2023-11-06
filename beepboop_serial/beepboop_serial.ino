#define RED 8
#define YELLOW 7
#define GREEN 6

#define WALK_1 3
#define STOP_1 2

#define WALK_2 5
#define STOP_2 4

#define BEEP_BOOP 9

#define BUTTON 10

#define WALK_ON_TIME 12
#define STOP_ON_TIME 6

#define STOP_FLASHES 3

#define YELLOW_ON_TIME 2
#define RED_ON_TIME 1

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(WALK_1, OUTPUT);
  pinMode(STOP_1, OUTPUT);
  pinMode(WALK_2, OUTPUT);
  pinMode(STOP_2, OUTPUT);
  pinMode(BEEP_BOOP, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(WALK_1, HIGH);
  digitalWrite(WALK_2, HIGH);
  digitalWrite(STOP_1, HIGH);
  digitalWrite(STOP_2, HIGH);
  digitalWrite(BEEP_BOOP, HIGH);
  
  Serial.begin(115200);
}

void loop() {
    if (Serial.available()) {
        uint8_t dat = Serial.read();
        digitalWrite(RED, (dat >> 0) & 1);
        digitalWrite(YELLOW, (dat >> 1) & 1);
        digitalWrite(GREEN, (dat >> 2) & 1);
        digitalWrite(WALK_1, (dat >> 3) & 1);
        digitalWrite(STOP_1, (dat >> 4) & 1);
        digitalWrite(WALK_2, (dat >> 5) & 1);
        digitalWrite(STOP_2, (dat >> 6) & 1);
        digitalWrite(BEEP_BOOP, (dat >> 7) & 1);
    }

    delay(10);
}
