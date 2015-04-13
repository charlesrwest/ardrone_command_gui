#ifndef  PROCESSMANAGERTHREADHPP
#define PROCESSMANAGERTHREADHPP

#include<QThread>
#include<QApplication>
#include "processControlFunctions.hpp"

/*
This class is responsible for making sure that there is a roscore, ardrone_autonomy and ardrone_command process running and restarting them if needed.
*/
class processManagerThread : public QThread
{
Q_OBJECT

public:
/*
This function initializes the processManagerThread.
@param inputParent: This is a pointer to the parent QT object (for cascade delete purposes).
*/
processManagerThread(QObject *inputParent = nullptr);



/*
This function cleans up the object and waits for the thread to stop running before returning.
*/
~processManagerThread();

public slots:
/*
This function kills and restarts ardrone_command, ardrone_autonomy and roscore (in that order).  The associated signals are emitted as things come on and off line.
*/
void restartROSCoreAndAssociatedProcesses();

/*
This function kills and restarts ardrone_command, ardrone_autonomy (in that order).  The associated signals are emitted as things come on and off line.
*/
void restartARDroneAutonomyAndAssociatedProcesses();

/*
This function kills and restarts ardrone_command.  The associated signals are emitted as things come on and off line.
*/
void restartARDroneCommandAndAssociatedProcesses();

/*
This function terminates ardrone_command, ardrone_autonomy and roscore.
*/
void killROSCoreAndAssociatedProcesses();

/*
This function emits a new nodesOnline signal every time the status of one of the nodes changes.
@param inputChangeStatus: A largely ignored parameter
*/
void handleNodesChanges(bool inputChangeStatus);

signals:
/*
Emits text indicating status of the three nodes when something changes.
*/
void nodesOnline(const QString &);

/*
This signal is emitted when the status of the roscore process changes.
*/
void rosCoreStatusChanged(bool ROSCoreOnline);

/*
This signal is emitted when the status of the ardrone_autonomy process changes.
*/
void ARDroneAutonomyStatusChanged(bool ARDroneAutonomyOnline);

/*
This signal is emitted when the status of the ardrone_command process changes.
*/
void ARDroneCommandStatusChanged(bool ARDroneCommandOnline);

protected:
bool roscoreOnline;
bool ardroneAutonomyOnline;
bool ardroneCommandOnline;

/*
This function is the code that is run in the seperate thread.  It is responsible for managing the processes and emitting signals via an event loop.
*/
void run() Q_DECL_OVERRIDE;

/*
This function is called periodically to check the status of the monitored processes and take appropriate action.
@param inputTimeEvent: The timer event that caused this function to be called
*/
void timerEvent(QTimerEvent *inputTimerEvent) Q_DECL_OVERRIDE;
};








#endif 
