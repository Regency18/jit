//
// Created by Rushe on 8/4/2026->
//

#ifndef JITVM_ARRAY_H
#define JITVM_ARRAY_H

#include <stddef.h>

#include "TokenType.h"

#define new_array(type)\
    typedef struct {\
        type* items;\
        size_t size;\
        size_t capacity;\
    } type##Array

#define array_append(array, item)\
    do {\
        if (array->size >= array->capacity) {\
            if (array->capacity == 0) array->capacity = 2;\
            else array->capacity *= 2;\
            Token* ptr = realloc(array->items, array->capacity*sizeof(*array->items));\
            if(!ptr) break;\
            array->items = ptr;\
        }\
        array->items[array->size++] = item;\
    } while(0)

#endif //JITVM_ARRAY_H