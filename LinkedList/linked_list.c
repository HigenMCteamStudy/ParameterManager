/**
 * @file linked_list.c
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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "linked_list.h"
#include "parameter.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
#define LINKED_LIST_SUCCESS	(0)
#define LINKED_LIST_FAILURE	(-1)
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
/**
 * @brief Traverses the linked list to find a node with the specified index, updating the previous node pointer.
 *
 * @param p_addr The starting node of the linked list.
 * @param p_prev A pointer to the pointer of the previous node, to be updated during traversal.
 * @param index The index of the node to search for.
 *
 * @return A pointer to the found node, or NULL if not found.
 */
static LinkedList_t * IndexTraversalSearch(LinkedList_t * p_addr,
                                           LinkedList_t ** p_prev,
                                           uint16_t index);

/**
 * @brief Copies data from a profile dictionary to a new node in the linked list based on the index.
 *
 * @param p_new A pointer to the new node where data will be copied.
 * @param index The index for accessing data in the profile dictionary.
 *
 * @return Returns LINKED_LIST_SUCCESS on success or a LINKED_LIST_FAILURE if an error occurs.
 */
static int32_t CopyProfileDictionary(LinkedList_t * p_new, uint16_t index);

/**
 * @brief Outputs the data stored in the node based on its type.
 *
 * @param p_temp A pointer to the node containing data to output.
 */
static void OutputByType(LinkedList_t * p_temp);


void LinkedList_Create(LinkedList_t ** p_addr)
{
	*p_addr = NULL;
}

void LinkedList_Append(LinkedList_t ** p_addr, uint16_t index)
{
	LinkedList_t * p_new;
	LinkedList_t * p_last = *p_addr;

	p_new = (LinkedList_t *)malloc(sizeof(LinkedList_t));
	if(LINKED_LIST_FAILURE == CopyProfileDictionary(p_new, index)) {
		return;
	}

	if(NULL == *p_addr) {
		*p_addr = p_new;
		return;
	}

	while(NULL != p_last->p_next) {
		p_last = p_last->p_next;
	}

	p_last->p_next = p_new;
}

void LinkedList_InputData(LinkedList_t * p_addr, uint16_t index, void * data)
{
	LinkedList_t * p_last = p_addr;

	while((NULL != p_last) && (p_last->pd.md_index != index)) {
		p_last = p_last->p_next;
	}

	if(NULL == p_last) {
		printf("[LinkedList_InputData]No object with index value");
		return;
	}

	switch (p_last->pd.type)
	{
	case P_TYPE_INT32_T:
		*(int32_t *)p_last->pd.p_data = *(int32_t *)data;
		break;
	case P_TYPE_UINT32_T:
		*(uint32_t *)p_last->pd.p_data = *(uint32_t *)data;
		break;
	case P_TYPE_INT16_T:
		*(int16_t *)p_last->pd.p_data = *(int16_t *)data;
		break;
	case P_TYPE_UINT16_T:
		*(uint16_t *)p_last->pd.p_data = *(uint16_t *)data;
		break;
	case P_TYPE_INT8_T:
		*(int8_t *)p_last->pd.p_data = *(int8_t *)data;
		break;
	case P_TYPE_UINT8_T:
		*(uint8_t *)p_last->pd.p_data = *(uint8_t *)data;
		break;
	default:
		break;
	}
}

void LinkedList_Print(LinkedList_t * p_addr)
{
	LinkedList_t * p_last = p_addr;
	int count = 0;

    while (NULL != p_last) {
		printf("[LinkedList_Print]Node Number : %d\n",++count);
		printf("[LinkedList_Print]index : %d\n", p_last->pd.md_index);

		OutputByType(p_last);
		printf("*****************************************\n");

        p_last = p_last->p_next;
    }
    printf("[LinkedList_Print]finish\n");
}

void LinkedList_Delete(LinkedList_t** p_addr, uint16_t index) {
	LinkedList_t * p_prev;
	LinkedList_t * p_target;

	p_target = IndexTraversalSearch(*p_addr, &p_prev, index);

	if(NULL == p_target) {
		printf("[LinkedList_Delete]No object with index value\n");
		return;
	}

	if(*p_addr == p_target) {
		*p_addr = p_target->p_next;
	}
	else {
		p_prev->p_next = p_target->p_next;
	}
	free(p_target);
}

void LinkedList_AllDelete(LinkedList_t** p_addr) {
	LinkedList_t * p_temp;

	if(NULL == *p_addr) {
		printf("[LinkedList_AllDelete]Not exist object\n");
		return;
	}

	while(NULL != (*p_addr)) {
		p_temp = (*p_addr)->p_next;
		free((*p_addr));
		(*p_addr) = p_temp;
	}
}

void LinkedList_Insert(LinkedList_t ** p_addr, uint16_t index)
{
	LinkedList_t * p_temp = *p_addr;
	LinkedList_t * p_prev = *p_addr;;
	LinkedList_t * p_new;

	p_new = (LinkedList_t *)malloc(sizeof(LinkedList_t));

	if((NULL != p_temp) && (p_temp->pd.md_index > index)) {
		if(LINKED_LIST_FAILURE == CopyProfileDictionary(p_new, index)) {
			printf("[LinkedList_Insert]Invalid index number\n");
			return;
		}
		p_new->p_next = p_temp;
		*p_addr = p_new;
		return;
	}

	while((NULL != p_temp)) {
		if((p_prev->pd.md_index <= index) && (p_temp->pd.md_index > index)) {
			if(LINKED_LIST_FAILURE == CopyProfileDictionary(p_new, index)) {
				printf("[LinkedList_Insert]Invalid index number\n");
				return;
			}

			p_new->p_next = p_prev->p_next;
			p_prev->p_next = p_new;
			return;
		}

		p_prev = p_temp;
		p_temp = p_temp->p_next;
	}

	if((NULL == p_temp) && (p_prev->pd.md_index <= index)) {
		if(LINKED_LIST_FAILURE == CopyProfileDictionary(p_new, index)) {
			printf("[LinkedList_Insert]Invalid index number\n");
			return;
		}
		p_new->p_next = NULL;
		p_prev->p_next = p_new;
		p_temp = p_new;
		return;
	}

	if(NULL == p_temp->p_next) {
		printf("[LinkedList_Insert]No object with index value\n");
		return;
	}
}

LinkedList_t * LinkedList_Search(LinkedList_t * p_addr, uint16_t index)
{
	LinkedList_t * p_target;
	LinkedList_t * p_prev;

	p_target = IndexTraversalSearch(p_addr, &p_prev, index);

	if(NULL == p_target) {
		printf("[LinkedList_Search]No object with index value\n");
		return NULL;
	}

	return p_target;
}

void LinkedList_DesTroy(LinkedList_t ** p_addr)
{
	LinkedList_t * p_temp;

	if(NULL == *p_addr) {
		printf("[LinkedList_DesTroy]Not exist object\n");
		return;
	}

	while(NULL != (*p_addr)) {
		p_temp = (*p_addr)->p_next;
		free((*p_addr));
		(*p_addr) = p_temp;
	}
}

static LinkedList_t * IndexTraversalSearch(LinkedList_t * p_addr,
										   LinkedList_t ** p_prev,
										   uint16_t index)
{
	LinkedList_t * p_target = p_addr;

	while((NULL != p_target) && (p_target->pd.md_index != index)) {
		(*p_prev) = p_target;
		p_target = p_target->p_next;
	}

	return p_target;
}

static int32_t CopyProfileDictionary(LinkedList_t * p_new, uint16_t index)
{
	parameter_desc_t * p_pd;

	p_pd = binarySearch(param_dic, 1, PARAMETER_MAX_NUMBER, index);

	if(NULL == p_pd) {
		free(p_new);
		return LINKED_LIST_FAILURE;
	}

	memcpy(&(p_new->pd), p_pd, sizeof(parameter_desc_t));
	p_new->p_next = NULL;

	return LINKED_LIST_SUCCESS;
}

static void OutputByType(LinkedList_t * p_temp)
{
	switch (p_temp->pd.type)
	{
	case P_TYPE_INT32_T:
		printf("[LinkedList_Print]data : %d\n", *(int32_t *)(p_temp->pd.p_data));
		break;
	case P_TYPE_UINT32_T:
		printf("[LinkedList_Print]data : %d\n", *(uint32_t *)(p_temp->pd.p_data));
		break;
	case P_TYPE_INT16_T:
		printf("[LinkedList_Print]data : %d\n", *(int16_t *)(p_temp->pd.p_data));
		break;
	case P_TYPE_UINT16_T:
		printf("[LinkedList_Print]data : %d\n", *(uint16_t *)(p_temp->pd.p_data));
		break;
	case P_TYPE_INT8_T:
		printf("[LinkedList_Print]data : %d\n", *(int8_t *)(p_temp->pd.p_data));
		break;
	case P_TYPE_UINT8_T:
		printf("[LinkedList_Print]data : %d\n", *(uint8_t *)(p_temp->pd.p_data));
		break;
	default:
		break;
	}
}