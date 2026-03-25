#pragma once

#include "ui/OptomotristColors.h"
#include <juce_gui_basics/juce_gui_basics.h>

#include <functional>

/**
 * Minimalist analog VU-style gain reduction meter.
 *
 * Displays a swept arc with tick marks (0-40 dB) and a needle
 * that deflects left as gain reduction increases.  Driven by a
 * meter source function that returns GR in dB (negative, e.g. -6
 * means 6 dB of reduction).  Call refresh() at ~24 Hz from the
 * editor timer.
 */
class GainReductionMeter : public juce::Component {
public:
  GainReductionMeter();
  ~GainReductionMeter() override = default;

  void paint(juce::Graphics &g) override;
  void resized() override;

  /** Supply a function that returns gain reduction in dB (range -60..0). */
  void setMeterSource(std::function<float()> source);

  /** Call at ~24 Hz to update the needle position with ballistic smoothing. */
  void refresh();

private:
  std::function<float()> meterSource;

  float displayGrDb = 0.0f; // ballistic-smoothed value for display

  // Arc geometry (computed in resized)
  float arcCentreX = 0.0f;
  float arcCentreY = 0.0f;
  float arcRadius = 0.0f;
  float arcStartAngle = 0.0f; // left side (40 dB)
  float arcEndAngle = 0.0f;   // right side (0 dB)

  static constexpr float maxDisplayDb = 40.0f;
  static constexpr float arcSweepDegrees = 180.0f;

  float grDbToAngle(float grDb) const;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainReductionMeter)
};
