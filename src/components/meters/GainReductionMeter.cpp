#include "GainReductionMeter.h"

#include <cmath>

namespace {

// Tick mark definitions: {dB value, isMajor}
struct TickMark {
  float db;
  bool isMajor;
};

// VU-style gain reduction scale markings
// Arc goes from 40 (left) to 0 (right)
constexpr TickMark tickMarks[] = {
    {0.0f, true},   {1.0f, true},   {2.0f, true},  {3.0f, true},
    {4.0f, false},  {5.0f, true},   {6.0f, false},  {7.0f, true},
    {8.0f, false},  {9.0f, false},  {10.0f, true},
    {12.0f, false}, {15.0f, true},  {20.0f, true},
    {25.0f, false}, {30.0f, true},  {40.0f, true},
};

constexpr int numTicks = sizeof(tickMarks) / sizeof(tickMarks[0]);

} // namespace

GainReductionMeter::GainReductionMeter() {}

void GainReductionMeter::setMeterSource(std::function<float()> source) {
  meterSource = std::move(source);
}

void GainReductionMeter::refresh() {
  if (!meterSource)
    return;

  // meterSource returns negative dB (e.g. -6.0 means 6dB of reduction)
  const float rawGrDb = meterSource();
  // Convert to positive dB for display (0 = no reduction, 6 = 6dB reduction)
  const float targetGrDb = juce::jlimit(0.0f, maxDisplayDb, -rawGrDb);

  // Ballistic smoothing: fast rise (~50ms), slower fall (~300ms)
  // At 24Hz refresh rate: rise coefficient ~0.7, fall coefficient ~0.15
  constexpr float riseCoeff = 0.7f;
  constexpr float fallCoeff = 0.15f;

  if (targetGrDb > displayGrDb)
    displayGrDb += (targetGrDb - displayGrDb) * riseCoeff;
  else
    displayGrDb += (targetGrDb - displayGrDb) * fallCoeff;

  // Snap to zero when very close
  if (displayGrDb < 0.05f)
    displayGrDb = 0.0f;

  repaint();
}

float GainReductionMeter::grDbToAngle(float grDb) const {
  // Map 0 dB -> arcEndAngle (right), maxDisplayDb -> arcStartAngle (left)
  // Use a slightly logarithmic-ish mapping so lower dB values get more space
  // (like a real VU meter where 0-10 takes more arc than 10-40)
  const float norm = grDb / maxDisplayDb;

  // Apply a gentle curve: sqrt gives more space to low values
  const float curved = std::sqrt(norm);

  // 0 dB = right side (arcEndAngle), 40 dB = left side (arcStartAngle)
  return arcEndAngle + curved * (arcStartAngle - arcEndAngle);
}

void GainReductionMeter::resized() {
  const auto bounds = getLocalBounds().toFloat();

  const float availableWidth = bounds.getWidth();
  const float availableHeight = bounds.getHeight();

  // Reserve space for labels below the arc (~24px) and above (~14px for tick labels)
  const float labelMarginBottom = 24.0f;
  const float labelMarginTop = 14.0f;
  const float usableHeight = availableHeight - labelMarginBottom;

  // For a 180° half-circle: width = 2*radius, height = radius + margins
  // Radius is limited by whichever dimension is tighter
  arcRadius = juce::jmin((availableWidth - 40.0f) * 0.5f,
                          usableHeight - labelMarginTop);
  arcRadius = juce::jmax(arcRadius, 20.0f); // minimum sanity

  // Pivot point: centred horizontally, positioned so arc fits with bottom margin
  arcCentreX = bounds.getCentreX();
  arcCentreY = bounds.getBottom() - labelMarginBottom;

  // Arc sweep: full 180 degrees (half circle)
  // Left side = arcStartAngle (40 dB), right side = arcEndAngle (0 dB)
  constexpr float pi = juce::MathConstants<float>::pi;
  arcStartAngle = -pi;         // left (9 o'clock) = 40 dB
  arcEndAngle = 0.0f;          // right (3 o'clock) = 0 dB
}

void GainReductionMeter::paint(juce::Graphics &g) {
  namespace C = OptomotristColors;

  if (arcRadius <= 0.0f)
    return;

  const float majorTickOuterRadius = arcRadius;
  const float majorTickInnerRadius = arcRadius - 10.0f;
  const float minorTickOuterRadius = arcRadius;
  const float minorTickInnerRadius = arcRadius - 6.0f;
  const float labelRadius = arcRadius - 22.0f;
  const float needleLength = arcRadius - 34.0f;

  // -- Draw the arc path (subtle background arc) --
  // JUCE addCentredArc uses angles where 0 = 12 o'clock, pi/2 = 3 o'clock
  // Convert from our math angles (0 = right, -pi = left) to JUCE angles
  // Math -pi (left) -> JUCE -pi/2, Math 0 (right) -> JUCE pi/2
  {
    constexpr float pi = juce::MathConstants<float>::pi;
    juce::Path arcBg;
    arcBg.addCentredArc(arcCentreX, arcCentreY, arcRadius, arcRadius,
                        0.0f, -pi * 0.5f, pi * 0.5f, true);
    g.setColour(juce::Colour(C::panelBorder).withAlpha(0.35f));
    g.strokePath(arcBg,
                 juce::PathStrokeType(1.5f,
                                      juce::PathStrokeType::curved,
                                      juce::PathStrokeType::rounded));
  }

  // -- Draw tick marks and labels --
  g.setFont(juce::Font(10.0f, juce::Font::plain));

  for (int i = 0; i < numTicks; ++i) {
    const auto &tick = tickMarks[i];
    const float angle = grDbToAngle(tick.db);
    const float cosA = std::cos(angle);
    const float sinA = std::sin(angle);

    const float outerR = tick.isMajor ? majorTickOuterRadius : minorTickOuterRadius;
    const float innerR = tick.isMajor ? majorTickInnerRadius : minorTickInnerRadius;

    // Tick line
    g.setColour(tick.isMajor ? juce::Colour(C::labelText).withAlpha(0.55f)
                             : juce::Colour(C::labelText).withAlpha(0.3f));
    g.drawLine(arcCentreX + innerR * cosA,
               arcCentreY + innerR * sinA,
               arcCentreX + outerR * cosA,
               arcCentreY + outerR * sinA,
               tick.isMajor ? 1.2f : 0.8f);

    // Label (major ticks only)
    if (tick.isMajor) {
      const auto labelText =
          tick.db == 0.0f ? juce::String("0") : juce::String(juce::roundToInt(tick.db));
      const float lx = arcCentreX + labelRadius * cosA;
      const float ly = arcCentreY + labelRadius * sinA;

      g.setColour(juce::Colour(C::labelText).withAlpha(0.7f));
      g.drawText(labelText,
                 juce::Rectangle<float>(lx - 14.0f, ly - 8.0f, 28.0f, 16.0f),
                 juce::Justification::centred,
                 false);
    }
  }

  // -- Draw the needle --
  {
    const float needleAngle = grDbToAngle(displayGrDb);
    const float cosA = std::cos(needleAngle);
    const float sinA = std::sin(needleAngle);

    // Needle shadow
    g.setColour(juce::Colour(0x20000000));
    g.drawLine(arcCentreX + 1.0f,
               arcCentreY + 1.0f,
               arcCentreX + needleLength * cosA + 1.0f,
               arcCentreY + needleLength * sinA + 1.0f,
               2.0f);

    // Needle
    g.setColour(juce::Colour(C::knobPointer));
    g.drawLine(arcCentreX,
               arcCentreY,
               arcCentreX + needleLength * cosA,
               arcCentreY + needleLength * sinA,
               1.8f);
  }

  // -- "GR" label --
  {
    g.setColour(juce::Colour(C::sectionTitle));
    g.setFont(juce::Font(11.0f, juce::Font::bold));
    g.drawText("GR",
               juce::Rectangle<float>(arcCentreX - 20.0f,
                                       arcCentreY - arcRadius * 0.25f,
                                       40.0f,
                                       16.0f),
               juce::Justification::centred,
               false);
  }
}
