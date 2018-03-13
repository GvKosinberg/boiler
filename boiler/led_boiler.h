/*
 * led_boiler.h
 *
 * Created: 13.03.2018
 * Author: Antipin
 * ������ � ��������
*/

#ifndef __led_boiler
#define __led_boiler

//======������� ����������� ���������� �� ������� ������======//
void main_screen()
{
	//=============��������� ���������� ��������� ��������=================//
	
	//��������� �1 � �2
	if (time_10_slide>0 && time_10_slide<=200 && flag_S == 3)
	{
		//����� ��������������� ��������� ������ �� �����
		LED_SetPos(0,0);
		LED_Write_String_P(PSTR("T1="));
		LED_SetPos(1,0);
		LED_Write_String_P(PSTR("T2="));
		//����� ��������������� ��������� ������ �� �����
		LED_SetPos(0,3);
		LED_Write_String(snc1);
		LED_SetPos(1,3);
		LED_Write_String(snc2);
		flag_S = 1;
	}
	
	//��������� �2 � �3
	else if (time_10_slide>200 && time_10_slide<=400 && flag_S == 1)
	{
		//����� ��������������� ��������� ������ �� �����
		LED_SetPos(0,0);
		LED_Write_String_P(PSTR("T2="));
		LED_SetPos(1,0);
		LED_Write_String_P(PSTR("T3="));
		//����� ��������������� ��������� ������ �� �����
		LED_SetPos(0,3);
		LED_Write_String(snc2);
		LED_SetPos(1,3);
		LED_Write_String(snc3);
		flag_S = 2;
	}
	
	//��������� �3 � �1
	else if (time_10_slide>400 && flag_S == 2)
	{
		//����� ��������������� ��������� ������ �� �����
		LED_SetPos(0,0);
		LED_Write_String_P(PSTR("T3="));
		LED_SetPos(1,0);
		LED_Write_String_P(PSTR("T1="));
		//����� ��������������� ��������� ������ �� �����
		LED_SetPos(0,3);
		LED_Write_String(snc3);
		LED_SetPos(1,3);
		LED_Write_String(snc1);
		flag_S = 3;
	}
	
	//�������� ����� ������� ������ �� ������ �� ��������� �������� ������ ��-�� �������������
	if (flag_T==0)
	{
		LED_SetPos(0,9);
		LED_Write_String_P(PSTR("ST"));
		//���� ������� ���������������� ������ �� ������
		flag_T=1;
	}
	if (flag_O==1)
	{
		LED_SetPos(0,11);
		//����� ��������� ������� 2 �� �����
		LED_Write_String(vis);
		LED_SetPos(1, 9);
		LED_Write_String(skv_s);
		flag_O = 0;
	}
}

#endif