/**
  ******************************************************************************
  * @file    seqlist.h
  * @author  Your Name
  * @version V1.0.0
  * @date    2024-05-01
  * @brief   Header file for sequential list (SeqList) implementation.
  ******************************************************************************
  * @attention
  *
  * This file is part of the STM32 project template.
  *
  ******************************************************************************
  */

#ifndef __SEQLIST_H
#define __SEQLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define SEQLIST_MAX_SIZE    ((uint16_t)100)

/**
  * @brief  SeqList item structure definition
  */
typedef struct
{
    uint8_t data;      /*!< Data value */
    uint16_t index;    /*!< Index in the list */
} SEQLIST_ItemTypeDef;

/**
  * @brief  SeqList structure definition
  */
typedef struct
{
    SEQLIST_ItemTypeDef *items; /*!< Pointer to item array */
    uint16_t length;            /*!< Current number of items */
    uint16_t tail;              /*!< Index of the tail (next insert position) */
} SEQLIST_HandleTypeDef;

void SeqList_Traverse(const SEQLIST_HandleTypeDef *hseq, void (*visit)(SEQLIST_ItemTypeDef *item));

#ifdef __cplusplus
}
#endif
#endif /* __SEQLIST_H */

