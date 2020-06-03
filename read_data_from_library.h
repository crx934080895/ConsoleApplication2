#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <winsock.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")
#pragma once

typedef struct user
{
	char name[10];	//姓名
	int age;		//年龄
	int sex;		//性别（1代表男性，0代表女性）
	char id_number[19];	//18位身份证号
	char passport[12];	//最长11位密码
	int power;	//身份标识（1标识管理员权限,0表示普通用户）
}user;
user user_list[100];
int user_num = 0;

typedef struct plane
{
	char num[10];	//航班号	
	char model[20];	//飞机型号
	char starting_point[20];	//出发地名称
	char destination[20];	//目的地名称
	char start_time[17];	//起飞时间  格式：2018.10.10#23:01
	char end_time[17];	//到达时间
	int count;	//剩余票数
	int price;	//价格
}plane;
plane plane_list[100];
int plane_num = 0;

static MYSQL mydata;	//数据库指针
char database_user[20];
char database_passport[20];



//以下为函数声明

//==================================================================
//函数名：load_users
//功能：从数据库读取用户数据到全局变量user_list
//输入参数：无
//返回值：无
//==================================================================
void load_users();

//==================================================================
//函数名：load_users
//功能：从数据库读取用户数据到全局变量user_list
//输入参数：无
//返回值：无
//==================================================================
void load_planes();

//==================================================================
//函数名：by_ticket
//功能：减少n张某个版本的余票数量，表示购买某个航班的n张票
//输入参数：num 航班号
//					count  购买数量
//返回值：类型int   1表示余票不足，购买失败
//							 2表示航班号输入错误，购买失败,
//							3 表示写入失败，未知错误
//				  			0表示购买成功
//==================================================================
int buy_ticket(char num[], int count);

//==================================================================
//函数名：modify_user_message
//功能：修改用户的某个字段信息
//输入参数：user_nmae	用户名
//				filed_name	字段名
//				new_value	修改后的值
//返回值：类型int
//          返回0表示修改成功；
//          返回1表示修改失败;
//==================================================================
int modify_user_message(char user_name[], char filed_name[], char new_value[]);

//==================================================================
//函数名：delet_user
//功能：根据用户名删除某个用户
//输入参数：user_nmae	用户名
//返回值：类型int
//          返回0表示修改成功；
//          返回1表示修改失败;
//==================================================================
int delet_user(char user_name[]);

//==================================================================
//函数名：regist
//功能：在原结构体数组非空位置的末尾添加成员
//输入参数：
//			user_name[10];	//姓名
//			age;		//年龄
//			sex;		//性别（1代表男性，0代表女性）
//			id_number[18];	//18位身份证号
//			passport[12];	//最长12位密码
//			power;	//身份标识（1标识管理员权限,0表示普通用户）
//返回值：类型int
//				注册成功返回0
//				注册失败返回1
//注意 使用此函数注册管理员身份时先要验证一个已知的管理员账户
//==================================================================
int regist(char name[],int age,int sex,char id_number[],char passport[],int power);

//==================================================================
//函数名：init
//功能：从配置文件中读取数据库的账号密码
//输入参数：无
//返回值：无
//==================================================================
void init();

//以上为函数声明，以下为函数实现

void load_planes()
{
	MYSQL_RES* result;	//查询结果指针
	MYSQL_ROW row;	//存放查询sql语句字符串数组

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("数据库连接失败！\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	// 查询数据库
	char sql[100] = "select * from new_schema.planes;";
	mysql_query(&mydata, sql);
	result = mysql_store_result(&mydata);//获取结果

	int count = 0;
	//一行一行地读取结果
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		strcpy_s(plane_list[count].num, 10, row[0]);
		strcpy_s(plane_list[count].model, 20, row[1]);
		strcpy_s(plane_list[count].starting_point, 20, row[2]);
		strcpy_s(plane_list[count].destination, 20, row[3]);
		strcpy_s(plane_list[count].start_time, 17, row[4]);
		strcpy_s(plane_list[count].end_time, 17, row[5]);
		plane_list[count].count = atoi(row[6]);
		plane_list[count].price = atoi(row[7]);
		count++;
	}
	plane_num = count;

	mysql_free_result(result);
	mysql_close(&mydata);
}

int buy_ticket(char num[], int count)
{
	MYSQL_RES* result = NULL;	//查询结果指针
	MYSQL_ROW row = NULL;	//存放查询sql语句字符串数组

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("数据库连接失败！\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	//构造查询语句查询余票
	int spare_ticket;	//余票数量
	char sql[100];
	sprintf_s(sql, 100, "SELECT count FROM new_schema.planes where(num='%s');", num);
	mysql_query(&mydata, sql);
	result = mysql_store_result(&mydata);//获取结果

	//没有找到对应航班，函数退出
	if (result->row_count == NULL)
	{
		return 2;
	}

	row = mysql_fetch_row(result);
	spare_ticket = atoi(row[0]);

	//余票不足,函数退出
	if (spare_ticket < count)
	{
		return 1;
	}

	//把结果写入数据库
	sprintf_s(sql, 100, "UPDATE `new_schema`.`planes` SET `count` = '%d' WHERE (`num` = '%s');", spare_ticket - count, num);


	if (mysql_query(&mydata, sql) == 0)
	{
		mysql_free_result(result);
		mysql_close(&mydata);
		load_planes();
		return 0;
	}
	else
	{
		return 3;
	}
}

void load_users()
{
	MYSQL_RES* result;	//查询结果指针
	MYSQL_ROW row;	//存放查询sql语句字符串数组

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("数据库连接失败！\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	// 查询数据库
	char sql[100] = "select * from new_schema.users;";
	mysql_query(&mydata, sql);
	result = mysql_store_result(&mydata);//获取结果

	int count = 0;
	//一行一行地读取结果
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		strcpy_s(user_list[count].name, 10, row[0]);
		strcpy_s(user_list[count].id_number, 19, row[3]);
		strcpy_s(user_list[count].passport, 12, row[4]);

		user_list[count].age = atoi(row[1]);
		user_list[count].sex = atoi(row[2]);
		user_list[count].power = atoi(row[5]);

		count++;
	}
	user_num = count;

	mysql_free_result(result);
	mysql_close(&mydata);

}

int modify_user_message(char user_name[],char filed_name[],char new_value[])
{
	MYSQL_RES* result = NULL;	//查询结果指针
	MYSQL_ROW row = NULL;	//存放查询sql语句字符串数组

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("数据库连接失败！\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	char sql[150];
	sprintf_s(sql, 150, "UPDATE `new_schema`.`users` SET `%s` = '%s' WHERE (`name` = '%s');",filed_name, new_value, user_name);
	
	if (mysql_query(&mydata, sql) == 0)
	{
		mysql_free_result(result);
		mysql_close(&mydata);
		//更新结构体数组
		load_users();
		return 0;
	}
	else
	{
		mysql_free_result(result);
		mysql_close(&mydata);
		return 1;
	}
}

int delet_user(char user_name[])
{

	MYSQL_ROW row = NULL;	//存放查询sql语句字符串数组

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("数据库连接失败！\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	char sql[100];
	sprintf_s(sql, 100, "DELETE FROM `new_schema`.`users` WHERE (`name` = '%s');", user_name);

	if (mysql_query(&mydata, sql) == 0)
	{
		mysql_close(&mydata);
		// 从数据库删除用户之后需要更新列表 
		load_users();
		return 0;
	}

	else
	{
		mysql_close(&mydata);
		return 1;
	}
}

int regist(char user_name[], int age, int sex, char id_number[], char passport[], int power)
{
	MYSQL_ROW row = NULL;	//存放查询sql语句字符串数组

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("数据库连接失败！\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	char sql[200];
	sprintf_s(sql, 200, "INSERT INTO `new_schema`.`users` (`name`, `age`, `sex`, `id_number`, `passport`, `power`) VALUES('%s', '%d', '%d', '%s', '%s', '%d');", user_name,age,sex,id_number,passport,power);

	if (mysql_query(&mydata, sql) == 0)
	{
		mysql_close(&mydata);
		load_users();
		return 0;
	}
	else
	{
		mysql_close(&mydata);
		return 1;
	}
	
}

void init()
{
	FILE* fp1 = fopen(".//config.txt", "r");
	if (fp1==NULL)
	{
		printf("数据库配置信息读取失败!");
		exit(0);
	}
	fgets(database_user, 20, fp1);
	fgets(database_passport, 20, fp1);
}