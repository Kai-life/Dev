#include "watchdog.h"



void WatchdogInit(void)
{
    /* 配置系统时钟 */
    rcu_periph_clock_enable(RCU_WWDGT);

    /*  初始化窗口看门狗 (Window Watchdog) */
    wwdgt_config(WDT_COUNTER_VAL, WDT_WINDOW_VAL, WDT_PRESCALER);
    wwdgt_enable();
}

