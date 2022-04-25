/**
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

// ====================================================================

#include "MAX14662.h"

static const char *TAG = "MAX14662" ;

// ====================================================================

MAX14662::MAX14662 ( i2c_port_t port, uint8_t address ) : port (port), address (address)
{

}

// --------------------------------------------------------------------

MAX14662::~MAX14662 ()
{

}

// --------------------------------------------------------------------

void MAX14662::init ()
{
    ESP_LOGI ( TAG, "Init --- I2C port: %d, address: 0x%X", port, address ) ;
    openAll () ;
}

// --------------------------------------------------------------------

esp_err_t MAX14662::openSwitch ( uint8_t switchNr )
{
    uint8_t currentState = getAllSwitches () ;
    
    currentState &= ~( 1 << switchNr ) ;

    esp_err_t ret = i2c_manager_write ( port, address, MAX14662_DIR0, &currentState, 1 ) ;
    
    if ( ret != ESP_OK ) ESP_LOGE ( TAG, "Error opening switch #%d", switchNr ) ;

    return ret ;
}

// --------------------------------------------------------------------

esp_err_t MAX14662::closeSwitch ( uint8_t switchNr )
{    
    uint8_t currentState = getAllSwitches () ;
    
    currentState |= ( 1 << switchNr ) ;

    esp_err_t ret = i2c_manager_write ( port, address, MAX14662_DIR0, &currentState, 1 ) ;
    
    if ( ret != ESP_OK ) ESP_LOGE ( TAG, "Error closing switch #%d", switchNr ) ;

    return ret ;
}

// --------------------------------------------------------------------

esp_err_t MAX14662::toggleSwitch ( uint8_t switchNr )
{
    uint8_t currentState = getAllSwitches () ;
    
    currentState ^= ( 1 << switchNr ) ;

    esp_err_t ret = i2c_manager_write ( port, address, MAX14662_DIR0, &currentState, 1 ) ;
    
    if ( ret != ESP_OK ) ESP_LOGE ( TAG, "Error toggling switch #%d", switchNr ) ;

    return ret ;
}

// --------------------------------------------------------------------

esp_err_t MAX14662::openAll ()
{
    uint8_t state = MAX14662_STATE_OPEN_ALL ;

    esp_err_t ret = i2c_manager_write ( port, address, MAX14662_DIR0, &state, 1 ) ;
    
    if ( ret != ESP_OK ) ESP_LOGE ( TAG, "Error opening all the switches!" ) ;
    
    return ret ;
}

// --------------------------------------------------------------------

esp_err_t MAX14662::closeAll ()
{
    uint8_t state = MAX14662_STATE_CLOSE_ALL ;

    esp_err_t ret = i2c_manager_write ( port, address, MAX14662_DIR0, &state, 1 ) ;
    
    if ( ret != ESP_OK ) ESP_LOGE ( TAG, "Error closing all the switches!" ) ;
    
    return ret ;
}

// --------------------------------------------------------------------

esp_err_t MAX14662::setSwitches ( uint8_t mask )
{
    esp_err_t ret = i2c_manager_write ( port, address, MAX14662_DIR0, &mask, 1 ) ;
    
    if ( ret != ESP_OK ) ESP_LOGE ( TAG, "Error setting bit mask!" ) ;
    
    return ret ;
}

// --------------------------------------------------------------------

uint8_t MAX14662::getAllSwitches ()
{
    uint8_t data = 0x00 ;
 
    esp_err_t ret = i2c_manager_read ( port, address, MAX14662_DIR0, &data, 1 ) ;

    // printf ( "MAX14662 register data: %d\n", *data ) ;
    
    if ( ret != ESP_OK )
	{
        ESP_LOGE ( TAG, "Error reading MAX14662 register!" ) ;
        return -1 ;
    }
    return data ;
}
