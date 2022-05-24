//FC28 - Umidade do Solo

#define FC28 A4
#define LimiarH 200
#define RelePin 8

int incomingByte;

void setup() {
  Serial.begin(9600);
  pinMode(RelePin, OUTPUT);
  digitalWrite(RelePin, LOW);
}

void loop() {
  int hum = analogRead(FC28);
  Serial.print("Umidde = ");
  Serial.print(hum);
  Serial.print(" ");

  if (hum > LimiarH)
  //solo está seco quando sensor mede acima de 1000
   {
    Serial.print("solo seco - ");
    digitalWrite(RelePin, HIGH);
    }
  else
  //totalmente úmido (direto na agua) mede 500
  //solo está encharcado quando sensor mede 380
   {
    Serial.print("solo umido - ");
    digitalWrite(RelePin,LOW);
    } 
  
  delay(2000);
}
