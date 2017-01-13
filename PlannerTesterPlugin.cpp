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
  bar->addLabel("PlannerTesterPlugin");
  bar->addSeparator();
  //bar->addButton("Test")->sigClicked().connect(boost::bind(&PlannerTesterPlugin::onTest, this));
  bar->addLabel("ObjectName:");  
  textEdit = new cnoid::PlainTextEdit();
  textEdit->setPlainText("object");
  textEdit->setFixedHeight(40);
  bar->addWidget(textEdit);
  bar->addButton("DetectObject")->sigClicked().connect(boost::bind(&PlannerTesterPlugin::onClickDetectObject, this));
  addToolBar(bar);
  RTC::Manager& rtcManager = RTC::Manager::instance();
  PlannerTesterRTC_CnoidInit(&rtcManager);
  const char* param = "PlannerTesterRTC_Cnoid?instance_name=PlannerTesterRTC_Cnoid&exec_cxt.periodic.type=PeriodicExecutionContext&exec_cxt.periodic.rate=30";
  RTObject_impl* rtc = rtcManager.createComponent(param);
  plannerRTC = dynamic_cast<PlannerTesterRTC_Cnoid*>(rtc);

  double radius = 1;
  cmMarker = new cnoid::CrossMarker(radius, cnoid::Vector3f(1.0f, 1.0f, 0.1f), 2.0);

  
  return true;
}

void PlannerTesterPlugin::onClickDetectObject() {
  std::cout << "Let's detect " << textEdit->toPlainText().toStdString() << std::endl;
  std::vector<double> out;
  if (plannerRTC->detectObject(textEdit->toPlainText().toStdString(), out)) {
    std::cout << " - OK" << std::endl;
    std::cout << " (";
    for(int i = 0;i < 6;i++) {
      std::cout << out[i] << ", ";
    }
    std::cout << ")" << std::endl;
    cmMarker->setTranslation(cnoid::Vector3(out[0],out[1],out[2]));    
    cnoid::ItemList<cnoid::BodyItem> items = cnoid::ItemTreeView::instance()->checkedItems<cnoid::BodyItem>();
    if (items.size() == 0) {
      std::cout << "Item not found." << std::endl;
      return;
    }
    
    
    cnoid::BodyItemPtr b = items[0];
    b->sceneBody()->addChildOnce(cmMarker, true);
    
  }
}

void PlannerTesterPlugin::onTest() {

  std::cout << "onTest" << std::endl;
    
}

//////
CNOID_IMPLEMENT_PLUGIN_ENTRY(PlannerTesterPlugin)
