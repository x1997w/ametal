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
 * \brief FLASH 例程，通过驱动层接口实现
 *
 * - 实验现象：
 *   1. 擦除出错：串口打印"erase error!"；
 *   2. 写入出错：串口打印"program error!"；
 *   3. 写入成功：串口打印 480扇区的(512)个 32bit 十六进制数据。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_10 引脚连接 PC 串口的 TXD，
 *    PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_zsl42x_drv_flash.c src_zsl42x_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-20  zp, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsl42x_drv_flash
 * \copydoc demo_zsl42x_drv_flash.c
 */

/** [src_zsl42x_drv_flash] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_zsl42x_flash.h"
#include "am_zsl42x.h"
#include "demo_zsl42x_entries.h"
#include "demo_am42x_core_entries.h"

#define FLASH_SECTOR    500

/**
 * \brief 例程入口
 */
void demo_zsl42x_core_drv_flash_entry (void)
{
    AM_DBG_INFO("demo am42x_core drv flash!\r\n");

    demo_zsl42x_drv_flash_entry(ZSL42x_FLASH, FLASH_SECTOR);
}

/** [src_zsl42x_drv_flash] */

/* end of file */
