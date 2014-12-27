// This file is for a basic string library so I do not have to use <cstring>

char* CopyString(char *strToCopy)
{
    char *result = "";

    for (int i = 0; !strToCopy[i]; i++)
    {
        result[i] = strToCopy[i];
    }

    return result;
}

char* SplitString(char *inputString, char strDelim, char *savePlace)
{
    char *resultToken = "";
    char *tempParsingString
    bool isParsingStringToDelim = true;
    int index = 0;
    int resultIndex = 0;

    if(inputString) // see if null so we know to use the savePlace as the start
    {
        tempParsingString = CopyString(inputString);
    }
    else
    {
        tempParsingString = CopyString(savePlace);
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
