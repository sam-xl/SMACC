#pragma once

#include <sensor_state_machine.h>
#include <orthogonals/sensor_orthogonal.h>
#include <orthogonals/obstacle_perception_orthogonal.h>

#include <sensor_msgs/LaserScan.h>
#include <substates_behaviors/sensor/custom_condition_temperature_sensor.h>
#include <smacc_interface_components/substate_behaviors/sensor_substate.h>

using namespace smacc;

typedef smacc::SensorTopic<sensor_msgs::LaserScan> LidarSensor ;

struct SensorState: smacc::SmaccState<SensorState, SensorStateMachine>
{
  public:
  typedef mpl::list<
                sc::transition<EvSensorInitialMessage<LidarSensor>, SensorState>, 
                sc::transition<EvSensorMessage<LidarSensor>, SensorState>, 
                sc::transition<EvSensorMessageTimeout<LidarSensor>, SensorState>,
                
                sc::transition<EvSensorInitialMessage<CustomConditionTemperatureSensor>, SensorState>, 
                sc::transition<EvSensorMessage<CustomConditionTemperatureSensor>, SensorState>, 
                sc::transition<EvSensorMessageTimeout<CustomConditionTemperatureSensor>, SensorState>,
                
                sc::transition<EvCustomTemperatureAlert, SensorState>> reactions; 


  using SmaccState::SmaccState;

  void onInitialize()
  {
    this->configure<ObstaclePerceptionOrthogonal>(new smacc::SensorTopic<sensor_msgs::LaserScan>("/scan", 1, ros::Duration(10)));
    this->configure<SensorOrthogonal>(new CustomConditionTemperatureSensor("/temperature"));
  }

  void onEntry()
  {
    ROS_INFO("sensor state onEntry" );
  }

  void onExit()
  {
  }
};
