/*
 * test_progss.c
 *
 * Tests LizScript with some simple programs.
 */

#include <assert.h>
#include <stdio.h>
#include "../src/lizscript.h"

bool compare_floats(float flt1, float flt2)
{
    float delta = flt1 - flt2;
    return delta < 0.00001 || delta > -0.00001;
}

/*
 * Mock functions
 */
LSData sensor_readings(LSData input, LSData* ctx)
{
    LSData result;
    float data[] = {0.23, 0.28, 0.46, 0.55, 0.53, 0.44};
    assert(NULL == ctx);
    assert(input.type == LS_INT_T);
    assert(input.ival >= 0);
    assert(input.ival < 6);
    result.type = LS_FLOAT_T;
    result.fval = data[input.ival];
    return result;
}

int main()
{
    LSParseResult r;
    char script[1000];
    int i;

    /*
     * Ramp function:
     *   Should return 0 if input is less than 100,
     *   fhen ramp smoothly to 255 between 100-200.
     *   Finally, ramps down to 0 between 900-1000.
     */
    for(i = 0; i <= 1000; i++)
    {
        sprintf(script, 
            "(let t %d"
            " (switch 0"
            "  (((< 100) t) 0)"
            "  (((< 200) t) (floor ((* 2.55) ((- 100) t))))"
            "  (((< 900) t) 255)"
            "  (((< 1000) t) ((- (floor ((* 2.55) ((- 900) t)))) 255))"
            " )"
            ")",         
            i
        );
        r = eval_lizscript(script);
        assert(r.result.type == LS_INT_T);
        if (i < 100)
            assert(r.result.ival == 0);
        else if (i < 200)
            assert(r.result.ival == (int)(2.55 * (i - 100)));
        else if (i < 900)
            assert(r.result.ival == 255);
        else if (i < 1000)
            assert(r.result.ival == 255 - (int)(2.55 * (i - 900)));
        else
            assert(r.result.ival == 0);
    }

    /*
     * Test a PI(D) controller.
     * Expose data through a custom function.
     */
    LSData sensor_func;
    sensor_func.type = LS_FUNC_T;
    sensor_func.func.input = LS_INT_T;
    sensor_func.func.output = LS_FLOAT_T;
    sensor_func.func.ctx = NULL;
    sensor_func.func.body = sensor_readings;
    
    lizscript_global("sensor_val", sensor_func);
    lizscript_global("sensor_buff_len", (LSData){ .type = LS_INT_T, .ival = 6});

    r = eval_lizscript(
        "(let Kp 1.3"
        "  (let Ki 0.4"
        "    (func error ((- #x) 0.5)"
        "      (func integrate"
        "        (switch 0 (((< sensor_buff_len) #x)"
        "          ((+ (error (sensor_val #x))) (integrate ((+ 1) #x))))"
        "        )"
        "        ((+ ((* Kp) (error (sensor_val 0)))) ((* Ki) (integrate 1)))"
        "      )"
        "    )"
        "  )"
        ")"
    );
    assert(r.result.type == LS_FLOAT_T);
    assert(compare_floats(r.result.fval, 0.459));
    
    return 0;
}
