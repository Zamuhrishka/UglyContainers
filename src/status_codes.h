/**
 * @file err.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief 
 * @date 2023-01-18
 */

#pragma once


//_____ I N C L U D E S _______________________________________________________

//_____ C O N F I G S  ________________________________________________________

//_____ D E F I N I T I O N S _________________________________________________
/**
*  \brief 
*/
typedef enum StatusCodes_tag {
    CONTAINER_OK = 0,						        /**<  Init stage. Always shall be the first */
    CONTAINER_PARAM_ERR,						/**<  Init stage. Always shall be the first */
    CONTAINER_OVERFLOW,						    /**<  Init stage. Always shall be the first */
    CONTAINER_FULL,						    /**<  Init stage. Always shall be the first */
    CONTAINER_EMPTY,						    /**<  Init stage. Always shall be the first */
    CONTAINER_BAD_POINTER,						/**<  Init stage. Always shall be the first */
} status_code_e;

//_____ M A C R O S ___________________________________________________________

//_____ V A R I A B L E S _____________________________________________________

//_____ P U B L I C  F U N C T I O N S_________________________________________
