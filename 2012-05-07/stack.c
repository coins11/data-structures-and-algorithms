
/*
 * Functions for the stack data structure
 * Copyright (c) 2008-2009, Kazuhiko Sakaguchi All rights reserved.
 * This file is part of the libdatastruct.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Stricter.org nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY KAZUHIKO SAKAGUCHI ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL KAZUHIKO SAKAGUCHI BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*******************************************************************************
    Including Headers
*******************************************************************************/

#include "stack.h"
#include "common_private.h"

/*******************************************************************************
    Macros
*******************************************************************************/

#define refer_by_offset(stack,offset) \
    ((stack)->array+(stack)->element_size*(offset))

#define refer_by_offset_from_bottom(stack,offset) \
    (refer_by_offset((stack),(offset)))

#define refer_by_offset_from_top(stack,offset) \
    (refer_by_offset((stack),stack_size(stack)-1-(offset)))

#define refer_bottom(stack) \
    ((stack)->array)

#define refer_top(stack) \
    refer_by_offset((stack),(stack)->size-1)

/*******************************************************************************
    Functions
*******************************************************************************/

stack_t *stack_initialize(size_t element_size
    ,void (*release_function)(void *))
{
    stack_t *stack = malloc(sizeof(stack_t));
    if(!stack){
        return NULL;
    }
    stack->array = NULL;
    stack->size = 0;
    stack->element_size = element_size;
    stack->array_size = 0;
    stack->release_function = release_function;
    return stack;
}

void stack_release(stack_t *stack)
{
    if(stack){
        if(stack->release_function != DEFAULT_RELEASE_FUNCTION){
            size_t counter = 0;
            while(counter != stack->size){
                stack->release_function(refer_by_offset(stack,counter));
                counter++;
            }
        }
        free(stack->array);
        free(stack);
    }
}

unsigned int stack_bottom(stack_t *stack,void *output)
{
    if(stack_empty(stack)){
        return STACK_EMPTY;
    }
    if(output){
        memcpy(output,refer_bottom(stack),stack->element_size);
    }
    return STACK_SUCCESS;
}

unsigned int stack_top(stack_t *stack,void *output)
{
    if(stack_empty(stack)){
        return STACK_EMPTY;
    }
    if(output){
        memcpy(output,refer_top(stack),stack->element_size);
    }
    return STACK_SUCCESS;
}

unsigned int stack_refer_from_bottom
    (stack_t *stack,size_t offset,void *output)
{
    if(offset >= stack_size(stack)){
        return STACK_OFFSET_IS_TOO_LARGE;
    }
    if(output){
        memcpy(output,refer_by_offset_from_bottom(stack,offset)
            ,stack->element_size);
    }
    return STACK_SUCCESS;
}

unsigned int stack_refer_from_top
    (stack_t *stack,size_t offset,void *output)
{
    if(offset >= stack_size(stack)){
        return STACK_OFFSET_IS_TOO_LARGE;
    }
    if(output){
        memcpy(output,refer_by_offset_from_top(stack,offset)
            ,stack->element_size);
    }
    return STACK_SUCCESS;
}

unsigned int stack_refer_many_elements_from_bottom
    (stack_t *stack,size_t offset_a,size_t offset_b,void *output)
{
    if(offset_a >= stack_size(stack) || offset_b >= stack_size(stack)){
        return STACK_OFFSET_IS_TOO_LARGE;
    }
    if(output){
        size_t offset_small,offset_big;
        if(offset_a < offset_b){
            offset_small = offset_a;
            offset_big = offset_b;
        }
        else{
            offset_small = offset_b;
            offset_big = offset_a;
        }
        memcpy(output,refer_by_offset_from_bottom(stack,offset_small)
            ,stack->element_size*(offset_big-offset_small+1));
    }
    return STACK_SUCCESS;
}

unsigned int stack_refer_many_elements_from_top
    (stack_t *stack,size_t offset_a,size_t offset_b,void *output_)
{
    char *output = output_;
    if(offset_a >= stack_size(stack) || offset_b >= stack_size(stack)){
        return STACK_OFFSET_IS_TOO_LARGE;
    }
    if(output){
        size_t offset_small,offset_big,area_size,counter = 0;
        if(offset_a < offset_b){
            offset_small = offset_a;
            offset_big = offset_b;
        }
        else{
            offset_small = offset_b;
            offset_big = offset_a;
        }
        area_size = offset_big-offset_small+1;
        while(counter != area_size){
            memcpy(output+stack->element_size*counter
                ,refer_by_offset_from_top(stack,offset_small+counter)
                ,stack->element_size);
            counter++;
        }
    }
    return STACK_SUCCESS;
}

unsigned int stack_push(stack_t *stack,const void *input)
{
    if(stack->size == stack->array_size){
        void *temp = realloc(stack->array,stack->element_size
            *(stack->array_size+STACK_MEMORY_ALLOCATION_UNIT_SIZE));
        if(!temp){
            return STACK_MEMORY_ALLOCATION_ERROR;
        }
        stack->array = temp;
        stack->array_size = stack->array_size+STACK_MEMORY_ALLOCATION_UNIT_SIZE;
    }
    memcpy(refer_by_offset(stack,stack->size),input,stack->element_size);
    stack->size++;
    return STACK_SUCCESS;
}

unsigned int stack_pop(stack_t *stack,void *output)
{
    if(stack_empty(stack)){
        return STACK_EMPTY;
    }
    stack->size--;
    if(output){
        memcpy(output,refer_by_offset(stack,stack->size),stack->element_size);
    }
    if(STACK_MEMORY_ALLOCATION_UNIT_SIZE*2 <= stack->array_size-stack->size){
        void *temp = realloc(stack->array,stack->element_size
            *(stack->array_size-STACK_MEMORY_ALLOCATION_UNIT_SIZE));
        if(temp){
            stack->array = temp;
            stack->array_size
                = stack->array_size-STACK_MEMORY_ALLOCATION_UNIT_SIZE;
        }
    }
    return STACK_SUCCESS;
}

unsigned int stack_push_many_elements
    (stack_t *stack,size_t push_size,const void *input)
{
    if(stack->size+push_size > stack->array_size){
        size_t new_size = STACK_MEMORY_ALLOCATION_UNIT_SIZE*((size_t)
            ((stack->size+push_size)/STACK_MEMORY_ALLOCATION_UNIT_SIZE)+1);
        void *temp = realloc(stack->array,stack->element_size*new_size);
        if(!temp){
            return STACK_MEMORY_ALLOCATION_ERROR;
        }
        stack->array = temp;
        stack->array_size = new_size;
    }
    memcpy(refer_by_offset(stack,stack->size)
        ,input,stack->element_size*push_size);
    stack->size += push_size;
    return STACK_SUCCESS;
}

unsigned int stack_pop_many_elements
    (stack_t *stack,size_t pop_size,void *output_)
{
    char *output = output_;
    if(stack->size < pop_size){
        return STACK_EMPTY;
    }
    if(output){
        size_t counter = pop_size;
        while(counter){
            memcpy(output+stack->element_size*(pop_size-counter)
                ,refer_by_offset_from_top(stack,pop_size-counter)
                ,stack->element_size);
            counter--;
        }
    }
    stack->size -= pop_size;
    return STACK_SUCCESS;
}

