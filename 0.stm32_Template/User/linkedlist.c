



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
SLList_t * Single_Linked_List_create(void)
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
ErrorStatus Single_Linked_List_append(SLList_t* list, DataType_t* data)
{
    // 1. Create a new node from the data
    SLList_t* new_node = Single_Linked_List_Node_create(data);
    if (NULL == new_node)
    {
        // Error handling code here
        // printf("Memory allocation failed!\n");
        return ERROR;
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
    return SUCCESS;
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
ErrorStatus Single_Linked_List_insert(SLList_t*  list, DataType_t* data, uint32_t index)
{
    //1.allocate memory for the new node
    SLList_t* new_node = Single_Linked_List_Node_create(data);
    if (NULL == new_node)
    {
        // Error handling code here
        // printf("Memory allocation failed!\n");
        return ERROR;
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
            return ERROR;
        }
        current = current->next;
    }
    new_node->next =current->next;
    current->next = new_node;
    return SUCCESS;
}



/**
 * @brief remove a specific node from single linked list
 * @param list: A pointer to the head of the linked list.
 * @param Data: the data of the node to be removed.

*/
ErrorStatus Single_Linked_List_remove (SLList_t* list, DataType_t* node_value)
{
    SLList_t* current = list;
    while((current->next!= NULL)&&(current->next->Data!= node_value))
    {
        current = current->next;

    }
    if (current->next == NULL)  
    {
        // Error handling code here
        // the node to be removed is not in the list
        // printf("Node not found!\n");
        return ERROR;
    }
    SLList_t* to_delete = current->next;
    current->next = to_delete->next;
    free(to_delete);
    return SUCCESS;
}



/**
 * @brief Creates an empty circular singly linked list.
 * 
 * @return Pointer to the head node of the new list (NULL if empty).
 */
SLList_t* csll_create(void);

/**
 * @brief Appends a node with given data to the circular singly linked list.
 * 
 * @param head Pointer to the head node of the list.
 * @param data Data to store in the new node.
 * @return Pointer to the (possibly new) head node of the list.
 */
SLList_t* csll_append(SLList_t* head, int data);

/**
 * @brief Inserts a new node after a given target node in the circular singly linked list.
 * 
 * @param head Pointer to the head node of the list.
 * @param target Pointer to the node after which the new node will be inserted.
 * @param data Data to store in the new node.
 * @return Pointer to the (possibly new) head node of the list.
 */
SLList_t* csll_insert_after(SLList_t* head, SLList_t* target, int data);

/**
 * @brief Removes the first node that contains the specified data from the circular singly linked list.
 * 
 * @param head Pointer to the head node of the list.
 * @param data Data value of the node to be removed.
 * @return Pointer to the (possibly new) head node of the list.
 */
SLList_t* csll_remove(SLList_t* head, int data);

/**
 * @brief Destroys the circular singly linked list and frees all allocated memory.
 * 
 * @param head Pointer to the head node of the list.
 */
void csll_destroy(SLList_t* head);


DLList_t* Double_linked_list_create(void)
{
    // 1. Allocate memory for the head of the double linked list
    DLList_t *Head = (DLList_t *)calloc(1, sizeof(DLList_t));
    if (NULL == Head)
    {
        // Error handling: memory allocation failed
        // printf("Memory allocation failed!\n");
        return NULL;
    }
    // 2. Initialize the head of the linked list
    Head->Data = NULL;
    Head->next = NULL;
    Head->prev = NULL;
    // 3. Return the head of the linked list
    return Head;
}

/**
 * @brief Creates a new node for a Double linked list.
 * @param data Pointer to the data to be stored in the new node.
 * @retval Pointer to the newly created node, or NULL if memory allocation fails.
 */
DLList_t*   Double_Linked_List_Node_create(DataType_t* data)
{
    // 1. Allocate memory for the Double Linked List Node
    DLList_t* Node = (DLList_t*)calloc(1, sizeof(DLList_t));
    if (NULL == Node)
    {
        // Error handling code here
        // printf("Memory allocation failed!\n");
        return NULL;
    }
    // 2. Initialize the Double Linked List Node
    Node->Data = data;
    Node->next = NULL;
    Node->prev = NULL;
    // 3. Return the Double Linked List Node
    return Node;
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
DLList_t*   Double_Linked_List_create_from_array( DataType_t* const* arr, int size)
{
    // 1. Handle edge cases: if the array is empty or null, return an empty list.
    if (arr == NULL || size == 0) {
        return NULL;
    }

    // 2. Create the head node from the first element.
    DLList_t * head = (DLList_t*)malloc(sizeof(DLList_t));
    if (NULL == head) {
        // Memory allocation failed
        return NULL;
    }
    // 3. Initialize the head node
    head->Data = NULL;
    head->next = NULL;
    head->prev = NULL;

    DLList_t * current = head;

    // 4. Loop through the rest of the array to create and link subsequent nodes.
    for (int i = 0; i < size; ++i) {
        DLList_t * new_node = (DLList_t*)malloc(sizeof(DLList_t));
        if (NULL == new_node) {
            // Memory allocation failed. To prevent memory leaks, we should
            // free the partially created list before returning.
            // (A helper function `free_list(head)` would be ideal here.)
            // For simplicity, we'll just return NULL in this example.
            // A robust implementation would clean up memory.
            return NULL; // Or handle error more gracefully
        }
        new_node->Data = arr[i];
        new_node->next = NULL;
        new_node->prev = current;

        // Link the new node to the end of the list
        current->next = new_node;
        // Move the 'current' pointer forward
        current = new_node;
    }

    // 5. Return the head of the fully constructed list.
    return head;
}
ErrorStatus Double_Linked_list_append(DLList_t* Dllist, DataType_t* data)
{
    // 1. Create a new node from the data
    DLList_t* appended_node = Double_Linked_List_Node_create(data);
    if (NULL == appended_node)
    {
        // Error handling code here
        // printf("Memory allocation failed!\n");
        return ERROR;
    }
    // 2. Traverse the list to find the last node
    DLList_t* current = Dllist;
    while (current->next != NULL)
    {
        current = current->next;
    }
    // 3. Append the new node to the end of the list
    current->next = appended_node;
    appended_node->prev = current;
    // 4. Return success
    return SUCCESS;

}

/**
 * @brief   insert a new node after the specified index of a single linked list.
 * @param list: A pointer to the head of the linked list.
 * @param data: a new node to be appended to the list.
 * @param index: the index to insert the new node.
 * @retval ErrorStatus: SUCCESS if insertion successful, ERROR otherwise.
 * @note    Index mapping:
 *                     index=0   index=1    index=2
 *         哨兵节点 ---> 节点1 ---> 节点2 ---> 节点3
 *         NULL        arr[0]     arr[1]     arr[2]
 *         prev=NULL  prev=哨兵   prev=节点1  prev=节点2
 *         next=节点1 next=节点2 next=节点3  next=NULL
 */
ErrorStatus Double_Linked_list_insert(DLList_t* Dllist, DataType_t* data, uint32_t index)
{
    //1.allocate memory for the new node
    DLList_t* new_node = Double_Linked_List_Node_create(data);
    if (NULL == new_node)
    {
        // Error handling code here
        // printf("Memory allocation failed!\n");
        return ERROR;
    }
    // 2. Check if the double linked list is empty
    if(Dllist->next == NULL)
    {
        // Error handling code here
        // the double linked list is empty, so the index is out of range
        return ERROR;
    }
    // 3.travse to the specified index of the list 
    DLList_t* current = Dllist->next;
    for(uint32_t i=0;i<index;i++)
    {
        if(current->next == NULL)
        {
            // Error handling code here 
            // the list only has i+1 nodes, so the index is out of range
            // printf("Index out of range!\n");
            return ERROR;
        }
        current = current->next;
    }
    //4.Insert the new node after the specified index
    new_node->next =current->next;
    new_node->prev = current;
    current->next = new_node;
    // 5. Update the next node's prev pointer if it exists
    if(new_node->next!= NULL)
    {
        new_node->next->prev = new_node;
    }
    return SUCCESS;

}

/**
 * @brief   Remove a node at the specified index from double linked list.
 * @param   Dllist: A pointer to the head of the linked list.
 * @param   index: The index of the node to be removed.
 * @retval  ErrorStatus: SUCCESS if removal successful, ERROR otherwise.
 * @note    Index mapping:
 * @note              index=0   index=1    index=2
 *         哨兵节点 ---> 节点1 ---> 节点2 ---> 节点3
 *         NULL        arr[0]     arr[1]     arr[2]
 *         prev=NULL  prev=哨兵   prev=节点1  prev=节点2
 *         next=节点1 next=节点2 next=节点3  next=NULL
 */
ErrorStatus Double_Linked_List_remove(DLList_t* Dllist, int32_t index)
{
    if(Dllist->next == NULL)
    {
        // Error handling code here
        // the double linked list is empty, so the index is out of range
        return ERROR;
    }
    // 3.travse to the specified index of the list and then Insert the new node after the specified index
    DLList_t* current = Dllist->next;
    for(int32_t i=0;i<index;i++)
    {
        if(current->next == NULL)
        {
            // Error handling code here 
            // the list only has i+1 nodes, so the index is out of range
            // printf("Index out of range!\n");
            return ERROR;
        }
        current = current->next;
    }
    //4.remove the specified node
    current->prev->next = current->next;
    if(current->next != NULL)
    {
        current->next->prev = current->prev;
    }
    free(current);
    return SUCCESS;
}
