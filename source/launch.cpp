// Launch.cpp is a command line utilitiy for launching Applications without
// a .bat script from a config file
// TODO: Write my own token parsing, and compare
#include <cstdio>
#include <string>
#include <stdlib.h>

#define internal static
#define local_persist static
#define global_variable static

struct AppPathPair
{
    char *application;
    char *path;
};

// TODO: Dynamicly store these so we don't have a hard limit and so we don't
// have to many
global_variable AppPathPair ParsingApps[100] = {};

internal AppPathPair
SplitLineToAppPathPair(char *str, char *delim = "=")
{
    AppPathPair curProccessingApp = {};
    char *saveptr; //just a place to save the rest of the line after the delim

    char *tempStr = str;
    char *token = strtok_s(tempStr, delim, &saveptr);

    //TODO: Make this less janky
    // This also assumes there is only 2 parts a application name and a
    // application path
    if(token)
    {
        printf("\nDEBUG | Application -> %s", token);
        curProccessingApp.application = token;

        token = strtok_s(NULL, delim, &saveptr);
        if(token)
        {
            printf("\nDEBUG | Path -> %s", token);
            curProccessingApp.path = token;
        }
    }
    else
    {
        printf_s("\nInvalid Token: %s", token);
    }
    return curProccessingApp;
}

internal int
CLConfigParser(char *configFile)
{
    // following if the current line in the config.cfg that I am trying to read
    // openTTD="C:\Program Files (x86)\OpenTTD\openttd.exe"
    // though when I debug the currentLine is only openTTD=\

    FILE *cfg = fopen(configFile, "r"); // open the config file read-only
    char currentLine[256] = {};
    int validLineCount = 0;

    if (cfg)
    {
        while(fgets(currentLine, 256, cfg))
        {
            ParsingApps[validLineCount] = SplitLineToAppPathPair((char *)&currentLine);
            validLineCount++;
        }

        fclose(cfg);
    }
    else
    {
        printf_s("\nThe config file was not found, please check the name : %s", configFile);
        fclose(cfg);
    }

    return validLineCount;
}

internal void
CLArgsParser(char *arg, int validAppCount)
{
    if(!strcmp(arg,"-h") || !strcmp(arg,"--help") || !strcmp(arg,"/?"))
    {
        printf("\n%s\n", arg);
        printf("THIS IS HELP\n");
        //TODO: Actually print some help for the end user
    }
    else
    {
        for(int i = 0; i < validAppCount; i++)
        {
            if(!strcmp(arg, ParsingApps[i].application))
            {
                //printf("\nPATH -> %s\n", ParsingApps[i].path);

                // String work to get everything in 1 string so system() can work
                char buffer[256];
                strcpy(buffer, "call ");
                strcat(buffer, ParsingApps[i].path);

                system(buffer);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc  > 0)
    {
        int validApplicationCount = CLConfigParser("config.cfg");
        if(validApplicationCount > 0)
        {
            char *cmdArg = argv[1];
            CLArgsParser(cmdArg, validApplicationCount);
        }
    }
    else
    {
        printf("\ninvalid argument count: must have 1 arg\n");
    }

    return 0;
}
