//Sensor LDR - Controle de Luminosidade

#define LDR A0
#define Limiar 1.5

int Leitura = 0;
float VoltageLDR;
float ResLDR;

void setup() {
  
  Serial.begin(9600);
  delay(100);

}

void loop() {
  Leitura = analogRead(LDR);
  VoltageLDR = Leitura * (3.3/1024);
  Serial.print("Luminosidade = ");
  Serial.print(VoltageLDR);

  if (VoltageLDR > Limiar)
    {
      Serial.print("Baixa Luminosidade - ");
      }
  else
    {
      Serial.print("Boa Luminosidade - ");
      }
    
  delay(500);

}
