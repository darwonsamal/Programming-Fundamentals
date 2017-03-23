/* Author: Darwon Rashid
Matric Number - 40280334
*/

// Libraries to be included for code.
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// define size for buffer.
#define  BUFFER 50

// Function created to count the number of words in the dictionary for use.
// Works by incrementing the counter by one every time there is a new line
// given that each line contains just one word.
int count_dictionary_words(FILE *f)
{
  // Variables to be used.
  int count = 0;
  char ch;
  // While the dictionary file is not finished, increment the counter by one
  // each time there is a new line.
  while((ch = fgetc(f)) != EOF)
  {
    if (ch == '\n')
    {
      count++;
    }
  }
  //    returns the number of 'words'
  return count;
}

// A neccesary function for qsort to work. qsort uses this function
// as a parameter for resorting arrays.
int string_compare_int(const void *f, const void *s)
{
  const char** first_string = (const char**)f;
  const char** second_string = (const char**)s;
  return strcmp(*first_string, *second_string);
}


// Function created to load the entire dictionary txt file into a double dimensional array for use.
// Requires the file and number of words in the file.
char** load_dictionary_array(FILE* d, int w, int case_flag)
{
  // We have to allocate proper memory for the double array in an efficient manner
  // and to do that we multiply the amount of word in the file by the size of a char*.
  char** array = malloc(w * sizeof(char*));
  char line[BUFFER];
  // We need a for loop to go over the array so we can put the actual words in them and then
  // also allocate memory for each index.
  for(int i = 0; i < w; ++i)
  {
    // Scans through the actual dictionary file and only takes in strings.
    fscanf(d, "%s", line);
    // Now, we allocate proper memory for each index and that is done by the length of the word times
    // the size of a char and that plus one counts in the new line.
    array[i] = malloc(strlen(line) * sizeof(char) + 1);
    // If it is not case sensitive, then we lowercase every word in the dictionary.
    if(case_flag == 1)
    {
      for (int j = 0; line[j]; ++j)
      {
        line[j] = tolower(line[j]);

      }
    }
    // Now we copy each word from the buffer to each index in the array.
    strcpy(array[i], line);
  }
  fclose(d);
  // Given we are going to use a binary search, we have to resort the lowercase dictionary for it to
  // work. We sort the lowercase dictionary using a C function called qsort.
  if(case_flag == 1)
  {
    qsort(array, w, sizeof(char*), string_compare_int);
  }
  // returns the array once we are done.
  return array;
}
// Function created to take a targetted word and compare it the dictionary, it uses a binary search method.
// Requires the dictionary array, targetted word, and number of words in the dictionary.
int binary_dictionary_search(char** array, char *word_buffer, int w)
{
  int top = w;
  int bottom = 0;
  int mid = 0;

  // Binary search mechanism.
  // Goes in the middle and checks if the targetted value is above or below, if it is below, it eliminates the top or vice versa
  // Then it repeates the process again until it finds the targetted word. If the targetted word is find, it returns 1, if not
  // It returns 0.
  while(bottom <= top)
  {
    mid = (bottom + top) / 2;
    // if found return 1.
    if(strcmp(array[mid], word_buffer) == 0)
    {
      return 1;
    }
    else if(strcmp(array[mid], word_buffer) > 0)
    {
      top = mid - 1;
    }
    else if(strcmp(array[mid], word_buffer) < 0)
    {
      bottom = mid + 1;
    }
    else if(bottom > top)
    {
      break;
    }
  }
  //if not found, return 0.
  return 0;
}
