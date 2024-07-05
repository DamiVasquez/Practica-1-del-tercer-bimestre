//practica 1 del tercer bimestre//
/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM / EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: MOTORES ELECTRICOS, ULTRASONICO Y NEOPIXEL
   Dev: Damasco Oxcal Vasquez
   Fecha: 5 DE JULIO 2024
*/

// Librerías
#include <Adafruit_NeoPixel.h>
#define PIN 6       // Pin al que está conectado el anillo de Neopixel
#define NUMPIXELS 16 // Número de Neopixels en el anillo (ajusta según tu anillo)

Adafruit_NeoPixel pixels_OXCAL = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Definición de pines para el display de 7 segmentos
const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 7;
const int F = 8;
const int G = 9;


// Definición de pines para el sensor ultrasónico HC-SR04
const int trig_Pin = 14;
const int echo_Pin = 15;

// Variables para el contador
int contador = 0;
const int distanciaMinima = 6;  // Distancia mínima en centímetros
const int distanciaMaxima = 10; // Distancia máxima en centímetros

void setup() {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
     
  // Inicialización del puerto serie para depuración
  Serial.begin(9600);
  
  pixels_OXCAL.begin();  // Inicializar el objeto Neopixel

  // Configurar todos los Neopixels al inicio
  actualizarNeopixel();

  for (int z = 2; z < 10; z++) {
    pinMode(z, OUTPUT);
  }
  
  // Configuración de pines para el sensor ultrasónico
  pinMode(trig_Pin, OUTPUT);
  pinMode(echo_Pin, INPUT);
}

void loop() {

  // Medición de la distancia con el sensor ultrasónico
  long duration, distance;
  digitalWrite(trig_Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_Pin, LOW);
  
  duration = pulseIn(echo_Pin, HIGH);
  distance = duration * 0.034 / 2; // Distancia en centímetros
  
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Contador de aforo
  if (distance >= distanciaMinima && distance <= distanciaMaxima) {
    delay(500); // Retardo para evitar contar múltiples veces por una sola persona
    contador++;
    
    // Asegurar que el contador no exceda 10
    if (contador > 10) {
      contador = 10;
    }

    // Actualizar display de 7 segmentos
    mostrarDigito(contador);

    // Actualizar Neopixel
    actualizarNeopixel();
    
    // Mostrar el contador en el monitor serie
    Serial.print("Contador: ");
    Serial.println(contador);
  }
  
  delay(300); // Pequeño retardo para estabilidad
}

void mostrarDigito(int digito) {
  // Tabla de verdad para mostrar los dígitos en el display de 7 segmentos
  switch (digito) {
    
    
    case 1:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    case 2:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
    case 3:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
    case 4:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 5:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 6:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 7:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    case 8:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 9:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    default:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
  }
}

void actualizarNeopixel() {
  // Cambiar el color del Neopixel basado en el número de personas
  uint32_t color;
  if (contador == 10) {
    color = pixels_OXCAL.Color(255, 0, 0); // Rojo
  } else {
    color = pixels_OXCAL.Color(0, 255, 0); // Verde
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels_OXCAL.setPixelColor(i, color);
  }
  pixels_OXCAL.show();
}
