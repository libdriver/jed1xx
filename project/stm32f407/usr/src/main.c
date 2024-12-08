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
 * @file      main.c
 * @brief     main source file
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
#include "driver_jed1xx_read_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     jed1xx full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t jed1xx(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {"type", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    jed1xx_type_t chip_type = JED1XX_TYPE_101_VOC;
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* chip type */
            case 2 :
            {
                if (strcmp("101", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_101_VOC;
                }
                else if (strcmp("103", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_103_H2;
                }
                else if (strcmp("104", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_104_C0;
                }
                else if (strcmp("105", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_105_NH3;
                }
                else if (strcmp("106", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_106_H2S;
                }
                else if (strcmp("107", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_107_C2H5OH;
                }
                else if (strcmp("109", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_109_C3H8;
                }
                else if (strcmp("110", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_110_CF2CL2;
                }
                else if (strcmp("112", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_112_NO2;
                }
                else if (strcmp("115", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_115_SMOG;
                }
                else if (strcmp("116", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_116_CH2O;
                }
                else if (strcmp("117", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_117_CH3COCH3;
                }
                else if (strcmp("131", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_131_O3;
                }
                else if (strcmp("138", optarg) == 0)
                {
                    chip_type = JED1XX_TYPE_138_C6H6;
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (jed1xx_read_test(chip_type, times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float ppm;
        
        /* basic init */
        res = jed1xx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 3000ms */
            jed1xx_interface_delay_ms(3000);
            
            /* read data */
            res = jed1xx_basic_read(&ppm);
            if (res != 0)
            {
                (void)jed1xx_basic_deinit();
                
                return 1;
            }
            
            /* output */
            jed1xx_interface_debug_print("jed1xx: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            jed1xx_interface_debug_print("jed1xx: output is %0.1fppm.\n", ppm);
        }
        
        /* deinit */
        (void)jed1xx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        jed1xx_interface_debug_print("Usage:\n");
        jed1xx_interface_debug_print("  jed1xx (-i | --information)\n");
        jed1xx_interface_debug_print("  jed1xx (-h | --help)\n");
        jed1xx_interface_debug_print("  jed1xx (-p | --port)\n");
        jed1xx_interface_debug_print("  jed1xx (-t read | --test=read) [--type=<101 | 103 | 104 | 105 | 106 | 107 | 109 | 110 |");
        jed1xx_interface_debug_print(" 112 | 115 | 116 | 117 | 131 | 138>] [--times=<num>]\n");
        jed1xx_interface_debug_print("  jed1xx (-e read | --example=read) [--type=<101 | 103 | 104 | 105 | 106 | 107 | 109 | 110 |");
        jed1xx_interface_debug_print(" 112 | 115 | 116 | 117 | 131 | 138>] [--times=<num>]\n");
        jed1xx_interface_debug_print("\n");
        jed1xx_interface_debug_print("Options:\n");
        jed1xx_interface_debug_print("  -e <read>, --example=<read>    Run the driver example.\n");
        jed1xx_interface_debug_print("  -h, --help                     Show the help.\n");
        jed1xx_interface_debug_print("  -i, --information              Show the chip information.\n");
        jed1xx_interface_debug_print("  -p, --port                     Display the pin connections of the current board.\n");
        jed1xx_interface_debug_print("  -t <read>, --test=<read>       Run the driver test.\n");
        jed1xx_interface_debug_print("      --times=<num>              Set the running times.([default: 3])\n");
        jed1xx_interface_debug_print("      --type=<101 | 103 | 104 |\n");
        jed1xx_interface_debug_print("              105 | 106 | 107 |\n");
        jed1xx_interface_debug_print("              109 | 110 | 112 |\n");
        jed1xx_interface_debug_print("              115 | 116 | 117 |\n");
        jed1xx_interface_debug_print("              131 | 138>         Set the chip type.([default: 101])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        jed1xx_info_t info;
        
        /* print jed1xx information */
        jed1xx_info(&info);
        jed1xx_interface_debug_print("jed1xx: chip is %s.\n", info.chip_name);
        jed1xx_interface_debug_print("jed1xx: manufacturer is %s.\n", info.manufacturer_name);
        jed1xx_interface_debug_print("jed1xx: interface is %s.\n", info.interface);
        jed1xx_interface_debug_print("jed1xx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        jed1xx_interface_debug_print("jed1xx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        jed1xx_interface_debug_print("jed1xx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        jed1xx_interface_debug_print("jed1xx: max current is %0.2fmA.\n", info.max_current_ma);
        jed1xx_interface_debug_print("jed1xx: max temperature is %0.1fC.\n", info.temperature_max);
        jed1xx_interface_debug_print("jed1xx: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        jed1xx_interface_debug_print("jed1xx: SCL connected to GPIOB PIN8.\n");
        jed1xx_interface_debug_print("jed1xx: SDA connected to GPIOB PIN9.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register jed1xx function */
    shell_init();
    shell_register("jed1xx", jed1xx);
    uart_print("jed1xx: welcome to libdriver jed1xx.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("jed1xx: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("jed1xx: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("jed1xx: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("jed1xx: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("jed1xx: param is invalid.\n");
            }
            else
            {
                uart_print("jed1xx: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
