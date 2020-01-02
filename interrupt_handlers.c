#include "iostm8s103f3.h"
#include "main.h"

extern char timer_flags;
extern char deca_minutes;  //0-10-2550 minutes
extern int AMP;//Amper
extern char state_indicator; //0-ampers 100-t1(time in load) 200-t2(interval on-on) 
//////////////////////////1-30 ampers for 30 days 
//////////////////////////100-130 time in load for 30 days
//////////////////////////200-230 interval on-on in load for 30 days
extern int day_T1[10];
extern int day_T2[10];
extern int day_AMP[10];
extern int count_turn_on;
extern int month_T1[30];
extern int month_T2[30];
extern int month_AMP[30];
extern int count_t_o[30];

char j;

__interrupt void time1(void)
{
 TIM1_SR1_UIF=0; //flag "0"
 PB_DDR|=32;    // beep
  for(int i=1;i<30000;i++){}  for(int i=1;i<30000;i++){}  for(int i=1;i<30000;i++){}
 PB_DDR&=~32;
 
for(char i=1;i<30;i++)  month_T1[30-i] = month_T1[30-i-1];
for(char i=1;i<30;i++)  month_T2[30-i] = month_T2[30-i-1];   
for(char i=1;i<30;i++)  month_AMP[30-i]= month_AMP[30-i-1];
for(char i=1;i<30;i++)  count_t_o[30-i]= count_t_o[30-i-1];
 
month_T1[0]=0; 
 j=0;
 while ((day_T1[j]!=0)&&(j<10))  {month_T1[0]+=day_T1[j];j++;}
 month_T1[0]/=j;
 
month_T2[0]=0;
 j=0;
 while ((day_T2[j]!=0)&&(j<10))  {month_T2[0]+=day_T2[j];j++;}
 month_T2[0]/=j;
 
month_AMP[0]=0;
 j=0;
 while ((day_AMP[j]!=0)&&(j<10)) {month_AMP[0]+=day_AMP[j];j++;}
 month_AMP[0]/=j;
 
 count_t_o[0]=count_turn_on;
 count_turn_on=0;
 }


__interrupt void time2(void)
{
 TIM2_SR1_UIF=0; //flag "0"
 TIM2_IER_CC1IE=0;
 deca_minutes++;

}

__interrupt void time2cc(void)
{TIM2_SR1_CC1IF=0;
 TIM2_IER_UIE=1;//enable interrupt by overfollow

}


