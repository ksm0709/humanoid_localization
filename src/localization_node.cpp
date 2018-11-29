// SVN $HeadURL$
// SVN $Id$

/*
 * 6D localization for humanoid robots
 *
 * Copyright 2009-2012 Armin Hornung, University of Freiburg
 * http://www.ros.org/wiki/humanoid_localization
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ros/ros.h>
#include <humanoid_localization/HumanoidLocalization.h>
#include "humanoid_localization/SrvParticlefilter.h"



bool Start_particlefilter_srv(humanoid_localization::SrvParticlefilter::Request &req, humanoid_localization::SrvParticlefilter::Response &res)
{
  ROS_INFO("global initialparticle filter is on");
  
  humanoid_localization::HumanoidLocalization localizationtmp(-1);

  if(req.start_particlefilter == 1){
  
    //global init particle filter on
    ROS_INFO("Receive service require: global particle filter on ");
    localizationtmp.initGlobal();
    
    res.particlefilter = 1;
  }
  else{
    //global init particle filter off
    ROS_INFO("Receive service require: global particle filter off ");
    res.particlefilter = 0;
    
  }
  return true;
}




int main(int argc, char** argv){
  ros::init(argc, argv, "humanoid_localization");

  ros::NodeHandle private_nh("~");
  unsigned seed;
  int iseed;
  private_nh.param("seed", iseed, -1);

   //ros service part
  ROS_INFO("ready srv server");
  ros::ServiceServer service_server = private_nh.advertiseService("particlefilter_srv", Start_particlefilter_srv);
 
  

  if(iseed == -1)
    seed = static_cast<unsigned int>(std::time(0));
  else
    seed = static_cast<unsigned int>(iseed);

  humanoid_localization::HumanoidLocalization localization(seed);



  ros::spin();

  return 0;
}


