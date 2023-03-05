#pragma once

class Connection {
private:
  double m_weight, m_delta_weight;

public:
  Connection();
  double get_weight() const;
  double get_delta_weight() const;
  void set_weight(double weight);
  void set_delta_weight(double delta);
};