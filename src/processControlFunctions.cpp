#include "processControlFunctions.hpp"

/*
This function gives a list of the names of all running commands and their associated PIDs.
@return: A vector of std::pair s of form <commandName, PID>
*/
std::vector<std::pair<std::string, int> > getListOfActiveProcesses()
{
std::vector<std::pair<std::string, int> > valuesToReturn;

PROCTAB* proc = openproc(PROC_FILLSTAT);

proc_t proc_info;
memset(&proc_info, 0, sizeof(proc_info));
while (readproc(proc, &proc_info) != NULL) 
{
valuesToReturn.push_back(std::pair<std::string, int>(std::string(proc_info.cmd), proc_info.tid));
}

closeproc(proc); //Add scope guard at some point

return valuesToReturn;
}


/*
This function checks if a given command is currently running or not.
@param inputCommandToFind: The command substring to search for among the active processes
@return: True if the command is running and false otherwise
*/
bool commandIsRunning(const std::string &inputCommandToFind)
{
std::vector<std::pair<std::string, int> > runningProcessesList;
runningProcessesList = getListOfActiveProcesses();

for(int i=0; i<runningProcessesList.size(); i++)
{
if(runningProcessesList[i].first.find(inputCommandToFind) != std::string::npos)
{
return true; //Found the command
}
}

return false; //Didn't find the command
}

/*
This function starts the given command and then checks to make sure it is running.
@param inputCommandToStart: A string indicating the command to run
@return: 1 if successful and 0 otherwise
*/
int startCommand(const std::string inputCommandToStart)
{

if(commandIsRunning(inputCommandToStart) )
{
return 1; //Command is already running
}

//Try to start ROS core
system((inputCommandToStart+" &").c_str());
sleep(3);

return 1;
}

/*
This function kills any processes that are currently running and contain the given substring.
@param inputCommandToKill: The string indicating the command
@return: 1 if successful and 0 otherwise
*/
int killCommand(const std::string &inputCommandToKill)
{
std::vector<std::pair<std::string, int> > runningProcessesList;
runningProcessesList = getListOfActiveProcesses();

int selfID = getpid();

for(int ii=0; ii<3 && commandIsRunning(inputCommandToKill); ii++)
{

for(int i=0; i<runningProcessesList.size(); i++)
{
if(runningProcessesList[i].first.find(inputCommandToKill) != std::string::npos && runningProcessesList[i].second != selfID) //Avoid suicide
{
system((std::string("kill ") + std::to_string(runningProcessesList[i].second)).c_str()); //Found the command, so kill it
sleep(1);
}
}

}

return !commandIsRunning(inputCommandToKill);
} 

/*
This function kills any processes that are currently running and contain the given substring using -9 signal option
@param inputCommandToKill: The string indicating the command
@return: 1 if successful and 0 otherwise
*/
int killCommandHard(const std::string &inputCommandToKill)
{
std::vector<std::pair<std::string, int> > runningProcessesList;
runningProcessesList = getListOfActiveProcesses();

int selfID = getpid();

for(int ii=0; ii<3 && commandIsRunning(inputCommandToKill); ii++)
{

for(int i=0; i<runningProcessesList.size(); i++)
{
if(runningProcessesList[i].first.find(inputCommandToKill) != std::string::npos && runningProcessesList[i].second != selfID) //Avoid suicide
{
system((std::string("kill -9 ") + std::to_string(runningProcessesList[i].second)).c_str()); //Found the command, so kill it
sleep(1);
}
}

}

return !commandIsRunning(inputCommandToKill);
}
