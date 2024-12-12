#define CONTROL_REGISTER_A_ADDRESS 0X80
#define CONTROL_REGISTER_B_ADDRESS 0x81
#define COUNTER_LOWER_REGISTER_ADDRESS 0X84
#define COMPARE_REGISTER_A_ADDRESS 0X88
#define TIMER_INTERRUPT_MASK_REGISTER_ADDRESS 0X6F;
#define MAX_VALUE 60000
#define MIN_VALUE 600
void port_intialization ();
void timer1_init(void);
void portf(void);
void portk(void);
void delay1(volatile char);
volatile char GREEN_LED = 0;
volatile char RED_LED = 0;
volatile char press = 0;


void port_intialization (){
  volatile char *dirf,*dirk;
  dirf=0x30;dirk=0x107;
  *dirf=0xff;*dirk=0x01;
  volatile char press = 0;
}
void portf(){
  volatile char *outf=0x31;
  if(GREEN_LED == 0) *outf=0x00;   
  if(GREEN_LED == 1) *outf=0x01;     
  if(GREEN_LED == 2) *outf=0x03;   
  if(GREEN_LED == 3) *outf=0x07;   
  if(GREEN_LED == 4) *outf=0x0F; 
  GREEN_LED = (GREEN_LED + 1) % 5;
  delay1(1);
}
void delay1(volatile char num){
   volatile long i;
   while(num){
    for(i=0;i<100;i++);
    num--;
   }
}
void portk(void){
  volatile char *outk=0x108;
  if(RED_LED == 0) *outk=0x00;  
  if(RED_LED == 1) *outk=0x01;   
  if(RED_LED == 2) *outk=0x03;  
  if(RED_LED == 3) *outk=0x07;   
  if(RED_LED == 4) *outk=0x0F; 
  RED_LED = (RED_LED + 1) % 5;
  delay1(1);
}
void timer1_init(void){
  volatile char *TCCR1_A = 0x80;  // FOR SELECTING MODE
  volatile char *TCCR1_B = 0X81;  // FOR SETTING ANY PRESCALER
  volatile short *TCNT1_L  = 0X84;  // FOR STORING COUNTING VALUE
  volatile short *OCR1A_L  = 0X88;  // COMPARED VALUE STORED HERE
  volatile char *TIMSK_1 = 0X6f;  // FOR ENABLING THE INTRRUPT
  // FOR CTC MODE AND PRESCALER=256
  *TCCR1_A  = 0X00;
  *TCCR1_B  = 0X0C;
  *TCNT1_L  = 0x00;  // COUNTING VALUE STARTS FROM 0
  *OCR1A_L  = MAX_VALUE;  // GIVING COMPARED VALUE
  *TIMSK_1  = 0X02;  // Output Compare A Match Interrupt Enable
}
ISR(TIMER1_COMPA_vect) {
  if(press == 0){
    portf();
  }
  else{
    portk();
  }
  press = press ^ 0x01;
}
