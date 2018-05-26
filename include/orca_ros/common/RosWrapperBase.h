#pragma once

#include <ros/ros.h>

namspace orca_ros
{
namespace common
{

    class RosWrapperBase
    {
    public:
        RosWrapperBase (const std::string& robot_name,
                        const std::string& controller_name,
                        const std::string& obj_name,
                        const std::string& generic_prefix);
        virtual ~RosWrapperBase ();


        /*! Gets the name of the robot
         *  \return String robot name
         */
        std::string getRobotName();

        /*! Gets the name of the controller in which the task is being used
         *  \return String controller in which the task is being used name
         */
        std::string getControllerName();

        /*! Gets the name of the generic prefix which is either 'tasks' or 'constraints'
         *  \return String generic prefix
         */
        std::string getGenericPrefix();

        /*! Gets a shared pointer to the public NodeHandle
         *  \return shared pointer to the public NodeHandle
         */
        std::shared_ptr<ros::NodeHandle> getNodeHandle();


        /*! Get a string with the appropriate namspace prefix for topics and services
         *  \return String with the namespace prefix and a trailing '/' for convenience.
         */
        std::string getNamespacePrefix();

    private:
        std::string rn_; /*!< robot name */
        std::string cn_; /*!< controller name */
        std::string gp_; /*!< generic prefix (either task or constraint) */
        std::string on_; /*!< wrapped object name */
        std::shared_ptr<ros::NodeHandle> nh_; /*!< public NodeHandle */
    };

} //common
} // orca_ros