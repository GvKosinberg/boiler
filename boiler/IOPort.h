#ifndef _IOPORT_																			//������ �� ���������� ��������� �����
#define _IOPORT_

#include <avr/iom128.h>																		//����������� ���������� �����/������
#include <util/delay.h>																		//����������� ���������� ��������� ��������

#ifndef F_CPU
# warning "F_CPU not defined. Frequency by default 14,7456 MHz"
#define F_CPU 14745600UL																	//����������� ��������� �������� ������� ���������������� (���������� ��� ���������� ������ ������� ��������)
#endif

#define LOW		0 																			//������ ��������� �����
#define HI		1 																			//������� ��������� �����
#define SW		2 																			//����������� ��������� �����

#include "LED.h"																			//���������� ������ � LED ��������

//==================== ������� ������������� ���������� ������/������� =====================
void IO_Init(void)
{
	DDRC&=0x80;																				//��������� ����� ���������� ������ Din0-Din6
#if _DIN-7																					//��� ������� ������� ������ 7 ���������� ������	
	DDRC&=0x80;																				//��������� ����� ����������� ����� Din7
#if _DIN-8																					//��� ������� ������� ������ 7 ���������� ������		
	DDRA&=0x0F;																				//��������� ����� ���������� ������ Din8-Din11	
#endif	
#endif	

	DDRB|=0x30;																				//��������� ����� ���������� ������� Dout0-Dout1
#if _DOUT-2																					//��� ������� ������� ������ 2 ���������� �s�����		
	DDRB|=0xC0;																				//��������� ����� ���������� ������� Dout2-Dout3
	DDRD|=0x30;																				//��������� ����� ���������� ������� Dout4-Dout5	
#if _DOUT-6																					//��� ������� ������� ������ 6 ���������� �s�����		
	DDRD|=0xC0;																				//��������� ����� ���������� ������� Dout6-Dout7
#endif
#endif
}

//====================== ������� ������ ��������� ���������� ������ ========================
uint8_t Input_Read(uint8_t Line)
{
	uint8_t temp=0;																			//��������������� ����������
	
	switch (Line)																			//����������� ������ �����
	{
	case 0: temp=((PINC & (1<<PC0))>>PC0) ^ 0x01; break;
	case 1: temp=((PINC & (1<<PC1))>>PC1) ^ 0x01; break;
	case 2: temp=((PINC & (1<<PC2))>>PC2) ^ 0x01; break;
	case 3: temp=((PINC & (1<<PC3))>>PC3) ^ 0x01; break;
	case 4: temp=((PINC & (1<<PC4))>>PC4) ^ 0x01; break;
	case 5: temp=((PINC & (1<<PC5))>>PC5) ^ 0x01; break;
	case 6: temp=((PINC & (1<<PC6))>>PC6) ^ 0x01; break;

#if _DIN-7																					//��� ������� ������� ������ 7 ���������� ������
	case 7: temp=((PINC & (1<<PC7))>>PC7) ^ 0x01; break;
#if _DIN-8																					//��� ������� ������� ������ 8 ���������� ������
	case 8: temp=((PINA & (1<<PA4))>>PA4) ^ 0x01; break;
	case 9: temp=((PINA & (1<<PA5))>>PA5) ^ 0x01; break;
	case 10: temp=((PINA & (1<<PA6))>>PA6) ^ 0x01; break;
	case 11: temp=((PINA & (1<<PA7))>>PA7) ^ 0x01; break;
#endif
#endif	
	}
	return temp;																			//������� ����������
}

//==================== ������� ������ ��������� ���� ���������� ������ =====================
int Input_Read_All(void)
{
#if !(_DIN-7)																				//��� ������� ������� 7 ���������� ������	
	return ~PINC & 0x007F;
#elif !(_DIN-8)																				//��� ������� ������� 8 ���������� ������
	return ~PINC & 0x00FF;
#else																						//��� ������� ������� ������ 8 ���������� ������
	return ((~PINA<<4) & 0x0F00)+(~PINC & 0x00FF);											
#endif
}

//==== ������� ������ ���������� � ������� ��������� ���� ��������� ������ �� ��������� =====
int Input_Led(void)
{

	uint8_t temp;																			//��������������� ����������
	int data;

	data=Input_Read_All();																	//������ ��������� ������

	#ifdef TIMER2
	LED_Cycle_Shift(0);																		//��������� ����������� ��������� ���������
	#endif
	LED_SetPos(0,0);																		//������� �� ������ ������
	
#if !(_DIN-7)																				//��� ������� ������� 7 ���������� ������	
	LED_Write_String("0123456         ");													//����� �������� � ���������� ������
#elif !(_DIN-8)																				//��� ������� ������� 8 ���������� ������
	LED_Write_String("01234567        ");													//����� �������� � ���������� ������
#else																						//��� ������� ������� ������ 8 ���������� ������
	LED_Write_String("0123456789AB    ");													//����� �������� � ���������� ������
#endif
	
	LED_SetPos(1,0);																		//������� �� ������ ������
	for (temp=0; temp<16; temp++)															//����� ��������� ������
	{
		if (data & (1<<temp)) _LED_Write_Byte(0xFF);										//���� ���������� "1", �������� ����������� �������������
		else _LED_Write_Byte(0x20);															//�����, ������ �������
	}
	
	return data;																			//������� ����������
}

//==================== ������� ��������� ��������� ���������� ������� ======================
void Output_Write(uint8_t Line, uint8_t Status)
{
	switch(Status)																			//����������� ������� ��������� ��������� ������
	{
	case 0:																					//���� ����� ����������� � ������ ���������
		switch(Line)																		//����������� ������ ����������� ������
		{
		case 0:	PORTB&=~(1<<PB4); break;
		case 1:	PORTB&=~(1<<PB5); break;
#if _DOUT-2																					//��� ������� ������� ������ 2 ���������� �s�����				
		case 2:	PORTB&=~(1<<PB6); break;
		case 3:	PORTB&=~(1<<PB7); break;
		case 4:	PORTD&=~(1<<PD4); break;
		case 5:	PORTD&=~(1<<PD5); break;
#if _DOUT-6																					//��� ������� ������� ������ 2 ���������� �s�����				
		case 6:	PORTD&=~(1<<PD6); break;
		case 7:	PORTD&=~(1<<PD7); break;		
#endif
#endif		
		}
		break;	
	case 1:																					//���� ����� ����������� � ������� ���������
		switch(Line)																		//����������� ������ ����������� ������
		{
		case 0:	PORTB|=(1<<PB4); break;
		case 1:	PORTB|=(1<<PB5); break;
#if _DOUT-2																					//��� ������� ������� ������ 2 ���������� �s�����						
		case 2:	PORTB|=(1<<PB6); break;
		case 3:	PORTB|=(1<<PB7); break;
		case 4:	PORTD|=(1<<PD4); break;
		case 5:	PORTD|=(1<<PD5); break;
#if _DOUT-6																					//��� ������� ������� ������ 2 ���������� �s�����				
		case 6:	PORTD|=(1<<PD6); break;
		case 7:	PORTD|=(1<<PD7); break;
#endif
#endif
		}
		break;		
	case 2:																					//���� ����� ������ ���� ��������� �� ���������������
		switch(Line)																		//����������� ������ ����������� ������
		{
		case 0:	PORTB^=(1<<PB4); break;
		case 1:	PORTB^=(1<<PB5); break;
#if _DOUT-2																					//��� ������� ������� ������ 2 ���������� �s�����				
		case 2:	PORTB^=(1<<PB6); break;
		case 3:	PORTB^=(1<<PB7); break;
		case 4:	PORTD^=(1<<PD4); break;
		case 5:	PORTD^=(1<<PD5); break;
#if _DOUT-6																					//��� ������� ������� ������ 2 ���������� �s�����				
		case 6:	PORTD^=(1<<PD6); break;
		case 7:	PORTD^=(1<<PD7); break;
#endif
#endif
		}
		break;		
	}
}

//================== ������� ��������� ��������� ���� ���������� ������� ===================
void Output_Write_All(uint8_t data)
{
	PORTB&=(data<<4) | 0xCF; PORTB|=(data<<4) & 0x30;
#if _DOUT-2																					//��� ������� ������� ������ 2 ���������� �s�����				
	PORTB&=(data<<4) | 0x3F; PORTB|=(data<<4) & 0xC0;
	PORTD&=data | 0xCF; PORTD|=data & 0x30;
#if _DOUT-6																					//��� ������� ������� ������ 2 ���������� �s�����				
	PORTD&=data | 0x3F; PORTD|=data & 0xC0;
#endif
#endif
}

//====================== ������� ������ ��������� ���������� ������� =======================
uint8_t Output_Read(uint8_t Line)
{
	uint8_t temp=0;																			//��������������� ����������
	
	switch (Line)																			//����������� ������ �����
	{
		case 0: temp=((PORTB & (1<<PB4))>>PB4); break;
		case 1: temp=((PORTB & (1<<PB5))>>PB5); break;
#if _DOUT-2																					//��� ������� ������� ������ 2 ���������� �s�����				
		case 2: temp=((PORTB & (1<<PB6))>>PB6); break;
		case 3: temp=((PORTB & (1<<PB7))>>PB7); break;
		case 4: temp=((PORTD & (1<<PD4))>>PD4); break;
		case 5: temp=((PORTD & (1<<PD5))>>PD5); break;
#if _DOUT-6																					//��� ������� ������� ������ 2 ���������� �s�����				
		case 6: temp=((PORTD & (1<<PD6))>>PD6); break;
		case 7: temp=((PORTD & (1<<PD7))>>PD7); break;
#endif
#endif
	}
	return temp;																			//������� ����������
}

//==================== ������� ������ ��������� ���� ���������� ������� ====================
uint8_t Output_Read_All(void)
{
	char temp;
	temp=(PORTB>>4) & 0x03;
#if _DOUT-2																					//��� ������� ������� ������ 2 ���������� �s�����				
	temp|=(PORTB>>4) & 0x0C;
	temp|=(PORTD & 0x30);
#if _DOUT-6																					//��� ������� ������� ������ 2 ���������� �s�����					
	temp|=(PORTD & 0xC0);
#endif
#endif
	return temp;
}

#endif