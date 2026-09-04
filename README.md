# FOC Motor Control (AUTOSAR-inspired)

FOC motor control for a BLDC/PMSM motor, built on an AUTOSAR-inspired layered architecture. I chose this structure for learning purposes and to keep drivers portable across different MCUs.

## Hardware

- **MCU:** NUCLEO-G431RB (STM32G431RB)
- **Motor:** GBM2804H-100T brushless gimbal motor
- **Motor driver:** STSPIN830
- **Encoder:** AS5600 magnetic encoder
- **Power supply:** 12V DC

## Status
- [x] Mcu module — clock configuration
- [x] Port module — pin configuration
- [ ] ADC driver — in progress
- [ ] PWM driver
- [ ] FOC control loop
