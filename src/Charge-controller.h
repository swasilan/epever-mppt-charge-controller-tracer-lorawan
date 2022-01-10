/*
EPSolar / EPEver Tracer A/B, Xtra, Triton Series MPPT Solar Charge Controllers (RS-485 Modbus RTU) Library for
reading states and writing settings from/to the Charge Controller.

Created by Sascha Waser, January 8, 2022

*/

#ifndef ChargeController_h
#define ChargeController_h

#include "Arduino.h"
#include <ModbusMaster.h>

struct PvData {
    uint16_t voltage;
    uint16_t current;
    uint32_t power;
};

struct BattData  {
    uint16_t voltage;
    uint16_t chargingCurrent;
    uint32_t chargingPower;
    uint16_t remainingPercentage;
};

struct LoadData {
    uint16_t voltage;
    uint16_t current;
    uint32_t power;
};

class ChargeController {
    private:
        // variables
        ModbusMaster _node;
        static int _MAX485_DE_RE_PIN;

        // methods
        static void preTransmission();
        static void postTransmission();
        
    public:
        ChargeController(const ModbusMaster& node, int MAX485_DE_RE_Pin);
        ~ChargeController();
        int8_t readOutputLoadState();
        void turnLoadPowerOn();
        void turnLoadPowerOff();

        PvData readPvData();
        BattData readBattData();
        LoadData readLoadData();

        
};

#endif

