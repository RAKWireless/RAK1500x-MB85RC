/**
   @file RAK1500x_MB85RC.cpp
   @author rakwireless.com
   @brief  MB85RC configuration function realization.
   @version 0.1
   @date 2022-03-28
   @copyright Copyright (c) 2022
**/

#include "RAK1500x_MB85RC.h"

/*!
 *  @brief  Initialize the class.
 *  @param  addr: The device IIC address. 
 */

RAK_MB85RC::RAK_MB85RC(byte addr)
{
  _deviceAddress = addr;
}

/*!
 *  @brief  Initalizes the MB85RC sensor.
 *  @param  wirePort      : IIC interface used.
 *  @param  deviceAddress : Device address. 
 *  @return If the device init successful return true else return false.
 */
bool RAK_MB85RC::begin(TwoWire &wirePort, uint8_t deviceAddress)
{
  uint16_t mID, pID;
  _deviceAddress = deviceAddress;
  _i2cPort = &wirePort;

  getID(&mID, &pID);

  switch (pID) 
  {
    case MB85RC256_PID:
      _product = MB85RC256;
      _productSize = 32768;
      break;
    case MB85RC512_PID:
      _productSize = 65536;
      _product = MB85RC512;
      break;
    case MB85RC1_PID:
			_productSize = 131072;
      _product = MB85RC1;
      break;
    default:
      _product = UNKNOWN;
      LIB_LOG("UNKNOWN DEVICE!");
      return false;    
  }
  return true;
}

/*!
 *  @brief  Reads the Manufacturer ID and the Product ID frm the IC.
 *  @param  manuID      : Manufacture ID.
 *  @param  prodID      : Product ID.
 *  @return none.
 */
void RAK_MB85RC::getID(uint16_t *manuID, uint16_t *prodID)
{
  uint8_t date[3] = {0};

  _i2cPort->beginTransmission(0x7C); // Setting up i2c connection.
  
  _i2cPort->write(0xAC);

  _i2cPort->endTransmission(false); 
  
  _i2cPort->requestFrom(0x7C, 3);
  
  uint16_t i = 0;
  while ( _i2cPort->available() ) // slave may send less than requested
  {
    date[i] = _i2cPort->read(); // receive a byte as a proper uint8_t
    i++;
  }

  *manuID = (date[0] << 4) + (date[1] >> 4);
  *prodID = ((date[1] & 0x0F) << 8) + date[2];
  
  LIB_LOG("Manufacturer ID: 0x%x",*manuID);
  LIB_LOG("Product      ID: 0x%x",*prodID);

}

/*!
 *  @brief  Get device capacity.
 *  @return Device capacity.(Unit: Byte)
 */
uint32_t RAK_MB85RC::getDeviceCapacity(void)
{
  return _productSize;
}

/*!
 *  @brief  Get device type. @FRAM_MODEL_t
 *  @return Device type.
 */
uint8_t RAK_MB85RC::getDeviceType(void)
{
  return _product;
}


/*!
 *  @brief  Write data of specified length to specified address through IIC.
 *  @param  regAddr     : Write address.
 *  @param  date        : Write data pointer.
 *  @param  size        : The length of the written data.
 */
void RAK_MB85RC::write(uint32_t regAddr ,uint8_t *date , uint32_t size) 
{
  uint8_t regH = (uint8_t)((regAddr >> 8) & 0xFF);
  uint8_t regL = (uint8_t)(regAddr & 0xFF);
  uint8_t deviceAddress = _deviceAddress;

  // Devide Address = 1010 + A2 + A1 + A16;
  if (_product == MB85RC1)
  {
    deviceAddress &= 0xFE ;
    deviceAddress  = ((regAddr >> 16) & 0x01) | deviceAddress;
		LIB_LOG("deviceAddress: 0x%x",deviceAddress);
  }
  
  LIB_LOG("Write REG: 0x%x%x",regH,regL);  

  _i2cPort->beginTransmission(deviceAddress); // Setting up i2c connection.

  _i2cPort->write(regH); // Register address high
  _i2cPort->write(regL); // Register address low

  for (uint16_t i = 0; i < size; i++)
  {
    _i2cPort->write(date[i]);
  }

  _i2cPort->endTransmission();
}

/*!
 *  @brief  Read data of specified length to specified address through IIC.
 *  @param  regAddr     : Read address.
 *  @param  date        : Read data pointer.
 *  @param  size        : The length of the read data.
 */
void RAK_MB85RC::read(uint32_t regAddr, uint8_t *date, uint32_t size)
{  
  uint8_t regH = (uint8_t)((regAddr >> 8) & 0xFF);
  uint8_t regL = (uint8_t)(regAddr & 0xFF);
  uint8_t deviceAddress = _deviceAddress;

  // Devide Address = 1010 + A2 + A1 + A16;
  if (_product == MB85RC1)
  {
    deviceAddress &= 0xFE ;
    deviceAddress  = ((regAddr >> 16) & 0x01) | deviceAddress;
		LIB_LOG("deviceAddress: 0x%x",deviceAddress);
  }
  
  LIB_LOG("Read REG: 0x%x%x",regH,regL);

  _i2cPort->beginTransmission(deviceAddress);
  _i2cPort->write(regH); // Register address high
  _i2cPort->write(regL); // Register address low
  _i2cPort->endTransmission(); 
  
  _i2cPort->requestFrom(deviceAddress, size);
  
  uint16_t i = 0;
  while ( _i2cPort->available() ) // Slave may send less than requested.
  {
    date[i] = _i2cPort->read(); // Receive a byte as a proper uint8_t.
    i++;
  }
}
