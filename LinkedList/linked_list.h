/**
 * @file linked_list.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include "profile_dic.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
typedef struct LinkedList LinkedList_t;

struct LinkedList
{
	LinkedList_t * p_next;
	parameter_desc_t pd;
};
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
 * @brief Initializes the linked list by setting the address pointer to NULL.
 *
 * @param p_addr A pointer to the linked list's starting address pointer.
 */
void LinkedList_Create(LinkedList_t ** p_Addr);

/**
 * @brief Appends a new node to the end of the linked list.
 *
 * @param p_addr A pointer to the pointer of the starting address of the linked list.
 * @param index The index for retrieving profile data to store in the new node.
 */
void LinkedList_Append(LinkedList_t ** p_addr, uint16_t index);

/**
 * @brief Inputs data into the specified node by index, using the node's type to handle casting.
 *
 * @param p_addr A pointer to the starting node of the linked list.
 * @param index The index of the target node to receive the data.
 * @param data A pointer to the data to be stored in the node.
 */
void LinkedList_InputData(LinkedList_t * p_addr, uint16_t index, void * data);

/**
 * @brief Prints all nodes in the linked list along with their index and data.
 *
 * @param p_addr A pointer to the starting node of the linked list.
 */
void LinkedList_Print(LinkedList_t * p_addr);

/**
 * @brief Deletes a node at a specified index from the linked list.
 *
 * @param p_addr A pointer to the pointer of the starting address of the linked list.
 * @param index The index of the node to delete.
 */
void LinkedList_Delete(LinkedList_t** p_addr, uint16_t index);

/**
 * @brief Deletes all nodes in the linked list and frees their allocated memory.
 *
 * @param p_addr A pointer to the pointer of the starting address of the linked list.
 */
void LinkedList_AllDelete(LinkedList_t** p_addr);

/**
 * @brief Inserts a new node at a specific index in the linked list.
 *
 * @param p_addr A pointer to the pointer of the starting address of the linked list.
 * @param index The index for the new node.
 */
void LinkedList_Insert(LinkedList_t ** p_addr, uint16_t index);

/**
 * @brief Searches for a node at a specific index in the linked list.
 *
 * @param p_addr A pointer to the starting node of the linked list.
 * @param index The index of the node to search for.
 *
 * @return A pointer to the found node, or NULL if not found.
 */
LinkedList_t * LinkedList_Search(LinkedList_t * p_addr, uint16_t index);

/**
 * @brief Destroys the entire linked list and frees all associated memory.
 *
 * @param p_addr A pointer to the pointer of the starting address of the linked list.
 */
void LinkedList_DesTroy(LinkedList_t ** p_addr);


#endif // LINKED_LIST_H