//nombers of row (port c)
#define c3 8 // D1->A1
#define c4 16
#define c5 32
#define c6 64
#define c7 128

#define c34 (c3|c4)
#define c56 (c5|c6)
#define c_mask (c3|c4|c5|c6|c7)

//nombers of column (port d)
#define d1 2
#define d2 4
#define d4 16
#define d5 32
#define d6 64
#define d_mask (d1|d2|d4|d5|d6)

#define bit_left_button  2 //left button a1
#define bit_right_button 4 //right button a2
#define bit_centr_button 8 //centr button a3

#define PA GPIOA
#define PB GPIOB
#define PD GPIOD
#define PC GPIOC

#define eeprom_alarm ((char*)0x4010)

#pragma vector = 13
__interrupt void time1(void);

#pragma vector = 16
__interrupt void time2cc(void);

#pragma vector = 15
__interrupt void time2(void);

//measurment_I_T1_T2
int get_ADC(void);
int current_AMP(void);
int ADC_compensation(int value_ADC);
void event_AMP(void);
void write_eeprom(char* addr_eeprom,char data);

//timers & buttons
void init_tim1(void);
void init_tim2(void);

void init_buttons(void);
void buttons(void);
void func_batton_1(void);
void func_batton_2(void);
void func_batton_3(void);
void func_batton_4(void);
void pushed_button(void);
void indicate_state (void);

//indicator50
void delay(int j);
void indicator (char s[10]);
void dig  (char a,char pozition);
void numb (int n,char point);
void print(char a, char pozition);

