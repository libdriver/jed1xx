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
 * @file      driver_jed1xx.c
 * @brief     driver jed1xx source file
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

#include "driver_jed1xx.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "JXCT JED1XX"       /**< chip name */
#define MANUFACTURER_NAME         "JXCT"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.3f                /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.0f                /**< chip max supply voltage */
#define MAX_CURRENT               25.0f               /**< chip max current */
#define TEMPERATURE_MIN           -40.0f              /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f               /**< chip max operating temperature */
#define DRIVER_VERSION            1000                /**< driver version */

/**
 * @brief chip address definition
 */
#define JED1XX_ADDRESS             0x54        /**< iic device address */

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to a jed1xx handle structure
 * @param[in]  reg register address
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_jed1xx_iic_read(jed1xx_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_read(JED1XX_ADDRESS, reg, data, len) != 0)      /* read the register */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to a jed1xx handle structure
 * @param[in] reg register address
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_jed1xx_iic_write(jed1xx_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_write(JED1XX_ADDRESS, reg, data, len) != 0)      /* write the register */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     set the chip type
 * @param[in] *handle pointer to a jed1xx handle structure
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t jed1xx_set_type(jed1xx_handle_t *handle, jed1xx_type_t type)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }

    handle->type = (uint32_t)(type);        /* set type */
    
    return 0;                               /* success return 0 */
}

/**
 * @brief      get the chip type
 * @param[in]  *handle pointer to a jed1xx handle structure
 * @param[out] *type pointer to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t jed1xx_get_type(jed1xx_handle_t *handle, jed1xx_type_t *type)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }

    *type = (jed1xx_type_t)(handle->type);        /* get type */
    
    return 0;                                     /* success return 0 */
}

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a jed1xx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t jed1xx_init(jed1xx_handle_t *handle)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->debug_print == NULL)                                   /* check debug_print */
    {
        return 3;                                                      /* return error */
    }
    if (handle->iic_init == NULL)                                      /* check iic_init */
    {
        handle->debug_print("jed1xx: iic_init is null.\n");            /* iic_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_deinit == NULL)                                    /* check iic_deinit */
    {
        handle->debug_print("jed1xx: iic_deinit is null.\n");          /* iic_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_read == NULL)                                      /* check iic_read */
    {
        handle->debug_print("jed1xx: iic_read is null.\n");            /* iic_read is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->iic_write == NULL)                                     /* check iic_write */
    {
        handle->debug_print("jed1xx: iic_write is null.\n");           /* iic_write is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->delay_ms == NULL)                                      /* check delay_ms */
    {
        handle->debug_print("jed1xx: delay_ms is null.\n");            /* delay_ms is null */
        
        return 3;                                                      /* return error */
    }
    
    if (handle->iic_init() != 0)                                       /* iic init */
    {
        handle->debug_print("jed1xx: iic init failed.\n");             /* iic init failed */
        
        return 1;                                                      /* return error */
    }
    handle->inited = 1;                                                /* flag finish initialization */
    
    return 0;                                                          /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a jed1xx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t jed1xx_deinit(jed1xx_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    if (handle->iic_deinit() != 0)                                 /* iic deinit */
    {
        handle->debug_print("jed1xx: iic deinit failed.\n");       /* iic deinit failed */
        
        return 1;                                                  /* return error */
    }
    handle->inited = 0;                                            /* set closed flag */
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief      read data
 * @param[in]  *handle pointer to a jed1xx handle structure
 * @param[out] *raw pointer to a raw data buffer
 * @param[out] *ppm pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t jed1xx_read(jed1xx_handle_t *handle, uint16_t *raw, float *ppm)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    res = a_jed1xx_iic_read(handle, 0xA1, buf, 2);                 /* read data */
    if (res != 0)                                                  /* check the result */
    {
        handle->debug_print("jed1xx: read data failed.\n");        /* read data failed */
        
        return 1;                                                  /* return error */
    }
    *raw = (((uint16_t)buf[0]) << 8) | buf[1];                     /* get raw data */
    *ppm = (float)(*raw) / 10000.0f * (float)(handle->type);       /* convert ppm */
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a jed1xx handle structure
 * @param[in] reg register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t jed1xx_set_reg(jed1xx_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    } 
    
    if (a_jed1xx_iic_write(handle, reg, buf, len) != 0)        /* write data */
    {
        return 1;                                              /* return error */
    }
    
    return 0;                                                  /* success return 0 */

}

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a jed1xx handle structure
 * @param[in]  reg register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t jed1xx_get_reg(jed1xx_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                       /* check handle */
    {
        return 2;                                             /* return error */
    }
    if (handle->inited != 1)                                  /* check handle initialization */
    {
        return 3;                                             /* return error */
    } 
    
    if (a_jed1xx_iic_read(handle, reg, buf, len) != 0)        /* read data */
    {
        return 1;                                             /* return error */
    }
    
    return 0;                                                 /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a jed1xx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t jed1xx_info(jed1xx_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(jed1xx_info_t));                         /* initialize jed1xx info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
