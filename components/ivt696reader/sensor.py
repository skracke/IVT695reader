# File: esphome/components/ivt695reader/sensor.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_POWER,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_WATT,
)

from . import IVT695Reader, CONF_IVT695READER_ID

AUTO_LOAD = ["ivt695reader"]

# Analog sensors
CONF_MESSAGE_COUNTER = "message_counter"
CONF_GT1_SUPPLY_TEMP = "gt1_supply_temp"
CONF_GT2_OUTSIDE_TEMP = "gt2_outside_temp"
CONF_GT31_WATER_TANK_TEMP = "gt31_water_tank_temp"
CONF_GT32_WATER_TANK_TEMP = "gt32_water_tank_temp"
CONF_GT33_WATER_TANK_TEMP = "gt33_water_tank_temp"
CONF_GT5_ROOM_TEMP = "gt5_room_temp"
CONF_GT6_COMPRESSOR_TEMP = "gt6_compressor_temp"
CONF_GT10_BRINE_TEMP = "gt10_brine_temp"
CONF_GT1_LLT = "gt1_llt"
CONF_GT1_LL = "gt1_ll"
CONF_GT1_SETPOINT = "gt1_setpoint"
CONF_GT1_UL = "gt1_ul"
CONF_GT32_LL = "gt32_ll"
CONF_GT32_ULT = "gt32_ult"
CONF_GT32_UL = "gt32_ul"
CONF_GT33_LL = "gt33_ll"
CONF_GT33_SETPOINT = "gt33_setpoint"
CONF_SV3_SETPOINT_OFFSET = "sv3_setpoint_offset"
CONF_POS_31 = "pos_31"
CONF_POS_32 = "pos_32"
CONF_POS_33 = "pos_33"
CONF_ELEC_HEAT_POW = "elec_heat_pow"
CONF_POS_35 = "pos_35"
CONF_POS_36 = "pos_36"
CONF_DEFAULT_SV2_OPEN = "default_sv2_open"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_IVT695READER_ID): cv.use_id(IVT695Reader),
        cv.Optional(CONF_MESSAGE_COUNTER): sensor.sensor_schema(
            accuracy_decimals=0
        ),
        cv.Optional(CONF_GT1_SUPPLY_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_GT2_OUTSIDE_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_GT31_WATER_TANK_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_GT32_WATER_TANK_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_GT33_WATER_TANK_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_GT5_ROOM_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_GT6_COMPRESSOR_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_GT10_BRINE_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_GT1_LLT): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_GT1_LL): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_GT1_SETPOINT): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_GT1_UL): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_GT32_LL): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_GT32_ULT): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_GT32_UL): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_GT33_LL): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_GT33_SETPOINT): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_SV3_SETPOINT_OFFSET): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_POS_31): sensor.sensor_schema(
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_POS_32): sensor.sensor_schema(
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_POS_33): sensor.sensor_schema(
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_ELEC_HEAT_POW): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_POWER,
        ),
        cv.Optional(CONF_POS_35): sensor.sensor_schema(
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_POS_36): sensor.sensor_schema(
            accuracy_decimals=1,
        ),
        cv.Optional(CONF_DEFAULT_SV2_OPEN): sensor.sensor_schema(
            accuracy_decimals=1,
        ),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_IVT695READER_ID])
    
    if CONF_MESSAGE_COUNTER in config:
        sens = await sensor.new_sensor(config[CONF_MESSAGE_COUNTER])
        cg.add(parent.set_message_counter_sensor(sens)) # Uses setter method
    
    if CONF_GT1_SUPPLY_TEMP in config:
        sens = await sensor.new_sensor(config[CONF_GT1_SUPPLY_TEMP])
        cg.add(parent.set_gt1_supply_temp_sensor(sens)) # Uses setter method
    
    if CONF_GT2_OUTSIDE_TEMP in config:
        sens = await sensor.new_sensor(config[CONF_GT2_OUTSIDE_TEMP])
        cg.add(parent.set_gt2_outside_temp_sensor(sens)) # Uses setter method
    
    if CONF_GT31_WATER_TANK_TEMP in config:
        sens = await sensor.new_sensor(config[CONF_GT31_WATER_TANK_TEMP])
        cg.add(parent.set_gt31_water_tank_temp_sensor(sens)) # Uses setter method
    
    if CONF_GT32_WATER_TANK_TEMP in config:
        sens = await sensor.new_sensor(config[CONF_GT32_WATER_TANK_TEMP])
        cg.add(parent.set_gt32_water_tank_temp_sensor(sens)) # Uses setter method
    
    if CONF_GT33_WATER_TANK_TEMP in config:
        sens = await sensor.new_sensor(config[CONF_GT33_WATER_TANK_TEMP])
        cg.add(parent.set_gt33_water_tank_temp_sensor(sens)) # Uses setter method
    
    if CONF_GT5_ROOM_TEMP in config:
        sens = await sensor.new_sensor(config[CONF_GT5_ROOM_TEMP])
        cg.add(parent.set_gt5_room_temp_sensor(sens)) # Uses setter method
    
    if CONF_GT6_COMPRESSOR_TEMP in config:
        sens = await sensor.new_sensor(config[CONF_GT6_COMPRESSOR_TEMP])
        cg.add(parent.set_gt6_compressor_temp_sensor(sens)) # Uses setter method
    
    if CONF_GT10_BRINE_TEMP in config:
        sens = await sensor.new_sensor(config[CONF_GT10_BRINE_TEMP])
        cg.add(parent.set_gt10_brine_temp_sensor(sens)) # Uses setter method
    
    if CONF_GT1_LLT in config:
        sens = await sensor.new_sensor(config[CONF_GT1_LLT])
        cg.add(parent.set_gt1_llt_sensor(sens)) # Uses setter method
    
    if CONF_GT1_LL in config:
        sens = await sensor.new_sensor(config[CONF_GT1_LL])
        cg.add(parent.set_gt1_ll_sensor(sens)) # Uses setter method
    
    if CONF_GT1_SETPOINT in config:
        sens = await sensor.new_sensor(config[CONF_GT1_SETPOINT])
        cg.add(parent.set_gt1_setpoint_sensor(sens)) # Uses setter method
    
    if CONF_GT1_UL in config:
        sens = await sensor.new_sensor(config[CONF_GT1_UL])
        cg.add(parent.set_gt1_ul_sensor(sens)) # Uses setter method
    
    if CONF_GT32_LL in config:
        sens = await sensor.new_sensor(config[CONF_GT32_LL])
        cg.add(parent.set_gt32_ll_sensor(sens)) # Uses setter method
    
    if CONF_GT32_ULT in config:
        sens = await sensor.new_sensor(config[CONF_GT32_ULT])
        cg.add(parent.set_gt32_ult_sensor(sens)) # Uses setter method
    
    if CONF_GT32_UL in config:
        sens = await sensor.new_sensor(config[CONF_GT32_UL])
        cg.add(parent.set_gt32_ul_sensor(sens)) # Uses setter method
    
    if CONF_GT33_LL in config:
        sens = await sensor.new_sensor(config[CONF_GT33_LL])
        cg.add(parent.set_gt33_ll_sensor(sens)) # Uses setter method
    
    if CONF_GT33_SETPOINT in config:
        sens = await sensor.new_sensor(config[CONF_GT33_SETPOINT])
        cg.add(parent.set_gt33_setpoint_sensor(sens)) # Uses setter method
    
    if CONF_SV3_SETPOINT_OFFSET in config:
        sens = await sensor.new_sensor(config[CONF_SV3_SETPOINT_OFFSET])
        cg.add(parent.set_sv3_setpoint_offset_sensor(sens)) # Uses setter method
    
    if CONF_POS_31 in config:
        sens = await sensor.new_sensor(config[CONF_POS_31])
        cg.add(parent.set_pos_31_sensor(sens)) # Uses setter method
    
    if CONF_POS_32 in config:
        sens = await sensor.new_sensor(config[CONF_POS_32])
        cg.add(parent.set_pos_32_sensor(sens)) # Uses setter method
    
    if CONF_POS_33 in config:
        sens = await sensor.new_sensor(config[CONF_POS_33])
        cg.add(parent.set_pos_33_sensor(sens)) # Uses setter method
    
    if CONF_ELEC_HEAT_POW in config:
        sens = await sensor.new_sensor(config[CONF_ELEC_HEAT_POW])
        cg.add(parent.set_elec_heat_pow_sensor(sens)) # Uses setter method
    
    if CONF_POS_35 in config:
        sens = await sensor.new_sensor(config[CONF_POS_35])
        cg.add(parent.set_pos_35_sensor(sens)) # Uses setter method
    
    if CONF_POS_36 in config:
        sens = await sensor.new_sensor(config[CONF_POS_36])
        cg.add(parent.set_pos_36_sensor(sens)) # Uses setter method
    
    if CONF_DEFAULT_SV2_OPEN in config:
        sens = await sensor.new_sensor(config[CONF_DEFAULT_SV2_OPEN])
        cg.add(parent.set_default_sv2_open_sensor(sens)) # Uses setter method
