//coauthored

#ifndef PERF_H
#define PERF_H

void perf_zero(void);//set all counters to 0
void perf_print(char *test_name); //printing the results, pointer is to print the name of the test(points to the 1st character of test name)
void perf_tests(void); //actual testing

#endif