# IVT695reader - ESPHome External Component

An ESPHome external component to monitor and control the **IVT 695 Twin** (Rego 455) geothermal heat pump.

This project uses an ESP8266 (typically a D1 Mini) to bridge the gap between your legacy heat pump and modern home automation like Home Assistant. It utilizes a hybrid approach: passive UART data eavesdropping combined with hardware-level button and encoder simulation.

## Features

* **Comprehensive Monitoring:** Parses the Rego 455 serial broadcast to provide real-time data for sensors, diagnostics, and operations.
* **Full Hardware Emulation:** Simulates physical interactions with the heat pump's control panel (Rotary encoder and dual buttons) using `open_drain` GPIO control.
* **Smart Hot Water Management:** Custom ESPHome logic to trigger and track "Additional Hot Water" (Shower mode) duration, including an auto-decreasing timer.
* **LED Status Sensing:** Monitors the front panel LEDs to detect system Alarms, Anti-legionella cycles, and Electric Heater activity.

## Hardware Setup

The project interfaces with the heat pump in three ways: Data (UART), Control (GPIO simulation), and Feedback (LED sensing).

### Visual Reference

*Front view of the Rego 455 board with the ESP8266 mounted.*
![Front view](https://github.com/skracke/IVT695reader/blob/main/IMG_1114.HEIC_compressed.JPEG?raw=true)

*Back view showing diagnostic port and power tap points.*
![Back view](https://github.com/skracke/IVT695reader/blob/main/IMG_1118.HEIC_compressed.JPEG?raw=true)

*Detail of the resistor ladder and 5V power connection.*
![Wiring detail](https://github.com/skracke/IVT695reader/blob/main/IMG_1115.HEIC_compressed.JPEG?raw=true)

### Detailed Wiring List

| ESP8266 Pin | Target / Component | Connection Logic |
| :--- | :--- | :--- |
| **TX** | Diagnostic Port RX | Serial communication to Rego 455 |
| **RX** | Diagnostic Port TX | Serial communication from Rego 455 |
| **D1** | Rotary Encoder (Left) | + 22k resistor to GND (Voltage divider) |
| **D2** | Rotary Encoder (Right) | + 22k resistor to GND (Voltage divider) |
| **D3** | Right Button | + 22k resistor to GND (Voltage divider) |
| **D4** | Left Button | + 22k resistor to GND (Voltage divider) |
| **D5** | Alarm LED | via 0.47k resistor |
| **D6** | Additional Hot Water LED | via 0.47k resistor |
| **D7** | Electric Heater LED | via 0.47k resistor |
| **G (GND)** | Rotary Encoder (Middle) | Common System Ground |
| **5V** | 5V Power Source | See red wire in wiring detail image |

> [!CAUTION]
> **Voltage Warning:** The Rego 455 panel operates on 5V logic. The 22k resistors listed above function as voltage dividers to protect the 3.3V ESP8266 pins. **Do not omit these resistors** as it may permanently damage your ESP8266.

## Technical Details

### UART Logic & Parsing
The component expects a semicolon-separated string of **37 values** from the heat pump, transmitted approximately every 60 seconds via the diagnostic port.

* **Scaling:** Most temperature values are received as integers and scaled by `0.1` (e.g., `215` becomes `21.5°C`). Electric heating power is scaled by a factor of `9.0`.
* **Error Handling:**
  * **Timeout:** If no UART data is received for **65 seconds**, the component enters an error state (`no_uart_data`).
  * **Stuck Counter:** If the message counter remains identical for more than 65 seconds, the component flags a `message_counter_stuck` error.

## Configuration & YAML Usage

### Basic Setup
```yaml
external_components:
  - source:
      type: git
      url: [https://github.com/skracke/IVT695reader](https://github.com/skracke/IVT695reader)
    components: [ ivt695reader ]

uart:
  id: uart_bus
  tx_pin: GPIO1
  rx_pin: GPIO3
  baud_rate: 9600

ivt695reader:
  id: ivt_bus
  uart_id: uart_bus
```

### Adding Sensors
```yaml
sensor:
  - platform: ivt695reader
    gt1_supply_temp:
      name: "Supply Temperature"
    elec_heat_pow:
      name: "Electrical Heater Power"

binary_sensor:
  - platform: ivt695reader
    compressor_in_op:
      name: "Compressor Running"
    alarm_active:
      name: "Heat Pump Alarm"
```

## Disclaimer
This is a DIY project involving hardware modification of an expensive appliance. Incorrect wiring can damage the Rego 455 board. Use at your own risk.
