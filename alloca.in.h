/* Memory allocation on the stack.

   Copyright (C) 1995, 1999, 2001-2004, 2006-2024 Free Software Foundation,
   Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Remph, 2024: Small adjustments made to make this independent of GNU
   autohell. Notably, this now operates under the assumption that it will be
   included as "alloca.h", not <alloca.h> */

/* Avoid using the symbol _ALLOCA_H here, as Bison assumes _ALLOCA_H
   means there is a real alloca function.  */
#ifndef XGL_ALLOCA_H /* because it's ex-gnulib */
#define XGL_ALLOCA_H

/* alloca (N) returns a pointer to N bytes of memory
   allocated on the stack, which will last until the function returns.
   Use of alloca should be avoided:
     - inside arguments of function calls - undefined behaviour,
     - in inline functions - the allocation may actually last until the
       calling function returns,
     - for huge N (say, N >= 65536) - you never know how large (or small)
       the stack is, and when the stack cannot fulfill the memory allocation
       request, the program just crashes.
 */

#define HAVE_ALLOCA 1

#if @HAVE_ALLOCA_H@
# include <alloca.h>
#else
# if defined __GNUC__ || (__clang_major__ >= 4)
#  define alloca __builtin_alloca
# elif defined _AIX
#  define alloca __alloca
# elif defined _MSC_VER
#  include <malloc.h>
#  define alloca _alloca
# elif defined __DECC && defined __VMS
#  define alloca __ALLOCA
# elif defined __TANDEM && defined _TNS_E_TARGET
#  ifdef  __cplusplus
extern "C"
#  endif
void *_alloca (unsigned short);
#  pragma intrinsic (_alloca)
#  define alloca _alloca
# elif defined __MVS__
#  include <stdlib.h>
# else
#  undef HAVE_ALLOCA
# endif
#endif /* HAVE_ALLOCA_H */

#endif /* XGL_ALLOCA_H */
