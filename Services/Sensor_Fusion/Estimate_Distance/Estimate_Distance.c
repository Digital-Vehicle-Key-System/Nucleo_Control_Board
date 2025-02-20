/*
 * Estimate_Distance.c
 *
 *  Created on: Feb 20, 2025
 *      Author: Mostafa Edrees
 */

#include <stdint.h>

#include "../../Math/Math_Functions.h"
#include "Estimate_Distance.h"

double Convert_RSSI_Into_Distance(int8_t Copy_s8RSSIvalue)
{
	double Local_f64Distance = 0.0, Local_f64Exponent = 0.0;

	Local_f64Exponent = (RSSI_ONE_METER - Copy_s8RSSIvalue)/(10.0f * PATH_LOSS_EXPONENT);
	Local_f64Distance = pow_fun(10, Local_f64Exponent);

	return Local_f64Distance;
}
