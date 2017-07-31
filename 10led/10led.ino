
//      2          a
//    -----      -----        --7--      -----    
//   |7    |6   |f    |b     |2    |6   |     |   
//   |     |    |     |      |     |    |     |
//    --5--      ---g--       ---1-      ----- 
//   |3    |0   |e    |c     |     |    |     | 
//   |     |    |     |      |3    |5   |     |  
//    -----  1   -----  h     --4--  8   -----  0 
//      4          d

// col   3         2           1         0


#define DIG_CNT 9

int Kpin_mass[] = {19,3,4,5,6,7,8,9};//segment 
int Apin_mass[] = {10,11,12,13,14,15,16,17,18};//razryad
unsigned long int nummmm =0;
unsigned long int last_mls=0;
volatile int state = 1;
// Install the interrupt routine.
volatile unsigned long millis_prev=0; 
void INTERR()
{ 
 if(millis()-100 > millis_prev)
 {
  if(state<2)
     state++;
   else
     state=0;
  millis_prev = millis();
 }

}

void setup() 
{
  // put your setup code here, to run once:
  for(int i=0;i<8;i++)
  {
    pinMode(Kpin_mass[i], OUTPUT);
    digitalWrite(Kpin_mass[i], 0);
  }
  for(int i=0;i<DIG_CNT;i++)
  {
    pinMode(Apin_mass[i], OUTPUT);
    digitalWrite(Apin_mass[i], 1);
  }
  Serial.begin(115200);

  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  delay(100);
// привязываем 0-е прерывание к функции INTERR().
  attachInterrupt(0, INTERR, RISING );  

}

void print_num(char* num, int  digit, byte dot)
{
  
  if(digit == 0)
   digitalWrite(Apin_mass[DIG_CNT-1], 1); 
  else
   digitalWrite(Apin_mass[digit-1], 1);
  
  for(int i=0;i<8;i++)
  {
    digitalWrite(Kpin_mass[i], 0);
  }

//  for(int i=0;i<(DIG_CNT-1-digit);i++)
//    num = num/10;
//    
//  num = num%10;
  
  
  switch(num[digit])
  {
    case 0:
      digitalWrite(Kpin_mass[0], 1);
      digitalWrite(Kpin_mass[2], 1);
      digitalWrite(Kpin_mass[3], 1);
      digitalWrite(Kpin_mass[4], 1);
      digitalWrite(Kpin_mass[6], 1);
      digitalWrite(Kpin_mass[7], 1);
      break;
    case 1:
      digitalWrite(Kpin_mass[0], 1);
      digitalWrite(Kpin_mass[6], 1);
      break;
    case 2:
      digitalWrite(Kpin_mass[2], 1);
      digitalWrite(Kpin_mass[6], 1);
      digitalWrite(Kpin_mass[5], 1);
      digitalWrite(Kpin_mass[3], 1);
      digitalWrite(Kpin_mass[4], 1);
      break;
    case 3:
      digitalWrite(Kpin_mass[2], 1);
      digitalWrite(Kpin_mass[6], 1);
      digitalWrite(Kpin_mass[5], 1);
      digitalWrite(Kpin_mass[0], 1);
      digitalWrite(Kpin_mass[4], 1);
      break;
    case 4:
      digitalWrite(Kpin_mass[7], 1);
      digitalWrite(Kpin_mass[5], 1);
      digitalWrite(Kpin_mass[6], 1);
      digitalWrite(Kpin_mass[0], 1);
      break;
    case 5:
      digitalWrite(Kpin_mass[2], 1);
      digitalWrite(Kpin_mass[7], 1);
      digitalWrite(Kpin_mass[5], 1);
      digitalWrite(Kpin_mass[0], 1);
      digitalWrite(Kpin_mass[4], 1);
      break;
    case 6:
      digitalWrite(Kpin_mass[2], 1);
      digitalWrite(Kpin_mass[7], 1);
      digitalWrite(Kpin_mass[5], 1);
      digitalWrite(Kpin_mass[0], 1);
      digitalWrite(Kpin_mass[4], 1);
      digitalWrite(Kpin_mass[3], 1);
      break;
    case 7:
      digitalWrite(Kpin_mass[0], 1);
      digitalWrite(Kpin_mass[6], 1);
      digitalWrite(Kpin_mass[2], 1);
      break;
    case 8:
      digitalWrite(Kpin_mass[2], 1);
      digitalWrite(Kpin_mass[7], 1);
      digitalWrite(Kpin_mass[5], 1);
      digitalWrite(Kpin_mass[0], 1);
      digitalWrite(Kpin_mass[4], 1);
      digitalWrite(Kpin_mass[3], 1);
      digitalWrite(Kpin_mass[6], 1);
      break;
    case 9:
      digitalWrite(Kpin_mass[2], 1);
      digitalWrite(Kpin_mass[7], 1);
      digitalWrite(Kpin_mass[5], 1);
      digitalWrite(Kpin_mass[0], 1);
      digitalWrite(Kpin_mass[4], 1);
      digitalWrite(Kpin_mass[6], 1);
      break;
  }

  if(dot == (DIG_CNT-1-digit))
    digitalWrite(Kpin_mass[1], 1);
  else
    digitalWrite(Kpin_mass[1], 0);

  digitalWrite(Apin_mass[digit], 0);
}

void loop() {
  // put your main code here, to run repeatedly:
 static unsigned long int dig =0;
 unsigned long int tmr = millis();
 static long int numb = 0;
 
 dig++;
 int digit = dig%DIG_CNT;

 //digit = 7 - digit;
 static char dot = 0;
 static unsigned long int lasttmr = 0; 
 
 if((!(tmr%1))&&(tmr!=lasttmr))
 {  
  nummmm++;
  lasttmr = tmr;
//  if(!(nummmm%100))
//  {
//    dot++;
//    if(dot>8)
//      dot = 0;
//    
//  }
 }
  
  
  if(state==0)
    numb = millis() - last_mls;
  else if(state == 2)
  {
    last_mls = millis();
    numb = 0;
    //state = 0;
  }
  //else if(state == 1)
//   Serial.println(numb);   
  long int tmpnum = numb;
  char num[9]={0};
  num[8] = (numb%10); 
  numb /= 10;
  num[7] = (numb%10);
  numb /= 10;
  num[6] = (numb%10);
  numb /= 10;
  int sec = numb%60;
  numb /= 60;
  num[5] = (sec%10);
  sec /=10;
  num[4] = (sec%10);
  int minut = numb%60;
  numb /= 60;
  num[3] = (minut%10);
  minut /=10;
  num[2] = (minut%10);
  int hour = numb%60;
  numb /= 60;
  num[1] = (hour%10);
  hour /=10;
  num[0] = (hour%10);
  numb = tmpnum;
  //Serial.println(num);
  switch(digit)
  {
    case 5:
      dot = 3;
      break;
    case 3: 
      dot = 5;
      break;
    case 1:
      dot = 7;
      break;
    default:
      dot = 3;
      break;
  }
  print_num(num,digit,dot);
  //delay(1000);
}
