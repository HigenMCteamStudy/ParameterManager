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
	// TODO : Initialize Linked List Start pointer
}

void LinkedList_Append(LinkedList_t ** p_addr, uint16_t index)
{
	// TODO : Append Linked List Object
}

void LinkedList_InputData(LinkedList_t * p_addr, uint16_t index, void * data)
{
	// TODO : Input data to Linked List Object
}

void LinkedList_Print(LinkedList_t * p_addr)
{
	// TODO : Print data of Linked List Objects
}

void LinkedList_Delete(LinkedList_t** p_addr, uint16_t index)
{
	// TODO : Delete Linked List Object with index
}

void LinkedList_AllDelete(LinkedList_t** p_addr)
{
	// TODO : Delete All Linked List Objects
}

void LinkedList_Insert(LinkedList_t ** p_addr, uint16_t index)
{
	// TODO : Insert Linked List Object with index
}

LinkedList_t * LinkedList_Search(LinkedList_t * p_addr, uint16_t index)
{
	// TODO : Search Linked List Object with index
}

void LinkedList_DesTroy(LinkedList_t ** p_addr)
{
	// TODO : De-Initialize Linked List Objects
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