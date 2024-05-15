//definir las entradas analogigas de los sensores
/*pulgar --> cafe 26
  indice ---> azul 39
  medio --> cafeconblanco 25
  anular --> cafe 27
  miñique --> azul 36*/
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
//#define TFT_GREY 0x5AEB
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
int pulgar = 27;
int resultadoMDP;
int indice = 39;
int resultadoMDI;
int medio = 33;
int resultadoMDM;
int anular = 32;
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
  tft.init();
  tft.setRotation(1);
  Serial.begin(9600);
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
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 50);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(4);
  tft.setTextFont(2);

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
          tft.print("A");
        } else if (datos.resultadoMIP < 900 && datos.resultadoMIP > 820 && datos.resultadoMII < 300) {
          Serial.println("O");
          tft.print("O");
        } else if (datos.resultadoMIP < 820 && datos.resultadoMIP > 700 && datos.resultadoMII < 350 && datos.resultadoMIM < 200) {
          Serial.println("E");
          tft.print("E");
        } else if (datos.resultadoMIP < 700) {
          Serial.println("S");
          tft.print("S");
        }
      } else if (datos.resultadoMIM < 260 &&  datos.resultadoMII > 450 && datos.resultadoMIP > 1050 ) {
        Serial.println("L");
        tft.print("L");
      } else if (datos.resultadoMIM < 250 && datos.resultadoMII < 500  && datos.resultadoMIP < 1150 ) {
        if (datos.resultadoMIP < 1100 &&  datos.resultadoMII < 400  && datos.resultadoMIM > 200 && datos.resultadoMIA < 220) {
          Serial.println("T");
          tft.print("T");
        } else if (datos.resultadoMIP > 900 &&  datos.resultadoMII < 450    && datos.resultadoMIM < 160) {
          Serial.println("Q");
          tft.print("X");
        }
      } else if (datos.resultadoMIM > 400 && datos.resultadoMII > 450  && datos.resultadoMIP > 1050 ) {
        Serial.println("H");
        tft.print("H");
      } else if (datos.resultadoMIP < 900 &&  datos.resultadoMII < 500 &&  datos.resultadoMIM < 500) {
        Serial.println("U");
        tft.print("U");
      } else if (datos.resultadoMIP < 1000 &&  datos.resultadoMII < 650 &&  datos.resultadoMIM > 550) {
        Serial.println("V");
        tft.print("V");
      }
    } else if (datos.resultadoMIA < 600 && datos.resultadoMIMn <  400) {
      if (datos.resultadoMIP < 1000 &&  datos.resultadoMII < 600 &&  datos.resultadoMIM < 700) {
        Serial.println("W");
        tft.print("W");
      }
    } else if (datos.resultadoMIMn < 550 && datos.resultadoMIA < 350 ) {
      if ( datos.resultadoMIM < 300 && datos.resultadoMII > 350  && datos.resultadoMIP < 1050 ) {
        Serial.println("C");
        tft.print("C");
      } else if ( datos.resultadoMIM > 250 && datos.resultadoMII < 400  && datos.resultadoMIP < 1050 ) {
        Serial.println("F");
        tft.print("F");
      } else if ( datos.resultadoMIM < 200 && datos.resultadoMII  > 250  && datos.resultadoMII  < 350  && datos.resultadoMIP < 900 ) {
        Serial.println("D");
        tft.print("D");
      } else if ( datos.resultadoMIM < 250 && datos.resultadoMII < 260  && datos.resultadoMIP < 1050 ) {
        Serial.println("I");
        tft.print("I");
      } else if ( datos.resultadoMIM < 200 && datos.resultadoMII < 300  && datos.resultadoMIP < 1100 ) {

        Serial.println("Y");
        tft.print("Y");
        //}
      }
    } else if (datos.resultadoMIP < 820 ) {
      Serial.println("B");
      tft.print("B");
    }
    if (datos.resultadoMIP < 1020 &&  datos.resultadoMII < 550 &&  datos.resultadoMII > 450 &&  datos.resultadoMIM > 200 &&  datos.resultadoMIM < 300) {
      Serial.println("P");
      tft.print("P");
    } else if ( datos.resultadoMIP < 900  && datos.resultadoMII < 460 && datos.resultadoMII > 400 && datos.resultadoMIM < 200) {
      Serial.println("Z");
      tft.print("Z");
    }
    //////////
    if (resultadoMDI < 600 && resultadoMDM < 700  && resultadoMDA < 800 && resultadoMDMn <   750) {
      if (ejeX < -7) {
        Serial.println("Aprovechar");
        tft.print("APROVECHAR");
      } else {
        Serial.println("A");
        tft.print("A");
      }
    //} else if (resultadoMDI < 600 && resultadoMDM < 500  && resultadoMDA < 750 && resultadoMDMn <   900) {
      //Serial.println("O");
      //tft.print("O");
    //} else if (resultadoMDI < 1200 && resultadoMDI > 1100 && resultadoMDI > 900 &&  resultadoMDM < 850 &&  resultadoMDM > 750  &&  resultadoMDA < 850 && resultadoMDMn <  870 && resultadoMDMn > 750) {
      //Serial.println("L");
      //tft.print("L");
    //} else if (resultadoMDI < 650 && resultadoMDM < 750  && resultadoMDA < 750 && resultadoMDMn <  850) {
      //Serial.println("E");
      //tft.print("E");
      //500y900
    } else if (resultadoMDI < 950 && resultadoMDI > 400 && resultadoMDM < 650 && resultadoMDM < 500  && resultadoMDA < 700 && resultadoMDMn <  900) {
      if (ejeX < 0) {
        Serial.println("Q");
        tft.print("Q");
      } else {
        Serial.println("X");
        tft.print("X");
      }
      /*}else if(resultadoMDI < 950  && resultadoMDM < 850&& resultadoMDA < 850 && resultadoMDMn <  800) {
        Serial.println("T");          */
    } else if (resultadoMDI > 1200 &&  resultadoMDM < 1100 && resultadoMDA < 950 && resultadoMDMn <  900) {
      if (ejeX < 10) {
        Serial.println("Cortar");
        tft.print("CORTAR");
      } else {
        Serial.println("H");
        tft.print("H");
      }
    } else if ( resultadoMDI < 1200  &&  resultadoMDM < 950 && resultadoMDM > 800 &&  resultadoMDA < 750) {
      if ( resultadoMDI < 1200 && resultadoMDI > 1000 ) {
        if (ejeX < -20 && ejeY > 15) {
          Serial.println("N");
          tft.print("N");

        } else if (ejeX  < -20 && ejeY < 15) {
          Serial.println("Ñ");
          tft.print("Ñ");
        } else {
          Serial.println("V");
          tft.print("V");
        }
      } else if (resultadoMDI < 1000 && resultadoMDI > 900  ) {
        Serial.println("U");
        tft.print("U");
      }
    } else if (resultadoMDI < 1150 &&  resultadoMDM > 750 && resultadoMDA > 1000 && resultadoMDMn <  850) {
      if (ejeX < -20) {
        Serial.println("M");
        tft.print("M");
      } else {
        Serial.println("W");
        tft.print("W");
      }
    } else if (resultadoMDI > 1000 && resultadoMDM < 800  &&  resultadoMDMn > 1000 && resultadoMDA >1000 ) {
      if (ejeY < 0) {
        Serial.println("Crecer");
        tft.print("CRECER");
      } else if (ejeX < 5 && ejeY < 50) {
        Serial.println("Contestar");
        tft.print("CONTESTAR");
      } else if (ejeX < 20 && ejeY < 50) {
        Serial.println("Ahogar");
        tft.print("AHOGAR");
      } else {
        Serial.println("C");
        tft.print("C");
      }
    } else if (resultadoMDI < 700 &&  resultadoMDM < 720 &&  resultadoMDM > 600 && resultadoMDA< 1200 && resultadoMDMn >   1000) {
      if (ejeX < 10) {
        Serial.println("Aceptar");
        tft.print("ACEPTAR");
      } else {
        Serial.println("F");
        tft.print("F");
      }
      /*}else if(resultadoMDP < 400 ) {
        Serial.println("B");*/
      //}else if(resultadoMDI < 500 &&  resultadoMDM < 400 && resultadoMDA < 600 && resultadoMDMn <  700) {
      //Serial.println("S");
      /*}else if( resultadoMDI < 550 &&  resultadoMDM < 700 && resultadoMDA < 700 && resultadoMDMn <  1150) {
        Serial.println("I");                  */
    } else if (resultadoMDI < 700 &&  resultadoMDM < 500 && resultadoMDA < 900 && resultadoMDMn <  1200 && resultadoMDMn >  1100) {
      if (ejeX > 60) {
        Serial.println("J");
        tft.print("J");
      } else {
        Serial.println("I");
        tft.print("I");
      }

    //} else if (resultadoMDI < 700 &&  resultadoMDM < 850 && resultadoMDA < 850 && resultadoMDMn <  1200 && resultadoMDMn > 1050) {
      //Serial.println("Y");
      //tft.print("Y");
    } else if (resultadoMDI < 1000&&  resultadoMDM < 700  &&  resultadoMDM > 500 && resultadoMDA < 750 && resultadoMDMn <  750) {
      if (ejeX <  0) {
        Serial.println("K");
        tft.print("K");
      } else {
        Serial.println("P");
        tft.print("P");
      }

    } else if (resultadoMDI > 950 &&  resultadoMDM < 400 && resultadoMDA < 750 && resultadoMDMn < 750) {
      if (ejeX < -7) {
        Serial.println("Asesinar");
        tft.print("ASESINAR");
      } else if (ejeX > 30) {
        Serial.println("Silencio");
        tft.print("SILENCIO");
      } else {
        Serial.println("Z");
        tft.print("Z");
      }
    } else if (resultadoMDI < 700 &&  resultadoMDM < 500 && resultadoMDA < 750 && resultadoMDMn <  850) {
      if (ejeX < -7) {
        Serial.println("Atrapar");
        tft.print("ATRAPAR");
      } else if (ejeX > 0) {
        Serial.println("Edad");
        tft.print("EDAD");
      } else {
        Serial.println("S");
        tft.print("S");
      }
    }
    if (datos.resultadoMIP == tierra ) {
      Serial.println("Error en el cable de tierra del dedo pulgar");
      tft.print("ERR. EN T. P.");
    } else if ( datos.resultadoMIP == corriente) {
      tft.print("ERR. EN C. P.");
      Serial.println("Error en el cable de corriente del dedo pulgar");
    } else if (datos.resultadoMII == tierra ) {
      tft.print("ERR. EN T. I.");
      Serial.println("Error en el cable de tierra del dedo indice");
    } else if ( datos.resultadoMII == corriente) {
      tft.print("ERR. EN C. I.");
      Serial.println("Error en el cable de corriente del dedo indice");
    } else if (datos.resultadoMIM == tierra ) {
      tft.print("ERR. EN T. M.");
      Serial.println("Error en el cable de tierra del dedo medio");
    } else if ( datos.resultadoMIM == corriente) {
      tft.print("ERR. EN C. M.");
      Serial.println("Error en el cable de corriente del dedo medio");
    } else if (datos.resultadoMIA == tierra ) {
      tft.print("ERR. EN T. A.");
      Serial.println("Error en el cable de tierra del dedo anular");
    } else if ( datos.resultadoMIA == corriente) {
      tft.print("ERR. EN C. A.");
      Serial.println("Error en el cable de corriente del dedo anular");
    } else if (datos.resultadoMIMn == tierra ) {
      tft.print("ERR. EN T. MN.");
      Serial.println("Error en el cable de tierra del dedo meñique");
    } else if ( datos.resultadoMIMn == corriente) {
      tft.print("ERR. EN C. MN.");
      Serial.println("Error en el cable de corriente del dedo meñique");
    } else if ( datos.resultadoMIP == tierra && datos.resultadoMII == tierra && datos.resultadoMIA == tierra && datos.resultadoMIMn == tierra) {
      tft.print("ERR. EN C.T.P.");
      Serial.println("Error en el cable de tierra principal");

    } else if ( datos.resultadoMIP == corriente && datos.resultadoMII == corriente && datos.resultadoMIA == corriente && datos.resultadoMIMn == corriente) {
      Serial.println("Error en el cable de corriente principal");
      tft.print("ERR. EN C.C.P.");
    }
    timer = millis();
  }
  delay(1000);
}
