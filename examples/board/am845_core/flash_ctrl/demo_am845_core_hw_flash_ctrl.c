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
 * \brief ������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������Ὣǩ����Ϣͨ�����ڴ�ӡ���ն��ϣ�
 *   2. ��ʾ��Ϊ�����֣��ֱ�Ϊ��������Ľ����Ӳ������Ľ����
 *   3. ������������Ӳ��������Ӧ����ͬ��
 *   4. LED �� 0.5s ��ʱ������˸��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_14 �������� PC ���ڵ� TXD��
 *       PIO0_23 �������� PC ���ڵ� RXD��
 *
 * \note
 *   �ɷ��ʵĵ�ַ��ΧΪ FLASH �ռ�(0x0000~0x8000)��
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_flash_ctrl.c src_am845_core_hw_flash_ctrl
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-04  sky, modified
 * - 1.00 15-07-16  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_flash_ctrl
 * \copydoc demo_am845_core_hw_flash_ctrl.c
 */

/** [src_am845_core_hw_flash_ctrl] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc_fmc.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_flash_ctrl_entry (void)
{
    AM_DBG_INFO("demo_am845_hw_flash_ctrl!\r\n");

    /* �����������ʱ��Ϊ����ϵͳʱ�� */
    demo_lpc845_hw_flash_ctrl_entry(AMHW_LPC_FMC_FLASHTIM_2);
}
/** [src_am845_core_hw_flash_ctrl] */

/* end of file */