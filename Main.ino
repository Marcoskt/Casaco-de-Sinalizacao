#include <Ultrasonic.h>
int ledPiscaDireito = 7, ledPiscaEsquerdo = 6 , btPiscaDireito = 3, btPiscaEsquerdo = 2, ledsAlerta = 8;
bool piscarLedDireito = false, piscarLedEsquerdo = false;
int tempoLedDireito = 400, tempoLedEsquerdo = 400, tempoLedsAlerta = 60;
long  ultimaExecLedEsq = 0;
long  ultimaExecLedDir  = 0;
long  ultimaExecAlerta  = 0;
int alerta = 100;

#define pino_trigger 10
#define pino_echo 11
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup() {
Serial.begin(9600);
pinMode(ledPiscaDireito, OUTPUT);
pinMode(ledPiscaEsquerdo, OUTPUT);
pinMode(ledsAlerta, OUTPUT);
pinMode(btPiscaDireito, INPUT_PULLUP);
pinMode(btPiscaEsquerdo, INPUT_PULLUP);
//Serial.println("iniciado");
}

void loop() {


//Pisca do led esquerdo 
if (millis() - ultimaExecLedEsq >= tempoLedEsquerdo){
  if(piscarLedEsquerdo){
    digitalWrite(ledPiscaEsquerdo, !digitalRead(ledPiscaEsquerdo));
  }else{
    digitalWrite(ledPiscaEsquerdo, LOW);
  }
  ultimaExecLedEsq = millis();
}



//Pisca do led direito
if (millis() - ultimaExecLedDir >= tempoLedDireito){
  if(piscarLedDireito){
    digitalWrite(ledPiscaDireito, !digitalRead(ledPiscaDireito));
  }else{
    digitalWrite(ledPiscaDireito, LOW);
  }
  ultimaExecLedDir = millis();
}



//Pisca de alerta de proximidade

//distância em CM
long microsec = ultrasonic.timing();
float cm = ultrasonic.convert(microsec, Ultrasonic::CM);
if (millis() - ultimaExecAlerta >= tempoLedsAlerta){
  if(cm <= alerta){
    digitalWrite(ledsAlerta, !digitalRead(ledsAlerta));
  }else{
    digitalWrite(ledsAlerta, LOW);
  }
  ultimaExecAlerta = millis();
}


//controle dos piscas
if(digitalRead(btPiscaDireito) == LOW){
 piscarLedDireito = !piscarLedDireito;
 delay(150);
}


if(digitalRead(btPiscaEsquerdo) == LOW){
  piscarLedEsquerdo = !piscarLedEsquerdo;
  delay(150);
}




}












