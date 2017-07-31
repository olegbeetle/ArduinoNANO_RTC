#include <iarduino_RTC.h>

iarduino_RTC time(RTC_DS3231);

void set_indication(int hour,int minute);

char incomingByte = 0;   // for incoming serial data

int reset_pin = 2;
int set0_pin = 3;
int set1_pin = 4;
int set2_pin = 5;
int set3_pin = 6;


int reg=0;
int cnt=0;
char timer[2];
int tmm[3]={0};

void setup() {
    delay(300);
    Serial.begin(9600);
    time.begin();
    pinMode(set0_pin, OUTPUT); // установка 2-го контакта в режим вывода
    pinMode(set1_pin, OUTPUT); // установка 2-го контакта в режим вывода
    pinMode(set2_pin, OUTPUT); // установка 2-го контакта в режим вывода
    pinMode(set3_pin, OUTPUT); // установка 2-го контакта в режим вывода
    pinMode(reset_pin, OUTPUT); // установка 2-го контакта в режим вывода    
}




void loop()
{
    if(millis()%1000==0){ // если прошла 1 секунда
      Serial.println(time.gettime("d-m-Y, H:i:s, D")); // выводим время 
      //delay(1); // приостанавливаем на 1 мс, чтоб не выводить время несколько раз за 1мс

      int minute = atoi(time.gettime("i"));  
      int hour   = atoi(time.gettime("H")); 
      set_indication(hour,minute);
    }

   
    
    if (Serial.available() > 0) 
    {
        // read the incoming byte:
        incomingByte = Serial.read();
        timer[reg] = incomingByte;
        reg=reg+1;
       
        char test[2] = {'0','\0'};
        test[0] = incomingByte;
             
        set_indication(0,atoi(test));

      //это блок для склейки и записи времени через ком-порт   
        if(reg == 2)
        {
         reg = 0;
         tmm[cnt] = atoi(timer);
         cnt++;
//         Serial.println( tmm[cnt-1],DEC);
        }
        if(cnt == 3)
        {
//          time.settime(tmm[2],tmm[1],tmm[0],23,12,16,5); 
          cnt=0;   
        }
    }

    
}


void set_indication(int hour,int minute)
{  
   digitalWrite(reset_pin, HIGH); // вывод №2 в активное состояние
   digitalWrite(reset_pin, LOW); // вывод №2 в пассивное состояние
   
   for(int i=0;i< minute%10;i++)
   { 
     digitalWrite(set0_pin, HIGH); // вывод №3 в активное состояние
     digitalWrite(set0_pin, LOW); // вывод №3 в пассивное состояние
   }
    for(int i=0;i< minute/10;i++)
   { 
     digitalWrite(set1_pin, HIGH); // вывод №3 в активное состояние
     digitalWrite(set1_pin, LOW); // вывод №3 в пассивное состояние
   }
    for(int i=0;i< hour%10;i++)
   { 
     digitalWrite(set2_pin, HIGH); // вывод №3 в активное состояние
     digitalWrite(set2_pin, LOW); // вывод №3 в пассивное состояние
   }
    for(int i=0;i< hour/10;i++)
   { 
     digitalWrite(set3_pin, HIGH); // вывод №3 в активное состояние
     digitalWrite(set3_pin, LOW); // вывод №3 в пассивное состояние
   }
}
