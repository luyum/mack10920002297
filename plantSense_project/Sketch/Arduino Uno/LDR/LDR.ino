//Sensor LDR - Controle de Luminosidade

#define LDR A0
#define Limiar 1.5
#define ledPin 13

int Leitura = 0;
float VoltageLDR;
float ResLDR;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(100);

}

void loop() {
  Leitura = analogRead(LDR);
  VoltageLDR = Leitura * (5.0/1024);
  Serial.print("Luminosidade = ");
  Serial.print(VoltageLDR);

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
    
  delay(500);

}
