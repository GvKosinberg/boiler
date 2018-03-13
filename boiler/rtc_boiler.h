/*
 * rtc_boiler.h
 *
 * Created: 13.03.2018
 * Author: Antipin
 * ������ � ������ ��������� �������
 */ 

#ifndef __rtc_boiler
#define __rtc_boiler

//=============������� �������� ��������� �������=============//
void check_time()
{
	//������ ��� "�������"
	if (hol_DOW_RAM[cur_DOW_RAM] == '0')
	{
		//������� ��� ��������� ����� ����� ����� � ����� �������� ���
		if (hour>time_nach_RAM[0] && hour<time_kon_RAM[0])
		{
			flag_N = 0;
			if (skv_s[4] == 'N')
			{
				skv_s[4] = 'D';
				flag_O = 1;
			}
		}
		//������� ��� �� ��������� ����� ����� ����� � ����� �������� ���
		else
		{
			flag_N = 1;
			if (skv_s[4] == 'D')
			{
				skv_s[4] = 'N';
				flag_O = 1;
			}
		}
		//������� ��� ����� ���� ������ �������� ���
		if (hour==time_nach_RAM[0])
		{
			//������� ������ ������ ������ ������ �������� ���
			if (min>=time_nach_RAM[1])
			{
				flag_N = 0;
				if (skv_s[4] == 'N')
				{
					skv_s[4] = 'D';
					flag_O = 1;
				}
			}
			//������� ������ ������ ������ ������ �������� ���
			else
			{
				flag_N = 1;
				if (skv_s[4] == 'D')
				{
					skv_s[4] = 'N';
					flag_O = 1;
				}
			}
		}
		//������� ��� ����� ���� ����� �������� ���
		if (hour == time_kon_RAM[0])
		{
			//������� ������ ������ ������ ����� �������� ���
			if (min>=time_kon_RAM[1])
			{
				flag_N = 1;
				if (skv_s[4] == 'D')
				{
					skv_s[4] = 'N';
					flag_O = 1;
				}
			}
			//������� ������ ������ ������ ����� �������� ���
			else
			{
				flag_N = 0;
				if (skv_s[4] == 'N')
				{
					skv_s[4] = 'D';
					flag_O = 1;
				}
			}
		}
	}
	//������ �������� ��� "��������/��������"
	else if (hol_DOW_RAM[cur_DOW_RAM] == '1')
	{
		flag_N = 1;
		if (skv_s[4] == 'D')
		{
			skv_s[4] = 'N';
			flag_O = 1;
		}
	}
	
	if(hour==23 && min==59 && sec==59)
	{
		for (int i = 0; i<3; i++) I_prev[i] = 0;
	}
}

void get_time()
{
	if (RTC_Get_Time(&flush, &flush, &flush)==0)
	{
		RTC_Get_Time(&hour, &min, &sec);																					//����� ������� ������ �������� ������� � RTC
		RTC_Get_Date(&cur_DOW_RAM, &flush, &flush, &flush);
		clock_err = 0;
	}
	else clock_err++;
	if (clock_err>10)
	{
		RTC_Init();
		flag_R=1;																											//��������� ������ "������ ����������"
		skv_s[0] = 'R';
		flag_O = 1;
	}
	
}

#endif