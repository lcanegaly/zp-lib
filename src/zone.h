#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "leak.h"

namespace zone_pressure {

class Zone {
 public:
  Zone();
  Zone(const Zone& z);
  Zone(std::string zone_id);
  void UpdateZone(double input_flow);
  void AddLeak(Leak* leak, char zone);
  double get_pressure();
  double get_flow();
  std::string get_zone_id() { return zone_id_; }
  std::vector<Leak*> get_leaks() { return leaks_; }

 private:
  void UpdateFlows(double input_flow);
  void UpdatePressure();
  std::string zone_id_;
  std::vector<Leak*> leaks_;
  bool equal_flow_ = false;
  double pressure_;
  double temperature_;
  double flow_in_;
  double flow_out_;
  double pressure_tick_;
};

}  // namespace zone_pressure
