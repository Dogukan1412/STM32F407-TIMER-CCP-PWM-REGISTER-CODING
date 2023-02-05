#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Led_Config(void);
void CLK_Config(void);
void TIM4_Config(void);


// pin D12 --> TIM4_CH1
// pin D13 --> TIM4_CH2
// pin D14 --> TIM4_CH3
// pin D15 --> TIM4_CH4

int main(void)
{
	Led_Config();
	CLK_Config();
	TIM4_Config();
  while (1)
  {
	  TIM4->CCR1 = 2499;			// pin D12 --> TIM4_CH1 25% duty cycle
	  TIM4->CCR2 = 4999;			// pin D13 --> TIM4_CH2 50% duty cycle
	  TIM4->CCR3 = 7499;			// pin D14 --> TIM4_CH3 75% duty cycle
	  TIM4->CCR4 = 9999;			// pin D15 --> TIM4_CH4 100% duty cycle
  }
}


void CLK_Config() // Clock speed for 168MHz
{
	RCC->CR |= 0x00010000;                 // HSEON ENABLE
	while(!(RCC->CR & 0x00020000));        // HSEON Ready Flag wait
	RCC->CR |= 0x00080000;              // CSS ENABLE
	RCC->CR |= 0x01000000;				// PLL ON
	RCC->PLLCFGR |= 0x00400000;        // PLL SRC HSE is selected
	RCC->PLLCFGR |= 0x00000004;       // PLL M 4
	RCC->PLLCFGR |= 0x00005A00;        // PLL N 168
	RCC->PLLCFGR |= 0x00000000;       // PLL P 2
	RCC->CFGR |= 0x00000000;          // AHB PRESCALER 1
	RCC->CFGR |= 0x00080000;          // APB2 PRESCALER 2
	RCC->CFGR |= 0x00001400;          // APB1 PRESCALER 4
	RCC->CIR |= 0x00080000;             // HSE READY FLAG CLEAR
	RCC->CIR |= 0x00800000;             // CSS FLAG CLEAR
}


void Led_Config(void)  // User led configuration
{
	RCC->AHB1ENR |= 0x1U << 3U; // D port clock enable

	GPIOD->MODER |= 0xAA000000; // pins D12, D13, D14, D15 is selected alternate mode
	GPIOD->OSPEEDR |= 0xFF000000; // very high speed is selected
	GPIOD->PUPDR |= 0x00000000; // no pull up, pull down

	GPIOD->AFR[1] |= 0x22220000;  // alternate function high register D12, D13, D14, D15
}


void TIM4_Config(void)
{
	RCC->APB1ENR |= 0x1U << 2U;				// timer4 clock bus enabled

	TIM4->CR1 |= 0x1U << 0U;				// counter enable
	TIM4->CR1 |= 0x0U << 4U;				// count up
	TIM4->CR1 |= 0x0U << 5U;				// edge aligned mod
	TIM4->CR1 |= 0x1U << 7U;				// TIM4_ARR register is buffered
	TIM4->CR1 |= 0x0U << 8U;				// clock divided 1
	TIM4->SMCR |= 0x0U << 0U;				// slave mode disable
	TIM4->PSC = 8399;						// prescaler = 8399
	TIM4->ARR = 9999;						// period = 9999

	//  84 000 000 / ( (9999 + 1) * (8399 + 1) ) = 1 Hertz = 1 second

	TIM4->CCMR1 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12;			// CC1 AND CC2 channel is configured output and pwm
	TIM4->CCMR2 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12;			// CC3 AND CC4 channel is configured output and pwm
	TIM4->CCER |= 1 << 12 | 1 << 8 | 1 << 4 | 1 << 0;			// On - OC1, OC2, OC3, OC4 signals are output on the corresponding output pin
}





/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
