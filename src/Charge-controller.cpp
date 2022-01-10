#include "Arduino.h"
#include "Charge-controller.h"

int ChargeController::_MAX485_DE_RE_PIN;

ChargeController::ChargeController(const ModbusMaster& node, int MAX485_DE_RE_PIN) {
    pinMode(MAX485_DE_RE_PIN, OUTPUT);
    digitalWrite(MAX485_DE_RE_PIN, 0);
    _MAX485_DE_RE_PIN = MAX485_DE_RE_PIN;

    _node = node;
    _node.preTransmission(preTransmission);
    _node.postTransmission(postTransmission);
}

void ChargeController::preTransmission() {
    digitalWrite(_MAX485_DE_RE_PIN, 1);
}

void ChargeController::postTransmission() {
    digitalWrite(_MAX485_DE_RE_PIN, 0);
}

int8_t ChargeController::readOutputLoadState(){
    uint8_t result = _node.readCoils(0x0006, 1);

    if(result == _node.ku8MBSuccess) {
        return _node.getResponseBuffer(0x00);
    }

    return -1;
}

void ChargeController::turnLoadPowerOn(){
    _node.writeSingleCoil(0x0006, 1);
}

void ChargeController::turnLoadPowerOff(){
    _node.writeSingleCoil(0x0006, 0);
}

PvData ChargeController::readPvData(){
    uint8_t result = _node.readInputRegisters(0x3100, 4);
    PvData measurement = {0, 0, 0};
    
    if(result == _node.ku8MBSuccess) {
        measurement.voltage = _node.getResponseBuffer(0x00);
        measurement.current = _node.getResponseBuffer(0x01);
        measurement.power = (_node.getResponseBuffer(0x02) | _node.getResponseBuffer(0x03) << 16);
    }

    return measurement;
}

BattData ChargeController::readBattData(){
    uint8_t result = _node.readInputRegisters(0x3104, 4);
    BattData measurement = {0, 0, 0, 0};

    if(result == _node.ku8MBSuccess) {
        measurement.voltage = _node.getResponseBuffer(0x00);
        measurement.chargingCurrent = _node.getResponseBuffer(0x01);
        measurement.chargingPower = (_node.getResponseBuffer(0x02) | _node.getResponseBuffer(0x03) << 16);
    }

    result = _node.readInputRegisters(0x311A, 1);
    if(result == _node.ku8MBSuccess) {
        measurement.remainingPercentage = _node.getResponseBuffer(0x00);
    }

    return measurement;
}

LoadData ChargeController::readLoadData(){
    uint8_t result = _node.readInputRegisters(0x310C, 4);
    LoadData measurement = {0, 0, 0};
    
    if(result == _node.ku8MBSuccess) {
        measurement.voltage = _node.getResponseBuffer(0x00);
        measurement.current = _node.getResponseBuffer(0x01);
        measurement.power = (_node.getResponseBuffer(0x02) | _node.getResponseBuffer(0x03) << 16);
    }

    return measurement;
}