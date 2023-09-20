
/*********************************************  SETTINGS ************************************************/
//botones jugadores
const int PUSH_init = PA_7;
const int PUSHB1 = PF_4; 
const int PUSHB2 = PF_0;

//estado botones (HIGH/LOW)
int inicio = 0;    
int control_P1 = 0;
int control_P2 = 0;

//puntaje cada jugador
int scoreP1 = 0;
int scoreP2 = 0;

//puertos de salida
int PORT1[8] = {PD_0,PD_1,PD_2,PD_3,PE_1,PE_2,PE_3,PA_6};
int PORT2[8] = {PB_3,PC_4,PC_5,PC_6,PC_7,PD_6,PD_7,PA_3};

//colores semaforo
const int color1 =  PF_1; //RED_LED     
const int color2 =  PF_3; //GREEN_LED
const int color3 = PF_2; //BLUE_LED

//banderas
bool coin = false;
int anti1=0;
int anti2=0;

/*********************************************  SETUP ************************************************/

void setup() 
{
  //OUTPUTS
  pinMode(color1, OUTPUT);
  pinMode(color2, OUTPUT); 
  pinMode(color3, OUTPUT); 
  
  for(int i=0; i<8; i++)
  {
  pinMode(PORT1[i], OUTPUT);
  pinMode(PORT2[i], OUTPUT);
  }
            
  //INPUTS
  pinMode(PUSHB1, INPUT_PULLUP); 
  pinMode(PUSHB2, INPUT_PULLUP);
  pinMode(PUSH_init, INPUT_PULLUP);     
}



/*********************************************  LOOP ************************************************/

void loop()
{
    inicio = digitalRead(PUSH_init); //lee el estado del pin

      
    if(inicio == LOW) //comenzando partida
    {   
      start();
    }

    if(coin == true) //juego
    {      
           /*~~~~~~~~~~~~ PLAYER1 ~~~~~~~~~~~~~*/
           control_P1 = digitalRead(PUSHB1); 

           if (control_P1 == LOW) 
           { 
            anti1=1;
           }
           if(control_P1 == HIGH && anti1 == 1)
           {
             anti1=0;
             scoreP1++;
             marcador1();
  
              if(scoreP1 == 8)
              {
                ganador(1);
              }
           }
           /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
           
           /*~~~~~~~~~~~~ PLAYER2 ~~~~~~~~~~~~~*/
           control_P2 = digitalRead(PUSHB2); 
               
           if (control_P2 == LOW) 
           { 
             anti2=1;
           }
           if(control_P2 == HIGH && anti2 == 1)
           {
             anti2=0;
             scoreP2++;
             marcador2();
             
               if(scoreP2 == 8)
                {
                  ganador(2);
                }
           }
           /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    }
          
}


/*********************************************  FUNCIONES ************************************************/
void start(void)
{
  restart(); //funcion reinicio puntaje 
  coin = true;

  digitalWrite(color1, HIGH);  //RED ON
  delay(1000);
  digitalWrite(color2, HIGH); //RED + GREEN ON
  delay(1000);
  digitalWrite(color1, LOW);  //GREEN ON
  delay(1000);
  digitalWrite(color2, LOW);  //LED OFF
  return;
}

void restart(void)
{ coin = false;
  scoreP1 = 0;
  scoreP2 = 0;
  for(int i=0; i<8; i++)
  { 
    digitalWrite(PORT2[i], LOW);
    digitalWrite(PORT1[i], LOW);
  }

  return;
}

void marcador1(void)
{
  //PORT1[8] = {PD_0,PD_1,PD_2,PD_3,PE_1,PE_2,PE_3,PA_6};

/* binario
byte b0 = (scoreP1)%2;
byte b1 = (scoreP1/2)%2;
byte b2 = (scoreP1/4)%2;
byte b3 = (scoreP1/8)%2;
byte b4 = (scoreP1/16)%2;
byte b5 = (scoreP1/32)%2;
byte b6 = (scoreP1/64)%2;
byte b7 = (scoreP1/128)%2;

digitalWrite(PD_0, b0);
digitalWrite(PD_1, b1);
digitalWrite(PD_2, b2);
digitalWrite(PD_3, b3);
digitalWrite(PE_1, b4);
digitalWrite(PE_2, b5);
digitalWrite(PE_3, b6);
digitalWrite(PA_6, b7);
*/

int LEDP1 = (scoreP1-1) %8;
digitalWrite(PORT1[LEDP1],HIGH); 

  return;
}

void marcador2(void)
{
  //PORT2[8] = {PB_3,PC_4,PC_5,PC_6,PC_7,PD_6,PD_7,PA_3};
  
  int LEDP2 = (scoreP2-1) %8;
  digitalWrite(PORT2[LEDP2],HIGH); 
  return;
}

void ganador(int jugador)
{ 
    if(jugador == 1)
    { 
      for(int j = 0; j<4 ; j++)
      {
        digitalWrite(color3, HIGH);  //Blue ON
        delay(1000);
        digitalWrite(color3, LOW);  //Blue OFF
        delay(1000);
      }
    }
    
    if(jugador == 2)
    {
          for(int j = 0; j<4 ; j++)
      {
        digitalWrite(color1, HIGH);  //RED ON
        delay(1000);
        digitalWrite(color1, LOW);  //RED OFF
        delay(1000);
      }
    }

    restart();
    return;
}
