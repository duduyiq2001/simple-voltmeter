# ATmega32 Voltmeter with Keypad and LCD Interface

This project implements a digital voltmeter using an **ATmega32 microcontroller** on a breadboard. The voltmeter reads input voltage through an analog-to-digital (AD) input, processes it, and displays four key measurements on a 16x2 LCD: **instantaneous voltage**, **maximum voltage**, **minimum voltage**, and **average voltage**. The system is controlled through a keypad, enabling users to reset or initiate sampling, and utilizes the ATmega32's timer/interrupt functionality for precise sampling.

## Project Overview

This voltmeter project showcases a fully functional embedded system design centered on the ATmega32. It is designed to:
- Take analog voltage readings every 500 ms.
- Display real-time voltage measurements on an LCD.
- Allow user interaction through a keypad to reset or start sampling.
- Calculate and display key statistics: current, max, min, and average voltage values.

## Features

- **Real-Time Voltage Measurement**: Samples analog voltage at precise 500 ms intervals.
- **Statistics Display**: Displays instantaneous, maximum, minimum, and average voltage.
- **User Control**: Keypad enables resetting values and starting sampling.
- **LCD Interface**: Displays readings and statistics in a clear, readable format.
- **Timer/Interrupt Precision**: Uses ATmega32’s timer/interrupt for accurate timing of sampling intervals.

## Components

- **ATmega32 Microcontroller**: Handles ADC conversion, processing, and timing.
- **16x2 LCD Module**: Displays the real-time voltage values.
- **Keypad**: Provides user input for resetting values and controlling sampling.
- **Voltage Divider (Optional)**: For scaling input voltage to ADC range.
- **Breadboard**: Used for circuit assembly and component interfacing.

## Circuit Design

- **Analog Input**: Voltage input is connected to one of the ATmega32’s ADC channels.
- **Keypad Interface**: Connects to ATmega32 for user input.
- **LCD Display**: Connected to the ATmega32 for showing voltage readings and statistics.
- **Timing Circuitry**: Utilizes ATmega32’s internal timer for 500 ms sampling intervals.

## Functionality

1. **Analog-to-Digital Conversion**: The ATmega32 samples the input voltage using its ADC at the highest available precision.
2. **Voltage Calculation**: Voltage is calculated based on ADC values and is updated every 500 ms.
3. **Display Parameters**:
   - **Instantaneous Voltage**: Current voltage reading.
   - **Max Voltage**: Highest recorded voltage since the last reset.
   - **Min Voltage**: Lowest recorded voltage since the last reset.
   - **Average Voltage**: Average voltage calculated from samples taken since the last reset.
4. **Reset and Sampling Control**: 
   - **Reset**: Resets all voltage parameters to blank values (----).
   - **Start Sampling**: Begins the ADC sampling and updates the display accordingly.
5. **Timer/Interrupt**: Ensures precise 500 ms intervals between samples.

### Formula for Voltage Calculation
The input voltage (\(V_{in}\)) is calculated using:
\[
V_{in} = \left(\frac{\text{ADC Value}}{1023}\right) \times V_{ref}
\]
where:
- **ADC Value**: 10-bit ADC result (0-1023).
- **Vref**: Reference voltage for the ADC.

## Software Implementation

- **Programming Language**: C, optimized for embedded systems.
- **Modules**:
  - **ADC Module**: Initializes and reads from the ADC.
  - **Timer/Interrupt Module**: Configures timer interrupts to trigger every 500 ms.
  - **Keypad Module**: Captures and interprets user inputs for reset and sampling.
  - **LCD Module**: Initializes and displays voltage readings on the LCD.

### Key Functions
- `ADC_init()`: Sets up ADC for high-precision voltage reading.
- `start_sampling()`: Initiates the voltage sampling process.
- `update_display()`: Calculates and updates the LCD with instantaneous, max, min, and average voltage.
- `reset_values()`: Clears all stored voltage data upon keypad reset command.

## Getting Started

### Prerequisites

- **ATmega32 Development Board** or equivalent setup.
- **AVR Programming Tools**: To compile and upload code.
- **16x2 LCD Module** and **Keypad**: For display and user input.
- **Breadboard and Wiring**: For circuit assembly.

### Setup Instructions

1. **Assemble the Circuit**:
   - Connect the voltage input to the ADC pin.
   - Connect the keypad for input control.
   - Interface the LCD to the ATmega32 to display readings.
2. **Upload the Code**:
   - Compile and upload the code using an AVR-compatible toolchain.
3. **Run the System**:
   - Power the circuit.
   - Use the keypad to start sampling and observe the measurements on the LCD.

## Notes

- **Voltage Range**: Keep input within the ATmega32’s ADC limits or use a voltage divider for higher voltages.
- **Calibration**: Accurate resistor values are recommended for precise voltage readings.
- **LCD Refresh Rate**: Sampling every 500 ms may cause slight delays in the display update; this is normal for embedded timing.
