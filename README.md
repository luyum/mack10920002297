# mack10920002297
Projeto IoT
Projeto que utiliza a placa NodeMCU ESP8266 com sensores e atuadores para leitura de umidade de solo e luminosidade.

Instalação da IDE Arduino
https://www.arduino.cc/en/software

Para usar o Node MCU ESP8266 com a IDE Arduino, é necessário inserir o link abaixo nas URLs Adicionais para Gerenciadores de Placas. 
Acessar Arquivo >> Preferências >> Configurações
http://arduino.esp8266.com/stable/package_esp8266com_index.json 
Em seguida selecionar a placa correta na aba Ferramentas. 
Caso necessário, importe e installe o pacote ESP8266 no Gerenciador de Placas (Ferramentas >> Placa >> Gerenciador de Placa)

MQTT
Instalar na IDE Arduino a Bibilioteca pubsubclient
https://github.com/knolleary/pubsubclient
Ferramentas >> Gerenciador de Biblioteca >> Procurar por PubSubClient 
Instalar a PubSubClient de Nick O'Leary

Definir ou instalar um broker
