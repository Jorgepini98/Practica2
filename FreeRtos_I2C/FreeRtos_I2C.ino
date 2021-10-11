#include <MPU9250_asukiaaa.h>

//defino los pines del I2C para el ESP32
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

#define ledPin 34


// se define el objeto utilizado para esta libreria
MPU9250_asukiaaa mySensor;
// Defino variables
double aX, aY, aZ;

const portTickType ledDelay = 200 / portTICK_RATE_MS;
const portTickType muestreoDelay = 100 / portTICK_RATE_MS;
const portTickType envioDelay = 1000 / portTICK_RATE_MS;


void setup() {
  
  //inicializo
  
  Serial.begin(115200);
  while(!Serial);
  Serial.println("started");

  #ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
  #endif

  mySensor.beginAccel();

  xTaskCreate(MuestreoAcel,"MuestreoAcel",10000,NULL,2,NULL);
  xTaskCreate(EnvioDatos,"EnvioDatos",10000,NULL,2,NULL);
//inicio el scheduler
  vTaskStartScheduler();

}

void MuestreoAcel(void*parameter){

while(1){
  if (mySensor.accelUpdate() == 0) {
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();  
  } else {
    Serial.println("Cannod read accel values");
  }
}
  vTaskDelay(muestreoDelay); 

  
}

void EnvioDatos(void*parameter){
   pinMode(ledPin,OUTPUT);

while(1){

   Serial.println("accelX: " + String(aX));
   Serial.println("accelY: " + String(aY));
   Serial.println("accelZ: " + String(aZ));

   digitalWrite(ledPin, HIGH);   
   vTaskDelay(ledDelay); 
   digitalWrite(ledPin, LOW);    
   vTaskDelay(envioDelay); 
}
   
}



//elimino la tarea "loop" par evitar errores con el reseteo del watchdog
void loop() {
  vTaskDelete(NULL);

}
