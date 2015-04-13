#ifndef  PROCESSCONTROLFUNCTIONSHPP
#define PROCESSCONTROLFUNCTIONSHPP

#include<vector>
#include<string>
#include<tuple>
#include <proc/readproc.h>
#include <sys/types.h>
#include <unistd.h>
#include<cstring>


/*
This function gives a list of the names of all running commands and their associated PIDs.
@return: A vector of std::pair s of form <commandName, PID>
*/
std::vector<std::pair<std::string, int> > getListOfActiveProcesses();

/*
This function checks if a given command is currently running or not.
@param inputCommandToFind: The command substring to search for among the active processes
@return: True if the command is running and false otherwise
*/
bool commandIsRunning(const std::string &inputCommandToFind);

/*
This function starts the given command and then checks to make sure it is running.
@param inputCommandToStart: A string indicating the command to run
@return: 1 if successful and 0 otherwise
*/
int startCommand(const std::string inputCommandToStart);

/*
This function kills any processes that are currently running and contain the given substring.
@param inputCommandToKill: The string indicating the command
@return: 1 if successful and 0 otherwise
*/
int killCommand(const std::string &inputCommandToKill);

/*
This function kills any processes that are currently running and contain the given substring using -9 signal option
@param inputCommandToKill: The string indicating the command
@return: 1 if successful and 0 otherwise
*/
int killCommandHard(const std::string &inputCommandToKill);










#endif 
