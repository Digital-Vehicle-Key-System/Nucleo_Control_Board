/*
 * Math_Functions.c
 *
 *  Created on: Feb 20, 2025
 *      Author: Mostafa Edrees
 */

#include "Math_Functions.h"

double sqrt_fun(double Copy_f64Number)
{
    if (Copy_f64Number < 0)
    {
    	/* Return -1 to indicate an error for negative inputs */
        return -1;
    }

    if (Copy_f64Number == 0 || Copy_f64Number == 1)
    {
    	/* The square root of 0 or 1 is itself */
        return Copy_f64Number;
    }

    double Local_f64Guess = Copy_f64Number / 2.0;
    double Local_f64Epsilon = 0.000001;  // Precision level

    while ((Local_f64Guess * Local_f64Guess - Copy_f64Number) > Local_f64Epsilon || (Local_f64Guess * Local_f64Guess - Copy_f64Number) < -Local_f64Epsilon) {
    	Local_f64Guess = (Local_f64Guess + Copy_f64Number / Local_f64Guess) / 2.0;
    }

    return Local_f64Guess;
}

double pow_fun(double Copy_f64BaseNum, int Copy_s32ExponentNum)
{
    double Local_f65Result = 1.0;
    int Local_s32PositiveExponent = Copy_s32ExponentNum < 0 ? -Copy_s32ExponentNum : Copy_s32ExponentNum;
    int Local_s32Iterator = 0;

    /* Multiply `result` by `base` positive_exponent times */
    for (int Local_s32Iterator = 0; Local_s32Iterator < Local_s32PositiveExponent; Local_s32Iterator++) {
    	Local_f65Result *= Copy_f64BaseNum;
    }

    /* If the exponent was negative, invert the result */
    if (Copy_s32ExponentNum < 0) {
    	Local_f65Result = 1.0 / Local_f65Result;
    }

    return Local_f65Result;
}
