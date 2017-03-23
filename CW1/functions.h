#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Counting the number of words in the dictionary.
int count_dictionary_words(FILE *f);

// A function that is used for qsort
int string_compare_int(const void *f, const void *s);

// Loading the words of the dictionary into an array
char** load_dictionary_array(FILE* d, int w, int case_flag);

// binary search that takes the target word and tries to find it in the
// dictionary.
int binary_dictionary_search(char** array, char *word_buffer, int w);
