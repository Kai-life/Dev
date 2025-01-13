#include "gpio.h"

static void PortA_GpioConfig(void)
{
	  rcu_periph_clock_enable(RCU_GPIOA);
	
	  gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_0);/* Ramp3 上拉低电平有效 */
	
	  gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_1);/* Ramp4 上拉低电平有效 */
	  
    gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_2);/* ADC_VBUS */
	  
	  gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_3);/* ADC_TEMP */
	
	  gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_4);/* DAC_SPEED */
	
	  gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_5);/* ERR_IN */
	  gpio_af_set(GPIOA, GPIO_AF_2, GPIO_PIN_5);/* 复用为Timer1_CH0的pwm输入捕获 */
	
	  gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6);/* SW_ON */
	  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
	  gpio_bit_reset(GPIOA, GPIO_PIN_6);/* 上电输出低电平关闭泄放电路 */
	
	  gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_7);/* CTRL_DIR */
	  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
	  gpio_bit_reset(GPIOA, GPIO_PIN_7);/* 上电输出低电平CW */
		
		gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);/* UART0_TX */
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
	  gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);
		
		gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);/* UART0_RX */
	  gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);
		
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);
	  gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);/* UART0_RTS */
	  gpio_bit_reset(GPIOA, GPIO_PIN_12);/* UART0_RTS */
}

static void PortB_GpioConfig(void)
{
	  rcu_periph_clock_enable(RCU_GPIOB);
	
	  gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_0);/* PLC_SPEED_A */
	
	  gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_3);/* SPEED_A 上拉低电平有效 */
	
	  gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_4);/* SPEED_B 上拉低电平有效 */
	
	  gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_5);/* SPEED_C 上拉低电平有效 */
	
	  gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_6);/* SPEED_D 上拉低电平有效 */
	
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_7);
	  gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
	  gpio_bit_set(GPIOB, GPIO_PIN_7);/* 上电关闭绿灯LED2 */
	  
	  gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8);
	  gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	  gpio_bit_set(GPIOB, GPIO_PIN_8);/* 上电关闭红灯LED1 */
	
}

static void PortF_GpioConfig(void)
{
    rcu_periph_clock_enable(RCU_GPIOF);
	
	  gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_0);/* Ramp1 上拉低电平有效 */
	
	  gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_1);/* Ramp2 上拉低电平有效 */
}

void GpioConfig(void)
{
    PortA_GpioConfig();
    PortB_GpioConfig();
    PortF_GpioConfig();
}
