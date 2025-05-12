/*
 * GPS.c
 *
 *  Created on: April 30, 2025
 *      Author: Ahmed Assem (not alone)
 */


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "UART/UART.h"
#include "GPS.H"

int len;
char temp[10];
const char MsgHeader[]="$GPGGA";
char MsgRecieved[MSG_SIZE]={0};

int region_num;

Point_t curr_p;

Point_t regions_center[8] = {
    {30.064268090854906, 31.280235667396962},   // HALL A/B
    {30.063766676822745, 31.280446220808095},   // HALL C/D
    {30.06344073542287, 31.278450738667114},      // CREDIT
    {30.064636656137818, 31.280275930604628},    // MOSQUE
    {30.065088897805047, 31.28016131743544},     // LIBRARY
    {30.063633409347997, 31.2790300957928},   // PITCH
    {30.065575216528064, 31.27840379996902},    // FOUNTAIN
    {30.06343160681975, 31.279626844021017}     // LUBAN
};

Region_t regions[9] = {
    {
        "N",  // Unknown location (default)
    },
    {
        "HALL A/B", {
            {30.06429942914546, 31.28028260605471}, // Bottom right
            {30.064215860343822, 31.28002444343042},  // Bottom left
            {30.063979662031283, 31.280126367374972}, // Top left
            {30.06406439171167, 31.280393917731413}  // Top right
        }
    },
    {
        "HALL C/D", {
            {30.063806140053256, 31.280511934932786},  // Bottom right
            {30.063706321257637, 31.28022762076955},  // Bottom left
            {30.06346954138637, 31.28035904901482},  // Top left
            {30.063571681792467, 31.280624587714446}   // Top right
        }
    },
    {
        "CREDIT", {
            {30.063721621370714, 31.27834076808161},  // Bottom right
            {30.063584660555012, 31.27791429683676},   // Bottom left
            {30.063036815397187, 31.278163742281862},  // Top left
            {30.063199312158584, 31.278587531317623}    // Top right
        }
    },
    {
        "MOSQUE", {
            {30.06482637524488, 31.280337591336576},   // Bottom right
            {30.06468709461234, 31.280180682104973},  // Bottom left
            {30.064531564341024, 31.28038318889105},  // Top left
            {30.064680130575557, 31.280553509168083}    // Top right
        }
    },
    {
        "LIBRARY", {
            {30.06546495354033, 31.28021227941106},    // Bottom right
            {30.06539763502673, 31.280021842565876},  // Bottom left
            {30.064840514532214, 31.28027665242619},  // Top left
            {30.064905512084387, 31.280464407062283}   // Top right
        }
    },
    {
        "PITCH", {
            {30.06429035494301, 31.279845487361417},    // Bottom right
            {30.0639491151972, 31.27886111662645},   // Bottom left
            {30.063306095608496, 31.279161524044206},   // Top left
            {30.06367055126727, 31.280151259197353}     // Top right
        }
    },
    {
        "FOUNTAIN", {
            {30.065529156599766, 31.27859603769791},   // Bottom right
            {30.06541973424104, 31.278360730803975},   // Bottom left
            {30.065623381311724, 31.27827644176734},   // Top left
            {30.065675052889887, 31.278511748661273}   // Top right
        }
    },
    {
        "LUBAN", {
            {30.063271975058978, 31.28007701252767},   // Bottom right
            {30.06287733989391, 31.27895316697591},    // Bottom left
            {30.063118763946434, 31.27883514978193},   // Top left
            {30.063506434029648, 31.279916079990425}   // Top right
        }
    }
};

	float Qa , Qb; //Latitudes
	float La , Lb;

float toFloat(char *c, int size){
	int i;
	int j;
	char *ptr = c;
	float result = 0;
	for (j = 0 ; j < size ; j++){
		if(ptr[j] == '.'){
			break;
		}
	}
		for (i = j - 1 ; i>=0 ; i--){
				result += (ptr[i]-48) * pow(10 , (j-1) - i);
		}
		
		for (i = j + 1 ; i < size ; i++){
				result += (ptr[i]-48) * pow(10 , j - i);
		}
		
	return result;
}



void HAL_GPSRecieveMsg(){
	
    int i = 0;
	int j ;
    char c;
	MsgRecieved[0]='$';
    while (i < (MSG_SIZE - 1)) {  
        c = UART5_ReceiveChar();
        if (c == '\r' || c == '\n') {  // End of input 
            break;
        }
        MsgRecieved[i++] = c;
				
    }
    MsgRecieved[i] = '\0';  // Null terminate the string
		MsgRecieved[0]='$';
}

char HAL_GPSParseMsg(GPS_DATA *data){
	
	int i;
	

    char *ptr = MsgRecieved;
    int field = 0;
	char *end;

	for (i=0 ; i<(sizeof(MsgHeader)-1) ; i++){
		if(MsgRecieved[i]!= MsgHeader[i]){
			return PARSING_ERROR;
		}
	}

    while (*ptr && field <= 14) {
        end = strchr(ptr, ',');
        if (!end) end = strchr(ptr, '*');  // Last field before checksum
        
				 len = end ? (end - ptr) : strlen(ptr);
			
	
        
        switch (field) {
            case 1: // UTC Time
                strncpy(temp, ptr, len);
                temp[len] = '\0';
								
								data->utc_time = toFloat(temp , len);
                break;
            case 2: // Latitude
                strncpy(temp, ptr, len);
                temp[len] = '\0';
                data->latitude = toFloat(temp , len); // Convert to float
                break;
            case 3: // N/S Indicator
                data->ns_indicator = *ptr;
                break;
            case 4: // Longitude
                strncpy(temp, ptr, len);
                temp[len] = '\0';
                data->longitude = toFloat(temp , len); // Convert to float
                break;
            case 5: // E/W Indicator
                data->ew_indicator = *ptr;
                break;
            case 6: // Position Fix
                strncpy(temp, ptr, len);
                temp[len] = '\0';
                data->position_fix = toFloat(temp , len);
                break;
            case 7: // Satellites Used
                strncpy(temp, ptr, len);
                temp[len] = '\0';
                data->satellites_used = toFloat(temp , len);
                break;
            case 8: // HDOP
                strncpy(temp, ptr, len);
                temp[len] = '\0';
                data->hdop = toFloat(temp , len);
                break;
            case 9: // Altitude
                strncpy(temp, ptr, len);
                temp[len] = '\0';
                data->altitude = toFloat(temp , len);
                break;
            case 10: // Altitude Units
                data->altitude_units = *ptr;
                break;
            case 11: // Geoid Separation
                strncpy(temp, ptr, len);
                temp[len] = '\0';
                data->geoid_separation = toFloat(temp , len);
                break;
            case 12: // Geoid Separation Units
                data->geoid_separation_units = *ptr;
                break;
            // fields 13, 14 are optional (DGPS data), can ignore safely
            default:
                break;
        }
        
        if (end) ptr = end + 1;
        field++;
    }
	return PARSING_OK;
}

float toRad(float angle){
	return (float) ((angle * PI) / 180);
}
float toDegree(float angle){
	int degrees = (int) angle / 100;
	float minutes = angle - (float)degrees * 100; 
	return (degrees + (minutes / 60));
}

float HAL_GPSCalculateDistance(double current_lat , double current_lon , double des_lat , double des_lon){
	
	float distance;
 //Longitudes
	float a,c;
	
	Qa = toRad(toDegree(current_lat));
	//Qb = toRad(toDegree(des_lat));
	Qb = toRad(des_lat);
	
	La = toRad(toDegree(current_lon));
	//Lb = toRad(toDegree(des_lon));
	
	Lb= toRad(des_lon);
	
	curr_p.latitude 	= toDegree(current_lat);
	curr_p.longitude 	= toDegree(current_lon);
	
	a = pow(sin((Qb-Qa)/2),2) + cos(Qa) * cos (Qb) * pow(sin((Lb-La)/2),2);

	c = 2 * atan2(sqrt(a), sqrt(1 - a));;
	
	distance = EARTH_RADIUS * c;
		
	return distance;
}

int Point_In_Quad(Point_t p, Point_t quad[4]) {
    int winding_number = 0;
		int i;

    for (i = 0; i < 4; i++) {
        Point_t a = quad[i];
        Point_t b = quad[(i + 1) % 4];

        if (a.latitude <= p.latitude) {
            if (b.latitude > p.latitude &&
                ((b.longitude - a.longitude) * (p.latitude - a.latitude) - (b.latitude - a.latitude) * (p.longitude - a.longitude)) > 0)
                winding_number++;
        } else {
            if (b.latitude <= p.latitude &&
                ((b.longitude - a.longitude) * (p.latitude - a.latitude) - (b.latitude - a.latitude) * (p.longitude - a.longitude)) < 0)
                winding_number--;
        }
    }

    return (winding_number == 0) ? POINT_NOT_IN_QUAD : POINT_IN_QUAD;
}


bool isPointInsideRegion(Point_t point, Point_t corners[4]) {
    int i, j;
    bool inside = false;
    for (i = 0, j = 3; i < 4; j = i++) {
        double xi = corners[i].longitude, yi = corners[i].latitude;
        double xj = corners[j].longitude, yj = corners[j].latitude;

        bool intersect = ((yi > point.latitude) != (yj > point.latitude)) &&
                         (point.longitude < (xj - xi) * (point.latitude - yi) / (yj - yi + 1e-10) + xi);
        if (intersect)
            inside = !inside;
    }
    return inside;
}
