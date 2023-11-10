/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 7 AUG 2023 	  					*/
/*  SWC : ADC                   			*/
/********************************************/

#ifndef		ADC_PRIV_H
#define 	ADC_PRIV_H

#define		ADC_AREF_REF_VOLTAGE                1
#define		ADC_AVCC_REF_VOLTAGE                2
#define		ADC_INTERNAL_REF_VOLTAGE            3

#define		ADC_DIVISION_BY_2_CHOICE			1
#define		ADC_DIVISION_BY_4_CHOICE            2
#define		ADC_DIVISION_BY_8_CHOICE            3
#define		ADC_DIVISION_BY_16_CHOICE           4
#define		ADC_DIVISION_BY_32_CHOICE           5
#define		ADC_DIVISION_BY_64_CHOICE           6
#define		ADC_DIVISION_BY_128_CHOICE          7

#define		ADC_AUTO_TRIGGER_ENABLE				1
#define		ADC_AUTO_TRIGGER_DISABLE			2


#define		ADC_FREE_RUNNING_MODE				 0
#define		ADC_ANALOG_COMPARATOR_AT_SRC         1
#define		ADC_EXTI0_AT_SRC                     2
#define		ADC_TIMER0_COMPARE_MATCH_AT_SRC      3
#define		ADC_TIMER0_OVERFLOW_AT_SRC           4
#define		ADC_TIMER_COMPARE_MATCH_B_AT_SRC     5
#define		ADC_TIMER1_OVERFLOW_AT_SRC           6
#define		ADC_TIMER1_CAPTURE_EVENT_AT_SRC      7


#define 	ADC_ADCSRA_PRESACLER_MASK				0xF8

#define		ADC_SFIOR_AUTO_TRIGGER_MASK				0x1F

#define 	ADC_ADMUX_CHANNEL_MASK					0xE0

#define 	OK				1
#define 	NOK				2

#define 	ADC_TIMEOUT_VALUE			80000

#define		IDLE				1
#define 	BUSY				2

#endif
