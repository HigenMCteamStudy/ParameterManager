/**
 * @file ParameterTest.cpp
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
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
#include "iostream"
#include "CppUTest/TestHarness.h"

extern "C"
{
	#include "linked_list.h"
	#include "profile_dic.h"
}
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
TEST_GROUP(ParameterManager)
{
	LinkedList_t * p_addr;
	void setup()
	{
		LinkedList_Create(&p_addr);
	}
	void teardown()
	{
		LinkedList_DesTroy(&p_addr);
	}
	void Count_nodeNum(LinkedList_t * p_addr, int nodeNum)
	{
		LinkedList_t * p_last = p_addr;
		int count = 0;

		while(NULL != p_last) {
			count++;
			p_last = p_last->p_next;
		}

		LONGS_EQUAL(nodeNum, count);
	}
	void compare_target(LinkedList_t * p_target)
	{
		parameter_desc_t * p_pd;
		if(NULL == p_target) {
			std::cout << "Not exist pointer" << std::endl;
			return;
		}
		p_pd = binarySearch(param_dic, 1, PARAMETER_MAX_NUMBER, p_target->pd.md_index);
		switch (p_target->pd.type)
		{
		case P_TYPE_INT32_T:
			LONGS_EQUAL(*(int32_t *)p_pd->p_data, *(int32_t *)p_target->pd.p_data);
			break;
		case P_TYPE_UINT32_T:
			LONGS_EQUAL(*(uint32_t *)p_pd->p_data, *(uint32_t *)p_target->pd.p_data);
			break;
		case P_TYPE_INT16_T:
			LONGS_EQUAL(*(int16_t *)p_pd->p_data, *(int16_t *)p_target->pd.p_data);
			break;
		case P_TYPE_UINT16_T:
			LONGS_EQUAL(*(uint16_t *)p_pd->p_data, *(uint16_t *)p_target->pd.p_data);
			break;
		case P_TYPE_INT8_T:
			LONGS_EQUAL(*(int8_t *)p_pd->p_data, *(int8_t *)p_target->pd.p_data);
			break;
		case P_TYPE_UINT8_T:
			LONGS_EQUAL(*(uint8_t *)p_pd->p_data, *(uint8_t *)p_target->pd.p_data);
			break;
		default:
			break;
		}

	}
};
/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
TEST(ParameterManager, CreatePM)
{
	// POINTERS_EQUAL(NULL, p_addr);
}
TEST(ParameterManager, AddPM)
{
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0000);
	Count_nodeNum(p_addr, 3);
}
TEST(ParameterManager, PrintPM)
{
	uint16_t data = 1;
	//테스트 케이스 1.1
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0001);
	LinkedList_Append(&p_addr, 0x0002);
	LinkedList_Append(&p_addr, 0x0003);
	// Invalid index number
	LinkedList_Append(&p_addr, 0x0009);
	LinkedList_InputData(p_addr, 0x0000, (void *)&data);
	data++;
	LinkedList_InputData(p_addr, 0x0001, (void *)&data);
	data++;
	LinkedList_InputData(p_addr, 0x0002, (void *)&data);
	data++;
	LinkedList_InputData(p_addr, 0x0003, (void *)&data);
	//테스트 케이스 1.2
	// LinkedList_Print(p_addr);
	Count_nodeNum(p_addr, 4);
}
TEST(ParameterManager, DeletePM)
{
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0001);
	LinkedList_Append(&p_addr, 0x0002);
	LinkedList_Append(&p_addr, 0x0003);
	//테스트 케이스 1.3
	LinkedList_Delete(&p_addr, 0x0003);
	//테스트 케이스 1.4
	LinkedList_Delete(&p_addr, 0x0005);
	LinkedList_Print(p_addr);
	Count_nodeNum(p_addr, 3);
}

TEST(ParameterManager, InsertingObjects)
{
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0003);
	//테스트 케이스 2.1
	LinkedList_Insert(&p_addr, 0x0002);
	//테스트 케이스 2.2
	LinkedList_Insert(&p_addr, 0x0004);
	// LinkedList_Print(p_addr);
	Count_nodeNum(p_addr, 4);
}

TEST(ParameterManager, SearchObject)
{
	LinkedList_t * p_target;
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0003);
	LinkedList_Insert(&p_addr, 0x0002);
	LinkedList_Insert(&p_addr, 0x0004);
	//테스트 케이스 3.1
	p_target = LinkedList_Search(p_addr, 0x0003);
	compare_target(p_target);
	//테스트 케이스 3.2
	p_target = LinkedList_Search(p_addr, 0x0005);
	POINTERS_EQUAL(NULL, p_target);
	p_target = LinkedList_Search(p_addr, 0x0001);
	POINTERS_EQUAL(NULL, p_target);
	Count_nodeNum(p_addr, 4);
}
TEST(ParameterManager, DeleteAllObject)
{
	//테스트 4.2
	LinkedList_AllDelete(&p_addr);
	LinkedList_Append(&p_addr, 0x0000);
	LinkedList_Append(&p_addr, 0x0003);
	LinkedList_Insert(&p_addr, 0x0002);
	LinkedList_Insert(&p_addr, 0x0004);
	//테스트 4.1
	LinkedList_AllDelete(&p_addr);
	Count_nodeNum(p_addr, 0);
}