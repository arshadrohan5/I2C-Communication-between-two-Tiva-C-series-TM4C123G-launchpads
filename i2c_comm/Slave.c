//#include "tm4c123gh6pm.h"
//#include <stdint.h>
//void EnableInterrupts(void);
//void DisableInterrupts(void);
//void delay(int mili)
//{
//	int i,j;
//	for(i=0;i<mili;i++){
//		for(j=0;j<4000;j++)
//			;
//	}
//}
//void ports_init()
//{
//	SYSCTL_RCGCGPIO_R = 0x20;
//	;
//	;
//	;
//	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
//	GPIO_PORTF_CR_R = 0x1F;
//	
//	GPIO_PORTF_DEN_R = 0x1F;
//	GPIO_PORTF_DIR_R = 0x0E;
//	GPIO_PORTF_PUR_R = 0x11;
//}
//////////////////////////////////////////////////////
//uint8_t read_Data(void)
//{
//	uint8_t data;
//	data = 0;
//	uint32_t scr;
//	scr = I2C1_SCSR_R;
//		if(scr & I2C_SCSR_RREQ)
//		{
//			// Data to be read
//			data=I2C1_SDR_R;
//		}
////		else if (I2C1_SCSR_R & I2C_SCSR_TREQ) {
////			// Data to be transmitted.
////			I2C1_SDR_R = data;
////		}
//	return data;
//}
//////////////////////////////////////////////////////
//void set_SA(uint8_t slaveAddress)
//{
//  I2C1_SOAR_R = (slaveAddress); //slave address of the master b(7:1)
//}
/////////////////////////////////////////////////////////
//void i2c_Init_s(void)
//{
//	SYSCTL_RCGCI2C_R = 0x2;
//	;
//	;
//	;
//	SYSCTL_RCGCGPIO_R |= 0x01;
//	;
//	;
//	;
//	GPIO_PORTA_AFSEL_R = 0xC0;
//	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0x00FFFFFF)|0x33000000;
//	GPIO_PORTA_ODR_R = 0x80;
//	GPIO_PORTA_DEN_R = 0xC0;
//	I2C1_MTPR_R = 7;
//	I2C1_MCR_R = I2C_MCR_SFE;
//	set_SA(0x08);
//	I2C1_SCSR_R = I2C_SCSR_DA;
//	
//}
/////////////////////////////////////////////////////////
//void Enable_Slave_Int( void)
//{
//	// Clear any prior interrupt and unmask interrupt for data interrupt
//	I2C1_SICR_R |= I2C_SICR_DATAIC;
//	I2C1_SIMR_R |= I2C_SIMR_DATAIM; 
//	NVIC_PRI9_R = (NVIC_PRI9_R & 0xFFFF00FF)|0x00006000;
//	NVIC_EN1_R = (1<<5);
//}
////////////////////////////////////////////
//void I2C1_Handler()
//{ 
//	volatile uint32_t readback;
//  uint8_t data;
//	I2C1_SICR_R |= I2C_SICR_DATAIC;//clear interrupt
//	readback = I2C1_SICR_R;
//	data=read_Data();
//		switch(data)
//		{
//			case 0x02:
//				GPIO_PORTF_DATA_R |= 0x02;
//				break;
//			case 0x04:
//				GPIO_PORTF_DATA_R |= 0x04;
//				break;
//			case 0x08:
//				GPIO_PORTF_DATA_R |= 0x08;
//				break;
//			case 0x11:
//				GPIO_PORTF_DATA_R &= ~0x0E;
//		}
//}
////===========================MAIN========================
//int main()
//{
//	DisableInterrupts();
//	EnableInterrupts();
//	ports_init();
//	i2c_Init_s();
//	Enable_Slave_Int();
//	while(1)
//	{
//		
//	}
//}
//	