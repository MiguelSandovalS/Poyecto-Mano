//definir las entradas analogigas de los sensores
/*pulgar --> cafe 33
  indice ---> azul 32
  medio --> cafeconblanco 35
  anular --> cafe 34
  miñique --> azul 36*/
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
// definir el objeto pantalla y sus caracteristicas
#define ANCHO 128
#define ALTO 64
#define OLED_RESET 4
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET)
//definir objeto
MPU6050 mpu6050(Wire);
// Variables que se reciben
typedef struct mensaje {
  int resultadoMIP;
  int resultadoMII;
  int resultadoMIM;
  int resultadoMIA;
  int resultadoMIMn;

} mensaje;
mensaje datos;
int pulgar = 33;
int resultadoMDP;
int indice = 32;
int resultadoMDI;
int medio = 35;
int resultadoMDM;
int anular = 34;
int resultadoMDA;
int menique = 36;
int resultadoMDMn;
long timer = 0;
int ejeX;
int ejeY;
int aceX;
int aceY;
int tierra = 4095;
int corriente = 0;
void OnDataRecv(const uint8_t * mac, const uint8_t *datosRecibidos, int len) {
  memcpy(&datos, datosRecibidos, sizeof(datos));

}
void setup() {
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Serial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Configuración WiFi modo ESTACIÓN
  WiFi.mode(WIFI_STA);
  // Inicio comunicación ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("A ocurrido un error al iniciar ESP-NOW");
    return;
  }
  // Creamos un registro de estado de paquetes recibidos
  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {
  mpu6050.update();
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  Serial.println("prueba 1 V2");
  Serial.println("");
  resultadoMDP = analogRead(pulgar);
  Serial.print("Pulgar: ");
  Serial.println(resultadoMDP);
  resultadoMDI = analogRead(indice);
  Serial.print("Indice: ");
  Serial.println(resultadoMDI);
  resultadoMDM = analogRead(medio);
  Serial.print("Medio: ");
  Serial.println(resultadoMDM);
  resultadoMDA = analogRead(anular);
  Serial.print("Anular: ");
  Serial.println(resultadoMDA);
  resultadoMDMn = analogRead(menique);
  Serial.print("Meñique: ");
  Serial.println(resultadoMDMn);
  Serial.println("");
  Serial.println(datos.resultadoMIP);
  Serial.println(datos.resultadoMII);
  Serial.println(datos.resultadoMIM);
  Serial.println(datos.resultadoMIA);
  Serial.println(datos.resultadoMIMn);
  
  if (millis() - timer > 500) {
    ejeX = mpu6050.getAccAngleX();
    ejeY = mpu6050.getAccAngleY();
    aceX = mpu6050.getAngleX();
    aceY = mpu6050.getAngleX();

    Serial.print("accAngleX : "); Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : "); Serial.println(mpu6050.getAccAngleY());
    Serial.print("angleX : "); Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : "); Serial.print(mpu6050.getAngleY());
    Serial.println("");
    if (  datos.resultadoMIA < 350 && datos.resultadoMIMn <   400) {
      if (datos.resultadoMII < 350  && datos.resultadoMIM < 200 &&  datos.resultadoMIP < 1050 ) {
        if (datos.resultadoMIP > 900 && datos.resultadoMII < 300) {
          Serial.println("A");
          oled.print("A");
        } else if (datos.resultadoMIP < 900 && datos.resultadoMIP > 820 && datos.resultadoMII < 300) {
          Serial.println("O");
          oled.print("O");
        } else if (datos.resultadoMIP < 820 && datos.resultadoMIP > 700 && datos.resultadoMII < 350 && datos.resultadoMIM < 200) {
          Serial.println("E");
          oled.print("E");
        } else if (datos.resultadoMIP < 700) {
          Serial.println("S");
          oled.print("S");
        }
      } else if (datos.resultadoMIM < 260 &&  datos.resultadoMII > 450 && datos.resultadoMIP > 1050 ) {
        Serial.println("L");
        oled.print("L");
      } else if (datos.resultadoMIM < 250 && datos.resultadoMII < 500  && datos.resultadoMIP < 1150 ) {
        if (datos.resultadoMIP < 1100 &&  datos.resultadoMII < 400  && datos.resultadoMIM > 200 && datos.resultadoMIA < 220) {
          Serial.println("T");
          oled.print("T");
        } else if (datos.resultadoMIP > 900 &&  datos.resultadoMII < 450    && datos.resultadoMIM < 160) {
          Serial.println("Q");
          oled.print("X");
        }
      } else if (datos.resultadoMIM > 400 && datos.resultadoMII > 450  && datos.resultadoMIP > 1050 ) {
        Serial.println("H");
        oled.print("H");
      } else if (datos.resultadoMIP < 900 &&  datos.resultadoMII < 500 &&  datos.resultadoMIM < 500) {
        Serial.println("U");
        oled.print("U");
      } else if (datos.resultadoMIP < 1000 &&  datos.resultadoMII < 650 &&  datos.resultadoMIM > 550) {
        Serial.println("V");
        oled.print("V");
      }
    } else if (datos.resultadoMIA < 600 && datos.resultadoMIMn <  400) {
      if (datos.resultadoMIP < 1000 &&  datos.resultadoMII < 600 &&  datos.resultadoMIM < 700) {
        Serial.println("W");
        oled.print("W");
      }
    } else if (datos.resultadoMIMn < 550 && datos.resultadoMIA < 350 ) {
      if ( datos.resultadoMIM < 300 && datos.resultadoMII > 350  && datos.resultadoMIP < 1050 ) {
        Serial.println("C");
        oled.print("C");
      } else if ( datos.resultadoMIM > 250 && datos.resultadoMII < 400  && datos.resultadoMIP < 1050 ) {
        Serial.println("F");
        oled.print("F");
      } else if ( datos.resultadoMIM < 200 && datos.resultadoMII  > 250  && datos.resultadoMII  < 350  && datos.resultadoMIP < 900 ) {
        Serial.println("D");
        oled.print("D");
      } else if ( datos.resultadoMIM < 250 && datos.resultadoMII < 260  && datos.resultadoMIP < 1050 ) {
        Serial.println("I");
        oled.print("I");
      } else if ( datos.resultadoMIM < 200 && datos.resultadoMII < 300  && datos.resultadoMIP < 1100 ) {

        Serial.println("Y");
        oled.print("Y");
      }
    } else if (datos.resultadoMIP < 820 ) {
      Serial.println("B");
      oled.print("B");
    }
    if (datos.resultadoMIP < 1020 &&  datos.resultadoMII < 550 &&  datos.resultadoMII > 450 &&  datos.resultadoMIM > 200 &&  datos.resultadoMIM < 300) {
      Serial.println("P");
      oled.print("P");
    } else if ( datos.resultadoMIP < 900  && datos.resultadoMII < 460 && datos.resultadoMII > 400 && datos.resultadoMIM < 200) {
      Serial.println("Z");
      oled.print("Z");
    }
    if (resultadoMDI < 600 && resultadoMDM < 700  && resultadoMDA < 800 && resultadoMDMn <   750) {
      if (ejeX < -7) {
        Serial.println("Aprovechar");
        oled.print("APROVECHAR");
      } else {
        Serial.println("A");
        oled.print("A");
      }
    } else if (resultadoMDI < 950 && resultadoMDI > 400 && resultadoMDM < 650 && resultadoMDM < 500  && resultadoMDA < 700 && resultadoMDMn <  900) {
      if (ejeX < 0) {
        Serial.println("Q");
        oled.print("Q");
      } else {
        Serial.println("X");
        oled.print("X");
      }
    } else if (resultadoMDI > 1200 &&  resultadoMDM < 1100 && resultadoMDA < 950 && resultadoMDMn <  900) {
      if (ejeX < 10) {
        Serial.println("Cortar");
        oled.print("CORTAR");
      } else {
        Serial.println("H");
        oled.print("H");
      }
    } else if ( resultadoMDI < 1200  &&  resultadoMDM < 950 && resultadoMDM > 800 &&  resultadoMDA < 750) {
      if ( resultadoMDI < 1200 && resultadoMDI > 1000 ) {
        if (ejeX < -20 && ejeY > 15) {
          Serial.println("N");
          oled.print("N");

        } else if (ejeX  < -20 && ejeY < 15) {
          Serial.println("Ñ");
          oled.print("Ñ");
        } else {
          Serial.println("V");
          oled.print("V");
        }
      } else if (resultadoMDI < 1000 && resultadoMDI > 900  ) {
        Serial.println("U");
        oled.print("U");
      }
    } else if (resultadoMDI < 1150 &&  resultadoMDM > 750 && resultadoMDA > 1000 && resultadoMDMn <  850) {
      if (ejeX < -20) {
        Serial.println("M");
        oled.print("M");
      } else {
        Serial.println("W");
        oled.print("W");
      }
    } else if (resultadoMDI > 1000 && resultadoMDM < 800  &&  resultadoMDMn > 1000 && resultadoMDA >1000 ) {
      if (ejeY < 0) {
        Serial.println("Crecer");
        oled.print("CRECER");
      } else if (ejeX < 5 && ejeY < 50) {
        Serial.println("Contestar");
        oled.print("CONTESTAR");
      } else if (ejeX < 20 && ejeY < 50) {
        Serial.println("Ahogar");
        oled.print("AHOGAR");
      } else {
        Serial.println("C");
        oled.print("C");
      }
    } else if (resultadoMDI < 700 &&  resultadoMDM < 720 &&  resultadoMDM > 600 && resultadoMDA< 1200 && resultadoMDMn >   1000) {
      if (ejeX < 10) {
        Serial.println("Aceptar");
        oled.print("ACEPTAR");
      } else {
        Serial.println("F");
        oled.print("F");
      }
    } else if (resultadoMDI < 700 &&  resultadoMDM < 500 && resultadoMDA < 900 && resultadoMDMn <  1200 && resultadoMDMn >  1100) {
      if (ejeX > 60) {
        Serial.println("J");
        oled.print("J");
      } else {
        Serial.println("I");
        oled.print("I");
      }
    } else if (resultadoMDI < 1000&&  resultadoMDM < 700  &&  resultadoMDM > 500 && resultadoMDA < 750 && resultadoMDMn <  750) {
      if (ejeX <  0) {
        Serial.println("K");
        oled.print("K");
      } else {
        Serial.println("P");
        oled.print("P");
      }

    } else if (resultadoMDI > 950 &&  resultadoMDM < 400 && resultadoMDA < 750 && resultadoMDMn < 750) {
      if (ejeX < -7) {
        Serial.println("Asesinar");
        oled.print("ASESINAR");
      } else if (ejeX > 30) {
        Serial.println("Silencio");
        oled.print("SILENCIO");
      } else {
        Serial.println("Z");
        oled.print("Z");
      }
    } else if (resultadoMDI < 700 &&  resultadoMDM < 500 && resultadoMDA < 750 && resultadoMDMn <  850) {
      if (ejeX < -7) {
        Serial.println("Atrapar");
        oled.print("ATRAPAR");
      } else if (ejeX > 0) {
        Serial.println("Edad");
        oled.print("EDAD");
      } else {
        Serial.println("S");
        oled.print("S");
      }
    }
    if (datos.resultadoMIP == tierra ) {
      Serial.println("Error en el cable de tierra del dedo pulgar");
      oled.print("ERR. EN T. P.");
    } else if ( datos.resultadoMIP == corriente) {
      oled.print("ERR. EN C. P.");
      Serial.println("Error en el cable de corriente del dedo pulgar");
    } else if (datos.resultadoMII == tierra ) {
      oled.print("ERR. EN T. I.");
      Serial.println("Error en el cable de tierra del dedo indice");
    } else if ( datos.resultadoMII == corriente) {
      oled.print("ERR. EN C. I.");
      Serial.println("Error en el cable de corriente del dedo indice");
    } else if (datos.resultadoMIM == tierra ) {
      oled.print("ERR. EN T. M.");
      Serial.println("Error en el cable de tierra del dedo medio");
    } else if ( datos.resultadoMIM == corriente) {
      oled.print("ERR. EN C. M.");
      Serial.println("Error en el cable de corriente del dedo medio");
    } else if (datos.resultadoMIA == tierra ) {
      oled.print("ERR. EN T. A.");
      Serial.println("Error en el cable de tierra del dedo anular");
    } else if ( datos.resultadoMIA == corriente) {
      oled.print("ERR. EN C. A.");
      Serial.println("Error en el cable de corriente del dedo anular");
    } else if (datos.resultadoMIMn == tierra ) {
      oled.print("ERR. EN T. MN.");
      Serial.println("Error en el cable de tierra del dedo meñique");
    } else if ( datos.resultadoMIMn == corriente) {
      oled.print("ERR. EN C. MN.");
      Serial.println("Error en el cable de corriente del dedo meñique");
    } else if ( datos.resultadoMIP == tierra && datos.resultadoMII == tierra && datos.resultadoMIA == tierra && datos.resultadoMIMn == tierra) {
      oled.print("ERR. EN C.T.P.");
      Serial.println("Error en el cable de tierra principal");

    } else if ( datos.resultadoMIP == corriente && datos.resultadoMII == corriente && datos.resultadoMIA == corriente && datos.resultadoMIMn == corriente) {
      Serial.println("Error en el cable de corriente principal");
      oled.print("ERR. EN C.C.P.");
    }
    timer = millis();
  }
  delay(1000);
  oled.display();
}
