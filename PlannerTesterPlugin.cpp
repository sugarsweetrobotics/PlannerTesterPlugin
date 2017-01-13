/**
 *   @author Yuki Suga at SSR
 */

#include <cnoid/ItemTreeView>
#include <cnoid/LazyCaller>
#include <cnoid/BodyItem>
#include <cnoid/WorldItem>
#include <cnoid/ToolBar>
#include <cnoid/OpenRTMUtil>
#include <cnoid/MessageView>
#include <boost/bind.hpp>
#include <cnoid/SceneMarkers>
#include <cnoid/SceneView>
#include <cnoid/EditableSceneBody>
#include "PlannerTesterPlugin.h"

#include "PlannerTesterRTC_Cnoid.h"

/**
 * Constructor
 */
PlannerTesterPlugin::PlannerTesterPlugin() : cnoid::Plugin("PlannerTester") {
  require("Body");
  require("OpenRTM");
}


/**
 */
bool PlannerTesterPlugin::initialize() {
  cnoid::ToolBar* bar = new cnoid::ToolBar("PlannerTester");
  bar->addButton("PlannerTest")->sigClicked().connect(boost::bind(&PlannerTesterPlugin::onTest, this));
  addToolBar(bar);

  RTC::Manager& rtcManager = RTC::Manager::instance();
  PlannerTesterRTC_CnoidInit(&rtcManager);
  const char* param = "PlannerTesterRTC_Cnoid?instance_name=PlannerTesterRTC_Cnoid&exec_cxt.periodic.type=PeriodicExecutionContext&exec_cxt.periodic.rate=30";
  RTObject_impl* rtc = rtcManager.createComponent(param);
  plannerRTC = dynamic_cast<PlannerTesterRTC_Cnoid*>(rtc);

  double radius = 1;
  cmMarker = new cnoid::CrossMarker(radius, cnoid::Vector3f(1.0f, 1.0f, 0.1f), 2.0);
  cmMarker->setTranslation(cnoid::Vector3(0,0,0.5));
  
  return true;
}


void PlannerTesterPlugin::onTest() {

  std::cout << "onTest" << std::endl;
  cnoid::ItemList<cnoid::BodyItem> items = cnoid::ItemTreeView::instance()->checkedItems<cnoid::BodyItem>();
  if (items.size() == 0) {
    std::cout << "Item not found." << std::endl;
    return;
  }

  
  cnoid::BodyItemPtr b = items[0];
  b->sceneBody()->addChild(cmMarker, true);
    
}

//////
CNOID_IMPLEMENT_PLUGIN_ENTRY(PlannerTesterPlugin)
