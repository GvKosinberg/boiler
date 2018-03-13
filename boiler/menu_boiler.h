/*
 * menu_boiler.h
 *
 * Created: 13.03.2018
 * Author: Antipin
 * �������� ���� � ���������� ������ ��� ���������
 */ 

#ifndef __menu_boiler
#define __menu_boiler

//============������� �������� ��������� ����=================//
void inline create_menu()
{
	
	Add_New_Menu(0, 6);
	
	Add_New_Element(0, EMPTY_ELEMENT, 7, PSTR("������1"), NONE, NONE);
	Add_New_Element(1, EMPTY_ELEMENT, 10, PSTR("������2"), NONE, NONE);
	Add_New_Element(2, EMPTY_ELEMENT, 13, PSTR("������3"), NONE, NONE);
	Add_New_Element(3, EMPTY_ELEMENT, 1, PSTR("�����. ��������/n �������"), NONE, NONE);
	Add_New_Element(4, EMPTY_ELEMENT, 5, PSTR("������ ���"), NONE, NONE);
	Add_New_Element(5, EMPTY_ELEMENT, 6, PSTR("������ ������/n ��������"), NONE, NONE);
	
	//=================================�����===============================//
	
	Add_New_Menu(1, 3);
	
	Add_New_Element(6, EMPTY_ELEMENT, 2, PSTR("��������� �����./n �������"), NONE, NONE);
	Add_New_Element(7, EMPTY_ELEMENT, 3, PSTR("������ ����/����"), NONE, NONE);
	Add_New_Element(8, EMPTY_ELEMENT, 4, PSTR("������ ����/n ������"), NONE, NONE);
	
	Add_New_Menu (2, 2);
	
	Add_New_Element(9, PARAM_ELEMENT, NONE, PSTR("�����"), cur_time, 5);
	Add_New_Element(10, LIST_ELEMENT, NONE, PSTR("���� ������"), disp_DOW[0], 3);
	
	Add_New_Menu(3, 2);
	
	Add_New_Element(11, PARAM_ELEMENT, NONE, PSTR("������ ���. ���"), time_nach_s, 5);
	Add_New_Element(12, PARAM_ELEMENT, NONE, PSTR("����� ���. ���"), time_kon_s, 5);
	
	Add_New_Menu(4, 1);
	
	Add_New_Element(13, WORD_ELEMENT, NONE, PSTR("� � � � � � �"), hol_DOW_RAM, 7);
	
	Add_New_Menu (5, 1);
	
	Add_New_Element(14, PARAM_ELEMENT, NONE, PSTR("������ � ���"), per_shim_s, 4);
	
	Add_New_Menu(6, 1);
	
	Add_New_Element(15, PARAM_ELEMENT, NONE, PSTR("������ �  ���"), per_dat_s, 4);
	
	
	//====================1 ������=====================================//
	
	Add_New_Menu (7, 2);
	
	Add_New_Element(16, EMPTY_ELEMENT, 8, PSTR("�����. ��������/n �����������"), NONE, NONE);
	Add_New_Element(17, EMPTY_ELEMENT, 9, PSTR("�����. ��������/n ����������"), NONE, NONE);
	
	Add_New_Menu(8, 2);
	
	Add_New_Element(18, PARAM_ELEMENT, NONE, PSTR("����������� ����"), temp_den_s[0], 2);
	Add_New_Element(19, PARAM_ELEMENT, NONE, PSTR("����������� ����"), temp_noch_s[0], 2);
	
	Add_New_Menu(9, 3);
	
	Add_New_Element(20, PARAM_ELEMENT, NONE, PSTR("��"), K_P_s[0], 6);
	Add_New_Element(21, PARAM_ELEMENT, NONE, PSTR("��"), K_I_s[0], 5);
	Add_New_Element(22, PARAM_ELEMENT, NONE, PSTR("��"), K_D_s[0], 6);

	//====================2 ������=====================================//
	
	Add_New_Menu (10, 2);
	
	Add_New_Element(23, EMPTY_ELEMENT, 11, PSTR("�����. ��������/n �����������"), NONE, NONE);
	Add_New_Element(24, EMPTY_ELEMENT, 12, PSTR("�����. ��������/n ����������"), NONE, NONE);
	
	Add_New_Menu(11, 2);
	
	Add_New_Element(25, PARAM_ELEMENT, NONE, PSTR("����������� ����"), temp_den_s[1], 2);
	Add_New_Element(26, PARAM_ELEMENT, NONE, PSTR("����������� ����"), temp_noch_s[1], 2);
	
	Add_New_Menu(12, 3);
	
	Add_New_Element(27, PARAM_ELEMENT, NONE, PSTR("��"), K_P_s[1], 6);
	Add_New_Element(28, PARAM_ELEMENT, NONE, PSTR("��"), K_I_s[1], 5);
	Add_New_Element(29, PARAM_ELEMENT, NONE, PSTR("��"), K_D_s[1], 6);
	
	//====================3 ������=====================================//
	
	Add_New_Menu (13, 2);
	
	Add_New_Element(30, EMPTY_ELEMENT, 14, PSTR("�����. ��������/n �����������"), NONE, NONE);
	Add_New_Element(31, EMPTY_ELEMENT, 15, PSTR("�����. ��������/n ����������"), NONE, NONE);
	
	Add_New_Menu(14, 2);
	
	Add_New_Element(32, PARAM_ELEMENT, NONE, PSTR("����������� ����"), temp_den_s[2], 2);
	Add_New_Element(33, PARAM_ELEMENT, NONE, PSTR("����������� ����"), temp_noch_s[2], 2);
	
	Add_New_Menu(15, 3);
	
	Add_New_Element(34, PARAM_ELEMENT, NONE, PSTR("��"), K_P_s[2], 6);
	Add_New_Element(35, PARAM_ELEMENT, NONE, PSTR("��"), K_I_s[2], 5);
	Add_New_Element(36, PARAM_ELEMENT, NONE, PSTR("��"), K_D_s[2], 6);
	
	//=================================================================//

}

//===������� ���������� ���������� ��� �� ��������� �� ����===//
void inline settings_changed(uint8_t el)																									//el - ����� ��������, � ������� ���� �������� ���������
{
	uint16_t val_16;																												//���������� ��� �������� ������������� �������� � ���������� ������� � EEPROM
	uint32_t val_32;
	//cli();
	switch (el)
	{
		case 9 :																													//������������� �������� �������
		hour = (cur_time[0]-0x30)*10 + (cur_time[1]-0x30);
		min = (cur_time[3]-0x30)*10 + (cur_time[4]-0x30);
		RTC_Set_Time(hour, min, sec);
		break;
		case 10 :																													//������������� �������� ��� ������
		for (int i = 0; i<7; i++)																									//����� �������� ������ � �������� "����"
		{
			if (disp_DOW[i][0] == 0)
			{
				cur_DOW_RAM = i;
				RTC_Set_Date(cur_DOW_RAM, flush, flush, flush);																		//������ ����������� ������ �������� ������ � EEPROM
			}
		}
		convert_to_show();
		break;
		case 11:																													//������������� ������� ������ �������� ���
		char_to_dec_16(&time_nach_s[0], 2, &val_16);																				//������������� �����
		eeprom_write_word(&time_nach[0], val_16);																					//������ ����� � EEPROM
		time_nach_RAM[0] = val_16;
		char_to_dec_16(&time_nach_s[3], 2, &val_16);																				//������������� �����
		time_nach_RAM[1] = val_16;
		eeprom_write_word(&time_nach[1], val_16);																					//������ ����� � EEPROM
		break;
		case 12:																													//������������� ������� ����� �������� ���
		char_to_dec_16(&time_kon_s[0], 2, &val_16);																					//������������� �����
		eeprom_write_word(&time_kon[0], val_16);																					//������ ����� � EEPROM
		time_kon_RAM[0] = val_16;
		char_to_dec_16(&time_kon_s[3], 2, &val_16);																					//������������� �����
		eeprom_write_word(&time_kon[1], val_16);																					//������ ����� � EEPROM
		time_kon_RAM[1] = val_16;
		break;
		case 13:																													//������������� �������� ��� ������ � ������
		for (int i = 0; i<7; i++)
		{
			eeprom_write_byte(&hol_DOW[i], hol_DOW_RAM[i]);
		}
		break;
		case 14:
		char_to_dec_16(per_shim_s, 4, &val_16);																						//������������� ������� ���
		if (val_16<1800)
		{
			LED_SetPos(1, 0);
			LED_Write_String_P(PSTR("ERROR"));
			break;
		}
		else
		{
			eeprom_write_word(&per_shim, val_16);																					//������ ������� ��� � EEPROM
			per_shim_RAM = val_16;
			time_10_shim = 0;
			break;
		}
		case 15:
		char_to_dec_16(per_dat_s, 4, &val_16);																						//������������� ������� ������ ��������
		eeprom_write_word(&per_dat, val_16);																						//������ ������� ������ �������� � EEPROM
		per_dat_RAM = val_16;
		time_10_dat = 0;
		break;
		
		//=========������ 1=============//
		case 18:
		char_to_dec_16(temp_den_s[0], 2, &val_16);																					//������������� ��������� ����������� ��� �������� ������ 1 �������
		eeprom_write_word(&temp_den[0], val_16);																					//������ ��������� ����������� ��� �������� ������ 1 ������� � EEPROM
		temp_den_RAM[0] = val_16;
		break;
		case 19:
		char_to_dec_16(temp_noch_s[0], 2, &val_16);																					//������������� ��������� ����������� ��� ������� ������ 1 �������
		eeprom_write_word(&temp_noch[0], val_16);																					//������ ��������� ����������� ��� ������� ������ 1 ������� � EEPROM
		temp_noch_RAM[0] = val_16;
		break;
		case 20:
		char_to_dec_32(K_P_s[0], 5, &val_32);																						//������������� ����������������� ������������ ���-���������� 1 �������
		eeprom_write_dword(&K_P[0], val_32);																						//������ ����������������� ������������ ���-���������� 1 ������� � EEPROM
		K_P_RAM[0] = val_32;
		break;
		case 21:
		char_to_dec_32(K_I_s[0], 5, &val_32);																						//������������� ������������� ������������ ���-���������� 1 �������
		eeprom_write_dword(&K_I[0], val_32);																						//������ ������������� ������������ ���-���������� 1 ������� � EEPROM
		K_I_RAM[0] = val_32;
		break;
		case 22:
		char_to_dec_32(K_D_s[0], 5, &val_32);																						//������������� ����������������� ������������ ���-���������� 1 �������
		eeprom_write_dword(&K_D[0], val_32);																						//������ ����������������� ������������ ���-���������� 1 ������� � EEPROM
		K_D_RAM[0] = val_32;
		break;
		//=========������ 2=============//
		case 25:
		char_to_dec_16(temp_den_s[1], 2, &val_16);																					//������������� ��������� ����������� ��� �������� ������ 2 �������
		eeprom_write_word(&temp_den[1], val_16);																					//������ ��������� ����������� ��� �������� ������ 2 ������� � EEPROM
		temp_den_RAM[1] = val_16;
		break;
		case 26:
		char_to_dec_16(temp_noch_s[1], 2, &val_16);																					//������������� ��������� ����������� ��� ������� ������ 2 �������
		eeprom_write_word(&temp_noch[1], val_16);																					//������ ��������� ����������� ��� ������� ������ 2 ������� � EEPROM
		temp_noch_RAM[1] = val_16;
		break;
		case 27:
		char_to_dec_32(K_P_s[1], 5, &val_32);																						//������������� ����������������� ������������ ���-���������� 2 �������
		eeprom_write_dword(&K_P[1], val_32);																						//������ ����������������� ������������ ���-���������� 2 ������� � EEPROM
		K_P_RAM[1] = val_32;
		break;
		case 28:
		char_to_dec_32(K_I_s[1], 5, &val_32);																						//������������� ������������� ������������ ���-���������� 2 �������
		eeprom_write_dword(&K_I[1], val_32);																						//������ ������������� ������������ ���-���������� 2 ������� � EEPROM
		K_I_RAM[1] = val_32;
		break;
		case 29:
		char_to_dec_32(K_D_s[1], 5, &val_32);																						//������������� ����������������� ������������ ���-���������� 2 �������
		eeprom_write_dword(&K_D[1], val_32);																						//������ ����������������� ������������ ���-���������� 2 ������� � EEPROM
		K_D_RAM[1] = val_32;
		break;
		//=========������ 3=============//
		case 32:
		char_to_dec_16(temp_den_s[2], 2, &val_16);																					//������������� ��������� ����������� ��� �������� ������ 3 �������
		eeprom_write_word(&temp_den[2], val_16);																					//������ ��������� ����������� ��� �������� ������ 3 ������� � EEPROM
		temp_den_RAM[2] = val_16;
		break;
		case 33:
		char_to_dec_16(temp_noch_s[2], 2, &val_16);																					//������������� ��������� ����������� ��� ������� ������ 3 �������
		eeprom_write_word(&temp_noch[2], val_16);																					//������ ��������� ����������� ��� ������� ������ 3 ������� � EEPROM
		temp_noch_RAM[2] = val_16;
		break;
		case 34:
		char_to_dec_32(K_P_s[2], 5, &val_32);																						//������������� ����������������� ������������ ���-���������� 3 �������
		eeprom_write_dword(&K_P[2], val_32);																						//������ ����������������� ������������ ���-���������� 3 ������� � EEPROM
		K_P_RAM[2] = val_32;
		break;
		case 35:
		char_to_dec_32(K_I_s[2], 5, &val_32);																						//������������� ������������� ������������ ���-���������� 3 �������
		eeprom_write_dword(&K_I[2], val_32);																						//������ ������������� ������������ ���-���������� 3 ������� � EEPROM
		K_I_RAM[2] = val_32;
		break;
		case 36:
		char_to_dec_32(K_D_s[2], 5, &val_32);																						//������������� ����������������� ������������ ���-���������� 3 �������
		eeprom_write_dword(&K_D[2], val_32);																						//������ ����������������� ������������ ���-���������� 3 ������� � EEPROM
		K_D_RAM[2] = val_32;
		break;
	}
	//mems_to_RAM();
	//sei();
}

#endif
