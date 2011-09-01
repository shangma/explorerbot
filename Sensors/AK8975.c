/*
             Bluetooth Robot
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
        www.fourwalledcubicle.com
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "AK8975.h"

static void AK8975_StartConversion(SensorData_t* const CompassSensorInfo)
{
	uint8_t PacketBuffer[1];

	/* Abort if sensor not connected and initialized */
	if (!(CompassSensorInfo->Connected))
	  return;

	/* Write to the control register to initiate the next single conversion */
	PacketBuffer[0] = AK8975_REG_CNTL_MODE_ONCE;	
	Sensor_WriteBytes(AK8975_ADDRESS, AK8975_REG_CNTL, PacketBuffer, 1);
}

void AK8975_Init(SensorData_t* const CompassSensorInfo)
{
	uint8_t PacketBuffer[1];

	/* Sensor considered not connected until it has been sucessfully initialized */
	CompassSensorInfo->Connected = false;

	/* Attempt to read the sensor's ID register, return error if sensor cannot be communicated with */
	if (Sensor_ReadBytes(AK8975_ADDRESS, AK8975_REG_WIA, PacketBuffer, 1) != TWI_ERROR_NoError)
	  return;

	/* Verify the returned sensor ID against the expected sensor ID */
	CompassSensorInfo->Connected = (PacketBuffer[0] == AK8975_DEVICE_ID);

	/* Abort if sensor not connected and initialized */
	if (!(CompassSensorInfo->Connected))
	  return;

	/* Try to trigger the first conversion in the sensor */
	AK8975_StartConversion(CompassSensorInfo);
}

void AK8975_Update(SensorData_t* const CompassSensorInfo)
{
	uint8_t PacketBuffer[6];

	/* Abort if sensor not connected and initialized */
	if (!(CompassSensorInfo->Connected))
	  return;
	
	/* Wait for sensor interrupt line to go high to signal end of conversion */
	while (!(PINB & (1 << 1)));

	/* Read the converted sensor data as a block packet */
	if (Sensor_ReadBytes(AK8975_ADDRESS, AK8975_REG_HXL, PacketBuffer, 6) != TWI_ERROR_NoError)
	  return;

	/* Save updated sensor data */
	CompassSensorInfo->Data.Triplicate.X = (((uint16_t)PacketBuffer[1] << 8) | PacketBuffer[0]);
	CompassSensorInfo->Data.Triplicate.Y = (((uint16_t)PacketBuffer[3] << 8) | PacketBuffer[2]);
	CompassSensorInfo->Data.Triplicate.Z = (((uint16_t)PacketBuffer[5] << 8) | PacketBuffer[4]);
		
	/* Start next sensor data conversion */
	AK8975_StartConversion(CompassSensorInfo);
}
