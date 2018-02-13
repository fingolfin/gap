/*
 * Small program to test libgap linkability and basic working
 */
#include <stdio.h>
#include <unistd.h>

#include <src/compiled.h>
#include <src/libgap.h>
#include <src/libgap_internal.h>

extern char ** environ;

void error_handler(char * msg)
{
    printf("Error: %s\n", msg);
}

void eval(char * cmd)
{
    printf("Input:\n%s", cmd);
    GAP_start_interaction(cmd);

    GAP_enter();
    Obj eval_result;
    ReadEvalCommand(STATE(BottomLVars),&eval_result, 0);
    ViewObjHandler(eval_result);
    char * out = GAP_get_output();
    GAP_exit();

    printf("Output:\n%s", out);
    GAP_finish_interaction();
}

int main(int argc, char **argv)
{
    GAP_set_error_handler(&error_handler);
    GAP_initialize(argc, argv);
    printf("Initialized\n");

    GAP_enter();
    CollectBags(0, 1);    // full GC
    GAP_exit();

    eval("1+2+3;\n");
    eval("g:=FreeGroup(2);\n");
    eval("a:=g.1;\n");
    eval("b:=g.2;\n");
    eval("lis:=[a^2, a^2, b*a];\n");
    eval("h:=g/lis;\n");
    eval("c:=h.1;\n");
    eval("Set([1..1000000], i->Order(c));\n");

    GAP_finalize();
    return 0;
}


/*
g:=FreeGroup(2);
a:=g.1;
b:=g.2;
lis:=[a^2, a^2, b*a];
h:=g/lis;
c:=h.1;
Set([1..300000], i->Order(c));
 */
