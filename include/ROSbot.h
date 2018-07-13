#ifndef _ROSBOT_H_
#define _ROSBOT_H_

#include "hFramework.h"

// #include "hCloudClient.h"
// #include "ros.h"
#include "wheel.h"
#include "VL53L0X.h"
// #include "hMotor.h"
#include "IMU.h"
// #include "tf/tf.h"
// #include "geometry_msgs/Twist.h"
// #include "geometry_msgs/PoseStamped.h"
// #include "sensor_msgs/BatteryState.h"
// #include "std_msgs/Bool.h"
// #include "sensor_msgs/Range.h"
// #include "geometry_msgs/Vector3.h"
#include "vector"

#define VL53L0XXshutPort hSens6

namespace hFramework
{

enum SensorType
{
  SENSOR_INFRARED,
  SENSOR_LASER
};

struct hMUX
{
  bool p2;
  bool p3;
  bool p4;
  bool active;
  float *dis;
  hMUX(bool tp2, bool tp3, bool tp4, bool tactive, float *tdis) : p2(tp2), p3(tp3), p4(tp4), active(tactive), dis(tdis) {}
  hMUX(bool tp2, bool tp3, bool tp4, bool tactive) : p2(tp2), p3(tp3), p4(tp4), active(tactive) {}
};

class ROSbot
{
public:
  ROSbot(){};
  void initROSbot(SensorType s = SENSOR_INFRARED);
  void initWheelController();
  void initBatteryMonitor(float voltage_threshold = 10.5);
  float getBatteryLevel();
  void setSpeed(float linear, float angular);
  void initOdometry();
  std::vector<float> getPose();
  void reset_odometry();
  void initDistanceSensors(SensorType s = SENSOR_INFRARED);
  std::vector<float> getRanges(SensorType s = SENSOR_INFRARED);
  void initIMU();
  std::vector<float> getRPY();

private:
  void wheelUpdater();
  void batteryMonitor();
  void odometryUpdater();
  std::vector<float> rosbotPose;
  void reset_encoders();
  void reset_odom_vars();
  void reset_wheels();
  int readLaserDistanceSensor(VL53L0X &s);
  void readIRSensors();

  Wheel *wheelFL;
  Wheel *wheelRL;
  Wheel *wheelFR;
  Wheel *wheelRR;
  float lin;
  float ang;
  float L_wheel_lin_speed;
  float R_wheel_lin_speed;
  float L_wheel_angular_velocity;
  float R_wheel_angular_velocity;
  float L_enc_speed;
  float R_enc_speed;
  float robot_width = 0.3;   // meters
  float wheel_radius = 0.04; //meters
  uint16_t enc_res = 1400;   // encoder tics per wheel revolution

  float voltage_limit;
  float current_voltage;
  bool batteryLow = false;
  uint16_t loop_delay = 10; // milliseconds
  float delay_s;
  int32_t enc_FL = 0; // encoder tics
  int32_t enc_RL = 0; // encoder tics
  int32_t enc_FR = 0; // encoder tics
  int32_t enc_RR = 0; // encoder tics

  int32_t enc_L = 0;         // encoder tics
  float wheel_L_ang_pos = 0; // radians
  float wheel_L_ang_vel = 0; // radians per second

  int32_t enc_R = 0;         // encoder tics
  float wheel_R_ang_pos = 0; // radians
  float wheel_R_ang_vel = 0; // radians per second

  float robot_angular_pos = 0; // radians
  float robot_angular_vel = 0; // radians per second

  float robot_x_pos = 0; // meters
  float robot_y_pos = 0; // meters
  float robot_x_vel = 0; // meters per second
  float robot_y_vel = 0; // meters per second

  VL53L0X sensor_dis[4]; //0 - FR, 1 - FL, 2 - RL, 3 - RR
  std::vector<float> ranges;
  float MUXStepTime = 50; //200ms for scan
  float dis1 = 0;         //Sharp LF
  float dis2 = 0;         //Sharp RF
  float dis3 = 0;         //Sharp LR
  float dis4 = 0;         //Sharp RR
  hSensor *sensMUX;
  hMUX tMUX[8] = {
      hMUX(false, false, false, true, &dis4), //ch0
      hMUX(false, false, true, true, &dis3),  //ch1
      hMUX(false, true, false, false),        //ch2
      hMUX(false, true, true, false),         //ch3
      hMUX(true, false, false, false),        //ch4
      hMUX(true, false, true, false),         //ch5
      hMUX(true, true, false, true, &dis1),   //ch6
      hMUX(true, true, true, true, &dis2)     //ch7
  };

  IMU imu;
  std::vector<float> imuArray;
};

extern ROSbot rosbot;
} // namespace hFramework
#endif