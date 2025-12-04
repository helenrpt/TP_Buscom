#ifndef GPIO_H_
#define GPIO_H_

void GPIO_Init(void);

void 		GPIO_SetPin(GPIO_TypeDef* GPIO, uint16_t pin);
void 		GPIO_ResetPin(GPIO_TypeDef* GPIO, uint16_t pin);
void 		GPIO_SetPullUp(GPIO_TypeDef* GPIO, uint16_t pin);
void 		GPIO_TogglePin(GPIO_TypeDef* GPIO, uint16_t pin);
uint16_t 	GPIO_ReadPin(GPIO_TypeDef* GPIO, uint16_t pin);

#endif
