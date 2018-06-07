//Asignación de pines y declaración de variables 

int sensorPin = A0;//Pin para lectura analógica 
int Pin2 = 6;//Pin para PWM 1 
int Pin1 = 7;//Pin para PWM 2 
int Pin4 = 8;//Pin para PWM 4
int Pin3 = 9;//Pin para PWM 3

float e=0;//error 
float e0=0;//error pasad0 
float pd=0;//variable de control 
float d=0;//Diferencia entre error y error pasado 
float val=0;//Valor analógico leído 

void setup() {
  //Inicializamos la comunicación serial
  Serial.begin(9600);
  
  //Escribimos por el monitor serie mensaje de inicio
  Serial.println("Valores del potenciometro");
  // declare the ledPin as an OUTPUT: 
  pinMode(Pin1,OUTPUT);//PIN1 salida PWM 
  pinMode(Pin2,OUTPUT);//PIN2 salida PWM
  pinMode(Pin3,OUTPUT);//PIN3 salida PWM 
  pinMode(Pin4,OUTPUT);//PIN4 salida PWM
}

void loop() {
 
  //Imprimimos por el monitor serie
  Serial.print("El valor es = ");
  Serial.println(val);
  delay(1000);
  val =analogRead(sensorPin);//lee entrada del sensor 
  e=val-515;//error= valor leído menos referencia 
  d=e-e0;//diferenciación discreta 
  e0=e;//error pasado //control 
  pd= (43*e) + (25*d);// constantes multiplicando a e y a d
  pd =constrain(pd, -255, 255);//Limitar pd

  //Condiciones de posición 
  if(pd>0){
    analogWrite(Pin1, pd);//activar pin1
    analogWrite(Pin2, 0);//desactivar pin
    analogWrite(Pin4, pd);//activar pin1
    analogWrite(Pin3, 0);//desactivar pin2
  }
  if(pd<0){
    analogWrite(Pin2,abs(pd));//activar pin2
    analogWrite(Pin1, 0);//Descativar pin1
    analogWrite(Pin3,abs(pd));//activar pin2
    analogWrite(Pin4, 0);//Descativar pin1
  }
}
