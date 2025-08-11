#ifndef __LBYEC2B_H__
#define __LBYEC2B_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**Converts string into Long Datatype
 * Arguments:
 *     word = The input string to be converted
 *     rowNum = The row number of the input string from the document
 *     columnNum = The column number of the input string from the document
 * Returns:
 *      If successful, it would return string into the long format
 *      If unsuccessful, produces an error prompt, then returns 0
 * Note:
 *      long allows a very long integer.
 */
long convertLong(char *word, int rowNum, int columnNum)
{

    char *endWord;
    long number = 0; //Allows large integers
    number = strtol(word, &endWord, 0);

    //If start & end location of the pointer is the same, then conversion not successful
    if (word == endWord)
    {
        //You can have some prompt here to catch some erros in conversion.
        //Just uncomment below. Do note: Please comment it again during submission
        // fprintf(stderr, "Row %d, Column %d: Unsuccesful Conversion %s to long\n", rowNum, columnNum, word);
    }
    return number;
}

/**Converts string into double Datatype
 * Arguments:
 *     word = The input string to be converted
 *     rowNum = The row number of the input string from the document
 *     columnNum = The column number of the input string from the document
 * Returns:
 *      If successful, it would return string into the double format
 *      If unsuccessful, produces an error prompt, then returns 0
 * Note:
 *      double is a very long float.
 */
double convertDouble(char *word, int rowNum, int columnNum)
{
    char *endWord;
    double number = 0.0; //Allows large floats (numbers with decimal point)
    number = strtod(word, &endWord);

    //If start & end location of the pointer is the same, then conversion not successful
    if (word == endWord)
    {
        //You can have some prompt here to catch some erros in conversion.
        //Just uncomment below. Do note: Please comment it again during submission
        // fprintf(stderr, "Row %d, Column %d: Unsuccesful Conversion of %s to double\n", rowNum, columnNum, word);
    }
    return number;
}

/**Converts string into datetime structure
 * Arguments:
 *     word = The input string to be converted
 *     rowNum = The row number of the input string from the document
 *     columnNum = The column number of the input string from the document
 * Returns:
 *      If successful, it would return datetime into the tm structure format
 *      If unsuccessful, produces an error prompt, then returns 0
 * Note:
 *      Assumes the ff format: YYYY-MM-DD HH:MM:SS
 *      e.g 2020-08-04 17:53:15
 * Reference:
 *      http://www.cplusplus.com/reference/ctime/tm/
 */
struct tm convertDatetime(char *word, int rowNum, int columnNum)
{
    struct tm resultDatetime = {0}; //initialize to zero

    int year, month, day, hour, minute, second;

    //If successful, it would return the number of read variables
    if (sscanf(word, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minute, &second) == 6)
    {
        resultDatetime.tm_year = year - 1900; //Years since 1900
        resultDatetime.tm_mon = month - 1;    //We start counting at zero so reduce 1
        resultDatetime.tm_mday = day;
        resultDatetime.tm_hour = hour;
        resultDatetime.tm_min = minute;
        resultDatetime.tm_sec = second;
    }
    else
    {
        //You can have some prompt here to catch some erros in conversion.
        //Just uncomment below. Do note: Please comment it again during submission
        // fprintf(stderr, "Row %d, Col %d: Cannot convert input %s into the given format\n", rowNum, columnNum, word);
    }
    return resultDatetime;
}

/**Converts string into date structure
 * Arguments:
 *     word = The input string to be converted
 *     rowNum = The row number of the input string from the document
 *     columnNum = The column number of the input string from the document
 * Returns:
 *      If successful, it would return date into the tm structure format
 *      If unsuccessful, produces an error prompt, then returns 0
 * Note:
 *      Assumes the ff format: YYYY-MM-DD
 *      e.g 2020-08-04
 * Reference:
 *      http://www.cplusplus.com/reference/ctime/tm/
 */
struct tm convertDate(char *word, int rowNum, int columnNum)
{
    struct tm resultDate = {0}; //initialize to zero

    int year, month, day;

    //If successful, it would return the number of read variables
    if (sscanf(word, "%4d-%2d-%2d", &year, &month, &day) == 3)
    {
        resultDate.tm_year = year - 1900; //Years since 1900
        resultDate.tm_mon = month - 1;    //We start counting at zero so reduce 1
        resultDate.tm_mday = day;
    }
    else
    {
        //You can have some prompt here to catch some erros in conversion.
        //Just uncomment below. Do note: Please comment it again during submission
        // fprintf(stderr, "Row %d, Col %d: Cannot convert input %s into the given format\n", rowNum, columnNum, word);
    }
    return resultDate;
}

#endif