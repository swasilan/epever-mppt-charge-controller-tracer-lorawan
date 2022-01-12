/*******************************************************************************
 *
 *  File:         lmic-node-uplink-formatters.js
 * 
 *  Function:     LMIC-node uplink payload formatter JavaScript function(s).
 * 
 *  Author:       Leonel Lopes Parente
 * 
 *  Description:  These function(s) are for use with The Things Network V3. 
 *                 
 ******************************************************************************/

 function decodeUplink(input) {
    var data = {};
    var warnings = [];

    if (input.fPort == 10) {
        data.pvVoltage = ((input.bytes[0] << 8) + input.bytes[1]) / 100;
        data.pvCurrent = ((input.bytes[2] << 8) + input.bytes[3]) / 100;
        data.pvPower = Number((data.pvVoltage * data.pvCurrent).toFixed(2));
        data.battVoltage = ((input.bytes[4] << 8) + input.bytes[5]) / 100;
        data.battChargeCurrent = ((input.bytes[6] << 8) + input.bytes[7]) / 100;
        data.battChargePower = Number((data.battVoltage * data.battChargeCurrent).toFixed(2));
        data.battRemainingPercentage = ((input.bytes[8] << 8) + input.bytes[9]) / 100;
        data.loadVoltage = ((input.bytes[10] << 8) + input.bytes[11]) / 100;
        data.loadCurrent = ((input.bytes[12] << 8) + input.bytes[13]) / 100;
        data.loadPower = Number((data.loadVoltage * data.loadCurrent).toFixed(2));
        data.payloadSizeInBits = input.bytes.length * 8;
    }
    else {
        warnings.push("Unsupported fPort");
    }
    return {
        data: data,
        warnings: warnings
    };
}