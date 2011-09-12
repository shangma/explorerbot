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

#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		#include <stdlib.h>

		#include <LUFA/Drivers/USB/USB.h>
		
		#include "../Hardware/RGB.h"
		
		#include "../Sensors/SensorsCommon.h"
		#include "../FatFS/ff.h"
		
	/* Macros: */
		#define DATALOG_FILENAME   "ExplrBot.txt"
		
	/* External Variables: */
		extern USB_ClassInfo_MS_Host_t Datalogger_MS_Interface;

	/* Function Prototypes: */
		bool Datalogger_ConfigurePipes(USB_Descriptor_Device_t* DeviceDescriptor,
		                               uint16_t ConfigDescriptorSize,
		                               void* ConfigDescriptorData);
		bool Datalogger_PostConfiguration(void);
		void Datalogger_USBTask(void);
		
		void Datalogger_LogSensors(void);

#endif

