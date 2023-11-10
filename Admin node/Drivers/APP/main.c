/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 6 NOV 2023                       */
/*  SWC: APP                                */
/********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_int.h"
#include "DIO_int.h"
#include "UART_int.h"
#include "GI_int.h"
#include "SPI_int.h"
#include "TWI_Interface.h"
#include "EEPROM_Interface.h"
#include <util/delay.h>


#define 	APP_ADMIN_PASS_SIZE			8
#define 	APP_USER_PASS_SIZE			8
#define 	APP_USER_ID_SIZE			8
#define     APP_OPTION_ADD_USER        '1'
#define     APP_OPTION_EDIT_USER       '2'
#define     APP_OPTION_DELETE_USER     '3'
#define		APP_SWITCH_TO_USER_MODE    '4'

#define     APP_OPERATION_STATUS_SUCCESS	2
#define     APP_OPERATION_STATUS_FAILURE	4
#define 	APP_NO_DATA_RECEIVED			6
#define		APP_BYTE_RECEIVED				8


#define		APP_USER_ID_EXIST			10
#define		APP_USER_ID_NOT_EXIST		30

#define		APP_USER_ID_UNAVAILABLE		0
#define     APP_USER_PASS_MISMATCH      0

#define		APP_USER_PASS_CORRECT		    10
#define		APP_USER_PASS_INCORRECT		    30

#define 	APP_RECEIVE_USER_ID         0x55
#define 	APP_RECEIVE_USER_PASS       0x66

#define 	APP_DATA_ACK 				40
#define		APP_DATA_NACK				50

#define		APP_DUMMY_DATA_1				0x90
#define		APP_DUMMY_DATA_2				0x80

#define     NUMBER_OF_USER         32
#define     PASSWORD_LENGTH         9
#define     USER_COUNT_LOCATION     1000
#define     USER_ID_LENGTH          9
#define     USER_ID_LOCATION        32
#define     USER_PASSWORD_LOCATION  528

volatile uint8 UserCount=0;
uint8 Command;



uint8 Add_User(char *User_ID,char *User_Password);
uint8 Edit_user(char *User_ID,char *User_Password);
uint8 Delete_user(char *User_ID);
uint8 Check_user_ID(char *User_ID);								// Checks ID
uint8 Check_user_Password(char *User_ID,char *User_Password);



void APP_voidDisplayAdmin(void);

uint8 APP_uint8GetAdminChoice(void);

void APP_uint8ExecuteAdminChoice(uint8 copy_uint8Choice);

void APP_voidReceiveFunc(uint8 copy_uint8ReceivedByte);


void main(void){

	PORT_voidInit();
	UART_voidInit();
	GI_voidEnable();
	SPI_voidInit();
	EEPROM_voidInit();


	uint8 local_uint8CorrectAdminPassFlag=1,local_uint8AdminChoice=0;
    uint8 local_uint8AdminPass[APP_ADMIN_PASS_SIZE+1]={'0','0','0','0','0','0','0','0','\0'};			// predefined Admin password
    uint8 local_uint8InputAdminPass[APP_ADMIN_PASS_SIZE+1]={0};

    do{

		UART_voidSendString("Enter Password:\n");
		UART_uint8ReceiveString(local_uint8InputAdminPass, APP_ADMIN_PASS_SIZE);
		UART_voidSendChar('\n');
		for(uint8 i=0;i<APP_ADMIN_PASS_SIZE;i++){

			if(local_uint8InputAdminPass[i]!=local_uint8AdminPass[i]){				// check Admin pass

				local_uint8CorrectAdminPassFlag = 0;
				UART_voidSendString("Wrong password entry!!\n");
				break;
			}
			local_uint8CorrectAdminPassFlag=1;
		}

    }while(local_uint8CorrectAdminPassFlag==0);

    APP_voidDisplayAdmin();
    UART_voidSendString("Access granted");

    SPI_uint8TransmitAsynch(APP_DUMMY_DATA_1, &APP_voidReceiveFunc);			// Preparing SPI Asynch communication

	EEPROM_voidWriteByte(0,USER_COUNT_LOCATION);

	EEPROM_voidReadByte(&UserCount,USER_COUNT_LOCATION);

	while(1){

			local_uint8AdminChoice = APP_uint8GetAdminChoice();					// no data transmitted from user node

			APP_uint8ExecuteAdminChoice(local_uint8AdminChoice);

	}


}



uint8 Add_User(char *User_ID,char *User_Password)
{
	uint8 VerificationByte=0xFF;
	uint16 LocationsCount=0;
	uint8 user_exist=0;
	if(UserCount!=0)
	{
		user_exist=Check_user_ID(User_ID);
	}
	/*User ID EXIST */
	if ((user_exist==0))
	{
		EEPROM_voidReadByte(&VerificationByte, USER_ID_LOCATION+USER_ID_LENGTH*LocationsCount);
		while(VerificationByte!=0xFF)
		{
			LocationsCount++;
			EEPROM_voidReadByte(&VerificationByte, USER_ID_LOCATION+USER_ID_LENGTH*LocationsCount);
		}

		for (int i=0;i<USER_ID_LENGTH;i++)
		{
			EEPROM_voidWriteByte(User_ID[i],(USER_ID_LOCATION+USER_ID_LENGTH*LocationsCount)+i);
		}
		for (int i=0;i<PASSWORD_LENGTH;i++)
		{
			EEPROM_voidWriteByte(User_Password[i],(USER_PASSWORD_LOCATION+PASSWORD_LENGTH*LocationsCount)+i);
		}
		UserCount++;
		EEPROM_voidWriteByte(UserCount, USER_COUNT_LOCATION);
		return 1;
	}
	else
	{
		return 0;
	}


}

uint8 Check_user_ID(char *User_ID)
{
	char ExistingUser[16];
	char ID_EXIST=0;
	uint16 ID_ADDRESS;
	uint8 i=0;
	uint8 count=0;
	for(i=0;i<NUMBER_OF_USER;i++)
	{
		EEPROM_voidReadSequential(ExistingUser,USER_ID_LOCATION+(USER_ID_LENGTH*i), USER_ID_LENGTH);
		if(0==strcmp(ExistingUser,User_ID))
		{
			count=i;
			ID_EXIST=1;
			break;
		}
	}
	if(1==ID_EXIST)
	{

		ID_ADDRESS=USER_ID_LOCATION+USER_ID_LENGTH*count;
	}
	else
	{
		ID_ADDRESS=0;
	}
	return ID_ADDRESS;
}
uint8 Edit_user(char *User_ID,char *User_Password)
{
	uint16 user_exist=Check_user_ID(User_ID);
	if(user_exist!=0)
	{
		//EEPROM_voidWritePage(User_Password,user_exist+(USER_PASSWORD_LOCATION-USER_ID_LOCATION));

		for (int i=0;i<PASSWORD_LENGTH;i++)
		{
			EEPROM_voidWriteByte(User_Password[i],user_exist+(USER_PASSWORD_LOCATION-USER_ID_LOCATION)+i);
		}
	}
	return user_exist;
}

uint8 Delete_user(char *User_ID)
{

	uint16 user_exist=Check_user_ID(User_ID);
	if(user_exist!=0)
	{
		//EEPROM_voidWritePage(User_Password,user_exist+(USER_PASSWORD_LOCATION-USER_ID_LOCATION));
		for(int i=0;i<USER_ID_LENGTH;i++)
		{
			EEPROM_voidWriteByte(0xFF,user_exist+i);
		}
		for (int i=0;i<PASSWORD_LENGTH;i++)
		{
			EEPROM_voidWriteByte(0xFF,user_exist+(USER_PASSWORD_LOCATION-USER_ID_LOCATION)+i);
		}
	}
	UserCount--;
	EEPROM_voidWriteByte(UserCount, USER_COUNT_LOCATION);
	return user_exist;
}



uint8  Check_user_Password(char *User_ID,char *User_Password)
{
	uint16 user_exist=Check_user_ID(User_ID);
	if(user_exist!=0)
	{
		//EEPROM_voidWritePage(User_Password,user_exist+(USER_PASSWORD_LOCATION-USER_ID_LOCATION));
		char  read_user_password[9];
		EEPROM_voidReadSequential(read_user_password, user_exist+(USER_PASSWORD_LOCATION-USER_ID_LOCATION),PASSWORD_LENGTH);
		if(0==strcmp(read_user_password,User_Password))
		{
			user_exist=1;

		}
		else{

			user_exist=0;
		}
	}
	return user_exist;

}




void APP_voidDisplayAdmin(void){

	UART_voidSendString("Admin: ");

}

uint8 APP_uint8GetAdminChoice(void){

	uint8 local_uint8AdminChoice;

	UART_voidSendChar('\n');
	UART_voidSendChar('\n');

    APP_voidDisplayAdmin();
    UART_voidSendString("Available options:\n");
    APP_voidDisplayAdmin();
    UART_voidSendString("  1-Add user\n");
    APP_voidDisplayAdmin();
    UART_voidSendString("  2-Edit user\n");
    APP_voidDisplayAdmin();
    UART_voidSendString("  3-Delete user\n");
    APP_voidDisplayAdmin();
    UART_voidSendString("  4-Switch to user mode\n");
    APP_voidDisplayAdmin();
    UART_voidSendString("\nEnter your choice: ");
    UART_uint8ReceiveString(&local_uint8AdminChoice,1);

    while(local_uint8AdminChoice<'1'||local_uint8AdminChoice>'4'){

    	UART_voidSendChar('\n');
        APP_voidDisplayAdmin();
        UART_voidSendString("Wrong entry!\n");
        APP_voidDisplayAdmin();
        UART_voidSendString("Try again\n");
        APP_voidDisplayAdmin();
        UART_uint8ReceiveString(&local_uint8AdminChoice,1);
    }

    return local_uint8AdminChoice;

}

void APP_uint8ExecuteAdminChoice(uint8 copy_uint8Choice){

	uint8 local_uint8UserID[APP_USER_ID_SIZE+1], local_uint8UserPass[APP_USER_PASS_SIZE+1];
	uint8 local_uint8UserIdStatus=1, local_uint8PassStatus, local_uint8UserInput;

	UART_voidSendChar('\n');

	switch(copy_uint8Choice){

		case APP_OPTION_ADD_USER:

			APP_voidDisplayAdmin();
			UART_voidSendString("Enter user ID:\n");
			APP_voidDisplayAdmin();
			UART_uint8ReceiveString(local_uint8UserID,APP_USER_ID_SIZE);
			// check ID in eeprom

			local_uint8UserIdStatus=Check_user_ID(local_uint8UserID);


			// if ID already exists in EEPROM
			if(local_uint8UserIdStatus!=APP_USER_ID_UNAVAILABLE){

				UART_voidSendChar('\n');
				APP_voidDisplayAdmin();
				UART_voidSendString("ID already exists!!\n");
				APP_voidDisplayAdmin();

				UART_voidSendString("Try another ID\n");

				break;
			}
			UART_voidSendChar('\n');
			APP_voidDisplayAdmin();
			UART_voidSendString("Enter user password:\n");
			APP_voidDisplayAdmin();
			UART_uint8ReceiveString(local_uint8UserPass,APP_USER_PASS_SIZE);
			// Save in eeprom
			Add_User(local_uint8UserID,local_uint8UserPass);

			UART_voidSendChar('\n');
			APP_voidDisplayAdmin();
			UART_voidSendString("Operation success");

			break;

		case APP_OPTION_EDIT_USER:

			APP_voidDisplayAdmin();
			UART_voidSendString("Enter user ID:\n");
			APP_voidDisplayAdmin();
			UART_uint8ReceiveString(local_uint8UserID,APP_USER_ID_SIZE);
			// check ID in eeprom

			local_uint8UserIdStatus = Check_user_ID(local_uint8UserID);

			// if ID doesn't exist in the EEPROM

			if(local_uint8UserIdStatus==APP_USER_ID_UNAVAILABLE){

				UART_voidSendChar('\n');
				APP_voidDisplayAdmin();
				UART_voidSendString("ID doesn't exist!!\n");
				APP_voidDisplayAdmin();

				UART_voidSendString("Try again\n");

				break;

			}
			UART_voidSendChar('\n');
			APP_voidDisplayAdmin();
			UART_voidSendString("Enter new user password:\n");
			APP_voidDisplayAdmin();
			UART_uint8ReceiveString(local_uint8UserPass,APP_USER_PASS_SIZE);
			// edit PASS in eeprom
			Edit_user(local_uint8UserID, local_uint8UserPass);

			UART_voidSendChar('\n');
			APP_voidDisplayAdmin();
			UART_voidSendString("Operation success");


			break;

		case APP_OPTION_DELETE_USER:

			APP_voidDisplayAdmin();
			UART_voidSendString("Enter user ID:\n");
			APP_voidDisplayAdmin();
			UART_uint8ReceiveString(local_uint8UserID,APP_USER_ID_SIZE);
			// check ID in eeprom

			local_uint8UserIdStatus = Check_user_ID(local_uint8UserID);

			// if ID doesn't exist in the EEPROM

			if(local_uint8UserIdStatus==APP_USER_ID_UNAVAILABLE){

				UART_voidSendChar('\n');
				APP_voidDisplayAdmin();
				UART_voidSendString("ID doesn't exist!!\n");
				APP_voidDisplayAdmin();

				UART_voidSendString("Try again\n");

				break;
			}

			// delete ID and PASS in eeprom
			Delete_user(local_uint8UserID);

			UART_voidSendChar('\n');
			APP_voidDisplayAdmin();
			UART_voidSendString("Operation success");

			break;

		case APP_SWITCH_TO_USER_MODE:

			UART_voidSendString("User: User mode activated\n");
			UART_voidSendString("User: to switch back to Admin Mode, Press \'A\'");

			uint8 local_uint8ReceivedData;

			do{

				UART_voidSendString("\nUser: ");
				UART_uint8ReceiveString(&local_uint8ReceivedData,1);

			}while('A'!=local_uint8ReceivedData);

			UART_voidSendString("\nAdmin: Admin mode activated");

			break;

    }

}

void APP_voidReceiveFunc(uint8 copy_uint8ReceivedByte){

	static uint8 type, IDIdx = 0, PASSIdx=0, ID[9], PASS[9], local_uint8PassStatus, local_uint8IdStatus;

    if (copy_uint8ReceivedByte == 0x55 && type == 0)
    {
        type  = 1;    // ID
        IDIdx = 0;
    }
    else if (copy_uint8ReceivedByte == 0x66 && type == 0)
    {
        type    = 2;    // PASSWORD
        PASSIdx = 0;
    }
    else if (type == 1)
    {
        ID[IDIdx] = copy_uint8ReceivedByte;
        IDIdx++;

        if (IDIdx == 8)
        {
            type  = 0;
            ID[8] = '\0';
            //UART_voidSendString(ID);
            local_uint8IdStatus = Check_user_ID(ID);
            if(local_uint8IdStatus==APP_USER_ID_UNAVAILABLE){

            	SPI_uint8TransmitAsynch(APP_USER_ID_NOT_EXIST,APP_voidReceiveFunc);
            }
            else{
            	SPI_uint8TransmitAsynch(APP_USER_ID_EXIST, APP_voidReceiveFunc);

            }
        }
    }
    else if (type == 2)
    {
        PASS[PASSIdx] = copy_uint8ReceivedByte;
        PASSIdx++;

        if (PASSIdx == 8)
        {
            type    = 0;
            PASS[8] = '\0';

           // UART_voidSendString(PASS);

            local_uint8PassStatus = Check_user_Password(ID, PASS);

            if(local_uint8PassStatus==APP_USER_PASS_MISMATCH){

            //	UART_voidSendString("APP_USER_PASS_INCORRECT");
            	SPI_uint8TransmitAsynch(APP_USER_PASS_INCORRECT, APP_voidReceiveFunc);
            }
            else{
            //	UART_voidSendString("APP_USER_PASS_CORRECT");
            	SPI_uint8TransmitAsynch(APP_USER_PASS_CORRECT, APP_voidReceiveFunc);

            }

        }
    }

    else if (type == 0 && copy_uint8ReceivedByte == APP_DUMMY_DATA_1)
    {
        if(local_uint8IdStatus==APP_USER_ID_UNAVAILABLE){

        	SPI_uint8TransmitAsynch(APP_USER_ID_NOT_EXIST,APP_voidReceiveFunc);
        }
        else{
        	SPI_uint8TransmitAsynch(APP_USER_ID_EXIST, APP_voidReceiveFunc);

        }
    }
    else if (type == 0 && copy_uint8ReceivedByte == APP_DUMMY_DATA_2)
    {

        if(local_uint8PassStatus==APP_USER_PASS_MISMATCH){

        	SPI_uint8TransmitAsynch(APP_USER_PASS_INCORRECT, APP_voidReceiveFunc);
        }
        else{
        	SPI_uint8TransmitAsynch(APP_USER_PASS_CORRECT, APP_voidReceiveFunc);

        }

    }

}

