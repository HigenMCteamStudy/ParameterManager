/**
 * @file profile_dic.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef PROFILE_DICTIONARY_H
#define PROFILE_DICTIONARY_H

/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdint.h>

#include "parameter.h"
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/

typedef struct parameter_desc parameter_desc_t;
/**
 * @brief Parameter read callback implementation
 *
 * @param [in] p_elem Element object for the specific parameter
 * @param [in] p_buf Buffer into which to read the data into
 * @param [in] len Length of the data to read, inbytes
 *
 * @return PARAM_SUCCESS on success, else failure
 */
typedef int32_t (*parameter_read)(parameter_desc_t * p_elem,
                                    void * p_buf,
                                    uint16_t len);

/**
 * @brief Parameter write callback implementation
 *
 * @param [in] p_elem Element object for the specific parameter
 * @param [in] p_buf Buffer which has data to write
 * @param [in] len Length of the data to write, inbytes
 *
 * @return PARAM_SUCCESS on success, else failure
 */
typedef int32_t (*parameter_write)(parameter_desc_t * p_elem,
                                    void * p_buf,
                                    uint16_t len);

/**
 * @brief Parameter persistent module element.
 *
 * This element is reprisentive parameter attribution
 *
 */
typedef struct parameter_desc
{
    uint32_t index; 			/**< parameter identification. High two bytes is index,
                        		low two bytes is sub index */
    uint16_t md_index;			/**< modebus index */
    uint16_t type; 				/**< parameter data type */
    uint16_t attr; 				/**< parameter access permitions(RD/WR/VAR/FUNC) */
    void * p_data; 				/**< parameter data point */
    int32_t min; 				/**< parameter data minimum value */
    uint32_t max; 				/**< parameter data maximum value */
    parameter_read read;        /**< parameter read function pointer */
    parameter_write write;      /**< parameter write function pointer */
} parameter_desc_t;
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
extern parameter_desc_t param_dic[PARAMETER_IDX_NUMBER];
/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/
/**
 * @brief Binary search function from parameter dictionary with parameter index
 *
 * @param elements Parameter dictionary
 * @param low Minium parameter index
 * @param high Maxium parameter index
 * @param target Parameter index want to searching
 * @return parameter_t * SUCCESS : pointer of parameter, Failed : PARAM_NULL
 */
parameter_desc_t * binarySearch(parameter_desc_t elements[],
    uint16_t low, uint16_t high, uint16_t target);

#endif // PROFILE_DICTIONARY_H