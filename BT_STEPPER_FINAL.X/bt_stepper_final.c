#include <xc.h>
#include <stdint.h>
#include <string.h>
#define _XTAL_FREQ 20000000
unsigned int a,b,i;
//--[ Control Data ]--

//--------------------------------
// Functions Declarations
#define RS RC0
#define E RC1
#define LOOP 400
void delay(void)
{
	unsigned d;
	for(d=1; d<=LOOP; d++);
}

void lcd_ins(unsigned char a)
{
	RS=0;
	PORTD=a;
	E=1;  delay(); E=0; delay();
	__delay_ms(4);
}

void lcd_putch(unsigned char a)
{
	RS=1;
	PORTD=a;
	E=1;  delay(); E=0; delay();
	__delay_ms(4);
}
		
void lcd_init(void)
{
	__delay_ms(20);
	lcd_ins(0x30);	// 
	lcd_ins(0x30);	// 
	lcd_ins(0x30);	// 
	lcd_ins(0x38);	// 8 bit inteface, 1 line to disp, font size 5x7
	lcd_ins(0x08);	//  enable display, no blink, no cursor
	lcd_ins(0x01);	//  clear display
	lcd_ins(0x06);	// cursor move dir, incr cursor, no shift (scrolling)
}
	
void lcd_clear(void)
{
	lcd_ins(1);
	__delay_ms(4);
}

void lcd_puts(char *p)
{
	while(*p)
	{
		lcd_putch(*p);
		p++;
		__delay_ms(10);
	}
	
}
void lcd_goto(int x)
{
	lcd_ins(0x80+x);
}

void lcd_shift(int dir)
{
      if (dir==0)
         lcd_ins(24);   // shift display left
/*     else
           lcd_ins(28);   // shift display right
*/}

long d;
void UART_RX_Init(void);
// Globals
//int UART_Buffer = 0;
//--------------------------------
unsigned char UART_Buffer; 
// Main Routine
void main(void)
{int i;
    TRISC=0; PORTC=0;
	ADCON1=7;
	PORTE=0;
	 TRISA=0;
    ADCON1=7;
    a=1;
	
	
	
	
  //--[ Peripherals & IO Configurations ]--
  UART_RX_Init(); // Initialize The UART in Master Mode @ 9600bps
  RCIE = 1; // UART Receving Interrupt Enable Bit
  PEIE = 1; // Peripherals Interrupt Enable Bit
  GIE = 1; // Global Interrupt Enable Bit
 lcd_init();
lcd_ins(12);	// display on
 
  //TRISD=0;     
 // TXIE=1;
  //PORTD=0;
 //unsigned char UART_Buffer;
  //---------------------------
 while(1);
  /*while(1) 
  {
      while(!PIR1bits.RCIF);
       UART_Buffer = RCREG; 
       switch( UART_Buffer)
       {
           case 'C': 
		{
			PORTD=a;
	        for(d=1; d<=25000; d++);
            PORTD=5;
	    }       
               
                    break;
       }
  }*/
  return;
}
//--------------------------------
// Functions Definitions
 
void UART_RX_Init()
{
  BRGH = 1; // Set For High-Speed Baud Rate
  SPBRG = 129; // Set The Baud Rate To Be 9600 bps
  // Enable The Ascynchronous Serial Port
  SYNC = 0;
  SPEN = 1;
  TRISC6=1;
  TRISC7=1;// Set The RX-TX Pins to be in UART mode (not io)
  TXEN=1;
  TXIF=0;  
  //--[ Enable UART Receiving Interrupts ]--
 
  //------------------
  CREN = 1; // Enable Data Continous Reception
}
 
void __interrupt( myISR(void))
{ 
lcd_puts("OJAS"); 

  //PIR1bits.RCIF = 0;
  while(!PIR1bits.RCIF);
  if((RCSTAbits.FERR==1)||(RCSTAbits.OERR==1))
  {
      RCSTAbits.CREN=0;
      UART_Buffer = RCREG; 
      RCSTAbits.CREN=1;
  }
 lcd_clear();
  lcd_puts("  OKREXTON"); 
  UART_Buffer = RCREG; // Read The Received Data Buffer
  lcd_puts("  Siddhant S");  
  lcd_puts(RCREG);
  PIR1bits.RCIF = 0;
  
    switch(UART_Buffer)
    {
        case 'C':
        {// lcd_clear();
	       // lcd_goto(0);
      //  lcd_puts(UART_Buffer);
         lcd_clear();
         lcd_goto(0);
     //    lcd_putch(RCREG);
         lcd_putch(UART_Buffer);
      //   lcd_puts("HANSHU");
       //  sprintf(UART_Buffer,"%c\n\r");
        for(i=1;i<=1000;i++)
        {
            PORTA=a;
        //PORTD=a;
        for(d=1;d<=1000;d++);
        a=a>>1;
        if(a<1)
            a=8;
        }
            break;
        }  
         
    // This could have been done within the main loop. Since it's not
    // Excessive processing, so it's OK to do it here below
   
      // case 'A':{PORTD=4; for(d=1; d<=25000; d++);}break; 
       case 'A':
        {// lcd_clear();
	       // lcd_goto(0);
      //  lcd_puts(UART_Buffer);
         lcd_clear();
         lcd_goto(0);
     //    lcd_putch(RCREG);
         lcd_putch(UART_Buffer);
      //   lcd_puts("HANSHU");
       //  sprintf(UART_Buffer,"%c\n\r");
        for(i=1;i<=1000;i++)
        {
            PORTA=a;
        //PORTD=a;
        for(d=1;d<=1000;d++);
        a=a<<1;
        if(a>8)
            a=1;
        }
            break;
        }  
         
        //case 'F':{PORTD=8; for(d=1; d<=25000; d++);}break;  
       
       // case 'S':{PORTD=16;for(d=1; d<=25000; d++);}break;
       case 'F':
        {// lcd_clear();
	       // lcd_goto(0);
      //  lcd_puts(UART_Buffer);
         lcd_clear();
         lcd_goto(0);
     //    lcd_putch(RCREG);
         lcd_putch(UART_Buffer);
      //   lcd_puts("HANSHU");
       //  sprintf(UART_Buffer,"%c\n\r");
        for(i=1;i<=1500;i++)
        {
            PORTA=a;
        //PORTD=a;
        for(d=1;d<=800;d++);
        a=a>>1;
        if(a<1)
            a=8;
        }
            break;
        }  
       case 'S':
        {// lcd_clear();
	       // lcd_goto(0);
      //  lcd_puts(UART_Buffer);
         lcd_clear();
         lcd_goto(0);
     //    lcd_putch(RCREG);
         lcd_putch(UART_Buffer);
      //   lcd_puts("HANSHU");
       //  sprintf(UART_Buffer,"%c\n\r");
        for(i=1;i<=500;i++)
        {
            PORTA=a;
        //PORTD=a;
        for(d=1;d<=2000;d++);
        a=a>>1;
        if(a<1)
            a=8;
        }
            break;
        }  
        case 'Q':{/*PORTD=32;*/for(d=1; d<=25000;d++);} break;
    
  }
  
    
    /* if(UART_Buffer == Blue_LED_OFF)
   else if(UART_Buffer =='A')
    {
      PORTD=8;
  else if(UART_Buffer =='A')
    {
      PORTD=8;
  
    *    RB0 = 0; // Blue LED OFF
    if(UART_Buffer == Yellow_Toggle)
      RB1 = ~RB1; // Toggle Yellow LED 
 */
 
    }