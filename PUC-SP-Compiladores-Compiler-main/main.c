#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"

/* provided by Bison/Flex */
extern FILE *yyin;
extern int   yyparse(void);
extern AstNode *parse_root;

static void usage(const char *prog) {
    fprintf(stderr,
        "usage: %s [options] <source.pas>\n"
        "  -o <file>   output binary (default: a.out)\n"
        "  --emit-ir   write LLVM IR to <source>.ll and stop\n"
        "  --emit-obj  write object file to <source>.o and stop\n",
        prog);
    exit(1);
}

int main(int argc, char **argv) {
    const char *src      = NULL;
    const char *out      = "a.out";
    int         emit_ir  = 0;
    int         emit_obj = 0;

    for (int i = 1; i < argc; i++) {
        if      (!strcmp(argv[i], "-o") && i+1 < argc) out = argv[++i];
        else if (!strcmp(argv[i], "--emit-ir"))         emit_ir  = 1;
        else if (!strcmp(argv[i], "--emit-obj"))        emit_obj = 1;
        else if (argv[i][0] != '-')                     src = argv[i];
        else    usage(argv[0]);
    }
    if (!src) usage(argv[0]);

    /* ── 1. Lex + Parse ──────────────────────────────────────── */
    yyin = fopen(src, "r");
    if (!yyin) { perror(src); return 1; }

    if (yyparse() != 0 || !parse_root) {
        fprintf(stderr, "compilation aborted: parse failed\n");
        fclose(yyin);
        return 1;
    }
    fclose(yyin);

    /* ── 2. Symbol table + Codegen ───────────────────────────── */
    /* derive module name from filename (strip path + extension) */
    const char *base = strrchr(src, '/');
    base = base ? base + 1 : src;
    char modname[256];
    snprintf(modname, sizeof(modname), "%s", base);
    char *dot = strrchr(modname, '.');
    if (dot) *dot = '\0';

    SymTable syms;
    sym_init(&syms);

    CG *cg = cg_create(modname);
    cg_emit(cg, parse_root, &syms);

    /* ── 3. Output ───────────────────────────────────────────── */
    if (emit_ir) {
        char irpath[300];
        snprintf(irpath, sizeof(irpath), "%s.ll", modname);
        int rc = cg_write_ir(cg, irpath);
        fprintf(rc ? stderr : stdout,
                rc ? "IR write failed\n" : "IR written: %s\n", irpath);
        cg_destroy(cg);
        ast_free(parse_root);
        return rc;
    }

    if (emit_obj) {
        char objpath[300];
        snprintf(objpath, sizeof(objpath), "%s.o", modname);
        int rc = cg_write_obj(cg, objpath);
        fprintf(rc ? stderr : stdout,
                rc ? "obj write failed\n" : "obj written: %s\n", objpath);
        cg_destroy(cg);
        ast_free(parse_root);
        return rc;
    }

    /* default: emit obj then link via clang */
    char objpath[300], cmd[512];
    snprintf(objpath, sizeof(objpath), "/tmp/%s.o", modname);

    if (cg_write_obj(cg, objpath) != 0) {
        cg_destroy(cg); ast_free(parse_root); return 1;
    }

    /* CORREÇÃO DO LINKADOR: Adicionada a flag '-lc' para linkar o printf e o atoi da libc nativa */
    snprintf(cmd, sizeof(cmd), "clang -no-pie %s -o %s -lc", objpath, out);
    int rc = system(cmd);
    if (rc != 0) fprintf(stderr, "link failed (exit %d)\n", rc);

    cg_destroy(cg);
    ast_free(parse_root);
    return rc;
}
