#include "orca_ros/gazebo/RosGazeboModel.h"

using namespace orca::gazebo;
using namespace orca_ros::common;
using namespace orca_ros::gazebo;

int main(int argc, char** argv)
{
    std::string robot_name("");
    if(!ros::param::get("~robot_name",robot_name))
    {
        ROS_ERROR_STREAM("Could not find robot_name in namespace " << ros::this_node::getNamespace());
        return 0;
    }

    std::string base_frame("");
    if(!ros::param::get("~base_frame",base_frame))
    {
        ROS_ERROR_STREAM("Could not find base_frame in namespace " << ros::this_node::getNamespace());
        return 0;
    }

    std::string urdf_url("");
    if(!ros::param::get("~urdf_url",urdf_url))
    {
        ROS_ERROR_STREAM("Could not find urdf_url in namespace " << ros::this_node::getNamespace());
        return 0;
    }

    GazeboServer gzserver;

    auto gzrobot = std::make_shared<GazeboModel>(gzserver.insertModelFromURDFFile(urdf_url));
    auto rosrobot = RosGazeboModel(gzrobot);

    gzserver.run([&](uint32_t n_iter,double current_time,double dt)
    {
        ros::spinOnce();
    });
    return 0;
}
