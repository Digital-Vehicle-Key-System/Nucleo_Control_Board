/*
 * Estimate_Distance.h
 *
 *  Created on: Feb 20, 2025
 *      Author: Mostafa Edrees
 */

#ifndef SENSOR_FUSION_ESTIMATE_DISTANCE_ESTIMATE_DISTANCE_H_
#define SENSOR_FUSION_ESTIMATE_DISTANCE_ESTIMATE_DISTANCE_H_

#define RSSI_ONE_METER				-60
#define PATH_LOSS_EXPONENT			2.5f

double Convert_RSSI_Into_Distance(int8_t Copy_s8RSSIRawValue);

#endif /* SENSOR_FUSION_ESTIMATE_DISTANCE_ESTIMATE_DISTANCE_H_ */
