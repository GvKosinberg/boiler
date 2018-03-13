/*
	�������� �����: ��� ��
	���� ��������: 13.03.2018
	�����: ������� �.�. (�����)
*/ 

// ������� ����������������
#define F_CPU 14745600UL

// ��������� ���-�����
#define COM_RX_BUFFER_SIZE 32
#define COM_TX_BUFFER_SIZE 32
#define COM1_PROTOCOL DCON

// ��������� ����
#define MAX_ELEMENTS_MENU 38
#define MAX_SUB_MENUS 17
#define MAX_HISTORY_ELEMENTS 16
#define MAX_HISTORY_NAMES 16

// ����������� ���������� �����/������
#include <avr/io.h>
// ����������� ���������� ���������� ��������
#include <stdio.h>
// ����������� ���������� ��� �������� ������ �� FLASH ������
#include <avr/pgmspace.h>																											
// ����������� ���������� ��� �������� ������ � EEPROM ������
#include <avr/eeprom.h>																												
// ����������� ���������� ��� �������������� ��������
#include <math.h>																													
// ����������� ���������� ��� ����������� � �������
#include <stdlib.h>


// ���������� ���� ����� MC

// #include "MC12D4R4O.h"
// #include "MC12D6R.h"
#include "MC8U6R.h"

// ���������������� ����������

// ���������� ��� ������ � ��������
#include "LED.h"
// ���������� ��� �������� ����
#include "Menu.h"
// ���������� ��� ������ � ��������
#include "Key.h"
// ���������� ��� ������ � ���-�������
#include "COM.h"
// ���������� ��� ������ � ������ ��������� �������
#include "RTC.h"
// �������� � ���������� ����������
#include "params.h"

// �������� inline'�
// ������, ������ � ����������� ������
#include "memory_ops.h"
// ��������� � ����������� � ����
#include "menu_boiler.h"
// ������ � ������ ��������� �������
#include "rtc_boiler.h"


//============================================================//

//==============������� ������������� �������=================//
void Timer0_Init(void)
{
	// ��������� �������� ������� 0 � 1024
	TCCR0 |= (1<<CS00)|(1<<CS01)|(1<<CS02);
	TCNT0 = 111;
	// ��������� ���������� �� ������������ ������� ��������
	TIMSK |= (1<<TOIE0);
	// ��������� ��� ������ ���������� ����������
	sei();
}

int main(void)
{
    while (1) 
    {
    }
}

