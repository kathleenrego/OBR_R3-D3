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
}

void loop(){
  frente_tras(1, 0, 11400);
}


void garra_subir (int x)
{
  if (x == 1)
  {
    for (int f = 15 ; f < 125 ; f++)
    {
      subir.write(f);
      delay(30);
    }
  }
  else
  {
    for (int f = 125 ; 15 < f; f--)
    {
      subir.write(f);
      delay(30);
    }
  }
}

void garra_fechar (int x)
{
  if (x == 1)
  {
    for (int f = 0 ; f < 60 ; f++)
    {
      fechar.write(f);
      delay(30);
    }
  }
  else
  {
    for (int f = 60 ; 1 < f; f--)
    {
      fechar.write(f);
      delay(30);
    }
  }
}

void frente_tras (int x, int y, int p) //Frente --> x = 1 p = passos | Tras --> x = 0 p = passos
{
  for (int f = 0 ; f < p ; f++)
  {
    frenteDireita = x;
    frenteEsquerda = y;
    

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

void esquerda (int x, int p) //Frente -- > x = 1 p = passos | Tras --> x = 0 p = passos
{
  for (int f = 0 ; f < p; f++)
  {
    direcao_esquerda = x;
    digitalWrite(pino_direcao_esquerda, direcao_esquerda);

    digitalWrite(pino_passo_esquerda, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_esquerda, 0);
    delayMicroseconds(100);
  }
}

void direita (int x, int p) //Frente -- > x = 1 p = passos | Tras --> x = 0 p = passos
{
  for (int f = 0 ; f < p; f++)
  {
    direcao_direita = x;
    digitalWrite(pino_direcao_direita, direcao_direita);

    digitalWrite(pino_passo_direita, 1);
    delayMicroseconds(100);
    digitalWrite(pino_passo_direita, 0);
    delayMicroseconds(100);
  }
}

void lerLinha()
{
  int xc = 415;
  int xd = 425;
  int xe = 535;
  int xfe = 97;
  int xfd = 640;

  int centro = analogRead((pino_sensorCor_centro));
  int direita = analogRead((pino_sensorCor_direita));
  int esquerda = analogRead((pino_sensorCor_esquerda));
  int frente_esquerda = analogRead((pino_sensorCor_frente_esquerda));
  int frente_direita = analogRead((pino_sensorCor_frente_direita));

  if (centro < xc )
  {
    c = 0;
  }
  else
  {
    c = 1;
  }

  if (direita < xd )
  {
    d = 0;
  }
  else
  {
    d = 1;
  }

  if (esquerda < xe )
  {
    e = 0;
  }
  else
  {
    e = 1;
  }

  if (frente_esquerda < xfe)
  {
    fe = 0;
  }
  else
  {
    fe = 1;
  }

  if (frente_direita < xfd)
  {
    fd = 0;
  }
  else
  {
    fd = 1;
  }

}

void seguirLinha()
{
  lerLinha();

  while (((!fe) && (fd) && (!c)) || ((!fe) && (fd) && (e) && (!d))) //Alinhamento simples esquerda
  {
    direita (1, 900);
    lerLinha();
  }
  while ((fe) && (fd) && (c) && (!e) && (d)) //Alinhamento 1 sensor esquerda
  {
    direita (1, 2500);
    lerLinha();
  }

  while (((fe) && (!fd) && (!c)) || ((fe) && (!fd) && (!e) && (d))) //Alinhamento simples direita
  {
    esquerda (1, 900);
    lerLinha();
  }
  while ((fe) && (fd) && (c) && (e) && (!d)) //Alinhamento 1 sensnor direita
  {
    esquerda (1, 2500);
    lerLinha();
  }

  if ((fe) && (fd) && (!c) && (!d)) // 90 esquerda
  {
    lerLinha();
    while (fe && fd)
    {
      frente_tras(0, 1000);
      lerLinha();
    }
    rotacionar(0, 1, 7600);
  }
  else if ((fe) && (fd) && (!c) && (!e) && (d))   //90 Direita
  {
    lerLinha();
    while (fe && fd)
    {
      frente_tras(0, 1000);
      lerLinha();
    }

    rotacionar(1, 0, 7600);

  }
  else
  {
    lerLinha();
    frente_tras (1, 100);
  }
}

void seguirLinhaRampa()
{
  lerLinha();

  if ((!fe) && (fd) && (!c) && (e) && (d)) //Alinhamento simples esquerda
  {
    direita (1, 500);
    lerLinha();
  }

  else if ((fe) && (!fd) && (!c) && (e) && (d)) //Alinhamento simples direita
  {
    esquerda (1, 500);
    lerLinha();
  }
  else
  {
    frente_tras (1, 100);
  }
}

void desvia()
{
  long distancia = ultraFrente();

  if ( distancia < 7)
  {
    delay(2);

    rotacionar (0, 1, 7600);
    frente_tras (1, 9000);
    rotacionar (1, 0, 7600);
    frente_tras (1, 23000);
    rotacionar (1, 0, 7600);
    frente_tras (1, 9000);
    rotacionar (0, 1, 7600);
  }
}

void rampa()
{
  long distanciaDireita = ultraDireita();
  long distanciaEsquerda = ultraEsquerda();

  if ((sala == 0) || (sala == 1))
  {
    if ((distanciaDireita < 25) && (distanciaEsquerda < 25))
    {
      seguirLinhaRampa();
      sala = 1;
    }
  }

  if ((((distanciaDireita < 25) && (distanciaEsquerda > 40)) || ((distanciaEsquerda < 25) && (distanciaDireita > 40))) && (sala == 1))
  {
      sala = 2; // Rampa Direita
      long distancia = ultraFrente();
      
      if (distancia < 40) //Verificando se tem bola no inicio da sala
      {
        float passos = distancia_Bola(distancia);

        frente_tras(1, passos);

        pegarBola();

        frente_tras(1, (22000 - passos));
        rotacionar (0, 1, 7600);
        frente_tras (1, 16500);
        procurar_Escape();

      }
      else
      {
        frente_tras (1, 22000);
        rotacionar (1, 0, 7600);
        distancia = ultraFrente();
      }

      if (distancia < 24) // Bola no centro da sala
      {
        float passos = distancia_Bola(distancia);

        frente_tras(1, passos);

        pegarBola();

        frente_tras(1, (16500 - passos));
        busca();
      }
      else
      {
        frente_tras (1, 16500);
        busca();
      }
  }
}

void busca()
{
  int giro = 250;
  int frente = 500;
  int i = 0; //Contador de passos do giro
  int j = 0 ; //Contador de passos até chegar a bola
  long distancia = ultraFrente();

  while (distancia > 28) //Raio para pegar a bola
  {
    distancia = ultraFrente();
    delay(500);
    rotacionar(1, 0, giro);
    i++;
  }

  rotacionar(1, 0, 500);

  float passos = distancia_Bola(distancia);

  frente_tras(1, passos);

  pegarBola();

  frente_tras(0, passos);
  //rotacionar(0, 1, (gi/ro * i));
  procurar_Escape();
}
void pegarBola()
{
  garra_fechar(0);
  delay(1000);
  garra_subir(1);
  delay(1000);
}

void procurar_Escape()
{
  int k = 0;

  delay(2000);
  rotacionar(1, 0, 3800);

  delay(500);
  long distancia = ultraFrente();

  if (distancia <= 40)
  {
    delay(500);
    distancia = ultraFrente();

    while (distancia >= 4)
    {
      delay(500);
      distancia = ultraFrente();
      frente_tras(1, 1000);
      k++;
    }

    garra_fechar(1);

    frente_tras(0, (1000 * k));

    rotacionar(1, 0, 3800);

    garra_subir(0);

    busca();

  }

  rotacionar(0, 1, 7600); //Verificar outro canto da sala
  distancia = ultraFrente();
  delay(2000);

  if (distancia <= 40)
  {
    delay(500);
    distancia = ultraFrente();

    while (distancia >= 4)
    {
      delay(500);
      distancia = ultraFrente();
//      frente_tras(1, 1000);
      k++;
    }

    garra_fechar(1);

//    frente_tras(0, (1000 * k));

    rotacionar(1, 0, 3800);

    garra_subir(0);

    rotacionar(0, 1, 7600);

    busca();
  }

  delay(2000);
  rotacionar(0, 1, 7200); //Verificar outro canto da sala
  distancia = ultraFrente();

  if (distancia <= 40)
  {
    delay(500);
    distancia = ultraFrente();

    while (distancia >= 4)
    {
      delay(500);
      distancia = ultraFrente();
//      frente_tras(1, 1000);
      k++;
    }

    garra_fechar(1);

//    frente_tras(0, (1000 * k));

    rotacionar(0,1, 3800);

    garra_subir(0);

    rotacionar(1, 0, 15600);

    busca();
  }
}

float ultraFrente()
{
  digitalWrite(trigPinFrente, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinFrente, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFrente, LOW);
  digitalWrite(trigPinFrente, LOW);

  float tempo;
  tempo = pulseIn(echoPinFrente, HIGH);
  float distanciaF = tempo / 29.4 / 2;

  return distanciaF;
}

float ultraEsquerda()
{
  digitalWrite(trigPinEsquerda, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinEsquerda, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinEsquerda, LOW);
  digitalWrite(trigPinEsquerda, LOW);

  float tempo;
  tempo = pulseIn(echoPinEsquerda, HIGH);
  float distanciaE = tempo / 29.4 / 2;

  return distanciaE;
}

float ultraDireita()
{
  digitalWrite(trigPinDireita, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinDireita, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinDireita, LOW);
  digitalWrite(trigPinDireita, LOW);

  float tempo;
  tempo = pulseIn(echoPinDireita, HIGH);
  float distanciaD = tempo / 29.4 / 2;

  return distanciaD;
}

float distancia_Bola(float dist)
{
  float result = (dist * 4300) / 10;
  return result;
}

