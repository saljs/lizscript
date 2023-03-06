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
    r = lizscript_eval("5");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 5);

    r = lizscript_eval("-287");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == -287);

    r = lizscript_eval("+80");
    assert(r.result.type == LS_INT_T);
    assert(r.result.ival == 80);

    r = lizscript_eval("+3.9");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 3.9));
    
    r = lizscript_eval(".5");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 0.5));

    r = lizscript_eval("    -.9");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, -0.9));
    
    r = lizscript_eval("2.0");
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 2));

    /*
     * Test parsing of characters
     */
    r = lizscript_eval(" 'b'");
    assert(r.result.type == LS_CHAR_T);
    assert(r.result.cval == 'b');
    
    r = lizscript_eval("'''");
    assert(r.result.type == LS_CHAR_T);
    assert(r.result.cval == '\'');

    r = lizscript_eval("''");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EUNEXPECTEDTOKEN);
    LSERR = NOERR;
    
    r = lizscript_eval("'r");
    assert(r.result.type == LS_INVALID_T);
    assert(LSERR == EUNEXPECTEDTOKEN);
    LSERR = NOERR;

    /*
     * Test parsing of bools
     */
    r = lizscript_eval("#t");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.bval == true);
    
    r = lizscript_eval("  #f");
    assert(r.result.type == LS_BOOL_T);
    assert(r.result.cval == false);

    return 0;
}
