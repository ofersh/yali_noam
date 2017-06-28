/*
 * Scouter.h
 *
 *  Created on: 27 Jun 2017
 *      Author: noam
 */

#ifndef SCOUTER_H_
#define SCOUTER_H_

class Scouter {
    
private:
    
    double velocity;
    double azimuth;
    
public:
	Scouter();
    
    void setVelocity(double v){velocity = v;}
    double getVelocity()const{return velocity;}
    
    void setAzimuth(double a){azimuth = a;}
    double getAzimuth()const{return azimuth;}
    
	virtual ~Scouter();
};

#endif /* SCOUTER_H_ */
