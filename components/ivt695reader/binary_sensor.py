# File: esphome/components/ivt695reader/binary_sensor.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_PROBLEM,
    DEVICE_CLASS_RUNNING,
)

from . import IVT695Reader, CONF_IVT695READER_ID

# Binary sensors
CONF_PRESS_SWITCH_DEFROST = "press_switch_defrost"
CONF_PRESS_SWITCH_HIGH = "press_switch_high"
CONF_PRESS_SWITCH_LOW = "press_switch_low"
CONF_VACATION_MODE = "vacation_mode"
CONF_COMPRESSOR_IN_OP = "compressor_in_op"
CONF_SHUNT_VALVE_OPENING = "shunt_valve_opening"
CONF_SHUNT_VALVE_CLOSING = "shunt_valve_closing"
CONF_CIRC_PUMP_HEAT_CARRIER = "circ_pump_heat_carrier"
CONF_FAN_IN_OP = "fan_in_op"
CONF_ALARM_ACTIVE = "alarm_active"
CONF_EXTERNAL_P2 = "external_p2"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_IVT695READER_ID): cv.use_id(IVT695Reader),
    cv.Optional(CONF_PRESS_SWITCH_DEFROST): binary_sensor.binary_sensor_schema(),
    cv.Optional(CONF_PRESS_SWITCH_HIGH): binary_sensor.binary_sensor_schema(
        device_class=DEVICE_CLASS_PROBLEM
    ),
    cv.Optional(CONF_PRESS_SWITCH_LOW): binary_sensor.binary_sensor_schema(
        device_class=DEVICE_CLASS_PROBLEM
    ),
    cv.Optional(CONF_VACATION_MODE): binary_sensor.binary_sensor_schema(),
    cv.Optional(CONF_COMPRESSOR_IN_OP): binary_sensor.binary_sensor_schema(
        device_class=DEVICE_CLASS_RUNNING
    ),
    cv.Optional(CONF_SHUNT_VALVE_OPENING): binary_sensor.binary_sensor_schema(),
    cv.Optional(CONF_SHUNT_VALVE_CLOSING): binary_sensor.binary_sensor_schema(),
    cv.Optional(CONF_CIRC_PUMP_HEAT_CARRIER): binary_sensor.binary_sensor_schema(),
    cv.Optional(CONF_FAN_IN_OP): binary_sensor.binary_sensor_schema(
        device_class=DEVICE_CLASS_RUNNING
    ),
    cv.Optional(CONF_ALARM_ACTIVE): binary_sensor.binary_sensor_schema(
        device_class=DEVICE_CLASS_PROBLEM
    ),
    cv.Optional(CONF_EXTERNAL_P2): binary_sensor.binary_sensor_schema(),
})

async def to_code(config):
    parent = await cg.get_variable(config[CONF_IVT695READER_ID])
    
    if CONF_PRESS_SWITCH_DEFROST in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_PRESS_SWITCH_DEFROST])
        cg.add(parent.set_press_switch_defrost_sensor(sens))
    
    if CONF_PRESS_SWITCH_HIGH in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_PRESS_SWITCH_HIGH])
        cg.add(parent.set_press_switch_high_sensor(sens))
    
    if CONF_PRESS_SWITCH_LOW in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_PRESS_SWITCH_LOW])
        cg.add(parent.set_press_switch_low_sensor(sens))
    
    if CONF_VACATION_MODE in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_VACATION_MODE])
        cg.add(parent.set_vacation_mode_sensor(sens))
    
    if CONF_COMPRESSOR_IN_OP in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_COMPRESSOR_IN_OP])
        cg.add(parent.set_compressor_in_op_sensor(sens))
    
    if CONF_SHUNT_VALVE_OPENING in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_SHUNT_VALVE_OPENING])
        cg.add(parent.set_shunt_valve_opening_sensor(sens))
    
    if CONF_SHUNT_VALVE_CLOSING in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_SHUNT_VALVE_CLOSING])
        cg.add(parent.set_shunt_valve_closing_sensor(sens))
    
    if CONF_CIRC_PUMP_HEAT_CARRIER in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_CIRC_PUMP_HEAT_CARRIER])
        cg.add(parent.set_circ_pump_heat_carrier_sensor(sens))
    
    if CONF_FAN_IN_OP in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_FAN_IN_OP])
        cg.add(parent.set_fan_in_op_sensor(sens))
    
    if CONF_ALARM_ACTIVE in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_ALARM_ACTIVE])
        cg.add(parent.set_alarm_active_sensor(sens))
    
    if CONF_EXTERNAL_P2 in config:
        sens = await binary_sensor.new_binary_sensor(config[CONF_EXTERNAL_P2])
        cg.add(parent.set_external_p2_sensor(sens))
