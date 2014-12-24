// Launch.cpp is a command line utilitiy for launching programings without a .bat

#include <cstdio>
#include <cstring>
#include <stdlib.h>

#define internal static
#define local_persist static
#define global_variable static

struct AppPathPair
{
	char *application;
	char *path;
};

// TODO: Dynamicly store these so we don't have a hard limit
global_variable AppPathPair ParsingApps[100] = {};

internal AppPathPair	// TODO: Stop Hacking void* and actually do this properly
SplitLineToAppPathPair(void *str, char *delim = "=")
{
	AppPathPair curProccessingApp = {};
    char *saveptr; //just a place to save the rest of the line after the delim
    char *token = strtok_s((char*)&str, delim, &saveptr);

	//TODO: Make this less janky
	if(token)
	{
		curProccessingApp.application = token;

		token = strtok_s((char*)&str, delim, &saveptr);
		if(token)
		{
			curProccessingApp.path = token;
		}
	}

	return curProccessingApp;
}

internal int
CLConfigParser(char *configFile)
{
	FILE *cfg = fopen(configFile, "r"); // open the config file read-only
	char currentLine[256] = {};
	int validLineCount = 0;

	if (cfg)
	{
		// TODO: Make this dynamic, and less complex
		while(!fscanf_s(cfg, "%[^\n]", &currentLine))
		{
			ParsingApps[validLineCount] = SplitLineToAppPathPair((void*)*currentLine);
			++validLineCount;
		}

		fclose(cfg);
	}
	else
	{
		printf("The config file was not found, please check the name : %s", configFile);
		fclose(cfg);
	}


	return validLineCount;
}

internal void
CLArgsParser(char *args[], int validAppCount)
{
	if(args[1] == "-h" || args[1] == "--help" || args[1] == "/?")
	{
		//TODO: Actually print some help for the end user
	}
	else
	{
		for(int i = 0; i <= validAppCount; i++)
		{
			if(args[1] == ParsingApps[i].application)
			{
				printf("I FOUND A MATCH TO THE PASSED ARGUMENT IN THE CONFIG FILE");
				system(ParsingApps[i].path);
			}
		}
	}

}

int
main(int argc, char *argv[])
{
	int validApplicationCount = CLConfigParser("config.cfg");
	if(validApplicationCount > 0)
	{
		CLArgsParser(argv, validApplicationCount);
	}

	return 0;
}
