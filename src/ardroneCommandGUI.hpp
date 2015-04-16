#ifndef  ARDRONECOMMANDGUIHPP
#define ARDRONECOMMANDGUIHPP

#include<QMainWindow>
#include "ui_ardroneCommandGuiTemplate.h"
#include "processManagerThread.hpp"
#include "ROSSubscriberThread.hpp"
#include<vector>
#include<map>
#include "ardrone_command/command.hpp"



class ardroneCommandGUI : public QMainWindow, public Ui::ardroneCommandGuiTemplate
{
Q_OBJECT

public:
/*
This function sets up the class, initializes the GUI, creates the ROS node and attempts to start getting information from the AR Drone.
*/
ardroneCommandGUI();





public slots:

/*
This function creates ardrone command signals based on the current value of the combobox.
*/
void generateARDroneCommandSignal(bool inputIgnored);

signals:
/*
This signal emits commands for the ardrone to execute.
*/
void ARDroneCommand(command);

private:
/*
This function generates the commands to execute a maneuver.
@return: The command set to execute
*/
std::vector<command> generateTakeOffFlyRectangleAndLandCommands();

/*
This function generates the commands to execute a maneuver.
@return: The command set to execute
*/
std::vector<command> generateTakeOffHoverOverSpotAndLandCommands();

//QVector<QLabel *> voteSliderLabels;
ROSSubscriberThread rosSubscriber;
processManagerThread managerThread; //ROS node manager

std::map<std::string, std::vector<command> > mapKeyToCommandSet; //This map stores the commands to run for any given map key
};





#endif
