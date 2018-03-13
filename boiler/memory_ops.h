/*
 * memory_ops.h
 *
 * Created: 13.03.2018
 * Author: Antipin
 * �������� � ������� (EEPROM<=>RAM)
 * ������ � ������
 * ����������� ������ (INT<=>CHAR)
 */ 

#ifndef __memory_ops
#define __memory_ops


//������� ������ ������ (16) �� EEPROM � ������ � ��������� ����������//
//src - ��������� �� �������� ������, sz - �����������, tgt - ��������� �� �������� ����������
void inline mems_to_char_16(uint16_t* src, uint8_t sz, uint8_t* tgt)
{
	//���������� ��� �������� ��������� �������� �������� ���������� ��� �������
	uint16_t tmp_src;
	//������ ���������� �� EEPROM (����� ������������� ����������)
	tmp_src = eeprom_read_word(src);
	
	for (int i = 0; i<sz; i++, tgt++)
	{
		//������������ ��������� 10 �������� ������� �����
		*tgt = (tmp_src/pow(10, sz-i-1)) + 0x30;
		//��������� �������� ������� �� ��������� ������� ������� �� ������� ��� ��������� ��������
		tmp_src -= (*tgt-0x30)*pow(10, sz-i-1);
	}
}

//������� ������ ������ (32) �� EEPROM � ������ � ��������� ����������//
//src - ��������� �� �������� ������, sz - �����������, tgt - ��������� �� �������� ����������
void inline mems_to_char_32(uint32_t* src, uint8_t sz, uint8_t* tgt)
{
	//���������� ��� �������� ��������� �������� �������� ���������� ��� �������
	uint32_t tmp_src;
	//������ ���������� ���������� �� EEPROM
	tmp_src = eeprom_read_dword(src);
	
	for (int i = 0; i<sz; i++, tgt++)
	{
		//������������ ��������� 10 �������� ������� �����
		*tgt = (tmp_src/pow(10, sz-i-1)) + 0x30;
		//��������� �������� ������� �� ��������� ������� ������� �� ������� ��� ��������� ��������
		tmp_src -= (*tgt-0x30)*pow(10, sz-i-1);
	}
	//���� ������� K_I (� ������)
	if (sz == 5)
	{
		//������ �����
		*(tgt-4) = '.';
	}
	//���� ������� K_P � K_D (� ������)
	else if (sz == 6)
	{
		*(tgt-7) = *(tgt-6);
		//����� ������ ������
		*(tgt-6) = *(tgt-5);
		*(tgt-5) = *(tgt-4);
		//������ �����
		*(tgt-4) = '.';
	}
}

//������� ������ �������� ���������� � ������������� ����������//
void convert_to_show()
{
	//====�����====//
	cur_time[0]=hour/10+0x30;
	cur_time[1]=hour%10+0x30;
	cur_time[2]=':';
	cur_time[3]=min/10+0x30;
	cur_time[4]=min%10+0x30;
	
	//====���� ������====//
	for (int i = 0; i<7; i++)
	{
		disp_DOW[i][0]=i+1;
	}
	disp_DOW[cur_DOW_RAM][0] = 0;
	
	//======��������� �������=====//
	
	per_dat_s[0] = per_dat_RAM/1000 + 0x30;
	per_dat_s[1] = per_dat_RAM%1000/100 + 0x30;
	per_dat_s[2] = per_dat_RAM%1000%100/10 + 0x30;
	per_dat_s[3] = per_dat_RAM%1000%100%10 + 0x30;
	
	mems_to_char_16(&per_shim, 4, per_shim_s);
	//mems_to_char_16(&per_dat, 4, per_dat_s);
	time_nach_s[2] = ':';
	mems_to_char_16(&time_nach[0], 2, &time_nach_s[0]);
	mems_to_char_16(&time_nach[1], 2, &time_nach_s[3]);
	time_kon_s[2] = ':';
	mems_to_char_16(&time_kon[0], 2, &time_kon_s[0]);
	mems_to_char_16(&time_kon[1], 2, &time_kon_s[3]);
	
	//====��������� �����������====//
	
	mems_to_char_16(&temp_den[0], 2, temp_den_s[0]);
	mems_to_char_16(&temp_den[1], 2, temp_den_s[1]);
	mems_to_char_16(&temp_den[2], 2, temp_den_s[2]);
	mems_to_char_16(&temp_noch[0], 2, temp_noch_s[0]);
	mems_to_char_16(&temp_noch[1], 2, temp_noch_s[1]);
	mems_to_char_16(&temp_noch[2], 2, temp_noch_s[2]);
	
	//====��������� �����������====//
	
	mems_to_char_32(&K_P[0], 6, K_P_s[0]);
	mems_to_char_32(&K_P[1], 6, K_P_s[1]);
	mems_to_char_32(&K_P[2], 6, K_P_s[2]);
	mems_to_char_32(&K_I[0], 5, K_I_s[0]);
	mems_to_char_32(&K_I[1], 5, K_I_s[1]);
	mems_to_char_32(&K_I[2], 5, K_I_s[2]);
	mems_to_char_32(&K_D[0], 6, K_D_s[0]);
	mems_to_char_32(&K_D[1], 6, K_D_s[1]);
	mems_to_char_32(&K_D[2], 6, K_D_s[2]);
}

//=====������� ����������� ���������� �������� � ��������=====//

//src - ��������� �� �������� ������, sz - �����������, tgt - ��������� �� �������� ����������
void inline char_to_dec_16(uint8_t* src, uint8_t sz, uint16_t* tgt)
{
	if (sz==4) *tgt = (uint16_t) (*src-0x30)*1000+(*(src+1)-0x30)*100+(*(src+2)-0x30)*10+(*(src+3)-0x30);
	if (sz==2) *tgt = (uint16_t) (*src-0x30)*10+(*(src+1)-0x30);
}

//src - ��������� �� �������� ������, sz - �����������, tgt - ��������� �� �������� ����������
void inline char_to_dec_32(uint8_t* src, uint8_t sz, uint32_t* tgt)
{
	//���������� ��� �������� ��������� �������� ���������� ��� ���������
	uint8_t* src_tmp = src;
	//������ ��������� ����� � �����
	uint8_t n = 0;
	//����� ����� � �����
	for (int i = 0; i<sz; i++, src_tmp++)
	{
		if (*src_tmp=='.') n = i;
	}
	
	//��� ������� ����� � ������� (Nmax-1)
	if (n==1) *tgt = (uint32_t) (*src-0x30)*1000+(*(src+2)-0x30)*100+(*(src+3)-0x30)*10+(*(src+4)-0x30);
	//��� ������� ����� � ������� (Nmax-2)
	if (n==2) *tgt = (uint32_t) (*src-0x30)*10000+(*(src+1)-0x30)*1000+(*(src+3)-0x30)*100+(*(src+4)-0x30)*10+(*(src+5)-0x30);
}

//=====������� ������ ������ �� EEPROM � �� ������ � RAM======//
void mems_to_RAM()
{
	time_nach_RAM[0] = (uint8_t)eeprom_read_word(&time_nach[0]);
	time_nach_RAM[1] = (uint8_t)eeprom_read_word(&time_nach[1]);
	time_kon_RAM[0] = (uint8_t)eeprom_read_word(&time_kon[0]);
	time_kon_RAM[1] = (uint8_t)eeprom_read_word(&time_kon[1]);
	per_dat_RAM = eeprom_read_word(&per_dat);
	per_shim_RAM = eeprom_read_word(&per_shim);
	for (int i = 0; i<7; i++)
	{
		hol_DOW_RAM[i] = eeprom_read_byte(&hol_DOW[i]);
	}
	for (int i = 0; i<3; i++)
	{
		temp_den_RAM[i] = eeprom_read_word(&temp_den[i]);
		temp_noch_RAM[i] = eeprom_read_word(&temp_noch[i]);
		K_P_RAM[i] = eeprom_read_dword(&K_P[i]);
		K_I_RAM[i] = eeprom_read_dword(&K_I[i]);
		K_D_RAM[i] = eeprom_read_dword(&K_D[i]);
	}
}

#endif
