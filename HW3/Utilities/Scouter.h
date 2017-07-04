/*
 * Scouter.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef Utilities_SCOUTER_H_
#define Utilities_SCOUTER_H_
#include "Geometry.h"



class Scouter {
    
private:
    
    double velocity;
    double azimuth;
    Point destination;
    
public:
	Scouter();
    
    double calculate_distance(const Point & from, const Point & to);
    
    void setVelocity(double v){velocity = v;}
    double getVelocity()const{return velocity;}
    
    void setAzimuth(double a){azimuth = a;}
    double getAzimuth()const{return azimuth;}
    
    void setDestination(Point dest);
    Point getDestCoordinates()const ;
    
	virtual ~Scouter();
};

#endif /* SCOUTER_H_ */
