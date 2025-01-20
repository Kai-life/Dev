/***********************************************************************************************
Copyright (c) Shenzhen Zhaowei Machinery & Electronics Co., Ltd. 2020-2030. All rights reserved.
************************************************************************************************
Filename:   task.h
Brief:      head file for task.c
Author:     songguoyun
Date:       2020.03.19
Others:
History:
1   Date:
    Author: 
    Modification:
2   Date:
    Author:
    Modification:
***********************************************************************************************/

#ifndef _TASK_H_
#define _TASK_H_

#include "gd32f1x0.h"
#include "t_type.h"

#define MAX_TASK_CNT    10          /* 最大任务数 */

typedef void (*TaskFun)(void);      /* 任务处理函数声明 */

typedef struct
{
    U8 task_id;                 /* 任务ID */
    BOOL run_flag;              /* 任务是否调用：1调用，0不调用 */
    U16 counter;                /* 计数器 */
    U16 interval;               /* 任务多少时间调用一次 */
    TaskFun p_task_func;        /* 要运行的任务函数 */
} TaskInfoStruct;

extern void TaskInit(void);
extern S8 AddTask(TaskFun p_task_func, U16 cnt);
extern void TaskDeal(void);
extern void UpdateTaskState(void);

#endif
