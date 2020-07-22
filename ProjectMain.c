// ---------------------------------------------------------------------------
// *                        www.apsis-solutions.com
// *               Copyright (c) Apsis Solutions, Bangalore
// *--------------------------------------------------------------------------
// *    Project         : Generic
// *    Module          : Project Main
// *    Description     : Project Starts Here
// *					  	  
// *    Author          : Ajith Kirlaya
// *    Workfile        : Projectmain.c
// *    Revision        : 2.0
// *    Last changed on : Date: 2017-10-08
// *                     
// *    Last changed by : Nitin Awasthi - +91-9880221378
// *    Last changed on : Date: 2019-11-19
// *
// *    Last changed by : Chiranjit Gorai
// *    Last changed on : Date: 2020-04-13
// *--------------------------------------------------------------------------

#include <p18f46k22.h>    
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "ProjectMain.h"  
#include "serial_codes.h"
#include "ADC.H" 
#include "PinAllocation.h"
#include "LCD.h"
#include "delay.h"
#include "timers.h"
#include "wifimodule.h" 

unsigned char guchLCDLine1String[17],guchLCDLine2String[17];
unsigned char uchBuffDisplay[] = "APSIS SOLUTIONS\n\r";
#pragma udata udata3
unsigned char uchRecieve150Ch[150],i = 0;
unsigned int guchDataTowebsite;
extern unsigned int gunField1Value,gunField2Value,gunField3Value,gunField4Value,gunField5Value,gunField6Value,gunField7Value,gunField8Value;
unsigned long ulVoltageInVolts;
extern unsigned char guchField5Value;
extern unsigned int gunDataFromFields;
unsigned char guchSendingData[10]= "TESTED OK";

unsigned int unSpeed1Required = 0;
unsigned int unSpeed2Required = 0;
unsigned int unSpeed3Required = 0;
unsigned int unSpeed4Required = 0;
unsigned int unTemperatureRequired = 0;
unsigned int unTemperatureFromSensor = 0;


void fnMixerSpeedRequired(unsigned char uchMixerSpeedRequired)
{
	if( uchMixerSpeedRequired == 1)
	{
		printf("Mixer Speed 1 Set\n\r");
		fnSpeed1Required();
	}
	else if (uchMixerSpeedRequired ==2)
	{
		printf("Mixer Speed 2 Set\n\r");
		fnSpeed2Required();
	}
	else if (uchMixerSpeedRequired ==3)
	{
		printf("Mixer Speed 3 Set\n\r");
		fnSpeed3Required();
	}
	else if (uchMixerSpeedRequired ==4)
	{
		printf("Mixer Speed 4 Set\n\r");
		fnSpeed4Required();
	}
	else if (uchMixerSpeedRequired ==5)
	{
		printf("Mixer Speed 5 Set\n\r");
		fnSpeed5Required();
	}
}

 void fnSpeed1Required(void)
 {
 	SPEED_1_RELAY = ENABLE_RELAY;
    SPEED_2_RELAY = DISABLE_RELAY; 
    SPEED_3_RELAY = DISABLE_RELAY; 
    SPEED_4_RELAY = DISABLE_RELAY;
    SPEED_5_RELAY = DISABLE_RELAY;
 }

 
 void fnSpeed2Required(void)
 {
 	SPEED_1_RELAY = DISABLE_RELAY;
    SPEED_2_RELAY = ENABLE_RELAY; 
    SPEED_3_RELAY = DISABLE_RELAY; 
    SPEED_4_RELAY = DISABLE_RELAY;
    SPEED_5_RELAY = DISABLE_RELAY;
 }


 void fnSpeed3Required(void)
 {
 	SPEED_1_RELAY = DISABLE_RELAY;
    SPEED_2_RELAY = DISABLE_RELAY; 
    SPEED_3_RELAY = ENABLE_RELAY; 
    SPEED_4_RELAY = DISABLE_RELAY;
    SPEED_5_RELAY = DISABLE_RELAY;
 }

 
 void fnSpeed4Required(void)
 {
 	SPEED_1_RELAY = DISABLE_RELAY;
    SPEED_2_RELAY = DISABLE_RELAY; 
    SPEED_3_RELAY = DISABLE_RELAY; 
    SPEED_4_RELAY = ENABLE_RELAY;
    SPEED_5_RELAY = DISABLE_RELAY;
 }

 void fnSpeed5Required(void)
 {
 	SPEED_1_RELAY = DISABLE_RELAY;
    SPEED_2_RELAY = DISABLE_RELAY; 
    SPEED_3_RELAY = DISABLE_RELAY; 
    SPEED_4_RELAY = DISABLE_RELAY;
    SPEED_5_RELAY = ENABLE_RELAY;
 }









void fnMain_Project()
{	
	unsigned int unTemperatureValue; 
	unsigned int unADCvalueSmokeSensor =0;
	unsigned int unDataFromThingspeakforDeviceControl = 0;
	unsigned int unDataFromField1,unDataFromField2;
	unsigned char uchCommandForRobot;
	unsigned char a=10,b=5,c=0;
	unsigned char uchData;
	unsigned char uchData1;
	
 	unsigned char uchRecieve150Ch[10],i = 0;
 	unsigned char uchtemp;
 	
 	unsigned char uchTempvalue[];
 	unsigned int  unADCvalue1=0;
 	unsigned int  unADCvalue2=0;
 	unsigned int  unADCvalue3=0;
 	unsigned int  unADCvalue4=0;
	
 	ANSELA = 0X00;
	Dir_DEVICE_0   = SET_OUTPUT;
	Dir_DEVICE_1   = SET_OUTPUT;
	Dir_DEVICE_2   = SET_OUTPUT;
	Dir_DEVICE_3   = SET_OUTPUT;
	Dir_DEVICE_4   = SET_OUTPUT;
	Dir_DEVICE_5   = SET_OUTPUT;

	Dir_BUZZER     		= SET_INPUT;
	BUZZER			 	= BUZZER_OFF; 

	DEVICE_0   = DEVICE_OFF;
	DEVICE_1   = DEVICE_OFF;
	DEVICE_2   = DEVICE_OFF;
	DEVICE_3   = DEVICE_OFF;
	DEVICE_4   = DEVICE_OFF;
	DEVICE_5   = DEVICE_OFF;


	Ans_SPEED_1_RELAY  = SET_DIGITAL;  
    Ans_SPEED_2_RELAY  = SET_DIGITAL;
    Ans_SPEED_3_RELAY  = SET_DIGITAL; 
    Ans_SPEED_4_RELAY  = SET_DIGITAL;
 // Ans_SPEED_5_RELAY  = SET_DIGITAL;
    Ans_HEATER_RELAY   = SET_DIGITAL;

    Dir_SPEED_1_RELAY  = SET_OUTPUT;
    Dir_SPEED_2_RELAY  = SET_OUTPUT;
    Dir_SPEED_3_RELAY  = SET_OUTPUT;
    Dir_SPEED_4_RELAY  = SET_OUTPUT;
    Dir_SPEED_5_RELAY  = SET_OUTPUT;
    Dir_HEATER_RELAY   = SET_OUTPUT;

	gunField1Value=-1;
	gunField2Value=-1;
	gunField3Value=-1; // value to update
	gunField4Value=-1;

	//***this while loop is added for this project***
	
	printf("Only Thingspeak Reading Mixer Grinder Automation\n\r");
    while(1)
    {
    	unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(8);//DP 2
        printf("\n\r***Mode = %d\n\r",unDataFromThingspeakforDeviceControl);
        if(unDataFromThingspeakforDeviceControl == 1)
        {
        	printf("\n\r--------------Auto Mode--------------\n\r");
        }
        else
        {
        	
            printf("\n\r--------------Manual Mode----------------\n\r");
 
            unSpeed1Required = fnFieldValuesFromChannels(2);//DP 2
            printf("\n\r***Speed Stage 1 = %d\n\r",unSpeed1Required);

            unSpeed2Required = fnFieldValuesFromChannels(3);//DP 2
            printf("\n\r***Speed Stage 2 = %d\n\r",unSpeed2Required);

            unSpeed3Required = fnFieldValuesFromChannels(4);//DP 2
            printf("\n\r***Speed Stage 3 = %d\n\r",unSpeed3Required);

            unSpeed4Required = fnFieldValuesFromChannels(5);//DP 2
            printf("\n\r***Speed Stage 4 = %d\n\r",unSpeed4Required);

            unTemperatureRequired = fnFieldValuesFromChannels(6);//DP 2
            printf("\n\r***Temperature Required = %d\n\r",unTemperatureRequired);

            printf("Starting the Operation of the Mixer\n\r");

            i=0;
            while(i < DELAY_ITERATION_REQUIRED)
            {

               printf("Setting the Temperature\n\r");

                unTemperatureFromSensor = unfnReadADCChannel(CHANNEL_15, ADC_10BIT_MODE);
                // Raw value has to be converted into the Actual Temperature Equivalent
                //
                //
                //
                //

                if(unTemperatureFromSensor > unTemperatureRequired)
                {
                	//Switch off the Heater
                	HEATER_RELAY = DISABLE_RELAY;
                }
                else
                {
                	//Switch on the Heater
                	HEATER_RELAY = ENABLE_RELAY;
                }
                delay_in_seconds(1);
                i++;
        } 

            fnMixerSpeedRequired(unSpeed1Required);
            delay_in_seconds(3);
              
            fnMixerSpeedRequired(unSpeed2Required);
            delay_in_seconds(3);

            fnMixerSpeedRequired(unSpeed3Required);
            delay_in_seconds(3);

            fnMixerSpeedRequired(unSpeed4Required);
            delay_in_seconds(3);


            printf("Your Chutney is Ready\n\r");


           }
       
            unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(1);//DP 2
            printf("\n\r***Type of Chutney = %d\n\r",unDataFromThingspeakforDeviceControl);


    //	unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(2);//DP 2

	//	printf("\n\r***unDataFromThingspeakforDeviceControl = %d\n\r",unDataFromThingspeakforDeviceControl);

	//	if(unDataFromThingspeakforDeviceControl == gunField2Value)
	//	{
	//		printf("Tested OK: Thank you for Testing...\n\r");
	//	}
	//	else
	//	{
	//	printf("ERROR: Tested NOK - Data Not Matched\n\r");
	//	}
    //      delay_in_seconds(4);
    
    }


    while(1)
	{
		printf("Nitin Waiting For Bluetooth Data...\n\r");
		while(uchfnReceive_Serial(UART1)!='*');
		printf("Data Received From Bluetooth ...\n\r");


		gunField1Value += 100;
		//gunField2Value += 200;
		gunField3Value += 300;
		gunField4Value += 400;


// *** the following were made as comments for this particular project***
	//	gunField2Value += 200;
		
	//	printf("\n\rUploading %d...",gunField2Value);

	//	fnDatauploadTothingspeakwebsite();
	//	printf("\n\rUploaded...");
	//	delay_in_seconds(2);
	


		unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(2);//DP 2
		// delay_in_seconds(1);

		if(unDataFromThingspeakforDeviceControl == gunField2Value)
		{
			printf("Tested OK: Thank you for Testing...\n\r");
		}
		else
		{
			printf("ERROR: Tested NOK - Data Not Matched\n\r");
		}
	


	}





























	printf("Waiting For Blutooth Data...\n\r");

	gunField2Value = 175;

	while(1)
	{
		// printf("Waiting For Blutooth Data...\n\r");
		// while(uchfnReceive_Serial(UART1)!='*');
		// printf("Data Recevied From Blutooth ...\n\r");

		gunField2Value = gunField2Value + 50;

		fnDatauploadTothingspeakwebsite();
		printf("\n\rUploaded...");
		delay_in_seconds(2);
		unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(2);//DP 2
		// delay_in_seconds(1);

		if(unDataFromThingspeakforDeviceControl == gunField2Value)
		{
			printf("Tested OK, Thank you for Tested...\n\r");
		}
		//printf("unDataFromThingspeakforDeviceControl =%d \n\r",unDataFromThingspeakforDeviceControl);
		//delay_in_seconds(5);

	}




	// while(1)
	// {


	// 	unDataFromThingspeakforDeviceControl = fnFieldValuesFromChannels(7);
	// 	printf("unDataFromThingspeakforDeviceControl =%d \n\r",unDataFromThingspeakforDeviceControl);
	// 	LATA= unDataFromThingspeakforDeviceControl & 0x3F;
	// 	delay_in_seconds(3);
	// 	unADCvalueSmokeSensor = unfnReadADCChannel(SMOKE_SENSOR_CHANNEL,ADC_10BIT_MODE);
	// 	printf("unADCvalueSmokeSensor =%d \n\r",unADCvalueSmokeSensor);
	// 	if(unADCvalueSmokeSensor > SMOKE_SENSOR_ADC_THRESHOLD)
	// 	{
	// 		BUZZER = BUZZER_ON;
	// 		gunField8Value = unADCvalueSmokeSensor;
	// 		fnDatauploadTothingspeakwebsite();
	// 		delay_in_seconds(3);
			
			
	// 	}
	// 	else
	// 	{

	// 		BUZZER	= BUZZER_OFF; 
	// 	}


	// }

	while(1)
	{
		unDataFromField1 = fnFieldValuesFromChannels(1);
		printf("unDataFromField4 = %d\n\r",unDataFromField1);
		
	}

	// while(1)
	// {
	// 	unADCvalue1 = unfnReadADCChannel(CHANNEL_0,ADC_10BIT_MODE);
	// 	unADCvalue2 = unfnReadADCChannel(CHANNEL_5,ADC_10BIT_MODE);
	// 	printf("unADCvalue1 =%04d  unADCvalue2 =%04d  \n\r",unADCvalue1,unADCvalue2);
	// 	gunField1Value=unADCvalue1;
	// 		delay_in_half_seconds(4);
		
	// }	
	// while(1)
	// {
	// 	unDataFromField1=fnFieldValuesFromChannels(1);
		
	// 	printf("unDataFromField1	= %d\n\r",unDataFromField1);
	// 	unDataFromField2=fnFieldValuesFromChannels(2);
	// 	printf("unDataFromField2	= %d\n\r",unDataFromField2);	
	// 	delay_in_half_seconds(2);
		
	// }
}
