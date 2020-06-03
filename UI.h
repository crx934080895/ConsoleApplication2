#include <stdio.h>
#include "user_system.h"
#include "ticket_system.h"
#include<windows.h>

/*����Ϊ��������*/

// �û���¼���溯��
void sign_in_screen();

// �û�ע����溯��
void regist_screen();

//	����Ա��¼���溯��
void administrator_sign_in_screen();

//	����Ա��̨���溯��
// ����Ա��̨���������ɾ�Ĳ��û����û�����
void administrator_screen();

//	��Ʊ���溯��
// ���Բ�ѯ���࣬����Ʊ��������ɸѡƱ���Ƽ�·�ߵ�
void ticket_screen();

//�����Ż�·��
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

//	�����溯��
void main_screen();

/* ����Ϊ��������������Ϊ����ʵ��*/

void main_screen()
{
	int j;
	printf("                      ����---��ӭ�����Ʊ����ϵͳ---����                \n\n");
	printf("==============================================================================\n");
	printf("#  1\t��ͨ�û���¼ϵͳ\t\t\t\t\t\t     #\n\n");
	printf("#  2\t���û�ע��\t\t\t\t\t\t\t     #\n\n");
	printf("#  3\t����Ա��¼\t\t\t\t\t\t\t     #\n\n");
	printf("#  0\t�˳�\t\t\t\t\t\t\t\t     #\n");
	printf("==============================================================================\n");
	printf("#  ����1-3(�����ַ���ʾ�˳�)��ѡ���Իس���������\n");
	scanf_s("%d", &j);
	switch (j)
	{
	case 1:
		system("cls");
		//�����Ļ
		sign_in_screen();	//�����Ʊϵͳ
		break;
	case 2:
		system("cls");
		regist_screen();	//�����û�ע��ϵͳ
		break;
	case 3:
		system("cls"); 
		administrator_sign_in_screen();	//��������̨
		break;
	default:
		exit(0);
	}
}

void administrator_screen()
{
	int j;
	printf("                      ����---��ӭ�����̨����ϵͳ---����               \n\n");
	printf("==============================================================================\n");
	printf("#  1\t��ѯ�û�\t\t\t\t\t\t\t     #\n\n");
	printf("#  2\t��ѯ�û���Ϣ\t\t\t\t\t\t\t     #\n\n");
	printf("#  3\t�޸��û���Ϣ\t\t\t\t\t\t\t     #\n\n");
	printf("#  4\tɾ���û���Ϣ\t\t\t\t\t\t\t     #\n\n");
	printf("#  5\t������ҳ\t\t\t\t\t\t\t     #\n\n");
	printf("#  0\t�˳�����\t\t\t\t\t\t\t     #\n");
	printf("==============================================================================\n");
	printf("#  ����0-5��ѡ���Իس�����: \n");
	scanf_s("%d", &j);

	switch (j)
	{
	case 1:
		while (1)
		{
			printf("==============================================================================\n");
			char field_name[15];
			char field_value[19];
			printf("������Ҫ��ѯ���ֶ��������س�ȷ��(��name,age,sex,id_number,passport,power��ѡ��)��\n");
			scanf_s("%s", field_name, 15);
			printf("������Ҫ��ѯ���ֶ�ֵ�����س�ȷ�ϣ�\n");
			scanf_s("%s", field_value, 19);
			user_result* result = query_user_by_info(field_value, field_name);
			if (result == NULL)
			{
				printf("\n�ֶ���������!\n");
				printf("==============================================================================\n");
			}
			else
			{
				if (result->result_num == 0)
				{
					printf("��ѯ���Ϊ��");
				}
				else
				{
					printf("==============================================================================\n");
					printf("��ѯ������£�\n");
					for (int i = 0; i < result->result_num; i++)
					{
						printf("name:%s\tage:%d\tsex:%d\tid_number:%s\tpassport:%s\tpower:%d\n", result->result[i]->name, result->result[i]->age, result->result[i]->sex, result->result[i]->id_number, result->result[i]->passport, result->result[i]->power);
						printf("==============================================================================\n");
					}
				}
			}
			printf("������ѯ������1�����س�ȷ��,���ع���Ա��ҳ�����������ַ���\n");
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
			printf("������Ҫ��ѯ���û��������س�ȷ��:\n");
			scanf_s(" %s", user_name, 10);
			printf("������Ҫ��ѯ���ֶ��������س�ȷ��(����all��ʾ��ʾȫ����Ϣ������age,sex,id_number,passport,power�н���ѡ��):\n");
			scanf_s(" %s", field_name, 15);
			char* result = NULL;

			printf("��ѯ�����\n");
			if (strcmp(field_name,"all")==0)
			{
				printf("��==============================================================================��\n");
				printf("  %-13s%-13s%-13s%-23s%-13s%-13s\n", "name", "age", "sex", "id_number", "passport", "power");
				result = query_info_by_uesr(1, user_name);
			}
			else
			{
				result = query_info_by_uesr(2, user_name, field_name);
			}
			if (result == NULL)
			{
				printf("��ѯ���Ϊ�գ�\n");
			}
			else
			{
				printf("%s\n", result);
			}
			printf("==============================================================================\n");
			printf("������ѯ������1�����س�ȷ��,���ع���Ա��ҳ�����������ַ���\n");
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
			printf("#  ������Ҫ�޸ĵ��û��������س�ȷ��:\n");
			scanf_s(" %s", user_name, 10);
			printf("#  ������Ҫ�޸ĵ��ֶ��������س�ȷ��:\n");
			scanf_s(" %s", field_name, 12);
			printf("#  �������ֶε���ֵ�����س�ȷ��:\n");
			scanf_s(" %s", new_value, 19);
			int flag = modify_user_message(user_name, field_name, new_value);
			printf("==============================================================================\n");
			if (flag)
			{
				printf("�޸�ʧ�ܣ�\n");
			}
			else
			{
				printf("�޸ĳɹ���\n");
			}
			printf("�����޸�������1�����س�ȷ��,���ع���Ա��ҳ�����������ַ���\n");
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
			printf("#  ������Ҫɾ�����û��������س�ȷ��:\n");
			scanf_s(" %s", user_name, 10);
			printf("==============================================================================\n");
			char flag[5];
			printf("#  ��ȷ���Ƿ�Ҫɾ�����û���ȷ�������롰Yes����yes�������س�ȷ��\n");
			scanf_s(" %s", flag, 5);
			int result = 1;
			if ( (strcmp(flag,"yes")==0) || (strcmp(flag, "Yes") == 0) )
			{
				result = delet_user(user_name);
			}
			if (result)
			{
				printf("ɾ���û�ʧ��\n");
			}
			else
			{
				printf("ɾ���û��ɹ�\n");
			}
			printf("#  ����ɾ��������1�����س�ȷ��,���ع���Ա��ҳ�����������ַ���\n");
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
	printf("                      ����---��ӭ�����̨����ϵͳ---����                \n\n");
	printf("==============================================================================\n");
	printf("#  ���������Ա�˺Ų����س�ȷ�ϣ�\n");
	scanf_s("%s", user_name,10);
	printf("#  ���������Ա���벢���س�ȷ�ϣ�\n");
	scanf_s("%s", user_passport,12);
	//��֤ͨ������ת����һ��UI���棬��֮��ʾ�˳�������
	if (administrator_verify(user_name, user_passport) == 0)
	{
		system("cls");
		administrator_screen(); 
	}
	else
	{
		int i;
		printf("#  ����Ա�˺Ż������������������1��������ҳ�������������֣�\n");
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
	printf("                      ����---��ӭ�����¼����---����                 \n\n");
	printf("==============================================================================\n");
	printf("#  �������û��������س�ȷ�ϣ�\n");
	scanf_s("%s", user, 10);
	printf("#  ���������벢���س�ȷ�ϣ�\n");
	scanf_s("%s", passWord,12);

	int ret = sign_in(user, passWord);

	if (0 == ret)
	{
		printf("��¼�ɹ�");
		system("cls");
		ticket_screen();
	}

	else if (1 == ret)
	{
		printf("������󣬣���y�������룬�������˳�����");
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
		printf("�û��������ڣ�������y�������룬�������˳�����\n");
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
	printf("                      ����---��ӭ����ע�����---����                 \n\n");
	printf("==============================================================================\n");
	char username[10]="", pass1[12]="", pass2[12]="", id_number[19];
	int age, sex, power;

	printf("#  �������û��������س�ȷ�ϣ�\n");
	scanf_s("%s", username,10);
	printf("#  ���������䲢���س�ȷ�ϣ�\n");
	scanf_s("%d", &age);

	do 
	{
		printf("#  �������Ա�(1�����У�0����Ů)�����س�ȷ�ϣ�\n");
		scanf_s(" %d", &sex);
		if (0 == sex || 1 == sex)
		{
			break;
		}
		printf("�����Ϲ淶������������");
	} while (1);

	printf("#  ���������֤���벢���س�ȷ�ϣ�\n");
	scanf_s(" %s", id_number,19);

	do 
	{
		printf("#  ��������ݱ�ʶ��(1��ʶ����ԱȨ��,0��ʾ��ͨ�û�)��\n");
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
				printf("#  ����֤����Ա��\n");
				char user_name_[10], pass_[12];
				printf("#  ���������Ա�˺Ų����س�ȷ�ϣ�\n");
				scanf_s(" %s", user_name_,10);
				printf("#  ���������Ա���벢���س�ȷ�ϣ�\n");
				scanf_s(" %s", pass_,12);
				ret = administrator_verify(user_name_, pass_);
				if (ret != 0)
				{
					printf("��֤ʧ�ܣ�\n");
					printf("������֤��Y����������֤�����������ַ��˳����򣩣�\n");
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
		printf("#  �����Ϲ淶������������");
	} while (1);
	printf("==============================================================================\n");
	do 
	{
		printf("#  ���������벢���س�ȷ�ϣ�\n");
		scanf_s(" %s", pass1,12);
		printf("#  ���ٴ��������벢���س�ȷ�ϣ�\n");
		scanf_s("%s", pass2,12);
	} while (strcmp(pass1, pass2) != 0);
	if (!regist(username, age, sex, id_number, pass1, power))
	{
		printf("ע��ɹ���3���ص���ҳ...");
		Sleep(3000);
		system("cls");
		main_screen();
	}
	else {
		printf("ע��ʧ��,3���ص���ҳ...");
		Sleep(3000);
		system("cls");
		main_screen();
	}
}

void ticket_screen()
{
	printf(" ��----------------���ã���ӭ�����Զ����ɻ���Ʊϵͳ��---��\n");
	printf("================================================================================\n");
	printf(" **-------- ----�� 1. � �� �� �� ��  Ϣ ��----- ------------------**\n\n" " **-------- ��  2. ��  ѯ  ��  ��  ��  Ϣ  -��-------- ------------**\n\n" " **-------- ---��  3.�Ժ��ఴ����Ʊ������---��-----------------------**\n\n" " **-------- ------��  4. ��ѯ����  ��-------- -----------------**\n\n" " **-------- ----------��  0.�˳�  -��-------- ---------------------**\n\n" " **-------- ---------------��  ��-------- -------------------------**\n\n" " **-------- -----------------�� -------- --------------------------**\n\n" " **-------- ---------------�� ��-------- --------------------------**\n\n");
	printf("================================================================================\n");
	printf("����0-4(�����ַ���ʾ�˳�)��ѡ���Իس���������\n");
	int j;
	scanf_s("%d", &j);
	switch (j)
	{
	case 1: {
		printf("==============================================================================\n\n");
		print_planes();
		char flag[10];
		printf("#  ������Ʊ������1�����س�ȷ�ϣ����������ַ����ض�Ʊҳ��\n");
		scanf_s(" %s", &flag,10);
		if (strcmp(flag, "1") == 0)
		{
			printf("==============================================================================\n");
			char plane_id[10];
			int num = 0;
			printf("#  ������Ҫ�����Ʊ�ĺ���Ų����س�ȷ��:\n");
			scanf_s(" %s", plane_id, 10);

			printf("#  ������Ҫ�����Ʊ�����������س�ȷ��:\n");
			scanf_s(" %d", &num);
			int result = buy_ticket(plane_id, num);
			switch (result)
			{
			case 1:
				printf("��Ʊ���㣬����ʧ��,3��󷵻ع�Ʊ��ҳ......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 2:
				printf("�����������󣬹���ʧ��,3��󷵻ع�Ʊ��ҳ......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 3:
				printf("δ֪���󣬹���ʧ��,3��󷵻ع�Ʊ��ҳ......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 0:
				printf("����ɹ���3��󷵻ع�Ʊ��ҳ......");
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
			printf("������Ҫ��ѯ����ĺ���Ų����س�ȷ��:\n");
			scanf_s(" %s", plane_id, 10);
			int result = 1;
			printf("#===================================================#\n");
			for (int i = 0; i < plane_num; i++)
			{
				if (strcmp(plane_list[i].num, plane_id) == 0)
				{
					result = 0;
					printf("������£�\n");
					printf("�����:%s\t�ɻ��ͺ�:%s\t����������:%s\tĿ�ĵ�����:%s\t���ʱ��:%s\t����ʱ��:%s\t�۸�:%d\tʣ��Ʊ��:%d\t\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination, plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
				}
			}
			if (result)
			{
				printf("��ѯ���Ϊ��\n");
			}
			char flag[10];
			printf("#===================================================#\n");
			printf("������ѯ������1�����������ַ����ض�Ʊ��ҳ\n");
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
		printf("#  ������Ʊ������1�����س�ȷ�ϣ����������ַ����ض�Ʊҳ��\n");
		scanf_s("%s", flag1,10);
		if (strcmp(flag1,"1")==0)
		{
			printf("==============================================================================\n");
			char plane_id[10];
			int num = 0;
			printf("#  ������Ҫ�����Ʊ�ĺ���Ų����س�ȷ��:\n");
			scanf_s(" %s", plane_id, 10);
			printf("#  ������Ҫ�����Ʊ�����������س�ȷ��:\n");
			scanf_s(" %d", &num);
			int result = buy_ticket(plane_id, num);
			switch (result)
			{
			case 1:
				printf("��Ʊ���㣬����ʧ��,3��󷵻ع�Ʊ��ҳ......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 2:
				printf("�����������󣬹���ʧ��,3��󷵻ع�Ʊ��ҳ......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 3:
				printf("δ֪���󣬹���ʧ��,3��󷵻ع�Ʊ��ҳ......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 0:
				printf("����ɹ���3��󷵻ع�Ʊ��ҳ......");
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
		printf("�������ѯ�����ֶ���ţ�0��ʾ����ţ�1��ʾ��㣬2��ʾĿ�ĵأ������س�ȷ��:\n");
		scanf_s(" %d", &field);
		printf("�������ѯ�ؼ��ֲ����س�ȷ��:\n");
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
		printf("#  ������Ʊ������1�����س�ȷ�ϣ����������ַ����ض�Ʊҳ��\n");
		scanf_s(" %s", &flag2,10);
		if (strcmp(flag2, "1") == 0)
		{
			printf("==============================================================================\n");
			char plane_id[10];
			int num = 0;
			printf("#  ������Ҫ�����Ʊ�ĺ���Ų����س�ȷ��:\n");
			scanf_s(" %s", plane_id, 10);
			printf("#  ������Ҫ�����Ʊ�����������س�ȷ��:\n");
			scanf_s(" %d", &num);
			int result = buy_ticket(plane_id, num);
			switch (result)
			{
			case 1:
				printf("��Ʊ���㣬����ʧ��,3��󷵻ع�Ʊ��ҳ......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 2:
				printf("�����������󣬹���ʧ��,3��󷵻ع�Ʊ��ҳ......\n");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 3:
				printf("δ֪���󣬹���ʧ��,3��󷵻ع�Ʊ��ҳ......");
				Sleep(3000);
				system("cls");
				ticket_screen();
				break;
			case 0:
				printf("����ɹ���3��󷵻ع�Ʊ��ҳ......");
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
