// ---------------------------------------------------------------------------
// *                        www.apsis-solutions.com
// *               Copyright (c) Apsis Solutions, Bangalore
// *--------------------------------------------------------------------------
// *    Project         : Generic
// *    Module          : ADC 
// *    Description     : Used to Configure the ADC and Read ADC
// *    Author          : Pankaj Sharma
// *    Workfile        : PinAllocation.h
// *    Revision        : 1.0
// *    Last changed on : Date: 2012-04-17
// *                     
// *    Last changed by : Pankaj Sharma
// *
// *--------------------------------------------------------------------------

#include<p18f46k22.h>


// Pin allocation.h
#define DEBUGMODE		1
#define RELEASEMODE	 	0
#define MODE			RELEASEMODE
#define DBGPRINTF if(MODE) printf

#define GPSMODE			RELEASEMODE
#define GPSDBGPRINTF	if(GPSMODE) printf

#define FAIL	0
#define PASS	1

#define SET_ANALOG   1
#define SET_DIGITAL  0

#define SET_INPUT   1
#define SET_OUTPUT  0

#define SET_TRUE 	1
#define SET_FALSE 	0

#define OUTPUT_HIGH  1
#define OUTPUT_LOW   0

#define ON 1
#define OFF 0

#define SELECT_GPS_ON_UART	1
#define SELECT_RFID_ON_UART	2
#define SELECT_PC_ON_UART		3



//  Configuration of LCD pins: 4 data pins, RS pin and Enable pin

#define RS_lcd          LATDbits.LATD0   	// For Selection of data or Command Mode.  				
#define Enable_lcd		LATDbits.LATD1   	// For Enabling the LCD.
#define lcd_d4_lsb		LATDbits.LATD2  	// pin 11 of LCD
#define lcd_d5			LATDbits.LATD3  	// pin 12 of LCD
#define lcd_d6			LATDbits.LATD4   	// pin 13 of LCD
#define lcd_d7_msb		LATDbits.LATD5   	// pin 14 of LCD	

// Direction selection of the PIC controller. The pin selected either as input or output as per the requirement
#define RS_lcd_dir          TRISDbits.TRISD0     				
#define Enable_lcd_dir		TRISDbits.TRISD1   
#define lcd_d4_lsb_dir		TRISDbits.TRISD2   // pin 11 of LCD DIR
#define lcd_d5_dir			TRISDbits.TRISD3   // pin 12 of LCD DIR
#define lcd_d6_dir			TRISDbits.TRISD4   // pin 13 of LCD DIR
#define lcd_d7_msb_dir		TRISDbits.TRISD5   // pin 14 of LCD DIR


#define Dir_DEVICE_0   TRISAbits.TRISA0
#define Dir_DEVICE_1   TRISAbits.TRISA1
#define Dir_DEVICE_2   TRISAbits.TRISA2
#define Dir_DEVICE_3   TRISAbits.TRISA3
#define Dir_DEVICE_4   TRISAbits.TRISA4
#define Dir_DEVICE_5   TRISAbits.TRISA5




#define DEVICE_0   LATAbits.LATA0
#define DEVICE_1   LATAbits.LATA1
#define DEVICE_2   LATAbits.LATA2
#define DEVICE_3   LATAbits.LATA3
#define DEVICE_4   LATAbits.LATA4
#define DEVICE_5   LATAbits.LATA5





#define SMOKE_SENSOR_CHANNEL 6//E1

#define BUZZER_ON 	1
#define BUZZER_OFF 	0

#define Dir_BUZZER 	TRISBbits.TRISB0
#define BUZZER      LATBbits.LATB0 	

#define DEVICE_OFF 		0
#define DEVICE_ON	 	1


#define SMOKE_SENSOR_ADC_THRESHOLD 500

#define DISABLE_RELAY   0
#define ENABLE_RELAY    1


#define SPEED_1_RELAY        PORTAbits.RA0
#define Dir_SPEED_1_RELAY    TRISAbits.TRISA0
#define Ans_SPEED_1_RELAY    ANSELAbits.ANSA0

#define SPEED_2_RELAY        PORTAbits.RA1
#define Dir_SPEED_2_RELAY    TRISAbits.TRISA1
#define Ans_SPEED_2_RELAY    ANSELAbits.ANSA1

#define SPEED_3_RELAY        PORTAbits.RA2
#define Dir_SPEED_3_RELAY    TRISAbits.TRISA2
#define Ans_SPEED_3_RELAY    ANSELAbits.ANSA2

#define SPEED_4_RELAY        PORTAbits.RA3
#define Dir_SPEED_4_RELAY    TRISAbits.TRISA3
#define Ans_SPEED_4_RELAY    ANSELAbits.ANSA3

#define SPEED_5_RELAY        PORTAbits.RA4
#define Dir_SPEED_5_RELAY    TRISAbits.TRISA4
#define Ans_SPEED_5_RELAY    ANSELAbits.ANSA4

#define HEATER_RELAY        PORTAbits.RA5
#define Dir_HEATER_RELAY    TRISAbits.TRISA5
#define Ans_HEATER_RELAY    ANSELAbits.ANSA5

#define DELAY_ITERATION_REQUIRED   2