#pragma once

/**
 *   @author Yuki Suga at SSR
 */

#include <cnoid/IdPair>
#include <cnoid/Plugin>
#include <src/Base/TextEdit.h>
#include <cnoid/CollisionDetector>

#include <map>
/// Reference class 
class PlannerTesterRTC_Cnoid;

enum RETVAL {
  RETVAL_OK,
  RETVAL_MODEL_NOT_FOUND,
  RETVAL_INVALID_PRECONDITION,
  RETVAL_INVALID_JOINT_NUM,
};

struct Return_t {
Return_t() : returnValue(RETVAL_OK), message("OK") {};
Return_t(RETVAL returnValue_, const std::string& message_): returnValue(returnValue_), message(message_) {};
  
  RETVAL returnValue;
  std::string message;
};



/**
 * Plugin Class
 */
class PlannerTesterPlugin : public cnoid::Plugin {
private:
  PlannerTesterRTC_Cnoid* plannerRTC;

public:

  
  /**
   * Constructor
   */
  PlannerTesterPlugin();

public:
  /**
   * Initialization Function called by System
   */
  virtual bool initialize();


  void onTest();
  void onClickDetectObject();


  cnoid::CrossMarkerPtr cmMarker;
  cnoid::PlainTextEdit* textEdit;
};


