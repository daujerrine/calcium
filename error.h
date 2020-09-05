/**
 * \file error.h
 * \author Anamitra Ghorui
 * \brief Calcium error codes
 *
 */

#ifndef _CA_ERROR_H
#define _CA_ERROR_H

/// Datatype for error codes.
typedef enum CaError {
    // Actual Errors
    CA_ERROR_HASH_INVALID_KEY = -10000,
    CA_ERROR_HASH_NOTFOUND,
    
    CA_ERROR_OK = 1,
    
    // Info Errors
    CA_ERROR_STACK_FULL,
    CA_ERROR_STACK_EMPTY,
    CA_ERROR_HASH_NEW,
    CA_ERROR_HASH_EXISTING,
} CaError;

#endif
