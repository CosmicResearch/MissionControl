#ifndef DATA_H
#define DATA_H


class Data
{
public:
    Data();
    struct t_orientation {
        float pitch;
        float roll;
        float yaw;
    } ;

    float getVelocity();
    float getAltitude();
    float getLatitude();
    float getLongitude();
    t_orientation getOrientation();

    void setVelocity(float velocity);
    void setAltitude(float altitude);
    void setLatitude(float latitude);
    void setLongitude(float longitude);
    void setOrientation(float pitch, float roll, float yaw);
private:
    float altitude;
    float velocity;
    float latitude;
    float longitude;
    t_orientation orientation;
};

#endif // DATA_H
