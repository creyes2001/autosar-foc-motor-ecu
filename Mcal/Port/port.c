#include "port.h"

static uint8 Port_GetPinNumber(Port_PinType Pin);
static GPIO_TypeDef* Port_GetGpioBase(Port_PinType Pin);
static void Port_SetPinSpeed(Port_PinType Pin,Port_PinSpeedType speed);
static void Port_SetOutputType(Port_PinType Pin,Port_PinOutputType outputType);
static void Port_SetResistorType(Port_PinType Pin,Port_PinResistorType resistorType);
static void Port_LockPinType(Port_PinType Pin);

void Port_Init(const Port_ConfigType* ConfigPtr){
	
	Port_ConfigDataType* ConfigData = ConfigPtr->Port_ConfigData;
	for(uint32 i = 0; i < ConfigPtr->size; i++){
		Port_SetPinMode(ConfigData[i]->PinId,ConfigData[i]->Pin_Mode);
		Port_SetPinSpeed(ConfigData[i]->PinId,ConfigData[i]->Pin_Speed);
		Port_SetOutputType(ConfigData[i]->PinId,ConfigData[i]->Pin_OutputType);
		Port_SetResistorType(ConfigData[i]->PinId,ConfigData[i]->Pin_ResistorType);
		
		if(!ConfigData[i]->DirectionChangable || ConfigData[i]->ModeCangable){
				Port_LockPinType(ConfigData[i]->PinId);
		}
	}

}

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction){
	uint8 pin = Port_GetPiNumber(Pin);
	
	if(Direction == PORT_PIN_IN){
		port->MODER &= ~(3 << (pin * 2));
	}
	else{
		port->MODER &= ~(3 << (pin * 2));
		port->MODER |= (1 << (pin * 2));
	}
}


void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode){
	uint8 pin = Port_GetPiNumber(Pin);
	GPIO_TypeDef* port = Port_GetPinBase(Pin);
	//PORT_PIN_MODE_AF0 must be 0
	port->MODER &= ~(3 << (pin * 2));
	
	if(Mode >= PORT_PIN_MODE_AF0 && Mode <= PORT_PIN_MODE_AF15){
		port->MODER |= (2 << (pin * 2));
		
		if(Mode <= PORT_PIN_MODE_AF7){
			port->AFR[0] &= ~(15 << (Mode * 4)); 
			port->AFR[0] |= (Mode << (Mode * 4)); 
		}
		else{
			port->AFR[1] &= ~(15 << (Mode * 4)); 
			port->AFR[1] |= (Mode << (Mode * 4)); 
		}

	}

	else{

		switch(Mode){
			case PORT_PIN_MODE_DI:
				port->MODER &= ~(3 << (pin * 2));
				break;

			case PORT_PIN_MODE_DO:
				port->MODER |= (1 << (pin * 2));
				break;

			case PORT_PIN_MODE_ANALOG:
				port->MODER |= (3 << (pin * 2));
				break;

			default:
				break;
		}

	}
}

static uint8 Port_GetPinNumber(Port_PinType Pin){
	uint8 pin = 0;
	do{
		pin = Pin / 16;
		if(pin >= 1){
			Pin -= 16;
		}
	}while(pin > 1);
	return Pin;
}

static GPIO_TypeDef* Port_GetGpioBase(Port_PinType Pin){
	if(Pin <= 0x0F){
		return GPIOA;
	}
	else if(Pin >= 0x10 && Pin <= 0x1F){
		return GPIOB;
	}
	else if(Pin >= 0x20 && Pin <= 0x2F){
		return GPIOC;
	}
	else if(Pin >= 0x30 && Pin <= 0x31){
		return GPIOD;
	}
	else{
		return GPIOF;
	}
}

static void Port_SetPinSpeed(Port_PinType Pin,Port_PinSpeedType speed){
	uint8 pin = Port_GetPiNumber(Pin);
	GPIO_TypeDef* port = Port_GetPinBase(Pin);
	port->OSPEEDR &= ~(3 << 2 * pin);
	switch(speed){
		case PORT_PIN_LOW_SPEED:
			port->OSPEEDR &= ~(3 << 2 * pin);
			break;

		case PORT_PIN_MEDIUM_SPEED:		
			port->OSPEEDR |= (1 << 2 * pin);
			break;

		case PORT_PIN_FAST_SPEED:
			port->OSPEEDR |= (2 << 2 * pin);
			break;

		case PORT_PIN_HIGH_SPEED:
			port->OSPEEDR |= (3 << 2 * pin);
			break;

		default:
			break;

	}
}

static void Port_SetOutputType(Port_PinType Pin,Port_PinOutputType outputType){
	uint8 pin = Port_GetPiNumber(Pin);
	GPIO_TypeDef* port = Port_GetPinBase(Pin);
	port->OTYPER &= ~(1 << pin);
	
	if(outputType == PORT_PIN_PUSH_PULL){
		port->OTYPER &= ~(1 << pin);
	}
	else{
		port->OTYPER |= (1 << pin);
	}
}

static void Port_SetResistorType(Port_PinType Pi,nPort_PinResistorType resistorType){
	uint8 pin = Port_GetPiNumber(Pin);
	GPIO_TypeDef* port = Port_GetPinBase(Pin);
	port->PUPDR &= ~(3 << (2 * pin));

	switch(resistorType){
		case PORT_PIN_RESISTOR_PULLUP:
			port->PUPDR |= (1 << (2 * pin));
			break;

		case PORT_PIN_RESISTOR_PULLDOWN:
			port->PUPDR |= (2 << (2 * pin));
			break;

		case PORT_PIN_RESISTOR_DISABLE:
			port->PUPDR &= ~(3 << (2 * pin));
			break;
	}
}

static void Port_LockPinType(Port_PinType Pin){
	uint8 pin = Port_GetPiNumber(Pin);
	GPIO_TypeDef* port = Port_GetPinBase(Pin);

	uint32 lck = 0x00000000;
	
	lck |= (1U << pin);
	lck |= (1U << 16U);
	port->LCKR = lck;
	lck &= ~(1U << 16U);
	port->LCKR = lck;
	lck |= (1U << 16U);
	port->LCKR = lck;
	(void)port->LCKR;
	(void)port->LCKR;
}
