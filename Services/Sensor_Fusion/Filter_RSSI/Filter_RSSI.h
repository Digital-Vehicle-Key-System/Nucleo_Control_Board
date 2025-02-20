/*
 * Filter_RSSI.h
 *
 *  Created on: Feb 20, 2025
 *      Author: Mostafa Edrees
 */

#ifndef SENSOR_FUSION_FILTER_RSSI_FILTER_RSSI_H_
#define SENSOR_FUSION_FILTER_RSSI_FILTER_RSSI_H_

#define FILTER_SIZE 				8

void RSSI_AverageFilter_updateRSSIvalue(int8_t *Copy_As8RSSIRawValues, int8_t *Copy_Ps8RSSIFilteredValue);

void RSSI_FilterItsValues(int8_t Copy_s8RSSIRawValue, int8_t *Copy_Ps8RSSIFilteredValue);

#endif /* SENSOR_FUSION_FILTER_RSSI_FILTER_RSSI_H_ */
