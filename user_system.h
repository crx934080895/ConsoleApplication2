#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdarg.h>
#include<stdbool.h>
#include "ticket_system.h"
#include "read_data_from_library.h"

typedef struct user_result
{
	int result_num;
	user* result[100];
}user_result;

//�ýṹ�����鴢���û���Ϣ
//user_list[100]����"read_data_from_library.h"����

//����Ϊ��������

//==================================================================
//��������query_user_by_info
//���ܣ���ѯĳ���ֶκ�ĳ����Ϣ���û�
//���������info_value	��Ϣ��ֵ
//				    field_name	�ֶ���
//����ֵ������user_result*�ṹ��ָ��
//				��δ�ҵ��򷵻�NULLָ��
//				�ҵ��򷵻ؽṹ���ָ�루����������ܲ�ֹһ����
//==================================================================
user_result* query_user_by_info(char* info_value, char* field_name);

//==================================================================
//��������sign_in
//���ܣ���ͨ�û���¼У�麯��
//���������user_name	�û���
//					user_passport	����
//����ֵ������int
//				��֤��ȷ����0
//				������󷵻�1
//				�û��������ڷ���2
//==================================================================
int sign_in(char* user_name, char* user_passport);

//==================================================================
//��������administrator_verify
//���ܣ�����Ա��¼У�麯��
//���������user_name	�û���
//					user_passport	����
//����ֵ������int
//				��֤��ȷ����0
//				������󷵻�1
//				�û��������ڷ���2
//				�ǹ���ԱȨ�޷���3
//==================================================================
int administrator_verify(char* user_name, char* user_passport);

//==================================================================
//��������query_info_by_uesr
//���ܣ���ѯĳ���û�����Ϣ���������ֶ�������ָ���ֶΣ�����ָ���ֶ���ȫ������ȫ����Ϣ
//���������int  1��2��1��ʾֻ���û�����2��ʾ�û������ֶ������У�   (�������)
//                 char* user_name(�������)	�û���
//					char* field_name��ѡ�������  �ֶ���
//					�˺�����Ҫ��������
//����ֵ������char*
//			���û�ָ���ֶ�,�򷵻ض�Ӧ�ֶε��ַ���
//          ���û�δָ���ֶΣ��������¸�ʽ"name:XX \t age:XX������������"���ַ���;
//==================================================================
char* query_info_by_uesr(int num, ...);

// ����Ϊ��������������Ϊ����ʵ��

user_result* query_user_by_info(char* info_value,char* field_name)
{
	int field_flag = 0;
	static user_result result;
	result.result_num = 0;
	char age[4];
	char sex[2];
	char power[3];

	if (strcmp(field_name,"name")==0)
	{
		field_flag = 1;
	}
	else if(strcmp(field_name, "age") == 0)
	{
		field_flag = 2;
	}
	else if (strcmp(field_name, "sex") == 0)
	{
		field_flag = 3;
	}
	else if (strcmp(field_name, "id_number") == 0)
	{
		field_flag = 4;
	}
	else if (strcmp(field_name, "passport") == 0)
	{
		field_flag = 5;
	}
	else if (strcmp(field_name, "power") == 0)
	{
		field_flag = 6;
	}

	switch (field_flag)
	{
		case 0:
			return NULL;
			break;
		case 1:
			for (int i = 0; i < user_num; i++)
			{
				if (strcmp(user_list[i].name, info_value) == 0)
				{
					result.result[result.result_num] = &user_list[i];
					result.result_num++;
				}
			}
			break;
			
		case 2:
			for (int i = 0; i < user_num; i++)
			{
				itoa(user_list[i].age, age, 10);
				if (strcmp(age, info_value) == 0)
				{
					result.result[result.result_num] = &user_list[i];
					result.result_num++;
				}
			}
			break;
		case 3:
			for (int i = 0; i < user_num; i++)
			{
				itoa(user_list[i].sex, sex, 10);
				if (strcmp(sex, info_value) == 0)
				{
					result.result[result.result_num] = &user_list[i];
					result.result_num++;
				}
			}
			break;
		case 4:
			for (int i = 0; i < user_num; i++)
			{
				if (strcmp(user_list[i].id_number, info_value) == 0)
				{
					result.result[result.result_num] = &user_list[i];
					result.result_num++;
				}
			}
			break;
		case 5:
			for (int i = 0; i < user_num; i++)
			{
				if (strcmp(user_list[i].passport, info_value) == 0)
				{
					result.result[result.result_num] = &user_list[i];
					result.result_num++;
				}
			}
			break;
		case 6:
			for (int i = 0; i < user_num; i++)
			{
				itoa(user_list[i].power, power, 10);
				if (strcmp(power, info_value) == 0)
				{
					result.result[result.result_num] = &user_list[i];
					result.result_num++;
				}
			}
			break;
	}
	return &result;
}

int sign_in(char* user_name, char* user_passport)
{
	int flag = 0,mark = -1;
	for (int i = 0; i < user_num; i++)
	{
		if (strcmp(user_list[i].name, user_name) == 0)  //�û����Ƿ����
		{
			flag = 1;
			mark = i;
			break;
		}
	}
	if (mark==-1)
	{
		return 2;
	}
	if (strcmp(user_list[mark].passport, user_passport) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int administrator_verify(char* user_name, char* user_passport)
{
	int flag = 0,mark=-1;
	for (int i = 0; i < user_num; i++)
	{
		if (strcmp(user_list[i].name, user_name) == 0)  //�û����Ƿ����
		{
			flag = 1;
			mark = i;
			break;
		}
	}
	if (mark==-1)
	{
		//δ�ҵ��û�
		return 2;
	}
	if (strcmp(user_list[mark].passport, user_passport) == 0)   //�����Ƿ���ȷ
	{
		if (user_list[mark].power == 1)      //�Ƿ�Ϊ����ԱȨ��
			return 0;
		else
			return 3;
	}
	//�������
	else
	{
		return 1;
	}
}

char* query_info_by_uesr(int num, ...)
{

	//��������б����,ʵ��sargv��һ���ַ���
	va_list sargv;
	//�Ѻ����������Ĳ�����ʼ�����б����棬num��ʾ��������
	va_start(sargv, num);
	//�ѵ�һ���������浽�ַ�������user_name��
	char* user_name = va_arg(sargv, char*);
	//�˱�����ʾ�Ƿ�ָ�����ֶ�
	bool have_field = false;
	//�����еڶ�����������ô�����洢��field�ַ���������
	char* field = NULL;
	if (num == 2)
	{
		field = va_arg(sargv, char*);
		have_field = true;
	}
	va_end(sargv);

	//��ʾ�Ƿ��ҵ������ֶ�Ӧ���û�
	bool  flag = false;
	// ѭ�����Ʊ�����ͬʱҲ�ǲ��ҽ�����±�
	int i = 0;
	for (i = 0; i < user_num; i++)
	{
		if (strcmp(user_name, user_list[i].name) == 0)
		{
			flag = true;
			break;
		}
	}
	if (!flag)
	{
		//�û�������
		return NULL;
	}

	//�ѽṹ���ڸ������ַ������ֶ�ֵ���浽�ַ�������
	static char age[4];
	static char sex[2];
	static char po[2];
	itoa(user_list[i].age, age, 10);
	itoa(user_list[i].sex, sex, 10);
	itoa(user_list[i].power, po, 10);

	//����ָ���ֶε�ֵ
	if (have_field)
	{
		if (strcmp(field, "age")==0)
		{
			return age;
		}
		if (strcmp(field, "sex")==0)
		{
			return sex;
		}
		if (strcmp(field, "id_number")==0)
		{
			return user_list[i].id_number;
		}
		if (strcmp(field, "passport")==0)
		{
			return user_list[i].passport;
		}
		if (strcmp(field, "power")==0)
		{
			return po;
		}
		//�ֶ���δ�ҵ�
		return NULL;
	}
	//���δָ���ֶΣ����������û�����Ϣ
	else
	{
		static char k[100];
		sprintf_s(k, 100, "  %-13s%-13s%-13s%-23s%-13s%-13s\n", user_list[i].name, age, sex, user_list[i].id_number, user_list[i].passport, po);
		return k;
	}
}