#include <stdio.h>
#include <assert.h>
#define CTXMAGIC 0xCAFEBABE
static int global_r;

typedef int (func_t) (int);

struct ctx_s {
    void * ctx_esp;
    void * ctx_ebp;
    unsigned int ctx_magic;
}

int try(struct ctx_s *pctx, func_t *f, int arg) {
    pctx->ctx_magic = CTXMAGIC;

    asm ("movl %%esp , %0" : "=r" (pctx->ctx_esp));
    asm ("movl %%ebp , %0" : "=r" (pctx->ctx_ebp)); 

    return f(arg);
}

int throw(struct ctx_s *pctx, int r) {
    assert(pctx->ctx_magic == CTXMAGIC);

    asm ("movl %0 , %%esp" : : "=r" (pctx->ctx_esp));
    asm ("movl %0 , %%ebp" : : "=r" (pctx->ctx_ebp));

    return global_r;
}