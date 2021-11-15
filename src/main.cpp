#include <Arduino.h>
#include <Manager.h>
#include <AdafruitSd.h>

Manager manager;

void handleStateMachine();

void setup() {
    // Cold start sequence
    manager.startSerial();
    manager.startStateMachine();
    // manager.init();

    // if (DEVELOPMENT) {
    //     manager.systemTest();
    // }
    
    Log::println("\n--- STARTING ---");
    
    Manager::setState(StateMachine::PAD_IDLE);
}

void loop() {
    handleStateMachine();
}

void handleStateMachine() {
    switch (Manager::getState()) {
        case (StateMachine::PAD_IDLE):
            manager.startCountingTime();
            manager.readSensors();

            Serial.print("ta no estado: ");
            Serial.println(Manager::getState());

            delay(1000);

            if (true) {
                Manager::setState(StateMachine::POWERED_FLIGHT);
            }

            break;

        case (StateMachine::POWERED_FLIGHT):
            Serial.print("ta no estado: ");
            Serial.println(Manager::getState());

            delay(1000);

            if (true) {
                Manager::setState(StateMachine::APOGEE);
            }

            break;

        case (StateMachine::APOGEE):
            Serial.print("ta no estado: ");
            Serial.println(Manager::getState());

            delay(1000);

            if (true) {
                Manager::setState(StateMachine::DROGUE_DEPLOYMENT);
            }

            break;

        case (StateMachine::DROGUE_DEPLOYMENT):
            Serial.print("ta no estado: ");
            Serial.println(Manager::getState());

            delay(1000);

            if (true) {
                Manager::setState(StateMachine::MAIN_DEPLOYMENT);
            }

            break;

        case (StateMachine::MAIN_DEPLOYMENT):
            Serial.print("ta no estado: ");
            Serial.println(Manager::getState());

            delay(1000);

            if (true) {
                Manager::setState(StateMachine::LANDED);
            }

            break;

        case (StateMachine::LANDED):
            Serial.print("ta no estado: ");
            Serial.println(Manager::getState());

            delay(1000);

            if (true) {
                Manager::setState(StateMachine::ABORT);
            }

            break;

        case (StateMachine::ABORT):
            Serial.print("ta no estado: ");
            Serial.println(Manager::getState());

            delay(1000);

            if (true) {
                Manager::setState(StateMachine::HOT_START);
            }

            break;

        case (StateMachine::HOT_START):
            Serial.print("ta no estado: ");
            Serial.println(Manager::getState());

            delay(1000);

            if (true) {
                Manager::setState(StateMachine::PAD_IDLE);
            }

            break;
        
        default:
            break;
        }
}