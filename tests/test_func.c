/*
 * test_func.c
 *
 * Tests func statements
 */

#include <assert.h>
#include "../src/lizscript.h"

int main()
{
    LSParseResult r;

    /*
     * Test basic functionality
     */
    r = lizscript_eval("(func foo ((+ #x) 5) (foo 3))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 8);
    
    r = lizscript_eval("(func foo (switch 10 (#x 5)) ((* (foo #t)) (foo #f)))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 50);

    /*
     * Test nested functions
     */
    r = lizscript_eval("(func square ((* #x) #x) (func cube ((* #x) (square #x)) (cube 3)))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 9);

    r = lizscript_eval("(func cube ((* #x) (func square ((* #x) #x) (square #x))) (cube 3))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 9);

    /*
     * Test recursion
     */
    r = lizscript_eval("(func fac (switch 1 (((> 1) #x) ((* #x) (fac ((- 1) #x))))) (fac 5))");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival = 120);
   
    /*
     * Test unbounded recursion fails
     */
   r = lizscript_eval("(func badfac ((* #x) (badfac ((- 1) #x))) (badfac 5))");
   assert(r.result.type == LS_INVALID_T);
   assert(LSERR == EMAXRECURSION);
   LSERR = NOERR;

    return 0;
}
