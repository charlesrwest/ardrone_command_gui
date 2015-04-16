 #include "ardroneCommandGUI.hpp"



/*
This function sets up the class, initializes the GUI, creates the ROS node and attempts to start getting information from the AR Drone.
*/
ardroneCommandGUI::ardroneCommandGUI()
{
qRegisterMetaType<command>("command");

//Populate map
mapKeyToCommandSet[std::string("Take Off, Fly Rectangle and Land")]    = generateTakeOffFlyRectangleAndLandCommands();
mapKeyToCommandSet[std::string("Take off, Hover over spot and Land")] = generateTakeOffHoverOverSpotAndLandCommands();

//Make window
setupUi(this);

//Start threads
managerThread.start();
rosSubscriber.start();

//Populate maneuver combobox
for(std::map<std::string, std::vector<command> >::iterator iter = mapKeyToCommandSet.begin(); iter != mapKeyToCommandSet.end(); iter++)
{
maneuverComboBox->addItem(QString(iter->first.c_str()), QVariant(0));
}

//Connect nodes online label to get information about the node statuses
connect(&managerThread, SIGNAL(nodesOnline(const QString &)), ROSNodesStatusLabel, SLOT(setText(const QString &)));

connect(&managerThread, SIGNAL(ARDroneNetworkConnectionStatus(const QString &)), networkConnectionStatus, SLOT(setText(const QString &)));


//Bind navdata messages
connect(&rosSubscriber, SIGNAL(droneState(const QString &)), flyingLandedLabel, SLOT(setText(const QString &)));

connect(&rosSubscriber, SIGNAL(velocityX(double)), xVelocityLabel, SLOT(setNum(double)));
connect(&rosSubscriber, SIGNAL(velocityY(double)), yVelocityLabel, SLOT(setNum(double)));
//connect(&rosSubscriber, SIGNAL(velocityZ(double)), zVelocityLabel, SLOT(setNum(double)));

connect(&rosSubscriber, SIGNAL(tiltX(double)), xTiltLabel, SLOT(setNum(double)));
connect(&rosSubscriber, SIGNAL(tiltY(double)), yTiltLabel, SLOT(setNum(double)));
connect(&rosSubscriber, SIGNAL(tiltZ(double)), zTiltLabel, SLOT(setNum(double)));

connect(&rosSubscriber, SIGNAL(altitude(int)), altitudeLabel, SLOT(setNum(int)));

connect(&rosSubscriber, SIGNAL(batteryStatus(double)), batteryStatusLabel, SLOT(setNum(double)));


//Bind command messages
connect(&rosSubscriber, SIGNAL(commandStatus(QString)), currentCommandLabel, SLOT(setText(const QString &)));

//Bind camera image messages
connect(&rosSubscriber, SIGNAL(cameraImage(QPixmap)), videoStreamLabel, SLOT(setPixmap(const QPixmap &)));

//Connect buttons
connect(takeOffPushButton, SIGNAL(clicked(bool)), &rosSubscriber, SLOT(sendTakeoffCommand(bool)));
connect(landAfterFinishingPushButton, SIGNAL(clicked(bool)), &rosSubscriber, SLOT(sendLandAfterFinishingCommand(bool)));
connect(landImmediatelyPushButton, SIGNAL(clicked(bool)), &rosSubscriber, SLOT(sendLandImmediatelyCommand(bool)));
connect(executeManeuverPushButton, SIGNAL(clicked(bool)), this, SLOT(generateARDroneCommandSignal(bool)));

//Connect command sending interfaces
connect(this, SIGNAL(ARDroneCommand(command)), &rosSubscriber, SLOT(sendARDroneCommand(command)));
}

/*
This function creates ardrone command signals based on the current value of the combobox.
*/
void ardroneCommandGUI::generateARDroneCommandSignal(bool inputIgnored)
{
if(mapKeyToCommandSet.count(std::string(maneuverComboBox->currentText().toUtf8().constData())) == 0)
{
return; //Command set not found, so ignore
} 

for(int i=0; i < mapKeyToCommandSet[std::string(maneuverComboBox->currentText().toUtf8().constData())].size(); i++)
{
emit ARDroneCommand(mapKeyToCommandSet[std::string(maneuverComboBox->currentText().toUtf8().constData())].at(i)); //Emit each command as a signal
}
}

/*
This function generates the commands to execute a maneuver.
@return: The command set to execute
*/
std::vector<command> ardroneCommandGUI::generateTakeOffFlyRectangleAndLandCommands()
{
std::vector<command> commands;

command commandWait;
commandWait.setWaitCommand(2.0);
commands.push_back(commandWait);


//Make commands to send
command commandTakeoff;
commandTakeoff.setTakeoffCommand();
commands.push_back(commandTakeoff);


command commandSetTargetAltitude;
commandSetTargetAltitude.setTargetAltitudeCommand(500.0);
commands.push_back(commandSetTargetAltitude);

command commandWaitUntilTargetAltitudeReached;
commandWaitUntilTargetAltitudeReached.setWaitUntilAltitudeReached(10.0);
commands.push_back(commandWaitUntilTargetAltitudeReached);

command commandWaitForQRCode;
commandWaitForQRCode.setWaitUntilSpecificQRCodeIsSpottedCommand("BigQRCode", 3.0);
commands.push_back(commandWaitForQRCode);

command commandLookAtQRCodePoint;
commandLookAtQRCodePoint.setMaintainOrientationTowardSpecificQRCode("BigQRCode");
commands.push_back(commandLookAtQRCodePoint);

command commandGoToQRCodePoint;
commandGoToQRCodePoint.setMaintainPositionAtSpecificQRCodePoint("BigQRCode", .5, 0.0, 3.0+.5);
commands.push_back(commandGoToQRCodePoint);



command QRCodePointWait1; QRCodePointWait1.setWaitUntilPositionAtSpecificQRCodePointReachedCommand(100.0);
commands.push_back(QRCodePointWait1);

command commandGoToQRCodePoint2;
commandGoToQRCodePoint2.setMaintainPositionAtSpecificQRCodePoint("BigQRCode", .5, 0.0, 3.0-.5);
commands.push_back(commandGoToQRCodePoint2);

commands.push_back(QRCodePointWait1);


command commandGoToQRCodePoint3;
commandGoToQRCodePoint3.setMaintainPositionAtSpecificQRCodePoint("BigQRCode", -.5, 0.0, 3.0-.5);
commands.push_back(commandGoToQRCodePoint3);

commands.push_back(QRCodePointWait1);


command commandGoToQRCodePoint4;
commandGoToQRCodePoint4.setMaintainPositionAtSpecificQRCodePoint("BigQRCode", -.5, 0.0, 3.0+.5);
commands.push_back(commandGoToQRCodePoint4);

commands.push_back(QRCodePointWait1);


command commandGoToQRCodePoint5;
commandGoToQRCodePoint5.setMaintainPositionAtSpecificQRCodePoint("BigQRCode", .5, 0.0, 3.0+.5);
commands.push_back(commandGoToQRCodePoint5);

commands.push_back(QRCodePointWait1);


command commandWait2;
commandWait2.setWaitCommand(2.0);
commands.push_back(commandWait2);

command commandCancelMaintainPositionAtQRCodePoint;
commandCancelMaintainPositionAtQRCodePoint.setCancelMaintainPositionAtSpecificQRCodePoint();
commands.push_back(commandCancelMaintainPositionAtQRCodePoint);


command commandCancelLookAtQRCodePoint;
commandCancelLookAtQRCodePoint.setCancelMaintainOrientationTowardSpecificQRCode();
commands.push_back(commandCancelLookAtQRCodePoint);

return commands;
}

/*
This function generates the commands to execute a maneuver.
@return: The command set to execute
*/
std::vector<command> ardroneCommandGUI::generateTakeOffHoverOverSpotAndLandCommands()
{
std::vector<command> commands;

command commandWait;
commandWait.setWaitCommand(2.0);
commands.push_back(commandWait);


//Make commands to send
command commandTakeoff;
commandTakeoff.setTakeoffCommand();
commands.push_back(commandTakeoff);


command commandSetTargetAltitude;
commandSetTargetAltitude.setTargetAltitudeCommand(500.0);
commands.push_back(commandSetTargetAltitude);

command commandWaitUntilTargetAltitudeReached;
commandWaitUntilTargetAltitudeReached.setWaitUntilAltitudeReached(10.0);
commands.push_back(commandWaitUntilTargetAltitudeReached);

command commandWaitForQRCode;
commandWaitForQRCode.setWaitUntilSpecificQRCodeIsSpottedCommand("BigQRCode", 3.0);
commands.push_back(commandWaitForQRCode);

command commandLookAtQRCodePoint;
commandLookAtQRCodePoint.setMaintainOrientationTowardSpecificQRCode("BigQRCode");
commands.push_back(commandLookAtQRCodePoint);

command commandGoToQRCodePoint;
commandGoToQRCodePoint.setMaintainPositionAtSpecificQRCodePoint("BigQRCode", 0.0, 0.0, 3.0+.5);
commands.push_back(commandGoToQRCodePoint);



command QRCodePointWait1; QRCodePointWait1.setWaitUntilPositionAtSpecificQRCodePointReachedCommand(100.0);
commands.push_back(QRCodePointWait1);

command commandWait2;
commandWait2.setWaitCommand(4.0);
commands.push_back(commandWait2);

command commandCancelMaintainPositionAtQRCodePoint;
commandCancelMaintainPositionAtQRCodePoint.setCancelMaintainPositionAtSpecificQRCodePoint();
commands.push_back(commandCancelMaintainPositionAtQRCodePoint);


command commandCancelLookAtQRCodePoint;
commandCancelLookAtQRCodePoint.setCancelMaintainOrientationTowardSpecificQRCode();
commands.push_back(commandCancelLookAtQRCodePoint);

return commands;
}
