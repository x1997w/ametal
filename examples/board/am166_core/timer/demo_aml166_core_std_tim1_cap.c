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
 * \brief TIM1 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ��� PIOA_0 �� PIOA_11 ���ӡ�
 *
 * - ʵ������
 *   1. TIM2 ͨ�� PIOA_0 ������� 2KHz �� PWM��
 *   2. TIM1 ��������ͨ�� 4 ʹ�� PIOA_11 ���Ų���
 *   3. ���ڴ�ӡ�����ò����ܵõ��� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_aml166_core_std_tim1_cap.c src_aml166_core_std_tim1_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-04-22  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml166_core_std_tim1_cap
 * \copydoc demo_aml166_core_std_tim1_cap.c
 */

/** [src_aml166_core_std_tim1_cap] */
#include <am_aml166_inst_init.h>
#include "ametal.h"
#include "am_pwm.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief �������
 */
void demo_aml166_core_std_tim1_cap_entry (void)
{
    am_pwm_handle_t pwm_handle = am_zlg116_tim2_pwm_inst_init();

    AM_DBG_INFO("demo aml166_core std tim1 cap!\r\n");

    /* TIM2 ���Ƶ��Ϊ 2KHz �� PWM */
    am_pwm_config(pwm_handle, 0, 500000 / 2, 500000);
    am_pwm_enable(pwm_handle, 0);

    demo_std_timer_cap_entry(am_zlg116_tim1_cap_inst_init(), 3);
}
/** [src_aml166_core_std_tim1_cap] */

/* end of file */