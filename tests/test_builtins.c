/*
 * test_builtins.c
 *
 * Tests the Lizscript built-in functions
 */

#include <assert.h>
#include "../src/lizscript.h"

bool compare_floats(float flt1, float flt2)
{
    float delta = flt1 - flt2;
    return delta < 0.00001 || delta > -0.00001;
}

int main()
{
    LSParseResult r;

    /*
     * Test add
     */
    r = lizscript_eval("((+ 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 14);

    r = lizscript_eval("((+ 3.2) 5.7)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 7.9));

    r = lizscript_eval("((+ 3) 5.)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 8));

    r = lizscript_eval("((+ 3.0) 5)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 8));

    r = lizscript_eval("((+ 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((+ '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test sub
     */
    r = lizscript_eval("((- 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 4);

    r = lizscript_eval("((- 3.2) 5.7)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 2.5));

    r = lizscript_eval("((- 3) 5.)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 2));

    r = lizscript_eval("((- 3.0) 5)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 2));

    r = lizscript_eval("((- 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((- '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test mul
     */
    r = lizscript_eval("((* 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 45);

    r = lizscript_eval("((* 3.2) 5.7)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 18.24));

    r = lizscript_eval("((* 3) 5.)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 15));

    r = lizscript_eval("((* 3.0) 5)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 15));

    r = lizscript_eval("((* 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((* '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test div
     */
    r = lizscript_eval("((/ 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 1);

    r = lizscript_eval("((/ 3.2) 5.7)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 1.78125));

    r = lizscript_eval("((/ 3) 9.)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 3));

    r = lizscript_eval("((/ 3.0) 9)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 3));

    r = lizscript_eval("((/ 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((/ '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((/ 3) 0)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 0);
    
    r = lizscript_eval("((/ 0) 3)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EDIVZERO);
    LSERR = NOERR;

    /*
     * Test mod
     */
    r = lizscript_eval("((% 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 4);

    r = lizscript_eval("((% 3) 5.)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((% 3) 5.)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((% 3) 0)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 0);
    
    r = lizscript_eval("((% 0) 3)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EDIVZERO);
    LSERR = NOERR;

    /*
     * Test floor
     */
    r = lizscript_eval("(floor 5.5)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);
    
    r = lizscript_eval("(floor 5.0)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);

    r = lizscript_eval("(floor 6)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test ceil
     */
    r = lizscript_eval("(ceil 5.5)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 6);
    
    r = lizscript_eval("(ceil 5.0)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);

    r = lizscript_eval("(ceil 6)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test eq
     */
    r = lizscript_eval("((= #t) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
    
    r = lizscript_eval("((= #f) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);
   
    r = lizscript_eval("((= 5) 5)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
   
    r = lizscript_eval("((= 5) 9)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((= 5) 5.0)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
   
    r = lizscript_eval("((= 5.) 5)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
   
    r = lizscript_eval("((= 5.) 7)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);
   
    r = lizscript_eval("((= 5) 'e')");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);
   
    r = lizscript_eval("((= 'e') 'e')");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((= 'e') 'r')");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    /*
     * Test lt
     */
    r = lizscript_eval("((< 5) 3)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((< 5.0) 5.0)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((< 3.2) 5.7)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((< 5) 3.)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((< 3.0) 5)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((< 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((< '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test gt
     */
    r = lizscript_eval("((> 5) 3)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((> 5.0) 5.0)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);
    
    r = lizscript_eval("((> 3.2) 5.7)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((> 5) 3.)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((> 3.0) 5)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((> 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((> '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test and
     */
    r = lizscript_eval("((and #t) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((and #t) #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((and #f) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((and #f) #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((and #t) 1)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((and 0) #t)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test or
     */
    r = lizscript_eval("((or #t) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((or #t) #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((or #f) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("((or #f) #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("((or #t) 1)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = lizscript_eval("((or 0) #t)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test not
     */
    r = lizscript_eval("(not #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = lizscript_eval("(not #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = lizscript_eval("(not 'f')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    return 0;
}
