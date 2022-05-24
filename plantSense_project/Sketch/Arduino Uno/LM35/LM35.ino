//Sensor LM35DZ - Controle de Temperatura

const int LM35 = A2;
float temp = 0;

void setup() {
  
  Serial.begin(9600);

}

void loop() {
  temp = (analogRead(LM35)* (5/1024.0) * 100);
  Serial.print("Temperatura = ");
  Serial.print(temp);
  Serial.print("*C ");
  delay(1000);

}
