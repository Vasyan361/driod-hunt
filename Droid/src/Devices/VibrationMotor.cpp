#include "VibrationMotor.h"

void VibrationMotor::init()
{
    pinMode(MOTOR_PIN, OUTPUT);
}

void VibrationMotor::run()
{
    if (millis() - timer > 300) {
        timer = millis();

        state = !state;
    }

    if (state) {
        digitalWrite(MOTOR_PIN, HIGH);
    } else {
        digitalWrite(MOTOR_PIN, LOW);
    }
}

void VibrationMotor::stop()
{
    digitalWrite(MOTOR_PIN, LOW);
}