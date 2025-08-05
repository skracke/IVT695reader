// File: esphome/components/ivt695reader/ivt695reader.h
#pragma once

#include "esphome/core/component.h" // Explicit inclusion for Component class methods
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <string>

namespace esphome
{
    namespace ivt695reader
    {
        class IVT695Reader : public Component, public uart::UARTDevice
        {
        public:
            // Constructor
            IVT695Reader(uart::UARTComponent *parent) : uart::UARTDevice(parent)
            {}

            // Standard ESPhome methods
            void setup() override;
            void loop() override;
            void dump_config() override;

            // Pointers to sensor objects
            // Analog values
            sensor::Sensor *message_counter_sensor{nullptr};
            sensor::Sensor *gt1_supply_temp_sensor{nullptr};
            sensor::Sensor *gt2_outside_temp_sensor{nullptr};
            sensor::Sensor *gt31_water_tank_temp_sensor{nullptr};
            sensor::Sensor *gt32_water_tank_temp_sensor{nullptr};
            sensor::Sensor *gt33_water_tank_temp_sensor{nullptr};
            sensor::Sensor *gt5_room_temp_sensor{nullptr};
            sensor::Sensor *gt6_compressor_temp_sensor{nullptr};
            sensor::Sensor *gt10_brine_temp_sensor{nullptr};

            // Binary values
            binary_sensor::BinarySensor *press_switch_defrost_sensor{nullptr};
            binary_sensor::BinarySensor *press_switch_high_sensor{nullptr};
            binary_sensor::BinarySensor *press_switch_low_sensor{nullptr};
            binary_sensor::BinarySensor *vacation_mode_sensor{nullptr};
            binary_sensor::BinarySensor *compressor_in_op_sensor{nullptr};
            binary_sensor::BinarySensor *shunt_valve_opening_sensor{nullptr};
            binary_sensor::BinarySensor *shunt_valve_closing_sensor{nullptr};
            binary_sensor::BinarySensor *circ_pump_heat_carrier_sensor{nullptr};
            binary_sensor::BinarySensor *fan_in_op_sensor{nullptr};
            binary_sensor::BinarySensor *alarm_active_sensor{nullptr};
            binary_sensor::BinarySensor *external_p2_sensor{nullptr};

            // Additional analog values
            sensor::Sensor *gt1_llt_sensor{nullptr};
            sensor::Sensor *gt1_ll_sensor{nullptr};
            sensor::Sensor *gt1_setpoint_sensor{nullptr};
            sensor::Sensor *gt1_ul_sensor{nullptr};
            sensor::Sensor *gt32_ll_sensor{nullptr};
            sensor::Sensor *gt32_ult_sensor{nullptr};
            sensor::Sensor *gt32_ul_sensor{nullptr};
            sensor::Sensor *gt33_ll_sensor{nullptr};
            sensor::Sensor *gt33_setpoint_sensor{nullptr};
            sensor::Sensor *sv3_setpoint_offset_sensor{nullptr};
            sensor::Sensor *pos_31_sensor{nullptr};
            sensor::Sensor *pos_32_sensor{nullptr};
            sensor::Sensor *pos_33_sensor{nullptr};
            sensor::Sensor *elec_heat_pow_sensor{nullptr};
            sensor::Sensor *pos_35_sensor{nullptr};
            sensor::Sensor *pos_36_sensor{nullptr};
            sensor::Sensor *default_sv2_open_sensor{nullptr};

            // Setter methods for sensors
            void set_message_counter_sensor(sensor::Sensor *s) { this->message_counter_sensor = s; }
            void set_gt1_supply_temp_sensor(sensor::Sensor *s) { this->gt1_supply_temp_sensor = s; }
            void set_gt2_outside_temp_sensor(sensor::Sensor *s) { this->gt2_outside_temp_sensor = s; }
            void set_gt31_water_tank_temp_sensor(sensor::Sensor *s) { this->gt31_water_tank_temp_sensor = s; }
            void set_gt32_water_tank_temp_sensor(sensor::Sensor *s) { this->gt32_water_tank_temp_sensor = s; }
            void set_gt33_water_tank_temp_sensor(sensor::Sensor *s) { this->gt33_water_tank_temp_sensor = s; }
            void set_gt5_room_temp_sensor(sensor::Sensor *s) { this->gt5_room_temp_sensor = s; }
            void set_gt6_compressor_temp_sensor(sensor::Sensor *s) { this->gt6_compressor_temp_sensor = s; }
            void set_gt10_brine_temp_sensor(sensor::Sensor *s) { this->gt10_brine_temp_sensor = s; }
            void set_gt1_llt_sensor(sensor::Sensor *s) { this->gt1_llt_sensor = s; }
            void set_gt1_ll_sensor(sensor::Sensor *s) { this->gt1_ll_sensor = s; }
            void set_gt1_setpoint_sensor(sensor::Sensor *s) { this->gt1_setpoint_sensor = s; }
            void set_gt1_ul_sensor(sensor::Sensor *s) { this->gt1_ul_sensor = s; }
            void set_gt32_ll_sensor(sensor::Sensor *s) { this->gt32_ll_sensor = s; }
            void set_gt32_ult_sensor(sensor::Sensor *s) { this->gt32_ult_sensor = s; }
            void set_gt32_ul_sensor(sensor::Sensor *s) { this->gt32_ul_sensor = s; }
            void set_gt33_ll_sensor(sensor::Sensor *s) { this->gt33_ll_sensor = s; }
            void set_gt33_setpoint_sensor(sensor::Sensor *s) { this->gt33_setpoint_sensor = s; }
            void set_sv3_setpoint_offset_sensor(sensor::Sensor *s) { this->sv3_setpoint_offset_sensor = s; }
            void set_pos_31_sensor(sensor::Sensor *s) { this->pos_31_sensor = s; }
            void set_pos_32_sensor(sensor::Sensor *s) { this->pos_32_sensor = s; }
            void set_pos_33_sensor(sensor::Sensor *s) { this->pos_33_sensor = s; }
            void set_elec_heat_pow_sensor(sensor::Sensor *s) { this->elec_heat_pow_sensor = s; }
            void set_pos_35_sensor(sensor::Sensor *s) { this->pos_35_sensor = s; }
            void set_pos_36_sensor(sensor::Sensor *s) { this->pos_36_sensor = s; }
            void set_default_sv2_open_sensor(sensor::Sensor *s) { this->default_sv2_open_sensor = s; }

            // Setter methods for binary sensors
            void set_press_switch_defrost_sensor(binary_sensor::BinarySensor *s) { this->press_switch_defrost_sensor = s; }
            void set_press_switch_high_sensor(binary_sensor::BinarySensor *s) { this->press_switch_high_sensor = s; }
            void set_press_switch_low_sensor(binary_sensor::BinarySensor *s) { this->press_switch_low_sensor = s; }
            void set_vacation_mode_sensor(binary_sensor::BinarySensor *s) { this->vacation_mode_sensor = s; }
            void set_compressor_in_op_sensor(binary_sensor::BinarySensor *s) { this->compressor_in_op_sensor = s; }
            void set_shunt_valve_opening_sensor(binary_sensor::BinarySensor *s) { this->shunt_valve_opening_sensor = s; }
            void set_shunt_valve_closing_sensor(binary_sensor::BinarySensor *s) { this->shunt_valve_closing_sensor = s; }
            void set_circ_pump_heat_carrier_sensor(binary_sensor::BinarySensor *s) { this->circ_pump_heat_carrier_sensor = s; }
            void set_fan_in_op_sensor(binary_sensor::BinarySensor *s) { this->fan_in_op_sensor = s; }
            void set_alarm_active_sensor(binary_sensor::BinarySensor *s) { this->alarm_active_sensor = s; }
            void set_external_p2_sensor(binary_sensor::BinarySensor *s) { this->external_p2_sensor = s; }
            
        protected:
            String input_string_;
            bool string_complete_{false};
            int16_t last_message_counter_value_{0}; // Stores the last known counter value
            uint32_t last_message_counter_timestamp_{0}; // Stores App.get_loop_component_start_time() when the counter last changed
            uint32_t last_data_read_time_{0}; // Timestamp for when data was last read from UART
            bool initial_counter_read_{false}; // Flag to handle the first reading after startup
            bool is_message_counter_stuck_{false}; // Flag to track if message_counter is stuck
            bool is_no_uart_data_error_{false}; // Flag to track if no data is coming from UART
            
            void fetch_serial_();
            void split_string_();
        };
    } // namespace ivt695reader
} // namespace esphome
