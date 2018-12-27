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
#include "CommandUtil.h"
#include "SoftwareSerial.h"

/**
 * Implement library CommandUtil.h
 */

/**
 * Constructor, get RX, TX ports
 */
CommandUtil::CommandUtil(int rxPort, int txPort) : _serialHandler(rxPort, txPort) {
    _data = "";
    _command = -1;
    //  Default
    _delay = 100;
}

void CommandUtil::begin(int portSpeed) {
    _serialHandler.begin(portSpeed);
}

/**
 * Get command as integer for evaluate
 */
uint8_t CommandUtil::getCommand(String data) {
	if(!hasValue(data)) {
	    return data.substring(1, data.indexOf(EOT_CHARACTER)).toInt();
	}
	//  else
	return data.substring(1, data.indexOf(STX_CHARACTER)).toInt();
}

/**
 * Verify if a command has value
 */
boolean CommandUtil::hasValue(String data) {
  //  Validate data
  if(data.length() == 0) {
    return false;
  }
  //
  if(data.indexOf(STX_CHARACTER) > 0) {
    return true;
  }
  //  default
  return false;
}

/**
 * Get value of command received from external device
 */
String CommandUtil::getValue(String data) {
  if(!hasValue(data)) {
    return "";
  }
  //  else
  return data.substring(data.indexOf(STX_CHARACTER) + 1);
}

/**
 * Get command as integer for evaluate
 */
uint8_t CommandUtil::getCommand() {
	return getCommand(_data);
}

/**
 * Verify if a command has value
 */
boolean CommandUtil::hasValue() {
  return hasValue(_data);
}

/**
 * Get value of command received from external device
 */
String CommandUtil::getValue() {
  return getValue(_data);
}

void CommandUtil::setDelay(int delay) {
    _delay = delay;
}

/**
 * Init Command
 */
void CommandUtil::initCommand(uint8_t command) {
	_serialHandler.write(SOH_CHARACTER);
	_serialHandler.write(command);
}

/**
 * Send value with key
 */
void CommandUtil::sendValue(char key[], char value[]) {
	_serialHandler.write(STX_CHARACTER);
	_serialHandler.write(key);
	_serialHandler.write(VALUE_SEPARATOR);
	_serialHandler.write(value);
	_serialHandler.write(ETX_CHARACTER);
}

/**
 * Send Value without command
 */
void CommandUtil::sendValue(char value[]) {
	_serialHandler.write(STX_CHARACTER);
	_serialHandler.write(value);
	_serialHandler.write(ETX_CHARACTER);
}

/**
 * End command Stream
 */
void CommandUtil::endCommand() {
	_serialHandler.write(EOT_CHARACTER);
}

/**
 * Read port for get info
 */
boolean CommandUtil::readPort() {
	boolean started = false;
	if (_serialHandler.available()) {
		delay(_delay);
	    //  Iterate it
		while(_serialHandler.available()) {
			char character = _serialHandler.read();
			if(character == SOH_CHARACTER) {
				_data = "";
				started = true;
			}
			//  For all
			if(started) {
				_data.concat(character);
			}
			//
			if(character == EOT_CHARACTER) {
                if(started) {
                    break;
                }
				started = false;
			}
	    }
		return true;
	}
	//	Return
	return false;
}
