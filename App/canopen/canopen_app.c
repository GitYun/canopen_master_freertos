/**
  ******************************************************************************
  * @�ļ���     �� canopen_app.c
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� CANOpenӦ�ó���Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2018-11-14 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "canopen_app.h"
#include "canopen_drv.h"
#include "TestMaster.h"
#include "bsp_usart.h"

#include <stdlib.h>

#define HELP_STRING                                                     \
    "Usage:\n"                                                          \
        "\tStep1: <command> <space> <arg number> <Enter>\n"             \
        "\tStep2: <1 data for pdo> or <(1~10) data for sdo> <Enter>\n"  \
    "command:\n"                                                        \
        "\t1: update pdo data;\n"                                       \
        "\t2: update sdo data.\n"                                       \
    "arguments number:\n"                                               \
        "\tpdo always is 1;\n"                                          \
        "\tsdo range is 1 to 10.\n"

/* ��̬���� ------------------------------------------------------------------*/
static void CANOpen_App_Task(void *pvParameters);

static UNS32 rpdo1_data_handler(CO_Data *d, const indextable *table, uint8_t b_subindex);
static UNS32 rsdo_param_handler(CO_Data *d, const indextable *table, uint8_t b_subindex);

/************************************************
�������� �� CANOpen_App_Init
��    �� �� CANOpenӦ�ó����ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void CANOpen_App_Init(void)
{
  BaseType_t xReturn;

  uint32_t error = RegisterSetODentryCallBack(&TestMaster_Data, 0x2000, 0, rpdo1_data_handler);

  for (uint8_t i = 0; i < 10; ++i)
  {
      error |= RegisterSetODentryCallBack(&TestMaster_Data, 0x2002, i, rsdo_param_handler);
  }

  if (error != 0)
  {
      for (;;)
      {
          printf("CANOpen Error!\n");
          vTaskDelay(1000);
      }
  }

  CANOpen_Driver_Init();

  xReturn = xTaskCreate(CANOpen_App_Task, "CANOpen_App_Task", CANOPEN_STACK_SIZE, NULL, CANOPEN_TASK_PRIORITY, NULL);
  if(pdPASS != xReturn)
  {
    return;                                      //������������ʧ��
  }
}

/************************************************
�������� �� CANOpen_App_Task
��    �� �� CANOpenӦ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
static void CANOpen_App_Task(void *pvParameters)
{
  int cmd = 0;
  int cmd_num = 0;

  unsigned char nodeID = 0x01;                   //�ڵ�ID

  setNodeId(&TestMaster_Data, nodeID);
  setState(&TestMaster_Data, Initialisation);
  setState(&TestMaster_Data, Operational);

  printf("welcom to canopen!\n");
  printf(HELP_STRING);

  for(;;)
  {
    vTaskDelay(500);

    /* Ӧ�ô��� */
    int ret = scanf("%d%d", &cmd, &cmd_num);

    if (ret == 2)
    {
        if (cmd == 1 && cmd_num == 1) // send pdo
        {
            scanf("%lu", &pdo_m2s_tx_data);

            sendOnePDOevent(&TestMaster_Data, 0);
        }

        if (cmd == 2 && cmd_num > 0)
        {
            for (int i = 0; i < cmd_num; ++i)
            {
                scanf("%lu", &sdo_m2s_tx_array[i]);
                writeNetworkDict(&TestMaster_Data, nodeID, 0x2002, i + 1, 4, uint8, &sdo_m2s_tx_array[i], 0);
            }
        }
    }
    else
    {
        printf(HELP_STRING);
    }
  }
}

static UNS32 rpdo1_data_handler(CO_Data *d, const indextable *table, uint8_t b_subindex)
{
    uint32_t value = *(uint32_t *)table->pSubindex[b_subindex].pObject;

    switch (table->index)
    {
    /* rpdo1 */
    case 0x2000:
        printf("0x2000: %ld\n", value);
        break;

    default:
        break;
    }

    return OD_SUCCESSFUL;
}

static UNS32 rsdo_param_handler(CO_Data *d, const indextable *table, uint8_t b_subindex)
{
    uint32_t value = *(uint32_t *)table->pSubindex[b_subindex].pObject;

    printf("0x%04x: %ld\n", 0x2022 + b_subindex, value);

    return OD_SUCCESSFUL;
}

/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
