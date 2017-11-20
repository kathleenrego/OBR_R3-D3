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
int frenteEsquerda = 0;
int frenteDireita = 1;
int trasEsquerda = 1;
int trasDireita = 0;
int passos_motor = 11400;

int e;
int c;
int d;
int fe;
int fd;

#define echoPinFrente 3
#define trigPinFrente 4

#define echoPinEsquerda 9
#define trigPinEsquerda 8

#define echoPinDireita 2
#define trigPinDireita 7

Ultrasonic ultrasonicFrente(4, 3);
Ultrasonic ultrasonicEsquerda(8, 9);
Ultrasonic ultrasonicDireita(7, 2);

int sala = 0;
