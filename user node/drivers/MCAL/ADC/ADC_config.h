/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 7 AUG 2023 	  					*/
/*  SWC : ADC                   			*/
/********************************************/

#ifndef		ADC_CONFIG_H
#define 	ADC_CONFIG_H


/*	
 * ADC_REF_VOLTAGE_CHOICE choices :
 * 
 *	ADC_AREF_REF_VOLTAGE    	
 *  ADC_AVCC_REF_VOLTAGE    
 *  ADC_INTERNAL_REF_VOLTAGE
 *
 */
#define 	ADC_REF_VOLTAGE_CHOICE			ADC_AVCC_REF_VOLTAGE


/* ADC_PRESCALER_VALUE choices:
 *
 *	ADC_DIVISION_BY_2_CHOICE	
 *	ADC_DIVISION_BY_4_CHOICE  
 *	ADC_DIVISION_BY_8_CHOICE  
 *	ADC_DIVISION_BY_16_CHOICE 
 *	ADC_DIVISION_BY_32_CHOICE 
 *	ADC_DIVISION_BY_64_CHOICE 
 *	ADC_DIVISION_BY_128_CHOICE
 *
 */
#define 	ADC_PRESCALER_VALUE				ADC_DIVISION_BY_2_CHOICE


/* ADC_AUTO_TRIGGER_OPTION choices :
 *	
 *	ADC_AUTO_TRIGGER_ENABLE	
 *  ADC_AUTO_TRIGGER_DISABLE
 *
 */
#define 	ADC_AUTO_TRIGGER_OPTION			ADC_AUTO_TRIGGER_DISABLE

#if 	ADC_AUTO_TRIGGER_OPTION	== ADC_AUTO_TRIGGER_ENABLE

/* ADC_AUTO_TRIGGER_SOURCE choices :
 *
 *	ADC_FREE_RUNNING_MODE
 *	ADC_ANALOG_COMPARATOR_AT_SRC    
 *  ADC_EXTI0_AT_SRC                
 *  ADC_TIMER0_COMPARE_MATCH_AT_SRC 
 *  ADC_TIMER0_OVERFLOW_AT_SRC      
 *  ADC_TIMER_COMPARE_MATCH_B_AT_SRC
 *  ADC_TIMER1_OVERFLOW_AT_SRC      
 *  ADC_TIMER1_CAPTURE_EVENT_AT_SRC 
 *
 */

#define		ADC_AUTO_TRIGGER_SOURCE		ADC_FREE_RUNNING_MODE

#endif



#endif
