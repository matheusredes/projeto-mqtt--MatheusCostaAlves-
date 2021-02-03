#include <PubSubClient.h>
#include <UIPEthernet.h>
#include <SPI.h>

byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED};
boolean mensagem;
EthernetClient client;
PubSubClient mqttClient(client);
int pino2 = 2;
bool estado_sensor;


void setup() {

 pinMode(pino2,INPUT_PULLUP);
 
 Ethernet.begin(mac);
 
 Serial.begin(9600);

 mqttClient.setServer("54.144.190.205",1883);
 
 Serial.print("O IP do Arduino e: ");
 Serial.println(Ethernet.localIP());
 
 Serial.print("A Mascara de Rede do Arduino e: ");
 Serial.println(Ethernet.subnetMask());
 
 Serial.print("O Gateway do Arduino e: ");
 Serial.println(Ethernet.gatewayIP());
 
 
}

void loop() {

  estado_sensor = digitalRead(pino2); 
  
  mqttClient.connect("MatheusCosta");

  if(estado_sensor==0){
  Serial.println("O Rack esta fechado");
  mensagem = mqttClient.publish("redes","Rack esta fechado");
  
  } else {

    mensagem = mqttClient.publish("redes","Rack esta aberto");
    Serial.println("O Rack esta aberto");  
  }
  
  mqttClient.loop();
  
}
