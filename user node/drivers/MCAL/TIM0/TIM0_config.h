/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V02                            */
/*  Date: 26 OCT 2023	   					*/
/*  SWC : TIM0                   			*/
/********************************************/

#ifndef		TIM0_CONFIG_H
#define 	TIM0_CONFIG_H

#define		CPU_FREQ_IN_KHZ			8000



/* you can choose between:-
 *
 *	 TIM0_NORMAL_MODE						
 *	 TIM0_CTC_MODE								
 *	 TIM0_FAST_PWM_MODE					
 *	 TIM0_PHASE_CORRECT_PWM_MODE
 *
 */


#define 	TIM0_MODE 		TIM0_CTC_MODE


#if 	TIM0_MODE == TIM0_FAST_PWM_MODE || TIM0_MODE == TIM0_PHASE_CORRECT_PWM_MODE

/*
 * Options :
 * 		TIM0_PWM_INVERTED
 * 		TIM0_PWM_NON_INVERTED
 *
 */

#define 	TIM0_PWM_MODE	TIM0_PWM_INVERTED


#endif




/* you can choose between:-
 *
 *	TIM0_PRESCALER_CLK_IO_BY_1
 *	TIM0_PRESCALER_CLK_IO_BY_8
 *	TIM0_PRESCALER_CLK_IO_BY_64
 *	TIM0_PRESCALER_CLK_IO_BY_256
 *	TIM0_PRESCALER_CLK_IO_BY_1024
 *	TIM0_PRESCALER_EXTERNAL_CLK_FALLING_EDGE
 *	TIM0_PRESCALER_EXTERNAL_CLK_RISING_EDGE	
 */


#define 	TIM0_PRESCALER_CHOICE		TIM0_PRESCALER_CLK_IO_BY_1024


#if	TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_1

#define	TIM0_TICK_TIME_INVERSE	CPU_FREQ_IN_KHZ/TIM0_CLK_PRESCALER_1

#elif TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_8

#define	TIM0_TICK_TIME_INVERSE	CPU_FREQ_IN_KHZ/TIM0_CLK_PRESCALER_8


#elif TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_64

#define	TIM0_TICK_TIME_INVERSE	CPU_FREQ_IN_KHZ/TIM0_CLK_PRESCALER_64


#elif TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_256

#define	TIM0_TICK_TIME_INVERSE	CPU_FREQ_IN_KHZ/TIM0_CLK_PRESCALER_256


#elif TIM0_PRESCALER_CHOICE==TIM0_PRESCALER_CLK_IO_BY_1024

#define	TIM0_TICK_TIME_INVERSE	CPU_FREQ_IN_KHZ/TIM0_CLK_PRESCALER_1024


#endif




#endif
