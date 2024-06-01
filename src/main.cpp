#include <Arduino.h>

// put function declarations here:
TaskHandle_t Tarea1;
TaskHandle_t Tarea2;

const int led=27;

void Tarea1codigo(void * parameter)
{
Serial.print("Tarea 1 is running on");
Serial.println(xPortGetCoreID());
 

for(;;)
  {
    Serial.print(" Led encendido ");
    digitalWrite (led, HIGH);
    vTaskDelay(1000);

  }
}
void Tarea2codigo(void * parameter)
{
Serial.print("Tarea 2 is running on: ");
Serial.println(xPortGetCoreID());
 

for(;;)
  {
  Serial.print(" Led apagado ");
  digitalWrite (led, LOW);
  vTaskDelay(1000);

  }
}
void setup() 
{ 
Serial.begin(115200); 
pinMode(led,OUTPUT);

xTaskCreatePinnedToCore( Tarea1codigo,"Tarea1", 10000,NULL,1,&Tarea1,1);
vTaskDelay(500);

xTaskCreatePinnedToCore( Tarea2codigo,"Tarea2", 10000,NULL,1,&Tarea2,0);
vTaskDelay(500);
} 

void loop(){}