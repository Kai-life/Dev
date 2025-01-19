#ifndef FLASH_H
#define FLASH_H

#include "gd32f1x0.h"

#define FLASH_MAX_SIZE    (0x10000)   /* 0x8000000 - 0x8010000 芯片FLASH大小 */
#define COFIG_SAVE_ADDR   (0x800FC00) /* 0x800FC00 - 0x800FFFF 配置信息存储地址 */
#define FLASH_PAGE_SIZE    1024  // 根据芯片手册定义Flash页面大小

/* 出厂设定值 */
#define RECOVERY_SLAVE_ADDR    (0x0001)
#define RECOVERY_BAUDRATE      (0x0004)
#define RECOVERY_DATA_FORMAT   (0x0005)
#define RECOVERY_DELAY_TIME    (0x0000)
#define RECOVERY_VISION        (0x0814)
/* 修改值 */


typedef struct
{
    uint32_t slaveAddr;    /* 从机地址 */
	  uint32_t slaveAddrLast;
	  uint32_t baudrate;     /* 波特率 */
	  uint32_t dataFormat;   /* 数据帧格式 */
	  uint32_t delayTime;    /* 指令延时应答 */
	  uint32_t lockFlag;     /* 解锁标志位 */
	  uint32_t version;      /* 版本 */
}SLAVE_CONFIG;

extern SLAVE_CONFIG Slave;

void ConfigMemory(void);
void ConfigWrite(void);
void ConfigRecovery(void);

#endif
