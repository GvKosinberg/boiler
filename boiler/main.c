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
// NOTE: commented _Frame_pause (CAUSE: Warns on compile)
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
// ������ ������ ����������
#include "pid_boiler.h"
// ������ � ���������
#include "snc_boiler.h"
// ������ � ��������� ��������
#include "buttons_boiler.h"
// ������ � ��������
#include "led_boiler.h"
// ��������� ����������
#include "interrupts_boiler.h"

//============================================================//

int main(void)
{
	_delay_ms(1000);
	
	//������������� ������
	LED_Init();
	//������������� RTC
	RTC_Init();
	//������������� ���
	COM_Init(COM_PORT1, 9600);

	//������������ ������ �� ����� (�������)
	DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB6) | (1 << PD7);
	//����������� ����� �� ����� (�����)
	DDRD |= (1 << PD4);
		
	//����� ������� �������� ��������� ����
	create_menu();
	//����� ������� ������� ��������
	start_sencors();
	//����� ������� ������ ������ �� EEPROM � RAM
	mems_to_RAM();
	//������������� �������
	Timer0_Init();
	//�������������� �������� ������� ��� ������� ������ ��������
	time_10_dat=per_dat_RAM*100-5;
	//������� ������ ��������
	read_sencors();
	//����������� ������� ������ �� EEPROM � ���������� ��� �����������
	convert_to_show();

    while (1) 
    {
		// ����������� ��������� ������
		main_screen();
		// ������ ������ � RTC
		get_time();
		// �������� �������
		check_time();
		// ���������� ������� �� ������
		check_buttons();
    }
}

