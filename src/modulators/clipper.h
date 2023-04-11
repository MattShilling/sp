#pragma once

#include "analysis/unit_utils.h"

class Clipper {
public:
  Clipper(double threshold_db);
  double clip(double amplitude);

private:
  double threshold_db_;
  double threshold_amplitude_;
};
