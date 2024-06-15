# Practica 4
## Part A
### Codi en línea
```cpp
 #include <Arduino.h>
 
 void anotherTask( void * parameter );
 void setup() 
{ Serial.begin(112500); 
xTaskCreate(anotherTask, "another Task", 10000,NULL,1,NULL);} 

void loop() 
{ 
Serial.println("this is ESP32 Task"); 
delay(1000); 
} 

void anotherTask( void * parameter ) 
{ 
for(;;) 
{ 
Serial.println("this is another Task"); 
delay(1000); 
} 
vTaskDelete( NULL ); 
}
```
### Explicació del codi
`1.Inclusió llibreries` 
```cpp
#include <Arduino.h>
```
Aquí s'inclou la llibreria d'Arduino.h la qual ens permet utilitzar les funcions bàsiques del microcontrolador.

`2.Declaració 'anotherTask'` 
```cpp
void anotherTask(void * parameter);
```
Aquesta és la declaració d'una funció anomenada **'anotherTask'** que agafa un parametre 'void'. Només es declara aquí, més endavant es fará servir.

`3.Setup`
```cpp
void setup() { 
    Serial.begin(115200); 
    xTaskCreate(anotherTask, "another Task", 10000, NULL, 1, NULL);
}
```
- **'Serial.begin(115200);:'** Inicia la comunicació serial a 115200 bauds.
- **'xTaskCreate(anotherTask, "another Task", 10000, NULL, 1, NULL);:'** Crea una nova tasca FreeRTOS. Els paràmetres son:
    - **'anotherTask:'** La funció que s'executarà com una tasca.
    - **'"another Task":'** El nom de la tasca.
    - **'10000:'** La mida de la pila assignada a la tasca.
    - **'NULL:'** Els paràmetres passats a la tasca (cap en aquest cas).
    - **'1:'** La prioritat de la tasca.
    - **'NULL:'** El controlador de la tasca (no s'utilitza aquí).
 
`4.Loop`
```cpp
void loop() { 
    Serial.println("this is ESP32 Task"); 
    delay(1000); 
}
```
- **'Serial.println("this is ESP32 Task");:'** Mostra el missatge "this is ESP32 Task" al monitor serial.
- **'delay(1000);:'** Fa una pausa de 1000 milisegons (1 segon).

`5.Declaració 'anotherTask'`
```cpp
void anotherTask(void * parameter) { 
    for (;;) { 
        Serial.println("this is another Task"); 
        delay(1000); 
    } 
    vTaskDelete(NULL); 
}
```
- **'for(;;):'** Un bucle infinit.
- **'Serial.println("this is another Task");:'** Mostra per pantalla el missatge "this is another Task" en el monitor serial.

## Part B
### Codi en línea
```cpp
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
```
### Explicació del codi
`1.Inclusió llibreries` 
```cpp
#include <Arduino.h>
```
Aquí s'inclou la llibreria d'Arduino.h la qual ens permet utilitzar les funcions bàsiques del microcontrolador.

`2.Declaració dels TaskHandles` 
```cpp
TaskHandle_t Tarea1;
TaskHandle_t Tarea2;
```
Aquestes tasques s'utilitzen per controlar les tasques creades per FreeRTOS.

`Declaració del LED`
```cpp
const int led = 27;
```
Defineix el pin 27 com el pin al que està conectat el LED.
