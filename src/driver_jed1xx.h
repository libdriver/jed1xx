/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_jed1xx.h
 * @brief     driver jed1xx header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-10-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/10/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_JED1XX_H
#define DRIVER_JED1XX_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup jed1xx_driver jed1xx driver function
 * @brief    jed1xx driver modules
 * @{
 */

/**
 * @addtogroup jed1xx_base_driver
 * @{
 */

/**
 * @brief jed1xx type enumeration definition
 */
typedef enum
{
    JED1XX_TYPE_101_VOC      = 100,          /**< jed101 voc  */
    JED1XX_TYPE_103_H2       = 5000,         /**< jed103 h2 */
    JED1XX_TYPE_104_C0       = 500,          /**< jed104 co */
    JED1XX_TYPE_105_NH3      = 300,          /**< jed105 nh3 */
    JED1XX_TYPE_106_H2S      = 3,            /**< jed106 h2s */
    JED1XX_TYPE_107_C2H5OH   = 500,          /**< jed107 c2h50h */
    JED1XX_TYPE_109_C3H8     = 10000,        /**< jed109 c3h8 */
    JED1XX_TYPE_110_CF2CL2   = 1000,         /**< jed110 cf2cl2 */
    JED1XX_TYPE_112_NO2      = 10,           /**< jed112 no2 */
    JED1XX_TYPE_115_SMOG     = 10000,        /**< jed115 smog */
    JED1XX_TYPE_116_CH2O     = 100,          /**< jed116 ch2o */
    JED1XX_TYPE_117_CH3COCH3 = 500,          /**< jed117 ch3coch3 */
    JED1XX_TYPE_131_O3       = 100,          /**< jed131 o3 */
    JED1XX_TYPE_138_C6H6     = 100,          /**< jed138 c6h6 */
} jed1xx_type_t;

/**
 * @brief jed1xx handle structure definition
 */
typedef struct jed1xx_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint32_t type;                                                                      /**< type */
} jed1xx_handle_t;

/**
 * @brief jed1xx information structure definition
 */
typedef struct jed1xx_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} jed1xx_info_t;

/**
 * @}
 */

/**
 * @defgroup jed1xx_link_driver jed1xx link driver function
 * @brief    jed1xx link driver modules
 * @ingroup  jed1xx_driver
 * @{
 */

/**
 * @brief     initialize jed1xx_handle_t structure
 * @param[in] HANDLE points to a jed1xx handle structure
 * @param[in] STRUCTURE is jed1xx_handle_t
 * @note      none
 */
#define DRIVER_JED1XX_LINK_INIT(HANDLE, STRUCTURE)      memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a jed1xx handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_JED1XX_LINK_IIC_INIT(HANDLE, FUC)        (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a jed1xx handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_JED1XX_LINK_IIC_DEINIT(HANDLE, FUC)      (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to a jed1xx handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_JED1XX_LINK_IIC_READ(HANDLE, FUC)        (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to a jed1xx handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_JED1XX_LINK_IIC_WRITE(HANDLE, FUC)       (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a jed1xx handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_JED1XX_LINK_DELAY_MS(HANDLE, FUC)        (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a jed1xx handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_JED1XX_LINK_DEBUG_PRINT(HANDLE, FUC)     (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup jed1xx_base_driver jed1xx base driver function
 * @brief    jed1xx base driver modules
 * @ingroup  jed1xx_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a jed1xx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t jed1xx_info(jed1xx_info_t *info);

/**
 * @brief     set the chip type
 * @param[in] *handle points to a jed1xx handle structure
 * @param[in] type is the chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t jed1xx_set_type(jed1xx_handle_t *handle, jed1xx_type_t type);

/**
 * @brief      get the chip type
 * @param[in]  *handle points to a jed1xx handle structure
 * @param[out] *type points to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t jed1xx_get_type(jed1xx_handle_t *handle, jed1xx_type_t *type);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a jed1xx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t jed1xx_init(jed1xx_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a jed1xx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t jed1xx_deinit(jed1xx_handle_t *handle);

/**
 * @brief      read data
 * @param[in]  *handle points to a jed1xx handle structure
 * @param[out] *raw points to a raw data buffer
 * @param[out] *ppm points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t jed1xx_read(jed1xx_handle_t *handle, uint16_t *raw, float *ppm);

/**
 * @}
 */

/**
 * @defgroup jed1xx_extend_driver jed1xx extend driver function
 * @brief    jed1xx extend driver modules
 * @ingroup  jed1xx_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a jed1xx handle structure
 * @param[in] reg is the register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t jed1xx_set_reg(jed1xx_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a jed1xx handle structure
 * @param[in]  reg is the register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t jed1xx_get_reg(jed1xx_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
