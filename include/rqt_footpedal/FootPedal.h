#ifndef rqt_footpedal__footpedal_H
#define rqt_footpedal__footpedal_H

#include <rqt_gui_cpp/plugin.h>
#include <ui_FootPedal_gui.h>
#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QKeyEvent>
#include "ros/ros.h"
#include "std_msgs/Bool.h"



namespace rqt_footpedal {

class FootPedal
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  FootPedal();
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

  // Comment in to signal that the plugin has a way to configure it
  //bool hasConfiguration() const;
  //void triggerConfiguration();

	bool eventFilter(QObject *target, QEvent *event);

protected slots:
  void setFocus(void);

private:
  Ui::FootPedal_gui ui_;
  QWidget* widget_;

  ros::Publisher pubLeft_;
  ros::Publisher pubMiddle_;
  ros::Publisher pubRight_;

  void publishLeft(bool currentState);
  void publishMiddle(bool currentState);
  void publishRight(bool currentState);
};
} // namespace
#endif // my_namespace__my_plugin_H
