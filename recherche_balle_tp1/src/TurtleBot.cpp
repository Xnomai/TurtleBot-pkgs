#include "TurtleBot.hpp"
#include <vector>


#define LINEAR_MAX_VELOCITY 0.25
#define ANGULAR_MAX_VELOCITY 2


TurtleBot::TurtleBot(ros::NodeHandle node):

    
	//Publishers
	publisherMobileBaseCommandsVelocity(node.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1)),
	publisherMobileBaseCommandsSound(node.advertise<kobuki_msgs::Sound>("/mobile_base/commands/sound", 1)),

	//Subcribers
	subscriberCameraRgbImageRaw(node.subscribe("/camera/rgb/image_raw", 1, &TurtleBot::callbackCameraRgbImageRaw,this)),
	subscriberCameraRgbImageColor(node.subscribe("/camera/rgb/image_color", 1, &TurtleBot::callbackCameraRgbImageColor,this)),
	subscriberCameraRgbImageRectColor(node.subscribe("/camera/rgb/image_rect_color", 1, &TurtleBot::callbackCameraRgbImageRectColor,this)),
	subscriberJointStates(node.subscribe("/joint_states", 1, &TurtleBot::callbackJointStates,this))
{
	TurtleBot::stop();
}

//Getters
sensor_msgs::Image TurtleBot::getCameraRgbImageRaw()
{
	return cameraRgbImageRaw;
}

sensor_msgs::Image TurtleBot::getCameraRgbImageColor()
{
	return cameraRgbImageColor;
}

sensor_msgs::Image TurtleBot::getCameraRgbImageRectColor()
{
	return cameraRgbImageRectColor;
}

geometry_msgs::Twist TurtleBot::getMobileBaseCommandsVelocity() 
{
	return mobileBaseCommandsVelocity;
}

sensor_msgs::JointState TurtleBot::getJointStates()
{
	return jointStates;
}



//Setters
void TurtleBot::setMobileBaseCommandsVelocity(float linearX, float linearY, float linearZ, float angularX, float angularY, float angularZ)
{
	mobileBaseCommandsVelocity.linear.x=linearX;
	mobileBaseCommandsVelocity.linear.y=linearY;
	mobileBaseCommandsVelocity.linear.z=linearZ;
	mobileBaseCommandsVelocity.angular.x=angularX;
	mobileBaseCommandsVelocity.angular.y=angularY;
	mobileBaseCommandsVelocity.angular.z=angularZ;
}

void TurtleBot::setMobileBaseCommandsSound(int sound)
{
	mobileBaseCommandsSound.value = sound;
}

//Callbacks
void TurtleBot::callbackCameraRgbImageRaw(const sensor_msgs::Image& msg)
{
	cameraRgbImageRaw = msg;
}

void TurtleBot::callbackCameraRgbImageColor(const sensor_msgs::Image& msg)
{
	cameraRgbImageColor = msg;
}

void TurtleBot::callbackCameraRgbImageRectColor(const sensor_msgs::Image& msg)
{
	cameraRgbImageRectColor = msg;
}

void TurtleBot::callbackJointStates(const sensor_msgs::JointState& msg)
{
	jointStates = msg;
}


//Publications
void TurtleBot::sendMobileBaseCommandsVelocity()
{
	publisherMobileBaseCommandsVelocity.publish(mobileBaseCommandsVelocity);
}

void TurtleBot::sendMobileBaseCommandsSound()
{
	publisherMobileBaseCommandsSound.publish(mobileBaseCommandsSound);
}

//Image convertion
unsigned char* TurtleBot::convertSensor_msgsImageToRaw(sensor_msgs::Image sensorMsgsImage)
{
	std::vector<unsigned char> vectorRaw(sensorMsgsImage.height*sensorMsgsImage.width);
	vectorRaw=sensorMsgsImage.data;
	unsigned char* raw = &vectorRaw[0];
	return raw;	
}

//Displays
void TurtleBot::displaySensorMsgsImage(std::string type, sensor_msgs::Image sensorMsgsImage)
{
	std::cout<<"--------"<<type<<"---------"<<std::endl;
  	std::cout<<sensorMsgsImage.height<<std::endl;
	std::cout<<sensorMsgsImage.width<<std::endl;
	std::cout<<sensorMsgsImage.encoding<<std::endl;
	std::cout<<sensorMsgsImage.is_bigendian<<std::endl;
	std::cout<<sensorMsgsImage.step<<std::endl;
}

void TurtleBot::displayMobileBaseCommandsVelocity()
{
	std::cout<<mobileBaseCommandsVelocity<<std::endl;
}

void TurtleBot::displayJointStates()
{
	std::cout<<jointStates<<std::endl;
}

void TurtleBot::displayMobileBaseCommandsSound()
{
	std::cout<<mobileBaseCommandsSound<<std::endl;
}


//Motions
void TurtleBot::stop()
{
	TurtleBot::setMobileBaseCommandsVelocity(0, 0, 0, 0, 0, 0);
}

void TurtleBot::moveForward()
{
	TurtleBot::setMobileBaseCommandsVelocity(LINEAR_MAX_VELOCITY, 0, 0, 0, 0, 0);
}

void TurtleBot::moveBackward()
{
	TurtleBot::setMobileBaseCommandsVelocity(-LINEAR_MAX_VELOCITY, 0, 0, 0, 0, 0);
}

void TurtleBot::turnRight()
{
	TurtleBot::setMobileBaseCommandsVelocity(0, 0, 0, 0, 0, -ANGULAR_MAX_VELOCITY);
}

void TurtleBot::turnLeft()
{
	TurtleBot::setMobileBaseCommandsVelocity(0, 0, 0, 0, 0, ANGULAR_MAX_VELOCITY);
}

void TurtleBot::moveForwardTurningRight()
{
	TurtleBot::setMobileBaseCommandsVelocity(LINEAR_MAX_VELOCITY, 0, 0, 0, 0, -ANGULAR_MAX_VELOCITY);
}

void TurtleBot::moveForwardTurningLeft()
{
	TurtleBot::setMobileBaseCommandsVelocity(LINEAR_MAX_VELOCITY, 0, 0, 0, 0, ANGULAR_MAX_VELOCITY);
}

void TurtleBot::moveBackwardTurningRight()
{
	TurtleBot::setMobileBaseCommandsVelocity(-LINEAR_MAX_VELOCITY, 0, 0, 0, 0, -ANGULAR_MAX_VELOCITY);
}

void TurtleBot::moveBackwardTurningLeft()
{
	TurtleBot::setMobileBaseCommandsVelocity(-LINEAR_MAX_VELOCITY, 0, 0, 0, 0, ANGULAR_MAX_VELOCITY);
}
