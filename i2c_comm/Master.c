#include "tm4c123gh6pm.h"
#include <stdint.h>

void delay(int mili)
{
	int i,j;
	for(i=0;i<mili;i++){
		for(j=0;j<4000;j++)
			;
	}
}
void ports_init()
{
	SYSCTL_RCGCGPIO_R = 0x20;
	;
	;
	;
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R = 0x1F;
	
	GPIO_PORTF_DEN_R = 0x1F;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_PUR_R = 0x11;
}
void i2c_Init()
{
	SYSCTL_RCGCI2C_R = (0x01 << 1);
	;
	;
	;
	SYSCTL_RCGCGPIO_R |= 0x01;
	;
	;
	;
	GPIO_PORTA_AFSEL_R = 0xC0;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0x00FFFFFF)|0x33000000;
	GPIO_PORTA_DEN_R = 0xC0;
	GPIO_PORTA_ODR_R = 0x80;//Open Drain func at pin7
	GPIO_PORTA_PUR_R = 0xC0;
	I2C1_MCR_R = I2C_MCR_MFE; //Enable master mode
	I2C1_MTPR_R = 0x07; //Calculating from data sheet
	
	
}
////////////////////////////////////////////////////////
void set_SA(uint8_t slaveAddress)
{
  I2C1_MSA_R = (slaveAddress << 1); //slave address of the master b(7:1)
}
///////////////////////////////////////////////////////////////
void set_mode_RW(uint8_t mode)
{
  
  if(mode == 0)
  {
    I2C1_MSA_R &= ~(1<<0); //Clear bit - transmit data
  }
  else
  {
    I2C1_MSA_R |= (1<<0); //set bit - receive data
  }
}
///////////////////////////////////////////////////////
void writeByte(uint8_t data, uint8_t cond)
{
  //This byte contains the data transferred during a transaction
  I2C1_MDR_R = data;
  while(I2C1_MCS_R & 0x01)
		;
  I2C1_MCS_R = cond;
	while(I2C1_MCS_R & 0x01)
		;
//  if( (I2C1_MCS_R & (1<<1) ) != 0)
//  {
//    if( (I2C1_MCS_R & (1<<4)) == 1){}
//    else
//    {
//      I2C1_MCS_R = (1<<2);
//      while( (I2C1_MCS_R & (1<<0)) != 0);
//    }
//  }
 delay(1000);	
}
//===========================MAIN======================
int main(void)
{
	ports_init();
	i2c_Init();
	set_SA(0x08);//slave address = 8
	set_mode_RW(0);
	while(1){
		switch(GPIO_PORTF_DATA_R)//pf4 pf3 pf2 pf1 pf0
		{
			case 0x0: //Both switches are pressed
				GPIO_PORTF_DATA_R |= 0x02; // 0001(PF1)0
				writeByte(0x02,7);
				break;
			case 0x01: //only sw1 is pressed
				GPIO_PORTF_DATA_R |= 0x04; // 001(PF2)00
				writeByte(0x04,7);
				break;
			case 0x10: //only sw2 is pressed
				GPIO_PORTF_DATA_R |= 0x08; // 01(PF2)000
				writeByte(0x08,7);
				break;
			default: // None of the switches are pressed
				GPIO_PORTF_DATA_R &= 0x11;//1 0001
				writeByte(0x11,7);
		}
		delay(500);
	}
}

