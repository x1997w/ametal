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
 * \brief LPTIM1 定时器 TIMING 例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. LED0 以 5Hz 的频率翻转。(计数周期是10Hz，led翻转周期为10/2=5Hz)
 *
 * \note
 *   1.在am_hwconf_zsn700_lptim.c文件中，__g_lptim1_timing_devinfo设备信息结构体选择
 *             AMHW_ZSN700_LPTIM_FUNCTION_TIMER  ----------- 定时器模式
 *             AMHW_ZSN700_LPTIM_MODE_RELOAD     ----------- 自动重载模式
 *             AM_FALSE                          ----------- 门控关闭
 *             AM_TRUE                           ----------- TOG、TOGN输出使能打开
 *
 * \par 源代码
 * \snippet demo_zsn700_std_lptim1_timing.c src_zsn700_std_lptim1_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-29  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_std_lptim1_timing
 * \copydoc demo_zsn700_std_lptim1_timing.c
 */

/** [src_zsn700_std_lptim1_timing] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zsn700_inst_init.h"
#include "demo_am700_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_zsn700_core_std_lptim1_timing_entry (void)
{
    AM_DBG_INFO("demo am700_core std lptim1 timing!\r\n");

    demo_std_timer_timing_entry(am_zsn700_lptim1_timing_inst_init(), 0);
}
/** [src_zsn700_std_lptim1_timing] */

/* end of file */
