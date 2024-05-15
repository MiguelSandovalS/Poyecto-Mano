//librerias para la conexion esp now
#include <WiFi.h>
#include <Wire.h>
#include <esp_now.h>
#include <MPU6050_tockn.h>
//direccion mac del microcontrolador que resibe la informacion
uint8_t macReceptora[] = {0x78, 0xE3, 0x6D, 0x11, 0xC4, 0x70};//78:E3:6D:11:C4:70 ttgo dysplay lcd y 54:43:B2:AC:E2:50 wemos lolin lite
//definir las entradas analogicas de los sensores
/*pulgar --> cafe 4 --> 33
  indice ---> negro --> 32
  medio --> 15 gris --> 35
  anular --> 13 blanco --> 34
  miñique --> morado 12 --> 36*/
int pulgar = 33;
int auxMIP;
int indice = 32;
int auxMII;
int medio = 35;
int auxMIM;
int anular = 34;
int auxMIA;
int menique = 36;
int auxMIMn;
int ejeY;
int ejeX;
int aceX;
int aceY;
//variables a enviar
typedef struct mensaje {
  int resultadoMIP;
  int resultadoMII;
  int resultadoMIM;
  int resultadoMIA;
  int resultadoMIMn;
  
 
} mensaje;
//mensaje se almacena en datos
mensaje datos;
//Notificacion para la recepcion de datos
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nEstado del último paquete enviado:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Entregado" : "Ha ocurrido un fallo en la entrega");  
  
  auxMIP = analogRead(pulgar);
  datos.resultadoMIP = auxMIP;
  
  auxMII = analogRead(indice);
  datos.resultadoMII = auxMII;
  
  auxMIM = analogRead(medio);
  datos.resultadoMIM = auxMIM;
  
  auxMIA = analogRead(anular);
  datos.resultadoMIA  = auxMIA;
  
  auxMIMn = analogRead(menique);
  datos.resultadoMIMn = auxMIMn;
}
void setup() {
  Serial.begin(9600);
  //configurar el modo de estacion wifi
  WiFi.mode(WIFI_STA);
  //iniciar la comunicacion esp-now
  if (esp_now_init() != ESP_OK) {
    Serial.println("A ocurrido un error al iniciar ESP-NOW");
    return;
  }
  //crear el rigistro de estados de paquetes de transmision}
  esp_now_register_send_cb(OnDataSent);
  //guardar los datos en la estructura para el emparejamiento con el receptor
  esp_now_peer_info_t datosEmparejamiento;
  memcpy ( datosEmparejamiento.peer_addr, macReceptora, 6 );
  datosEmparejamiento.channel = 0;
  datosEmparejamiento.encrypt = false;
  //Añadir el receptor
  if (esp_now_add_peer(&datosEmparejamiento) != ESP_OK) {
    Serial.println("Fallo de emparejamiento");
    return;
  }
}
void loop() {
  // Envío de mensaje por ESP-NOW
  esp_err_t resultado = esp_now_send(macReceptora, (uint8_t *) &datos, sizeof(datos));
  if (resultado == ESP_OK) {
    Serial.println("Enviado correctamente");
  }
  else {
    Serial.println("Ha ocurrrido un error en el envío de datos");
  }  
  
  Serial.print("Pulgar: ");
  Serial.println(datos.resultadoMIP);
  Serial.print("Indice: ");
  Serial.println(datos.resultadoMII);
  Serial.print("Medio: ");
  Serial.println(datos.resultadoMIM);
  Serial.print("Anular: ");
  Serial.println(datos.resultadoMIA);
  Serial.print("Meñique: ");
  Serial.println(datos.resultadoMIMn);
  if(  datos.resultadoMIA < 350 && datos.resultadoMIMn <   400){            
    if (datos.resultadoMII < 350  && datos.resultadoMIM < 200 &&  datos.resultadoMIP < 1050 ){
      if(datos.resultadoMIP > 900 && datos.resultadoMII < 300){          
        Serial.println("A"); 
      }else if(datos.resultadoMIP < 900 && datos.resultadoMIP > 820 && datos.resultadoMII < 300){                
        Serial.println("O"); 
      }else if(datos.resultadoMIP < 820 && datos.resultadoMIP > 700 && datos.resultadoMII < 350 && datos.resultadoMIM < 200){
          Serial.println("E");
      }else if(datos.resultadoMIP < 700){
        Serial.println("S"); 
      }        
    } else if(datos.resultadoMIM < 260 &&  datos.resultadoMII > 450 && datos.resultadoMIP > 1050 ) {
      Serial.println("L");         
    }else if(datos.resultadoMIM < 250 && datos.resultadoMII < 500  && datos.resultadoMIP < 1150 ){ 
      /*if(datos.resultadoMIP < 800 && datos.resultadoMII < 350 && datos.resultadoMIM < 200){
          Serial.println("E");
      }else if(datos.resultadoMIP < 1100 &&  datos.resultadoMII < 400  && datos.resultadoMIM > 200 && datos.resultadoMIA < 220) {*/
      if(datos.resultadoMIP < 1100 &&  datos.resultadoMII < 400  && datos.resultadoMIM > 200 && datos.resultadoMIA < 220) {
        Serial.println("T");  
      }else if(datos.resultadoMIP > 900 &&  datos.resultadoMII < 400     && datos.resultadoMIM < 160) {
        Serial.println("Q");    
      }  
    /*}else if(datos.resultadoMIA < 250 && datos.resultadoMIMn < 350 ){
      if( datos.resultadoMIP > 1000  && datos.resultadoMII > 460 && datos.resultadoMIM > 150  ){
        Serial.println("P");
      }else if( datos.resultadoMIP < 900  && datos.resultadoMII < 460  && datos.resultadoMIM < 150){
        Serial.println("Z");               
      }*/        
    }else if(datos.resultadoMIM > 400 && datos.resultadoMII > 450  &&datos.resultadoMIP > 1050 ){
      Serial.println("H");       
    }else if(datos.resultadoMIP < 900 &&  datos.resultadoMII < 500 &&  datos.resultadoMIM < 500) {
      Serial.println("U");      
    }else if(datos.resultadoMIP < 1000 &&  datos.resultadoMII < 650 &&  datos.resultadoMIM > 550) {
      Serial.println("V"); 
    }  
  }else if(datos.resultadoMIA < 600 && datos.resultadoMIMn <  400){
    if(datos.resultadoMIP < 1000 &&  datos.resultadoMII < 600 &&  datos.resultadoMIM < 700){
        Serial.println("M");  
    }  
  }else if(datos.resultadoMIMn < 550 && datos.resultadoMIA < 350 ){
    if( datos.resultadoMIM < 300 && datos.resultadoMII > 350  &&datos.resultadoMIP < 1050 ){
      Serial.println("C");                  
    }else if( datos.resultadoMIM > 250 && datos.resultadoMII < 400  &&datos.resultadoMIP < 1050 ){        
      Serial.println("F");
    }else if( datos.resultadoMIM < 200 && datos.resultadoMII  > 250  && datos.resultadoMII  < 350  &&datos.resultadoMIP < 900 ){        
      Serial.println("D");
    }else if( datos.resultadoMIM < 250 && datos.resultadoMII < 260  &&datos.resultadoMIP < 1050 ){        
      Serial.println("I");  
    }else if( datos.resultadoMIM < 200 && datos.resultadoMII < 300  &&datos.resultadoMIP < 1100 ){        
      Serial.println("Y");  
    }
  }else if(datos.resultadoMIP < 820 ) {
    Serial.println("B");      
  
  }
  if(datos.resultadoMIP < 1020 &&  datos.resultadoMII < 550 &&  datos.resultadoMII > 450 &&  datos.resultadoMIM > 200 &&  datos.resultadoMIM < 300) {
        Serial.println("P");  
  }else if( datos.resultadoMIP < 900  && datos.resultadoMII < 460 && datos.resultadoMII > 400 && datos.resultadoMIM < 200){
        Serial.println("Z");
  }
  
 
  delay(1000);
}
