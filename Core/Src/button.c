
#include "button.h"

void button_led_toggle_test();
int get_button(GPIO_TypeDef *GPIO, int GPIO_Pin, int button_num);

void button_led_toggle_test()
{
	// 버튼을 한번 눌렀다 떼면 led가 toggle되도록 code를 구현
	if(get_button(GPIOC, GPIO_PIN_0, BTN0) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	}
	if(get_button(GPIOC, GPIO_PIN_1, BTN1) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
	}
	if(get_button(GPIOC, GPIO_PIN_2, BTN2) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
	}
	if(get_button(GPIOC, GPIO_PIN_3, BTN3) == BUTTON_PRESS)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	}
	if(get_button(GPIOC, GPIO_PIN_13, BTN4) == BUTTON_PRESS)	// Demo b'd
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}
}

int get_button(GPIO_TypeDef *GPIO, int GPIO_Pin, int button_num)
{
	// 지역 변수에 static을 쓰면 전역 변수처럼 함수를 빠져나갔다 다시 들어 와도 값을 유지한다.
	static unsigned char button_status[BUTTON_NUMER] =
	{BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE};

	int currtn_state;

	currtn_state = HAL_GPIO_ReadPin(GPIO, GPIO_Pin);	// 버튼을 읽는다.
	if (currtn_state == BUTTON_PRESS && button_status[button_num] == BUTTON_RELEASE)	// 버튼이 처음 눌려진 noise
	{
		HAL_Delay(60);	// noise가 지나가기를 기다린다.
		button_status[button_num] = BUTTON_PRESS;	// noise가 지나간 상태의 High 상태
		return BUTTON_RELEASE;	// 아직은 완전히 눌렸다 떼어지 상태가 아니다.
	}
	else if (currtn_state == BUTTON_RELEASE && button_status[button_num] ==  BUTTON_PRESS)
	{
		HAL_Delay(60);
		button_status[button_num] = BUTTON_RELEASE;	// 다음 버튼 체크를 위해서 초기화
		return BUTTON_PRESS;	// 완전히 1번 눌렸다 뗴어진 상태로 인정
	}
	return BUTTON_RELEASE;	// 버튼이 open인 상태
}
