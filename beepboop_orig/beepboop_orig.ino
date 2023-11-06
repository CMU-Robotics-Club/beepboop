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
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(STOP_1, LOW);
  digitalWrite(STOP_2, LOW);
  state_green_wait();
  state_yellow();
  state_red();
  digitalWrite(STOP_1, HIGH);
  digitalWrite(STOP_2, HIGH);  
  state_walk();
  state_stop();
  digitalWrite(STOP_1, LOW);
  digitalWrite(STOP_2, LOW);
  state_red();
}

void state_green_wait() {
 digitalWrite(GREEN, LOW);
  for(;;) {
    if(digitalRead(BUTTON) == LOW){
      delay(50);
      if(digitalRead(BUTTON) == LOW){
       break;
      }    
    }
  }
  digitalWrite(GREEN, HIGH);
}

void state_yellow() {
  digitalWrite(YELLOW, LOW);
  delay(YELLOW_ON_TIME * 1000);
  digitalWrite(YELLOW, HIGH);
}

void state_red() {
  digitalWrite(RED, LOW);
  delay(RED_ON_TIME * 1000);
  digitalWrite(RED, HIGH);
}

void state_walk() {
  digitalWrite(WALK_1, LOW);
  digitalWrite(WALK_2, LOW);
  digitalWrite(BEEP_BOOP, LOW);
  digitalWrite(RED, LOW);
  delay(WALK_ON_TIME * 1000);
  digitalWrite(WALK_1, HIGH);
  digitalWrite(WALK_2, HIGH);
  digitalWrite(BEEP_BOOP, HIGH);
  digitalWrite(RED, HIGH);  
}

void state_stop() {
  digitalWrite(RED, LOW);
  for(int i = 0; i < STOP_FLASHES; i++) {
    digitalWrite(STOP_1, LOW);
    digitalWrite(STOP_2, LOW);
    delay(((STOP_ON_TIME / STOP_FLASHES) * 1000) / 2);
    digitalWrite(STOP_1, HIGH);
    digitalWrite(STOP_2, HIGH);  
    delay(((STOP_ON_TIME / STOP_FLASHES) * 1000) / 2);  
  }
  digitalWrite(RED, HIGH);  
}
