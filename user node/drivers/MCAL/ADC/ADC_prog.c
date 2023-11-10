/********************************************/
/*  author: Mohamed Walid               	*/
/*  version: V01                            */
/*  Date: 7 AUG 2023 	  					*/
/*  SWC : ADC                   			*/
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_int.h"
#include "ADC_config.h"
#include "ADC_priv.h"
#include "ADC_reg.h"

static uint16* ADC_puint16ConversionResult = NULL;
static void (*ADC_pfvoidCallBackFunc) (void);

static uint8 ADC_uint8BusyState = IDLE;

void ADC_voidInit(void){
	
#if ADC_REF_VOLTAGE_CHOICE==ADC_AREF_REF_VOLTAGE

	CLEAR_BIT(ADMUX,ADC_REFS0);
	CLEAR_BIT(ADMUX,ADC_REFS1);

#elif ADC_REF_VOLTAGE_CHOICE==ADC_AVCC_REF_VOLTAGE

	CLEAR_BIT(ADMUX,ADC_REFS0);
	SET_BIT(ADMUX,ADC_REFS1);

#elif ADC_REF_VOLTAGE_CHOICE==ADC_INTERNAL_REF_VOLTAGE

	SET_BIT(ADMUX,ADC_REFS0);
	SET_BIT(ADMUX,ADC_REFS1);


#endif
	
#if ADC_RESOLUTION_CHOICE==ADC_10BIT_RESOLUTION_CHOICE

	CLEAR_BIT(ADMUX,ADC_ADLAR);

#elif ADC_RESOLUTION_CHOICE==ADC_8BIT_RESOLUTION_CHOICE

	SET_BIT(ADMUX,ADC_ADLAR);

#endif
	
#if ADC_AUTO_TRIGGER_OPTION==ADC_AUTO_TRIGGER_DISABLE

	CLEAR_BIT(ADCSRA,ADC_ADATE);			// single conversion mode

#elif ADC_AUTO_TRIGGER_OPTION==ADC_AUTO_TRIGGER_ENABLE

	SET_BIT(ADCSRA,ADC_ADATE);

	SFIOR &= ADC_SFIOR_AUTO_TRIGGER_MASK;
	SFIOR |= (ADC_AUTO_TRIGGER_SOURCE<<5);

#endif


	ADCSRA &= ADC_ADCSRA_PRESACLER_MASK;		// setting the prescaler using the selected value
	ADCSRA |= ADC_PRESCALER_VALUE;

	SET_BIT(ADCSRA, ADC_ADEN);		// Enabling ADC by default
}


uint8 ADC_uint8StartConversionSynch(ADC_structConversionParam * copyPSconversionInputs){

	uint8 local_uint8ErrorStatus = OK;

	if(ADC_uint8BusyState == IDLE){

		ADC_uint8BusyState = BUSY;

		if(copyPSconversionInputs != NULL){

			uint32 local_uint32Counter = ADC_TIMEOUT_VALUE;

			ADMUX &= ADC_ADMUX_CHANNEL_MASK;
			ADMUX |= copyPSconversionInputs->copy_uint8Channel;				// channel selection setting

			if(copyPSconversionInputs->copy_uint8ConvResolution == ADC_8BIT_RESOLUTION_CHOICE){

				SET_BIT(ADMUX, ADC_ADLAR);
			}
			else if(copyPSconversionInputs->copy_uint8ConvResolution == ADC_10BIT_RESOLUTION_CHOICE){

				CLEAR_BIT(ADMUX, ADC_ADLAR);
			}

			SET_BIT(ADCSRA, ADC_ADSC);		// starting conversion

			while(GET_BIT(ADCSRA, ADC_ADIF)==0 && local_uint32Counter!=0 ){

				local_uint32Counter--;
			}
			if(local_uint32Counter != 0 ){

				SET_BIT(ADCSRA, ADC_ADIF);		// clearing the ADC CC flag

				if(copyPSconversionInputs->copy_uint8ConvResolution == ADC_8BIT_RESOLUTION_CHOICE){

					copyPSconversionInputs->copy_puint16Result = ADCH;
				}
				else if(copyPSconversionInputs->copy_uint8ConvResolution == ADC_10BIT_RESOLUTION_CHOICE){

					copyPSconversionInputs->copy_puint16Result = ADCL_16BIT;
				}
			}else{

				local_uint8ErrorStatus = NOK;
			}
		}
		else{
			local_uint8ErrorStatus = NOK;
		}
		ADC_uint8BusyState = IDLE;
	}
	else if(ADC_uint8BusyState==BUSY){

		local_uint8ErrorStatus = NOK;
	}

	return local_uint8ErrorStatus;
}


uint8 ADC_uint8StartCovnersionAsynch(ADC_structConversionParam * copyPSconversionInputs, void (*copy_pfvoidNotifictaionFunc)(void) ){

	uint8 local_uint8ErrorStatus = OK;

	if(ADC_uint8BusyState == IDLE){

		ADC_uint8BusyState = BUSY;

		if(copyPSconversionInputs != NULL && copy_pfvoidNotifictaionFunc != NULL){

			ADMUX &= ADC_ADMUX_CHANNEL_MASK;
			ADMUX |= copyPSconversionInputs->copy_uint8Channel;				// channel selection setting

			if(copyPSconversionInputs->copy_uint8ConvResolution == ADC_8BIT_RESOLUTION_CHOICE){

				SET_BIT(ADMUX, ADC_ADLAR);
			}
			else if(copyPSconversionInputs->copy_uint8ConvResolution == ADC_10BIT_RESOLUTION_CHOICE){

				CLEAR_BIT(ADMUX, ADC_ADLAR);
			}

			ADC_pfvoidCallBackFunc = copy_pfvoidNotifictaionFunc;		// setting the callback function
			ADC_puint16ConversionResult = &(copyPSconversionInputs->copy_puint16Result);


			SET_BIT(ADCSRA, ADC_ADIE);		// Enabling interrupt

			SET_BIT(ADCSRA, ADC_ADSC);		// starting conversion

		}
		else{

			local_uint8ErrorStatus = NOK;
		}
		ADC_uint8BusyState = IDLE;
	}
	else if(ADC_uint8BusyState==BUSY){

		local_uint8ErrorStatus = NOK;
	}

	return local_uint8ErrorStatus;
}


void ADC_voidDisable(void){

	CLEAR_BIT(ADCSRA, ADC_ADEN);
}

void ADC_voidEnable(void){

	SET_BIT(ADCSRA, ADC_ADEN);

}

void __vector_16(void)		__attribute__((signal));

void __vector_16(void){

	if(GET_BIT(ADMUX,ADC_ADLAR)==1){

		*ADC_puint16ConversionResult = ADCH;
	}
	else if(GET_BIT(ADMUX,ADC_ADLAR)==0){

		*ADC_puint16ConversionResult = ADCL_16BIT;
	}

	ADC_pfvoidCallBackFunc();

	CLEAR_BIT(ADCSRA, ADC_ADIE);		// Disable interrupt

}

