#include "data.h"

Data::Data()
{
    this->altitude = 0.0;
    this->latitude = 0.0;
    this->longitude = 0.0;
    this->velocity = 0.0;
    this->orientation.pitch = 0.0;
    this->orientation.roll = 0.0;
    this->orientation.yaw = 0.0;
}

float Data::getAltitude() {return altitude;}
float Data::getLatitude() {return latitude;}
float Data::getLongitude() {return longitude;}
Data::t_orientation Data::getOrientation() {return orientation;}
float Data::getVelocity() {return velocity;}

void Data::setAltitude(float altitude) {this->altitude = altitude;}
void Data::setLatitude(float latitude) {this->latitude = latitude;}
void Data::setLongitude(float longitude) {this->longitude = longitude;}
void Data::setOrientation(float pitch, float roll, float yaw) {
    this->orientation.pitch = pitch;
    this->orientation.roll = roll;
    this->orientation.yaw = yaw;
}
void Data::setVelocity(float velocity) {this->velocity = velocity;}
