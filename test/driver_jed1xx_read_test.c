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
 * @file      driver_jed1xx_read_test.c
 * @brief     driver jed1xx read test source file
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

#include "driver_jed1xx_read_test.h"

static jed1xx_handle_t gs_handle;        /**< jed1xx handle */

/**
 * @brief     read test
 * @param[in] type chip type
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 * @note      none
 */
uint8_t jed1xx_read_test(jed1xx_type_t type, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    uint16_t raw;
    float ppm;
    jed1xx_info_t info;
   
    /* link interface function */
    DRIVER_JED1XX_LINK_INIT(&gs_handle, jed1xx_handle_t);
    DRIVER_JED1XX_LINK_IIC_INIT(&gs_handle, jed1xx_interface_iic_init);
    DRIVER_JED1XX_LINK_IIC_DEINIT(&gs_handle, jed1xx_interface_iic_deinit);
    DRIVER_JED1XX_LINK_IIC_READ(&gs_handle, jed1xx_interface_iic_read);
    DRIVER_JED1XX_LINK_IIC_WRITE(&gs_handle, jed1xx_interface_iic_write);
    DRIVER_JED1XX_LINK_DELAY_MS(&gs_handle, jed1xx_interface_delay_ms);
    DRIVER_JED1XX_LINK_DEBUG_PRINT(&gs_handle, jed1xx_interface_debug_print);

    /* get jed1xx information */
    res = jed1xx_info(&info);
    if (res != 0)
    {
        jed1xx_interface_debug_print("jed1xx: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print jed1xx information */
        jed1xx_interface_debug_print("jed1xx: chip is %s.\n", info.chip_name);
        jed1xx_interface_debug_print("jed1xx: manufacturer is %s.\n", info.manufacturer_name);
        jed1xx_interface_debug_print("jed1xx: interface is %s.\n", info.interface);
        jed1xx_interface_debug_print("jed1xx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        jed1xx_interface_debug_print("jed1xx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        jed1xx_interface_debug_print("jed1xx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        jed1xx_interface_debug_print("jed1xx: max current is %0.2fmA.\n", info.max_current_ma);
        jed1xx_interface_debug_print("jed1xx: max temperature is %0.1fC.\n", info.temperature_max);
        jed1xx_interface_debug_print("jed1xx: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start basic read test */
    jed1xx_interface_debug_print("jed1xx: start read test.\n");
    
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
    
    /* delay 3000 ms for read */
    jed1xx_interface_delay_ms(3000);
    for (i = 0; i < times; i++)
    {
        /* read data */
        res = jed1xx_read(&gs_handle, &raw, &ppm);
        if (res != 0)
        {
            jed1xx_interface_debug_print("jed1xx: read failed.\n");
            (void)jed1xx_deinit(&gs_handle);
           
            return 1;
        }
    
        /* print result */
        jed1xx_interface_debug_print("jed1xx: output raw is 0x%04X.\n", raw);
        jed1xx_interface_debug_print("jed1xx: output is %.01fppm.\n", ppm);

        /* delay 3000 ms*/
        jed1xx_interface_delay_ms(3000);
    }

    /* finish basic read test and exit */
    jed1xx_interface_debug_print("jed1xx: finish read test.\n");
    (void)jed1xx_deinit(&gs_handle);
    
    return 0;
}
