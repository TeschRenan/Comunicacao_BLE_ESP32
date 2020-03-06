#ifndef BLE_CLASS_H
#define BLE_CLASS_H

#include <Arduino.h>
#include <ArduinoJson.h> 
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <iostream>
#include <string>
 
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" 

using namespace std;

class BLEClass{
  public:    
  BLEServer *ServerBLE;
  BLEService *ServiceBLE;
  BLECharacteristic * TxCharacteristicBLE;
  BLECharacteristic * RxCharacteristicBLE;
  BLEClass();
  void Loop(String);
  void SendString(String);
  String RetornaString();
  bool RetornaConexao();

};


    
class MyServerCallbacks: public BLEServerCallbacks {
    public:

    BLEServer *pServer = NULL;
    BLEClass* BLE_Class;

    MyServerCallbacks();

    
    void onConnect(BLEServer* pServer);

    void onDisconnect(BLEServer* pServer);

};

class MyCallbacks: public BLECharacteristicCallbacks {
    public:
    BLECharacteristic *pTxCharacteristic;
    MyCallbacks();
    
    void onWrite(BLECharacteristic *pCharacteristic);
};

#endif
