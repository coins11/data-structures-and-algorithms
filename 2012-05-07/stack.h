
/*
 * Definition for the stack data structure
 * Copyright (c) 2009, Kazuhiko Sakaguchi All rights reserved.
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

#ifndef HEADER_STACK_H

#define HEADER_STACK_H

/*******************************************************************************
    Constants
*******************************************************************************/

#define STACK_SUCCESS                             0x00000000
#define STACK_MEMORY_ALLOCATION_ERROR             0x00000001
#define STACK_EMPTY                               0x00000002
#define STACK_OFFSET_IS_TOO_LARGE                 0x00000004

#define STACK_MEMORY_ALLOCATION_UNIT_SIZE         32

/*******************************************************************************
    Including Headers
*******************************************************************************/

#include "common_public.h"

/*******************************************************************************
    Structures
*******************************************************************************/

typedef struct stack stack_t;

struct stack
{
    char *array;
    size_t size;
    size_t element_size;
    size_t array_size;
    void (*release_function)(void *);
};

/*******************************************************************************
    Macros
*******************************************************************************/

#define stack_size(stack) \
    ((stack)->size)

#define stack_empty(stack) \
    (!(stack)->size)

/*******************************************************************************
    Functions
*******************************************************************************/

extern stack_t *stack_initialize
    (size_t,void (*)(void *));
extern void stack_release
    (stack_t *);
extern unsigned int stack_bottom
    (stack_t *,void *);
extern unsigned int stack_top
    (stack_t *,void *);
extern unsigned int stack_refer_from_bottom
    (stack_t *,size_t,void *);
extern unsigned int stack_refer_from_top
    (stack_t *,size_t,void *);
extern unsigned int stack_refer_many_elements_from_bottom
    (stack_t *,size_t,size_t,void *);
extern unsigned int stack_refer_many_elements_from_top
    (stack_t *,size_t,size_t,void *);
extern unsigned int stack_push
    (stack_t *,const void *);
extern unsigned int stack_pop
    (stack_t *,void *);
extern unsigned int stack_push_many_elements
    (stack_t *,size_t,const void *);
extern unsigned int stack_pop_many_elements
    (stack_t *,size_t,void *);

#endif /* HEADER_STACK_H */

