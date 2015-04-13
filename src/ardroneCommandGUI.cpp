 #include "ardroneCommandGUI.hpp"

/*
This function sets up the class, initializes the GUI, creates the ROS node and attempts to start getting information from the AR Drone.
*/
ardroneCommandGUI::ardroneCommandGUI()
{
setupUi(this);
managerThread.start();

//Connect nodes online label to get information about the node statuses
connect(&managerThread, SIGNAL(nodesOnline(const QString &)), ROSNodesStatusLabel, SLOT(setText(const QString &)));
//nodesOnline
}
