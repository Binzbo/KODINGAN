#include <Arduino_FreeRTOS.h>
#include <task.h>
void Task1( void *pvParameters );
void Task2( void *pvParameters );

TaskHandle_t TaskHandle_1; // handler for Task1
TaskHandle_t TaskHandle_2; // handler for Task2
//TaskHandle_t TaskHandle_3; // handler for Task3

int const LED_BOARD = 13;
int const LED_RED = 10;       // On board LED
int const LED_GREEN = 12;       // On board LED
int const LED_YELLOW = 11;       // On board LED
int const SENSOR_1 = 2;     // Pin to attach to sensor output
#define delayLED 100

boolean objectDetect1, buttonPress; // Flag to show whether an object has been detected
//===============================================================================
//  Initialization
//===============================================================================
void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);     
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BOARD, OUTPUT);
  pinMode (SENSOR_1, INPUT);
  pinMode (A8, INPUT);
  Serial.begin(9600);

   xTaskCreate(Task1, "Proxi1", 100, NULL, 1, &TaskHandle_1);
   xTaskCreate(Task2, "Button2", 100, NULL, 1, &TaskHandle_2);
//   xTaskCreate(Task3, "LED3", 100, NULL, 1, &TaskHandle_3);
   vTaskStartScheduler();
}
//===============================================================================
//  Main
//===============================================================================
void loop() 
{
 
}

void Task1(void* pvParameters) // Membaca proximity sensor (objek dekat atau tidak) --> turnLED atau offLED
{
  while(1)
  {
    
    Serial.println("Task1 runs");
    if (digitalRead(SENSOR_1) == 0)        // If detector Output is HIGH, there is no object
    {
      objectDetect1 = true;
      Serial.println("Object_1 Detected");
    }
    else                                
    {
    objectDetect1 = false;
    }

    if (objectDetect1 == true)
    {
      turnLED();
    }
    else
    {
      offLED();
    }
    
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // 100ms
  }
}

void Task2(void* pvParameters)
{
  while(1)
  {
    Serial.println("Task2 runs");
    buttonPress=digitalRead(A8);

     Serial.print("Button is: ");
     Serial.println(buttonPress);
      if (buttonPress == 0)
      {
        runLED(); //500 ms
      }
    vTaskDelay( 100 / portTICK_PERIOD_MS );

    
  }
}

void turnLED()
{
    digitalWrite (LED_RED, HIGH);      // turn on LED to show the detection.
    digitalWrite (LED_GREEN, HIGH);
    digitalWrite (LED_YELLOW, HIGH);
}

void offLED()
{
    digitalWrite (LED_RED, LOW);      // turn on LED to show the detection.
    digitalWrite (LED_GREEN, LOW);
    digitalWrite (LED_YELLOW, LOW);
}

void runLED()
{
  digitalWrite (LED_RED, HIGH);
  delay(delayLED);
  digitalWrite (LED_RED, LOW);
  delay(delayLED);
  digitalWrite (LED_GREEN, HIGH);
  delay(delayLED);
  digitalWrite (LED_GREEN, LOW);
  delay(delayLED);
  digitalWrite (LED_YELLOW, HIGH);
  delay(delayLED);
  digitalWrite (LED_YELLOW, LOW);
}
