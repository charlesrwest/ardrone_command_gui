#ifndef  ROSSUBSCRIBERTHREADHPP
#define ROSSUBSCRIBERTHREADHPP

#include<QThread>
#include<QString>
#include<QImage>
#include<QPixmap>
#include<QMetaType>
#include<string>
#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include <unistd.h>
#include<memory>
#include <ardrone_autonomy/CamSelect.h>
#include <ardrone_autonomy/LedAnim.h>
#include <ardrone_autonomy/FlightAnim.h>
#include <ardrone_autonomy/RecordEnable.h>
#include <ardrone_autonomy/Navdata.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

#include "ardrone_command/serialized_ardrone_command.h"
#include "ardrone_command/commandInterface.h"
#include "ardrone_command/command.hpp"

#include "ardrone_command/altitude_control_state.h"
#include "ardrone_command/qr_code_state_info.h"
#include "ardrone_command/qr_go_to_point_control_info.h"
#include "ardrone_command/qr_orientation_control_info.h"
#include "ardrone_command/command_status_info.h"

Q_DECLARE_METATYPE(command);



class ROSSubscriberThread : public QThread
{
Q_OBJECT

public:
/*
This function initializes the ROSSubscriberThread.
@param inputParent: This is a pointer to the parent QT object (for cascade delete purposes).
*/
ROSSubscriberThread(QObject *inputParent = nullptr);



/*
This function cleans up the object and waits for the thread to stop running before returning.
*/
~ROSSubscriberThread();

public slots:
/*
This function sends a command to ardrone_autonomy to tell the ardrone to take off.
*/
void sendTakeoffCommand(bool input);

/*
This function sends a command to ardrone_command to tell it to land after finishing any other commands it has received.
*/
void sendLandAfterFinishingCommand(bool input);

/*
This function sends a command to ardrone_autonomy to tell the ardrone to land now.
*/
void sendLandImmediatelyCommand(bool input);

/*
This function takes the given command and sends it to the AR Drone.
@param inputCommand: The command to send
*/
void sendARDroneCommand(const command &inputCommand);


signals:
/*
Emits text indicating the flying/landing/other status
*/
void droneState(const QString &);

/*
Emits text indicating the charge state of the drone
*/
void batteryStatus(double);

/*
Emits text indicating which command is currently being done
*/
void commandStatus(const QString &);

/*
Emits text indicating the X velocity of the drone
*/
void velocityX(double);

/*
Emits text indicating the Y velocity of the drone
*/
void velocityY(double);

/*
Emits text indicating the Z velocity of the drone
*/
void velocityZ(double);

/*
Emits text indicating the X tile of the drone
*/
void tiltX(double);

/*
Emits text indicating the Y tile of the drone
*/
void tiltY(double);

/*
Emits text indicating the Z tile of the drone
*/
void tiltZ(double);

/*
Emits text indicating the altitude of the drone
*/
void altitude(int);

/*
Emits QImage from the front camera of the AR Drone
*/
void cameraImage(QPixmap);



protected:


/*
This function is the code that is run in the seperate thread.  It is responsible for recieving ROS messages and forwarding commands.
*/
void run() Q_DECL_OVERRIDE;

/*
This function is called periodically to call ROS::spin().
@param inputTimeEvent: The timer event that caused this function to be called
*/
void timerEvent(QTimerEvent *inputTimerEvent) Q_DECL_OVERRIDE;

/*
This function is the callback that takes ROS navdata messages and sends signals based on that.
@param inputMessage: The  nav-data message to handle 
*/
void handleNavData(const ardrone_autonomy::Navdata::ConstPtr &inputMessage);

/*
This function is the callback that takes ROS image messages and emits image signals based on that.
@param inputImageMessage: The image message to handle 
*/
void handleImageUpdate(const sensor_msgs::ImageConstPtr& inputImageMessage);

/*
This function takes command status messages and emits signals based on it.
@param inputMessage: The message to print out.
*/
void handleCommandStatusInfoMessage(const ardrone_command::command_status_info::ConstPtr &inputMessage);

std::unique_ptr<ros::NodeHandle> nodeHandle;
ros::Subscriber navDataSubscriber;
ros::Subscriber videoSubscriber;
ros::Subscriber commandSubscriber;
ros::Publisher takeOffPublisher;
ros::Publisher landingPublisher;
ros::Publisher emergencyStopPublisher;
};








#endif
