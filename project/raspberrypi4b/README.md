### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(jed1xx REQUIRED)
```

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
./jed1xx -i

jed1xx: chip is JXCT JED1XX.
jed1xx: manufacturer is JXCT.
jed1xx: interface is IIC.
jed1xx: driver version is 1.0.
jed1xx: min supply voltage is 3.3V.
jed1xx: max supply voltage is 5.0V.
jed1xx: max current is 25.00mA.
jed1xx: max temperature is 85.0C.
jed1xx: min temperature is -40.0C.
```

```shell
./jed1xx -p

jed1xx: SCL connected to GPIO3(BCM).
jed1xx: SDA connected to GPIO2(BCM).
```

```shell
./jed1xx -t read --type=107 --times=3

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
./jed1xx -e read --type=107 --times=3

jed1xx: 1/3.
jed1xx: output is 573.7ppm.
jed1xx: 2/3.
jed1xx: output is 578.9ppm.
jed1xx: 3/3.
jed1xx: output is 573.7ppm.
```

```shell
./jed1xx -h

Usage:
  jed1xx (-i | --information)
  jed1xx (-h | --help)
  jed1xx (-p | --port)
  jed1xx (-t read | --test=read) [--type=<101 | 103 | 104 | 105 | 106 | 107 | 109 | 110 |         112 | 115 | 116 | 117 | 131 | 138>] [--times=<num>]
  jed1xx (-e read | --example=read) [--type=<101 | 103 | 104 | 105 | 106 | 107 | 109 | 110 |         112 | 115 | 116 | 117 | 131 | 138>] [--times=<num>]

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

#### 3.3 Command Problem

1. There is some unknown problem in the iic interface of jed1xx on the raspberry board, one command may try many times to run successfully or run failed.
