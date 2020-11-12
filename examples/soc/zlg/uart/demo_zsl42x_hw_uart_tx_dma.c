/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ�����ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ��ָ�����ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      uart tx dma test running
 *      uart tx dma test done
 *
 * \note
 *    1. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_zsl42x_hw_uart_tx_dma.c src_zsl42x_hw_uart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-23  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_hw_uart_tx_dma
 * \copydoc demo_zsl42x_hw_uart_tx_dma.c
 */

/** [src_zsl42x_hw_uart_tx_dma] */
#include "ametal.h"
#include "am_int.h"
#include "am_zsl42x_dma.h"
#include "hw/amhw_zsl42x_uart.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE      (115200)             /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief DMA ���������� */
static amhw_zsl42x_dma_xfer_desc_t g_desc;

/** \brief ������ɱ�־ */
static volatile am_bool_t g_trans_done = AM_FALSE;

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst[]  = "uart tx dma test running\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst1[] = "uart tx dma test done\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst2[] = "DMA tx transfer start:\r\n";

static int32_t             g_dma_chan = 0;    /**< \brief DMA ͨ���� */
static amhw_zsl42x_uart_t *gp_hw_uart = NULL; /**< \brief UART ���� */

/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_zsl42x_dma_isr_connect() �������ݡ�
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (# AM_zsl42x_DMA_INT_NORMAL) �� (# AM_zsl42x_DMA_INT_ERROR)
 *
 * \return �ޡ�
 */
static void uart_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_ZSL42x_DMA_INT_COMPLETE) {
        if (flag_chan == g_dma_chan) {

            /* ����UART����ʱʹ��DMA���� */
            amhw_zsl42x_uart_disable(gp_hw_uart, AMHW_ZSL42x_UART_DMA_TX);
            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }

}

/**
 * \brief DMA�������á�
 */
static int uart_tx_dma_tran_cfg (amhw_zsl42x_uart_t *p_hw_uart,
                                 int32_t             dma_chan,
                                 const uint8_t      *p_txbuf,
                                 uint32_t            dma_tran_len)
{
    uint32_t flags;

    /* ����DMA�жϷ����� */
    am_zsl42x_dma_isr_connect(dma_chan, uart_dma_isr, (void *)dma_chan);

    /* DMA �������� */
       flags = AMHW_ZSL42x_DMA_CHAN_TRANSFER_MODE_BLOCK    | /* SPIֻ�п鴫��ģʽ */
               AMHW_ZSL42x_DMA_CHAN_SIZE_8BIT              | /* ����λ�� 8bit */

               AMHW_ZSL42x_DMA_CHAN_SRC_ADD_INC_ENABLE     | /* Դ��ַ���� */
               AMHW_ZSL42x_DMA_CHAN_RELOAD_SRC_ADD_DISABLE | /* Դ��ַ������*/

               AMHW_ZSL42x_DMA_CHAN_DST_ADD_INC_DISABLE    | /* Ŀ���ַ������ */
               AMHW_ZSL42x_DMA_CHAN_RELOAD_DST_ADD_ENABLE  | /* Ŀ���ַ���� */

               AMHW_ZSL42x_DMA_CHAN_RELOAD_COUNTER_ENABLE  | /* �������������� */
               AMHW_ZSL42x_DMA_CHAN_INT_ERR_DISABLE        | /* ��������жϽ��� */
               AMHW_ZSL42x_DMA_CHAN_INT_TX_CMP_ENABLE      | /* ��������ж�ʹ�� */
               AMHW_ZSL42x_DMA_CHAN_CIRCULAR_MODE_DISABLE ;  /* �ر�ѭ��ģʽ */

    /* ����ͨ�������� */
    am_zsl42x_dma_xfer_desc_build(&g_desc,                       /* ͨ�������� */
                                  (uint32_t)(p_txbuf),           /* Դ�����ݻ����� */
                                  (uint32_t)(&(p_hw_uart->sbuf)),/* Ŀ������ݻ����� */
                                  dma_tran_len,                  /* �����ֽ��� */
                                  flags);                        /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_zsl42x_dma_xfer_desc_chan_cfg(&g_desc,
                                         AMHW_ZSL42x_DMA_PER_TO_MER,/* �ڴ浽���� */
                                         dma_chan) == AM_ERROR) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief UART��ʼ��
 */
static void uart_hw_init (amhw_zsl42x_uart_t *p_hw_uart, uint32_t clk_rate)
{
    /* ����ģʽ����  */
    amhw_zsl42x_uart_mode_sel(p_hw_uart, AMHW_ZSL42x_UART_WORK_MODE_1);

    /* ��Ƶϵ������  */
    amhw_zsl42x_uart_clk_div_sel(p_hw_uart, AMHW_ZSL42x_UART_CLK_DIV_MODE13_8);

    /* �ȴ����Ϳ���� */
    while (amhw_zsl42x_uart_flag_check(p_hw_uart,
                                       AMHW_ZSL42x_UART_FLAG_TX_EMPTY) ==
                                       AM_FALSE);

    /* ֹͣλ���� */
    amhw_zsl42x_uart_stop_bit_sel(p_hw_uart  , AMHW_ZSL42x_UART_STOP_1_0_BIT);

    /* У������ */
    amhw_zsl42x_uart_parity_bit_sel(p_hw_uart, AMHW_ZSL42x_UART_PARITY_NO);

    /* ���������� */
    amhw_zsl42x_uart_baudrate_set( p_hw_uart, clk_rate, UART_BAUDRATE);

    /* �ر����д����ж� */
    amhw_zsl42x_uart_int_disable(p_hw_uart, AMHW_ZSL42x_UART_INT_ALL);
}


/**
 * \brief UART����DMA�����ʼ��
 */
static void uart_hw_dma_init (amhw_zsl42x_uart_t *p_hw_uart)
{
    /* ���ڷ���DMA����ʹ�� */
    amhw_zsl42x_uart_enable(p_hw_uart, AMHW_ZSL42x_UART_DMA_TX);

    /* ����ʹ��
     * Mode0:     0������; 1������
     * Mode1/2/3: 0������; 1�� ����/����
     */
    amhw_zsl42x_uart_enable(p_hw_uart,AMHW_ZSL42x_UART_RX);
}

/**
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_zsl42x_hw_uart_tx_dma_entry (void    *p_hw_uart,
                                     uint32_t clk_rate,
                                     int32_t  dma_chan,
                                     int32_t  dma_src)
{
    uint8_t i = 0;
    uint8_t j = 0;

    gp_hw_uart = (amhw_zsl42x_uart_t *)p_hw_uart;
    g_dma_chan = dma_chan;

    /* UART��ʼ�� */
    uart_hw_init(gp_hw_uart, clk_rate);

    /* UART��DMA����ĳ�ʼ�� */
    uart_hw_dma_init(gp_hw_uart);

    uart_tx_dma_tran_cfg(gp_hw_uart,
                         dma_chan,
                         g_buf_dst2,
                         sizeof(g_buf_dst2) - 1);

    /* Ĭ��ͨ��0��ͨ��1���ȼ�һ������ѯ��*/
    am_zsl42x_dma_priority_same();

    /* ���ô��������ź���Դ */
    am_zsl42x_dma_chan_src_set (dma_chan, dma_src);

    /* ����ÿ��DMA������СΪ�ѿ�����ͨ��������1�� */
    am_zsl42x_dma_block_data_size(dma_chan, 1);

    /* ��ʼͨ������ */
    am_zsl42x_dma_chan_start(dma_chan);

    while (1) {

        if (g_trans_done == AM_TRUE) {

            j++;
            g_trans_done = AM_FALSE;

            /* ���ڷ���DMA����ʹ�� */
            amhw_zsl42x_uart_enable(p_hw_uart, AMHW_ZSL42x_UART_DMA_TX);

            if (j < 3) {
                am_zsl42x_dma_chan_stop(dma_chan);
                if (0 == i) {
                    uart_tx_dma_tran_cfg(gp_hw_uart,
                                         dma_chan,
                                         g_buf_dst,
                                         sizeof(g_buf_dst) - 1);
                } else {
                    uart_tx_dma_tran_cfg(gp_hw_uart,
                                         dma_chan,
                                         g_buf_dst1,
                                         sizeof(g_buf_dst1) - 1);
                }
                i++;
                am_zsl42x_dma_chan_start(dma_chan);
            }

        }
    }
}
/** [src_zsl42x116_hw_uart_tx_dma] */

/* end of file */