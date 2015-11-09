#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include "mpc.h"

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

enum { LVAL_NUM, LVAL_ERR, LVAL_SYM,
       LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

typedef lval*(*lbuiltin)(lenv*, lval*);

struct lenv {
  int count;
  char** syms;
  lval** vals;
};

struct lval {
  int type;
  long num;
  char* err;
  char* sym;
  lbuiltin fun;
  int count;
  lval** cell;
};

lval* lval_num(long x);
lval* lval_err(char *fmt, ...);
lval* lval_sym(char* s);
lval* lval_sexpr(void);
lval* lval_qexpr(void);

char* ltype_name(int t);

void lval_del(lval* v);
lval* lval_add(lval* v, lval* x);
lval* lval_copy(lval* v);

lenv* lenv_new(void);
void lenv_del(lenv* e);
lval* lenv_get(lenv* e, lval* k);
void lenv_put(lenv* e, lval* k, lval* v);

void lenv_add_builtin(lenv* e, char* name, lbuiltin func);
void lenv_add_builtins(lenv* e);

void lval_print(lval* v);
void lval_println(lval* v);
void lval_expr_print(lval* v, char open, char close);
lval* lval_join(lval* x, lval* y);

lval* lval_read_num(mpc_ast_t* t);
lval* lval_read(mpc_ast_t* t);

lval* lval_eval_sexpr(lenv* e, lval* v);
lval* lval_eval(lenv* e, lval* v);

lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);

lval* builtin(lval* a, char* func);
lval* builtin_op(lenv* e, lval* a, char* op);
lval* builtin_head(lenv* e, lval* a);
lval* builtin_tail(lenv* e, lval* a);
lval* builtin_list(lenv* e, lval* a);
lval* builtin_eval(lenv* e, lval* a);
lval* builtin_join(lenv* e, lval* a);

lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);

lval* builtin_def(lenv* e, lval* a);
