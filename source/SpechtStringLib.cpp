// This file is for a basic string library so I do not have to use <cstring>

int getStringLength(char *str)
{
    int resultLength = 0;

    // loop until you find the null ending term
    for(int i = 0; str[i]; i++)
    {
        ++resultLength;
    }
    return resultLength;
}

void clearTempStringsToNull(char *str)
{
    int length = getStringLength(str);
    for(int i = 0; i < length; i++)
    {
        str[i] = 0;
    }
}

//TODO: make another compreString that is case insensitive
int compareString(char *fString, char *sString) // first/second String
{
    int firstStringLength = getStringLength(fString);

    if(firstStringLength != getStringLength(sString))
    {
        return 0;
    }

    for(int index = 0; index <= firstStringLength; index++)
    {
        if(fString[index] == sString[index])
        { }
        else
        { return 0; }
    }
    return 1;
}

//NOTE(Dustin): You will have to free this memory if you use this function
char* CopyString(char *strToCopy)
{
    char *result = (char*)calloc(getStringLength(strToCopy)+1, sizeof(char));
    //clearTempStringsToNull(result);

    for (int i = 0; strToCopy[i]; i++)
    {
        result[i] = strToCopy[i];
    }
    return result;
}
// if the end user knows the length they can pass it instead of my getting it

char* CopyString(char *strToCopy, int lengthOfStrToCopy)
{
    char *result = (char*)calloc(lengthOfStrToCopy+1,sizeof(char));
    //clearTempStringsToNull(result);

    for (int i = 0; strToCopy[i]; i++)
    {
        result[i] = strToCopy[i];
    }
    return result;
}

//NOTE(Dustin): Overloaded function, the calle defines were the copy gets placed
void CopyString(char *strToCopy, char *placeToPutCopiedString)
{
    for (int i = 0; strToCopy[i]; i++)
    {
        placeToPutCopiedString[i] = strToCopy[i];
    }
}

//NOTE(Dustin): Enduser needs to free the resultstring
char* CatString(char *originString, char *strToCat)
{
    int originLength = getStringLength(originString);
    int catStrLength = getStringLength(strToCat);
    int outstringLength = (originLength + catStrLength);
    int catStrIndex = 0;

    char *resultString = ((char*)calloc(outstringLength+1, sizeof(char)));
    //clearTempStringsToNull(resultString);

    for(int index = 0; index < outstringLength; index++)
    {
        if(index < originLength)
        {
            resultString[index] = originString[index];
        }
        else
        {
                resultString[index] = strToCat[catStrIndex];
                catStrIndex++;
        }
    }
    return resultString;
}

//Lets the enduser mangage the memory for the outputstring
void CatString(char *originString, char *strToCat, char *outputString)
{
    int originLength = getStringLength(originString);
    int catStrLength = getStringLength(strToCat);
    int outstringLength = (originLength + catStrLength);
    int catStrIndex = 0;

    for(int index = 0; index < outstringLength; index++)
    {
        if(index < originLength)
        {
            outputString[index] = originString[index];
        }
        else
        {
            if (index < catStrLength)
            {
                outputString[index] =strToCat[catStrIndex];
                catStrLength++;
            }
            else
            {
                // How did you get here
            }
        }
    }
}

//Lets the enduser pass in the lengths if he has them from something prior
char* CatString(char *originString, int originLength, char *strToCat, int catStrLength)
{
    int catStrIndex = 0;
    char *resultString = ((char*)calloc((originLength + catStrLength) + 1, sizeof(char)));
    //clearTempStringsToNull(resultString);

    for(int index = 0; index <= (originLength + catStrLength); index++)
    {
        if(index <= originLength)
        {
            resultString[index] = originString[index];
        }
        if (index <= catStrLength)
        {
            resultString[index] = strToCat[catStrIndex];
            catStrLength++;
        }
    }
    return resultString;
}

//TODO: create a overload of this that lets user mangage all the mermory allocs
char* SplitString(char *inputString, char strDelim, char *savePlace)
{
    //char *resultToken = ((char*)malloc(getStringLength(inputString)+1));
    char *tempParsingString = ((char*)calloc(getStringLength(inputString)+1, sizeof(char)));
    //clearTempStringsToNull(tempParsingString);
    bool isParsingStringToDelim = true;
    int index = 0;
    int resultIndex = 0;

    if(inputString) // see if null so we know to use the savePlace as the start
    {
        CopyString(inputString, tempParsingString);
        clearTempStringsToNull(savePlace);
    }
    else
    {
        CopyString(savePlace, tempParsingString);
    }

    while (isParsingStringToDelim)
    {
        //TODO: make this take multiple possible delim characters
        if(tempParsingString[index] == strDelim)
        {
            isParsingStringToDelim = false;
            index++;

            for(int i = 0; tempParsingString[(index)]; i++)
            {
                savePlace[i] = tempParsingString[index];
                index++;
            }
        }
        else if(tempParsingString[index])
        {
            resultIndex++;
            index++;
        }
    }

    if(resultIndex)
    {
        char *resultToken = ((char*)calloc(resultIndex+1, sizeof(char)));
        //clearTempStringsToNull(resultToken);

        for(int i = 0; i < resultIndex; i++)
        {
            //resultToken is a pointer on the heap
            resultToken[i] = tempParsingString[i];
        }

        free(tempParsingString);
        return resultToken;
    }
    else
    {
        free(tempParsingString);
        return NULL;
    }
}

void SplitString(char *inputString, char *outputString ,char strDelim, char *savePlace)
{
    //char *resultToken = ((char*)calloc(getStringLength(inputString)+1));
    char *tempParsingString = ((char*)calloc(getStringLength(inputString)+1, sizeof(char)));
    //clearTempStringsToNull(tempParsingString);
    bool isParsingStringToDelim = true;
    int index = 0;
    int resultIndex = 0;

    if(inputString) // see if null so we know to use the savePlace as the start
    {
        CopyString(inputString, tempParsingString);
    }
    else
    {
        CopyString(savePlace, tempParsingString);
    }

    while (isParsingStringToDelim)
    {
        //TODO: make this take multiple possible delim characters
        if(tempParsingString[index] == strDelim)
        {
            isParsingStringToDelim = false;
            index++;

            for(int i = 0; tempParsingString[(index)]; i++)
            {
                savePlace[i] = tempParsingString[index];
                index++;
            }
        }
        else if(tempParsingString[index])
        {
            resultIndex++;
            index++;
        }
    }

    if(resultIndex)
    {

        for(int i = 0; i < resultIndex; i++)
        {
            outputString[i] = tempParsingString[i];
        }

        free(tempParsingString);
    }
    else
    {
        free(tempParsingString);
    }
}
