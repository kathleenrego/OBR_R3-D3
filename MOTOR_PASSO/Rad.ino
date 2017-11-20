#include <Ultrasonic.h>
#include <Servo.h>

int pino_passo_esquerda = 50; // Branco
int pino_direcao_esquerda = 51; // Azul
int pino_passo_direita = 52; // Laranja
int pino_direcao_direita = 53; // Verde

int pino_sensorCor_esquerda = A2; // Cinza
int pino_sensorCor_direita = A0; // Verde
int pino_sensorCor_centro = A1; // Laranja
int pino_sensorCor_frente_direita = A3; // Azul
int pino_sensorCor_frente_esquerda = A4; // Cinza

int servo_subir = 6; // Laranja
int servo_fechar = 5; // Laranja

Servo subir;
Servo fechar;

int direcao_esquerda = 1;
int direcao_direita = 1;
int passos_motor = 11400;

int e;
int c;
int d;
int f;

#define echoPinFrente 7
#define trigPinFrente 6

//#define echoPinEsquerda 9
//#define trigPinEsquerda 8

#define echoPinDireita 5
#define trigPinDireita 4

Ultrasonic ultrasonicFrente(6, 7);
Ultrasonic ultrasonicDireita(4, 5);

int sala = 0;

void setup()
{
  Serial.begin(9600);
  subir.attach(servo_subir);
  fechar.attach(servo_fechar);
  subir.write(15);
  fechar.write(60);

  pinMode(pino_sensorCor_direita, INPUT);
  pinMode(pino_sensorCor_centro, INPUT);
  pinMode(pino_sensorCor_esquerda, INPUT);
  pinMode(pino_sensorCor_frente_esquerda, INPUT);
  pinMode(pino_sensorCor_frente_direita, INPUT);

  pinMode(pino_passo_esquerda, OUTPUT);
  pinMode(pino_direcao_esquerda, OUTPUT);

  pinMode(pino_passo_direita, OUTPUT);
  pinMode(pino_direcao_direita, OUTPUT);

  pinMode(A10, INPUT); // direita
  pinMode(A11, INPUT);// centro
  pinMode(A9, INPUT); // frente
  pinMode(A8, INPUT); // esquerda
  pinMode(7,INPUT);

  pinMode(24, INPUT); // sensor rampa
  pinMode(25, INPUT); // esquerda ---- levemente bugado
  pinMode(27, INPUT); // direita-baixo --- altamente bugado

  pinMode(echoPinFrente,INPUT);
  pinMode(trigPinFrente,OUTPUT);
  pinMode(echoPinDireita,INPUT);
  pinMode(trigPinDireita,OUTPUT);

  Serial.begin(9600);
}


void loop(){

    rotacionar(1, 1, 11400);

}

void sensorDeLinha(){
    if (analogRead(A9) > 500){
      f = 0;
    }else{
      f = 1;
      }
  if (analogRead(A11) < 500){ // diferentao - centro
      c = 0;
  }else{
      c = 1;
  }
 if (analogRead(A10) > 500){
      d = 0;
  }else{
      d = 1;
  }
   if (analogRead(A8) > 500){
      e = 0;
  }else{
      e = 1;
  }
}
void ultraFrente(){
  
  digitalWrite(trigPinFrente, LOW);
  delay(5);

  digitalWrite(trigPinFrente, HIGH);
  delay(5);

  digitalWrite(trigPinFrente, LOW);

  // faz a conversão do tempo de resposta do echo em centimetros.
  float distanciaF;
  long microsec = ultrasonicFrente.timing();  
  distanciaF = ultrasonicFrente.convert(microsec, Ultrasonic::CM);
  
  return distanciaF;
}

void ultraDireita(){
  digitalWrite(trigPinDireita, LOW);
  delay(5);

  digitalWrite(trigPinDireita, HIGH);
  delay(5);

  digitalWrite(trigPinDireita, LOW);

  // faz a conversão do tempo de resposta do echo em centimetros.
  float distanciaD;
  long microsec = ultrasonicDireita.timing();  
  distanciaD = ultrasonicDireita.convert(microsec, Ultrasonic::CM);

  return distanciaD;
}
void frente_tras (int x, int y, int p) //Frente --> x = 1 p = passos | Tras --> x = 0 p = passos
{
  for (int f = 0 ; f < p ; f++)
  {
    direcao_direita = x;
    direcao_esquerda = y;
    

    digitalWrite(pino_direcao_esquerda, direcao_esquerda);
    digitalWrite(pino_direcao_direita, direcao_direita);

    digitalWrite(pino_passo_esquerda, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_esquerda, 0);
    delayMicroseconds(100);
    digitalWrite(pino_passo_direita, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_direita, 0);
    delayMicroseconds(100);
  }
}


void rotacionar (int x, int y, int p) // Esquerda -- > x = 1 y = 0 p = passos | Direita --> x = 0 y = 1 p = passos
{
  for (int f = 0 ; f < p; f++)
  {
    direcao_direita = x;
    digitalWrite(pino_direcao_direita, direcao_direita);

    digitalWrite(pino_passo_direita, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_direita, 0);
    delayMicroseconds(100);


    direcao_esquerda = y;
    digitalWrite(pino_direcao_esquerda, direcao_esquerda);

    digitalWrite(pino_passo_esquerda, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_esquerda, 0);
    delayMicroseconds(100);
  }
}
