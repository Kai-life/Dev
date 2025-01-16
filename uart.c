#include "uart.h"

void BaudrateSet(void);
void DataFormatSet(void);

void Usart0Init(void)
{
    rcu_periph_clock_enable(RCU_USART0);						            /* 使能USART0外设时钟 */
	
	  usart_deinit(USART0);				      			                    /* 复位USART0 */
	  
	  BaudrateSet();
	  DataFormatSet();
//	  usart_word_length_set(USART0, USART_WL_8BIT);		            /* 配置USART0字长 */
//	  usart_stop_bit_set(USART0, USART_STB_1BIT);					        /* 配置USART0停止位 */
//	  usart_parity_config(USART0, USART_PM_NONE);					        /* 配置USART0奇偶校验 */
//	  usart_baudrate_set(USART0, 9600);							              /* 配置USART0波特率 */
	  
	  usart_receive_config(USART0, USART_RECEIVE_ENABLE);			    /* 配置USART0接收 */
	  usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);		    /* 配置USART0发送 */
	  usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);	/* 配置USART0_RTS硬件控制流（接收） */
	  usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);	/* 配置USART0_CTS硬件控制流（发送）*/
	
	  usart_interrupt_enable(USART0, USART_INT_RBNE);
	  usart_interrupt_enable(USART0, USART_INT_IDLE);
	  usart_interrupt_enable(USART0, USART_INT_TC);     /* 使能发送完成中断 */
	  nvic_irq_enable(USART0_IRQn, 0, 1);
	
	  usart_enable(USART0);										/* 使能USART0 */
}

void BaudrateSet(void)
{
    switch(Slave.baudrate)
		{
			case 0x00:
				 usart_baudrate_set(USART0, 1200);							              /* 配置USART0波特率 */
			break;
			case 0x01:
				 usart_baudrate_set(USART0, 2400);							              /* 配置USART0波特率 */
			break;
			case 0x02:
				 usart_baudrate_set(USART0, 4800);							              /* 配置USART0波特率 */
			break;
			case 0x03:
				 usart_baudrate_set(USART0, 9600);							              /* 配置USART0波特率 */
			break;
			case 0x04:
				 usart_baudrate_set(USART0, 19200);							              /* 配置USART0波特率 */
			break;
			case 0x05:
				 usart_baudrate_set(USART0, 38400);							              /* 配置USART0波特率 */
			break;
			case 0x06:
				 usart_baudrate_set(USART0, 57600);							              /* 配置USART0波特率 */
			break;
			case 0x07:
				 usart_baudrate_set(USART0, 115200);							            /* 配置USART0波特率 */
			break;
			case 0x08:
				 usart_baudrate_set(USART0, 230400);							            /* 配置USART0波特率 */
			break;
			default:
			usart_baudrate_set(USART0, 9600);							              /* 配置USART0波特率 */
			break;
		}
}

void DataFormatSet(void)
{
    switch(Slave.dataFormat)
		{
			case 0x03:
			{
			    usart_word_length_set(USART0, USART_WL_8BIT);		            /* 配置USART0字长 */
	        usart_stop_bit_set(USART0, USART_STB_1BIT);					        /* 配置USART0停止位1 */
	        usart_parity_config(USART0, USART_PM_EVEN);					        /* 配置USART0奇校验 */
			}
			break;
			case 0x04:
			{
			    usart_word_length_set(USART0, USART_WL_8BIT);		            /* 配置USART0字长 */
	        usart_stop_bit_set(USART0, USART_STB_1BIT);					        /* 配置USART0停止位1 */
	        usart_parity_config(USART0, USART_PM_ODD);					        /* 配置USART0偶校验 */
			}
			break;
			case 0x05:
			{
			    usart_word_length_set(USART0, USART_WL_8BIT);		            /* 配置USART0字长 */
	        usart_stop_bit_set(USART0, USART_STB_1BIT);					        /* 配置USART0停止位 */
	        usart_parity_config(USART0, USART_PM_NONE);					        /* 配置USART0奇偶校验 */
			}
			break;
			case 0x06:
			{
			    usart_word_length_set(USART0, USART_WL_8BIT);		            /* 配置USART0字长 */
	        usart_stop_bit_set(USART0, USART_STB_2BIT);					        /* 配置USART0停止位2 */
	        usart_parity_config(USART0, USART_PM_NONE);					        /* 配置USART0奇偶校验 */
			}
		  break;
			default:
			{
			    usart_word_length_set(USART0, USART_WL_8BIT);		            /* 配置USART0字长 */
	        usart_stop_bit_set(USART0, USART_STB_1BIT);					        /* 配置USART0停止位 */
	        usart_parity_config(USART0, USART_PM_NONE);					        /* 配置USART0奇偶校验 */
			}
			break;
		}
		
}
