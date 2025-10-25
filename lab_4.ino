const int photoResistorPin = A2;
const int ledPin = 12;
const int lightThreshold = 150;
bool thresholdMet = false;
bool commandGiven = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(photoResistorPin);

  int mappedLight = map(light, 0, 1023, 0, 255);

  //Serial.print("Lighting: ");
  //Serial.println(mappedLight);
  
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();

    if (command == "stop") {
      thresholdMet = false;
      commandGiven = true;
      digitalWrite(ledPin, LOW);
      Serial.println("LED light blinking has been stopped.");
    } else {
      Serial.println("Invalid command.");
    }
  }

  if (mappedLight >= lightThreshold && !commandGiven) {
    thresholdMet = true;
  }
  
  if (thresholdMet)
  {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}




