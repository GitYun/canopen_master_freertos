/**
  ******************************************************************************
  * @�ļ���     �� bsp_usart.c
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� USART�ײ�����Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2018-11-14 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp_usart.h"

#include "FreeRTOS.h"
#include "task.h"

#include <string.h>
#include <stdarg.h>

/***************************************** DEBUG���Դ��� *****************************************/
/************************************************
�������� �� UART_DEBUG_Configuration
��    �� �� ���Դ�������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void UART_DEBUG_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;

  /* ʱ������ */
  RCC_APB2PeriphClockCmd(DEBUG_COM_TX_GPIO_CLK | DEBUG_COM_RX_GPIO_CLK , ENABLE);

  if(USART1 == DEBUG_COM)
    RCC_APB2PeriphClockCmd(DEBUG_COM_CLK, ENABLE);
  else
    RCC_APB1PeriphClockCmd(DEBUG_COM_CLK, ENABLE);

  /* �������� */
  GPIO_InitStructure.GPIO_Pin = DEBUG_COM_TX_PIN;                    //UART Tx
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(DEBUG_COM_TX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = DEBUG_COM_RX_PIN;                    //UART Rx
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(DEBUG_COM_RX_GPIO_PORT, &GPIO_InitStructure);

  /* NVIC���� */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = DEBUG_COM_Priority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* UART���� */
  USART_InitStructure.USART_BaudRate = DEBUG_COM_BaudRate;           //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //����λ��
  USART_InitStructure.USART_StopBits = USART_StopBits_1;             //ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No ;               //У��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //�շ�����
  USART_Init(DEBUG_COM, &USART_InitStructure);

  USART_ClearFlag(DEBUG_COM, USART_FLAG_RXNE | USART_FLAG_TC);

#if  USE_UART_SCANF_WITH_INTERRUPT
  USART_ITConfig(DEBUG_COM, USART_IT_RXNE, ENABLE);                  //�����ж�
#endif

  USART_Cmd(DEBUG_COM, ENABLE);                                      //ʹ��UART
}

/************************************************
�������� �� DEBUG_SendByte
��    �� �� ���Դ��ڷ���һ���ֽ�
��    �� �� Data --- ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void DEBUG_SendByte(uint8_t Data)
{
  /* �ȴ�����Ϊ�� */
  while(RESET == USART_GetFlagStatus(DEBUG_COM, USART_FLAG_TXE));

  USART_SendData(DEBUG_COM, Data);
}

/************************************************
�������� �� DEBUG_SendNByte
��    �� �� ���Դ��ڷ���N���ֽ�
��    �� �� pData ---- ����
            Length --- ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void DEBUG_SendNByte(uint8_t *pData, uint16_t Length)
{
  while(Length--)
  {
    DEBUG_SendByte(*pData);

    if (*pData == '\n')
    {
        DEBUG_SendByte('\r');
    }

    pData++;
  }
}

#if USE_UART_SCANF_WITH_INTERRUPT

static char g_recv_buffer[1024] = {0};
static int g_read_idx = 0;
static int g_write_idx = 0;
static char g_oneline_flag = 0;

void push_recv_data(int ch)
{
    if (g_oneline_flag == 0)
    {
        if (ch == '\r' || ch == '\n')
        {
            g_oneline_flag = 1;
        }

        if (g_write_idx < 1024)
        {
            g_recv_buffer[g_write_idx++] = (uint8_t)ch;
            g_write_idx &= 0x3FF;
        }
    }
}

int uart_scanf(char* ptr, const char* fmt, ...)
{
    static char cli_buf[1024] = {0};
    char* cli = ptr ? ptr : cli_buf;
    int ret = 0;
    va_list vp;

    for (;;)
    {
        if (g_oneline_flag)
        {
            g_oneline_flag = 0;
            break;
        }
        else
        {
            vTaskDelay(10);
        }
    }

    int count = (g_write_idx - g_read_idx);

    if (count <= 0)
        count = 1024 + count;

    char ch = 0;
    for (int i = 0; i < count; ++i)
    {
        ch =  g_recv_buffer[(g_read_idx + i) & 0x3FF];
        cli[i] = ch;
    }

    g_read_idx = (g_read_idx + count) & 0x3FF;

    va_start(vp, fmt);
    ret = vsscanf(cli, fmt, vp);
    va_end(vp);

    return ret;
}
#endif

#if defined (__GNUC__)

int __io_putchar(int ch)
{
    DEBUG_SendByte((uint8_t)ch);

    return ch;
}

int __io_getchar(FILE *f)
{
    while(USART_GetFlagStatus(DEBUG_COM, USART_FLAG_RXNE) == RESET)
    {
        vTaskDelay(pdMS_TO_TICKS(10)); // 10ms convert to os tick
    }

    return USART_ReceiveData(DEBUG_COM);
}

#else

/************************************************
�������� �� fputc
��    �� �� �ض���putc����
��    �� �� ch --- �ַ�
            *f --- �ļ�ָ��
�� �� ֵ �� �ַ�
��    �� �� strongerHuang
*************************************************/
int fputc(int ch, FILE *f)
{
  DEBUG_SendByte((uint8_t)ch);

  return ch;
}

/************************************************
�������� �� fgetc
��    �� �� �ض���getc����
��    �� �� *f --- �ļ�ָ��
�� �� ֵ �� �ַ�
��    �� �� strongerHuang
*************************************************/
int fgetc(FILE *f)
{
  while(USART_GetFlagStatus(DEBUG_COM, USART_FLAG_RXNE) == RESET);

  return (int)USART_ReceiveData(DEBUG_COM);
}

#endif // defined (__GNUC__)

/************************************************
�������� �� USART_Initializes
��    �� �� ���ڳ�ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART_Initializes(void)
{
  UART_DEBUG_Configuration();
}


/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
