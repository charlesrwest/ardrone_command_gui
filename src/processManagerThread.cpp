#include "processManagerThread.hpp"

/*
This function initializes the processManagerThread.
@param inputParent: This is a pointer to the parent QT object (for cascade delete purposes).
*/
processManagerThread::processManagerThread(QObject *inputParent) : QThread(inputParent)
{
this->moveToThread(this);

roscoreOnline = false;
ardroneAutonomyOnline = false;
ardroneCommandOnline = false;

//Connect slot to receive notice when one of the node statuses changes
connect(this, SIGNAL(rosCoreStatusChanged(bool)), this, SLOT(handleNodesChanges(bool)));
connect(this, SIGNAL(ARDroneAutonomyStatusChanged(bool)), this, SLOT(handleNodesChanges(bool)));
connect(this, SIGNAL(ARDroneCommandStatusChanged(bool)), this, SLOT(handleNodesChanges(bool)));
}



/*
This function cleans up the object and waits for the thread to stop running before returning.
*/
processManagerThread::~processManagerThread()
{
quit(); //Tell thread event loop to exit

killROSCoreAndAssociatedProcesses();
wait(); //Wait for thread to exit
}


/*
This function kills and restarts ardrone_command, ardrone_autonomy and roscore (in that order).  The associated signals are emitted as things come on and off line.
*/
void processManagerThread::restartROSCoreAndAssociatedProcesses()
{
killCommand("roscore");

roscoreOnline = false;
emit rosCoreStatusChanged(false);

while(startCommand("roscore") != 1)
{
}

roscoreOnline = true;
emit rosCoreStatusChanged(true);

//Restart adrone_command
restartARDroneAutonomyAndAssociatedProcesses();
}

/*
This function kills and restarts ardrone_command, ardrone_autonomy (in that order).  The associated signals are emitted as things come on and off line.
*/
void processManagerThread::restartARDroneAutonomyAndAssociatedProcesses()
{
killCommandHard("ardrone_driver");

ardroneAutonomyOnline = false;
emit ARDroneAutonomyStatusChanged(false);

while(startCommand("rosrun ardrone_autonomy ardrone_driver  _realtime_navdata:=True _navdata_demo:=0 _realtime_video:=True") != 1)
{
}


ardroneAutonomyOnline = true;
emit ARDroneAutonomyStatusChanged(true);

//Restart adrone_command
restartARDroneCommandAndAssociatedProcesses();
}

/*
This function kills and restarts ardrone_command.  The associated signals are emitted as things come on and off line.
*/
void processManagerThread::restartARDroneCommandAndAssociatedProcesses()
{
killCommandHard("ardrone_command");

ardroneCommandOnline = false;
emit ARDroneCommandStatusChanged(false);

while(startCommand("rosrun ardrone_command ardrone_command") != 1)
{
}

ardroneCommandOnline = true;
emit ARDroneCommandStatusChanged(true);
}

/*
This function terminates ardrone_command, ardrone_autonomy and roscore.
*/
void processManagerThread::killROSCoreAndAssociatedProcesses()
{
killCommandHard("ardrone_command");
ardroneCommandOnline = false;
emit ARDroneCommandStatusChanged(false);

killCommandHard("ardrone_driver");
ardroneAutonomyOnline = false;
emit ARDroneAutonomyStatusChanged(false);

killCommand("roscore");
roscoreOnline = false;
emit ARDroneAutonomyStatusChanged(false);
}

/*
This function emits a new nodesOnline signal every time the status of one of the nodes changes.
@param inputChangeStatus: A largely ignored parameter
*/
void processManagerThread::handleNodesChanges(bool inputChangeStatus)
{
if(roscoreOnline && ardroneAutonomyOnline && ardroneCommandOnline)
{
emit nodesOnline("ROS Status: Online");
}
else
{
emit nodesOnline("ROS Status: Offline");
}
}

/*
This function is the code that is run in the seperate thread.  It is responsible for managing the processes and emitting signals.
*/
void processManagerThread::run()
{


//Register a timer to make sure the processes will be checked on periodically
startTimer(1000); //Check every second


//Start event loop, handing slots and timer events
exec();
}
 

/*
This function is called periodically to check the status of the monitored processes and take appropriate action.
@param inputTimeEvent: The timer event that caused this function to be called
*/
void processManagerThread::timerEvent(QTimerEvent *inputTimerEvent)
{
//If ROS core isn't running, then start it (and associated processes)
if(!commandIsRunning("roscore"))
{
printf("roscore not running\n");
restartROSCoreAndAssociatedProcesses();
}

//If ardrone_autonomy isn't running, then start it (and associated processes)
if(!commandIsRunning("ardrone_driver"))
{
printf("ardrone_driver not running\n");
restartARDroneAutonomyAndAssociatedProcesses();
}

//If ardrone_autonomy isn't running, then start it (and associated processes)
if(!commandIsRunning("ardrone_command"))
{
printf("ardrone_command not running\n");
restartARDroneCommandAndAssociatedProcesses();
}

}
