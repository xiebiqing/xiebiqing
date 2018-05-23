#include "LPC11xx.h"                    // Device header
#define LED1_ON()  (LPC_GPIO2->DATA &= ~(1<<0))
#define LED1_OFF() (LPC_GPIO2->DATA |= (1<<0))

#define LED2_ON()  (LPC_GPIO2->DATA &= ~(1<<1))
#define LED2_OFF() (LPC_GPIO2->DATA |= (1<<1))



void LedInit()
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); //使能IOCON时钟
    LPC_IOCON->PIO2_0 &= ~0x07;    
    LPC_IOCON->PIO2_0 |= 0x00; //把P2.0管脚设置为GPIO
	
	  LPC_IOCON->PIO2_1 &= ~0x07; 
    LPC_IOCON->PIO2_1 |= 0x00; //把P2.1管脚设置为GPIO
		
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 禁能IOCON时钟
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);     // 使能GPIO
    LPC_GPIO2->DIR  |= (1<<0); ; // 把P2.0设置为输出引脚
    LPC_GPIO2->DATA |= (1<<0); ; // 把P2.0设置为高电平
	
	  LPC_GPIO2->DIR  |= (1<<1); ; // 把P2.1设置为输出引脚
    LPC_GPIO2->DATA |= (1<<1); ; // 把P2.1设置为高电平
	
	}


void TIMER32_0_IRQHandler (void)
{
    LPC_TMR32B0->IR = 0x01;                                 //向匹配通道0写1清除中断
    if (LPC_GPIO2->DATA & (1<<0)) 
    {
            LED1_ON();                                                        //点亮LED
    } 
    else 
    {
            LED1_OFF();                                                       //熄灭LED
    }
		
		if (LPC_GPIO2->DATA & (1<<1)) 
    {
            LED2_ON();                                                        //点亮LED
    } 
    else 
    {
            LED2_OFF();                                                       //熄灭LED
    }
		
		}

void Timer0Init (void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9);  //使能TIM32B0时钟
    LPC_TMR32B0->IR      = 0x01; //MR0中断复位，即清中断(bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0)
    LPC_TMR32B0->PR      = 0;                           //每一个PCLK加1
    LPC_TMR32B0->MCR     = 0x03;                    //MR0匹配时复位TC,并产生中断
    LPC_TMR32B0->MR0     = SystemCoreClock/2; //匹配时间，也就是定时时间
    LPC_TMR32B0->TCR     = 0x01;                    //启动计数器:TCR[0]=1;
    NVIC_EnableIRQ(TIMER_32_0_IRQn);            //使能中断
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