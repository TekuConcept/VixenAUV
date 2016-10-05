/**
 * Created by TekuConcept on 8/4/2016.
 */

#ifndef IMU_INTERFACE_H
#define IMU_INTERFACE_H

/* System Includes */
#include <iostream>
#include <string>
#include <sstream>

/* IMU Includes */
#include <BMP085.h>
#include <HMC5883L.h>
#include <MPU6050.h>

class IMU {
public:
    IMU() {
        e_sense.initialize();
        c_sense.setMode(HMC5883L::Mode::Continuous);
        m_sense.awake();
    }
    ~IMU() {
        m_sense.sleep();
        c_sense.setMode(HMC5883L::Mode::Idle);
    }
    
    /* - - DEBUG FUNCTIONS FOR LIVE TESTING - - */
    void debug_compass() {
        float x = c_sense.X();
        float y = c_sense.Y();
        float z = c_sense.Z();
        std::cout << "Compass: [X: " << x << ", Y: " << y << ", Z: " << z << "]\n";
    }
    
    void debug_accelerometer() {
        float x = m_sense.accel_X();
        float y = m_sense.accel_Y();
        float z = m_sense.accel_Z();
        std::cout << "Accelerometer: [X: ";
        std::cout << x << ", Y: " << y << ", Z: " << z << "]\n";
    }
    
    void debug_gyroscope() {
        float x = m_sense.gyro_X();
        float y = m_sense.gyro_Y();
        float z = m_sense.gyro_Z();
        std::cout << "Gyroscope: [X: ";
        std::cout << x << ", Y: " << y << ", Z: " << z << "]\n";
    }
    
    void debug_temperature() {
        float a = m_sense.temperature();
        float b = e_sense.readTemperature();
        std::cout << "Temperature: [MPU6050: " << a << ", BMP085: " << b << "]\n";
    }
    
    void debug_pressure() {
        float p = e_sense.readAltitude();
        std::cout << "Pressure: [BMP085: " << p << "]\n";
    }
    
    std::string test() {
        return "[This is a test string]";
    }
    
    
    /* - - RELEASE FUNCTIONS FOR ACTIVE DEVELOPMENT - - */
    
    /* Returns JSON strings containing the latest sensor data. */
    std::string compass() {
        std::stringstream ss;
        float x = c_sense.X();
        float y = c_sense.Y();
        float z = c_sense.Z();
        ss << "{\"Compass\": {\"X\":" << x << ",\"Y\":";
        ss << y << ",\"Z\":" << z << "}}";
        return ss.str();
    }
    
    std::string accelerometer() {
        std::stringstream ss;
        float x = m_sense.accel_X();
        float y = m_sense.accel_Y();
        float z = m_sense.accel_Z();
        ss << "{\"Accelerometer\": {\"X\":" << x << ",\"Y\":";
        ss << y << ",\"Z\":" << z << "}}";
        return ss.str();
    }
    
    std::string gyroscope() {
        std::stringstream ss;
        float x = m_sense.gyro_X();
        float y = m_sense.gyro_Y();
        float z = m_sense.gyro_Z();
        ss << "{\"Gyroscope\": {\"X\":" << x << ",\"Y\":";
        ss << y << ",\"Z\":" << z << "}}";
        return ss.str();
    }
    
    std::string temperature() {
        std::stringstream ss;
        float a = m_sense.temperature();
        float b = e_sense.readTemperature();
        ss << "{\"Temperature\": {\"MPU6050\":" << a;
        ss << ",\"BMP085\":" << b << "}}";
        return ss.str();
    }
    
    std::string pressure() {
        std::stringstream ss;
        float p = e_sense.readAltitude();
        ss << "{\"Pressure\": {\"BMP085\":" << p << "}}";
        return ss.str();
    }



    /* Direct calls for specific values. */
    float compass_x() {
        return c_sense.X();
    }
    float compass_y() {
        return c_sense.Y();
    }
    float compass_z() {
        return c_sense.Z();
    }
    
    float accel_x() {
        return m_sense.accel_X();
    }
    float accel_y() {
        return m_sense.accel_Y();
    }
    float accel_z() {
        return m_sense.accel_Z();
    }
    
    float gyro_x() {
        return m_sense.gyro_X();
    }
    float gyro_y() {
        return m_sense.gyro_Y();
    }
    float gyro_z() {
        return m_sense.gyro_Z();
    }
    
    float average_temperature() {
        float a = m_sense.temperature();
        float b = e_sense.readTemperature();
        return (a + b) / 2;
    }
    
    float pressure_val() {
        return e_sense.readAltitude();
    }
    
    
    
private:
    BMP085 e_sense;
    HMC5883L c_sense;
    MPU6050 m_sense;
};

#endif