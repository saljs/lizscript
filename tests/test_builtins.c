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
    r = eval_lizscript("((+ 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 14);

    r = eval_lizscript("((+ 3.2) 5.7)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 7.9));

    r = eval_lizscript("((+ 3) 5.)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 8));

    r = eval_lizscript("((+ 3.0) 5)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 8));

    r = eval_lizscript("((+ 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((+ '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test sub
     */
    r = eval_lizscript("((- 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 4);

    r = eval_lizscript("((- 3.2) 5.7)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 2.5));

    r = eval_lizscript("((- 3) 5.)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 2));

    r = eval_lizscript("((- 3.0) 5)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 2));

    r = eval_lizscript("((- 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((- '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test mul
     */
    r = eval_lizscript("((* 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 45);

    r = eval_lizscript("((* 3.2) 5.7)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 18.24));

    r = eval_lizscript("((* 3) 5.)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 15));

    r = eval_lizscript("((* 3.0) 5)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 15));

    r = eval_lizscript("((* 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((* '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test div
     */
    r = eval_lizscript("((/ 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 1);

    r = eval_lizscript("((/ 3.2) 5.7)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 1.78125));

    r = eval_lizscript("((/ 3) 9.)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 3));

    r = eval_lizscript("((/ 3.0) 9)");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 3));

    r = eval_lizscript("((/ 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((/ '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((/ 3) 0)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 0);
    
    r = eval_lizscript("((/ 0) 3)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EDIVZERO);
    LSERR = NOERR;

    /*
     * Test mod
     */
    r = eval_lizscript("((% 5) 9)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 4);

    r = eval_lizscript("((% 3) 5.)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((% 3) 5.)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((% 3) 0)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 0);
    
    r = eval_lizscript("((% 0) 3)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EDIVZERO);
    LSERR = NOERR;

    /*
     * Test floor
     */
    r = eval_lizscript("(floor 5.5)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);
    
    r = eval_lizscript("(floor 5.0)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);

    r = eval_lizscript("(floor 6)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test ceil
     */
    r = eval_lizscript("(ceil 5.5)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 6);
    
    r = eval_lizscript("(ceil 5.0)");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);

    r = eval_lizscript("(ceil 6)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test eq
     */
    r = eval_lizscript("((= #t) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
    
    r = eval_lizscript("((= #f) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);
   
    r = eval_lizscript("((= 5) 5)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
   
    r = eval_lizscript("((= 5) 9)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((= 5) 5.0)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
   
    r = eval_lizscript("((= 5.) 5)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
   
    r = eval_lizscript("((= 5.) 7)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);
   
    r = eval_lizscript("((= 5) 'e')");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);
   
    r = eval_lizscript("((= 'e') 'e')");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((= 'e') 'r')");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    /*
     * Test lt
     */
    r = eval_lizscript("((< 5) 3)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((< 5.0) 5.0)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((< 3.2) 5.7)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((< 5) 3.)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((< 3.0) 5)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((< 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((< '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test gt
     */
    r = eval_lizscript("((> 5) 3)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((> 5.0) 5.0)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);
    
    r = eval_lizscript("((> 3.2) 5.7)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((> 5) 3.)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((> 3.0) 5)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((> 3) '5')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((> '3') 5)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test and
     */
    r = eval_lizscript("((and #t) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((and #t) #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((and #f) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((and #f) #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((and #t) 1)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((and 0) #t)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test or
     */
    r = eval_lizscript("((or #t) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((or #t) #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((or #f) #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("((or #f) #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("((or #t) 1)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    r = eval_lizscript("((or 0) #t)");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    /*
     * Test not
     */
    r = eval_lizscript("(not #f)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);

    r = eval_lizscript("(not #t)");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == false);

    r = eval_lizscript("(not 'f')");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EWRONGTYPE);
    LSERR = NOERR;

    return 0;
}
