//FC28 - Umidade do Solo
const int FC28 = D7;

#define LimiarH 0

void setup() {
  Serial.begin(9600);
  pinMode(FC28, INPUT);
}

void loop() {
  int hum = digitalRead(FC28);
  Serial.print("Umidade = ");
  Serial.print(hum);
  Serial.print(" ");

  if (hum > LimiarH)
  //solo está seco quando sensor mede 1
   {
    Serial.print("solo seco - ");
    }
  else
  //solo está encharcado quando sensor mede 0
   {
    Serial.print("solo umido - ");
    } 
  
  delay(2000);
}
