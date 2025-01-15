#include "timer.h"

PWM_CAPTURE_STRUCT DrivePwm;

/***********************************************************************************************
Function:   Timer0_Config
Brief:      TIMER0配置
Input:
Output:
Return:
Others:     50us定时器触发ADC注入通道采样
            72MHz/2400 = 30KHz.
***********************************************************************************************/
static void Timer0_Config(void)
{
    timer_parameter_struct       timer_initpara;                                  /* 定时器基本结构体 */
	  timer_ic_parameter_struct    timer_icintpara;                                 /* 输入捕获结构体 */
	  timer_struct_para_init(&timer_initpara);                                      /* 初始化结构体 */
	  timer_channel_input_struct_para_init(&timer_icintpara);
	
	  rcu_periph_clock_enable(RCU_TIMER0);  	                                      /* 开启时钟 */
	  timer_deinit(TIMER0);                                                         /* 复位定时器配置 */
	
	  timer_initpara.prescaler            = 0;                                      /* 预分频值 */
	  timer_initpara.alignedmode          = TIMER_COUNTER_EDGE;                     /* 对齐模式 */
	  timer_initpara.counterdirection     = TIMER_COUNTER_UP;                       /* 计数方向 */
	  timer_initpara.clockdivision        = TIMER_CKDIV_DIV1;                       /* 时钟分割系数 */
	  timer_initpara.period               = 2400;                                   /* 计数周期值 */
	  timer_initpara.repetitioncounter    = 0;                                      /* 重复计数器周期数 */
	  timer_init(TIMER0,&timer_initpara);                                           /* 基础配置写入 */
	
    timer_master_output_trigger_source_select(TIMER0,TIMER_TRI_OUT_SRC_UPDATE);   /* 配置TRGO输出触发源 */
	  timer_master_slave_mode_config(TIMER0,TIMER_MASTER_SLAVE_MODE_ENABLE);        /* 使能主从模式 */
		
		timer_interrupt_flag_clear(TIMER0,TIMER_INT_UP);                              /* 清除定时器0更新中断标志位 */
	  timer_interrupt_enable(TIMER0,TIMER_INT_UP);   											          /* 使能中断 */
		nvic_irq_enable(TIMER0_BRK_UP_TRG_COM_IRQn,1,1);                              /* 设置优先级组 */
		
		timer_enable(TIMER0);                                                         /* 使能定时器 */
}

/***********************************************************************************************
Function:   Timer1_Config
Brief:      TIMER1配置
Input:
Output:
Return:
Others:     捕获马达驱动板，ERROR信号PWM输出
***********************************************************************************************/
static void Timer1_Config(void)
{
    timer_parameter_struct       timer_initpara;                                  /* 定时器基本结构体 */
    timer_ic_parameter_struct    timer_icintpara;                                 /* 输入捕获结构体 */

    timer_struct_para_init(&timer_initpara);                                      /* 初始化结构体 */
    timer_channel_input_struct_para_init(&timer_icintpara);

    rcu_periph_clock_enable(RCU_TIMER1);                                          /* 开启时钟 */
    rcu_periph_clock_enable(RCU_GPIOA);                                           /* 开启GPIO时钟 */

    timer_deinit(TIMER1);                                                         /* 复位定时器配置 */

    timer_initpara.prescaler            = (72-1);                                 /* 预分频值 */
    timer_initpara.alignedmode          = TIMER_COUNTER_EDGE;                     /* 对齐模式 */
    timer_initpara.counterdirection     = TIMER_COUNTER_UP;                       /* 计数方向 */
    timer_initpara.clockdivision        = TIMER_CKDIV_DIV1;                       /* 时钟分割系数 */
    timer_initpara.period               = 65535;                                  /* 计数周期值 */
    timer_initpara.repetitioncounter    = 0;                                      /* 重复计数器周期数 */
    timer_init(TIMER1, &timer_initpara);                                          /* 基础配置写入 */

    /* CH0输入配置,与CH1绑定会自动配置 */
    timer_icintpara.icpolarity          = TIMER_IC_POLARITY_RISING;               /* 输入通道极性 */
    timer_icintpara.icselection         = TIMER_IC_SELECTION_DIRECTTI;            /* 输入通道模式选择 */
    timer_icintpara.icprescaler         = TIMER_IC_PSC_DIV1;                      /* 输入通道分频系数 */
    timer_icintpara.icfilter            = 10;                                     /* 输入通道滤波系数 */             
    timer_input_pwm_capture_config(TIMER1, TIMER_CH_0, &timer_icintpara);         /* PWM捕获模式 */
		
		timer_input_trigger_source_select(TIMER1, TIMER_SMCFG_TRGSEL_CI0FE0);         /* 触发中断源选择 TIMER_SMCFG_TRGSEL_CI0FE0 */
	  timer_slave_mode_select(TIMER1, TIMER_SLAVE_MODE_RESTART);			              /*  配置定时器为复位模式 */
	  timer_master_slave_mode_config(TIMER1, TIMER_MASTER_SLAVE_MODE_ENABLE);       /*  复位模式. 选中的触发输入的上升沿重新初始化计数器，并且产生更新事件 */
	  timer_auto_reload_shadow_enable(TIMER1);

    timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_CH0);                       /* 清除通道0更新中断标志位 */
    nvic_irq_enable(TIMER1_IRQn, 1, 0);                                           /* 设置优先级组 */
    timer_interrupt_enable(TIMER1, TIMER_INT_CH0);                                /* 使能中断 */
    
    timer_enable(TIMER1);                                                         /* 使能定时器 */
}

/***********************************************************************************************
Function:   TimerConfig
Brief:      TIMER配置接口（外部）
Input:
Output:
Return:
Others:     
***********************************************************************************************/
void TimerConfig(void)
{
	  Timer0_Config();
	  Timer1_Config();
}


