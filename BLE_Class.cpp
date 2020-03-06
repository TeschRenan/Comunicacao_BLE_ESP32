#include "BLE_Class.h"

bool deviceConnected = false;
String ConteudoCallback  = "";

BLEClass::BLEClass(){

  BLEDevice::init("UART Service");

// Cria o servidor BLE
  ServerBLE = BLEDevice::createServer();

  MyServerCallbacks* CallSever = new MyServerCallbacks();

  ServerBLE->setCallbacks(CallSever);
  
// Cria o serviço BLE
  ServiceBLE = ServerBLE->createService(SERVICE_UUID);
// Cria uma característica BLE
  TxCharacteristicBLE = ServiceBLE->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );
                      
  TxCharacteristicBLE->addDescriptor(new BLE2902());

  RxCharacteristicBLE = ServiceBLE->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  RxCharacteristicBLE->setCallbacks(new MyCallbacks());

  //Iniciando o Serviço BLE
  ServiceBLE->start();

  // Inicia a descoberta por outros dispositivos
  ServerBLE->getAdvertising()->start();
  Serial.println("Aguardando uma conexão do cliente para notificar ...");
  
}
void BLEClass::SendString(String Value){

    char DataString[16];
    strlcpy(DataString, Value.c_str(), sizeof(DataString)); 

    TxCharacteristicBLE->setValue(DataString);
   
    TxCharacteristicBLE->notify(); // Envia o valor para o aplicativo!
    
    Serial.print("*** Dado enviado: ");
    Serial.print(DataString);
    Serial.println(" ***");
}
String BLEClass::RetornaString(){
  return ConteudoCallback;
}
bool BLEClass::RetornaConexao(){
  return deviceConnected;
}

void BLEClass::Loop(String Value){
  if(deviceConnected){
    this->SendString(Value);
  }

}
MyServerCallbacks::MyServerCallbacks(){
      
}
MyCallbacks::MyCallbacks(){
  
}

void MyServerCallbacks::onConnect(BLEServer* pServer) {
       deviceConnected =  true;
      Serial.println("Dispositivo Conectado");
}

void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
      deviceConnected =  false;
      Serial.println("Dispositivo Desconectado");
      
}

void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      ConteudoCallback = rxValue.c_str();
      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Valor Recebido: ");
        for (int i = 0; i < rxValue.length(); i++)
          Serial.print(rxValue[i]);

        Serial.println();
        Serial.println("*********");
  }
}
