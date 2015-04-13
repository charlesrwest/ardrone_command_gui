#ifndef  ARDRONECOMMANDGUIHPP
#define ARDRONECOMMANDGUIHPP

#include<QMainWindow>
#include "ui_ardroneCommandGuiTemplate.h"
#include "processManagerThread.hpp"

class ardroneCommandGUI : public QMainWindow, public Ui::ardroneCommandGuiTemplate
{
Q_OBJECT

public:
/*
This function sets up the class, initializes the GUI, creates the ROS node and attempts to start getting information from the AR Drone.
*/
ardroneCommandGUI();





//public slots:


private:
//QVector<QLabel *> voteSliderLabels;
processManagerThread managerThread; //ROS node manager
};





#endif
