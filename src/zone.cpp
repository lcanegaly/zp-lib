#include "zone.h"

namespace zone_pressure {

Zone::Zone()
    : zone_id_{},
      equal_flow_{false},
      pressure_{0.0},
      temperature_{70},
      flow_in_{0.0},
      flow_out_{0.0},
      pressure_tick_{0.001} {}

Zone::Zone(const Zone& z)
    : zone_id_{z.zone_id_},
      leaks_{z.leaks_},
      equal_flow_{false},
      pressure_{z.pressure_},
      temperature_{z.temperature_},
      flow_in_{z.flow_in_},
      flow_out_{z.flow_out_},
      pressure_tick_{0.001} {}

Zone::Zone(std::string zone_id)
    : zone_id_{zone_id},
      equal_flow_{false},
      pressure_{0.0},
      temperature_{70},
      flow_in_{0.0},
      flow_out_{0.0},
      pressure_tick_{0.001} {}

double Zone::get_pressure() { return pressure_; }

double Zone::get_flow() { return flow_out_; }

void Zone::UpdateZone(double input_flow) {
  if (flow_out_ - flow_in_ > 2) {
    pressure_ = pressure_tick_;
    pressure_tick_ /= 10;
  }
  UpdateFlows(input_flow);
  UpdatePressure();
}

// Add a leak to a zone, choose which side to attach.
void Zone::AddLeak(Leak* leak, char zone) {
  if (zone == 'a') leak->SetZones(zone_id_, "");
  if (zone == 'b') leak->SetZones("", zone_id_);

  if (leaks_.size() == 0)
    leaks_.push_back(leak);
  else {
    for (int i = 0; i < leaks_.size(); i++) {
      if (leak->get_leak_name() == leaks_[i]->get_leak_name())
        leaks_[i] = leak;
      else {
        leaks_.push_back(leak);
        return;
      }
    }
  }
}

void Zone::AddLeak(Leak* leak) {
  if (leak->zoneA() == "" && leak->zoneB() =="") 
    leak->SetZones(zone_id_, "");
  else if (leak->zoneA() != "" && leak->zoneB() == "")
    leak->SetZones("", zone_id_);

  if (leaks_.size() == 0)
    leaks_.push_back(leak);
  else {
    for (int i = 0; i < leaks_.size(); i++) {
      if (leak->get_leak_name() == leaks_[i]->get_leak_name())
        leaks_[i] = leak;
      else {
        leaks_.push_back(leak);
        return;
      }
    }
  }
}

void Zone::UpdateFlows(double input_flow) {
  flow_in_ = input_flow;
  flow_out_ = 0;
  for (auto x : leaks_) {
    double flow = x->CalculateFlowFromZone(zone_id_, pressure_);
    if (flow > 0)
      flow_out_ += flow;
    else if (flow < 0)
      flow_in_ += -flow;
  }
}

void Zone::UpdatePressure() {
  if (flow_in_ > flow_out_)
    pressure_ += pressure_tick_;
  else if (flow_in_ < flow_out_)
    pressure_ -= pressure_tick_;

  for (auto x : leaks_) {
    x->SetZonePressure(zone_id_, pressure_);
  }
}

}  // namespace zone_pressure
