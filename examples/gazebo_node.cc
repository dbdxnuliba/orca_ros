#include "orca_ros/orca_ros.h"
#include <signal.h>
bool exit_ = false;
void sigintHandler(int sig)
{
    exit_ = true;
}

using namespace orca::gazebo;
using namespace orca_ros::common;
using namespace orca_ros::gazebo;

int main(int argc, char** argv)
{
    // Start the server with ROS enabled
    GazeboServer gzserver({"-s","libgazebo_ros_paths_plugin.so","-s","libgazebo_ros_api_plugin.so"});

    // ros::init(argc, argv, "gazebo_node", ros::init_options::NoSigintHandler);
    // signal(SIGINT, sigintHandler);

    std::string robot_name("");
    if(!ros::param::get("~robot_name",robot_name))
    {
        ROS_ERROR_STREAM("" << ros::this_node::getName() << "Could not find robot_name in namespace "
            << ros::this_node::getNamespace()
            << "/" << ros::this_node::getName());
        return 0;
    }

    std::string base_frame("");
    if(!ros::param::get("~base_frame",base_frame))
    {
        ROS_ERROR_STREAM("" << ros::this_node::getName() << "Could not find base_frame in namespace "
            << ros::this_node::getNamespace()
            << "/" << ros::this_node::getName());
        return 0;
    }

    std::string urdf_url("");
    if(!ros::param::get("~urdf_url",urdf_url))
    {
        ROS_ERROR_STREAM("" << ros::this_node::getName() << "Could not find urdf_url in namespace "
            << ros::this_node::getNamespace()
            << "/" << ros::this_node::getName());
        return 0;
    }

    bool robot_compensates_gravity = false;
    if(!ros::param::get("~robot_compensates_gravity",robot_compensates_gravity))
    {
        ROS_ERROR_STREAM("" << ros::this_node::getName() << "Could not find robot_compensates_gravity in namespace "
            << ros::this_node::getNamespace()
            << "/" << ros::this_node::getName());
        return 0;
    }

    auto gzrobot = std::make_shared<GazeboModel>(gzserver.insertModelFromURDFFile(urdf_url));
    
    std::map<std::string, double> init_joint_positions;
    if(!ros::param::get("~init_joint_positions",init_joint_positions))
    {
        ROS_WARN_STREAM("" << ros::this_node::getName() << "Could not find init_joint_positions in namespace "
            << ros::this_node::getNamespace()
            << "/" << ros::this_node::getName());
    }
    std::vector<std::string> jn;
    std::vector<double> jp;
    for(auto e : init_joint_positions)
    {
        jn.push_back(e.first);
        jp.push_back(e.second);
    }
    gzrobot->setModelConfiguration(jn,jp);


    
    auto robot_kinematics = std::make_shared<orca::robot::RobotDynTree>();
    robot_kinematics->loadModelFromFile(urdf_url);

    auto gzrobot_ros_wrapper = RosGazeboModel(gzrobot,robot_kinematics,robot_compensates_gravity);

    gzserver.run([&](uint32_t n_iter,double current_time,double dt)
    {
        // if(exit_)
        //     gzserver.shutdown();
    });
    return 0;
}
