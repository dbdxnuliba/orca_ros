// This file is a part of the orca framework.
// Copyright 2017, ISIR / Universite Pierre et Marie Curie (UPMC)
// Main contributor(s): Antoine Hoarau, hoarau@isir.upmc.fr
//
// This software is a computer program whose purpose is to [describe
// functionalities and technical features of your software].
//
// This software is governed by the CeCILL-C license under French law and
// abiding by the rules of distribution of free software.  You can  use,
// modify and/ or redistribute the software under the terms of the CeCILL-C
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info".
//
// As a counterpart to the access to the source code and  rights to copy,
// modify and redistribute granted by the license, users are provided only
// with a limited warranty  and the software's author,  the holder of the
// economic rights,  and the successive licensors  have only  limited
// liability.
//
// In this respect, the user's attention is drawn to the risks associated
// with loading,  using,  modifying and/or developing or reproducing the
// software by the user in light of its specific status of free software,
// that may mean  that it is complicated to manipulate,  and  that  also
// therefore means  that it is reserved for developers  and  experienced
// professionals having in-depth computer knowledge. Users are therefore
// encouraged to load and test the software's suitability as regards their
// requirements in conditions enabling the security of their systems and/or
// data to be ensured and,  more generally, to use and operate it in the
// same conditions as regards security.
//
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL-C license and that you accept its terms.

#pragma once

#include "orca_ros/common/RosWrapperBase.h"

namespace orca_ros
{
namespace optim
{

class RosControllerProxy : public orca_ros::common::RosWrapperBase
{
public:
    RosControllerProxy(  const std::string& robot_name,
                         const std::string& controller_name);

    virtual ~RosControllerProxy();

    std::string getName();
    void print();
    void setPrintLevel(int level);
    void update(double current_time, double dt);
    bool addTask(orca_ros::TaskDescription td);
    bool addConstraint(orca_ros::ConstraintDescription cd);
    Eigen::VectorXd getFullSolution();
    Eigen::VectorXd getJointTorqueCommand();
    Eigen::VectorXd getJointAccelerationCommand();
    void activateAll(double current_time);
    void deactivateAll(double current_time);
    bool allDeactivated();


private:
    ros::ServiceClient sc_getName_;
    ros::ServiceClient sc_print_;
    ros::ServiceClient sc_setPrintLevel_;
    ros::ServiceClient sc_update_;
    ros::ServiceClient sc_addTask_;
    ros::ServiceClient sc_addConstraint_;
    ros::ServiceClient sc_getFullSolution_;
    ros::ServiceClient sc_getJointTorqueCommand_;
    ros::ServiceClient sc_getJointAccelerationCommand_;
    ros::ServiceClient sc_activateAll_;
    ros::ServiceClient sc_deactivateAll_;
    ros::ServiceClient sc_allDeactivated_;
};

} // namespace optim
} // namespace orca
