/* Author: Darwon Rashid
Matric Number - 40280334
*/

// Libraries to be included for code.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

// define size for buffer.
#define  BUFFER 50

// Main method.
int main(int argc, char const *argv[])
{
  // Variables used for flags.
  int input_flag = 0;
  int output_flag = 0;
  int case_flag = 0;
  int flag = 1;
  int exit_flag = 0;
  // Variables used for files.
  FILE* input_file;
  FILE* output_file;
  FILE* dictionary = fopen("dictionary.txt", "r");
  // A for loop that goes through the command line arguements to see what the user wants.
  // For example, if "-i" is pressed, the input_flag is on and the file is next arguement after "-i".
  // This works for both "-o" and "-c".
  for(int j = 0; j < argc; j++)
  {
    if(strcmp(argv[j], "-i") == 0)
    {
      input_file = fopen(argv[j + 1], "r");
      input_flag = 1;
    }
    if(strcmp(argv[j],"-o") == 0)
    {
      output_file = fopen(argv[j + 1], "w");
      output_flag = 1;
    }
    if(strcmp(argv[j],"-c") == 0)
    {
      case_flag = 1;
    }
  }
  //Variables used for the spell checking algorithm
  char word_buffer[BUFFER];
  char *lower_case_word_buffer;
  int cap_word_flag = 0;
  int sentence_flag = 0;
  int found_flag = 0;
  int first_word_flag = 1;
  int reset_flag = 1;
  int mistake_flag = 0;
  char c;
  int line_count = 1;
  int stdin_line_count = 1;
  int i = 0;
  // Number of words in the dictionary
  int dictionary_words = count_dictionary_words(dictionary);
  // Rewinding the dictionary back to the begining due to the count_dictionary_words function.
  rewind(dictionary);
  // Loads the dictionary into the array for use.
  char** dictionary_array = load_dictionary_array(dictionary, dictionary_words, case_flag);
  // if there is no input_flag, then we use stdin as input.
  if(input_flag == 0)
  {
    input_file = stdin;
    printf("#########################\n");
    printf("#      Spell-Checker    #\n");
    printf("#      Darwon Rashid    #\n");
    printf("#########################\n");
    printf("\n");
    printf("Type 'EXIT' to end the program\n");
    printf("If there is no error signal, it means there are no errors.\n");
    printf("Enter sentences or words for spell checking \n");
    printf("\n");
  }


    // Goes over the input_file until it is the end of the file.
    while (!feof(input_file))
    {
      // Takes in the file character by character
      c = fgetc(input_file);
      // Adds in characters that are only alphabets into our word_buffer.
      if(isalpha(c))
      {
        word_buffer[i++] = c;
      }
      // If there are no more alphabets, put a null pointer, and that is a full word.
      else
      {
        word_buffer[i] = '\0';
        //if we are using stdin and want to exit.
        if(input_flag == 0 && strcmp(word_buffer, "EXIT") == 0)
        {
          exit_flag = 1;
          break;
        }
        // Treat the first word as a begining of a new sentence given it has to start with a capital.
        if(first_word_flag == 1 &&  word_buffer[0] >= 'A' && word_buffer[0] <= 'Z')
        {
         sentence_flag = 1;

         first_word_flag = 0;
        }

        // if statement for dealing with a capital word after a "." or "?" or "!" or "\n".
        if(cap_word_flag == 1 && word_buffer[0] >= 'A' && word_buffer[0] <= 'Z')
        {
          //Markes a sentence_flag.
          sentence_flag = 1;
          // cap_word_flag resets to 0 until the next sentence stop.
          cap_word_flag = 0;
        }
        // if "-c" is pressed and case_flag is on, we lowercase every word in the input_file.
        if(case_flag == 1)
        {
          for (int j = 0; word_buffer[j] ; ++j)
          {
            word_buffer[j] = tolower(word_buffer[j]);
          }
        }

        // if there is a new sentence and the case flag isnt on we test that word for both lower case and normal case to see if it is correct or not.
        if(sentence_flag == 1 && case_flag != 1)
        {
          // We make a new word to copy our buffer into and we allocate space for it.
          char *lower_case_word_buffer = malloc(i * sizeof(char) + 1);
          //copy
          strcpy(lower_case_word_buffer, word_buffer);

          // We lower it.
          lower_case_word_buffer[0] = tolower(lower_case_word_buffer[0]);

          // Compare them against the dictionary and see if they are correct or not. if they are wrong they will return 0.
          if(strlen(word_buffer) > 0 && binary_dictionary_search(dictionary_array, lower_case_word_buffer, dictionary_words) == 0 && binary_dictionary_search(dictionary_array, word_buffer, dictionary_words) == 0)
          {
            //If our output flag is on, we print it on the output file.
            if(output_flag)
            {
              fprintf(output_file, "The word '%s' is wrong and is on line %d\n", word_buffer, line_count);
              exit_flag = 2;
            }
            //If not, then we print to console.
            else
            {
              printf("The word '%s' is wrong and is on line %d\n", word_buffer, line_count);
              exit_flag = 1;
            }
            // We free the space allocated for the lower case word.
            free(lower_case_word_buffer);
          }
        }
        // If the word isnt a start of a new sentence, then we just compare it to the dictionary by how the word it is on itself
        // and we don't modify it.
        else if(strlen(word_buffer) > 0 && binary_dictionary_search(dictionary_array, word_buffer, dictionary_words) == 0)
        {
          if(output_flag)
          {
            fprintf(output_file, "The word '%s' is wrong and is on line %d\n", word_buffer, line_count);
            exit_flag = 2;
          }

          else
          {
            printf("The word '%s' is wrong and is on line %d\n", word_buffer, line_count);
            exit_flag = 1;
          }
        }

        // If there is a "\n" character in the txt file, add the counter by one to tell which line you are on.
        if(c == '\n')
        {
          line_count++;
        }

        // Reset the sentence_flag back to 0 so it doesn't treat every word as a start of a sentence.
        sentence_flag = 0;

        // If these are encountered, then the cap_word_flag will be turned on, and the next word will be a begining of a new word.
        if(c == '\n' || c == '?' || c == '!' || c == '.')
        {
          cap_word_flag = 1;
        }

        // reset the word_buffer back to 0 and have the next word buffered into it.
        i = 0;

      }
    }
    // We close input file once we are done with it.
    fclose(input_file);

    // And now we have to release the dictionary_array, we first have to free all the memory placed in each index,
    // and then we free the array itself.
    for(int i = 0; i < dictionary_words; i++)
  	{
  		free(dictionary_array[i]);
  	}
  	free(dictionary_array);

  // Exit flags depending on what operation you have done.
  if(exit_flag == 1)
  {
    printf("\n");
    printf("Thanks for using Spell!\n");
    printf("Exitng Spell...\n");
    printf("Copyright Darwon 2017.\n");
  }
  else if(exit_flag == 2)
  {
    printf("\n");
    printf("Output file has succesfully been processed!\n");
    printf("Thanks for using Spell!\n");
    printf("Exitng Spell...\n");
    printf("Copyright Darwon 2017.\n");
  }

  return 0;
}
