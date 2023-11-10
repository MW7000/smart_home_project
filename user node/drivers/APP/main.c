/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 9 NOV 2023                        */
/*  SWC: APP                                */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_int.h"
#include "DIO_int.h"
#include "GI_int.h"
#include "SPI_int.h"
#include "TIM0_int.h"
#include "TIM1_int.h"
#include "TIM2_int.h"
#include "ADC_int.h"
#include "KEYPAD_int.h"
#include "LCD_int.h"
#include "util/delay.h"

static uint8 private_uint8KeypadReading, private_uint8KeypadBuffer, private_uint8LogInFlag;
static uint16 DC[2]={72,1};

#define		APP_USER_LOGGED_IN			7
#define		APP_USER_LOGGED_OUT			9

#define		APP_USER_ID_LENGTH			8
#define		APP_USER_PASS_LENGTH		8

#define		APP_USER_ID_LENGTH_PLUS_1		9
#define		APP_USER_PASS_LENGTH_PLUS_1		9


#define		APP_USER_ID_ID				0x55
#define		APP_USER_PASS_ID			0x66

#define 	APP_USER_ID_EXISTS			10
#define		APP_USER_ID_NOT_EXIST		30

#define 	APP_USER_PASS_MATCH			10
#define		APP_USER_PASS_MISMATCH		30

#define		APP_DUMMY_DATA_1				0x90
#define		APP_DUMMY_DATA_2				0x80


#define		APP_MAX_INCORRECT_DATA_ENTRY_TIMES		3


#define 	APP_DOOR_CONTROL_CHOICE		'1'
#define 	APP_FAN_CONTROL_CHOICE		'2'
#define 	APP_LIGHT_CONTROL_CHOICE	'3'
#define 	APP_LOGOUT_CHOICE			'4'


void APP_SetKeypadReading(void);

void APP_voidSetUserChoice(void);

void APP_voidExecuteUserChoice(void);

void main(void){

	uint8  local_uint8ReceivedData, local_uint8IdCounter=0, local_uint8PassCounter=0;
	uint8 local_uint8Id[APP_USER_ID_LENGTH_PLUS_1], local_uint8Pass[APP_USER_PASS_LENGTH_PLUS_1];

	private_uint8LogInFlag=APP_USER_LOGGED_OUT;

	PORT_voidInit();
	GI_voidEnable();
	SPI_voidInit();
	TIM0_voidInit();
	TIM1_voidInit();
	TIM2_voidInit();
	TIM2_voidStart();
	ADC_voidInit();
	KEYPAD_voidInit();
	LCD_voidInit();

	TIM0_voidSetCallBackFunc(&APP_SetKeypadReading);
	TIM0_voidSetDelayAsynch_ms(80,TIM0_DELAY_CONTINUOUS);
	TIM0_voidStart();

	TIM1_voidFGeneratePWM(50,DC);							// Door normally closed
	private_uint8KeypadReading = KEYPAD_KEY_NOT_PRESSED;


	LCD_voidGoToLocation(1,3);
	LCD_voidWriteString("Smart Home");
	LCD_voidGoToLocation(2,5);
	LCD_voidWriteString("System");
	_delay_ms(3000);

	while(KEYPAD_KEY_NOT_PRESSED==private_uint8KeypadReading);			// until user enters any key

	while(1){

			if(private_uint8LogInFlag==APP_USER_LOGGED_OUT){

				do{
					LCD_voidClearScreen();
					LCD_voidWriteString("Enter your ID");
					LCD_voidGoToLocation(2,0);
					LCD_voidWriteString("> ");

					for(uint8 i=0;i<APP_USER_ID_LENGTH;i++){

						while(private_uint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);
						private_uint8KeypadBuffer = private_uint8KeypadReading;
						local_uint8Id[i]=private_uint8KeypadBuffer;
						LCD_voidWriteChar(private_uint8KeypadBuffer);

						private_uint8KeypadReading = KEYPAD_KEY_NOT_PRESSED;
					}
					local_uint8Id[APP_USER_ID_LENGTH]='\0';

					LCD_voidClearScreen();
					LCD_voidWriteString("Verifying...");

					// sending ID to admin node to verify
					DIO_voidSetPinValue(DIO_PIN_NO_12,DIO_PIN_HIGH);
					_delay_ms(1);
					DIO_voidSetPinValue(DIO_PIN_NO_12,DIO_PIN_LOW);			//  SS PIN

					while(SPI_NO_ERROR!=SPI_uint8TransceiveSynch(APP_USER_ID_ID, &local_uint8ReceivedData));

					for(uint8 i=0;i<APP_USER_ID_LENGTH_PLUS_1;i++){

						SPI_uint8TransceiveSynch(local_uint8Id[i], &local_uint8ReceivedData);
						_delay_ms(1);

					}

					while( local_uint8ReceivedData!=APP_USER_ID_EXISTS && local_uint8ReceivedData!=APP_USER_ID_NOT_EXIST )
						SPI_uint8TransceiveSynch(APP_DUMMY_DATA_1,&local_uint8ReceivedData);

					if(local_uint8ReceivedData==APP_USER_ID_EXISTS){

						LCD_voidClearScreen();
						LCD_voidWriteString("Enter your pass");
						LCD_voidGoToLocation(2,0);
						LCD_voidWriteString("> ");

						for(uint8 i=0;i<APP_USER_PASS_LENGTH;i++){

							while(private_uint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);

							private_uint8KeypadBuffer = private_uint8KeypadReading;
							local_uint8Pass[i]=private_uint8KeypadBuffer;
							LCD_voidWriteChar(private_uint8KeypadBuffer);

							private_uint8KeypadReading = KEYPAD_KEY_NOT_PRESSED;

						}
						local_uint8Pass[APP_USER_PASS_LENGTH]='\0';

						LCD_voidClearScreen();
						LCD_voidWriteString("Verifying...");

						// sending pass to admin node to verify

						while(SPI_NO_ERROR!=SPI_uint8TransceiveSynch(APP_USER_PASS_ID,&local_uint8ReceivedData));

						for(uint8 i=0;i<APP_USER_PASS_LENGTH_PLUS_1;i++){

							SPI_uint8TransceiveSynch(local_uint8Pass[i],&local_uint8ReceivedData);
							_delay_ms(1);

						}

						while(local_uint8ReceivedData!=APP_USER_PASS_MATCH && local_uint8ReceivedData!=APP_USER_PASS_MISMATCH)
							SPI_uint8TransceiveSynch(APP_DUMMY_DATA_2, &local_uint8ReceivedData);

						if(local_uint8ReceivedData==APP_USER_PASS_MATCH){

							private_uint8LogInFlag = APP_USER_LOGGED_IN;
						}
						else if(local_uint8ReceivedData==APP_USER_PASS_MISMATCH){

							LCD_voidClearScreen();
							LCD_voidWriteString("Incorrect pass");
							_delay_ms(1000);
							local_uint8PassCounter++;
						}

					}
					else if(local_uint8ReceivedData==APP_USER_ID_NOT_EXIST){

						LCD_voidClearScreen();
						LCD_voidWriteString("ID doesn't exist");
						_delay_ms(1000);
						local_uint8IdCounter++;
					}

			}while( (local_uint8IdCounter<APP_MAX_INCORRECT_DATA_ENTRY_TIMES) && (local_uint8PassCounter<APP_MAX_INCORRECT_DATA_ENTRY_TIMES) && (private_uint8LogInFlag==APP_USER_LOGGED_OUT) );

				if( (local_uint8IdCounter==APP_MAX_INCORRECT_DATA_ENTRY_TIMES) || (local_uint8PassCounter==APP_MAX_INCORRECT_DATA_ENTRY_TIMES) ){

					LCD_voidClearScreen();
					LCD_voidGoToLocation(1,2);
					LCD_voidWriteString("UNAUTHORIZED");
					LCD_voidGoToLocation(2,5);
					LCD_voidWriteString("ACCESS");
					// fire alarm
					for(uint8 i=0;i<60;i++){

						DIO_voidSetPinValue(DIO_PIN_NO_7,DIO_PIN_HIGH);				// Buzzer alarm
						DIO_voidSetPinValue(DIO_PIN_NO_30,DIO_PIN_HIGH);				// Led toggling
						_delay_ms(1000);
						DIO_voidSetPinValue(DIO_PIN_NO_7,DIO_PIN_LOW);				// Buzzer alarm
						DIO_voidSetPinValue(DIO_PIN_NO_30,DIO_PIN_LOW);				// Led toggling
						_delay_ms(1000);

					}

				}

				local_uint8IdCounter=0;
				local_uint8PassCounter=0;
			}
			else if(private_uint8LogInFlag==APP_USER_LOGGED_IN){

				APP_voidSetUserChoice();

				APP_voidExecuteUserChoice();

			}


	}


}


void APP_SetKeypadReading(void){

	private_uint8KeypadReading = KEYPAD_uint8GetPressedKey();

}

void APP_voidSetUserChoice(void){

	do{
		LCD_voidClearScreen();
		LCD_voidWriteString("Manage your home");
		LCD_voidGoToLocation(2,0);
		LCD_voidWriteString("through CMD ID: ");
		_delay_ms(3000);
		LCD_voidClearScreen();
		LCD_voidWriteString("1-door 2-Fan");
		LCD_voidGoToLocation(2,0);
		LCD_voidWriteString("3-light 4-logout");
		_delay_ms(3000);
		LCD_voidClearScreen();
		LCD_voidWriteString("> ");
		while(private_uint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);
		private_uint8KeypadBuffer = private_uint8KeypadReading;
		LCD_voidWriteChar(private_uint8KeypadBuffer);
		_delay_ms(500);

	}while(private_uint8KeypadBuffer< '1' || private_uint8KeypadBuffer> '4' );

}

void APP_voidExecuteUserChoice(void){

	LCD_voidClearScreen();

	switch(private_uint8KeypadBuffer){

	case APP_DOOR_CONTROL_CHOICE:

		LCD_voidWriteString("1-Open Door");
		LCD_voidGoToLocation(2,0);
		LCD_voidWriteString("2-Close Door");

		_delay_ms(2000);
		LCD_voidClearScreen();
		LCD_voidWriteString("> ");
		while(private_uint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);
		private_uint8KeypadBuffer = private_uint8KeypadReading;
		LCD_voidWriteChar(private_uint8KeypadBuffer);
		LCD_voidGoToLocation(2,0);
		if(private_uint8KeypadBuffer=='1'){

			DC[0] = 25;
			TIM1_voidFGeneratePWM(50,DC);				// 0 degrees
			LCD_voidWriteString("Opening...");
		}
		else if(private_uint8KeypadBuffer=='2'){

			DC[0] = 72;
			TIM1_voidFGeneratePWM(50,DC);				// 90 degrees
			LCD_voidWriteString("Closing...");
		}

		_delay_ms(500);
		break;

	case APP_FAN_CONTROL_CHOICE:


		LCD_voidWriteString("Enter Fan Speed:");
		LCD_voidGoToLocation(2,0);
		LCD_voidWriteString("> ");
		while(private_uint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);
		private_uint8KeypadBuffer = private_uint8KeypadReading;
		LCD_voidWriteChar(private_uint8KeypadBuffer);
		_delay_ms(500);
		LCD_voidClearScreen();
		if(private_uint8KeypadBuffer=='1'){

			TIM2_voidGeneratePWMSignal(25);
			LCD_voidWriteString("Fan operating");
			LCD_voidGoToLocation(2,0);
			LCD_voidWriteString("at speed 1");
		}
		else if(private_uint8KeypadBuffer=='2'){

			TIM2_voidGeneratePWMSignal(50);
			LCD_voidWriteString("Fan operating");
			LCD_voidGoToLocation(2,0);
			LCD_voidWriteString("at speed 2");

		}
		else if(private_uint8KeypadBuffer=='3'){

			TIM2_voidGeneratePWMSignal(75);
			LCD_voidWriteString("Fan operating");
			LCD_voidGoToLocation(2,0);
			LCD_voidWriteString("at speed 3");

		}
		else if(private_uint8KeypadBuffer=='4'){

			TIM2_voidGeneratePWMSignal(100);
			LCD_voidWriteString("Fan operating");
			LCD_voidGoToLocation(2,0);
			LCD_voidWriteString("at speed 4");

		}


		_delay_ms(1000);

		break;

	case APP_LIGHT_CONTROL_CHOICE:


		LCD_voidWriteString("Enter room NO:");
		LCD_voidGoToLocation(2,0);
		LCD_voidWriteString("> ");
		while(private_uint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);
		private_uint8KeypadBuffer = private_uint8KeypadReading;
		LCD_voidWriteChar(private_uint8KeypadBuffer);
		_delay_ms(500);
		LCD_voidClearScreen();
		if(private_uint8KeypadBuffer=='1'){

			uint16 local_uint16KeypadResult=0;
			LCD_voidWriteString("Enter room light");
			LCD_voidGoToLocation(2,0);
			LCD_voidWriteString("intensity > ");
			for(uint8 i=10;i>0;i/=10){

				while(KEYPAD_KEY_NOT_PRESSED==private_uint8KeypadReading);
				private_uint8KeypadBuffer = private_uint8KeypadReading;
				LCD_voidWriteChar(private_uint8KeypadBuffer);
				local_uint16KeypadResult += (private_uint8KeypadBuffer-'0')*i;
				private_uint8KeypadReading = KEYPAD_KEY_NOT_PRESSED;
			}
			DC[1] = local_uint16KeypadResult*10;

			TIM1_voidFGeneratePWM(50,DC);

		}
		else if(private_uint8KeypadBuffer>'1'&&private_uint8KeypadBuffer< '5'){

			uint8 local_uint8LedChoice = private_uint8KeypadBuffer;
			LCD_voidWriteString("1-Turn off LED");
			LCD_voidGoToLocation(2,0);
			LCD_voidWriteString("2-Turn on LED");
			_delay_ms(1000);
			LCD_voidClearScreen();
			LCD_voidWriteString("> ");
			while(private_uint8KeypadReading==KEYPAD_KEY_NOT_PRESSED);
			private_uint8KeypadBuffer = private_uint8KeypadReading;
			LCD_voidWriteChar(private_uint8KeypadBuffer);

			if(private_uint8KeypadBuffer=='1'){

				if(local_uint8LedChoice=='2'){
					DIO_voidSetPinValue(DIO_PIN_NO_5,DIO_PIN_LOW);
				}
				else if(local_uint8LedChoice=='3'){
					DIO_voidSetPinValue(DIO_PIN_NO_6,DIO_PIN_LOW);
				}
				else if(local_uint8LedChoice=='4'){
					DIO_voidSetPinValue(DIO_PIN_NO_28,DIO_PIN_LOW);
				}

			}
			else if(private_uint8KeypadBuffer=='2'){


				if(local_uint8LedChoice=='2'){
					DIO_voidSetPinValue(DIO_PIN_NO_5,DIO_PIN_HIGH);
				}
				else if(local_uint8LedChoice=='3'){
					DIO_voidSetPinValue(DIO_PIN_NO_6,DIO_PIN_HIGH);
				}
				else if(local_uint8LedChoice=='4'){
					DIO_voidSetPinValue(DIO_PIN_NO_28,DIO_PIN_HIGH);
				}

			}

		}


		break;

	case APP_LOGOUT_CHOICE:


		private_uint8LogInFlag = APP_USER_LOGGED_OUT;

		LCD_voidWriteString("logging out....");
		_delay_ms(1000);

		break;

	}

}
