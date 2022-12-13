| <center><img src="./assets/rakstar.jpg" alt="RAKstar" width=25%></center>  | ![RAKWireless](./assets/RAK-Whirls.png) | [![Build Status](https://github.com/RAKWireless/RAK13005-TLE7259-Library/workflows/RAK%20Library%20Build%20CI/badge.svg)](https://github.com/RAKWireless/RAK13005-TLE7259-Library/actions) |
| -- | -- | -- |

# <RAK15003 RAK15004 RAK15005>

RAK1500x-MB85RC library is suitable for RAK15003, RAK15004, RAK15005, they use MB85RC256, MB85RC512, MB85RC1M FRAM (Ferroelectric Random Access Memory), using the ferroelectric process and silicon gate CMOS process technologies for forming the nonvolatile memory cells.
	Unlike SRAM, the MB85RC is able to retain data without using a data backup battery.
	The read/write endurance of the nonvolatile memory cells used for the MB85RC has improved to be at least 1012 cycles, significantly outperforming other nonvolatile memory products in the number.
	The MB85RC does not need a polling sequence after writing to the memory such as the case of Flash memory or E2PROM.

[*RAKWireless <RAK#> <function>*](https://store.RAKWireless.com/products/RAK15003)

[*RAKWireless <RAK#> <function>*](https://store.RAKWireless.com/products/RAK15004)

[*RAKWireless <RAK#> <function>*](https://store.RAKWireless.com/products/RAK15005)

# Documentation

* **[Product Repository](https://github.com/RAKWireless/RAK15003)** - Product repository for the RAKWireless RAK15003 FRAM 256Kb module.
* **[Product Repository](https://github.com/RAKWireless/RAK15004)** - Product repository for the RAKWireless RAK15004 FRAM 512Kb module.
* **[Product Repository](https://github.com/RAKWireless/RAK15005)** - Product repository for the RAKWireless RAK15005 FRAM 1Mb module.
* **[Documentation](https://docs.RAKWireless.com/Product-Categories/WisBlock/RAK15003/Overview/)** - Documentation and Quick Start Guide for the RAK15003 FRAM 256Kb module.
* **[Documentation](https://docs.RAKWireless.com/Product-Categories/WisBlock/RAK15004/Overview/)** - Documentation and Quick Start Guide for the RAK15004 FRAM 512Kb module.
* **[Documentation](https://docs.RAKWireless.com/Product-Categories/WisBlock/RAK15005/Overview/)** - Documentation and Quick Start Guide for the RAK15005 FRAM 1Mb module.

# Installation

In Arduino IDE open Sketch->Include Library->Manage Libraries then search for RAK1500x-MB85RC.

In PlatformIO open PlatformIO Home, switch to libraries and search for RAK1500x-MB85RC.
Or install the library project dependencies by adding

```log
lib_deps =
  RAKWireless/RAKWireless MB85RC FRAM library
```

into **`platformio.ini`**

For manual installation download the archive, unzip it and place the RAK1500x-MB85RC folder into the library directory.
In Arduino IDE this is usually <arduinosketchfolder>/libraries/
In PlatformIO this is usually <user/.platformio/lib>

# Usage

The library provides RAK_MB85RC class, which allows communication with MB85RC via IIC. These examples show how to use MB85RC.

- [RAK1500x_FRAM_Read_Write_MB85RC](./examples/RAK1500x_FRAM_Read_Write_MB85RC) Test RAK1500x FRAM read and write functions. Suitable for RAK15003, RAK15004, RAK15005.

## This class provides the following methods:

**bool RAK_MB85RC::begin(TwoWire &wirePort, uint8_t deviceAddress)**

Initialize MB85RC.

#### Parameters:

| Direction | Name          | Function                                                     |
| --------- | ------------- | ------------------------------------------------------------ |
| in        | wirePort      | IIC interface used.                                          |
| in        | deviceAddress | Device address.                                              |
| return    |               | If the device init successful return true else return false. |

**void RAK_MB85RC::getID(uint16_t *manuID, uint16_t *prodID) **

Reads the Manufacturer ID and the Product ID frm the IC.

#### Parameters:

| Direction | Name   | Function                         |
| --------- | ------ | -------------------------------- |
| in        | manuID | Manufacture ID variable pointer. |
| in        | prodID | Product ID variable pointer.     |
| return    |        | NONE                             |

**uint32_t RAK_MB85RC::getDeviceCapacity(void)**

Get device capacity.

#### Parameters:

| Direction | Name | Function                      |
| --------- | ---- | ----------------------------- |
| return    |      | Device capacity.(Unit: Byte). |

**uint8_t RAK_MB85RC::getDeviceType(void) **

Get device type. @FRAM_MODEL_t

#### Parameters:

| Direction | Name | Function     |
| --------- | ---- | ------------ |
| return    |      | Device type. |

**void RAK_MB85RC::write(uint32_t regAddr ,uint8_t *date , uint32_t size)   **

Write data of specified length to specified address through IIC.

#### Parameters:

| Direction | Name    | Function                        |
| --------- | ------- | ------------------------------- |
| in        | regAddr | Write address.                  |
| in        | date    | Write data pointer.             |
| in        | size    | The length of the written data. |
| return    |         | NONE                            |

**void RAK_MB85RC::read(uint32_t regAddr, uint8_t *date, uint32_t size)   **

Read data of specified length to specified address through IIC.

#### Parameters:

| Direction | Name    | Function                     |
| --------- | ------- | ---------------------------- |
| in        | regAddr | Read address.                |
| in        | date    | Read data pointer.           |
| in        | size    | The length of the read data. |
| return    |         | NONE                         |