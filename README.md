# ESP32-MAX14662

ESP32 driver for the MAX14662 8-channel I2C switch / multiplexer, for use with the ESP-IDF build framework. The I2C communication is handled 
by the *i2c_manager* component.

To be able to use it, you first need to have the i2c_manager repository in the components directory. I2C ports then have to be enabled and setup 
individually via menuconfig. You can find more information here: https://github.com/ropg/i2c_manager#simplest-usage
