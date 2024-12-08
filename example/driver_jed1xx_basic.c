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
 * @file      driver_jed1xx_basic.c
 * @brief     driver jed1xx basic source file
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

#include "driver_jed1xx_basic.h"

static jed1xx_handle_t gs_handle;        /**< jed1xx handle */

/**
 * @brief     basic example init
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t jed1xx_basic_init(jed1xx_type_t type)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_JED1XX_LINK_INIT(&gs_handle, jed1xx_handle_t);
    DRIVER_JED1XX_LINK_IIC_INIT(&gs_handle, jed1xx_interface_iic_init);
    DRIVER_JED1XX_LINK_IIC_DEINIT(&gs_handle, jed1xx_interface_iic_deinit);
    DRIVER_JED1XX_LINK_IIC_READ(&gs_handle, jed1xx_interface_iic_read);
    DRIVER_JED1XX_LINK_IIC_WRITE(&gs_handle, jed1xx_interface_iic_write);
    DRIVER_JED1XX_LINK_DELAY_MS(&gs_handle, jed1xx_interface_delay_ms);
    DRIVER_JED1XX_LINK_DEBUG_PRINT(&gs_handle, jed1xx_interface_debug_print);
    
    /* set type */
    res = jed1xx_set_type(&gs_handle, type);
    if (res != 0)
    {
        jed1xx_interface_debug_print("jed1xx: set type failed.\n");
       
        return 1;
    }
    
    /* jed1xx init */
    res = jed1xx_init(&gs_handle);
    if (res != 0)
    {
        jed1xx_interface_debug_print("jed1xx: init failed.\n");
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *ppm pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t jed1xx_basic_read(float *ppm)
{
    uint16_t raw;
    
    /* read */
    if (jed1xx_read(&gs_handle, &raw, ppm) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t jed1xx_basic_deinit(void)
{
    /* deinit jed1xx and close bus */
    if (jed1xx_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
