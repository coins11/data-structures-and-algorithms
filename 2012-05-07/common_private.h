
/*
 * Common private definition for the libdatastruct
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

#ifndef HEADER_COMMON_PRIVATE_H

#define HEADER_COMMON_PRIVATE_H

/*******************************************************************************
    Constants
*******************************************************************************/

#define GLIBC_ALLOCA                              1

/*******************************************************************************
    Including Headers
*******************************************************************************/

#include <stdlib.h>

#if GLIBC_ALLOCA
#include <alloca.h>
#endif

#include "common_public.h"

/*******************************************************************************
    Macros
*******************************************************************************/

#if GLIBC_ALLOCA

#define portable_alloca(size)                     (alloca(size))
#define portable_alloca_free(ptr)                 ((void)0)
#define portable_alloca_check(ptr)                (1)

#else

#define portable_alloca(size)                     (malloc(size))
#define portable_alloca_free(ptr)                 (free(ptr))
#define portable_alloca_check(ptr)                (ptr)

#endif

/*******************************************************************************
    Functions
*******************************************************************************/

extern unsigned int power_of_two_alignment
    (unsigned int);

#endif /* HEADER_COMMON_PRIVATE_H */

