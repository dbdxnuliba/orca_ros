#pragma once

#include <orca_ros/orca_ros.h>
#include <orca/gazebo/GazeboServer.h>
#include <orca/gazebo/GazeboModel.h>
#include <orca/robot/RobotDynTree.h>

namespace orca_ros
{
namespace gazebo
{

class RosGazeboModel : public common::RosWrapperBase
{
public:
    RosGazeboModel(std::shared_ptr<orca::gazebo::GazeboModel> gz_model
        , std::shared_ptr<orca::robot::RobotDynTree> robot_kinematics);
    void desiredTorqueSubscriberCb(const orca_ros::JointTorqueCommand::ConstPtr& msg);
    void publishRobotState();
private:
    ros::Publisher state_pub_;
    ros::Publisher joint_states_pub_;
    ros::Subscriber desired_torque_sub_;
    Eigen::VectorXd torque_command_;
    std::shared_ptr<orca::gazebo::GazeboModel> gz_model_;
    orca_ros::RobotState state_;
    sensor_msgs::JointState joint_states_;
    std::shared_ptr<orca::robot::RobotDynTree> robot_kinematics_;
    bool robot_compensates_gravity_ = false;
    bool first_command_received_ = false;
};

} // namespace gazebo
} // namespace orca
