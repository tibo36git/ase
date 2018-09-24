#include <stdio.h>
#include "lib_try_throw.h"

int try(struct ctx_s *pctx, func_t *f, int arg) {
    pctx->ctx_magic = CTXMAGIC;

    asm ("movl %%esp , %0" : "=r" (pctx->ctx_esp));
    asm ("movl %%ebp , %0" : "=r" (pctx->ctx_ebp)); 

    return f(arg);
}

int throw(struct ctx_s *pctx, int r) {
    static int global_r;

    assert(pctx->ctx_magic == CTXMAGIC);

    asm ("movl %0 , %%esp" : : "r" (pctx->ctx_esp));
    asm ("movl %0 , %%ebp" : : "r" (pctx->ctx_ebp));

    return global_r;
}