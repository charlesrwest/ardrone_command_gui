#include "ROSSubscriberThread.hpp"


/*
This function initializes the ROSSubscriberThread.
@param inputParent: This is a pointer to the parent QT object (for cascade delete purposes).
*/
ROSSubscriberThread::ROSSubscriberThread(QObject *inputParent)
{
this->moveToThread(this);
qRegisterMetaType<command>("command");

}



/*
This function cleans up the object and waits for the thread to stop running before returning.
*/
ROSSubscriberThread::~ROSSubscriberThread()
{
quit(); //Tell thread event loop to exit
wait(); //Wait for thread to exit
ros::shutdown();
} 

/*
This function sends a command to ardrone_autonomy to tell the ardrone to take off.
*/
void ROSSubscriberThread::sendTakeoffCommand(bool input)
{
std_msgs::Empty emptyMessage;
takeOffPublisher.publish(emptyMessage);
}

/*
This function sends a command to ardrone_command to tell it to land after finishing any other commands it has received.
*/
void ROSSubscriberThread::sendLandAfterFinishingCommand(bool input)
{
std::vector<command> commands;

command commandLand;
commandLand.setLandingCommand();
commands.push_back(commandLand);

command commandCancelMaintainPositionAtQRCodePoint;
commandCancelMaintainPositionAtQRCodePoint.setCancelMaintainPositionAtSpecificQRCodePoint();
commands.push_back(commandCancelMaintainPositionAtQRCodePoint);


command commandCancelLookAtQRCodePoint;
commandCancelLookAtQRCodePoint.setCancelMaintainOrientationTowardSpecificQRCode();
commands.push_back(commandCancelLookAtQRCodePoint);

//Serialize and send commands
ardrone_command::commandInterface interface;
for(int i=0; i<commands.size(); i++)
{
auto commandMessage = commands[i].serialize();
ardrone_command::commandInterface::Request request;
request.command = commandMessage;

ardrone_command::commandInterface::Response response;

ros::service::call("/ardrone_command/commandInterface", request, response);
}
}

/*
This function sends a command to ardrone_autonomy to tell the ardrone to land now.
*/
void ROSSubscriberThread::sendLandImmediatelyCommand(bool input)
{
std_msgs::Empty emptyMessage;
landingPublisher.publish(emptyMessage);
}


/*
This function takes the given command and sends it to the AR Drone.
@param inputCommand: The command to send
*/
void ROSSubscriberThread::sendARDroneCommand(const command &inputCommand)
{
printf("I got called\n");

//copy command
command buffer = inputCommand;

//Serialize and send command
ardrone_command::commandInterface interface;
auto commandMessage = buffer.serialize();
ardrone_command::commandInterface::Request request;
request.command = commandMessage;

ardrone_command::commandInterface::Response response;

ros::service::call("/ardrone_command/commandInterface", request, response);
}


/*
This function is the code that is run in the seperate thread.  It is responsible for recieving ROS messages and forwarding commands.
*/
void ROSSubscriberThread::run()
{
//Register a timer to make sure the processes will be checked on periodically
startTimer(20); //Check every 20 millseconds

int buffer = 0;
ros::init(buffer, NULL, "ardrone_command_gui");

nodeHandle.reset(new ros::NodeHandle);

//Subscribe to the nav-data topic with a buffer size of 1000
navDataSubscriber = nodeHandle->subscribe("ardrone/navdata", 1000, &ROSSubscriberThread::handleNavData, this); 

//Subscribe to the video from the AR drone with a buffer size of 5
videoSubscriber = nodeHandle->subscribe("ardrone/front/image_raw", 5, &ROSSubscriberThread::handleImageUpdate, this); 

//Subscribe to what commands are being run
commandSubscriber = nodeHandle->subscribe("/ardrone_command/command_processing", 1000, &ROSSubscriberThread::handleCommandStatusInfoMessage, this);


//Create publisher to control takeoff
takeOffPublisher = nodeHandle->advertise<std_msgs::Empty>("/ardrone/takeoff", 1000);

//Create publisher to control landing
landingPublisher = nodeHandle->advertise<std_msgs::Empty>("/ardrone/land", 1000);

//Create publisher to control emergency stop
emergencyStopPublisher = nodeHandle->advertise<std_msgs::Empty>("/ardrone/reset", 1000);

//Start event loop, handing slots and timer events
exec();
}

/*
This function is called periodically to call ROS::spin().
@param inputTimeEvent: The timer event that caused this function to be called
*/
void ROSSubscriberThread::timerEvent(QTimerEvent *inputTimerEvent)
{
ros::spinOnce();//Take care of ROS callbacks
}

/*
This function is the callback that takes ROS navdata messages and sends signals based on that.
@param inputMessage: The  nav-data message to handle 
*/
void ROSSubscriberThread::handleNavData(const ardrone_autonomy::Navdata::ConstPtr &inputMessage)
{
emit tiltX(inputMessage->rotX);
emit tiltY(inputMessage->rotY);
emit tiltZ(inputMessage->rotZ);

emit altitude(inputMessage->altd);


emit batteryStatus(inputMessage->batteryPercent);

switch(inputMessage->state)
{
case 0:
emit droneState("UNKNOWN_STATE");
break;

case 1:
emit droneState("INITIALIZED");
break;

case 2:
emit droneState("LANDED");
break;

case 3:
case 7:
emit droneState("FLYING");
break;

case 4:
emit droneState("HOVERING");
break;

case 5:
emit droneState("TEST");
break;

case 6:
emit droneState("TAKING_OFF");
break;

case 8:
emit droneState("LANDING");
break;

case 9:
emit droneState("LOOPING");
break;
}


emit velocityX(inputMessage->vx > .05 ? inputMessage->vx : 0.0);
emit velocityY(inputMessage->vy > .05 ? inputMessage->vy : 0.0);
emit velocityZ(inputMessage->vz > .05 ? inputMessage->vz : 0.0);
}

/*
This function is the callback that takes ROS image messages and emits image signals based on that.
@param inputImageMessage: The image message to handle 
*/
void ROSSubscriberThread::handleImageUpdate(const sensor_msgs::ImageConstPtr& inputImageMessage)
{
//This image uses memory from the ROS message, so it can't really be used outside of this function
QImage temporaryImage(&(inputImageMessage->data[0]), inputImageMessage->width, inputImageMessage->height, QImage::Format_RGB888);

//Could try emitting without copying to see what happens
QImage imageFromARDrone; //Copy image so that image memory is safe to use
imageFromARDrone = temporaryImage;



emit cameraImage(QPixmap::fromImage(imageFromARDrone)); //Send the signal so it can be used for rendering
}

/*
This function takes command status messages and emits signals based on it.
@param inputMessage: The message to print out.
*/
void ROSSubscriberThread::handleCommandStatusInfoMessage(const ardrone_command::command_status_info::ConstPtr &inputMessage)
{
std::vector<command> receivedCommands = deserialize_commands(inputMessage->command);

for(int i=0; i<receivedCommands.size(); i++)
{
emit commandStatus(QString(commandTypeToString(receivedCommands[i].type).c_str()));
}
}
