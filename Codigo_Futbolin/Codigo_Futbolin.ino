#include <TimeLib.h>
#define TRIGGER 3
#define ECHO 4
//infrarrojos
const byte sonido = 2;
float objetoDetectadoSensor = 0;

//Displays
//Arreglo para mostrar los valores en el display
byte display1[10][7]=
{
  {1,1,1,1,1,1,0},//0
  {0,0,0,0,1,1,0},//1
  {1,1,0,1,1,0,1},//2
  {0,1,0,1,1,1,1},//3
  {0,0,1,0,1,1,1},//4
  {0,1,1,1,0,1,1},//5
  {1,1,1,1,0,1,1},//6
  {0,0,0,1,1,1,0},//7
  {1,1,1,1,1,1,1},//8
  {0,1,1,1,1,1,1}//9
};

int goles1 = 0;
int goles2 = 0;

//Constantes
const float Velocidadsonido = 34300.0;
const float balonDetectado = 17.0;

//Funciones
void inicializarMarcador(){
  for (int e=0; e<7; e++){
      digitalWrite (e + 22, display1[0][e]);
      digitalWrite (e + 29, display1[0][e]);
   }
}

void iniciarTrigger(){
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIGGER, LOW);
}

float calcularDistancia(){
  unsigned long tiempo = pulseIn(ECHO, HIGH);
  float distancia = tiempo * 0.000001*Velocidadsonido/2.0;
  delay(10);
  return distancia;
}

void terminarJuego(int goles1, int goles2){
  for(int i=0;i<4;i++){
    for(int e=0; e<7; e++){
      if(display1[goles1][e]==1){
        digitalWrite (e + 22, 0);
      }if(display1[goles2][e]==1){
        digitalWrite (e + 29, 0);
      }
     }
    delay(200);
    for(int e=0; e<7; e++){
        digitalWrite (e + 22, display1[goles1][e]);
        digitalWrite (e + 29, display1[goles2][e]);
      }
     delay(200);
  }
  exit(0);
}


//SETUP
void setup()
{
  setTime(0,0,0,20,10,2015);
  Serial.begin(9600);
  pinMode(sonido, OUTPUT);
  for (int i=22; i<36; i++){//Definir pines de salida (Display)
    pinMode(i, OUTPUT);
  }
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  inicializarMarcador();
}

void loop()
{
  time_t t = now();
	Serial.println(minute(t));
	if(minute(t)==1){
	  terminarJuego(goles1,goles2);
	}
  iniciarTrigger();
  float distancia = calcularDistancia();
  if(distancia <= balonDetectado){
    digitalWrite(sonido, HIGH);
    goles1++;
    if(goles1>9){
      goles2++;
      goles1 = 0;
      for (int e=0; e<7; e++){
      digitalWrite (e + 29, display1[goles2][e]);
      }
      if(goles2==9 && goles1>9){
        goles1=0;
        goles2=0;
      }
    }
    for (int e=0; e<7; e++){
      digitalWrite (e + 22, display1[goles1][e]);
    }
    digitalWrite(sonido, LOW);
    delay(3000);
  }
 
}
