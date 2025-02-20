/*
 * Trilateration.c
 *
 *  Created on: Feb 20, 2025
 *      Author: Mostafa Edrees
 */

#include <stdint.h>
#include <stddef.h>

#include <main.h>

#include "../../Math/Math_Functions.h"

#include "Trilateration.h"


static float norm(S_Point_Coordinates Copy_strPoint_Coordinates)
{
	return sqrt_fun(pow_fun(Copy_strPoint_Coordinates.X_coordinate, 2) + pow_fun(Copy_strPoint_Coordinates.Y_coordinate, 2));
}


/**
  * @brief Trilateration Algorithm Function
  * @param Copy_strPoint1Coordinates coordinates of the 1st known point
  * @param Copy_strPoint2Coordinates coordinates of the 2nd known point
  * @param Copy_strPoint3Coordinates coordinates of the 3rd known point
  * @param Copy_f64Dis_unkonwn_Point1 distance between the unknown point and the 1st known point
  * @param Copy_f64Dis_unkonwn_Point2 distance between the unknown point and the 2nd known point
  * @param Copy_f64Dis_unkonwn_Point3 distance between the unknown point and the 3rd known point
  * @retval The coordinates of the unknown point
  */
S_Point_Coordinates Trilateration_Algo(S_Point_Coordinates Copy_strPoint1Coordinates, S_Point_Coordinates Copy_strPoint2Coordinates, S_Point_Coordinates Copy_strPoint3Coordinates,
									double Copy_f64Dis_unkonwn_Point1, double Copy_f64Dis_unkonwn_Point2, double Copy_f64Dis_unkonwn_Point3)
{
	S_Point_Coordinates Local_strResultPositionCoordinates;

    /* Unit vector in a direction from point1 to point2 */
    double Local_f64Distance_P2P1 = sqrt_fun(pow_fun(Copy_strPoint2Coordinates.X_coordinate - Copy_strPoint1Coordinates.X_coordinate, 2) + pow_fun(Copy_strPoint2Coordinates.Y_coordinate - Copy_strPoint1Coordinates.Y_coordinate, 2));
    S_Point_Coordinates ex = {(Copy_strPoint2Coordinates.X_coordinate - Copy_strPoint1Coordinates.X_coordinate) / Local_f64Distance_P2P1, (Copy_strPoint2Coordinates.Y_coordinate - Copy_strPoint1Coordinates.Y_coordinate) / Local_f64Distance_P2P1};
    S_Point_Coordinates aux = {Copy_strPoint3Coordinates.X_coordinate - Copy_strPoint1Coordinates.X_coordinate, Copy_strPoint3Coordinates.Y_coordinate - Copy_strPoint1Coordinates.Y_coordinate};

    /* Signed magnitude of the x component */
    double i = ex.X_coordinate * aux.X_coordinate + ex.Y_coordinate * aux.Y_coordinate;

    /* The unit vector in the y direction */
    S_Point_Coordinates aux2 = {Copy_strPoint3Coordinates.X_coordinate - Copy_strPoint1Coordinates.X_coordinate - i * ex.X_coordinate, Copy_strPoint3Coordinates.Y_coordinate - Copy_strPoint1Coordinates.Y_coordinate - i * ex.Y_coordinate};
    S_Point_Coordinates ey = {aux2.X_coordinate / norm(aux2), aux2.Y_coordinate / norm(aux2)};

    /* Signed magnitude of the y component */
    double j = ey.X_coordinate * aux.X_coordinate + ey.Y_coordinate * aux.Y_coordinate;

    /* Coordinates */
    double x = (pow_fun(Copy_f64Dis_unkonwn_Point1, 2) - pow_fun(Copy_f64Dis_unkonwn_Point2, 2) + pow_fun(Local_f64Distance_P2P1, 2)) / (2 * Local_f64Distance_P2P1);
    double y = (pow_fun(Copy_f64Dis_unkonwn_Point1, 2) - pow_fun(Copy_f64Dis_unkonwn_Point3, 2) + pow_fun(i, 2) + pow(j, 2)) / (2 * j) - (i * x) / j;

    /* Result coordinates */
    Local_strResultPositionCoordinates.X_coordinate = Copy_strPoint1Coordinates.X_coordinate + x * ex.X_coordinate + y * ey.X_coordinate;
    Local_strResultPositionCoordinates.Y_coordinate = Copy_strPoint1Coordinates.Y_coordinate + x * ex.Y_coordinate + y * ey.Y_coordinate;

    return Local_strResultPositionCoordinates;
}
