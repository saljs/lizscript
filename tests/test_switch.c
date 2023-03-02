/*
 * test_switch.c
 *
 * Tests switch statements
 */

#include <assert.h>
#include "../src/lizscript.h"

int main()
{
    LSParseResult r;

    /* 
     * Test basic functionality
     */
    r = eval_lizscript("(switch 3 (#t 5))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 5);

    r = eval_lizscript("(switch 3 (#f 7) (#t 5))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 5);

    r = eval_lizscript("(switch 3 (#f 7) (#t 5) (#t 9) )");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 5);

    r = eval_lizscript("(switch 3 (#f 7) (#f 5) (#f 9))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 3);

    /*
     * Test with nested statements
     */
    r = eval_lizscript("(switch 3 (((< 7) 3) 5))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 5);

    r = eval_lizscript("(switch ((- 3) 6) (((< 4) 7) 7) (((= 5) 5) ((+ 3) 2)))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 5);

    r = eval_lizscript("(switch ((- 3) 6) (((< 4) 7) 7) (((= 5) 5) ((+ 3) 2)) (((= 4) 4) 9))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 5);

    r = eval_lizscript("(switch ((- 3) 6)) (((< 4) 7) 7) (((= 5) 9) ((+ 3) 2)) (((= 4) 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 3);


    /*
     * Test errors
     */
    r = eval_lizscript("(switch 3 (9 5))");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("(switch (#t 5))");
    assert(r.result.type == LS_INVALID_T);
    LSERR = NOERR;




    return 0;
}
