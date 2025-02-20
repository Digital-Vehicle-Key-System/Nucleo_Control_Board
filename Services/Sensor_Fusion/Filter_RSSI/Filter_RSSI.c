/*
 * Filter_RSSI.c
 *
 *  Created on: Feb 20, 2025
 *      Author: Mostafa Edrees
 */

#include <stdint.h>

#include <main.h>

#include "../../Math/Math_Functions.h"
#include "Filter_RSSI.h"

void RSSI_AverageFilter_updateRSSIvalue(int8_t *Copy_As8RSSIRawValues, int8_t *Copy_Ps8RSSIFilteredValue)
{
    if(Copy_As8RSSIRawValues == NULL || Copy_Ps8RSSIFilteredValue == NULL)
    {
    	Error_Handler();
    }

    *Copy_Ps8RSSIFilteredValue = 0;
    for (uint8_t i = 0; i < FILTER_SIZE; i++)
    {
    	*Copy_Ps8RSSIFilteredValue += Copy_As8RSSIRawValues[i];
    }

    *Copy_Ps8RSSIFilteredValue /= FILTER_SIZE;
}

void RSSI_FilterItsValues(int8_t Copy_s8RSSIRawValue, int8_t *Copy_Ps8RSSIFilteredValue)
{
	/* apply kalman filter */
}
