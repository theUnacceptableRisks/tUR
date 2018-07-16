// Generated by gencpp from file ground_station/ArmStatus.msg
// DO NOT EDIT!


#ifndef GROUND_STATION_MESSAGE_ARMSTATUS_H
#define GROUND_STATION_MESSAGE_ARMSTATUS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ground_station
{
template <class ContainerAllocator>
struct ArmStatus_
{
  typedef ArmStatus_<ContainerAllocator> Type;

  ArmStatus_()
    : time_recorded(0)
    , turntable_temp(0)
    , turntable_velo(0)
    , turntable_goal(0)
    , turntable_posi(0)
    , turntable_onoff(false)
    , shoulder_temp(0)
    , shoulder_velo(0)
    , shoulder_goal(0)
    , shoulder_posi(0)
    , shoulder_onoff(false)
    , elbow_temp(0)
    , elbow_velo(0)
    , elbow_goal(0)
    , elbow_posi(0)
    , elbow_onoff(false)
    , wrist_temp(0)
    , wrist_velo(0)
    , wrist_goal(0)
    , wrist_posi(0)
    , wrist_onoff(false)
    , gripper_temp(0)
    , gripper_velo(0)
    , gripper_goal(0)
    , gripper_posi(0)
    , gripper_onoff(false)
    , armposition_in_mm_X(0)
    , armposition_in_mm_Y(0)
    , armposition_in_mm_Z(0)
    , armorientation_in_rads(0)  {
    }
  ArmStatus_(const ContainerAllocator& _alloc)
    : time_recorded(0)
    , turntable_temp(0)
    , turntable_velo(0)
    , turntable_goal(0)
    , turntable_posi(0)
    , turntable_onoff(false)
    , shoulder_temp(0)
    , shoulder_velo(0)
    , shoulder_goal(0)
    , shoulder_posi(0)
    , shoulder_onoff(false)
    , elbow_temp(0)
    , elbow_velo(0)
    , elbow_goal(0)
    , elbow_posi(0)
    , elbow_onoff(false)
    , wrist_temp(0)
    , wrist_velo(0)
    , wrist_goal(0)
    , wrist_posi(0)
    , wrist_onoff(false)
    , gripper_temp(0)
    , gripper_velo(0)
    , gripper_goal(0)
    , gripper_posi(0)
    , gripper_onoff(false)
    , armposition_in_mm_X(0)
    , armposition_in_mm_Y(0)
    , armposition_in_mm_Z(0)
    , armorientation_in_rads(0)  {
  (void)_alloc;
    }



   typedef uint32_t _time_recorded_type;
  _time_recorded_type time_recorded;

   typedef int8_t _turntable_temp_type;
  _turntable_temp_type turntable_temp;

   typedef uint8_t _turntable_velo_type;
  _turntable_velo_type turntable_velo;

   typedef int16_t _turntable_goal_type;
  _turntable_goal_type turntable_goal;

   typedef int16_t _turntable_posi_type;
  _turntable_posi_type turntable_posi;

   typedef uint8_t _turntable_onoff_type;
  _turntable_onoff_type turntable_onoff;

   typedef int8_t _shoulder_temp_type;
  _shoulder_temp_type shoulder_temp;

   typedef uint8_t _shoulder_velo_type;
  _shoulder_velo_type shoulder_velo;

   typedef int16_t _shoulder_goal_type;
  _shoulder_goal_type shoulder_goal;

   typedef int16_t _shoulder_posi_type;
  _shoulder_posi_type shoulder_posi;

   typedef uint8_t _shoulder_onoff_type;
  _shoulder_onoff_type shoulder_onoff;

   typedef int8_t _elbow_temp_type;
  _elbow_temp_type elbow_temp;

   typedef uint8_t _elbow_velo_type;
  _elbow_velo_type elbow_velo;

   typedef int16_t _elbow_goal_type;
  _elbow_goal_type elbow_goal;

   typedef int16_t _elbow_posi_type;
  _elbow_posi_type elbow_posi;

   typedef uint8_t _elbow_onoff_type;
  _elbow_onoff_type elbow_onoff;

   typedef int8_t _wrist_temp_type;
  _wrist_temp_type wrist_temp;

   typedef uint8_t _wrist_velo_type;
  _wrist_velo_type wrist_velo;

   typedef int16_t _wrist_goal_type;
  _wrist_goal_type wrist_goal;

   typedef int16_t _wrist_posi_type;
  _wrist_posi_type wrist_posi;

   typedef uint8_t _wrist_onoff_type;
  _wrist_onoff_type wrist_onoff;

   typedef int8_t _gripper_temp_type;
  _gripper_temp_type gripper_temp;

   typedef uint8_t _gripper_velo_type;
  _gripper_velo_type gripper_velo;

   typedef int16_t _gripper_goal_type;
  _gripper_goal_type gripper_goal;

   typedef int16_t _gripper_posi_type;
  _gripper_posi_type gripper_posi;

   typedef uint8_t _gripper_onoff_type;
  _gripper_onoff_type gripper_onoff;

   typedef int16_t _armposition_in_mm_X_type;
  _armposition_in_mm_X_type armposition_in_mm_X;

   typedef int16_t _armposition_in_mm_Y_type;
  _armposition_in_mm_Y_type armposition_in_mm_Y;

   typedef int16_t _armposition_in_mm_Z_type;
  _armposition_in_mm_Z_type armposition_in_mm_Z;

   typedef int16_t _armorientation_in_rads_type;
  _armorientation_in_rads_type armorientation_in_rads;





  typedef boost::shared_ptr< ::ground_station::ArmStatus_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ground_station::ArmStatus_<ContainerAllocator> const> ConstPtr;

}; // struct ArmStatus_

typedef ::ground_station::ArmStatus_<std::allocator<void> > ArmStatus;

typedef boost::shared_ptr< ::ground_station::ArmStatus > ArmStatusPtr;
typedef boost::shared_ptr< ::ground_station::ArmStatus const> ArmStatusConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ground_station::ArmStatus_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ground_station::ArmStatus_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ground_station

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'ground_station': ['/home/korisd/tUR/ROSCode/RAM/src/ground_station/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ground_station::ArmStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ground_station::ArmStatus_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ground_station::ArmStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ground_station::ArmStatus_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ground_station::ArmStatus_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ground_station::ArmStatus_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ground_station::ArmStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "7485d942837d3cb41efb02705164112e";
  }

  static const char* value(const ::ground_station::ArmStatus_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x7485d942837d3cb4ULL;
  static const uint64_t static_value2 = 0x1efb02705164112eULL;
};

template<class ContainerAllocator>
struct DataType< ::ground_station::ArmStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ground_station/ArmStatus";
  }

  static const char* value(const ::ground_station::ArmStatus_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ground_station::ArmStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint32 time_recorded\n\
\n\
int8 turntable_temp\n\
uint8 turntable_velo\n\
int16 turntable_goal\n\
int16 turntable_posi\n\
bool turntable_onoff\n\
\n\
int8 shoulder_temp\n\
uint8 shoulder_velo\n\
int16 shoulder_goal\n\
int16 shoulder_posi\n\
bool shoulder_onoff\n\
\n\
int8 elbow_temp\n\
uint8 elbow_velo\n\
int16 elbow_goal\n\
int16 elbow_posi\n\
bool elbow_onoff\n\
\n\
int8 wrist_temp\n\
uint8 wrist_velo\n\
int16 wrist_goal\n\
int16 wrist_posi\n\
bool wrist_onoff\n\
\n\
int8 gripper_temp\n\
uint8 gripper_velo\n\
int16 gripper_goal\n\
int16 gripper_posi\n\
bool gripper_onoff\n\
\n\
int16 armposition_in_mm_X\n\
int16 armposition_in_mm_Y\n\
int16 armposition_in_mm_Z\n\
int16 armorientation_in_rads\n\
";
  }

  static const char* value(const ::ground_station::ArmStatus_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ground_station::ArmStatus_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.time_recorded);
      stream.next(m.turntable_temp);
      stream.next(m.turntable_velo);
      stream.next(m.turntable_goal);
      stream.next(m.turntable_posi);
      stream.next(m.turntable_onoff);
      stream.next(m.shoulder_temp);
      stream.next(m.shoulder_velo);
      stream.next(m.shoulder_goal);
      stream.next(m.shoulder_posi);
      stream.next(m.shoulder_onoff);
      stream.next(m.elbow_temp);
      stream.next(m.elbow_velo);
      stream.next(m.elbow_goal);
      stream.next(m.elbow_posi);
      stream.next(m.elbow_onoff);
      stream.next(m.wrist_temp);
      stream.next(m.wrist_velo);
      stream.next(m.wrist_goal);
      stream.next(m.wrist_posi);
      stream.next(m.wrist_onoff);
      stream.next(m.gripper_temp);
      stream.next(m.gripper_velo);
      stream.next(m.gripper_goal);
      stream.next(m.gripper_posi);
      stream.next(m.gripper_onoff);
      stream.next(m.armposition_in_mm_X);
      stream.next(m.armposition_in_mm_Y);
      stream.next(m.armposition_in_mm_Z);
      stream.next(m.armorientation_in_rads);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ArmStatus_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ground_station::ArmStatus_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ground_station::ArmStatus_<ContainerAllocator>& v)
  {
    s << indent << "time_recorded: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.time_recorded);
    s << indent << "turntable_temp: ";
    Printer<int8_t>::stream(s, indent + "  ", v.turntable_temp);
    s << indent << "turntable_velo: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.turntable_velo);
    s << indent << "turntable_goal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.turntable_goal);
    s << indent << "turntable_posi: ";
    Printer<int16_t>::stream(s, indent + "  ", v.turntable_posi);
    s << indent << "turntable_onoff: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.turntable_onoff);
    s << indent << "shoulder_temp: ";
    Printer<int8_t>::stream(s, indent + "  ", v.shoulder_temp);
    s << indent << "shoulder_velo: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.shoulder_velo);
    s << indent << "shoulder_goal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.shoulder_goal);
    s << indent << "shoulder_posi: ";
    Printer<int16_t>::stream(s, indent + "  ", v.shoulder_posi);
    s << indent << "shoulder_onoff: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.shoulder_onoff);
    s << indent << "elbow_temp: ";
    Printer<int8_t>::stream(s, indent + "  ", v.elbow_temp);
    s << indent << "elbow_velo: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.elbow_velo);
    s << indent << "elbow_goal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.elbow_goal);
    s << indent << "elbow_posi: ";
    Printer<int16_t>::stream(s, indent + "  ", v.elbow_posi);
    s << indent << "elbow_onoff: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.elbow_onoff);
    s << indent << "wrist_temp: ";
    Printer<int8_t>::stream(s, indent + "  ", v.wrist_temp);
    s << indent << "wrist_velo: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.wrist_velo);
    s << indent << "wrist_goal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.wrist_goal);
    s << indent << "wrist_posi: ";
    Printer<int16_t>::stream(s, indent + "  ", v.wrist_posi);
    s << indent << "wrist_onoff: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.wrist_onoff);
    s << indent << "gripper_temp: ";
    Printer<int8_t>::stream(s, indent + "  ", v.gripper_temp);
    s << indent << "gripper_velo: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.gripper_velo);
    s << indent << "gripper_goal: ";
    Printer<int16_t>::stream(s, indent + "  ", v.gripper_goal);
    s << indent << "gripper_posi: ";
    Printer<int16_t>::stream(s, indent + "  ", v.gripper_posi);
    s << indent << "gripper_onoff: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.gripper_onoff);
    s << indent << "armposition_in_mm_X: ";
    Printer<int16_t>::stream(s, indent + "  ", v.armposition_in_mm_X);
    s << indent << "armposition_in_mm_Y: ";
    Printer<int16_t>::stream(s, indent + "  ", v.armposition_in_mm_Y);
    s << indent << "armposition_in_mm_Z: ";
    Printer<int16_t>::stream(s, indent + "  ", v.armposition_in_mm_Z);
    s << indent << "armorientation_in_rads: ";
    Printer<int16_t>::stream(s, indent + "  ", v.armorientation_in_rads);
  }
};

} // namespace message_operations
} // namespace ros

#endif // GROUND_STATION_MESSAGE_ARMSTATUS_H