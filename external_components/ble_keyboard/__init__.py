import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_NAME
from esphome.core import CORE
from esphome.components.esp32 import include_builtin_idf_component

DEPENDENCIES = []
AUTO_LOAD = []

esphome_ns = cg.esphome_ns
Esp32BLEKeyboard = esphome_ns.class_("Esp32BLEKeyboard", cg.PollingComponent)

CONF_DEVICE_NAME = "device_name"
CONF_MANUFACTURER = "manufacturer"

CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(Esp32BLEKeyboard),
        cv.Optional(CONF_DEVICE_NAME, default=CORE.name): cv.string,
        cv.Optional(CONF_MANUFACTURER, default="ESPHome"): cv.string,
    }
).extend(cv.polling_component_schema("1000ms"))


async def to_code(config):
    include_builtin_idf_component("bt")
    var = cg.new_Pvariable(
        config[CONF_ID], config[CONF_DEVICE_NAME], config[CONF_MANUFACTURER]
    )
    await cg.register_component(var, config)
