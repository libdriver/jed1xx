### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. JED1XX

#### 3.1 Command Instruction

1. Show jed1xx chip and driver information.

   ```shell
   jed1xx (-i | --information)
   ```

2. Show jed1xx help.

   ```shell
   jed1xx (-h | --help)
   ```

3. Show jed1xx pin connections of the current board.

   ```shell
   jed1xx (-p | --port)
   ```

4. Run jed1xx read test, num means test times.

   ```shell
   jed1xx (-t read | --test=read) [--type=<101 | 103 | 104 | 105 | 106 | 107 | 109 | 110 | 112 | 115 | 116 | 117 | 131 | 138>] [--times=<num>]
   ```

5. Run jed1xx read function, num means test times.

   ```shell
   jed1xx (-e read | --example=read) [--type=<101 | 103 | 104 | 105 | 106 | 107 | 109 | 110 | 112 | 115 | 116 | 117 | 131 | 138>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
jed1xx -i

jed1xx: chip is JXCT JED1XX.
jed1xx: manufacturer is JXCT.
jed1xx: interface is IIC.
jed1xx: driver version is 1.0.
jed1xx: min supply voltage is 3.3V.
jed1xx: max supply voltage is 5.0V.
jed1xx: max current is 0.05mA.
jed1xx: max temperature is 85.0C.
jed1xx: min temperature is -40.0C.
```

```shell
jed1xx -p

jed1xx: SCL connected to GPIOB PIN8.
jed1xx: SDA connected to GPIOB PIN9.
```

```shell
jed1xx -t read --type=107 --times=3

jed1xx: chip is JXCT JED1XX.
jed1xx: manufacturer is JXCT.
jed1xx: interface is IIC.
jed1xx: driver version is 1.0.
jed1xx: min supply voltage is 3.3V.
jed1xx: max supply voltage is 5.0V.
jed1xx: max current is 25.00mA.
jed1xx: max temperature is 85.0C.
jed1xx: min temperature is -40.0C.
jed1xx: start read test.
jed1xx: output raw is 0x2A5A.
jed1xx: output is 542.1ppm.
jed1xx: output raw is 0x2B2C.
jed1xx: output is 552.6ppm.
jed1xx: output raw is 0x29F0.
jed1xx: output is 536.8ppm.
jed1xx: finish read test.
```

```shell
jed1xx -e read --type=107 --times=3

jed1xx: 1/3.
jed1xx: output is 573.7ppm.
jed1xx: 2/3.
jed1xx: output is 578.9ppm.
jed1xx: 3/3.
jed1xx: output is 573.7ppm.
```

```shell
jed1xx -h

Usage:
  jed1xx (-i | --information)
  jed1xx (-h | --help)
  jed1xx (-p | --port)
  jed1xx (-t read | --test=read) [--type=<101 | 103 | 104 | 105 | 106 | 107 | 109 | 110 | 112 | 115 | 116 | 117 | 131 | 138>] [--times=<num>]
  jed1xx (-e read | --example=read) [--type=<101 | 103 | 104 | 105 | 106 | 107 | 109 | 110 | 112 | 115 | 116 | 117 | 131 | 138>] [--times=<num>]

Options:
  -e <read>, --example=<read>    Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <read>, --test=<read>       Run the driver test.
      --times=<num>              Set the running times.([default: 3])
      --type=<101 | 103 | 104 |
              105 | 106 | 107 |
              109 | 110 | 112 |
              115 | 116 | 117 |
              131 | 138>         Set the chip type.([default: 101])
```

