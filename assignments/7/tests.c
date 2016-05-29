#include "cutest/CuTest.h"
#include <stdio.h>

CuSuite* getDequeTestSuite();
CuSuite* getGraphTestSuite();

int main()
{
    CuSuite* suite = CuSuiteNew();
    CuSuiteConsume(suite, getDequeTestSuite());
    CuSuiteConsume(suite, getGraphTestSuite());
    CuSuiteRun(suite);
    CuString* output = CuStringNew();
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);
    return 0;
}