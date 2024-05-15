//librerias para la conexion esp now
#include <WiFi.h>
#include <Wire.h>
#include <esp_now.h>
//definir objeto
//definir las entradas analogigas de los sensores
/*pulgar --> cafe 4 --> 33
  indice ---> negro --> 32
  medio --> 15 gris --> 35
  anular --> 13 blanco --> 34
  miñique --> morado 12 --> 36*/
int pulgar = 33;
int resultadoMIP;
int indice = 32;
int resultadoMII;
int medio = 35;
int resultadoMIM;
int anular = 34;
int resultadoMIA;
int menique = 36;
int resultadoMIMn;
int tierra = 4095;
int corriente = 0;
/*int ejeY;
  int ejeX;
  int aceX;
  int aceY;*/
void setup() {
  Serial.begin(9600);
}
void loop() {

  resultadoMIP = analogRead(pulgar);
  Serial.print("Pulgar: ");
  Serial.println(resultadoMIP);

  resultadoMII = analogRead(indice);
  Serial.print("Indice: ");
  Serial.println(resultadoMII);


  resultadoMIM = analogRead(medio);
  Serial.print("Medio: ");
  Serial.println(resultadoMIM);

  resultadoMIA = analogRead(anular);
  Serial.print("Anular: ");
  Serial.println(resultadoMIA);

  resultadoMIMn = analogRead(menique);
  Serial.print("Meñique: ");
  Serial.println(resultadoMIMn);
  //la de milis por defecto eran 500


  Serial.println("");
  if (  resultadoMIA < 350 && resultadoMIMn <   400) {
    if (resultadoMII < 350  && resultadoMIM < 200 &&  resultadoMIP < 1050 ) {
      if (resultadoMIP > 900 && resultadoMII < 300) {
        Serial.println("A");
      } else if (resultadoMIP < 900 && resultadoMIP > 820 && resultadoMII < 300) {
        Serial.println("O");
      } else if (resultadoMIP < 820 && resultadoMIP > 700 && resultadoMII < 350 && resultadoMIM < 200) {
        Serial.println("E");
      } else if (resultadoMIP < 700) {
        Serial.println("S");
      }
    } else if (resultadoMIM < 260 &&  resultadoMII > 450 && resultadoMIP > 1050 ) {
      Serial.println("L");
    } else if (resultadoMIM < 250 && resultadoMII < 500  && resultadoMIP < 1150 ) {
      /*if(resultadoMIP < 800 && resultadoMII < 350 && resultadoMIM < 200){
          Serial.println("E");
        }else if(resultadoMIP < 1100 &&  resultadoMII < 400  && resultadoMIM > 200 && resultadoMIA < 220) {*/
      if (resultadoMIP < 1100 &&  resultadoMII < 400  && resultadoMIM > 200 && resultadoMIA < 220) {
        Serial.println("T");
      } else if (resultadoMIP > 900 &&  resultadoMII < 400     && resultadoMIM < 160) {
        Serial.println("Q");
      }
      /*}else if(resultadoMIA < 250 && resultadoMIMn < 350 ){
        if( resultadoMIP > 1000  && resultadoMII > 460 && resultadoMIM > 150  ){
          Serial.println("P");
        }else if( resultadoMIP < 900  && resultadoMII < 460  && resultadoMIM < 150){
          Serial.println("Z");
        }*/
    } else if (resultadoMIM > 400 && resultadoMII > 450  && resultadoMIP > 1050 ) {
      Serial.println("H");
    } else if (resultadoMIP < 900 &&  resultadoMII < 500 &&  resultadoMIM < 500) {
      Serial.println("U");
    } else if (resultadoMIP < 1000 &&  resultadoMII < 650 &&  resultadoMIM > 550) {
      Serial.println("V");
    }
  } else if (resultadoMIA < 600 && resultadoMIMn <  400) {
    if (resultadoMIP < 1000 &&  resultadoMII < 600 &&  resultadoMIM < 700) {
      Serial.println("M");
    }
  } else if (resultadoMIMn < 550 && resultadoMIA < 350 ) {
    if ( resultadoMIM < 300 && resultadoMII > 350  && resultadoMIP < 1050 ) {
      Serial.println("C");
    } else if ( resultadoMIM > 250 && resultadoMII < 400  && resultadoMIP < 1050 ) {
      Serial.println("F");
    } else if ( resultadoMIM < 200 && resultadoMII  > 250  && resultadoMII  < 350  && resultadoMIP < 900 ) {
      Serial.println("D");
    } else if ( resultadoMIM < 250 && resultadoMII < 260  && resultadoMIP < 1050 ) {
      Serial.println("I");
    } else if ( resultadoMIM < 200 && resultadoMII < 300  && resultadoMIP < 1100 ) {
      Serial.println("Y");
    }
  } else if (resultadoMIP < 820 ) {
    Serial.println("B");

  }
  if (resultadoMIP < 1020 &&  resultadoMII < 550 &&  resultadoMII > 450 &&  resultadoMIM > 200 &&  resultadoMIM < 300) {
    Serial.println("P");
  } else if ( resultadoMIP < 900  && resultadoMII < 460 && resultadoMII > 400 && resultadoMIM < 200) {
    Serial.println("Z");
  }
  /*}else if(resultadoMIM < 300 && resultadoMIA < 300 ) {
    if(resultadoMII < 400){
      if(resultadoMIP < 1050 &&  resultadoMIMn < 500){
        Serial.println("O");
      }else if(resultadoMIP < 1100 &&  resultadoMIMn > 500 &&  resultadoMIP > 1000 ) {
        Serial.println("D");
      }else if(resultadoMIP < 1000 &&  resultadoMIMn > 500) {
        Serial.println("I");
      }else if(resultadoMIMn < 500 && resultadoMII < 300  && resultadoMIP < 1100 ){
        Serial.println("Y");
      }
    }
    } */
  if (resultadoMIP == tierra ) {
    Serial.println("Error en el cable de tierra del dedo pulgar");
  } else if ( resultadoMIP == corriente) {
    Serial.println("Error en el cable de corriente del dedo pulgar");
  } else if (resultadoMII == tierra ) {
    Serial.println("Error en el cable de tierra del dedo indice");
  } else if ( resultadoMII == corriente) {
    Serial.println("Error en el cable de corriente del dedo indice");
  } else if (resultadoMIM == tierra ) {
    Serial.println("Error en el cable de tierra del dedo medio");
  } else if ( resultadoMIM == corriente) {
    Serial.println("Error en el cable de corriente del dedo medio");
  } else if (resultadoMIA == tierra ) {
    Serial.println("Error en el cable de tierra del dedo anular");
  } else if ( resultadoMIA == corriente) {
    Serial.println("Error en el cable de corriente del dedo anular");
  } else if (resultadoMIMn == tierra ) {
    Serial.println("Error en el cable de tierra del dedo meñique");
  } else if ( resultadoMIMn == corriente) {
    Serial.println("Error en el cable de corriente del dedo meñique");
  } else if ( resultadoMIP == tierra && resultadoMII == tierra && resultadoMIA == tierra && resultadoMIMn == tierra) {
    Serial.println("Error en el cable de tierra principal");
  } else if ( resultadoMIP == corriente && resultadoMII == corriente && resultadoMIA == corriente && resultadoMIMn == corriente) {
    Serial.println("Error en el cable de corriente principal");
  }




  delay(700);
}
