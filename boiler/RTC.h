#ifndef _RTC_																					//������ �� ���������� ��������� �����
#define _RTC_

static uint8_t _I2C_Time_Out;																	//������� ����-����
static char _I2C_buf[6];																		//����� ��� ������/������ ������
static uint8_t _I2C_Error;																		//���� ������

//============= ������� �������� ��������� ����� � ����������� �������-���������� ==============
unsigned char bin2bcd(unsigned char n)
{
	return (n/10<<4)+(n % 10);
}

//============ ������� �������� ������������ �������-����������� ����� � �������� ==============
unsigned char bcd2bin(unsigned char n)
{
	return (n>>4)*10+(n & 0x0F);
}

//======================== ������� ��������� ������� ����� �� ���� I2C =========================
//������ ��������� ������� ����� ������� �������� �� I2C ����� ������������ ���������� (����� ������ ��������� � ���� ��� ������/������)
//������� ��������� � �������� ����������:
//Adr - ����� ������������ ���������� (������� ��� ������ ������ ��������� ��� ������/������ (0-������/1-������))

void _I2C_Start(uint8_t Adr)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWEA);												//����� ���� ���������� I2C, ��������� ������� "�����", ���������� ������ I2C
	
	_I2C_Time_Out=0;
	while(!(TWCR & (1<<TWINT)))																	//�������� ���������� ��������
	{
		if (++_I2C_Time_Out>10) {_I2C_Error=1; break;}											//����� ���� � ������� 1 �� ���� �� �����������
		_delay_us(100);
	}
	
	TWDR=Adr;																					//�������� ������ � ���� ������/������
	
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWEA);												//�������� ������
	_I2C_Time_Out=0;
	while(!(TWCR & (1<<TWINT)))																	//�������� ���������� ��������
	{
		if (++_I2C_Time_Out>10) {_I2C_Error=1; break;}											//����� ���� � ������� 1 �� ���� �� �����������
		_delay_us(100);
	}
}

//======================== ������� ��������� ������� ���� �� ���� I2C ==========================
void _I2C_Stop(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);														//��������� ������ (��������� ������� "����")
}

//========================== ������� ������ ����� ������ �� ���� I2C ===========================
//������� ��������� � �������� ����������:
//*buf - ����� ������������ ������
//Length - ���������� ������������ ����

void _I2C_Write(char *buf, uint8_t Length)
{
	uint8_t temp;																				//��������������� ����������
	
	for (temp=0; temp<Length; temp++)
	{
		TWDR=*buf;																				//������ ������ � �������
		buf++;
		TWCR=(1<<TWINT)|(1<<TWEN);																//������ �������� ������
		
		_I2C_Time_Out=0;
		while(!(TWCR & (1<<TWINT)))																//�������� ���������� ��������
		{
			if (++_I2C_Time_Out>10) {_I2C_Error=1; break;}										//����� ���� � ������� 1 �� ���� �� �����������
			_delay_us(100);
		}
	}
	_I2C_Stop();																				//��������� ������
	_delay_us(10);
}

//========================== ������� ������ ���� ������ � ���� I2C =============================
//������� ��������� � �������� ����������:
//*buf - ����� ��� ������
//Length - ���������� ����������� ����

void _I2C_Read(char *buf, uint8_t Length)
{
	uint8_t temp;																				//��������������� ����������
	
	for (temp=0; temp<Length; temp++)
	{
		if(temp==Length-1) TWCR=(1<<TWINT)|(1<<TWEN);											//������ ������
		else TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
		
		_I2C_Time_Out=0;
		while(!(TWCR & (1<<TWINT)))																//�������� ���������� ������
		{
			if (++_I2C_Time_Out>10) {_I2C_Error=1; break;}										//����� ���� � ������� 1 �� ���� �� �����������
			_delay_us(100);
		}
		*buf=TWDR;
		buf++;
		if(temp==Length-1) _I2C_Stop();															//��������� ������
	}
	_delay_us(10);
}

/*
//=========== ������� ������ ����� ������ �� ���������� ����� ��������� ������� ============
//������� ��������� � �������� ����������:
//LastByte - ������� ���������� ����� � �������
//������� ����������:
//�������� ������������ ����� ������

char _RTC_Read(char LastByte)
{
	if(LastByte) TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);											//������ ������
	else TWCR=(1<<TWINT)|(1<<TWEN);												
	uint8_t temp=0;
	while(!(TWCR & (1<<TWINT)))																	//�������� ������
	{
		if (++temp>10) {_I2C_Error=1; break;}													//����� ���� � ������� 1 �� ���� �� �����������
		_delay_us(100);
	}
	return TWDR;																				//������� ����������
}
*/

//================= ������� ������������� ���������� ����� ��������� ������� ===================
char RTC_Init(void)
{
	TWSR=0;																						//��������� ������������ �������� �����
	TWBR=77;																					//��������� �������� �������� �����
	TWAR=0x01;																					//����� ���������� ����� ��������� �������
	
	_I2C_Error=0;																				//�������� ������� ������
	_I2C_Start(0xD0);

	_I2C_buf[0]=0x07; _I2C_buf[1]=0x91;
	_I2C_Write(_I2C_buf,2);

	if (_I2C_Error) return 1;																	//���� ���� ������
	else return 0;
}

//============================== ������� ������ �������� ������� ===============================
char RTC_Get_Time(unsigned char* hour, unsigned char* min, unsigned char* sec)
{
	_I2C_Error=0;																				//�������� ������� ������
	_I2C_Start(0xD0);																			//���������������� ���������� �� ������ �������
	
	_I2C_buf[0]=0x00;
	_I2C_Write(_I2C_buf,1);
	
	_I2C_Start(0xD1);
	
	_I2C_Read(_I2C_buf,3);																		//������ ������, �����, �����
	*sec=bcd2bin(_I2C_buf[0]);																	//�������
	*min=bcd2bin(_I2C_buf[1]);																	//������
	*hour=bcd2bin(_I2C_buf[2]);																	//����

	if (_I2C_Error) return 1;																	//���� ���� ������
	else return 0;
}

//================================= ������� ��������� ������� ==================================
char RTC_Set_Time(unsigned char hour, unsigned char min, unsigned char sec)
{
	_I2C_Error=0;																				//�������� ������� ������
	_I2C_Start(0xD0);																			//���������������� ���������� �� ������ �������
	
	_I2C_buf[0]=0x00;
	_I2C_buf[1]=bin2bcd(sec);
	_I2C_buf[2]=bin2bcd(min);
	_I2C_buf[3]=bin2bcd(hour);
	_I2C_Write(_I2C_buf,4);
	
	if (_I2C_Error) return 1;																	//���� ���� ������
	else return 0;
}

//============================== ������� ������ ������� ���� ===============================
char RTC_Get_Date(unsigned char* day, unsigned char* date, unsigned char* month, unsigned char* year)
{
	_I2C_Error=0;																				//�������� ������� ������
	_I2C_Start(0xD0);																			//���������������� ���������� �� ������ ����
	
	_I2C_buf[0]=0x03;
	_I2C_Write(_I2C_buf,1);
	
	_I2C_Start(0xD1);
	
	_I2C_Read(_I2C_buf,4);																		//������ ��� ������, ����, ������, ����
	*day=bcd2bin(_I2C_buf[0])-1;																	//���� ������
	*date=bcd2bin(_I2C_buf[1]);																	//�����
	*month=bcd2bin(_I2C_buf[2]);																//�����
	*year=bcd2bin(_I2C_buf[3]);																	//���
	
	if (_I2C_Error) return 1;																	//���� ���� ������
	else return 0;
}

//================================ ������� ��������� ���� ==================================
char RTC_Set_Date(unsigned char day, unsigned char date, unsigned char month, unsigned char year)
{
	_I2C_Error=0;																				//�������� ������� ������
	_I2C_Start(0xD0);																			//���������������� ���������� �� ������ ����

	_I2C_buf[0]=0x03;
	_I2C_buf[1]=bin2bcd(day)+1;
	_I2C_buf[2]=bin2bcd(date);
	_I2C_buf[3]=bin2bcd(month);
	_I2C_buf[4]=bin2bcd(year);
	_I2C_Write(_I2C_buf,5);	
	
	if (_I2C_Error) return 1;																	//���� ���� ������
	else return 0;
}

#endif