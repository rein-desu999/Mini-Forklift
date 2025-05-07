RC Forklift for Assistive Mobility
An Arduino-powered forklift with Bluetooth control and safety features

📌 Overview
This project designs an RC forklift to assist individuals with disabilities, combining:
- Bluetooth mobile control (via ArduinoBlue)
- Proximity detection (ultrasonic sensor + LED/buzzer alerts)
- Lifting mechanism (servo motor)
- Precise motor control (H-bridge driver)
- Dimensions: 10″ (L) × 6″ (W) × 12″ (H)
- Budget: $79.61 + $15 donation parts

🛠️ Hardware Components
Component	Usage
Arduino Uno/Nano	Main controller
HC-05 Bluetooth Module	Wireless communication
Ultrasonic Sensor	Object detection (≤10 inches)
Servo Motor	Lifting mechanism
L298N Motor Driver	DC motor control
LED + Buzzer	Safety alerts
(Optional: Add wiring diagram or Fritzing schematic image.)

🚀 Features
Bluetooth Control
- Throttle/steering via ArduinoBlue app (Android/iOS).
- Button-triggered servo lifting (CW()/CCW()).
  
Safety System
- Ultrasonic sensor triggers LED + buzzer when objects are too close (<3 inches).
- Motor Control
- Smooth forward/backward movement with speed mapping.
- Differential steering (reduce speed on one side for turns).

📝 Code Setup
Libraries Required:

cpp
#include <ArduinoBlue.h>
#include <Servo.h>
#include <SoftwareSerial.h>


Connect components as per pin definitions (e.g., servoPin = 11, trigPin = 13).

Pair HC-05 with your phone via Bluetooth.

Calibration:

Adjust MINIMUM_MOTOR_SPEED (default: 40) for smoother starts.

Set maxDistanceInches (default: 10) for proximity alerts.

🎯 Project Goals & Outcomes
✅ Accessibility: Assist users with mobility challenges.

✅ Safety: Real-time obstacle detection.

✅ Modularity: Code structured for easy expansion (e.g., add sensors).

Lessons Learned:

Integrating Bluetooth + sensor feedback.

Balancing mechanical load vs. motor torque.

🔗 Resources
Full Lab Report

ArduinoBlue Library: GitHub Link (add if available)

🙏 Credits
Code develop by Boi Hoanh Lam as part of EGR 1000.
