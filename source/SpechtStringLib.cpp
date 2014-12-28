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

//NOTE(Dustin): You will have to free this memory if you use this function
char* CopyString(char *strToCopy)
{
    char *result = (char*)mallac(getStringLength(strToCopy)+1);

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
    char *resultToken;
    char tempParsingString[getStringLength(inputString)];
    bool isParsingStringToDelim = true;
    int index = 0;
    int resultIndex = 0;

    if(inputString) // see if null so we know to use the savePlace as the start
    {
        CopyString(inputString, (char*)tempparsingstring);
    }
    else
    {
        CopyString(savePlace), (char*)tempparsingstring;
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
        elseif(!tempParsingString[index])
        {
            resultToken[resultIndex] = tempParsingString[index];

            resultIndex++;
            index++;
        }
        else
        {
            return inputString;
        }

    }
    return resultToken;
}
