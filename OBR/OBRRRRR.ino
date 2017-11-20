#include <Servo.h> 
Servo motorELE;
Servo motorFEC;
#include <Ultrasonic.h>
#define echoPinF 31 //Pino 10 recebe o pulso do echo do Ult da Frente
#define trigPinF 30 //Pino 9 envia o pulso para gerar o echo do Ult da Frente
#define echoPinLE 45 //Pino 11 recebe o pulso do echo o Ult do Lado Esquerdo
#define trigPinLE 44 //Pino 12 envia o pulso para gerar o echo do Ult do lado Direito

const int rD = 37, gD = 38, bD = 39; //portas dos leds dos sensores de cor da esquerda e direita
const int inD = A3, inE = A4; //saídas dos sensores de cor da direita e esquerda
int corD, e, m, f, d, td, te, corE; // recebem o que é lido pelos sensores de cor
int enE = 5, in1E = 6, in2E = 7, enD = 2, in3D = 3, in4D = 4; // ponte-h motores 
int transE = 0, transD = 0;
int transAnte = 0;
int estadoAnte = 0;
Ultrasonic ultrasonicF(30,31); //Ultrassoninc da Frente
Ultrasonic ultrasonicLE(44,45); //Ultrassinic do Lado Esquerdo 
int velocidade2 = 85, velocidadeC = 200;
long timeD, timeD2, timeD3;
//int vo = 190;
//int ve = 180;
float distancia = 0;
float distancia2 = 0;
int x = 0;

void setup()
{
  pinMode(A9, INPUT);
  pinMode(10, INPUT);
  pinMode(53, INPUT);
  pinMode(12, INPUT);
  pinMode(26, INPUT);
  pinMode(52, INPUT);
  pinMode(51, INPUT);
  pinMode(50, INPUT);
  //Motores
  pinMode(in4D, OUTPUT); // Direita
  pinMode(in3D, OUTPUT); // Direita
  pinMode(enD, OUTPUT); //Enable Direita
  pinMode(enE, OUTPUT); //Enable Esquerda
  pinMode(in1E, OUTPUT); //Esquerda
  pinMode(in2E, OUTPUT); //Esquerda
  motorELE.attach(12);
  motorFEC.attach(11); 
  motorELE.write(30); //alto 40  baixo 140 alto
  motorFEC.write(50); //maximo 50 ( para varrer) minimo 15 (fechar) andar (120) 

  //Ultrassonics 
  pinMode(echoPinF, INPUT); //pino 9 como entrada
  pinMode(trigPinF, OUTPUT); // pino 10 como saida
  pinMode(echoPinLE, INPUT); //pino 9 como entrada
  pinMode(trigPinLE, OUTPUT); // pino 10 como saida


  //Sensores De Cor 
  pinMode(rD, OUTPUT); 
  pinMode(bD, OUTPUT);
  pinMode(gD, OUTPUT);
  pinMode(inD, INPUT);
  pinMode(inE, INPUT);
  

  digitalWrite(rD, LOW);
  digitalWrite(gD, LOW);
  digitalWrite(bD, LOW);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  

  Serial.begin(9600);
}

void loop()
{     
  
  Serial.print("Frente-----> ");
   Serial.println(analogRead(A5));
   Serial.println();
   Serial.print("Esquerda-----> ");
   Serial.println(analogRead(A7));
   Serial.println();
   Serial.print("Meio-----> ");
   Serial.println(analogRead(A6));
   Serial.println();
   Serial.print("direita-----> ");
   Serial.println(analogRead(A8));
   Serial.println();
   delay(1000);
   
/**/

}  

void frente(){
  norte(80);
}



void rampaRedutor(){
    norte(150); 
    delay(600);
    norte(0);
    delay(2000);
    if(digitalRead(10) == 1){
      delay(1000);
    }
    
    if(digitalRead(10) == 1){
      delay(500);
    
      int g=0;
      while (g==0){
         if(e==0 && d==0){
          norte(250);
          sensorDeLinha();
        }
        if(e == 1 && d == 0){
           oesteR(250);
          sensorDeLinha();
        }
        if(e == 0 && d == 1){
          lesteR(250);
          sensorDeLinha();
        }
        sensorDeCor(&corD, &corE);
        if(te == 3 && td == 3 ){
          norte(250);          
          delay(500);
          norte(0);
          delay(200); 
          g=1;
        }
     }   
   }
 }
 
void desviarObjeto(){
  if(ultraFrente() <= 10){
    sul(90);
    delay(300);
    timeD = millis();
    while(ultraLateralE() > 15){
      leste(220);      
    }
    long timeD2 = millis();

    while(ultraLateralE() <= 18){
          norte(80);
      }
    norte(90);
    delay(300);
    timeD2 = timeD2 - (timeD);
    timeD = millis();      
      timeD3=0;
      while((timeD2-300)  > (timeD3-timeD)){
          oeste(220);
          timeD3 = millis(); 

    }

while(ultraLateralE() > 18){
      norte(80);      
    }

while(ultraLateralE() < 18){
      norte(80);      
    }
    norte(80);
    delay(300);
    timeD3=0;
    timeD = millis();      
    while((timeD2-100)  > (timeD3-timeD)){
          oeste(220);          
          timeD3 = millis(); 
          Serial.println("passou");      
    }
    sensorDeLinha();
    while (e == 0 && d == 0){
      norte(80);
      sensorDeLinha();
    }
    leste(240);
    delay(700); 
    norte(0);
    delay(5000);
  }
}



void sala3(){
  if (ultraLateralE()> 25){
    LadoEsquerdo();
  }
  else if (ultraLateralE()<25){
    LadoDireito();
  }
}

void varrerD(){
  sul(80);
  delay(800);
  norte(0);
  delay(300);
  motorELE.write(30);
  motorFEC.write(50);
  norte(0);
  delay(300); 
  leste(200);
  delay(200);
  norte(0);
  delay(100);
  
   while(ultraFrente() >= 29){
      leste(210); //
   }
   if(ultraFrente() <= 29){
      if(ultraFrente() < 20){
        sul(80);
        delay(600);
      }      
      motorELE.write(135); //alto 40  baixo 140 alto
      delay(500);
      motorFEC.write(50); //maximo 50 ( para varrer) minimo 15 (fechar) andar (120)
      norte(0);
      delay(400);
      long timeF = millis();
      long timeAt;
      while(analogRead(A9) < 600){
        frente();
        timeAt = millis();
  
        if ((timeAt-timeF) > 6000){
          timeF = millis();  
          varrerE();
          
        }
      }          
   }
}

void varrerE(){
  sul(80);
  delay(800);
  norte(0);
  delay(300);
  motorELE.write(30);
  motorFEC.write(50);
  norte(0);
  delay(300); 
  oeste(200);
  delay(200);
  norte(0);
  delay(100);
   while(ultraFrente() >= 29){
      oeste(210); //
   }
   if(ultraFrente() <= 29){
      if(ultraFrente() < 20){
        sul(80);
        delay(700);
      }      
      motorELE.write(135); //alto 40  baixo 140 alto
      delay(500);
      motorFEC.write(50); //maximo 50 ( para varrer) minimo 15 (fechar) andar (120)
      norte(0);
      delay(400);
      long timeF = millis();
      long timeAt;
      while(analogRead(A9) < 600){
        frente();
        timeAt = millis();
  
        if ((timeAt-timeF) > 6000){
          timeF = millis();  
          varrerD();
          
        }
      }          
   }
}


void LadoEsquerdo (){
  
   while(ultraFrente() >= 30){
    frente();
   }   
   while(ultraLateralE() < 110){
     oeste(210); //
   }
  
   delay(300);
   norte(0);
   delay(200); //
   while(ultraFrente() >= 35){
     frente();
   }
   delay(100); //
   int w=0;
   while(ultraFrente() >= 29){
      oeste(210); //
   }
   if(ultraFrente() <= 31){
      if(ultraFrente() < 20){
        sul(80);
        delay(700);
      }      
      motorELE.write(135); //alto 40  baixo 140 alto
      delay(500);
      motorFEC.write(50); //maximo 50 ( para varrer) minimo 15 (fechar) andar (120)
      norte(0);
      delay(400);
      long timeF = millis();
      long timeAt;
      while(analogRead(A9) < 600){
        frente();
        timeAt = millis();
  
        if ((timeAt-timeF) > 6000){
          timeF = millis();   
          varrerE();
          
        }
      }          
      if(analogRead(A9) > 600){
        int f = 0;
        
        while (f == 0){  
          norte(80);
          delay(300);
          norte(0);
          delay(500);
          motorFEC.write(8);
          delay(2000);
          motorELE.write(40);
           //maximo 50 ( para varrer) minimo 15 (fechar) andar (120)
          delay(2000);
           //alto 40  baixo 140 alto
          f = 1;
          // chamar funçao de entrega 
        }
        while( f==1){
            long to=millis();
            long tt;
            while(digitalRead(51)==0){
            norte(90);
            tt = millis();
              if((tt - to)>4000){
                oeste(200);
                delay(200);
                to=millis();
              }
            if((digitalRead(9)==1 || digitalRead(52)==1 || digitalRead(50)==1) && digitalRead(51)==0){
              sul(80);
              delay(100);
              sul(0);
              delay(200);
              motorELE.write(110); //alto 40  baixo 140 alto
              delay(1000);
              motorFEC.write(50); //maximo 50 ( para varrer) minimo 15 (fechar) andar (120)
              delay(1000);
              sul(100);
              delay(150);
              
          }
        }
        if (digitalRead(51)==1){
            sudoeste(220);
            delay(200);
            oeste(220);
            delay(600);
        }
    }
  }  
}
}

void LadoDireito (){
  
   while(ultraFrente() >= 30){
    frente();
   }   
   while(ultraLateralE() < 30){
     leste(210); //
   }
  
   delay(700);
   norte(0);
   delay(200); //
   while(ultraFrente() >= 35){
     frente();
   }
   delay(100); //
   int w=0;
   while(ultraFrente() >= 29){
      leste(210); //
   }
   if(ultraFrente() <= 20){
      if(ultraFrente() < 20){
        sul(80);
        delay(700);
      }      
      motorELE.write(135); //alto 40  baixo 140 alto
      delay(500);
      motorFEC.write(50); //maximo 50 ( para varrer) minimo 15 (fechar) andar (120)
      norte(0);
      delay(400);
      long timeF = millis();
      long timeAt;
      while(analogRead(A9) < 600){
        frente();
        timeAt = millis();
  
        if ((timeAt-timeF) > 7000){
          timeF = millis();
          varrerD();
        }
      }          
      if(analogRead(A9) > 600){
        int f = 0;
        
        while (f == 0){  
          norte(80);
          delay(300);
          norte(0);
          delay(500);
          motorFEC.write(8);
          delay(2000);
          motorELE.write(40);
           //maximo 50 ( para varrer) minimo 15 (fechar) andar (120)
          delay(2000);
           //alto 40  baixo 140 alto
          f = 1;
          // chamar funçao de entrega 
        }
        while(f== 1){
            long to=millis();
            long tt;
            while(digitalRead(51)==0){
            norte(120);
            tt = millis();
              if((tt - to)>4000){
                leste(200);
                delay(600);
                to=millis();
              }
            if((digitalRead(9)==1 || digitalRead(52)==1 || digitalRead(50)==1) && digitalRead(51)==0){
              sul(80);
              delay(100);
              sul(0);
              delay(200);
              motorELE.write(110); //alto 40  baixo 140 alto
              delay(1000);
              motorFEC.write(50); //maximo 50 ( para varrer) minimo 15 (fechar) andar (120)
              delay(1000);
              sul(100);
              delay(150);
              
          }
        }
        if (digitalRead(51)==1){
            sudeste(220);
            delay(200);
            leste(220);
            delay(600);
        }
    }
  }  
}
}




void sensorDeLinha(){  
  if(analogRead(A5) > 150){
    f = 0;
    }else{
      f = 1;  
  }
  if(analogRead(A6) > 80){
      m = 0;

      }else{
        m = 1;
      }
  if(analogRead(A7) > 250){
      e = 0;
      }else{
        e = 1;
        
            }if(analogRead(A8) > 250){
              d = 0;
              }else{
                d = 1;
              }
            }

            void sensorDeCor(int *corD, int *corE)
            {
              *corD = 0; 
              *corE = 0; 
              int rvalD, gvalD, bvalD, rvalE, gvalE, bvalE;
              rvalD = 0;
              gvalD = 0;
              bvalD = 0;
              rvalE = 0;
              gvalE = 0;
              bvalE = 0;

  digitalWrite(rD, HIGH);  // Liga o led vermelho do sensor da direita.
  delay(5);

  rvalD = rvalD + analogRead(inD); // Recebe o que está sendo lido pelo fototransistor da direita enquanto o led vermelho esta ligado.
  rvalE = rvalE + analogRead(inE); // Recebe o que está sendo lido pelo fototransistor da esquerda enquanto o led vermelho esta ligado.
  delay(5);

  digitalWrite(rD, LOW); //Apaga o led vermelho do sensor da direita.

  delay(5);

  digitalWrite(gD, HIGH);
  delay(5);

  gvalD = gvalD + analogRead(inD);
  gvalE = gvalE + analogRead(inE);
  delay(5);

  digitalWrite(gD, LOW);

  delay(5);

  digitalWrite(bD, HIGH);
  delay(5);

  bvalD = bvalD + analogRead(inD);
  bvalE = bvalE + analogRead(inE);
  delay(5);

  digitalWrite(bD, LOW);
  
  //Sensor 1 - Esquerda
  int soma;
  soma = rvalE + gvalE + bvalE;
  Serial.print("Esquerdo-----> ");
  Serial.println(soma);

  
  if((soma > 230) && (soma < 600)){
    *corE = 2; //verde
  }
  else if (soma > 1600){
    *corE = 3; //prata
  }
  te = *corE;

  //Sensor 3 - Direita
  int somador;
  somador = rvalD+gvalD+bvalD;
  
  Serial.print("Direito-----> ");
  Serial.println(somador);
  
  if((somador > 1100) && (somador < 1700)){
    *corD = 2; //verde
  }
  else if ( somador > 2930){
    *corD = 3; //prata
  }
  td = *corD;
}

//----------------------------------------> Ultrassonics
float ultraFrente(){
  digitalWrite(trigPinF, LOW);
  delay(5);

  digitalWrite(trigPinF, HIGH);
  delay(5);

  digitalWrite(trigPinF, LOW);

  // faz a conversão do tempo de resposta do echo em centimetros.
  float distanciaF;
  long microsec = ultrasonicF.timing();  
  distanciaF = ultrasonicF.convert(microsec, Ultrasonic::CM);
  return distanciaF; 

}

float ultraLateralE(){
  digitalWrite(trigPinLE, LOW);
  delay(5);

  digitalWrite(trigPinLE, HIGH);
  delay(5);

  digitalWrite(trigPinLE, LOW);

  // faz a conversão do tempo de resposta do echo em centimetros.
  float distanciaLE;
  long microsec = ultrasonicLE.timing();  
  distanciaLE = ultrasonicLE.convert(microsec, Ultrasonic::CM);
  return distanciaLE; 

}





//----------------------------------------> Funções dos Motores
void sul (int velocidade)
{
  analogWrite(enD,velocidade);
  digitalWrite(in3D, HIGH);
  digitalWrite(in4D, LOW);

  analogWrite(enE,velocidade);
  digitalWrite(in1E, HIGH);
  digitalWrite(in2E, LOW);
}
void sudoeste (int velocidade)
{
  analogWrite(enD,velocidade);
  digitalWrite(in3D, HIGH);
  digitalWrite(in4D, LOW);

  analogWrite(enE,velocidade);
  digitalWrite(in1E, LOW);
  digitalWrite(in2E, LOW);
}
void sudeste (int velocidade)
{
  analogWrite(enD,velocidade);
  digitalWrite(in3D, LOW);
  digitalWrite(in4D, LOW);

  analogWrite(enE,velocidade);
  digitalWrite(in1E, HIGH);
  digitalWrite(in2E, LOW);
}

void norte(int velocidade)
{
  analogWrite(enD, velocidade);
  digitalWrite(in3D, LOW);
  digitalWrite(in4D, HIGH);

  analogWrite(enE, velocidade);
  digitalWrite(in1E, LOW);
  digitalWrite(in2E, HIGH);
}

void leste(int velocidade)
{
  analogWrite(enD,velocidade);
  digitalWrite(in3D, HIGH);
  digitalWrite(in4D, LOW);

  analogWrite(enE,velocidade);
  digitalWrite(in1E, LOW);
  digitalWrite(in2E, HIGH);
}

void noroeste(int velocidade)
{
  analogWrite(enD,velocidade);
  digitalWrite(in3D, LOW);
  digitalWrite(in4D, HIGH);

  analogWrite(enE,velocidade);
  digitalWrite(in1E, LOW);
  digitalWrite(in2E, LOW);
}
void lesteC ()
{
  analogWrite(enD,190);
  digitalWrite(in3D, HIGH);
  digitalWrite(in4D, LOW);

  analogWrite(enE,190);
  digitalWrite(in1E, LOW);
  digitalWrite(in2E, HIGH);
}

void lesteR (int velocidade)
{
  analogWrite(enD,160);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  digitalWrite(in3D, LOW);
  digitalWrite(in4D, HIGH);

  analogWrite(enE,velocidade);
  digitalWrite(in1E, LOW);
  digitalWrite(in2E, HIGH);
}

void oeste (int velocidade)
{
  analogWrite(enE,velocidade);
  digitalWrite(in1E, HIGH);
  digitalWrite(in2E, LOW);

  analogWrite(enD,velocidade);
  digitalWrite(in3D, LOW);
  digitalWrite(in4D, HIGH);
}
void oesteC (int velocidade)
{
  analogWrite(enE,120);
  digitalWrite(in1E, HIGH);
  digitalWrite(in2E, LOW);

  analogWrite(enD,120);
  digitalWrite(in3D, LOW);
  digitalWrite(in4D, HIGH);
}

void oesteR (int velocidade)
{
  analogWrite(enE,160);
  digitalWrite(in1E, LOW);
  digitalWrite(in2E, HIGH);

  analogWrite(enD,velocidade);
  digitalWrite(in3D, LOW);
  digitalWrite(in4D, HIGH);
}

