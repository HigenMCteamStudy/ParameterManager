/**
 * @file main.c
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief There is an explanation in the 'document'
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdio.h>

#include "linked_list.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    Macro
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    variables(external)
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
static int Count_nodeNum(LinkedList_t * p_addr);

int main(void)
{
	LinkedList_t * p_addr;
	LinkedList_t * p_target;
	uint16_t data = 1234;
	int count;
	//p_addr 포인터를 NULL로 초기화
	LinkedList_Create(&p_addr);

	//Stage 1
	//객체가 하나도 만들어 지지 않았을 때 삭제/전체 삭제를 하여도 아무 반응이 없어야 함
	LinkedList_Delete(&p_addr, 0x0000);
	LinkedList_AllDelete(&p_addr);

	//index를 가진 객체 생성
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0004);

	//index를 가진 객체 생성 및 index를 보고 정렬되게 삽입
	LinkedList_Insert(&p_addr, 0x0002);
	LinkedList_Insert(&p_addr, 0x0001);
	LinkedList_Append(&p_addr, 0x0300);
	LinkedList_Append(&p_addr, 0x0301);
	//객체 개수 리턴
	count = Count_nodeNum(p_addr);
	//객체 개수 출력
	printf("Stage 1-1. As of now, the number of nodes is %d.\n", count);
	printf("-----------------------------------------\n");

	//Stage 2
	//객체 제거(활성화된 index가 아닐 시 무시)
	LinkedList_Delete(&p_addr, 0x0100);
	LinkedList_Delete(&p_addr, 0x0000);
	LinkedList_Delete(&p_addr, 0x0004);
	LinkedList_Delete(&p_addr, 0x0301);

	count = Count_nodeNum(p_addr);
	printf("Stage 2-1. As of now, the number of nodes is %d.\n", count);
	//생성된 객체들 데이터 출력
	LinkedList_Print(p_addr);
	printf("-----------------------------------------\n");

	//Stage 3
	//index를 가지고 객체 검색
	p_target = LinkedList_Search(p_addr, 0x0300);
	//검색된 객체 데이터 출력
	printf("Stage 3-1. Target data min value : %d\n", p_target->pd.min);
	printf("Stage 3-2. Target data max value : %d\n", p_target->pd.max);
	printf("Stage 3-3. Target data : %d\n", *(uint16_t*)p_target->pd.p_data);
	printf("-----------------------------------------\n");

	//Stage 4
	//작성된 index를 가진 객체 데이터 입력/수정
	LinkedList_InputData(p_addr, 0x0300, (void*)&data);
	printf("Stage 4-1. Target data min value : %d\n", p_target->pd.min);
	printf("Stage 4-2. Target data max value : %d\n", p_target->pd.max);
	printf("Stage 4-3. Target data : %d\n", *(uint16_t*)p_target->pd.p_data);
	printf("-----------------------------------------\n");

	//Stage 5
	//모든 객체 삭제 후 개수 출력
	LinkedList_AllDelete(&p_addr);
	count = Count_nodeNum(p_addr);
	printf("Stage 5-1. As of now, the number of nodes is %d.\n", count);
	//객체 추가 후 개수 출력
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0004);
	count = Count_nodeNum(p_addr);
	printf("Stage 5-2. As of now, the number of nodes is %d.\n", count);
	printf("-----------------------------------------\n");

	//Stage 6
	//객체 제거(AllDelete와 동일)
	LinkedList_DesTroy(&p_addr);
	count = Count_nodeNum(p_addr);
	printf("Stage 6-1. As of now, the number of nodes is %d.\n", count);
	return 0;
}
static int Count_nodeNum(LinkedList_t * p_addr)
{
	LinkedList_t * p_last = p_addr;
	int count = 0;

	while(NULL != p_last) {
		count++;
		p_last = p_last->p_next;
	}

	return count;
}
