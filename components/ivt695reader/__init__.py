import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import uart
from esphome.const import (
    CONF_UART_ID, CONF_ID
)

CODEOWNERS = ["elt"]

MULTI_CONF = True

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor", "binary_sensor"]

CONF_IVT695READER_ID = "ivt695reader_id"

ivt695reader_ns = cg.esphome_ns.namespace("esphome::ivt695reader")
IVT695Reader = ivt695reader_ns.class_("IVT695Reader", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(IVT695Reader),
        }
    ).extend(uart.UART_DEVICE_SCHEMA),
    cv.only_with_arduino,
)

async def to_code(config):
    uart_component = await cg.get_variable(config[CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_component)
    await cg.register_component(var, config)
