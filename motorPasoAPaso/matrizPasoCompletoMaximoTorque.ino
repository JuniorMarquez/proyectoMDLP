#include <MultiStepper.h>
#include <AccelStepper.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)

// Motor pin definitions
#define mtrPin1  D1     // IN1 on the ULN2003 driver 1
#define mtrPin2  D2     // IN2 on the ULN2003 driver 1
#define mtrPin3  D5     // IN3 on the ULN2003 driver 1
#define mtrPin4  D6     // IN4 on the ULN2003 driver 1
int IN1 = mtrPin1;      // pin digital 8 de Arduino a IN1 de modulo controlador
int IN2 = mtrPin2;      // pin digital 9 de Arduino a IN2 de modulo controlador
int IN3 = mtrPin3;     // pin digital 10 de Arduino a IN3 de modulo controlador
int IN4 = mtrPin4;     // pin digital 11 de Arduino a IN4 de modulo controlador
int demora = 20;      // demora entre pasos, no debe ser menor a 10 ms.
// paso completo con maximo torque
int paso [4][4] =    // matriz (array bidimensional) con la secuencia de pasos
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setup() {
  pinMode(IN1, OUTPUT);   // todos los pines como salida
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {

  for (int i = 0; i < 512; i++) // 512*4 = 2048 pasos
  {
    for (int i = 0; i < 4; i++)   // bucle recorre la matriz de a una fila por vez
    {         // para obtener los valores logicos a aplicar
      digitalWrite(IN1, paso[i][0]);  // a IN1, IN2, IN3 e IN4
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(demora);
    }
  }

  digitalWrite(IN1, LOW); // detiene por 5 seg.
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(5000);

}
