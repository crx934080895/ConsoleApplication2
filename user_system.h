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

//用结构体数组储存用户信息
//user_list[100]已在"read_data_from_library.h"定义

//以下为函数声明

//==================================================================
//函数名：query_user_by_info
//功能：查询某个字段含某个信息的用户
//输入参数：info_value	信息的值
//				    field_name	字段名
//返回值：类型user_result*结构体指针
//				若未找到则返回NULL指针
//				找到则返回结构体的指针（搜索结果可能不止一条）
//==================================================================
user_result* query_user_by_info(char* info_value, char* field_name);

//==================================================================
//函数名：sign_in
//功能：普通用户登录校验函数
//输入参数：user_name	用户名
//					user_passport	密码
//返回值：类型int
//				验证正确返回0
//				密码错误返回1
//				用户名不存在返回2
//==================================================================
int sign_in(char* user_name, char* user_passport);

//==================================================================
//函数名：administrator_verify
//功能：管理员登录校验函数
//输入参数：user_name	用户名
//					user_passport	密码
//返回值：类型int
//				验证正确返回0
//				密码错误返回1
//				用户名不存在返回2
//				非管理员权限返回3
//==================================================================
int administrator_verify(char* user_name, char* user_passport);

//==================================================================
//函数名：query_info_by_uesr
//功能：查询某个用户的信息，可输入字段名返回指定字段，若无指定字段则全部返回全部信息
//输入参数：int  1或2（1表示只有用户名，2表示用户名和字段名都有）   (必填参数)
//                 char* user_name(必填参数)	用户名
//					char* field_name（选填参数）  字段名
//					此函数需要不定参数
//返回值：类型char*
//			若用户指定字段,则返回对应字段的字符串
//          若用户未指定字段，返回如下格式"name:XX \t age:XX······"的字符串;
//==================================================================
char* query_info_by_uesr(int num, ...);

// 以上为函数声明，以下为函数实现

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
		if (strcmp(user_list[i].name, user_name) == 0)  //用户名是否存在
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
		if (strcmp(user_list[i].name, user_name) == 0)  //用户名是否存在
		{
			flag = 1;
			mark = i;
			break;
		}
	}
	if (mark==-1)
	{
		//未找到用户
		return 2;
	}
	if (strcmp(user_list[mark].passport, user_passport) == 0)   //密码是否正确
	{
		if (user_list[mark].power == 1)      //是否为管理员权限
			return 0;
		else
			return 3;
	}
	//密码错误
	else
	{
		return 1;
	}
}

char* query_info_by_uesr(int num, ...)
{

	//申请参数列表变量,实际sargv是一个字符串
	va_list sargv;
	//把函数传进来的参数初始化到列表里面，num表示参数个数
	va_start(sargv, num);
	//把第一个参数保存到字符串变量user_name中
	char* user_name = va_arg(sargv, char*);
	//此变量表示是否指定了字段
	bool have_field = false;
	//假如有第二个参数，那么把它存储到field字符串常量中
	char* field = NULL;
	if (num == 2)
	{
		field = va_arg(sargv, char*);
		have_field = true;
	}
	va_end(sargv);

	//表示是否找到了名字对应的用户
	bool  flag = false;
	// 循环控制变量，同时也是查找结果的下标
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
		//用户不存在
		return NULL;
	}

	//把结构体内各个非字符串的字段值保存到字符串里面
	static char age[4];
	static char sex[2];
	static char po[2];
	itoa(user_list[i].age, age, 10);
	itoa(user_list[i].sex, sex, 10);
	itoa(user_list[i].power, po, 10);

	//返回指定字段的值
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
		//字段名未找到
		return NULL;
	}
	//如果未指定字段，返回整个用户的信息
	else
	{
		static char k[100];
		sprintf_s(k, 100, "  %-13s%-13s%-13s%-23s%-13s%-13s\n", user_list[i].name, age, sex, user_list[i].id_number, user_list[i].passport, po);
		return k;
	}
}