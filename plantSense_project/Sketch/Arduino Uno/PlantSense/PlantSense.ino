//Sensor LDR - Controle de Luminosidade

#define LDR A0
#define Limiar 1.5
#define ledPin 13

const int LM35 = A2;
int lum = 0;
float VoltageLDR;
float ResLDR;
float temp = 0;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  lum = analogRead(LDR);
  VoltageLDR = lum * (5.0/1024);
  Serial.print("Luminosidade = ");
  Serial.print(VoltageLDR);
  Serial.print(" ");
  
  temp = (analogRead(LM35)*(5/1024.0)*100);
  Serial.print("Leitura sensor LM35 = ");
  Serial.print(temp);
  Serial.print("*C ");

  if (VoltageLDR > Limiar)
    {
      digitalWrite(ledPin, HIGH);
      Serial.print("Baixa Luminosidade - ");
      }
  else
    {
      digitalWrite(ledPin, LOW);
      Serial.print("Boa Luminosidade - ");
      }
  delay(2000);
}
