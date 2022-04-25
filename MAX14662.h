/**
 * @file MAX14662.h
 * 
 * ESP32 driver for the MAX14662 8-channel I2C switch / multiplexer
 * 
 * For use with the ESP-IDF build framework; the I2C communication
 * is handled by the i2c_manager component.
 * 
 * @author Jakub Prikner <jakub.prikner@gmail.com>
 * https://www.prikner.net
 *
 */

/**
 * The MIT License
 * 
 * Copyright (c) 2022 Jakub Prikner <jakub.prikner@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// ====================================================================

#ifndef __MAX14662_H__
#define __MAX14662_H__

#include <inttypes.h>
#include <esp_log.h>
#include "esp_err.h"

// I2C Manager driver
#include <i2c_manager.h>

// --------------------------------------------------------------------

/** default I2C port **/
#define I2C_DEFAULT_PORT (I2C_NUM_0)

/** default I2C address **/
#define MAX14662_DEFAULT_ADDRESS (0x4C)

/** DIR0 address (the only register present) **/
#define MAX14662_DIR0  (0x00)

/** switches bit addresses definition (bit 0 - 7) **/
#define MAX14662_SW_1  (0B000)
#define MAX14662_SW_2  (0B001)
#define MAX14662_SW_3  (0B010)
#define MAX14662_SW_4  (0B011)
#define MAX14662_SW_5  (0B100)
#define MAX14662_SW_6  (0B101)
#define MAX14662_SW_7  (0B110)
#define MAX14662_SW_8  (0B111)

#define MAX14662_STATE_CLOSE_ALL   (0B11111111)
#define MAX14662_STATE_OPEN_ALL    (0B00000000)

// ====================================================================

class MAX14662
{
    public:
        MAX14662 ( i2c_port_t port = I2C_DEFAULT_PORT, uint8_t address = MAX14662_DEFAULT_ADDRESS ) ;

        ~MAX14662 () ;
    
        // --------------------------------------------------------------------
        /**
        Begin using the library instance. 
        Perform a reset of all the switches to its default (open) state.
        */
        void init () ;

        // --------------------------------------------------------------------
        /**
        The openSwitch command opens a single switch. 
        (MAX14662_SW_1 : MAX14662_SW_8)
        */
        esp_err_t openSwitch ( uint8_t switchNr ) ;

        // --------------------------------------------------------------------
        /**
        The closeSwitch command closes a single switch. 
        (MAX14662_SW_1 : MAX14662_SW_8)
        */
        esp_err_t closeSwitch ( uint8_t switchNr ) ;

        // --------------------------------------------------------------------
        /**
        The toggleSwitch command toggles a single switch state.
        (MAX14662_SW_1 : MAX14662_SW_8)
        */
        esp_err_t toggleSwitch ( uint8_t switchNr ) ;
        
        // --------------------------------------------------------------------
        /**
        The openAll command opens all the switches at once.
        */
        esp_err_t openAll () ;
        
        // --------------------------------------------------------------------
        /**
        The closeAll command closes all the switches at once.
        */
        esp_err_t closeAll () ;
        
        // --------------------------------------------------------------------
        /**
        The setSwitches command allows to set a custom bit mask configuration
        in the DIR0 register.
        */
        esp_err_t setSwitches ( uint8_t mask ) ;
                
        // --------------------------------------------------------------------
        /**
        This command reads the current value of the DIR0 register, 
        which contains current states of the switches.
        */
        uint8_t getAllSwitches () ;

    private:
        i2c_port_t port ;
        uint8_t    address ;

};


#endif  // __MAX14662_H__