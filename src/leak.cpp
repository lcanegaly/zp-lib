#include "leak.h"

namespace zone_pressure {

Leak::Leak(std::string name, double orifice_diameter,
           double discharge_coefficient, double temperature)
    : leak_name_{name},
      zone_a_id_{""},
      zone_b_id_{""},
      orifice_diameter_{orifice_diameter},
      discharge_coefficient_{discharge_coefficient},
      temperature_{temperature},
      zone_a_pressure_{0},
      zone_b_pressure_{0} {}

double Leak::CalculateFlowFromZone(std::string requestee_zone_id,
                                   double requestee_zone_pressure) {
  double pa = (requestee_zone_id == zone_a_id_)
                  ? requestee_zone_pressure - zone_b_pressure_
                  : requestee_zone_pressure - zone_a_pressure_;
  return orifice_flow::OrificeFlowCfm(0.0, orifice_diameter_, 70.0, pa,
                                      discharge_coefficient_);
}

void Leak::SetZones(std::string zone_a_id, std::string zone_b_id) {
  zone_a_id_ = (zone_a_id == "") ? zone_a_id_ : zone_a_id;
  zone_b_id_ = (zone_b_id == "") ? zone_b_id_ : zone_b_id;
}

void Leak::SetZonePressure(std::string requestee_zone_id,
                           double requestee_zone_pressure) {
  if (requestee_zone_id == zone_a_id_) {
    zone_a_pressure_ = requestee_zone_pressure;
  } else if (requestee_zone_id == zone_b_id_) {
    zone_b_pressure_ = requestee_zone_pressure;
  }
}

}  // namespace zone_pressure

