# FOC Motor Control (AUTOSAR-inspired)

FOC motor control for a BLDC/PMSM motor, built on an AUTOSAR-inspired layered architecture. I chose this structure for learning purposes and to keep drivers portable across different MCUs.

## Hardware

- **MCU:** NUCLEO-G431RB (STM32G431RB)
- **Motor:** GBM2804H-100T brushless gimbal motor
- **Motor driver:** STSPIN830
- **Encoder:** AS5600 magnetic encoder
- **Power supply:** 12V DC

## Status
- [x] Mcu driver — Clock configuration
- [x] Port driver — Pin configuration
- [x] ADC driver — Configurable channel groups
- [x] PWM driver — Configurable PWM channels
- [x] GPT driver — Timer compare channels
- [x] NVIC driver — ISR priority configuration
- [ ] I2C driver — Master transfers (in progress)
- [ ] FOC control loop

## Project structure
```
.
├── Application/         # Application layer (planned)
├── Bsw/
│   ├── Cdd/             # Complex device drivers
│   ├── EcuAbstraction/  # Motor-control HAL (planned)
│   └── Services/
├── Cmsis/               # ARM / ST CMSIS headers
├── Common/              # Std_Types.h, Platform_Types.h
├── Mcal/
│   ├── Adc/             # Channel groups, injected/regular, SW/HW trigger
│   ├── Gpt/             # Timer and compare channels
│   ├── Mcu/             # PLL / clock setup
│   ├── Port/            # Pin configuration and locking
│   ├── Pwm/             # PWM channels
│   ├── mcal.c / mcal.h  # MCAL init entry point
├── Platform/
│   ├── Nvic/            # ISR priority configuration
│   ├── startup_stm32g431xx.s
│   ├── STM32G431RBTX_FLASH.ld
│   └── system_stm32g4xx.c
├── Rte/                 # Runtime environment (planned)
├── main.c
├── Makefile
└── STM32G431.svd        # Register description for debugging

```

## Build

### Requirements
- arm-none-eabi-gcc 
- GNU Make
- OpenOCD
- ST-Link (built into the Nucleo-G431RB)

### Commands
make            # build, output in build/
make flash      # flash through OpenOCD
make clean

