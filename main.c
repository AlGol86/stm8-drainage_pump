#include "iostm8s103f3.h"
#include "main.h"

char y[10] ; //10 columns indicator50
char button=0; //left(K1): 1  right(K2): 2  center(K3): 3  long push(K3): 4  for ignor doble push (pushing batton) for action:5
int counter_button=0;
int AMPcounter=0;
char trig_AMP=0;
int day_T1[10];
int day_T2[10];
int day_AMP[10];
int count_turn_on=0;
int month_T1[30];
int month_T2[30];
int month_AMP[30];
int count_t_o[30];

char alarm_flag=0;

char deca_minutes=0;  //0-10-2550 minutes
int AMP=0; // 000..709 (*0.01) A
int AMP_del=0;
char step_AMP=0;
int T1=0;
int T2=0;
char state_indicator=0; //0-ampers 100-t1(time in load) 200-t2(interval on-on) 
//////////////////////////1-30 ampers for 30 days 
//////////////////////////100-130 time in load for 30 days
//////////////////////////200-230 interval on-on in load for 30 days
char timer_flags=0;
char counti=0;
int sys_del=0;

int main( void )
{ 
for (char i=0;i<10;i++) y[i]=0;
for (char i=0;i<10;i++) day_T1[i]=0;
for (char i=0;i<10;i++) day_T2[i]=0;
for (char i=0;i<10;i++) day_AMP[i]=0;
for (char i=0;i<30;i++) month_T1[i]=0;
for (char i=0;i<30;i++) month_T2[i]=0;
for (char i=0;i<30;i++) month_AMP[i]=0;
for (char i=0;i<30;i++) count_t_o[i]=0;

init_buttons();
init_tim1();
  
 while(1)
 {  
 indicator(y); 
 }
} 
