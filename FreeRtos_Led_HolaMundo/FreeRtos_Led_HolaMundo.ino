
#define ledPin 34

//defino los tiempos de cada tarea
const portTickType ledDelay = 200 / portTICK_RATE_MS;
const portTickType HolaMundoDelay = 1000 / portTICK_RATE_MS;

void setup() {
  
  Serial.begin(112500);

  
//creo las dos tareas a realizar, pongo prioridad a 2 para evitar problemas con el reseteo del watchdog
  xTaskCreate(LED,"LED",10000,NULL,2,NULL);
  xTaskCreate(HolaMundo,"HolaMundo",10000,NULL,2,NULL);
//inicio el scheduler
  vTaskStartScheduler();

}

//tarea parpadeo led cada 200ms
void LED(void*parameter)
{
  pinMode(ledPin,OUTPUT);
  while(1)
  {
   Serial.println("TareaLed");
  digitalWrite(ledPin, HIGH);   
  vTaskDelay(ledDelay); 
  digitalWrite(ledPin, LOW);    
  vTaskDelay(ledDelay); 
  }
}

//tarea "Hola Mundo" por UART cada 1000ms
void HolaMundo(void*parameter)
{
  while(1)
  {
  Serial.println("Hola Mundo");
  vTaskDelay(HolaMundoDelay);
  }
}

//elimino la tarea "loop" par evitar errores con el reseteo del watchdog
void loop() 
{
  vTaskDelete(NULL);
}
  
