#include "flash.h"

SLAVE_CONFIG Slave;

/* 读取指定地址的半字(16位数据) */
/* faddr:读地址(此地址必须为2的倍数!!) */
/*************************数据存储数组******GD32F150K8页大小1k*************************************/



void FlashWriteWords(uint32_t addr, uint32_t *pdata, uint16_t n) {
    uint16_t i;
    
    // 1. 解锁Flash编程和擦除控制器
    fmc_unlock();

    // 2. 擦除指定页
    // 地址必须是页对齐的
    uint32_t page_addr = addr & ~(FLASH_PAGE_SIZE - 1); // 对齐到页边界
    fmc_page_erase(page_addr);

    // 等待擦除完成
    while (fmc_flag_get(FMC_FLAG_END) == RESET);

    // 清除标志位
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

    // 3. 写入数据
    for (i = 0; i < n; i++) {
        // 写入数据
        fmc_word_program(addr + 4 * i, pdata[i]);

        // 等待写入完成
        while (fmc_flag_get(FMC_FLAG_END) == RESET);

        // 检查写入是否成功
        if (fmc_flag_get(FMC_FLAG_PGERR) != RESET) {
            // 写入错误处理，可以添加错误代码或退出
            break;
        }
    }

    // 4. 锁定Flash编程和擦除控制器
    fmc_lock();
}

void FlashReadWords(uint32_t addr, uint32_t *pdata, uint16_t n)        /* 从指定地址页连续读出n个数据 */
{
    uint16_t i;

    for (i = 0; i < n; i++)
    {
        *pdata = *(uint32_t*)(addr + 4 * i);         /* 从指定页的addr地址开始读 */
        pdata++;
    }
}

void ConfigMemory(void)
{
	  uint32_t flashReadData[5];
	
	  FlashReadWords(COFIG_SAVE_ADDR, flashReadData, 5);
	
	  if(flashReadData[0] == 0x5AA5)
		{
		    Slave.slaveAddr  = flashReadData[1];
			  Slave.slaveAddrLast = Slave.slaveAddr;
				Slave.baudrate   = flashReadData[2];
				Slave.dataFormat = flashReadData[3];
				Slave.delayTime  = flashReadData[4];
			  Slave.lockFlag   = 0;
			  Slave.version    = RECOVERY_VISION;
		}
		else
		{
		    Slave.slaveAddr  = RECOVERY_SLAVE_ADDR;
			  Slave.slaveAddrLast = RECOVERY_SLAVE_ADDR;
				Slave.baudrate   = RECOVERY_BAUDRATE;
				Slave.dataFormat = RECOVERY_DATA_FORMAT;
				Slave.delayTime  = RECOVERY_DELAY_TIME;
			  Slave.lockFlag   = 0;
			  Slave.version    = RECOVERY_VISION;
		}	
}

void ConfigWrite(void)
{
	  uint32_t writeData[5];
	  
    writeData[0] = 0x5AA5;/* 表示与出厂设置有所变动 */
		writeData[1] = Slave.slaveAddr;
	  writeData[2] = Slave.baudrate;
	  writeData[3] = Slave.dataFormat;
	  writeData[4] = Slave.delayTime;
		FlashWriteWords(COFIG_SAVE_ADDR, writeData, 5);
}

void ConfigRecovery(void)
{
    uint32_t writeData[5];
	  
    writeData[0] = 0x0000;/* 恢复出厂设置 */
		writeData[1] = RECOVERY_SLAVE_ADDR;
	  writeData[2] = RECOVERY_BAUDRATE;
	  writeData[3] = RECOVERY_DATA_FORMAT;
	  writeData[4] = RECOVERY_DELAY_TIME;
		FlashWriteWords(COFIG_SAVE_ADDR, writeData, 5);
}
