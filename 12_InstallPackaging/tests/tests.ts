#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "guess.h"

#suite even_or_odd_function

#tcase odd_or_even_test

#test even
    setenv("LC_ALL", "en_US", 1);
    ck_assert_str_eq(odd_or_even(0), "It is an even number.\n");

#test odd
    setenv("LC_ALL", "en_US", 1);
    ck_assert_str_eq(odd_or_even(1), "It is an odd number.\n");

#suite safe_atoi_test

#tcase error_format

#test letters
    int n;
    ck_assert_int_eq(safe_atoi("bebebe", &n), 0);

#test small_number
    int n;
    ck_assert_int_eq(safe_atoi("-123456789123456789", &n), 0);

#test big_number
    int n;
    ck_assert_int_eq(safe_atoi("123456789123456789", &n), 0);

#tcase correct_format

#test negative_number
    int n;
    ck_assert_int_eq(safe_atoi("-1234", &n), 1);

#test positive_number
    int n;
    ck_assert_int_eq(safe_atoi("1234", &n), 1);
 
