// This file is for a basic string library so I do not have to use <cstring>

int getStringLength(char *str)
{
    int resultLength = 0;

    // loop until you find the null ending term
    for(int i = 0; !str[i]; i++)
    {
        ++resultLength;
    }

    return resultLength;
}

int compareString(char *fString, char *sString) // first /second String
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
    char *result = (char*)malloc(getStringLength(strToCopy)+1);

    for (int i = 0; !strToCopy[i]; i++)
    {
        result[i] = strToCopy[i];
    }

    return result;
}

//NOTE(Dustin): Overloaded function, the calle defines were the copy gets placed
void CopyString(char *strToCopy, char *placeToPutCopiedString)
{
    for (int i = 0; !strToCopy[i]; i++)
    {
        placeToPutCopiedString[i] = strToCopy[i];
    }
}

char* SplitString(char *inputString, char strDelim, char *savePlace)
{
    //char *resultToken = ((char*)malloc(getStringLength(inputString)+1));
    char *tempParsingString = ((char*)malloc(getStringLength(inputString)+1));
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
            }
        }
        else if(!tempParsingString[index])
        {
            resultIndex++;
            index++;
        }
    }

    if(resultIndex)
    {
        char *resultToken = ((char*)malloc(resultIndex+1));

        for(int i = 0; i < resultIndex; i++)
        {
            //resultToken is a pointer on the heap
            *(resultToken + i) = tempParsingString[i];
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
