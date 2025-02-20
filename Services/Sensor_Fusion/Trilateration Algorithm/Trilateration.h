/*
 * Trilateration.h
 *
 *  Created on: Feb 20, 2025
 *      Author: Mostafa Edrees
 */

#ifndef SENSOR_FUSION_TRILATERATION_ALGORITHM_TRILATERATION_H_
#define SENSOR_FUSION_TRILATERATION_ALGORITHM_TRILATERATION_H_

/* Define Point structure */
typedef struct {
    float X_coordinate, Y_coordinate;
} S_Point_Coordinates;

/*------------------------------------------------------*/
/*				Functions Prototypes					*/
/*------------------------------------------------------*/
S_Point_Coordinates Trilateration_Algo(S_Point_Coordinates Copy_strPoint1Coordinates, S_Point_Coordinates Copy_strPoint2Coordinates, S_Point_Coordinates Copy_strPoint3Coordinates,
									double Copy_f64Dis_unkonwn_Point1, double Copy_f64Dis_unkonwn_Point2, double Copy_f64Dis_unkonwn_Point3);

#endif /* SENSOR_FUSION_TRILATERATION_ALGORITHM_TRILATERATION_H_ */
