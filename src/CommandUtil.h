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
/** Value Separator */
static const char VALUE_SEPARATOR = '|';
/** Supported commands  */
static const char MESSAGE = '0';
/** Maintenance commands    */
static const char RESET_DEVICE = '1';
static const char CLEAR_EEPROM = '2';
static const char DEVICE_INFO = '3';
/** Wireless setup / info   */
static const char REMOTE_SETUP = '4';

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
        void initCommand(uint8_t command);
        void sendValue(char key[], char value[]);
        void sendValue(char key[]);
        void endCommand();
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
