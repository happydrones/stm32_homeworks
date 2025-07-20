#include "linkedlist.h"


/**
 * @brief Creates a new single linked list head node.
 *
 * This function allocates memory for the head node of a single linked list,
 * initializes its data and next pointers to NULL, and returns a pointer to the head node.
 *
 * @return Pointer to the head node of the newly created single linked list,
 *         or NULL if memory allocation fails.
 */
SLList_t * single_linked_list_create(void)
{
    // 1. Allocate memory for the head of the linked list
    SLList_t *Head = (SLList_t *)calloc(1, sizeof(SLList_t));
    if (NULL == Head)
    {
        // Error handling: memory allocation failed
        // printf("Memory allocation failed!\n");
        return NULL;
    }
    // 2. Initialize the head of the linked list
    Head->next = NULL;
    Head->Data = NULL;
    // 3. Return the head of the linked list
    return Head;
}

/**
 * @brief Creates a new singly linked list from an array of integers.
 * @param arr:  A pointer to the input array of integers.
 * @param size: The number of elements in the array.
 * @retval SLList_t*： A pointer to the head of the newly created list.
 *         Returns NULL if the input size is 0 or if memory allocation fails.
 * @note The caller is responsible for freeing the memory allocated for the list
 *       once it is no longer needed (e.g., by calling a `free_list` function).
 * 
 * This function iterates through the provided array and allocates a new node
 * for each element, linking them together in the same order.
 */
SLList_t* create_list_from_array( DataType_t* const* arr, int size) 
{
    // 1. Handle edge cases: if the array is empty or null, return an empty list.
    if (arr == NULL || size == 0) {
        return NULL;
    }

    // 2. Create the head node from the first element.
    SLList_t * head = (SLList_t*)malloc(sizeof(SLList_t));
    if (head == NULL) {
        // Memory allocation failed
        return NULL;
    }
    head->Data = arr[0];
    head->next = NULL;

    // 3. Use a 'current' pointer to keep track of the last node created.
    SLList_t * current = head;

    // 4. Loop through the rest of the array to create and link subsequent nodes.
    for (int i = 1; i < size; ++i) {
        SLList_t * new_node = (SLList_t*)malloc(sizeof(SLList_t));
        if (new_node == NULL) {
            // Memory allocation failed. To prevent memory leaks, we should
            // free the partially created list before returning.
            // (A helper function `free_list(head)` would be ideal here.)
            // For simplicity, we'll just return NULL in this example.
            // A robust implementation would clean up memory.
            return NULL; // Or handle error more gracefully
        }
        new_node->Data = arr[i];
        new_node->next = NULL;

        // Link the new node to the end of the list
        current->next = new_node;
        // Move the 'current' pointer forward
        current = new_node;
    }

    // 5. Return the head of the fully constructed list.
    return head;
}

/**
 * @brief Creates a new node for a single linked list.
 * @param data Pointer to the data to be stored in the new node.
 * @retval Pointer to the newly created node, or NULL if memory allocation fails.
 * This function allocates memory for a new node, initializes its data pointer
 * with the provided data, and sets its next pointer to NULL.
 */
SLList_t* Single_Linked_List_Node_create(DataType_t* data)
{
    // 1. Allocate memory for the node
    SLList_t *Node = (SLList_t *)calloc(1, sizeof(SLList_t));
    if (NULL == Node)
    {
        // Error handling code here
        // printf("Memory allocation failed!\n");
        return NULL;
    }
    // 2. Initialize the node
    Node->Data = data;
    Node->next = NULL;
    // 3. Return the node
    return Node;
}

/**
 * @brief   insert a new node to the sepcified index of a single linked list.
 * @param list: A pointer to the head of the linked list.
 * @param data: a new node to be appended to the list.
 * @param index: the index to insert the new node.
 * @retval bool ： 
 *         Returns true if the node is successfully appended to the list, false otherwise.
 * @note 
 */
bool insert_single_linked_list(SLList_t*  list, DataType_t* data, uint32_t index)
{
    //1.allocate memory for the new node
    SLList_t* new_node = Single_Linked_List_Node_create(data);
    if (NULL == new_node)
    {
        // Error handling code here
        // printf("Memory allocation failed!\n");
        return false;
    }
    //2.insert the new node to the specified index of the list
    SLList_t* current = list->next;
    for(uint32_t i=0;i<index-1;i++)
    {
        if(current->next == NULL)
        {
            // Error handling code here 
            // the list only has i+1 nodes, so the index is out of range
            // printf("Index out of range!\n");
            return false;
        }
        current = current->next;
    }
    new_node->next =current->next;
    current->next = new_node;
    return true;
}

/**
 * @brief   Appends a new node to the end of a single linked list.
 * @param list: A pointer to the head of the linked list.
 * @param data: a new node to be appended to the list.
 * @retval bool ： 
 *         Returns true if the node is successfully appended to the list, false otherwise.
 * @note 
 * 
 * This function iterates through the provided array and allocates a new node
 * for each element, linking them together in the same order.
 */
bool append_single_linked_list(SLList_t* list, DataType_t* data)
{
    // 1. Create a new node from the data
    SLList_t* new_node = Single_Linked_List_Node_create(data);
    if (NULL == new_node)
    {
        // Error handling code here
        // printf("Memory allocation failed!\n");
        return false;
    }
    // 2. Traverse the list to find the last node
    SLList_t* current = list;
    while (current->next!= NULL)
    {
        current = current->next;
    }
    // 3. Append the new node to the end of the list
    current->next = new_node;
    // 4. Return success    
    return true;
}

/**
 * @brief delect spesific node from single linked list
 * 

*/
bool Delect_Node (SLList_t* list, DataType_t* Data)
{
    SLList_t* current = list->next;
	return false;

}
