#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <winsock.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")
#pragma once

typedef struct user
{
	char name[10];	//����
	int age;		//����
	int sex;		//�Ա�1�������ԣ�0����Ů�ԣ�
	char id_number[19];	//18λ���֤��
	char passport[12];	//�11λ����
	int power;	//��ݱ�ʶ��1��ʶ����ԱȨ��,0��ʾ��ͨ�û���
}user;
user user_list[100];
int user_num = 0;

typedef struct plane
{
	char num[10];	//�����	
	char model[20];	//�ɻ��ͺ�
	char starting_point[20];	//����������
	char destination[20];	//Ŀ�ĵ�����
	char start_time[17];	//���ʱ��  ��ʽ��2018.10.10#23:01
	char end_time[17];	//����ʱ��
	int count;	//ʣ��Ʊ��
	int price;	//�۸�
}plane;
plane plane_list[100];
int plane_num = 0;

static MYSQL mydata;	//���ݿ�ָ��
char database_user[20];
char database_passport[20];



//����Ϊ��������

//==================================================================
//��������load_users
//���ܣ������ݿ��ȡ�û����ݵ�ȫ�ֱ���user_list
//�����������
//����ֵ����
//==================================================================
void load_users();

//==================================================================
//��������load_users
//���ܣ������ݿ��ȡ�û����ݵ�ȫ�ֱ���user_list
//�����������
//����ֵ����
//==================================================================
void load_planes();

//==================================================================
//��������by_ticket
//���ܣ�����n��ĳ���汾����Ʊ��������ʾ����ĳ�������n��Ʊ
//���������num �����
//					count  ��������
//����ֵ������int   1��ʾ��Ʊ���㣬����ʧ��
//							 2��ʾ�����������󣬹���ʧ��,
//							3 ��ʾд��ʧ�ܣ�δ֪����
//				  			0��ʾ����ɹ�
//==================================================================
int buy_ticket(char num[], int count);

//==================================================================
//��������modify_user_message
//���ܣ��޸��û���ĳ���ֶ���Ϣ
//���������user_nmae	�û���
//				filed_name	�ֶ���
//				new_value	�޸ĺ��ֵ
//����ֵ������int
//          ����0��ʾ�޸ĳɹ���
//          ����1��ʾ�޸�ʧ��;
//==================================================================
int modify_user_message(char user_name[], char filed_name[], char new_value[]);

//==================================================================
//��������delet_user
//���ܣ������û���ɾ��ĳ���û�
//���������user_nmae	�û���
//����ֵ������int
//          ����0��ʾ�޸ĳɹ���
//          ����1��ʾ�޸�ʧ��;
//==================================================================
int delet_user(char user_name[]);

//==================================================================
//��������regist
//���ܣ���ԭ�ṹ������ǿ�λ�õ�ĩβ��ӳ�Ա
//���������
//			user_name[10];	//����
//			age;		//����
//			sex;		//�Ա�1�������ԣ�0����Ů�ԣ�
//			id_number[18];	//18λ���֤��
//			passport[12];	//�12λ����
//			power;	//��ݱ�ʶ��1��ʶ����ԱȨ��,0��ʾ��ͨ�û���
//����ֵ������int
//				ע��ɹ�����0
//				ע��ʧ�ܷ���1
//ע�� ʹ�ô˺���ע�����Ա���ʱ��Ҫ��֤һ����֪�Ĺ���Ա�˻�
//==================================================================
int regist(char name[],int age,int sex,char id_number[],char passport[],int power);

//==================================================================
//��������init
//���ܣ��������ļ��ж�ȡ���ݿ���˺�����
//�����������
//����ֵ����
//==================================================================
void init();

//����Ϊ��������������Ϊ����ʵ��

void load_planes()
{
	MYSQL_RES* result;	//��ѯ���ָ��
	MYSQL_ROW row;	//��Ų�ѯsql����ַ�������

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("���ݿ�����ʧ�ܣ�\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	// ��ѯ���ݿ�
	char sql[100] = "select * from new_schema.planes;";
	mysql_query(&mydata, sql);
	result = mysql_store_result(&mydata);//��ȡ���

	int count = 0;
	//һ��һ�еض�ȡ���
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
	MYSQL_RES* result = NULL;	//��ѯ���ָ��
	MYSQL_ROW row = NULL;	//��Ų�ѯsql����ַ�������

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("���ݿ�����ʧ�ܣ�\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	//�����ѯ����ѯ��Ʊ
	int spare_ticket;	//��Ʊ����
	char sql[100];
	sprintf_s(sql, 100, "SELECT count FROM new_schema.planes where(num='%s');", num);
	mysql_query(&mydata, sql);
	result = mysql_store_result(&mydata);//��ȡ���

	//û���ҵ���Ӧ���࣬�����˳�
	if (result->row_count == NULL)
	{
		return 2;
	}

	row = mysql_fetch_row(result);
	spare_ticket = atoi(row[0]);

	//��Ʊ����,�����˳�
	if (spare_ticket < count)
	{
		return 1;
	}

	//�ѽ��д�����ݿ�
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
	MYSQL_RES* result;	//��ѯ���ָ��
	MYSQL_ROW row;	//��Ų�ѯsql����ַ�������

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("���ݿ�����ʧ�ܣ�\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	// ��ѯ���ݿ�
	char sql[100] = "select * from new_schema.users;";
	mysql_query(&mydata, sql);
	result = mysql_store_result(&mydata);//��ȡ���

	int count = 0;
	//һ��һ�еض�ȡ���
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
	MYSQL_RES* result = NULL;	//��ѯ���ָ��
	MYSQL_ROW row = NULL;	//��Ų�ѯsql����ַ�������

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("���ݿ�����ʧ�ܣ�\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	char sql[150];
	sprintf_s(sql, 150, "UPDATE `new_schema`.`users` SET `%s` = '%s' WHERE (`name` = '%s');",filed_name, new_value, user_name);
	
	if (mysql_query(&mydata, sql) == 0)
	{
		mysql_free_result(result);
		mysql_close(&mydata);
		//���½ṹ������
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

	MYSQL_ROW row = NULL;	//��Ų�ѯsql����ַ�������

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("���ݿ�����ʧ�ܣ�\\n");
		fprintf(stderr, " %s\n", mysql_error(&mydata));
		exit(0);
	}

	char sql[100];
	sprintf_s(sql, 100, "DELETE FROM `new_schema`.`users` WHERE (`name` = '%s');", user_name);

	if (mysql_query(&mydata, sql) == 0)
	{
		mysql_close(&mydata);
		// �����ݿ�ɾ���û�֮����Ҫ�����б� 
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
	MYSQL_ROW row = NULL;	//��Ų�ѯsql����ַ�������

	mysql_init(&mydata);

	if (mysql_real_connect(&mydata, "localhost", "root", "123456", "new_schema", 3306, NULL, 0) == NULL)
	{
		printf("���ݿ�����ʧ�ܣ�\\n");
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
		printf("���ݿ�������Ϣ��ȡʧ��!");
		exit(0);
	}
	fgets(database_user, 20, fp1);
	fgets(database_passport, 20, fp1);
}