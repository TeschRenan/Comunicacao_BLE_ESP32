/*   
    Baseado no exemplo de Neil Kolban para a IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
   
   Portado para o Arduino ESP32 por Renan Tesch

   Crie um servidor BLE que, assim que receber uma conexão, enviará notificações periódicas em formato JSON.
   O serviço é puclicado como: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
   Tem uma característica de: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - usada para receber dados com "WRITE"
   Tem uma característica de: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - usada para enviar dados com "NOTIFY"

   O design da criação do servidor BLE é:
   1. Crie um servidor BLE
   2. Crie um serviço BLE
   3. Crie uma característica BLE no serviço
   4. Crie um descritor BLE na característica
   5. Inicie o serviço.
   6. Comece a anunciar.

  Neste exemplo, rxValue são os dados recebidos (acessíveis apenas dentro do Metodo onWrite).
   E os dados a serem enviados, neste exemplo usa o metodo (BLE->SendString(String Value), apenas um byte incrementado a cada segundo.
*/

#include "BLE_Class.h"
#define TIME_ENVIO_BLE 1000

BLEClass* BLE_Class;

String ConteudoAntigo;
int Cont = 0;
unsigned long TimeBLE = 0;

void setup() {
  Serial.begin(115200);
  
  BLE_Class =  new BLEClass();

}

void loop() {
  if (millis() - TimeBLE > TIME_ENVIO_BLE  && BLE_Class->RetornaConexao()){
    String StringBLE = "{Contador:";
    StringBLE += "\"";
    StringBLE += Cont;
    StringBLE += "\"}";
    Cont ++;
    Serial.println("Valor Enviado no LOOP");
    Serial.println(StringBLE);
    BLE_Class->Loop(StringBLE);
    TimeBLE = millis();
  }
  
  
  if (ConteudoAntigo != BLE_Class->RetornaString()){
    ConteudoAntigo = BLE_Class->RetornaString();
    Serial.println("Valor Recebido pelo Callback");
    Serial.println(ConteudoAntigo);
  }
}
