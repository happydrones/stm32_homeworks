#include "seqlist.h"

/**
 * @brief Creates a sequential list
 * @param size The size of the list
 * @return Pointer to the created list
 */
SEQLIST_HandleTypeDef* SEQLIST_Create(uint16_t size) 
{
    SEQLIST_HandleTypeDef* manager = (SEQLIST_HandleTypeDef*)malloc(sizeof(SEQLIST_HandleTypeDef));
    if ( NULL == manager) 
    {
        return NULL;
    }
    manager->items = (SEQLIST_ItemTypeDef*)malloc(sizeof(SEQLIST_ItemTypeDef) * size);
    if (NULL == manager->items)
    {
        free(manager);
        return NULL;
    }
    manager->length = size;
    return manager;
}




/**
 * @brief Traverses the sequential list and applies the visit function to each element.
 * @param list Pointer to the sequential list
 * @param visit Function pointer to process each element
 */
void SEQLIST_Traverse(const SEQLIST_HandleTypeDef* list, void (*visit)(SEQLIST_ItemTypeDef* item)) {
    for (uint16_t i = 0; i < list->length; ++i) {
        visit(&list->items[i]);
    }
}

/**
 * a test function to test the seqlist
 */
uint32_t test_seqlist(uint32_t* L, uint32_t t, uint16_t length)
{
    uint32_t index;
    int32_t temp1= -1;
    uint32_t temp2;
    uint32_t e;
    for (uint16_t i = 0; i < length; i++)
    {
        if(t <L[i])
        {
            temp1 = L[i];
            e = temp1;
            index = i;
            L[i] = t;
            break;
        }
        if((i == length-1)&&(temp1 == -1))
        {
            L[length]=t;
            return UINT32_MAX;
        }
           
    }

    index += 1;
    for (uint16_t i = index; i < length; i++)
    {
        temp2 = L[i];
        L[i] = temp1;
        temp1 = temp2;
    }
    return e;
}
