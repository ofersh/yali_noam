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
	Scouter()=default;
	virtual ~Scouter()=default;

    double calculate_distance(const Point & from, const Point & to);
    
    void setVelocity(double v){velocity = v;}
    double getVelocity()const{return velocity;}
    
    void setAzimuth(double a){azimuth = a;}
    void setAzimuth(Point source, Point dest);
    double getAzimuth()const{return azimuth;}
    
    void setDestination(Point dest);
    Point getDestCoordinates()const ;
    
    Point calculateNextStep(const Point current);




};

#endif /* SCOUTER_H_ */
