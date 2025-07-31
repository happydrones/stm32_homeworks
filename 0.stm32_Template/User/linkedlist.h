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

/* Define --------------------------------------------------------------------*/
#define MAX_NODE_NUM 1000000 // Maximum number of nodes in the linked list

/* Typedef -------------------------------------------------------------------*/
#define MAX_NODE_NUM 1000000
typedef int DataType_t;

/* Structures ----------------------------------------------------------------*/



/** 
  * @brief  Single linked list node structure definition
  */
typedef struct _SINGLE_LINKED_LIST
{
	DataType_t* Data;
    struct _SINGLE_LINKED_LIST* next;

}SLList_t;
/**
  * @}
  */    

/** 
  * @brief  Double linked list node structure definition
  */
typedef struct _DOUBLE_LINKED_LIST
{
    DataType_t* Data;
    struct _DOUBLE_LINKED_LIST* prev;
    struct _DOUBLE_LINKED_LIST* next;

}DLList_t;
/**
  * @}
  */    

/** @defgroup Single_Linked_List_Exported_Functions
  * @{
  */
SLList_t*   Single_Linked_List_create(void);
SLList_t*   Single_Linked_List_Node_create(DataType_t* data);
SLList_t* create_list_from_array( DataType_t* const* arr, int size);
ErrorStatus Single_Linked_List_append(SLList_t* list, DataType_t* data);
ErrorStatus Single_Linked_List_insert(SLList_t*  list, DataType_t* data, uint32_t index);
ErrorStatus Single_Linked_List_remove (SLList_t* list, DataType_t* node_value);


DataType_t* get_single_linked_list(SLList_t* list, uint32_t index);
DataType_t* get_double_linked_list(DLList_t* list, uint32_t index);

uint32_t get_single_linked_list_size(SLList_t* list);
uint32_t get_double_linked_list_size(DLList_t* list);

void clear_single_linked_list(SLList_t* list);
void clear_double_linked_list(DLList_t* list);
/**
  * @}
  */     



/** @defgroup Double_Linked_List_Exported_Functions
  * @{
  */
DLList_t*   Double_linked_list_create(void);
DLList_t*   Double_Linked_List_Node_create(DataType_t* data);
DLList_t*   Double_Linked_List_create_from_array( DataType_t* const* arr, int size);
ErrorStatus Double_Linked_list_append(DLList_t* Dllist, DataType_t* data);
ErrorStatus Double_Linked_list_insert(DLList_t* Dllist, DataType_t* data, uint32_t index);
ErrorStatus Double_Linked_List_remove(DLList_t* Dllist, int32_t index);
/**
  * @}
  */

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
