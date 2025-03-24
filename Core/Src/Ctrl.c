#include "main.h"
#include "Ctrl.h"
#include "math.h"
#include "Calculate.h"
/* USER CODE BEGIN 1 */
short KNOB_L_FLAG,KNOB_R_FLAG;
int binary[4] ;
int highByte[6] ;
int lowByte[6] ;
uint8_t TXData[10]; 
int32_t LX,LY,RX,RY;
uint16_t ADC_Value[BIT]; 
uint8_t ADC1_Flag; 
uint32_t LXtemp=0, LYtemp=0, RXtemp=0, RYtemp=0,LXhistory1=0,LYhistory1=0, RXhistory1=0, RYhistory1=0,LXhistory2=0,LYhistory2=0, RXhistory2=0, RYhistory2=0;
uint32_t LXmax=2048,LXmid=2048,LXmin=2048,LYmax=2048,LYmid=2048,LYmin=2048,RXmax=2048,RXmid=2048,RXmin=2048,RYmax=2048,RYmid=2048,RYmin=2048;
uint8_t emergencySuspensionFlag=0;
uint16_t emergencySuspensionTimer=0;
uint8_t emergencySuspend=0x00;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_7)
	{
		switch(KNOB_L2){
			case 0: KNOB_L_FLAG=1;break;
			case 1: KNOB_L_FLAG=2;break;
		}
	}
	if(GPIO_Pin==GPIO_PIN_9)
	{
		switch(KNOB_R2){
			case 0: KNOB_L_FLAG=1;break;
			case 1: KNOB_L_FLAG=2;break;
		}
	}

}
/* USER CODE END 1 */

void Update_BOTTOM(void)
{
		static uint8_t current_bot=0;
	
		//PACK1
		if(BOTTOM_1==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_1_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_1_OFF;
		}
		
		if(BOTTOM_2==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_2_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_2_OFF;
		}

		if(BOTTOM_3==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_3_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_3_OFF;
		}

		if(BOTTOM_4==0)//A
		{
				 TXData[BUTTON_PACKET] |= BOTTOM_4_ON;  
		}
		else
		{
				 TXData[BUTTON_PACKET] &= BOTTOM_4_OFF;
		}
						
//		if(BOTTOM_5==0)//A
//		{
//				 TXData[BUTTON_PACKET] |= BOTTOM_5_ON;  
//		}
//		else
//		{
//				 TXData[BUTTON_PACKET] &= BOTTOM_5_OFF;
//		}

//		if(BOTTOM_6==0)//A
//		{
//				 TXData[BUTTON_PACKET] |= BOTTOM_6_ON;  
//		}
//		else
//		{
//				 TXData[BUTTON_PACKET] &= BOTTOM_6_OFF;
//		}

//		if(BOTTOM_7==0)//A
//		{
//				 TXData[BUTTON_PACKET] |= BOTTOM_7_ON;  
//		}
//		else
//		{
//				 TXData[BUTTON_PACKET] &= BOTTOM_7_OFF;
//		}

//		if(BOTTOM_8==0)//A
//		{		
//				current_bot=1;
//				TXData[BUTTON_PACKET] |= BOTTOM_8_ON;  
//		}
//		else
//		{		
//				current_bot=0;
//				TXData[BUTTON_PACKET] &= BOTTOM_8_OFF;
//		}


		//PACK2
		if(SWITCH_1==0)
		{
				 TXData[SWITCH_PACKET] |= SWITCH_1_ON;  
		}
		
		else
		{
				 TXData[SWITCH_PACKET] &= SWITCH_1_OFF;
		}
		
		if(SWITCH_2==0)//A
		{
				 TXData[SWITCH_PACKET] |= SWITCH_2_ON;  
		}
		else
		{
				 TXData[SWITCH_PACKET] &= SWITCH_2_OFF;
		}
		if(SWITCH_3==0)
		{
				 TXData[SWITCH_PACKET] |= SWITCH_3_ON;  
		}
		
		else
		{
				 TXData[SWITCH_PACKET] &= SWITCH_3_OFF;
		}
		
		if(SWITCH_4==0)//A
		{
				 TXData[SWITCH_PACKET] |= SWITCH_4_ON;  
		}
		else
		{
				 TXData[SWITCH_PACKET] &= SWITCH_4_OFF;
		}
		switch(KNOB_L_FLAG){
			case 0:TXData[SWITCH_PACKET] &= KNOB_L_NULL;break;
			case 1:TXData[SWITCH_PACKET] &= KNOB_L_NULL;TXData[SWITCH_PACKET] |= KNOB_L_UP;break;
			case 2:TXData[SWITCH_PACKET] &= KNOB_L_NULL;TXData[SWITCH_PACKET] |= KNOB_L_DOWN;break;
		}
		switch(KNOB_R_FLAG){
			case 0:TXData[SWITCH_PACKET] &= KNOB_R_NULL;break;
			case 1:TXData[SWITCH_PACKET] &= KNOB_R_NULL;TXData[SWITCH_PACKET] |= KNOB_R_UP;break;
			case 2:TXData[SWITCH_PACKET] &= KNOB_R_NULL;TXData[SWITCH_PACKET] |= KNOB_R_DOWN;break;
		}
}
void Flags_clear(){
		KNOB_L_FLAG=0;
		KNOB_R_FLAG=0;
}
void init_ADC_data()
{
	//标志位清零
	if(ADC1_Flag==0){  
		RXmid=ADC_Value[0];
		LYmid=ADC_Value[1];		
		LXmid=ADC_Value[2];
		RYmid=ADC_Value[3];
		ADC1_Flag=1;
	}
	else{
		RXmid=floor((RXmid+ADC_Value[0])/2);
		LYmid=floor((LYmid+ADC_Value[1])/2);
		LXmid=floor((LXmid+ADC_Value[2])/2);
		RYmid=floor((RYmid+ADC_Value[3])/2);
	}
}
void init_ADC_MaxMin(){
	RXtemp=ADC_Value[0];
	LYtemp=ADC_Value[1];		
	LXtemp=ADC_Value[2];
	RYtemp=ADC_Value[3];
	if(LXtemp>LXmax) LXmax=LXtemp;
	if(LXtemp<LXmin) LXmin=LXtemp;
	if(LYtemp>LYmax) LYmax=LYtemp;
	if(LYtemp<LYmin) LYmin=LYtemp;
	if(RXtemp>RXmax) RXmax=RXtemp;
	if(RXtemp<RXmin) RXmin=RXtemp;
	if(RYtemp>RYmax) RYmax=RYtemp;
	if(RYtemp<RYmin) RYmin=RYtemp;
		
}
void Update_ADC(void)
{
	//标志位清零
	//存储历史
		RXhistory2=RXhistory1;
		RYhistory2=RYhistory1;
	  LXhistory2=LXhistory1;
		LYhistory2=LYhistory1;
		RXhistory1=RXtemp;
		RYhistory1=RYtemp;
		LXhistory1=LXtemp;
		LYhistory1=LYtemp;
	//读取ADC
																																																																							 
		RXtemp=ADC_Value[0];
		LYtemp=ADC_Value[1];		
		LXtemp=ADC_Value[2];
		RYtemp=ADC_Value[3];

	
	//限幅
	if(LXtemp>LXmax) LXtemp=LXmax;
	if(LXtemp<LXmin) LXtemp=LXmin;
	if(LYtemp>LYmax) LYtemp=LYmax;
	if(LYtemp<LYmin) LYtemp=LYmin;
	if(RXtemp>RXmax) RXtemp=RXmax;
	if(RXtemp<RXmin) RXtemp=RXmin;
	if(RYtemp>RYmax) RYtemp=RYmax;
	if(RYtemp<RYmin) RYtemp=RYmin;
	//MAP
	LX=(int32_t)map( ((LXtemp*3+LXhistory1*2+LXhistory2)/6), LXmin, LXmid,LXmax, -32767,0, 32767 );
	LY=(int32_t)map( ((LYtemp*3+LYhistory1*2+LYhistory2)/6), LYmin, LYmid,LYmax, -32767,0, 32767 );
	RX=(int32_t)map( ((RXtemp*3+RXhistory1*2+RXhistory2)/6), RXmin, RXmid,RXmax, 32767, 0,-32767 );
	RY=(int32_t)map( ((RYtemp*3+RYhistory1*2+RYhistory2)/6), RYmin, RYmid,RYmax, -32767,0,32767 );
	
	//提取高八位和第八位
	// LX
	binary[0] = LX;  
	highByte[0] = (binary[0] >> 8) & 0xFF;  
	lowByte[0] = binary[0] & 0xFF;  
	// LY
	binary[1] = LY;  
	highByte[1] = (binary[1] >> 8) & 0xFF;  
	lowByte[1] = binary[1] & 0xFF;  
	// RX
	binary[2] = RX;  
	highByte[2] = (binary[2] >> 8) & 0xFF;  
	lowByte[2] = binary[2] & 0xFF;  
	// RY
	binary[3] = RY;  
	highByte[3] = (binary[3] >> 8) & 0xFF; 
	lowByte[3] = binary[3] & 0xFF; 
	
	//LX
	TXData[LX_LSB] =lowByte[0];
	TXData[LX_MSB] =highByte[0];
	//LY
	TXData[LY_LSB] =lowByte[1];
	TXData[LY_MSB] =highByte[1];
	//RX
	TXData[RX_LSB] =lowByte[2];
	TXData[RX_MSB] =highByte[2];
	//RY
	TXData[RY_LSB] =lowByte[3];
	TXData[RY_MSB] =highByte[3];

}
int32_t map(int32_t x, int32_t in_min, int32_t in_mid, int32_t in_max, int32_t out_min, int32_t out_mid, int32_t out_max) {
    if (x <= in_mid) {
        return (x - in_min) * (out_mid - out_min) / (in_mid - in_min) + out_min;
    } else {
        return (x - in_mid) * (out_max - out_mid) / (in_max - in_mid) + out_mid;
    }
}

