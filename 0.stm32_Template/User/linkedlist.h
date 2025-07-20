/**
 *******************************************************************************
 * @file    LinkedList.h
 * @author  Oscar
 * @version V1.0.0  
 * @date    2025-07-08
 * @brief   This file provides a linked list implementation for stm32f10x devices
 *          supporting microseconds(us),10 microseconds(10us), milliseconds(ms),
 *          and seconds(s).
 ******************************************************************************
 * @note    The file contains two kinds of linked list implementations:
 *          1. Single-linked list
 *          2. Double-linked list
 * @attention 
 *         
 *         
 *            
 *<h2><center>&copy; COPYRIGHT 2025 Oscar happydrones123@gmail.com </center></h2>
 *******************************************************************************
 */


#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* Define --------------------------------------------------------------------*/
#define MAX_NODE_NUM 1000000 // Maximum number of nodes in the linked list

/* Typedef -------------------------------------------------------------------*/
#define MAX_NODE_NUM 1000000
typedef int DataType_t;

/* Structures ----------------------------------------------------------------*/

/**
 * @struct Node
 * @brief Represents a single node in a singly linked list.
 * Each node contains an DataType_t data payload and a pointer to the
 * next node in the sequence.
 */
typedef struct _SINGLE_LINKED_LIST
{
	DataType_t* Data;
    struct _SINGLE_LINKED_LIST* next;

}SLList_t;

typedef struct _DOUBLE_LINKED_LIST
{
    DataType_t* Data;
    struct DLList_t* head;
    struct DLList_t* tail;

}DLList_t;

/* Function prototypes -------------------------------------------------------*/
SLList_t* single_linked_list_create(void);
void init_double_linked_list(DLList_t* list);
SLList_t* Single_Linked_List_Node_create(DataType_t* data);

bool append_single_linked_list(SLList_t* list, DataType_t* data);
void append_double_linked_list(DLList_t* list, DataType_t* data);

bool insert_single_linked_list(SLList_t*  list, DataType_t* data, uint32_t index);
void insert_double_linked_list(DLList_t* list, DataType_t* data, uint32_t index);

void remove_single_linked_list(SLList_t* list, uint32_t index);
void remove_double_linked_list(DLList_t* list, uint32_t index);

DataType_t* get_single_linked_list(SLList_t* list, uint32_t index);
DataType_t* get_double_linked_list(DLList_t* list, uint32_t index);

uint32_t get_single_linked_list_size(SLList_t* list);
uint32_t get_double_linked_list_size(DLList_t* list);

void clear_single_linked_list(SLList_t* list);
void clear_double_linked_list(DLList_t* list);     

/* End of file -*/  
#endif /* __LINKEDLIST_H__ */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
