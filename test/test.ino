double time, altitude, pressure, roll, pitch, yaw, temperature, velocity, latitude, longitude;

/**
 * 
 * WARNING: a double on Arduino UNO has the same precision as a float (4 bytes).
 * 
 */

void setup() {
    while(!Serial){}
    Serial.begin(115200);
    time = 5.0;
    altitude = 50;
    pressure = 1000;
    roll = 1;
    pitch = 2;
    yaw = 2.5;
    temperature = 19.1;
    velocity = 0;
    latitude = 41.385064;
    longitude = 2.173403;
}

void loop() {
    time = micros();
    altitude += 0.5;
    pressure += 10;
    roll += 0.1;
    pitch += 0.2;
    yaw += 0.5;
    temperature += 0.1;
    velocity += 2;
    latitude += 0.00003;
    longitude += 0.000076;
    Serial.print("0");
    Serial.write((byte *)&time, 4);
    Serial.write((byte *)&pressure, 4);
    Serial.write((byte *)&temperature, 4);
    Serial.write((byte *)&roll, 4);
    Serial.write((byte *)&pitch, 4);
    Serial.write((byte *)&yaw, 4);
    Serial.println();

    Serial.print("1");    
    Serial.write((byte *)&time, 4);
    Serial.write((byte *)&altitude, 4);
    Serial.write((byte *)&velocity, 4);
    Serial.write((byte *)&latitude, 4);
    Serial.write((byte *)&longitude, 4);
    Serial.println();

    if (Serial.available() > 0) {
        String received = Serial.readStringUntil("/n");
        received = "received: " + received;
        Serial.println(received);
    }
    delay(1000);
}

