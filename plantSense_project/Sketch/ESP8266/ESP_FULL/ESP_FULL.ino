// Bibliotecas
#include <ESP8266WiFi.h> //inclui suporte ao NodeMCU
#include <PubSubClient.h> //inclui suporte ao MQTT no HiveMQ Cloud

// Definicoes e constantes
#define Limiar 2.9
const int LDR = A0;
const int FC28 = D7;
int LeituraSensorLDR;
int LeituraSensorFC28;
float VoltageLDR;

// Configuracoes da rede WiFi
const char* ssid = "LUS2.4G"; //SSID da rede WiFi
const char* password = "ted1620l"; //senha da rede WiFi

const char* mqtt_server = "broker.mqtt-dashboard.com"; //URL do broker MQTT
const int mqtt_server_port = 1883; //porta do broker MQTT

// Variaveis globais e objetos
#define MSG_BUFFER_SIZE (500) //define MSG_BUFFER_SIZE como 500
WiFiClient client; //cria o objeto client
PubSubClient mqtt_client(client); //cria o objeto mqtt_client
long lastMsg = 0;

String clientID = "ESP8266Client-"; //identificacao do cliente

String topicoPrefixo = "MACK10920002297"; //para o prefixo do topico, utilizar MACK seguido do TIA
String topicoTodos = topicoPrefixo + "/#"; //para retornar todos os topicos
String topico_0 = topicoPrefixo + "/test"; //topico para teste
String mensagem_0 = "NodeMCU Connected"; //mensagem para o topico 0
String topico_1 = topicoPrefixo + "/LDR"; //topico para o sensor LDR
String mensagem_1 = ""; //mensagem para o topico 1
String topico_2 = topicoPrefixo + "/FC28"; //topico para o sensor FC28
String mensagem_2 = ""; //mensagem para o topico 2
String topico_3 = topicoPrefixo + "/RedLed"; //topico para o atuador 1 - Led Vermelho
String mensagem_3 = ""; //mensagem para o topico 3
String topico_4 = topicoPrefixo + "/GreenLed"; //topico para o atuador 2 - Led Verde
String mensagem_4 = ""; //mensagem para o topico 4
String mensagemTemp = ""; //armazena temporariamente as mensagens recebidas via MQTT

// Funcao para configurar a conexao WiFi
void setup_wifi() {
  //WiFi.mode(WIFI_STA); //ativa o modo de estacao
  WiFi.begin(ssid, password);
  Serial.print("Conectando a ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

// Funcao para receber mensagens
void callback(char* topic, byte* payload, unsigned int length) {
  mensagemTemp = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    mensagemTemp += (char)payload[i];
  }

  if (String(topic) == topico_2) {
    mensagem_2 = mensagemTemp;
  }
  if (String(topic) == topico_4) {
    mensagem_4 = mensagemTemp;
  }

  Serial.println();

  // Switch on the LED if the first character is present
  if ((char)payload[0] != NULL) {
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED on
    // Note that LOW is the voltage level but actually the LED is on;
    // this is because it is active low on the ESP-01
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
  }
}

// Funcao para conectar no broker MQTT
void reconnect() {
  // Loop until we’re reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection…");

  // Create a random client ID
    randomSeed(micros()); //inicializa a semente do gerador de numeros aleatorios
    clientID += String(random(0xffff), HEX);

  // Attempt to connect
    if (mqtt_client.connect(clientID.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqtt_client.publish(topico_0.c_str(), mensagem_0.c_str());
      // ... and resubscribe
      mqtt_client.subscribe(topicoTodos.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} 

void setup() {
  const int LDR = A0;
  const int FC28 = D7;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D1, OUTPUT); //pino 1, onde esta ligado o Led Vermelho
  pinMode(D2, OUTPUT); //pino 1, onde esta ligado o Led Verde
  Serial.begin(9600); //inicializa a saida serial
  setup_wifi();

  mqtt_client.setServer(mqtt_server, mqtt_server_port); //configura a conexao com o broker MQTT
  mqtt_client.setCallback(callback); //configura o recebimento de mensagens
}

void loop() {
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop(); //processa as mensagens e mantem a conexao com o broker MQTT

  //Leitura do Sensor LDR
  LeituraSensorLDR = analogRead(LDR);
  VoltageLDR = LeituraSensorLDR * (3.3/1024);
  Serial.print("Luminosidade = ");
  Serial.print(VoltageLDR);
  Serial.println();
  
  if (VoltageLDR > Limiar)
    {
      Serial.print("Baixa Luminosidade");
      mensagem_1 = "Baixa Luminosidade";
      Serial.println();
      }
  else
    {
      Serial.print("Boa Luminosidade");
      mensagem_1 = "Boa Luminosidade";
      Serial.println();
      }

  //Leitura Sensor FC28
  LeituraSensorFC28 = digitalRead(FC28);

  if (LeituraSensorFC28 == 1)
    {
      Serial.print("Regar a planta");
      mensagem_2 = "Regar a planta";
      Serial.println();
      digitalWrite(D1, HIGH); //led vermelho
      digitalWrite(D2, LOW); //led verde
      }
  else
    {
      Serial.print("Está tudo bem com a planta");
      mensagem_2 = "Está tudo bem com a planta";
      Serial.println();
      digitalWrite(D1, LOW); //led vermelho
      digitalWrite(D2, HIGH); //led verde
      }
  
  delay(1000);
  
  //Publica mensagens
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    mqtt_client.publish(topico_1.c_str(), mensagem_1.c_str());
    mqtt_client.publish(topico_2.c_str(), mensagem_2.c_str());
  }
}
