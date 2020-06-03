#include <stdio.h>
#include "read_data_from_library.h"
#pragma once

//�ýṹ�����鴢��ɻ���Ϣ
//user_plane[100]����"read_data_from_library.h"����

//��������6�����У����ڽӾ����ʾ������֮��ľ���

//��ʾ���к�����Ϣ
void print_planes()
{
	for (int i = 0; i < plane_num; i++)
	{
		printf("��==============================================================================��\n\n");
		printf("%d  %-22s%-22s%-22s%-22s\n", i + 1, "�����", "�ɻ��ͺ�", "����������", "Ŀ�ĵ�����");
		printf("   %-22s%-22s%-22s%-22s\n\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination);
		printf("%d  %-22s%-22s%-22s%-22s\n", i + 1, "���ʱ��", "����ʱ��", "�۸�", "ʣ��Ʊ��");
		printf("   %-22s%-22s%-22d%-22d\n\n", plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
	}
}

//ͨ������Ų�ѯĳ�ܺ������Ϣ
void query_plane_by_num(char plane_id[])
{
	int count = 0;
	for (int i = 0; i < plane_num; i++)
	{
		if (strcmp(plane_id, plane_list[i].num) == 0)
		{
			printf("\t\t\t��==============================================================================��\n\n");
			printf("\t\t\t  %-22s%-22s%-22s%-22s\n", "�����", "�ɻ��ͺ�", "����������", "Ŀ�ĵ�����");
			printf("\t\t\t   %-22s%-22s%-22s%-22s\n\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination);
			printf("\t\t\t  %-22s%-22s%-22s%-22s\n", "���ʱ��", "����ʱ��", "�۸�", "ʣ��Ʊ��");
			printf("\t\t\t   %-22s%-22s%-22d%-22d\n\n", plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
		}
	}
	if (count == 0)
	{
		printf("���ҽ��Ϊ��\n");
	}
	printf("#===================================================#\n");
}

//�����ΪXX���еĺ���
void query_plane_by_starting_point(char start_point[])
{
	int count = 0;
	for (int i = 0; i < plane_num; i++)
	{
		if (strcmp(start_point,plane_list[i].starting_point)==0)
		{
			count++;
			printf("��==============================================================================��\n\n");
			printf("  %-22s%-22s%-22s%-22s\n", "�����", "�ɻ��ͺ�", "����������", "Ŀ�ĵ�����");
			printf("   %-22s%-22s%-22s%-22s\n\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination);
			printf("  %-22s%-22s%-22s%-22s\n", "���ʱ��", "����ʱ��", "�۸�", "ʣ��Ʊ��");
			printf("   %-22s%-22s%-22d%-22d\n\n", plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
		}
	}
	if (count ==0)
	{
		printf("���ҽ��Ϊ��\n");
	}
	printf("==============================================================================\n");
}

//���յ�ΪXX���еĺ���
void query_plane_destination(char destination[])
{
	int count = 0;
	for (int i = 0; i < plane_num; i++)
	{
		if (strcmp(destination, plane_list[i].destination) == 0)
		{
			count++;
			printf("��==============================================================================��\n\n");
			printf("  %-22s%-22s%-22s%-22s\n", "�����", "�ɻ��ͺ�", "����������", "Ŀ�ĵ�����");
			printf("   %-22s%-22s%-22s%-22s\n\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination);
			printf("  %-22s%-22s%-22s%-22s\n", "���ʱ��", "����ʱ��", "�۸�", "ʣ��Ʊ��");
			printf("   %-22s%-22s%-22d%-22d\n\n", plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
		}
	}
	if (count == 0)
	{	
		printf("���ҽ��Ϊ��\n");
	}
	printf("==============================================================================\n");
}


