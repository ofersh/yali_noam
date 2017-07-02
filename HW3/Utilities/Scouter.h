/*
 * Scouter.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef Utilities_SCOUTER_H_
#define Utilities_SCOUTER_H_


using coordinates = pair<double, double>; //VERY IMPORTANT, FIRST Y THEN X.

class Scouter {
    
private:
    
    double velocity;
    double azimuth;
    
public:
	Scouter();
    
    double calculate_distance(const coordinates & from, const coordinates & to);
    
    
    
    
    void setVelocity(double v){velocity = v;}
    double getVelocity()const{return velocity;}
    
    void setAzimuth(double a){azimuth = a;}
    double getAzimuth()const{return azimuth;}
    
    
	virtual ~Scouter();
};

#endif /* SCOUTER_H_ */
