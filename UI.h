#include <stdio.h>
#include "user_system.h"
#include "ticket_system.h"
#include<windows.h>

/*以下为函数声明*/

// 用户登录界面函数
void sign_in_screen();

// 用户注册界面函数
void regist_screen();

//	管理员登录界面函数
void administrator_sign_in_screen();

//	管理员后台界面函数
// 管理员后台管理可以增删改查用户或用户数据
void administrator_screen();

//	购票界面函数
// 可以查询航班，购买票，按规则筛选票，推荐路线等
void ticket_screen();

//查最优惠路线
void plane_price_sort()
{
	struct plane k;
	for (int i = 0; i < plane_num; i++)
	{
		for (int j = 0; j < plane_num - 1; j++)
		{
			if (plane_list[j].price > plane_list[j + 1].price)
			{
				k = plane_list[j];
				plane_list[j] = plane_list[j + 1];
				plane_list[j + 1] = k;
			}
		}
	}
	print_planes();
}

//	主界面函数
void main_screen();

/* 以上为函数声明，以下为函数实现*/

void main_screen()
{
	int j;
	printf("                      ★★★---欢迎进入机票管理系统---★★★                \n\n");
	printf("==============================================================================\n");
	printf("#  1\t普通用户登录系统\t\t\t\t\t\t     #\n\n");
	printf("#  2\t新用户注册\t\t\t\t\t\t\t     #\n\n");
	printf("#  3\t管理员登录\t\t\t\t\t\t\t     #\n\n");
	printf("#  0\t退出\t\t\t\t\t\t\t\t     #\n");
	printf("==============================================================================\n");
	printf("#  请在1-3(其它字符表示退出)中选择以回车键结束：\n");
	scanf_s("%d", &j);
	switch (j)
	{
	case 1:
		system("cls");
		//清除屏幕
		sign_in_screen();	//进入机票系统
		break;
	case 2:
		system("cls");
		regist_screen();	//进入用户注册系统
		break;
	case 3:
		system("cls"); 
		administrator_sign_in_screen();	//进入管理后台
		break;
	default:
		exit(0);
	}
}

void administrator_screen()
{
	int j;
	printf("                      ★★★---欢迎进入后台管理系统---★★★               \n\n");
	printf("==============================================================================\n");
	printf("#  1\t查询用户\t\t\t\t\t\t\t     #\n\n");
	printf("#  2\t查询用户信息\t\t\t\t\t\t\t     #\n\n");
	printf("#  3\t修改用户信息\t\t\t\t\t\t\t     #\n\n");
	printf("#  4\t删除用户信息\t\t\t\t\t\t\t     #\n\n");
	printf("#  5\t返回主页\t\t\t\t\t\t\t     #\n\n");
	printf("#  0\t退出程序\t\t\t\t\t\t\t     #\n");
	printf("==============================================================================\n");
	printf("#  请在0-5中选择并以回车结束: \n");
	scanf_s("%d", &j);

	switch (j)
	{
	case 1:
		while (1)
		{
			printf("==============================================================================\n");
			char field_name[15];
			char field_value[19];
			printf("请输入要查询的字段名并按回车确认(在name,age,sex,id_number,passport,power中选择)：\n");
			scanf_s("%s", field_name, 15);
			printf("请输入要查询的字段值并按回车确认：\n");
			scanf_s("%s", field_value, 19);
			user_result* result = query_user_by_info(field_value, field_name);
			if (result == NULL)
			{
				printf("\n字段名不存在!\n");
				printf("==============================================================================\n");
			}
			else
			{
				if (result->result_num == 0)
				{
					printf("查询结果为空");
				}
				else
				{
					printf("==============================================================================\n");
					printf("查询结果如下：\n");
					for (int i = 0; i < result->result_num; i++)
					{
						printf("name:%s\tage:%d\tsex:%d\tid_number:%s\tpassport:%s\tpower:%d\n", result->result[i]->name, result->result[i]->age, result->result[i]->sex, result->result[i]->id_number, result->result[i]->passport, result->result[i]->power);
						printf("==============================================================================\n");
					}
				}
			}
			printf("继续查询请输入1并按回车确认,返回管理员主页请输入任意字符：\n");
			char flag[10];
			scanf_s(" %s", &flag,10);
			if (strcmp(flag,"1")!=0)
			{
				system("cls");
				getchar();
				administrator_screen();
			}
		}
		break;

	case 2:
		printf("==============================================================================\n");
		while (1)
		{
			char field_name[15];
			char user_name[10];
			printf("请输入要查询的用户名并按回车确认:\n");
			scanf_s(" %s", user_name, 10);
			printf("请输入要查询的字段名并按回车确认(输入all表示显示全部信息或者在age,sex,id_number,passport,power中进行选择):\n");
			scanf_s(" %s", field_name, 15);
			char* result = NULL;

			printf("查询结果：\n");
			if (strcmp(field_name,"all")==0)
			{
				printf("☆==============================================================================☆\n");
				printf("  %-13s%-13s%-13s%-23s%-13s%-13s\n", "name", "age", "sex", "id_number", "passport", "power");
				result = query_info_by_uesr(1, user_name);
			}
			else
			{
				result = query_info_by_uesr(2, user_name, field_name);
			}
			if (result == NULL)
			{
				printf("查询结果为空！\n");
			}
			else
			{
				printf("%s\n", result);
			}
			printf("==============================================================================\n");
			printf("继续查询请输入1并按回车确认,返回管理员主页请输入任意字符：\n");
			char flag[10];
			scanf_s(" %s", &flag,10);
			if (strcmp(flag,"1")!=0)
			{
				system("cls");
				getchar();
				administrator_screen();
			}
		}
		break;

	case 3:
		printf("==============================================================================\n");
		while (1)
		{
			char user_name[10];
			char field_name[12];
			char new_value[19];
			printf("#  请输入要修改的用户名并按回车确认:\n");
			scanf_s(" %s", user_name, 10);
			printf("#  请输入要修改的字段名并按回车确认:\n");
			scanf_s(" %s", field_name, 12);
			printf("#  请输入字段的新值并按回车确认:\n");
			scanf_s(" %s", new_value, 19);
			int flag = modify_user_message(user_name, field_name, new_value);
			printf("==============================================================================\n");
			if (flag)
			{
				printf("修改失败！\n");
			}
			else
			{
				printf("修改成功！\n");
			}
			printf("继续修改请输入1并按回车确认,返回管理员主页请输入任意字符：\n");
			char flag2[10];
			scanf_s(" %s", &flag2,10);
			if (strcmp(flag2, "1") != 0)
			{
				system("cls");
				getchar();
				administrator_screen();
			}
		}
		break;

	case 4:
		printf("==============================================================================\n");
		while (1)
		{
			char user_name[10];
			printf("#  请输入要删除的用户名并按回车确认:\n");
			scanf_s(" %s", user_name, 10);
			printf("==============================================================================\n");
			char flag[5];
			printf("#  请确认是否要删除该用户，确认请输入“Yes”或“yes”并按回车确认\n");
			scanf_s(" %s", flag, 5);
			int result = 1;
			if ( (strcmp(flag,"yes")==0) || (strcmp(flag, "Yes") == 0) )
			{
				result = delet_user(user_name);
			}
			if (result)
			{
				printf("删除用户失败\n");
			}
			else
			{
				printf("删除用户成功\n");
			}
			printf("#  继续删除请输入1并按回车确认,返回管理员主页请输入任意字符：\n");
			char flag2[10];
			scanf_s(" %s", &flag2,10);
			printf("==============================================================================\n");
			if (strcmp(flag2,"1")!=0)
			{
				system("cls");
				getchar();
				administrator_screen();
			}
		}
		break;
	case 5:
		system("cls");
		main_screen();
		break;
	case 0:
		exit(0);
	}
}

void administrator_sign_in_screen()
{
	char user_name[10];
	char user_passport[12];

	printf("==============================================================================\n\n");
	printf("                      ★★★---欢迎进入后台管理系统---★★★                \n\n");
	printf("==============================================================================\n");
	printf("#  请输入管理员账号并按回车确认：\n");
	scanf_s("%s", user_name,10);
	printf("#  请输入管理员密码并按回车确认：\n");
	scanf_s("%s", user_passport,12);
	//验证通过则跳转到下一个UI界面，反之提示退出或重试
	if (administrator_verify(user_name, user_passport) == 0)
	{
		system("cls");
		administrator_screen(); 
	}
	else
	{
		int i;
		printf("#  管理员账号或密码错误，重试请输入1，返回主页请输入其它数字：\n");
		scanf_s("%d", &i);
		switch (i)
		{
		case 1:
			system("cls");
			administrator_sign_in_screen();
		default:
			system("cls");
			main_screen();
		}
	}
}

void sign_in_screen()
{
	char user[10];
	char passWord[12];
	printf("==============================================================================\n\n");
	printf("                      ★★★---欢迎进入登录界面---★★★                 \n\n");
	printf("==============================================================================\n");
	printf("#  请输入用户名并按回车确认：\n");
	scanf_s("%s", user, 10);
	printf("#  请输入密码并按回车确认：\n");
	scanf_s("%s", passWord,12);

	int ret = sign_in(user, passWord);

	if (0 == ret)
	{
		printf("登录成功");
		system("cls");
		ticket_screen();
	}

	else if (1 == ret)
	{
		printf("密码错误，（按y重新输入，其他键退出）：");
		char in;
		scanf_s(" %c", &in,1);
		if ('y' == in || 'Y' == in)
		{
			system("cls");
			sign_in_screen();
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		printf("用户名不存在，（输入y重新输入，其他键退出）：\n");
		char in;
		scanf_s(" %c", &in,1);
		if ('y' == in || 'Y' == in)
		{
			system("cls");
			sign_in_screen();
		}
		else
		{
			exit(0);
		}
	}
}

void regist_screen()
{
	printf("==============================================================================\n\n");
	printf("                      ★★★---欢迎进入注册界面---★★★                 \n\n");
	printf("==============================================================================\n");
	char username[10]="", pass1[12]="", pass2[12]="", id_number[19];
	int age, sex, power;

	printf("#  请输入用户名并按回车确认：\n");
	scanf_s("%s", username,10);
	printf("#  请输入年龄并按回车确认：\n");
	scanf_s("%d", &age);

	do 
	{
		printf("#  请输入性别(1代表男，0代表女)并按回车确认：\n");
		scanf_s(" %d", &sex);
		if (0 == sex || 1 == sex)
		{
			break;
		}
		printf("不符合规范，请重新输入");
	} while (1);

	printf("#  请输入身份证号码并按回车确认：\n");
	scanf_s(" %s", id_number,19);

	do 
	{
		printf("#  请输入身份标识符(1标识管理员权限,0表示普通用户)：\n");
		scanf_s("%d", &power);
		if (0 == power)
		{
			break;
		}
		else if (1 == power)
		{
			int ret;
			do 
			{
				printf("#  请验证管理员：\n");
				char user_name_[10], pass_[12];
				printf("#  请输入管理员账号并按回车确认：\n");
				scanf_s(" %s", user_name_,10);
				printf("#  请输入管理员密码并按回车确认：\n");
				scanf_s(" %s", pass_,12);
				ret = administrator_verify(user_name_, pass_);
				if (ret != 0)
				{
					printf("验证失败！\n");
					printf("重新验证（Y代表重新验证，输入其它字符退出程序）：\n");
					char in;
					scanf_s("%c", &in,1);
					if ('y' != in && 'Y' != in)
					{
						exit(0);
					}
				}
			} while (ret);
			break;
		}
		printf("#  不符合规范，请重新输入");
	} while (1);
	printf("==============================================================================\n");
	do 
	{
		printf("#  请输入密码并按回车确认：\n");
		scanf_s(" %s", pass1,12);
		printf("#  请再次输入密码并按回车确认：\n");
		scanf_s("%s", pass2,12);
	} while (strcmp(pass1, pass2) != 0);
	if (!regist(username, age, sex, id_number, pass1, power))
	{
		printf("注册成功，3秒后回到主页...");
		Sleep(3000);
		system("cls");
		main_screen();
	}
	else {
		printf("注册失败,3秒后回到主页...");
		Sleep(3000);
		system("cls");
		main_screen();
	}
}

void ticket_screen()
{
	printf(" ★----------------您好，欢迎进入自动化飞机订票系统！---★\n");
	printf("================================================================================\n");
	printf(" **-------- ----☆ 1. 浏 览 航 班 信  息 ☆----- ------------------**\n\n" " **-------- ☆  2. 查  询  航  班  信  息  -☆-------- ------------**\n\n" " **-------- ---☆  3.对航班按航班票价排序---☆-----------------------**\n\n" " **-------- ------☆  4. 查询航班  ☆-------- -----------------**\n\n" " **-------- ----------☆  0.退出  -☆-------- ---------------------**\n\n" " **-------- ---------------☆  ☆-------- -------------------------**\n\n" " **-------- -----------------☆ -------- --------------------------**\n\n" " **-------- ---------------☆ ☆-------- --------------------------**\n\n");
	printf("================================================================================\n");
	printf("请在0-4(其它字符表示退出)中选择以回车键结束：\n");
	int j;
	scanf_s("%d", &j);
	switch (j)
	{
	case 1: {
		printf("==============================================================================\n\n");
		print_planes();
		char flag[10];
		printf("#  继续订票请输入1并按回车确认，输入其它字符返回订票页面\n");
		scanf_s(" %s", &flag,10);
		if (strcmp(flag, "1") == 0)
		{
			printf("==============================================================================\n");
			char plane_id[10];
			int num = 0;
			printf("#  请输入要购买机票的航班号并按回车确认:\n");
			scanf_s(" %s", plane_id, 10);

			printf("#  请输入要购买机票的数量并按回车确认:\n");
			scanf_s(" %d", &num);
			int result = buy_ticket(plane_id, num);
			switch (result)
			{
			case 1:
				printf("余票不足，购买失败,3秒后返回购票主页......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 2:
				printf("航班号输入错误，购买失败,3秒后返回购票主页......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 3:
				printf("未知错误，购买失败,3秒后返回购票主页......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 0:
				printf("购买成功，3秒后返回购票主页......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			}
		}
		else
		{
			system("cls");
			ticket_screen();
		}
		break;
	}

	case 2: {
		while (1)
		{
			printf("#===================================================#\n");
			char plane_id[10];
			printf("请输入要查询航班的航班号并按回车确认:\n");
			scanf_s(" %s", plane_id, 10);
			int result = 1;
			printf("#===================================================#\n");
			for (int i = 0; i < plane_num; i++)
			{
				if (strcmp(plane_list[i].num, plane_id) == 0)
				{
					result = 0;
					printf("结果如下：\n");
					printf("航班号:%s\t飞机型号:%s\t出发地名称:%s\t目的地名称:%s\t起飞时间:%s\t降落时间:%s\t价格:%d\t剩余票量:%d\t\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination, plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
				}
			}
			if (result)
			{
				printf("查询结果为空\n");
			}
			char flag[10];
			printf("#===================================================#\n");
			printf("继续查询请输入1，输入其它字符返回订票首页\n");
			scanf_s(" %s", &flag,10);
			if (strcmp(flag,"1")==0)
			{
				system("cls");
				ticket_screen();
			}
		}
		break; }

	case 3: {
		printf("#===================================================#\n");
		plane_price_sort();
		printf("#===================================================#\n");
		char flag1[10];
		printf("#  继续订票请输入1并按回车确认，输入其它字符返回订票页面\n");
		scanf_s("%s", flag1,10);
		if (strcmp(flag1,"1")==0)
		{
			printf("==============================================================================\n");
			char plane_id[10];
			int num = 0;
			printf("#  请输入要购买机票的航班号并按回车确认:\n");
			scanf_s(" %s", plane_id, 10);
			printf("#  请输入要购买机票的数量并按回车确认:\n");
			scanf_s(" %d", &num);
			int result = buy_ticket(plane_id, num);
			switch (result)
			{
			case 1:
				printf("余票不足，购买失败,3秒后返回购票主页......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 2:
				printf("航班号输入错误，购买失败,3秒后返回购票主页......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 3:
				printf("未知错误，购买失败,3秒后返回购票主页......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 0:
				printf("购买成功，3秒后返回购票主页......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			}
		}
		else
		{
			system("cls");
			ticket_screen();
		}
		break; }

	case 4: {
		printf("#===================================================#\n");
		int field = 0;
		char key[15];
		printf("请输入查询依据字段序号（0表示航班号，1表示起点，2表示目的地）并按回车确认:\n");
		scanf_s(" %d", &field);
		printf("请输入查询关键字并按回车确认:\n");
		scanf_s(" %s", key, 15);
		switch (field)
		{
		case 0:
			query_plane_by_num(key);
			break;

		case 1:
			query_plane_by_starting_point(key);
			break;

		case 2:
			query_plane_destination(key);
			break;

		default:
			break;
		}
		char flag2[10];
		printf("#  继续订票请输入1并按回车确认，输入其它字符返回订票页面\n");
		scanf_s(" %s", &flag2,10);
		if (strcmp(flag2, "1") == 0)
		{
			printf("==============================================================================\n");
			char plane_id[10];
			int num = 0;
			printf("#  请输入要购买机票的航班号并按回车确认:\n");
			scanf_s(" %s", plane_id, 10);
			printf("#  请输入要购买机票的数量并按回车确认:\n");
			scanf_s(" %d", &num);
			int result = buy_ticket(plane_id, num);
			switch (result)
			{
			case 1:
				printf("余票不足，购买失败,3秒后返回购票主页......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 2:
				printf("航班号输入错误，购买失败,3秒后返回购票主页......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 3:
				printf("未知错误，购买失败,3秒后返回购票主页......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 0:
				printf("购买成功，3秒后返回购票主页......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			}
		}
		else
		{
			system("cls");
			ticket_screen();
		}
		break;
		break;
	}

	case 0: {
		exit(0);
		break;
	}

	default: {
		exit(0);
	}
	}
}
