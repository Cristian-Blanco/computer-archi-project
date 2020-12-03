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
  Serial.print(distancia);
  Serial.println("cm");
  delay(10);
  return distancia;
}


//SETUP
void setup()
{
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
  iniciarTrigger();
  float distancia = calcularDistancia();
  if(distancia <= balonDetectado){
    digitalWrite(sonido, HIGH);
    goles1++;
    if(goles1>9){
      goles2++;
      goles1 = 0;
      Serial.println(goles2 + " " + goles1);
      for (int e=0; e<7; e++){
      digitalWrite (e + 29, display1[goles2][e]);
      }
      if(goles2==9 && goles1>9){
        goles1=0;
        goles2=0;
      }
    }
    Serial.println(goles1);
    for (int e=0; e<7; e++){
      digitalWrite (e + 22, display1[goles1][e]);
    }
    digitalWrite(sonido, LOW);
    delay(3000);
    Serial.println("OBSTACULO DETECTADO EN VERDE");
  
  }
 
}
