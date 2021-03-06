

#ifndef Utilities_SCOUTER_H_
#define Utilities_SCOUTER_H_
#include "Geometry.h"



//hold information of ship location and current route.
//including speed.
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
    double getAzimuth()const;
    
    void setDestination(Point dest);
    Point getDestCoordinates()const ;
    
    //Main functionality. set course and calculate next step.
    void setCourse();
    Point calculateNextStep(const Point current);




};

#endif /* SCOUTER_H_ */
