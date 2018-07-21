#ifndef ROULETTE_H
#define ROULETTE_H

#include "ros/ros.h"
#include <vector>
#include "geometry_msgs/Vector3.h"
#include "riptide_msgs/Constants.h"
#include "riptide_msgs/ControlStatusAngular.h"
#include "riptide_msgs/ControlStatusLinear.h"
#include "riptide_msgs/AttitudeCommand.h"
#include "riptide_msgs/AlignmentCommand.h"
#include "riptide_msgs/Pneumatics.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "darknet_ros_msgs/BoundingBox.h"
#include "riptide_autonomy/be_autonomous.h"
#include "riptide_autonomy/object_describer.h"
#include <cmath>
using namespace std;
typedef riptide_msgs::Constants rc;

class BeAutonomous;

class ObjectDescriber;

class Roulette
{

private:
  ros::Subscriber task_bbox_sub, alignment_status_sub, attitude_status_sub;
  vector<ros::Subscriber> active_subs;

  darknet_ros_msgs::BoundingBoxes task_bboxes;
  riptide_msgs::AlignmentCommand align_cmd;
  riptide_msgs::AttitudeCommand attitude_cmd;
  riptide_msgs::Pneumatics pneumatics_cmd;

  double duration;
  int detections, attempts;
  ros::Time acceptable_begin;
  ros::Time detect_start;
  bool clock_is_ticking, drop_clock_is_ticking;

  // ALignment variables
  bool got_heading;
  double green_heading, marker_drop_heading, drop_duration, drop_duration_thresh;
  int align_id, num_markers_dropped;
  ros::Time drop_time;

  // Create instance to master
  BeAutonomous* master;
  ObjectDescriber* od;
  bool task_completed;

public:

  Roulette(BeAutonomous* master);
  void Start();
  void IDRoulette(const darknet_ros_msgs::BoundingBoxes::ConstPtr& bbox_msg);
  void AlignmentStatusCB(const riptide_msgs::ControlStatusLinear::ConstPtr& status_msg);
  void SetMarkerDropHeading(double heading);
  void AttitudeStatusCB(const riptide_msgs::ControlStatusAngular::ConstPtr& status_msg);
  void Abort();
};

#endif