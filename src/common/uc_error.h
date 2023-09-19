/**
 * @file uc_error.h
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
typedef enum uc_error_tag
{
  UC_ERROR__OK = 0,          /**<  Init stage. Always shall be the first */
  UC_ERROR__INVALID_ARG,     /**<  Init stage. Always shall be the first */
  UC_ERROR__OVERFLOW,        /**<  Init stage. Always shall be the first */
  UC_ERROR__BUFFER_FULL,     /**<  Init stage. Always shall be the first */
  UC_ERROR__EMPTY,           /**<  Init stage. Always shall be the first */
  UC_ERROR__INVALID_POINTER, /**<  Init stage. Always shall be the first */
} uc_error_e;

//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
