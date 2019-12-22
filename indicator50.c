#include "iostm8s103f3.h"
#include "main.h"
int dellight=20 ;
extern char button;
extern char y[10] ; //10 columns
extern int AMP;
extern int AMP_del;
extern int T1;
extern int T2;
extern char step_AMP;
extern int day_AMP[10];
extern int sys_del;
extern char state_indicator; 
extern char deca_minutes;
extern char alarm_flag;
//dalay & internal functions
void delay(int j) 
{
 for (int i=1; i<j;i++)  
  {asm("nop");}
 
 buttons(); //chek buttons - set variable "button"
 pushed_button(); // execute functions depend on variable "button" set 
 event_AMP();
 extern char trig_AMP;
 if(step_AMP==0) 
 {
   AMP=current_AMP();
   if(trig_AMP==1) 
       {T1=TIM2_CNTRH<<2; T1|=TIM2_CNTRL>>6;}  
   else T2=(deca_minutes*10)+(TIM2_CNTRH/14);
 } 
 if((trig_AMP==1)&&(AMP_del!=10001)) 
 {
    AMP_del++; 
    if(AMP_del==10000) 
    {
       for(char i=1;i<10;i++) day_AMP[10-i]=day_AMP[9-i];
       day_AMP[0]=AMP;
       AMP_del=10001;
    }
 } 
 if(trig_AMP==0) 
       AMP_del=0;
 indicate_state();
 if((state_indicator%50==0)) 
 {
   sys_del++; 
   if(sys_del==7000) 
   { 
      state_indicator++;
      sys_del=0;
   }
 }
 step_AMP++;
 if((beep_flag)&&((TIM2_CNTRL&96)==0)) 
   PB_DDR|=32; 
 else 
   PB_DDR&=~32;
 
}

void indicator (char s[10])
{ 
  PD_ODR|=d_mask;  // be cearful!!! (D2..D6=> bit_odr=1)
  PC_ODR|=c_mask;  // be cearful!!! (C3..C6=> bit_odr=1)
  
  PD_CR1&=~d_mask; // be cearful!!! (open drain)
  PC_CR1&=~c_mask; // be cearful!!! (open drain)
 
  PD_DDR|=d_mask;  // be cearful!!! (D2..D6=> out) value=0
  PC_DDR|=c_mask;  // be cearful!!! (C3..C6=> out) value=0
 

  // column_2 :
 
  PD_ODR&=~d1; //"-"

  PC_CR1|=s[1]&c34;
  delay(dellight);
  PC_CR1&=~c34; 
  PC_CR1|=s[1]&c56;
  delay(dellight);
  PC_CR1&=~c56;
  PC_CR1|=s[1]&c7;
  delay(dellight);
  PC_CR1&=~c7;
  
  PD_ODR|=d1;
  
 // column_1 :
 
  PD_CR1|=d1;//"+"
 
  PC_ODR&=~s[0]|~c34;
  delay(dellight);
  PC_ODR|=c34;
  PC_ODR&=~s[0]|~c56;
  delay(dellight);
  PC_ODR|=c56;
  PC_ODR&=~s[0]|~c7;
  delay(dellight);
  PC_ODR|=c7;
  
  PD_CR1&=~d1;
 
  // column_4 :
 
  PD_ODR&=~d2; //"-"

  PC_CR1|=s[3]&c34;
  delay(dellight);
  PC_CR1&=~c34; 
  PC_CR1|=s[3]&c56;
  delay(dellight);
  PC_CR1&=~c56;
  PC_CR1|=s[3]&c7;
  delay(dellight);
  PC_CR1&=~c7;
  
  PD_ODR|=d2;
  
 // column_3 :
 
  PD_CR1|=d2;//"+"
 
  PC_ODR&=~s[2]|~c34;
  delay(dellight);
  PC_ODR|=c34;
  PC_ODR&=~s[2]|~c56;
  delay(dellight);
  PC_ODR|=c56;
  PC_ODR&=~s[2]|~c7;
  delay(dellight);
  PC_ODR|=c7;
  
  PD_CR1&=~d2;
  
    // column_6 :
 
  PD_ODR&=~d4; //"-"

  PC_CR1|=s[5]&c34;
  delay(dellight);
  PC_CR1&=~c34; 
  PC_CR1|=s[5]&c56;
  delay(dellight);
  PC_CR1&=~c56;
  PC_CR1|=s[5]&c7;
  delay(dellight);
  PC_CR1&=~c7;
  
  PD_ODR|=d4;
  
 // column_5 :
 
  PD_CR1|=d4;//"+"
 
  PC_ODR&=~s[4]|~c34;
  delay(dellight);
  PC_ODR|=c34;
  PC_ODR&=~s[4]|~c56;
  delay(dellight);
  PC_ODR|=c56;
  PC_ODR&=~s[4]|~c7;
  delay(dellight);
  PC_ODR|=c7;
  
  PD_CR1&=~d4;
  
    // column_8 :
 
  PD_ODR&=~d5; //"-"

  PC_CR1|=s[7]&c34;
  delay(dellight);
  PC_CR1&=~c34; 
  PC_CR1|=s[7]&c56;
  delay(dellight);
  PC_CR1&=~c56;
  PC_CR1|=s[7]&c7;
  delay(dellight);
  PC_CR1&=~c7;
  
  PD_ODR|=d5;
  
 // column_7 :
 
  PD_CR1|=d5;//"+"
 
  PC_ODR&=~s[6]|~c34;
  delay(dellight);
  PC_ODR|=c34;
  PC_ODR&=~s[6]|~c56;
  delay(dellight);
  PC_ODR|=c56;
  PC_ODR&=~s[6]|~c7;
  delay(dellight);
  PC_ODR|=c7;
  
  PD_CR1&=~d5;
   
  // column_10 :
 
  PD_ODR&=~d6; //"-"

  PC_CR1|=s[9]&c34;
  delay(dellight);
  PC_CR1&=~c34; 
  PC_CR1|=s[9]&c56;
  delay(dellight);
  PC_CR1&=~c56;
  PC_CR1|=s[9]&c7;
  delay(dellight);
  PC_CR1&=~c7;
  
  PD_ODR|=d6;
  
 // column_9 :
 
  PD_CR1|=d6;//"+"
 
  PC_ODR&=~s[8]|~c34;
  delay(dellight);
  PC_ODR|=c34;
  PC_ODR&=~s[8]|~c56;
  delay(dellight);
  PC_ODR|=c56;
  PC_ODR&=~s[8]|~c7;
  delay(dellight);
  PC_ODR|=c7;
  
  PD_CR1&=~d6;
}

void dig (char a, char pozition) // a - gigit for print;  pozition - 1 .. 3
{  
  switch (pozition)
  {
case 1: {pozition=0; break;} 
case 2: {pozition=4; break;}
case 3: {pozition=7; break;}
  }
  switch (a)
  {
case 0: {y[pozition]=248;y[pozition+1]=136;y[pozition+2]=248; break;}
case 1: {y[pozition]=0;  y[pozition+1]=0;  y[pozition+2]=248; break;}
case 2: {y[pozition]=184;y[pozition+1]=168;y[pozition+2]=232; break;}
case 3: {y[pozition]=168;y[pozition+1]=168;y[pozition+2]=248; break;}
case 4: {y[pozition]=224;y[pozition+1]=32; y[pozition+2]=248; break;}
case 5: {y[pozition]=232;y[pozition+1]=168;y[pozition+2]=184; break;} 
case 6: {y[pozition]=248;y[pozition+1]=168;y[pozition+2]=184; break;}
case 7: {y[pozition]=128;y[pozition+1]=128;y[pozition+2]=248; break;}
case 8: {y[pozition]=248;y[pozition+1]=168;y[pozition+2]=248; break;}
case 9: {y[pozition]=232;y[pozition+1]=168;y[pozition+2]=248; break;}
 }
} 


void numb (int n,char point)
{
 dig((n%1000)/100,1);  
 dig((n%100)/10,2);
 dig(n%10,3);
 switch (point)
 {
 case 0: {y[3]=0; break;}
 case 1: {y[3]=8; break;}
 case 2: {y[3]=80;break;}
 } 
}


void print (char a, char pozition)
{  
  y[3]=0;
  switch (pozition)
  {
case 1: {pozition=0; break;} 
case 2: {pozition=4; break;}
case 3: {pozition=7; break;}
  }  
  switch (a)
  {
case 'T': {y[pozition]=128;y[pozition+1]=248;y[pozition+2]=128; break;}
case 'K': {y[pozition]=248;y[pozition+1]=80; y[pozition+2]=136; break;}
case 'P': {y[pozition]=248;y[pozition+1]=160;y[pozition+2]=224; break;}
case 'A': {y[pozition]=120; y[pozition+1]=160;y[pozition+2]=120; break;}
case 'E': {y[pozition]=248;y[pozition+1]=168;y[pozition+2]=168; break;} 
case 'G': {y[pozition]=248;y[pozition+1]=128;y[pozition+2]=248; break;} //cyr-'pe'
case '<': {y[pozition]=120;y[pozition+1]=168;y[pozition+2]=184; break;} //cyr-'be'
case ' ': {y[pozition]=0;y[pozition+1]=0;y[pozition+2]=0; break;}
case 'L': {y[pozition]=248;y[pozition+1]=64;y[pozition+2]=56; break;}   //cyr-'el'
  }
} 
