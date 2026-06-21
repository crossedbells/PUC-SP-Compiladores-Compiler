#ifndef CODEGEN_H
#define CODEGEN_H

#include <llvm-c/Core.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Analysis.h>
#include "ast.h"

typedef struct {
    LLVMContextRef  ctx;
    LLVMModuleRef   mod;
    LLVMBuilderRef  bld;
    SymTable       *syms;

    /* cached extern refs */
    LLVMValueRef    fn_printf;
    LLVMValueRef    fn_atoi;

    /* argc/argv passed into main, forwarded for paramcount/paramstr */
    LLVMValueRef    llvm_argc;
    LLVMValueRef    llvm_argv;

    /* current function being built (for return resolution) */
    LLVMValueRef    cur_fn;
    PascalType      cur_fn_rettype;
    LLVMValueRef    cur_fn_retslot;  /* alloca for function result */
} CG;

/* lifecycle */
CG  *cg_create(const char *module_name);
void cg_destroy(CG *cg);

/* entry point: walk full AST, emit IR */
void cg_emit(CG *cg, AstNode *root, SymTable *syms);

/* emit to .ll file */
int  cg_write_ir(CG *cg, const char *path);

/* emit native object file via TargetMachine */
int  cg_write_obj(CG *cg, const char *path);

#endif /* CODEGEN_H */
