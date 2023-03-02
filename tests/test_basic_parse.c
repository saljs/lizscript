/*
 * test_parser.c
 *
 * Tests the Lizscript to ensure that it can parse basic types correctly.
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
     * Test parsing of numbers
     */
    r = eval_lizscript("5");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);

    r = eval_lizscript("-287");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == -287);

    r = eval_lizscript("+80");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 80);

    r = eval_lizscript("+3.9");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 3.9));
    
    r = eval_lizscript(".5");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 0.5));

    r = eval_lizscript("    -.9");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, -0.9));
    
    r = eval_lizscript("2.0");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 2));

    /*
     * Test parsing of characters
     */
    r = eval_lizscript(" 'b'");
    assert(r.result.type == LS_CHAR_T);
    assert(r.result.cval == 'b');
    
    r = eval_lizscript("'''");
    assert(r.result.type == LS_CHAR_T);
    assert(r.result.cval == '\'');

    r = eval_lizscript("''");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EUNEXPECTEDTOKEN);
    LSERR = NOERR;
    
    r = eval_lizscript("'r");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EUNEXPECTEDTOKEN);
    LSERR = NOERR;

    /*
     * Test parsing of bools
     */
    r = eval_lizscript("#t");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
    
    r = eval_lizscript("  #f");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.cval == false);

    return 0;
}
