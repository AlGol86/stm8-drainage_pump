#include "iostm8s103f3.h"
#include "main.h"

extern int AMPcounter;
extern int AMP;//Amper
extern int T1;
extern int T2;
extern int day_T1[10];
extern int day_T2[10];
extern int day_AMP[10];
extern int count_turn_on;
extern int month_T1[30];
extern int month_T2[30];
extern int month_AMP[30];
extern int count_t_o[30];
extern char trig_AMP;
extern char deca_minutes;
extern char alarm_flag;

int get_ADC(void)
{
PD_DDR&=~8;
PD_CR1&=~8;
  //ADC_CR2_ALIGN=1;
ADC_CR1_CONT=0;
ADC_CSR_CH=4;
ADC_CR1_ADON=1;
ADC_CR1_ADON=1;
while(ADC_CSR_EOC==0)
  {asm("nop");}
ADC_CSR_EOC=0;
return ((ADC_DRH<<2)+ADC_DRL); 
}

int ADC_compensation(int value_ADC)
{
 if (value_ADC!=0) 
 {
 value_ADC+=20;
 value_ADC*=17;
 value_ADC/=25;
 }
 return (value_ADC);
}

int current_AMP(void)
{return (ADC_compensation(get_ADC()));}

void event_AMP(void)
{if((AMP>50)&&(AMPcounter<2500)) AMPcounter++; 
else if(AMPcounter>0) AMPcounter--;
if((AMPcounter>2000)&&(trig_AMP==0))  
{
  trig_AMP=1;         //(trig_AMP==1)-count T1
  for(char i=1;i<10;i++) day_T2[10-i]=day_T2[10-i-1]; 
  day_T2[0]=T2; 
  count_turn_on++;
  init_tim2();
}
if((AMPcounter<10)&&(trig_AMP==1))    
{
  trig_AMP=0;          //(trig_AMP==0)-count T2
  for(char i=1;i<10;i++) day_T1[10-i]=day_T1[10-i-1]; 
  day_T1[0]=T1; 
  init_tim2();
}
if((AMPcounter>2000)&&(AMP>200)) 
{
  PB_DDR|=16;
  alarm_flag=1;
}
if((AMPcounter>2000)&&(trig_AMP==1)&&(T1>300)&&(T1<350)) 
{
  PB_DDR|=16;
  alarm_flag=1;
}
}


