/**
  ******************************************************************************
  * @文件名     ： app.h
  * @作者       ： strongerHuang
  * @版本       ： V1.0.0
  * @日期       ： 2018年11月14日
  * @摘要       ： 应用程序头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _APP_H
#define _APP_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"


/* 宏定义 --------------------------------------------------------------------*/
#define APP_STACK_SIZE            128                      //开始任务堆栈大小
#define APP_TASK_PRIORITY         1                        //开始任务优先级


/* 函数申明 ------------------------------------------------------------------*/
void AppTaskCreate(void);


#endif /* _APP_H */

/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
