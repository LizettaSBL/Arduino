#include <Servo.h>
Servo servo;     //  назначается вывод сервы
int echoPin = 11;
int trigPin = 12;
int diodPin=13;
int servoPin=9;

void setup() {
 servo.attach(servoPin);  // Указываем объекту класса Servo, что серво присоединен к пину 9
  // Инициализируем взаимодействие по последовательному порту
 Serial.begin (9600);
 //Определяем вводы и выводы
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(diodPin, OUTPUT);
}

void loop() {
  // Сначала генерируем короткий импульс длительностью 2 микросекунд.
 int duration, cm;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 // Выставив высокий уровень сигнала, ждем около 10 микросекунд. 
 //В этот момент датчик будет посылать сигналы с частотой 40 КГц.
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 //  Время задержки акустического сигнала на эхолокаторе.
 duration = pulseIn(echoPin, HIGH);
 cm = duration / 58; //переводим время задержки в расстоятие в см
 //проверка дальности объекта. При выполнении условия (расстояние меньше 30 см) 
 //запускает поворот сервопривода и включение светодиода
 if(cm<20)
 {
   servo.write(90); //поворот сервопривода на 90 градусов
   digitalWrite(diodPin,HIGH); //подача на пин выского уровня сигнала
 }
 else {
   servo.write(0); //поворот сервопривода в начальное положение
   digitalWrite(diodPin,LOW); //подача на пин низкого уровня сигнала
 }
 
   Serial.println(cm); //вывод расстояния
   delay(1000); //задержка в 1 сек между генерациями волн
}
