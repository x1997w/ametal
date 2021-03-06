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
 * \brief GPIO 例程，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. 将 J14 的 KEY 和 PIOC_7 短接在一起。
 *
 * - 实验现象：
 *   1. 按一次按键 LED0 灯熄灭，再按一次按键 LED0 灯亮，如此反复。
 *
 * \note
 *    LED0 需要短接 J9 跳线帽，才能被 PIOC_7 控制。
 *
 * \par 源代码
 * \snippet demo_hk32f103rbt6_hw_gpio.c src_hk32f103rbt6_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-24 zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hk32f103rbt6_hw_gpio
 * \copydoc demo_hk32f103rbt6_hw_gpio.c
 */

/** [src_hk32f103rbt6_hw_gpio] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_hk32f103rbt6.h"
#include "am_vdebug.h"
#include "amhw_hk32f103rbt6_gpio.h"
#include "demo_hk32f103rbt6_entries.h"
#include "demo_hk32f103rbt6_core_entries.h"

#define INPUT_PIN  PIOC_7 /**< \brief 输入引脚 */
#define OUTPUT_PIN PIOC_9 /**< \brief 输出引脚 */

/**
 * \brief 例程入口
 */
void demo_hk32f103rbt6_core_hw_gpio_entry (void)
{

    AM_DBG_INFO("demo hk32f103rbt6_core hw gpio!\r\n");

    /* 开启 GPIOC 端口时钟 */
    am_clk_enable(CLK_IOPC);

    /* 开启系统配置的时钟 */
    am_clk_enable(CLK_AFIO);

    demo_hk32f103rbt6_hw_gpio_entry((amhw_hk32f103rbt6_gpio_t*)HK32F103RBT6_GPIO, INPUT_PIN, OUTPUT_PIN);
}
/** [src_hk32f103rbt6_hw_gpio] */

/* end of file */
