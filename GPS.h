/*
 * GPS.h
 *
 *  Created on: April 30, 2025
 *      Author: Ahmed Assem
 */

#ifndef GPS_H
#define GPS_H
//***********************MACROS*********************

#define MSG_SIZE  					130

#define PARSING_ERROR  			0
#define PARSING_OK					1

#define PI 									3.14159
#define EARTH_RADIUS        6371000.0

#define POINT_IN_QUAD				  1
#define POINT_NOT_IN_QUAD     0

#define MAX_DISTANCE					90000000

//***********************TYPEDEF*********************
typedef struct {
    float utc_time;          // hhmmss.ss
	
    float latitude;          // ddmm.mmmm
    char ns_indicator;          // 'N' or 'S'
    float longitude;         // dddmm.mmmm
    char ew_indicator;          // 'E' or 'W'
	
    int  position_fix;          // 0 = Invalid, 1 = GPS fix, 2 = DGPS fix
	
    int  satellites_used;       // Number of satellites
	
    float hdop;                 // Horizontal Dilution of Precision
    float altitude;             // Altitude value
    char altitude_units;        // 'M' for meters
	
    float geoid_separation;     // Geoid separation
    char geoid_separation_units;// 'M' for meters
	/*
		float a;
		float b;
		float c;
		*/
	
	
} GPS_DATA;


typedef struct {
    float latitude;  
    float longitude;  
} Point_t;

typedef struct {
    char* name;           
    Point_t corners[4];   
} Region_t;

//---------------------------------------------------------
//                        APIs
//---------------------------------------------------------
void 	HAL_GPSRecieveMsg();
char 	HAL_GPSParseMsg(GPS_DATA *data);
float HAL_GPSCalculateDistance(double current_lat , double current_lon , double des_lat , double des_lon);
int Point_In_Quad(Point_t p, Point_t quad[4]);
bool isPointInsideRegion(Point_t point, Point_t corners[4]);
#endif /*GPS_H*/