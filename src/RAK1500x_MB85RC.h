/**
   @file RAK1500x_MB85RC.h
   @author rakwireless.com
   @brief  TDK 6-axis digital output sense IC library.
   @version 0.1
   @date 2022-01-01
   @copyright Copyright (c) 2022
**/

#ifndef __RAK1500x_MB85RC_H__
#define __RAK1500x_MB85RC_H__

#include <Arduino.h>
#include <Wire.h>
#include "stdint.h"

#define LIB_DEBUG 0
#if LIB_DEBUG > 0
  #define LIB_LOG(...)                      \
    {                                       \
      Serial.printf("<%s>",__FUNCTION__);   \
      Serial.printf("<%d>",__LINE__);       \
      Serial.printf(__VA_ARGS__);           \
      Serial.printf("\n");                  \
      delay(10);                            \
    }
#else
  #define LIB_LOG(...)
#endif


/**
 * @brief MB85RCx address on the I2C bus.
 */
#define MB85RC_DEV_ADDRESS         (0x56)
#define MB85RC256_DEV_ADDRESS      (0x56)  // 1010 + A2 + A1 +A0
#define MB85RC512_DEV_ADDRESS      (0x56)  // 1010 + A2 + A1 +A0
#define MB85RC1_DEV_ADDRESS        (0x56)  // 1010 + A2 + A1 +A16 the most significant address of the memory address A16 (1 bit).



/**
 * @brief FRAM type.
 */
typedef enum 
{
  MB85RC256,
  MB85RC512,
  MB85RC1,
  UNKNOWN,
}FRAM_MODEL_t;

typedef enum 
{
  MB85RC256_PID = 0x510,
  MB85RC512_PID = 0x658,
  MB85RC1_PID   = 0x758,
}FRAM_ID_t;


//class RAK_MB85RC
class RAK_MB85RC
{
public: 

  RAK_MB85RC(byte addr = MB85RC256_DEV_ADDRESS);

  bool begin(TwoWire &wirePort = Wire, uint8_t deviceAddress = MB85RC256_DEV_ADDRESS); 

  
  void getID(uint16_t *manuID, uint16_t *prodID);
  uint8_t getDeviceType(void);
  uint32_t getDeviceCapacity(void);
  
  void write(uint32_t regAddr ,uint8_t *date , uint32_t size);
  void read(uint32_t regAddr, uint8_t *date, uint32_t size);
  
private:
  // READ IIC 

  TwoWire *_i2cPort = &Wire; // The generic connection to user's chosen I2C hardware
  uint8_t _deviceAddress;
  uint8_t _product = UNKNOWN;
  uint32_t _productSize = 0;  // Unit: Byte
};

#endif
