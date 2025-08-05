// File: esphome/components/ivt695reader/ivt695reader.cpp
#include "ivt695reader.h"
#include <cstring> // For strtok and strlen
#include "esphome/core/application.h" // Include for App.get_loop_component_start_time()
#include "esphome/core/component.h" // Ensure Component class is known
#include <algorithm> // For std::min
#include <cctype> // For isdigit

namespace esphome
{
    namespace ivt695reader
    {
        // Define constants for better readability and maintainability
        static const char *const TAG = "ivt695reader.component"; // Uses const for TAG
        static const int NUM_IVT_VALUES = 37; // Number of expected values in the message string
        static const float TEMP_SCALE_FACTOR = 10.0f; // Scaling factor for temperature values (division by 10)
        static const float ELEC_HEAT_POWER_FACTOR = 9.0f; // Multiplication factor for electric heating power
        
        // Timeout for when no data is received from UART (e.g., 65 seconds)
        static const uint32_t NO_UART_DATA_THRESHOLD_MS = 65 * 1000; 

        void IVT695Reader::setup()
        {
            // Initialize timestamps at startup
            this->last_message_counter_timestamp_ = App.get_loop_component_start_time();
            this->last_data_read_time_ = App.get_loop_component_start_time(); 
            
            // At startup, the component is initially available (no error status)
            this->status_clear_error();
            this->is_message_counter_stuck_ = false; 
            this->is_no_uart_data_error_ = false; 
        }

        void IVT695Reader::loop()
        {
            uint32_t current_time = App.get_loop_component_start_time();

            // Check if no data has been read from UART for too long
            if (!this->is_no_uart_data_error_ && (current_time - this->last_data_read_time_ > NO_UART_DATA_THRESHOLD_MS)) {
                ESP_LOGW(TAG, "No data received from UART for over %u ms. Setting component to error status.", NO_UART_DATA_THRESHOLD_MS);
                this->status_set_error("no_uart_data");
                this->is_no_uart_data_error_ = true;
                // If we detect no UART data, we can also assume the counter is stuck
                this->is_message_counter_stuck_ = true;
            }

            // Check if data is available in the UART buffer
            if (available())
            {
                this->fetch_serial_();
            }
            // If a complete string has been received, process it
            if (this->string_complete_)
            {
                this->split_string_();
            }
        }

        void IVT695Reader::fetch_serial_()
        {
            char in_char;
            // Read characters from UART until a newline character ('\n') is found
            while (available())
            {
                in_char = read();
                this->last_data_read_time_ = App.get_loop_component_start_time(); // Update timestamp on each character read

                // If we were previously in "no UART data" error, clear it now
                if (this->is_no_uart_data_error_) {
                    ESP_LOGI(TAG, "UART data flow resumed. Clearing component error status.");
                    this->status_clear_error();
                    this->is_no_uart_data_error_ = false;
                }

                // Filter out all characters except digits, semicolons, and minus signs
                // The newline character is handled separately to mark the end of the message.
                if (isdigit(in_char) || in_char == ';' || in_char == '-')
                {
                    this->input_string_ += in_char;
                }
                // If a newline character is found, mark the string as complete and stop reading
                if (in_char == '\n') {
                    this->string_complete_ = true;
                    break; // Exit the loop once the entire message has been read
                }
            }
            // Log the received string for debugging if it's complete
            if (this->string_complete_) {
                // Log the entire string on one line again, now that we filter out problematic characters
                ESP_LOGD(TAG, "Input string (raw, no spaces): %s", this->input_string_.c_str());
            }
        }

        void IVT695Reader::split_string_()
        {
            // Convert Arduino String to a C-string (char array) for strtok
            // Add 1 for the null terminator
            char temp_input_string[this->input_string_.length() + 1];
            this->input_string_.toCharArray(temp_input_string, sizeof(temp_input_string));

            char *token;
            float ivt[NUM_IVT_VALUES]; // Uses constant
            int c = 0; // Counter for number of parsed values

            // Get the first token
            token = strtok(temp_input_string, ";");

            // Loop through the string and parse the values
            while (token != nullptr && c < NUM_IVT_VALUES) // Uses constant
            {
                // Convert token to float and store in ivt array
                ivt[c] = atof(token);
                c++; // Go to next index

                // Get the next token
                token = strtok(nullptr, ";");
            }

            // Error handling: Check if the correct number of values were parsed
            if (c != NUM_IVT_VALUES) { // Uses constant
                ESP_LOGE(TAG, "Parsing error: Expected %d values, but got %d.", NUM_IVT_VALUES, c); // Uses constant
                // Reset the string and flag even on error to avoid infinite loop
                this->string_complete_ = false;
                this->input_string_ = "";
                // Set component to error status on parsing error
                if (!this->is_message_counter_stuck_) { 
                    this->status_set_error("parsing_error");
                    this->is_message_counter_stuck_ = true; 
                }
                return; // Abort function on error
            }

            // Publish message_counter and handle its status
            if (this->message_counter_sensor != nullptr) {
                int16_t current_message_counter = (int16_t)ivt[0];
                this->message_counter_sensor->publish_state(current_message_counter);

                // Update counter value and timestamp
                bool counter_has_changed = (current_message_counter != this->last_message_counter_value_);

                if (!this->initial_counter_read_) {
                    // First reading after startup
                    this->last_message_counter_value_ = current_message_counter;
                    this->last_message_counter_timestamp_ = App.get_loop_component_start_time();
                    this->initial_counter_read_ = true;
                    // Ensure component is in normal status on first successful read
                    if (this->is_message_counter_stuck_) { 
                        ESP_LOGI(TAG, "Initial message counter read successful. Clearing component error status.");
                        this->status_clear_error();
                        this->is_message_counter_stuck_ = false; 
                    }
                } else {
                    if (counter_has_changed) {
                        this->last_message_counter_value_ = current_message_counter;
                        this->last_message_counter_timestamp_ = App.get_loop_component_start_time();
                        if (this->is_message_counter_stuck_) { // Counter started moving again 
                            ESP_LOGI(TAG, "Message counter started moving again. Clearing component error status.");
                            this->status_clear_error();
                            this->is_message_counter_stuck_ = false; 
                        }
                    } else {
                        // Counter has not changed. Check if too much time has passed.
                        // Heat pump sends data every 59 seconds. Give it 65 seconds for tolerance.
                        const uint32_t STUCK_THRESHOLD_MS = 65 * 1000; // Reset for normal operation

                        if (!this->is_message_counter_stuck_ && (App.get_loop_component_start_time() - this->last_message_counter_timestamp_ > STUCK_THRESHOLD_MS)) { 
                            ESP_LOGW(TAG, "Message counter has not changed for over %u ms. Setting component error status.", STUCK_THRESHOLD_MS);
                            this->status_set_error("message_counter_stuck");
                            this->is_message_counter_stuck_ = true; 
                        }
                    }
                }
            }

            // Publish other sensor values
            if (this->gt1_supply_temp_sensor != nullptr)
                this->gt1_supply_temp_sensor->publish_state(ivt[1] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt2_outside_temp_sensor != nullptr)
                this->gt2_outside_temp_sensor->publish_state(ivt[2] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt31_water_tank_temp_sensor != nullptr)
                this->gt31_water_tank_temp_sensor->publish_state(ivt[3] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt32_water_tank_temp_sensor != nullptr)
                this->gt32_water_tank_temp_sensor->publish_state(ivt[4] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt33_water_tank_temp_sensor != nullptr)
                this->gt33_water_tank_temp_sensor->publish_state(ivt[5] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt5_room_temp_sensor != nullptr)
                this->gt5_room_temp_sensor->publish_state(ivt[6] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt6_compressor_temp_sensor != nullptr)
                this->gt6_compressor_temp_sensor->publish_state(ivt[7] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt10_brine_temp_sensor != nullptr)
                this->gt10_brine_temp_sensor->publish_state(ivt[8] / TEMP_SCALE_FACTOR); // Uses constant

            // Binary sensors
            if (this->press_switch_defrost_sensor != nullptr)
                this->press_switch_defrost_sensor->publish_state(ivt[9] != 0);

            if (this->press_switch_high_sensor != nullptr)
                this->press_switch_high_sensor->publish_state(ivt[10] != 0);

            if (this->press_switch_low_sensor != nullptr)
                this->press_switch_low_sensor->publish_state(ivt[11] != 0);

            if (this->vacation_mode_sensor != nullptr)
                this->vacation_mode_sensor->publish_state(ivt[12] != 0);

            if (this->compressor_in_op_sensor != nullptr)
                this->compressor_in_op_sensor->publish_state(ivt[13] != 0);

            if (this->shunt_valve_opening_sensor != nullptr)
                this->shunt_valve_opening_sensor->publish_state(ivt[14] != 0);

            if (this->shunt_valve_closing_sensor != nullptr)
                this->shunt_valve_closing_sensor->publish_state(ivt[15] != 0);

            if (this->circ_pump_heat_carrier_sensor != nullptr)
                this->circ_pump_heat_carrier_sensor->publish_state(ivt[16] != 0);

            if (this->fan_in_op_sensor != nullptr)
                this->fan_in_op_sensor->publish_state(ivt[17] != 0);

            if (this->alarm_active_sensor != nullptr)
                this->alarm_active_sensor->publish_state(ivt[18] != 0);

            if (this->external_p2_sensor != nullptr)
                this->external_p2_sensor->publish_state(ivt[19] != 0);

            // Additional analog sensors
            if (this->gt1_llt_sensor != nullptr)
                this->gt1_llt_sensor->publish_state(ivt[20] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt1_ll_sensor != nullptr)
                this->gt1_ll_sensor->publish_state(ivt[21] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt1_setpoint_sensor != nullptr)
                this->gt1_setpoint_sensor->publish_state(ivt[22] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt1_ul_sensor != nullptr)
                this->gt1_ul_sensor->publish_state(ivt[23] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt32_ll_sensor != nullptr)
                this->gt32_ll_sensor->publish_state(ivt[24] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt32_ult_sensor != nullptr)
                this->gt32_ult_sensor->publish_state(ivt[25] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt32_ul_sensor != nullptr)
                this->gt32_ul_sensor->publish_state(ivt[26] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt33_ll_sensor != nullptr)
                this->gt33_ll_sensor->publish_state(ivt[27] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->gt33_setpoint_sensor != nullptr)
                this->gt33_setpoint_sensor->publish_state(ivt[28] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->sv3_setpoint_offset_sensor != nullptr)
                this->sv3_setpoint_offset_sensor->publish_state(ivt[29] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->pos_31_sensor != nullptr)
                this->pos_31_sensor->publish_state(ivt[30] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->pos_32_sensor != nullptr)
                this->pos_32_sensor->publish_state(ivt[31] / TEMP_SCALE_FACTOR); // Använder konstant

            if (this->pos_33_sensor != nullptr)
                this->pos_33_sensor->publish_state(ivt[32] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->elec_heat_pow_sensor != nullptr)
                this->elec_heat_pow_sensor->publish_state(ivt[33] * ELEC_HEAT_POWER_FACTOR); // Uses constant

            if (this->pos_35_sensor != nullptr)
                this->pos_35_sensor->publish_state(ivt[34] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->pos_36_sensor != nullptr)
                this->pos_36_sensor->publish_state(ivt[35] / TEMP_SCALE_FACTOR); // Uses constant

            if (this->default_sv2_open_sensor != nullptr)
                this->default_sv2_open_sensor->publish_state(ivt[36] / TEMP_SCALE_FACTOR); // Uses constant

            // Reset the flag and string for the next message
            this->string_complete_ = false;
            this->input_string_ = "";
        }

        void IVT695Reader::dump_config()
        {
            ESP_LOGCONFIG(TAG, "IVT 695 Heat Pump Reader:");
            ESP_LOGCONFIG(TAG, "  All %d sensors configured", NUM_IVT_VALUES); // Uses constant
        }
    } // namespace ivt695reader
} // namespace esphome
