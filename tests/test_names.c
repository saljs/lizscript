/*
 * test_names.c
 *
 * Tests the LizScript name-mapping mechanism.
 */

#include <assert.h>
#include "../src/lizscript.h"

int main()
{
    LSParseResult r;

    /*
     * Test mapping of atoms
     */
    r = eval_lizscript("(let foo 5 foo)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);

    r = eval_lizscript("foo");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == ENOTFOUND);

    r = eval_lizscript("(let bar 3 ((+ bar) 4))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 7);

    r = eval_lizscript("(let baz 4 ((+ 5) baz))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 9);

    /*
     * Test mapping of functions
     */
    r = eval_lizscript("(let add_three (+ 3) (add_three 8))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 11);

    r = eval_lizscript("(add_three 4)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == ENOTFOUND);
    
    r = eval_lizscript("(let add_four (+ 4) (add_four (add_four 8)))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 16);

    /*
     * Test nested let
     */
    r = eval_lizscript("(let foo 5 (let bar -3 ((+ foo) bar)))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 2);

    r = eval_lizscript("(let foo 5 (let foo 7 foo))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 7);

    r = eval_lizscript("(let add_two (+ 2) (let sub_one (- 1) (add_two (sub_one 5))))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 6);
    
    r = eval_lizscript("(sub_one 4)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == ENOTFOUND); 

    return 0;
}
