//
// Created by korisd on 4/20/18.
//

#ifndef RAM_ARM_CONTROLLER_H
#define RAM_ARM_CONTROLLER_H

#include <ros/ros.h>
#include <string>
#include <geometry_msgs/Pose.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt16.h>
#include "arm_controller/kinematics.h"
#include "state_machine/Error.h"
#include "dynamixel_workbench_toolbox/dynamixel_workbench.h"
#include "dynamixel_workbench_msgs/XH.h"


/*
 * Publishers
 */
ros::Publisher queue_size;
ros::Publisher state_machine_mode;
ros::Publisher desired_mode;
ros::Publisher current_kinematics;
ros::Publisher goal_kinematics;
ros::Publisher servo_rotation_info;
ros::Publisher servo_shoulder_info;
ros::Publisher servo_elbow_info;
ros::Publisher servo_wrist_info;

/*
 * Subscribers
 */

ros::Subscriber enqueue_waypoint;
ros::Subscriber reset_queue;
ros::Subscriber operation_mode;

DynamixelWorkbench bench;


#define MAX_UPDATE_PARAMS 5
std::string updateParams[MAX_UPDATE_PARAMS] = {
        "Torque_Enabled", "Goal_Position",
        "Present_Position", "Present_Velocity",
        "Profile_Velocity"
};

typedef enum
{
    ROTATION_SERVO, SHOULDER_SERVO,
    ELBOW_SERVO, WRIST_SERVO, MAX_SERVO
} SERVO_MSG;

ros::Publisher servo_info[MAX_SERVO];
dynamixel_workbench_msgs::XH servos[MAX_SERVO];

std::string servo_topic_names[MAX_SERVO] = {
        "servo/rotation", "servo/shoulder",
        "servo/elbow", "servo/wrist"
};

void setupPublishers( ros::NodeHandle &ros_handle  );
void setupSubscribers( ros::NodeHandle &ros_handle );
void setupCallbackFunctions( ros::NodeHandle &ros_handle );
bool setupDynamixelBus();
bool setupDynamixelDriver();
bool setupBulkRead();

bool readAndUpdateServos();
void enqueueHandler( const geometry_msgs::Pose::ConstPtr &message );
void resetQueueHandler( const std_msgs::UInt8::ConstPtr &message );
void operationModeHandler( const std_msgs::UInt8::ConstPtr &message );
void publishServoInfo();
#endif //RAM_ARM_CONTROLLER_H
