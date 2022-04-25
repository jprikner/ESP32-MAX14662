#include "MAX14662.h"

// --------------------------------------------------------------------

extern "C"
{
    void app_main ( void )
    {
        // create library instance of the MAX14662 chip connected to I2C 0 port with the I2C address of 0x4C
        MAX14662 max ( I2C_NUM_0, 0x4C ) ;
        
        // initialize & reset all switches to open state
        max.init () ;

        printf ( "\n--- Handling a LED connected to SW 8 ---\n") ;
        
        while (1) 
        {
            printf ( "Turn the LED on\n" ) ;
		    max.closeSwitch ( MAX14662_SW_8 ) ;
            
            vTaskDelay ( pdMS_TO_TICKS (2000) ) ;

            printf ( "Turn the LED off\n" ) ;
            max.openSwitch ( MAX14662_SW_8 ) ;
            
            vTaskDelay ( pdMS_TO_TICKS (2000) ) ;


            printf ( "Turn the LED on again, setting the bit mask in the setSwitches() command\n" ) ;
            // manually set bit mask (in this case resulting in closing of SW 8 => turn the LED on)
            max.setSwitches ( 0B10000000 ) ;

            vTaskDelay ( pdMS_TO_TICKS (2000) ) ;

            printf ( "Read DIR0 register: 0x%X\n", max.getAllSwitches () ) ;
            
            vTaskDelay ( pdMS_TO_TICKS (2000) ) ;

            printf ( "Turn the LED off again, using the openAll() command\n" ) ;
            // open all switches (turn the LED off)
            max.openAll () ;

            vTaskDelay ( pdMS_TO_TICKS (2000) ) ;
        }     
    }
}