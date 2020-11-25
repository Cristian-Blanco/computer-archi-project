#include <Keypad.h>

//matriz del teclado
const byte FILAS = 4;
const byte COLUMNAS = 4;
//esta matriz muestra el contenido que tiene el teclado
char keys[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte pinesFilas[FILAS] = {9, 8, 7, 6}; //los pines de filas
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2};//pines de columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);//funcion de la libreria para que detecte el teclado

char TECLA;//variable que nos ayudara a mostrar el boton presionado
int triqui[3][3] = {//generamos el tablero a utilizar en el triqui
  {0,0,0},
  {0,0,0},
  {0,0,0}
};
boolean jugador = true; //esta variable nos permite saber si esta jugando el humano o el robot
int jugadas = 0;

//funciones
boolean comprobarMovimiento(int var){
  boolean existente = false;
  switch(var){
    case 1:
      existente = (triqui[0][0] == 0) ? false : true;
      break;
    case 2:
      existente = (triqui[0][1] == 0) ? false : true;
      break;
    case 3:
      existente = (triqui[0][2] == 0) ? false : true;
      break;
    case 4:
      existente = (triqui[1][0] == 0) ? false : true;
      break;
    case 5:
      existente = (triqui[1][1] == 0) ? false : true;
      break;
    case 6:
      existente = (triqui[1][2] == 0) ? false : true;
      break;
    case 7:
      existente = (triqui[2][0] == 0) ? false : true;
      break;
    case 8:
      existente = (triqui[2][1] == 0) ? false : true;
      break;
    case 9:
      existente = (triqui[2][2] == 0) ? false : true;
      break;
  }
  return existente;
}

boolean comprobarMovimientoHumano(char var){
  boolean existente = false;
  switch(var){
    case '1':
      existente = (triqui[0][0] == 0) ? false : true;
      break;
    case '2':
      existente = (triqui[0][1] == 0) ? false : true;
      break;
    case '3':
      existente = (triqui[0][2] == 0) ? false : true;
      break;
    case '4':
      existente = (triqui[1][0] == 0) ? false : true;
      break;
    case '5':
      existente = (triqui[1][1] == 0) ? false : true;
      break;
    case '6':
      existente = (triqui[1][2] == 0) ? false : true;
      break;
    case '7':
      existente = (triqui[2][0] == 0) ? false : true;
      break;
    case '8':
      existente = (triqui[2][1] == 0) ? false : true;
      break;
    case '9':
      existente = (triqui[2][2] == 0) ? false : true;
      break;
  }
  return existente;
}

void hayGanador(boolean jugador){
  if(jugador){
      for(int i=0;i<3;i++){
        if(triqui[i][0]==1&&triqui[i][1]==1&&triqui[i][2]==1){
          Serial.print("El jugador ");
          Serial.print("humano");
          Serial.print(" ha ganado");
          delay(1000);
           exit(0);
        }
        if(triqui[0][i]==1&&triqui[1][i]==1&&triqui[2][i]==1){
          Serial.print("El jugador ");
          Serial.print("humano");
          Serial.print(" ha ganado");
          delay(1000);
          exit(0);
        }
      }
      
      if(((triqui[0][0]==1&&triqui[2][2]==1)||(triqui[0][2]==1&&triqui[2][0]==1))&&triqui[1][1]==1){
        Serial.print("El jugador ");
        Serial.print("humano");
        Serial.print(" ha ganado");
        delay(1000);
        exit(0);
      }
  }else{
    for(int i=0;i<3;i++){
        if(triqui[i][0]==2&&triqui[i][1]==2&&triqui[i][2]==2){
          Serial.print("El jugador ");
          Serial.print("Robot");
          Serial.print(" ha ganado");
          delay(1000);
           exit(0);
        }
        if(triqui[0][i]==2&&triqui[1][i]==2&&triqui[2][i]==2){
          Serial.print("El jugador ");
          Serial.print("Robot");
          Serial.print(" ha ganado");
          delay(1000);
          exit(0);
        }
      }
      
      if(((triqui[0][0]==2&&triqui[2][2]==2)||(triqui[0][2]==2&&triqui[2][0]==2))&&triqui[1][1]==2){
        Serial.print("El jugador ");
        Serial.print("Robot");
        Serial.print(" ha ganado");
        delay(1000);
        exit(0);
      }
  }
}

//main
void setup(){
  Serial.begin(9600); //habilitamos el monitor de serie
  for(int i=22; i<=39; i++){//obtenemos todos los pines de salida de los diodo leds
    pinMode(i, OUTPUT);
  }

  randomSeed(analogRead(A0));
}

void loop(){
  
  TECLA = teclado.getKey();//obtenemos el valor tocado en el teclado
  while(comprobarMovimientoHumano(TECLA)){ 
      Serial.println("Posicion Repetida");
      TECLA = teclado.getKey();
  }
  Serial.print(TECLA);
  if(jugador){
    switch(TECLA){
      case '1':
        triqui[0][0] = 1;
        digitalWrite(22, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '2':
        triqui[0][1] = 1;
        digitalWrite(23, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '3':
        triqui[0][2] = 1;
        digitalWrite(24, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '4':
        triqui[1][0] = 1;
        digitalWrite(25, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '5':
        triqui[1][1] = 1;
        digitalWrite(26, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '6':
        triqui[1][2] = 1;
        digitalWrite(27, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '7':
        triqui[2][0] = 1;
        digitalWrite(28, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '8':
        triqui[2][1] = 1;
        digitalWrite(29, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '9':
        triqui[2][2] = 1;
        digitalWrite(30, HIGH);
        jugador = false;
        jugadas += 1;
        break;
      case '0':
        for(int i=0; i<3; i++){
          Serial.print("\n");
          for(int j=0; j<3; j++){
            Serial.print(triqui[i][j]);
          }
        }
        delay(2000); 
        break;
    }
    hayGanador(jugador);
  }
  else{
    jugador = true;
    Serial.println("TURNO MAQUINA");
    int numRandom = random(1,9);
    boolean ejecutar = comprobarMovimiento(numRandom);
    while(ejecutar){ 
      numRandom = random(1,9);
      ejecutar = comprobarMovimiento(numRandom);
    }
    Serial.println(numRandom);
    switch(numRandom){
      case 1:
        triqui[0][0] = 2;
        digitalWrite(31, HIGH);
        jugadas += 1;
        break;
      case 2:
        triqui[0][1] = 2;
        digitalWrite(32, HIGH);
        jugadas += 1;
        break;
      case 3:
        triqui[0][2] = 2;
        digitalWrite(33, HIGH);
        jugadas += 1;
        break;
      case 4:
        triqui[1][0] = 2;
        digitalWrite(34, HIGH);
        jugadas += 1;
        break;
      case 5:
        triqui[1][1] = 2;
        digitalWrite(35, HIGH);
        jugadas += 1;
        break;
      case 6:
        triqui[1][2] = 2;
        digitalWrite(36, HIGH);
        jugadas += 1;
        break;
      case 7:
        triqui[2][0] = 2;
        digitalWrite(37, HIGH);
        jugadas += 1;
        break;
      case 8:
        triqui[2][1] = 2;
        digitalWrite(38, HIGH);
        jugadas += 1;
        break;
      case 9:
        triqui[2][2] = 2;
        digitalWrite(39, HIGH);
        jugadas += 1;
        break;
    }
    hayGanador(jugador);
  }

  if(jugadas>=9){
    Serial.println("Se ha terminado el juego y nadie ha ganado, gracias por jugar");
    delay(1000);
    for(int i=0; i<3; i++){
          Serial.print("\n");
          for(int j=0; j<3; j++){
            Serial.print(triqui[i][j]);
          }
        }
   delay(2000); 
   exit(0);
  }
  
}
