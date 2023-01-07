#pragma once
#include <string>
#include "orifice/orificeflow.h"

namespace zone_pressure {

class Leak {
 public:
  Leak() = default;
  ~Leak() = default;
  Leak(std::string name, double orifice_diameter, double discharge_coefficient,
       double temperature);
  double CalculateFlowFromZone(std::string requestee_zone_id,
                               double requestee_zone_pressure);
  void SetZones(std::string zone_a_id, std::string zone_b_id);
  void SetZonePressure(std::string requestee_zone_id,
                       double requestee_zone_pressure);
  double get_size() { return orifice_diameter_; }
  std::string get_leak_name() { return leak_name_; }
  std::string zoneA() {return zone_a_id_;}
  std::string zoneB() {return zone_b_id_;}

 private:
  std::string leak_name_;
  std::string zone_a_id_;
  std::string zone_b_id_;
  double orifice_diameter_;
  double discharge_coefficient_;
  double temperature_;
  double zone_a_pressure_;
  double zone_b_pressure_;
};

}  // namespace zone_pressure
