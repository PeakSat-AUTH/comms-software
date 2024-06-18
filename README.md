# COMMS Software

This repository contains the code that will run on the STM32H743 Microcontroller Unit, which is a
32-bit ARM Cortex-M7 core, on the AcubeSAT's
COMMS Board. The business logic is orchestrated by FreeRTOS tasks on the MCU.
You can check the instructions here on how to set up the toolchain to run the repository's code
### Software to be implemented
Business Logic regarding:
  - the board's [component drivers](https://gitlab.com/acubesat/comms/software/component-drivers) (transceiver, sensors, memory)
  - the Power Distribution Network and the RF Frontend
  - the [CCSDS Data Layer](https://gitlab.com/acubesat/comms/software/ccsds-telemetry-packets) and [Physical Layer](https://gitlab.com/acubesat/comms/software/physical_layer)
  - CAN inter-communication
  - ECSS Services used by COMMS

This project also relies on the [Cross Platform Software](https://gitlab.com/acubesat/obc/cross-platform-software)
repository, created to accomodate the common functionality for all of the satellite's platforms. It's
full integration with COMMS Software is still a work in progress

## Build instructions

```bash
git clone --recurse-submodules <HTTPS or SSH repo link>
cd comms_software
```
If you are using CLion you can `Reload CMake Project` and then build from the GUI.

In case you want to build the project from CLI
```bash
mkdir build && cd build
cmake ..
cmake --build . --target STM32H7A3ZIQSetup.elf -- -j 6
```

In order to upload the executable to a physical Nucleo Board you can run the following command in CLI
```bash
openocd -s /usr/share/openocd/scripts -f {PATH TO PROJECT}/stm32h7x3i_eval.cfg -c "tcl_port disabled" -c "gdb_port disabled" -c "tcl_port disabled" -c "program \"{PATH TO PROJECT}/build/STM32H7A3ZIQSetup.elf\"" -c reset -c shutdown
```
where you replace the `{PATH TO PROJECT}` part with the relative directory (to the working directory you run the command in) where the repository lies
