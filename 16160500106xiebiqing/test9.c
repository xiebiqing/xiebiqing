#include "LPC11xx.h"                    // Device header
#define LED1_ON()  (LPC_GPIO2->DATA &= ~(1<<0))
#define LED1_OFF() (LPC_GPIO2->DATA |= (1<<0))

#define LED2_ON()  (LPC_GPIO2->DATA &= ~(1<<1))
#define LED2_OFF() (LPC_GPIO2->DATA |= (1<<1))



void LedInit()
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); //ʹ��IOCONʱ��
    LPC_IOCON->PIO2_0 &= ~0x07;    
    LPC_IOCON->PIO2_0 |= 0x00; //��P2.0�ܽ�����ΪGPIO
	
	  LPC_IOCON->PIO2_1 &= ~0x07; 
    LPC_IOCON->PIO2_1 |= 0x00; //��P2.1�ܽ�����ΪGPIO
		
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);     // ʹ��GPIO
    LPC_GPIO2->DIR  |= (1<<0); ; // ��P2.0����Ϊ�������
    LPC_GPIO2->DATA |= (1<<0); ; // ��P2.0����Ϊ�ߵ�ƽ
	
	  LPC_GPIO2->DIR  |= (1<<1); ; // ��P2.1����Ϊ�������
    LPC_GPIO2->DATA |= (1<<1); ; // ��P2.1����Ϊ�ߵ�ƽ
	
	}


void TIMER32_0_IRQHandler (void)
{
    LPC_TMR32B0->IR = 0x01;                                 //��ƥ��ͨ��0д1����ж�
    if (LPC_GPIO2->DATA & (1<<0)) 
    {
            LED1_ON();                                                        //����LED
    } 
    else 
    {
            LED1_OFF();                                                       //Ϩ��LED
    }
		
		if (LPC_GPIO2->DATA & (1<<1)) 
    {
            LED2_ON();                                                        //����LED
    } 
    else 
    {
            LED2_OFF();                                                       //Ϩ��LED
    }
		
		}

void Timer0Init (void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);  //ʹ��TIM32B0ʱ��
    LPC_TMR32B0->IR      = 0x01; //MR0�жϸ�λ�������ж�(bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0)
    LPC_TMR32B0->PR      = 0;                           //ÿһ��PCLK��1
    LPC_TMR32B0->MCR     = 0x03;                    //MR0ƥ��ʱ��λTC,�������ж�
    LPC_TMR32B0->MR0     = SystemCoreClock/2; //ƥ��ʱ�䣬Ҳ���Ƕ�ʱʱ��
    LPC_TMR32B0->TCR     = 0x01;                    //����������:TCR[0]=1;
    NVIC_EnableIRQ(TIMER_32_0_IRQn);            //ʹ���ж�
}


void Delay(void)
{
  uint16_t i,j;
	for(i=0;1<5000;i++)
	   for(j=0;j<200;j++);
	   
}



int main(void)
{
    LedInit();
    Timer0Init();
    while (1) 
	  {
			 LED1_ON();
       LED2_OFF();
					
       Delay();
			
       LED1_OFF();
       LED2_ON();
       			
					}
}