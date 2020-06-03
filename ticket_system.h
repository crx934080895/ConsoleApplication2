#include <stdio.h>
#include "read_data_from_library.h"
#pragma once

//用结构体数组储存飞机信息
//user_plane[100]已在"read_data_from_library.h"定义

//至少设置6个城市，用邻接矩阵表示两城市之间的距离

//显示所有航班信息
void print_planes()
{
	for (int i = 0; i < plane_num; i++)
	{
		printf("☆==============================================================================☆\n\n");
		printf("%d  %-22s%-22s%-22s%-22s\n", i + 1, "航班号", "飞机型号", "出发地名称", "目的地名称");
		printf("   %-22s%-22s%-22s%-22s\n\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination);
		printf("%d  %-22s%-22s%-22s%-22s\n", i + 1, "起飞时间", "降落时间", "价格", "剩余票量");
		printf("   %-22s%-22s%-22d%-22d\n\n", plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
	}
}

//通过航班号查询某架航班的信息
void query_plane_by_num(char plane_id[])
{
	int count = 0;
	for (int i = 0; i < plane_num; i++)
	{
		if (strcmp(plane_id, plane_list[i].num) == 0)
		{
			printf("\t\t\t☆==============================================================================☆\n\n");
			printf("\t\t\t  %-22s%-22s%-22s%-22s\n", "航班号", "飞机型号", "出发地名称", "目的地名称");
			printf("\t\t\t   %-22s%-22s%-22s%-22s\n\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination);
			printf("\t\t\t  %-22s%-22s%-22s%-22s\n", "起飞时间", "降落时间", "价格", "剩余票量");
			printf("\t\t\t   %-22s%-22s%-22d%-22d\n\n", plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
		}
	}
	if (count == 0)
	{
		printf("查找结果为空\n");
	}
	printf("#===================================================#\n");
}

//查起点为XX城市的航班
void query_plane_by_starting_point(char start_point[])
{
	int count = 0;
	for (int i = 0; i < plane_num; i++)
	{
		if (strcmp(start_point,plane_list[i].starting_point)==0)
		{
			count++;
			printf("☆==============================================================================☆\n\n");
			printf("  %-22s%-22s%-22s%-22s\n", "航班号", "飞机型号", "出发地名称", "目的地名称");
			printf("   %-22s%-22s%-22s%-22s\n\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination);
			printf("  %-22s%-22s%-22s%-22s\n", "起飞时间", "降落时间", "价格", "剩余票量");
			printf("   %-22s%-22s%-22d%-22d\n\n", plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
		}
	}
	if (count ==0)
	{
		printf("查找结果为空\n");
	}
	printf("==============================================================================\n");
}

//查终点为XX城市的航班
void query_plane_destination(char destination[])
{
	int count = 0;
	for (int i = 0; i < plane_num; i++)
	{
		if (strcmp(destination, plane_list[i].destination) == 0)
		{
			count++;
			printf("☆==============================================================================☆\n\n");
			printf("  %-22s%-22s%-22s%-22s\n", "航班号", "飞机型号", "出发地名称", "目的地名称");
			printf("   %-22s%-22s%-22s%-22s\n\n", plane_list[i].num, plane_list[i].model, plane_list[i].starting_point, plane_list[i].destination);
			printf("  %-22s%-22s%-22s%-22s\n", "起飞时间", "降落时间", "价格", "剩余票量");
			printf("   %-22s%-22s%-22d%-22d\n\n", plane_list[i].start_time, plane_list[i].end_time, plane_list[i].price, plane_list[i].count);
		}
	}
	if (count == 0)
	{	
		printf("查找结果为空\n");
	}
	printf("==============================================================================\n");
}


