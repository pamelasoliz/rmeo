#include <ros.h>
#include <std_msgs/String.h>
/**********************************************/
/*Definicion de pines de sensores ultra sonido*/
/**********************************************/
/*sensor izquierdo*/
#define trigI 13
#define echoI 12
/*sensor central */
#define trigC 10
#define echoC 11
/*sensor derecho*/ 
#define trigD 9
#define echoD 8
/**********************************************/

/**********************************************/
/***       pines de control de MOTORES      ***/
/**********************************************/
/*Motor Derecho*/
#define vel_D 7
#define ade_D 6
#define atr_D 5  
/*Motor Izquierdo*/
#define vel_I 2
#define ade_I 3
#define atr_I 4 
/**********************************************/

/**********************************************/
/*              Controlador PID               */
/**********************************************/
double Sp;  //stpoin o punto de referencia
double eT=0;  //ERROR actual
double kp = 0.9504;  //Constante Proporcional
double kd = 0;  // Constante Derivativa
double ki = 15.59;  // Constante Integral
double TI_1 = 0;
double yT;  // Salida
double eT0=0; // ERROR anterior
double uT;  // Señal de control
double T = 0.06; // Tiempo de muestreo

double tnR = 0;
double TR = 0;
double t0R = 0;
double eTR = 0;
double eT0R = 0;
double TI_1R = 0;
int pwmR = 100;
double uTR=0;

double tnL = 0;
double TL = 0;
double t0L = 0;
double eTL = 0;
double eT0L = 0;
double TI_1L = 0;
int pwmL = 100;
double uTL=0;
/**********************************************/
int distI_1;
int distC_1;
int distD_1;
/*********************************************/
ros::NodeHandle  nh;

std_msgs::String str_msg;

ros::Publisher chatter("chatter", &str_msg);

void callback ( const std_msgs::String& msg){

  str_msg.data = msg.data;
  chatter.publish( &str_msg );
}

ros::Subscriber<std_msgs::String> sub("talker", callback);

void setup() {
//Interrupciones para el encoder

//Encoder Derecho
attachInterrupt(digitalPinToInterrupt(19),PIDright,RISING);

//Encoder Izquierdo
attachInterrupt(digitalPinToInterrupt(18),PIDleft,RISING);

pinMode(trigI,OUTPUT);
pinMode(trigC,OUTPUT);
pinMode(trigD,OUTPUT);
pinMode(echoI,INPUT);
pinMode(echoC,INPUT);
pinMode(echoD,INPUT);
pinMode(vel_D,OUTPUT);
pinMode(ade_D,OUTPUT);
pinMode(atr_D,OUTPUT);
pinMode(vel_I,OUTPUT);
pinMode(ade_I,OUTPUT);
pinMode(atr_I,OUTPUT);
pinMode(1,OUTPUT);
  Serial.begin(9600);



/***********************************/

  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);

/***********************************/

}

void loop() {
{
 
  nh.spinOnce();
  delay(3);
}
   
  
 int distI = objeto(trigI,echoI);
 int distC = objeto(trigC,echoC);
 int distD = objeto(trigD,echoD);

 
  //Serial.println(distI);
  //Serial.println(distC);
  //Serial.println(distD);
  
if(distI < 20 || distC < 20 || distD < 20)
{
  evasion();
  }
else
{
  adelante();
  }
//delay(100);

//distI_1 = distI;  
}

int PIDright()
{
  noInterrupts();
  tnR = millis();
  TR = tnR-t0R;
  double  frecR = 1000/TR;
  double TDR = (kd/T)*(eTR-eT0R);
  double TIR = ki*T*eTR - (TIR-TI_1R); 
  uTR = kp + TIR + TDR;
  int pwmR = map(uTR,-500,500,95,100);
  delay(T);
  TI_1R = TIR;
  eT0R = eTR;
  interrupts();
  }
  
 int PIDleft()
 {
  noInterrupts();
  tnL = millis();
  TL = tnL-t0L;
  double frecL = 1000/TL;
  double TDL = (kd/T)*(eTL-eT0L);
  double TIL = ki*T*eTL - (TIL-TI_1L); 
  uTL = kp + TIL + TDL;
  int pwmL = map(uTL,-500,500,95,100);
  delay(T);
  TI_1L = TIL;
  eT0L = eTL;
  interrupts();
  }

int objeto(int TRIG, int ECHO)
{
  long duracion;
  long distancia;
  digitalWrite(TRIG,LOW);
  delayMicroseconds(4);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  duracion = pulseIn(ECHO,HIGH);
  duracion = duracion/2;
  distancia = duracion/29;
  return distancia;
  delay(50);
  }
void adelante()
{
  analogWrite(vel_D,pwmR);
  digitalWrite(ade_D,1);
  digitalWrite(atr_D,0);

  analogWrite(vel_I,pwmL);
  digitalWrite(ade_I,1);
  digitalWrite(atr_I,0);  
  
  }

void evasion ()
{
  analogWrite(vel_D,pwmR);
  digitalWrite(ade_D,1);
  digitalWrite(atr_D,0);

  analogWrite(vel_I,pwmL);
  digitalWrite(ade_I,0);
  digitalWrite(atr_I,1);  
  delay(200);
  }


/******************************************/
  //{
  //nh.spinOnce();
  //delay(3);

   //}
/*****************************************/
