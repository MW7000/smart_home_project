/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 7 AUG 2023 	  					*/
/*  SWC : ADC                   			*/
/********************************************/

#ifndef		ADC_INT_H
#define 	ADC_INT_H


typedef struct { uint16 copy_puint16Result; uint8 copy_uint8Channel; uint8 copy_uint8ConvResolution; } ADC_structConversionParam;

#define		ADC_SINGLE_ENDED_CHANNEL_0                     0
#define		ADC_SINGLE_ENDED_CHANNEL_1                     1
#define		ADC_SINGLE_ENDED_CHANNEL_2                     2
#define		ADC_SINGLE_ENDED_CHANNEL_3                     3
#define		ADC_SINGLE_ENDED_CHANNEL_4                     4
#define		ADC_SINGLE_ENDED_CHANNEL_5                     5
#define		ADC_SINGLE_ENDED_CHANNEL_6                     6
#define		ADC_SINGLE_ENDED_CHANNEL_7                     7
#define		ADC_DIFF_CHS_ADC0_ADC0_GAIN_10X                8
#define		ADC_DIFF_CHS_ADC1_ADC0_GAIN_10X                9
#define		ADC_DIFF_CHS_ADC0_ADC0_GAIN_200X               10
#define		ADC_DIFF_CHS_ADC1_ADC0_GAIN_200X               11
#define		ADC_DIFF_CHS_ADC2_ADC2_GAIN_10X                12
#define		ADC_DIFF_CHS_ADC3_ADC2_GAIN_10X                13
#define		ADC_DIFF_CHS_ADC2_ADC2_GAIN_200X               14
#define		ADC_DIFF_CHS_ADC3_ADC2_GAIN_200X               15
#define		ADC_DIFF_CHS_ADC0_ADC1_GAIN_1X                 16
#define		ADC_DIFF_CHS_ADC1_ADC1_GAIN_1X                 17
#define		ADC_DIFF_CHS_ADC2_ADC1_GAIN_1X                 18
#define		ADC_DIFF_CHS_ADC3_ADC1_GAIN_1X                 19
#define		ADC_DIFF_CHS_ADC4_ADC1_GAIN_1X                 20
#define		ADC_DIFF_CHS_ADC5_ADC1_GAIN_1X                 21
#define		ADC_DIFF_CHS_ADC6_ADC1_GAIN_1X                 22
#define		ADC_DIFF_CHS_ADC7_ADC1_GAIN_1X                 23
#define		ADC_DIFF_CHS_ADC0_ADC2_GAIN_1X                 24
#define		ADC_DIFF_CHS_ADC1_ADC2_GAIN_1X                 25
#define		ADC_DIFF_CHS_ADC2_ADC2_GAIN_1X                 26
#define		ADC_DIFF_CHS_ADC3_ADC2_GAIN_1X                 27
#define		ADC_DIFF_CHS_ADC4_ADC2_GAIN_1X                 28
#define		ADC_DIFF_CHS_ADC5_ADC2_GAIN_1X                 29
#define		ADC_TEST_VOLTAGE                         	   30
#define		ADC_0V_GND_TEST                                31

#define		ADC_8BIT_RESOLUTION_CHOICE			1
#define		ADC_10BIT_RESOLUTION_CHOICE			2

void ADC_voidInit(void);

void ADC_voidDisable(void);

void ADC_voidEnable(void);

/* Parameters :
 * pointer to ADC_structConversionParam type
 */
uint8 ADC_uint8StartConversionSynch(ADC_structConversionParam * copyPSconversionInputs);

/* Parameters :
 * pointer to ADC_structConversionParam type
 * pointer to function
 * important note : you must enable GIE first
 *
 */

uint8 ADC_uint8StartCovnersionAsynch(ADC_structConversionParam * copyPSconversionInputs, void (*copy_pfvoidNotifictaionFunc)(void) );



#endif
