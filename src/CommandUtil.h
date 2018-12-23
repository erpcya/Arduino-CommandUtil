/*************************************************************************************
 * Copyright (C) 2012-2018 E.R.P. Consultores y Asociados, C.A.                      *
 * Contributor(s): Yamel Senih ysenih@erpya.com                                      *
 * This program is free software: you can redistribute it and/or modify              *
 * it under the terms of the GNU General Public License as published by              *
 * the Free Software Foundation, either version 3 of the License, or                 *
 * (at your option) any later version.                                               *
 * This program is distributed in the hope that it will be useful,                   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                     *
 * GNU General Public License for more details.                                      *
 * You should have received a copy of the GNU General Public License                 *
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.            *
 ************************************************************************************/
#ifndef CommandUtil_h
#define CommandUtil_h

#include "Arduino.h"
#include "SoftwareSerial.h"
/** Start of Header */
static const char SOH_CHARACTER = 1;
/** Start of Text   */
static const char STX_CHARACTER = 2;
/** End of Text */
static const char ETX_CHARACTER = 3;
/** End of Transmission */
static const char EOT_CHARACTER = 4;
/** Supported commands  */
static const uint8_t MESSAGE = 0;
/** Maintenance commands    */
static const uint8_t RESET_DEVICE = 1;
static const uint8_t CLEAR_EEPROM = 2;
static const uint8_t DEVICE_INFO = 3;
/** Wireless setup / info   */
static const uint8_t WIFI = 4;
/** MQTT setup / info   */
static const uint8_t MQTT = 5;

/**
 * This class if used for handle all serial command
 */
class CommandUtil {
    public:
	CommandUtil(int rxPort, int txPort);
        void begin(int portSpeed);
        void setDelay(int delay);
        uint8_t getCommand();
        boolean hasValue();
        String getValue();
        boolean readPort();
    private:
        String _data;
        uint8_t _command;
        uint8_t _delay;
        SoftwareSerial _serialHandler;
        uint8_t getCommand(String data);
        boolean hasValue(String data);
        String getValue(String data);
};
#endif
