#include "iostm8s103f3.h"
#include "main.h"

extern char timer_flags;
extern char alarm_flag;
extern char deca_minutes;  //0-10-2550 minutes
extern int AMP;//Amper
extern int T1;
extern int T2;
extern char trig_AMP;
extern int day_T1[10];
extern int day_T2[10];
extern int day_AMP[10];
extern int count_turn_on;
extern int month_T1[30];
extern int month_T2[30];
extern int month_AMP[30];
extern int count_t_o[30];
extern int sys_del;
extern char button; //left(K1): 1  right(K2): 2  center(K3): 3  long push(K3): 4  for ignor doble push (pushed batton) for action:5
extern int counter_button;
extern char state_indicator; //0-ampers 100-t1(time in load) 200-t2(interval on-on) 
//////////////////////////1-30 ampers for 30 days 
//////////////////////////100-130 time in load for 30 days
//////////////////////////200-230 interval on-on in load for 30 days

void init_tim1(void) //count days each 24 hours
{

TIM1_IER_UIE=0;//enable interrupt by overfollow
	//TIM1_IER_CC1IE=1;//enable interrupt by compare
  TIM1_PSCRH=0xFF; //prescaler 0-255 
  TIM1_PSCRL=0xFF; //prescaler 0-255 
  TIM1_ARRH=216; //preload registr high bits
  TIM1_ARRL=0xFF;
  TIM1_RCR=23; //0:1 hour   1:2 hours 23: 24 hours 
	//TIM1_CCR1H=12;//capture/compare registr high bits
	//TIM1_CCR1L=0;
	TIM1_CNTRH=0;
	TIM1_CNTRL=0;
      
	asm("rim");
	TIM1_CR1_CEN=1;
        for(int i=1;i<30000;i++){}
        for(int i=1;i<30000;i++){}
        TIM1_SR1_UIF=0;
        TIM1_IER_UIE=1;
    
}
 

void init_tim2(void) //count seconds 
{    
         asm("rim");
        
        deca_minutes=0;
  	TIM2_IER_UIE=0;
	TIM2_IER_CC1IE=1;
        TIM2_PSCR=15; //15 
	TIM2_ARRH=0x8f; //0x8f
        TIM2_ARRL=0x60; //0x60
	TIM2_CNTRH=0;
	TIM2_CNTRL=0;
        TIM2_CR1_CEN=1;
}

  
void indicate_state (void)
{
switch (state_indicator)
 {
 case 0:   {print ('T',1);dig (0,2);print ('K',3); break;}
 case 1:   {numb(AMP,1); break;}
 case 100: {print ('P',1);print ('A',2);print ('<',3);break;} //K1
 case 101: {if(trig_AMP) numb(T1,0); else numb(day_T1[0],0); break;}
 case 200: {print ('G',1);print ('E',2);print ('P',3); break;} //K2
 case 201: {if(trig_AMP==0) numb(T2,0);else numb(day_T2[0],0); break;}
 case 150: {print ('K',1);dig (0,2);print ('L',3); break;} //K2
 case 151: {numb(count_turn_on,0); break;}
 }
if ((state_indicator>1)&&(state_indicator<32))     {if ((TIM2_CNTRL&96)==0) {numb(state_indicator-2,0);  print ('T',1);}else numb(month_AMP[state_indicator-2],1); }//
if ((state_indicator>101)&&(state_indicator<132))  {if ((TIM2_CNTRL&96)==0) {numb(state_indicator-102,0);print ('P',1);}else numb(month_T1[state_indicator-102],0);}//
if ((state_indicator>201)&&(state_indicator<232))  {if ((TIM2_CNTRL&96)==0) {numb(state_indicator-202,0);print ('G',1);}else numb(month_T2[state_indicator-202],0);}//day_T2[state_indicator-202]
if ((state_indicator>151)&&(state_indicator<182))  {if ((TIM2_CNTRL&96)==0) {numb(state_indicator-152,0);print ('L',1);}else numb(count_t_o[state_indicator-152],0);}
}

void init_buttons(void)
{
  PA_DDR&=~(bit_right_button | bit_left_button | bit_centr_button);  // pin_button 1,2,3=>input
  PA_CR1|=bit_right_button | bit_left_button | bit_centr_button;     //pin_button 1,2,3 =>pull-up
  PA_CR2&=~(bit_right_button | bit_left_button | bit_centr_button); //interrupts disabled
}

void buttons(void)
{
  if ((((PA_IDR & bit_left_button)==0)||((PA_IDR&bit_right_button)==0)||((PA_IDR&bit_centr_button)==0))&&(counter_button<10000)) counter_button++;
   else if (counter_button>5) counter_button=5;  //(counter_button=10000) or (any batton not pushed)
          else if (counter_button>0)counter_button--;  //(counter_button=1..5) and (any batton not pushed)
 if ((counter_button>2)&&((PA_IDR&bit_left_button )==0)&&(button==0)) button=1;
 if ((counter_button>2)&&((PA_IDR&bit_right_button)==0)&&(button==0)) button=2;
 if ((counter_button>2)&&((PA_IDR&bit_centr_button)==0)&&(button==0)) button=3;
 if ((counter_button>8000)&&((PA_IDR&bit_centr_button)==0))           button=4; //long push
 if ((counter_button<2)&&(button==5))  { button=0;}
 
}

void pushed_button(void)
{
switch (button)
 {
 case 0: {asm("nop");              break;}
 case 1: {func_batton_1();button=5;break;} //K1
 case 2: {func_batton_2();button=5;break;} //K2
 case 4: {func_batton_4();button=5;break;} //K3
 case 3: {func_batton_3();button=5;break;} //K3-long
 case 5: {asm("nop");              break;}
 }
}



void func_batton_1(void) //left button K1
{
  switch (state_indicator)
 {
 case 0:   {state_indicator=150;break;}
 case 1:   {state_indicator=150;break;}
 case 100: {state_indicator=0;  break;} 
 case 101: {state_indicator=0;  break;}
 case 200: {state_indicator=100;break;} 
 case 201: {state_indicator=100;break;}
 case 150: {state_indicator=200;break;} 
 case 151: {state_indicator=200;break;}
 }
 if ((state_indicator>2)&&(state_indicator<32)) state_indicator--;
 else  if (state_indicator==2) state_indicator=31;
 if ((state_indicator>102)&&(state_indicator<132)) state_indicator--;
 else  if (state_indicator==102) state_indicator=131;
 if ((state_indicator>202)&&(state_indicator<232)) state_indicator--;
 else  if (state_indicator==202) state_indicator=231;
 if ((state_indicator>152)&&(state_indicator<182)) state_indicator--;
 else  if (state_indicator==152) state_indicator=181;
 
}

void func_batton_2(void) //right button K2
{
    switch (state_indicator)
 {
 case 0:   {state_indicator=100; break;}
 case 1:   {state_indicator=100; break;}
 case 100: {state_indicator=200;   break;} 
 case 101: {state_indicator=200;   break;}
 case 200: {state_indicator=150; break;} 
 case 201: {state_indicator=150; break;}
 case 150: {state_indicator=0;break;} 
 case 151: {state_indicator=0;break;}
 }
 if ((state_indicator>1)&&(state_indicator<31)) state_indicator++;
 else  if (state_indicator==31) state_indicator=2;
 if ((state_indicator>101)&&(state_indicator<131)) state_indicator++;
 else  if (state_indicator==131) state_indicator=102;
 if ((state_indicator>201)&&(state_indicator<231)) state_indicator++;
 else  if (state_indicator==231) state_indicator=202;
 if ((state_indicator>151)&&(state_indicator<181)) state_indicator++;
 else  if (state_indicator==181) state_indicator=152;
}

void func_batton_3(void)
{
 if ((state_indicator>1)&&(state_indicator<32))    state_indicator=0;
  else
   if ((state_indicator>101)&&(state_indicator<132)) state_indicator=100;
    else 
      if ((state_indicator>201)&&(state_indicator<232)) state_indicator=200;
       else
          if ((state_indicator>151)&&(state_indicator<182)) state_indicator=150;
            else
              switch (state_indicator)
                 {
                 case 0:   {state_indicator=2;  break;}
                 case 1:   {state_indicator=2;  break;}
                 case 100: {state_indicator=102;break;} 
                 case 101: {state_indicator=102;break;}
                 case 200: {state_indicator=202;break;} 
                 case 201: {state_indicator=202;break;}
                 case 150: {state_indicator=152;break;} 
                 case 151: {state_indicator=152;break;}
                 }
 
}

void func_batton_4(void)
{
  alarm_flag=0;
  PB_DDR&=~16;
  write_eeprom(eeprom_alarm,0);
  init_tim2();
  T1=0;
}

