/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 7 AUG 2023 	  					*/
/*  SWC : ADC                   			*/
/********************************************/


#ifndef		ADC_REG_H
#define 	ADC_REG_H

#define		ADMUX			*((volatile uint8 *) 0x27)

#define 	ADC_REFS1			7
#define 	ADC_REFS0			6
#define 	ADC_ADLAR			5


#define		ADCSRA          *((volatile uint8 *) 0x26)

#define 	ADC_ADEN			7
#define 	ADC_ADSC            6
#define 	ADC_ADATE           5
#define 	ADC_ADIF            4
#define 	ADC_ADIE		    3


#define		ADCH            *((volatile uint8 *) 0x25)
#define		ADCL            *((volatile uint8 *) 0x24)
#define 	ADCL_16BIT		*((volatile uint16 *) 0x24)
#define		SFIOR			*((volatile uint8 *) 0x50)



#endif
