// -*- C++ -*-
/*!
 * @file  PlannerTesterRTC_Cnoid.cpp
 * @brief PlannerTesterRTC Service on Choreonoid
 * @date $Date$
 *
 * $Id$
 */

#include "PlannerTesterRTC_Cnoid.h"

// Module specification
// <rtc-template block="module_spec">
static const char* plannertesterrtc_cnoid_spec[] =
  {
    "implementation_id", "PlannerTesterRTC_Cnoid",
    "type_name",         "PlannerTesterRTC_Cnoid",
    "description",       "PlannerTesterRTC Service on Choreonoid",
    "version",           "1.0.0",
    "vendor",            "Ogata Laboratory",
    "category",          "MotionPlanning",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.debug", "1",

    // Widget
    "conf.__widget__.debug", "text",
    // Constraints

    "conf.__type__.debug", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PlannerTesterRTC_Cnoid::PlannerTesterRTC_Cnoid(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_objectDetectorPort("objectDetector")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PlannerTesterRTC_Cnoid::~PlannerTesterRTC_Cnoid()
{
}



bool PlannerTesterRTC_Cnoid::detectObject(const std::string& name, std::vector<double>& out) {

  if (m_objectDetectorPort.get_connector_profiles()->length() > 0) {
    Manipulation::ObjectIdentifier objectID;
    objectID.name = CORBA::string_dup(name.c_str());
    Manipulation::ObjectInfo_var objInfo;
    Manipulation::ReturnValue_var retval = m_objectDetectionService->detectObject(objectID, objInfo);
    std::cout << "detectObject: " << (const char*)retval->message << std::endl;
    if (retval->id == Manipulation::OK) {
      out.push_back(objInfo->pose.position.x);
      out.push_back(objInfo->pose.position.y);
      out.push_back(objInfo->pose.position.z);
      out.push_back(objInfo->pose.orientation.r);
      out.push_back(objInfo->pose.orientation.p);
      out.push_back(objInfo->pose.orientation.y);
      return true;
    } else {
      return false;
    }
  } else {
    std::cout << "No connection" << std::endl;
    std::cout << "- Dummy Data is output." << std::endl;
    out.push_back(0);
    out.push_back(0);
    out.push_back(0.5);
    out.push_back(0);
    out.push_back(0);
    out.push_back(0);
    return true;
  }
  return false;
}

RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  m_objectDetectorPort.registerConsumer("Manipulation_ObjectDetectionService", "Manipulation::ObjectDetectionService", m_objectDetectionService);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_objectDetectorPort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("debug", m_debug, "1");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PlannerTesterRTC_Cnoid::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void PlannerTesterRTC_CnoidInit(RTC::Manager* manager)
  {
    coil::Properties profile(plannertesterrtc_cnoid_spec);
    manager->registerFactory(profile,
                             RTC::Create<PlannerTesterRTC_Cnoid>,
                             RTC::Delete<PlannerTesterRTC_Cnoid>);
  }
  
};


