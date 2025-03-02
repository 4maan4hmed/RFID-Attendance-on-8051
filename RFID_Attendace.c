#include<reg51.h>
#include<intrins.h>

void i2c_start(void);
void i2c_stop(void);
void i2c_ACK(void);
void i2c_write(unsigned char);
void i2c_DevWrite(unsigned char);
void lcd_send_cmd(unsigned char);
void lcd_send_data(unsigned char);
void lcd_send_str(unsigned char *);
void lcd_slave(unsigned char );
void delay_ms(unsigned int);
void clear(void);
//++++++++++++++++++++++++++++++++++++++++++


char count = 0;            // count = 0

char input[12];           // character array of size 12

char ch;   


char rxdata(void);      

//++++++++++++++++++++++++++++++++++++++++++
unsigned char slave1=0x4E;
unsigned char slave_add;

sbit scl=P0^6;
sbit sda=P0^7;

void i2c_start(void)
{
sda=1;_nop_();_nop_();
scl=1;_nop_();_nop_();
sda=0;_nop_();_nop_();
}

void i2c_stop(void)
{
scl=0;
sda=0;
scl=1;
sda=1;
}

void lcd_slave(unsigned char slave)
{
slave_add=slave;
}

void i2c_ACK(void)
{
scl=0;
sda=1;
scl=1;
while(sda);
}

void i2c_write(unsigned char dat)
{
unsigned char i;
for(i=0;i<8;i++)
{
scl=0;
sda=(dat&(0x80)>>i)?1:0;
scl=1;
}
}

void lcd_send_cmd(unsigned char cmd)
{
unsigned char cmd_l,cmd_u;
cmd_l=(cmd<<4)&0xf0;
cmd_u=(cmd &0xf0);
i2c_start();			 //BL EN RW RS 1 1 0 0
i2c_write(slave_add);
i2c_ACK();
i2c_write(cmd_u|0x0C);
i2c_ACK();
delay_ms(1);
i2c_write(cmd_u|0x08); // 1 0 0 0
i2c_ACK();
delay_ms(10);
i2c_write(cmd_l|0x0C);	 // 1 1 0 0
i2c_ACK();
delay_ms(1);
i2c_write(cmd_l|0x08);
i2c_ACK();
delay_ms(10);
i2c_stop();
}

void lcd_send_data(unsigned char dataw)// 1 1 0 1
{
unsigned char dataw_l,dataw_u;
dataw_l=(dataw<<4)&0xf0;
dataw_u=(dataw &0xf0);
i2c_start();
i2c_write(slave_add);
i2c_ACK();
i2c_write(dataw_u|0x0D);//BL EN RW RS   1 1 0 1
i2c_ACK();
delay_ms(1);
i2c_write(dataw_u|0x09);// 1 0 0 1
i2c_ACK();
delay_ms(10);
i2c_write(dataw_l|0x0D);
i2c_ACK();
delay_ms(1);
i2c_write(dataw_l|0x09);
i2c_ACK();
delay_ms(10);
i2c_stop();
}

void lcd_send_str(unsigned char *p)
{
while(*p != '\0')
lcd_send_data(*p++);
}


void delay_ms(unsigned int n)
{
unsigned int m;
for(n;n>0;n--)
{
  for(m=121;m>0;m--);
    _nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
}

void lcd_init()
{
lcd_send_cmd(0x02);	// Return home
lcd_send_cmd(0x28);	// 4 bit mode
lcd_send_cmd(0x0C);	// Display On , cursor off
lcd_send_cmd(0x06);	// Increment Cursor (shift cursor to right)
lcd_send_cmd(0x01); // clear display
}

void main(void)
{
		
TMOD=0x20;                  //timer 1 , mode 2 , auto reload

SCON=0x50;                   //8bit data , 1 stop bit , REN enabled

TH1=0xfd;                  //timer value for 9600 bits per second(bps)

                   TR1=1;    //start the timer

lcd_slave(slave1);
lcd_init();
lcd_send_cmd(0x80);
lcd_send_str("   Greetings!   ");
lcd_send_cmd(0xC0);	
lcd_send_str("Please Tap CARD");
	

                         while(count<10	)                //repeat for 12 times

                         {
                                    input[count]=rxdata(); //receive serial data and store it.

                                    count++;
						
                         }
												 clear();
												 	lcd_send_cmd(0x80);
												 if(input[9]=='7'&& input[8]=='4'){
													 lcd_send_cmd(0x80);
													 lcd_send_str("Amaan Ahmad");
													 lcd_send_cmd(0xC0);
													 lcd_send_str("22BEC1179");
													 
												 }
												 else if(input[9]=='9' && input[8]=='1'){
													 lcd_send_cmd(0x80);
													 lcd_send_str("Akshat Verma");
													 lcd_send_cmd(0xC0);
													 lcd_send_str("22BEC1318"); 	
													
												 }
												  else if(input[9]=='1' && input[8]=='0'){
													 lcd_send_cmd(0x80);
													 lcd_send_str("Pranav Choudhary");
													 lcd_send_cmd(0xC0);
													 lcd_send_str("22BEC1447");
													
												 }
													else if(input[9]=='9' && input[8]=='8'){
													 lcd_send_cmd(0x80);
													 lcd_send_str("Sarthak Bhagwat");
													 lcd_send_cmd(0xC0);
													 lcd_send_str("22BEC1189");
												
												 }
												  else{
														lcd_send_cmd(0x80);
													 lcd_send_str("Not in directory");
														lcd_send_cmd(0xC0);
													 lcd_send_str(input);
													}
delay_ms(2500);
clear();
}
char rxdata()

{	
	
  while(RI==0){
	}  //wait till RI becomes HIGH
  RI=0;           //make RI low
  ch=SBUF;      //copy received data 
  return ch;      //return the received data to main function.


}
void clear(){
	lcd_send_cmd(0x80);
lcd_send_str("                ");
lcd_send_cmd(0xC0);
lcd_send_str("                ");
}