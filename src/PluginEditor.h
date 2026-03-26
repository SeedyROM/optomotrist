#pragma once

#include "PluginProcessor.h"
#include "components/brand/TopBar.h"
#include "components/controls/RotaryKnob.h"
#include "components/meters/GainReductionMeter.h"

#include "data/RuntimeParameters.h"
#include "ui/PluginLookAndFeel.h"
#include <juce_audio_processors/juce_audio_processors.h>

class OptomotristAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        private juce::Timer {
public:
  OptomotristAudioProcessorEditor(OptomotristAudioProcessor &);
  ~OptomotristAudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  void timerCallback() override;
  void showOptionsMenu();
  void promptSavePreset();
  void refreshPresetControls();

  void drawSectionPanel(juce::Graphics &g, juce::Rectangle<int> bounds,
                        const juce::String &title);

  static constexpr int minEditorWidth = 760;
  static constexpr int minEditorHeight = 620;
  OptomotristAudioProcessor &audioProcessor;

  PluginLookAndFeel pluginLnf;
  TopBar topBar;

  // --- Main controls ---
  RotaryKnob inputDriveKnob;
  RotaryKnob peakReductionKnob;
  RotaryKnob gainKnob;
  RotaryKnob mixKnob;

  // --- Limit/Compress toggle ---
  juce::ToggleButton limitModeToggle;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
      limitModeAttachment;

  // --- Sidechain / Character controls ---
  RotaryKnob scEmphasisKnob;
  RotaryKnob scEmphasisFreqKnob;
  RotaryKnob scHpfKnob;
  RotaryKnob t4BiasKnob;

  // --- Gain reduction meter ---
  GainReductionMeter grMeter;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OptomotristAudioProcessorEditor)
};
