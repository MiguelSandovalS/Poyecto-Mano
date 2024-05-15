//definir las entradas analogigas de los sensores
/*pulgar --> cafe 26 
indice ---> azul 39
medio --> cafeconblanco 25
anular --> cafe 27 
miñique --> azul 36*/
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#define TFT_GREY 0x5AEB
MPU6050 mpu6050(Wire);
int indice = 39;
int resultadoMDI;
int medio = 32;
int resultadoMDM;
int anular = 32;
int resultadoMDA;
int menique = 36;
int resultadoMDMn;
long timer = 0;
int maximoDePalabras =  50;
String arregloOracion[50];
int contador = 0;
int ejeX;
int ejeY;
int aceX;
int aceY;
void setup() {  
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  tft.init();
  tft.setRotation(1);
}
void agregarPalabra(String nuevaPalabra, int contador ){
  if(contador < maximoDePalabras){
    arregloOracion[maximoDePalabras] = nuevaPalabra;
    Serial.println(contador);
    delay(1000);
  }else{
    Serial.println("No se pueden agregar más palabras");
  }
}
void loop() {    
  mpu6050.update();
  Serial.println("");
  resultadoMDI= analogRead(indice);
  Serial.print("Indice: ");
  Serial.println(resultadoMDI);
  resultadoMDM= analogRead(medio);
  Serial.print("Medio: ");
  Serial.println(resultadoMDM);
  resultadoMDA= analogRead(anular);
  Serial.print("Anular: ");   
  Serial.println(resultadoMDA);
  resultadoMDMn= analogRead(menique);
  Serial.print("Meñique: ");
  Serial.println(resultadoMDMn);
  if(millis() - timer > 500){
    ejeX = mpu6050.getAccAngleX(); 
    ejeY = mpu6050.getAccAngleY(); 
    aceX = mpu6050.getAngleX(); 
    aceY = mpu6050.getAngleX(); 
    
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY()); 
    Serial.println("");
    //Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    //Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
    //ejeY = mpu6050.getAccAngleY();
   tft.fillScreen(TFT_GREY);
  tft.setCursor(0, 50);  
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(4);
  tft.setTextFont(2); 
   if(resultadoMDI < 650 && resultadoMDM < 700  && resultadoMDA < 700 && resultadoMDMn <   700){                  
    if(ejeX < -7){
      Serial.println("Aprovechar");
      
    }else {
      Serial.println("A");
      tft.print("Cortar");
    }         
   }else if(resultadoMDI < 600 && resultadoMDM < 500  && resultadoMDA < 750 && resultadoMDMn <   900){
    Serial.println("O");     
  }else if(resultadoMDI < 1200 && resultadoMDI > 1100 && resultadoMDI > 900 &&  resultadoMDM < 850 &&  resultadoMDM > 700  &&  resultadoMDA < 850 && resultadoMDMn <  870 && resultadoMDMn > 750) {
    Serial.println("L");             
    tft.print("L");
  }else if(resultadoMDI < 650 && resultadoMDM < 750  && resultadoMDA < 750 && resultadoMDMn <  850){
    Serial.println("E");
  //500y900
  }else if(resultadoMDI < 900 && resultadoMDI > 750 && resultadoMDM < 750 && resultadoMDM > 650  && resultadoMDA < 750 && resultadoMDMn <  800) {
    if(ejeX < 0){
      Serial.println("Q");
      tft.print("Q");
    }else {
      tft.print("X");
      Serial.println("X");
    }
  /*}else if(resultadoMDI < 950  && resultadoMDM < 850&& resultadoMDA < 850 && resultadoMDMn <  800) {
    Serial.println("T");          */
  }else if(resultadoMDI > 1200 &&  resultadoMDM < 900 && resultadoMDA < 900 && resultadoMDMn <  900){
      if(ejeX < 10){
        tft.print("Cortar");
      Serial.println("Cortar");
    }else {
      tft.print("H");
      Serial.println("H");
    }        
  }else if( resultadoMDI < 1200  &&  resultadoMDM < 700 && resultadoMDM > 550 &&  resultadoMDA < 750){
    if( resultadoMDI < 1200 && resultadoMDI > 1000 ){ 
       if(ejeX < -20 && ejeY > 15){
        tft.print("N");
        Serial.println("N");
       }else if(ejeX  < -20 && ejeY < 15){
        Serial.println("Ñ");
        tft.print("Ñ");
      }else {
        Serial.println("V");
        tft.print("V");
      }       
    }else if (resultadoMDI < 1000 && resultadoMDI > 900  ){  
          Serial.println("U");       
          tft.print("U");
    }
   }else if(resultadoMDI < 1150 &&  resultadoMDM > 900 && resultadoMDA < 1350 && resultadoMDMn <  850){
    if(ejeX < -20){
      Serial.println("M");
      tft.print("M");
    }else {
      Serial.println("W");
      tft.print("W");
    }      
   }else if(resultadoMDM < 1000 && resultadoMDM > 800 && resultadoMDI < 800  &&  resultadoMDMn < 1000 && resultadoMDA < 1020 ){
    if(ejeY < 0){
      Serial.println("Crecer");
      tft.print("Crecer");
    }else if(ejeX < 5 && ejeY < 50){
      Serial.println("Contestar");  
      tft.print("Contestar");
    }else if(ejeX < 20 && ejeY < 50){
      Serial.println("Ahogar");    
      tft.print("Ahogar");
    }else {
      Serial.println("C");
      tft.print("C");
    }
   }else if(resultadoMDI < 700 &&  resultadoMDM < 1250 &&  resultadoMDM > 1150 && resultadoMDA < 1250 && resultadoMDMn <  1150){
    if(ejeX < 10){
      Serial.println("Aceptar");    
      tft.print("Aceptar");
    }else {
      Serial.println("F");
      tft.print("F");
    }                   
   /*}else if(resultadoMDP < 400 ) {
    Serial.println("B");*/
   //}else if(resultadoMDI < 500 &&  resultadoMDM < 400 && resultadoMDA < 600 && resultadoMDMn <  700) {
    //Serial.println("S"); 
   /*}else if( resultadoMDI < 550 &&  resultadoMDM < 700 && resultadoMDA < 700 && resultadoMDMn <  1150) {
    Serial.println("I");                  */
   }else if(resultadoMDI < 700 &&  resultadoMDM < 850 && resultadoMDA < 820 && resultadoMDMn <  1200 && resultadoMDMn >  1100) {
    if(ejeX > 60){
      Serial.println("J");
      tft.print("J");
    }else {
      Serial.println("I");
      tft.print("I");
    }
   
   }else if(resultadoMDI < 700 &&  resultadoMDM < 850 && resultadoMDA < 850 && resultadoMDMn <  1200 && resultadoMDMn > 1050){
    Serial.println("Y");
    tft.print("Y");
   }else if(resultadoMDI < 1100 &&  resultadoMDM < 820 && resultadoMDA < 820 && resultadoMDMn <  750){
    if(ejeX <  0){
      Serial.println("K");
      tft.print("K");
    }else {
      Serial.println("P");
      tft.print("P");
    }
    
   }else if(resultadoMDI < 1100 &&  resultadoMDM < 750 && resultadoMDA < 800 && resultadoMDMn <  850){
    if(ejeX < -7){
      Serial.println("Asesinar");
      tft.print("ASESINAR");
    }else if(ejeX > 30){
      Serial.println("Silencio");
      tft.print("SILENCIO");
    }else {
      Serial.println("Z");
      tft.print("Z");
    } 
   }else if(resultadoMDI < 700 &&  resultadoMDM < 850 && resultadoMDA < 800 && resultadoMDMn <  850){
    if(ejeX < -7){
      Serial.println("Atrapar");
      tft.print("ATRAPAR");
     }else if(ejeX > 0){
      Serial.println("Edad");
      tft.print("EDAD");
    }else {
      Serial.println("S");
      tft.print("S");
    }     
   }
   
    timer = millis();    
  }
  delay(1000);
}
