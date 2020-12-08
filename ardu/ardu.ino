// analog pins
int readPin = A0;
int readValue;

void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readValue = analogRead(readPin);
  Serial3.println(readValue);
  delay(100);
}
