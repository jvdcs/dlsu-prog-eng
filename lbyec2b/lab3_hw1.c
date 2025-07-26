#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "lbyec2b.h"
//Datetime is simply a shorcut to built-in struct tm
//Reference http://www.cplusplus.com/reference/ctime/tm/
typedef struct tm Datetime;

typedef struct EpiData
{
    //Make sure to change the fields below. The existing one only works on sample1.csv file
    //Write your fields below
    long id;
    char name[256];
    char email[256];
    char address[256];
    Datetime birthday;
    double fave;

} EpiData;

typedef struct Case
{
    long confirmed;
    long active;
    long recovered;
    long died;
} Case;

/**Counts Death on a specific age group
 * Arguments:
 *      report = A structure array that contains the data to be analyzed
 *      agegroup = The target age group in Five-year format (e.g. 50 - 54)
 *      N = contains the number of records from the given report
 * Returns:
 *      number of death records on a specific age group
 * Note:
 *      Return Data Type is long because confirmed cases may exceed limit of int (which 32 767)
 */
long countDiedByAgeGroup(EpiData *report, char *agegroup, int N)
{ //Write your code below

    return 0; //You can edit this
}

/**Compares whether two dates are equal or not
 * Arguments:
 *      src_date = the original date
 *      target_date = the target date
 * Returns:
 *      true if they are the same. False if they're not
 * Note:
 *      - Datetime is simply a shortcut to the built-in struct tm of C
 *      - In order to access the "fields" inside tm make sure to check struct tm documentations
 *      - It will only check year,month and day only. Does not include hour,minute, second
 * Reference:
 *      http://www.cplusplus.com/reference/ctime/tm/
 */
bool isDateEqual(Datetime src_date, Datetime target_date)
{                 //Write your code below
    return false; //you can edit this
}

/** Counts the confirmed cases on a specific region name on a specific date
 * Arguments:
 *      report = A structure array that contains the data to be analyzed
 *      region = The name of region that to be "searched" on.
 *      date = The data to be "searched" on in string format. (format: YYYY-MM-DD)
 *      N = contains the number of records from the given report
 * Returns:
 *      the count of confirmed cases on from the given region on a specific date
 * 
 * Note:
 *      This function will only work it is "exactly" the same as the region name
 *      If region name is misspelled, then this function will return a count of zero
 *      It assumes that the input date variable is in the format of YYYY-MM-DD.
 *      For the date, it would be based on DateRepConf column as mentioned from DOH's metadata
 *      This function uses isDateEqual function.
 */
double countRegionByPublishDate(EpiData *report, char *region, char *date, int N)
{               //Write your code below
    return 0.0; //You can edit this
}

/** Counts the confirmed cases on a specific region name
 * Arguments:
 *      report = A structure array that contains the data to be analyzed
 *      region = The name of region that to be "searched" on.
 *      N = contains the number of records from the given report
 * Returns:
 *      the count of confirmed cases on from the given region
 * 
 * Note:
 *      This function will only work it is "exactly" the same as the region name
 *      If region name is misspelled, then this function will return a count of zero
 */
long countRegion(EpiData *report, char *region, int N)
{             //Write your code below
    return 0; //You can edit this
}

/**Calculates the Total Cases similar to COVID19 Tracker.
 * It is able to calculate the ff: (a) Confirmed, (b) Active, (c) Died
 * 
 * Arguments:
 *      report = A structure array that contains the data to be analyzed
 *      N = contains the number of records from the given report
 * Returns:
 *      A Case Structure. 
 *      The Case Structure as defined above contains the ff fields:
 *            (a) confirmed (long)
 *            (b) active (long)
 *            (c) died (long)
 *            (d) recovered (long)
 * 
 * Note:
 *     - Make sure to initialize that count variable is initialized as 0. It helps to remove error.
 *     - Data Type of each field in Case is long because confirmed cases may exceed limit of int (which 32 767) 
*/
Case calcCases(EpiData *report, long N)
{
    //Initialize all fields of the struct Case with 0.
    Case count = {0, 0, 0, 0};
    //Write your code below

    return count; //You can edit this
}

/**Serves as the main "Manager" for different types of analysis
 * Shows also the prompt to help the user which type of analysis he wants
 * 
 * Arguments:
 *      report = A structure array that contains the data to be analyzed
 *      N = contains the number of records from the given report
 * Returns:
 *      No return.
 */
void analyzeData(EpiData *report, long N)
{
    int choice = 0;
    char region[256], date[256], ageGroup[256];
    Case totalCount;
    long count = 0;
    printf("Analysis Options:\n");
    printf("1. Total Confirmed Case\n");
    printf("2. Total Case By Region\n");
    printf("3. Total Case on Region by Publish Date\n");
    printf("4. Total Death by Age Group\n");
    printf("5. Exit\n");
    do
    {
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            totalCount = calcCases(report, N);
            printf("Confirmed: %ld, Active: %ld, Recovered: %ld, Died: %ld\n", totalCount.confirmed, totalCount.active, totalCount.recovered, totalCount.died);
        }
        else if (choice == 2)
        {
            printf("Enter Region: ");
            scanf(" %[^\n]s", region);
            count = countRegion(report, region, N);
            printf("Total count on %s is %ld\n", region, count);
        }
        else if (choice == 3)
        {
            printf("Enter Region: ");
            scanf(" %[^\n]s", region);
            printf("Enter Date[YYYY-MM-DD]: ");
            scanf(" %[^\n]s", date);
            count = countRegionByPublishDate(report, region, date, N);
            printf("Total count on %s published on %s is %ld\n", region, date, count);
        }
        else if (choice == 4)
        {
            printf("Enter Age Group (e.g. 50 to 54): ");
            scanf(" %[^\n]s", ageGroup);
            count = countDiedByAgeGroup(report, ageGroup, N);
            printf("Total count for agegroup %s is %ld\n", ageGroup, count);
        }

    } while (choice != 5);
}

/**parse the current string from a specific row number and column number into the right format/datatype
 * Arguments:
 *      word = it's current string that contains the data from a specific row number and column number of the csv file
 *      rowNum = specifies the row number of the provided word
 *      columnNum = specifies the column number of the provided word
 *      
 *      row = points to the current row of the output structure array. This is where the formatted word will be written on.
 * 
 * Returns:
 *      No return. But the output is written on row. It points to the current row of the ouput structure array.
 *      As row variable is a pointer, whichever data we write into it, will be automatically reflected. (aka. Pass-by-reference)
 */
void processWord(char *word, int rowNum, int columnNum, EpiData *row)
{
    /*Make sure to change the code below as it only works on sample1.csv. 
    Yes, you can delete the whole function except for function definiton above*/
    switch (columnNum)
    {
    case 1:
        row->id = convertLong(word, rowNum, columnNum); //Convert String to Long. Please check at lbyec2b.h
        printf("Sucessfully converted into a long datatype %ld\n", row->id);
        break;
    case 2:
        strcpy(row->name, word); //Copies string to another string. Ref: http://www.cplusplus.com/reference/cstring/strcpy/
        printf("Successfuly copied %s...\n", row->name);
        break;
    case 3:
        strcpy(row->email, word);
        printf("Successfuly copied %s...\n", row->email);
        break;
    case 4:
        strcpy(row->address, word);
        printf("Successfuly copied %s...\n", row->address);
        break;
    case 5:
        row->birthday = convertDate(word, rowNum, columnNum); //Convert String to Date. Please check at lbyec2b.h
        printf("Successfuly converted into tm struct %d/%d/%d...\n", row->birthday.tm_mon + 1, row->birthday.tm_mday, row->birthday.tm_year + 1900);
        break;
    case 6:
        row->fave = convertDouble(word, rowNum, columnNum); //Convert String to Date. Please check at lbyec2b.h
        printf("Successfuly coverted into double format %lf...\n", row->fave);
        break;
    default: //When can't be found, this is where you define the default. In this case, I want to do nothing
        break;
    }
}

/**Converts CSV file into the the output structure array
 * Arguments:
 *      filename = the filename of the csv file
 *      directory = the folder name on where the csv is stored
 *      report = the output structure array where the data from csv will be stored into
 * 
 * Returns:
 *      If conversion is successful, it will return the number of records on the CSV
 *      If unsucessful, it returns 0.
 */
long loadCSV(char filename[], char directory[], EpiData *report)
{
    FILE *fp;
    char buffer[2048];
    char word[2048];
    char token_pos = 0;
    int record_count = 0; //Current count of row
    int field_count = 0;  //Current count of column
    char *path;
    path = malloc((strlen(filename) + strlen(directory) + 1) * sizeof(char));
    strcpy(path, directory);
    strcat(path, "/");
    strcat(path, filename);
    fp = fopen(path, "r");

    if (!fp)
    {
        printf("Error reading CSV File. Make sure filename is correct.");
        return 0;
    }

    int isHeader = 1;
    //fgets gets 4096 characters on the pointed file. It will be stored on buffer
    //If fgets is successful, then we will continue with the loop
    //Else if it reaches end of file, then the loop stops
    //Note: At index 4096, fgets puts a null character
    //Asumes that the whole row AT MOST 4096 characters.
    while (fgets(buffer, 4096, fp))
    {

        //We assume to get the header at our first read, So we want to skip it.
        if (isHeader == 1)
        {
            isHeader = 0;
            continue;
        }

        //Let's start parsing the column
        field_count = 0;
        int i = 0;       //Index of the current character
        int isquote = 0; //0 means false
        do
        {
            word[token_pos] = buffer[i]; //Store current char on word
            token_pos++;

            if (!isquote && (buffer[i] == ',' || buffer[i] == '\n'))
            {
                word[token_pos - 1] = 0; //Terminate it to be formally considered as a string
                token_pos = 0;           //Reset index so give way for the next word on the next loop
                field_count += 1;        //Sets the column number
                processWord(word, record_count, field_count, report);
            }

            //In CSV spec, If you see a phrase enclosed in double quote, it is considered as one field
            //If current char is a double quote, and the next char is not a double quote
            if (buffer[i] == '"' && buffer[i + 1] != '"')
            {
                isquote = !isquote; //Invert the current status.
                token_pos--;        //In order not to include double quote on the actual word content
            }

            //In CSV spec, it allows a word enclosed in double quote to have double quote inside
            //If current char is double quote and the next one is also a double quote
            if (buffer[i] == '"' && buffer[i + 1] == '"')
            {
                i = i + 1; //So that we can only get one double quote.
            }

            i = i + 1;
        } while (buffer[i]); //Continue with the loop as long as it's a character.
        //However, when it sees a null character, it will stop.

        record_count += 1; //Increment record count by 1
        report++;          //Go to the next row of the report. Note: This is pointer arithmetic. Thus, you go to the next location.
    }

    fclose(fp);
    free(path);
    return record_count; //Reduce one to reduce the header
}

int main(void)
{
    //The variable to store all data here
    EpiData *report;
    report = (EpiData *)malloc(1000000 * sizeof(EpiData)); //max of 1,000,000 records

    //At this point, it loads sample1.csv, but this is not the data you want for covid!
    //Can you check what is the filename for the data of covid cases?
    long total = loadCSV("sample1.csv", "assets", report);

    analyzeData(report, total);

    //Free up the memory
    free(report);

    return 0;
}
