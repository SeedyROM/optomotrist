#include "PluginEditor.h"
#include "BinaryData.h"
#include "PluginProcessor.h"

#include "ui/OptomotristColors.h"

#include <memory>
OptomotristAudioProcessorEditor::OptomotristAudioProcessorEditor(
    OptomotristAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p),
      inputDriveKnob(p.apvts, RuntimeParamIDs::inputDrive, "INPUT DRIVE",
                     " dB"),
      peakReductionKnob(p.apvts, RuntimeParamIDs::peakReduction,
                        "PEAK REDUCTION"),
      gainKnob(p.apvts, RuntimeParamIDs::gain, "GAIN", " dB"),
      mixKnob(p.apvts, RuntimeParamIDs::mix, "MIX", "%"),
      scEmphasisKnob(p.apvts, RuntimeParamIDs::scEmphasis, "SC EMPHASIS", "%"),
      scEmphasisFreqKnob(p.apvts, RuntimeParamIDs::scEmphasisFreq,
                         "SC EMP FREQ", " Hz"),
      scHpfKnob(p.apvts, RuntimeParamIDs::scHpf, "SC HPF", " Hz"),
      t4BiasKnob(p.apvts, RuntimeParamIDs::t4Bias, "T4 BIAS", "%") {
  setLookAndFeel(&pluginLnf);
  addAndMakeVisible(topBar);

  // --- Add controls ---
  addAndMakeVisible(inputDriveKnob);
  addAndMakeVisible(peakReductionKnob);
  addAndMakeVisible(gainKnob);
  addAndMakeVisible(mixKnob);
  addAndMakeVisible(scEmphasisKnob);
  addAndMakeVisible(scEmphasisFreqKnob);
  addAndMakeVisible(scHpfKnob);
  addAndMakeVisible(t4BiasKnob);

  // --- Limit/Compress toggle ---
  limitModeToggle.setButtonText("LIMIT");
  addAndMakeVisible(limitModeToggle);
  limitModeAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
          p.apvts, RuntimeParamIDs::limitMode, limitModeToggle);

  // --- GR meter ---
  addAndMakeVisible(grMeter);
  grMeter.setMeterSource([&p] { return p.getGainReductionDb(); });

  // --- Output meter on Gain knob ---
  gainKnob.setMeterSource([&p] { return p.getOutputMeterPeak(); });

  // --- TopBar callbacks ---
  topBar.onSelectSlotA = [this] {
    audioProcessor.setActiveABSlot(OptomotristAudioProcessor::ABSlot::A);
    topBar.setActiveABSlot(true);
    refreshPresetControls();
  };
  topBar.onSelectSlotB = [this] {
    audioProcessor.setActiveABSlot(OptomotristAudioProcessor::ABSlot::B);
    topBar.setActiveABSlot(false);
    refreshPresetControls();
  };
  topBar.onPresetSelected = [this](const juce::String &presetName) {
    if (audioProcessor.loadPreset(presetName))
      refreshPresetControls();
  };
  topBar.onShowOptionsMenu = [this] { showOptionsMenu(); };
  topBar.setActiveABSlot(audioProcessor.getActiveABSlot() ==
                         OptomotristAudioProcessor::ABSlot::A);
  refreshPresetControls();

  setResizable(true, true);
  setResizeLimits(minEditorWidth, minEditorHeight, 1072, minEditorHeight);
  setSize(minEditorWidth, minEditorHeight);

  startTimerHz(24);
}

OptomotristAudioProcessorEditor::~OptomotristAudioProcessorEditor() {
  stopTimer();
  setLookAndFeel(nullptr);
}

void OptomotristAudioProcessorEditor::timerCallback() {
  gainKnob.refreshMeter();
  grMeter.refresh();
}

void OptomotristAudioProcessorEditor::refreshPresetControls() {
  topBar.setPresetNames(audioProcessor.getAvailablePresetNames());
  topBar.setSelectedPresetName(audioProcessor.getDisplayedPresetName());
  topBar.setActiveABSlot(audioProcessor.getActiveABSlot() ==
                         OptomotristAudioProcessor::ABSlot::A);
}

void OptomotristAudioProcessorEditor::promptSavePreset() {
  auto dialog = std::make_unique<juce::AlertWindow>(
      "Save Preset", "Enter a preset name.", juce::AlertWindow::NoIcon);
  dialog->addTextEditor("presetName", audioProcessor.getActivePresetName(),
                        "Preset name");
  dialog->addButton("Save", 1);
  dialog->addButton("Cancel", 0);

  auto *dialogPtr = dialog.release();
  dialogPtr->enterModalState(
      true, juce::ModalCallbackFunction::create([this, dialogPtr](int result) {
        std::unique_ptr<juce::AlertWindow> owner(dialogPtr);
        if (result == 1 &&
            audioProcessor.saveUserPreset(
                dialogPtr->getTextEditorContents("presetName").trim()))
          refreshPresetControls();
      }),
      true);
}

void OptomotristAudioProcessorEditor::showOptionsMenu() {
  juce::PopupMenu menu;
  menu.setLookAndFeel(&pluginLnf);
  menu.addItem(1, "Copy A to B");
  menu.addItem(2, "Copy B to A");
  menu.addItem(3, "Clear A/B", audioProcessor.hasDistinctABState());
  menu.addSeparator();
  menu.addItem(4, "Save Preset...");
  menu.addItem(5, "Delete Current Preset",
               !audioProcessor.getActivePresetName().isEmpty() &&
                   !audioProcessor.isActivePresetFactory());
  menu.addItem(6, "Reveal Presets Folder");

  menu.showMenuAsync(
      juce::PopupMenu::Options().withTargetComponent(
          topBar.getOptionsTargetComponent()),
      [this](int result) {
        if (result == 1)
          audioProcessor.copyABSlot(OptomotristAudioProcessor::ABSlot::A,
                                    OptomotristAudioProcessor::ABSlot::B);
        else if (result == 2)
          audioProcessor.copyABSlot(OptomotristAudioProcessor::ABSlot::B,
                                    OptomotristAudioProcessor::ABSlot::A);
        else if (result == 3)
          audioProcessor.clearABState();
        else if (result == 4)
          promptSavePreset();
        else if (result == 5)
          audioProcessor.deleteActiveUserPreset();
        else if (result == 6)
          audioProcessor.revealPresetDirectory();

        topBar.setActiveABSlot(audioProcessor.getActiveABSlot() ==
                               OptomotristAudioProcessor::ABSlot::A);
        refreshPresetControls();
      });
}

void OptomotristAudioProcessorEditor::drawSectionPanel(
    juce::Graphics &g, juce::Rectangle<int> bounds, const juce::String &title) {
  namespace C = OptomotristColors;
  const auto fb = bounds.toFloat();
  constexpr float cornerRadius = 6.0f;

  // Background
  g.setColour(juce::Colour(C::panelBg));
  g.fillRoundedRectangle(fb, cornerRadius);

  // Border
  g.setColour(juce::Colour(C::panelBorder));
  g.drawRoundedRectangle(fb.reduced(0.5f), cornerRadius, 1.0f);

  // Section title
  if (title.isNotEmpty()) {
    g.setColour(juce::Colour(C::sectionTitle));
    g.setFont(juce::Font(11.0f, juce::Font::bold));
    g.drawText(title, bounds.getX() + 12, bounds.getY() + 2,
               bounds.getWidth() - 24, 24, juce::Justification::centredLeft);
  }
}

void OptomotristAudioProcessorEditor::paint(juce::Graphics &g) {
  namespace C = OptomotristColors;
  g.fillAll(juce::Colour(C::background));

  auto bounds = getLocalBounds();
  bounds.removeFromTop(50); // TopBar
  bounds.reduce(12, 12);    // Content padding

  const int sectionGap = 8;

  // --- Top row: COMPRESSOR (with GR inside) | OUTPUT ---
  const int topRowHeight = juce::jlimit(240, 380, (bounds.getHeight() * 2) / 3);
  auto topRow = bounds.removeFromTop(topRowHeight);
  bounds.removeFromTop(sectionGap);

  // Column widths: compressor ~60%, output ~40%
  const int totalW = topRow.getWidth() - sectionGap;
  const int compressorW = totalW * 3 / 5;

  auto compressorSection = topRow.removeFromLeft(compressorW);
  topRow.removeFromLeft(sectionGap);
  auto outputSection = topRow;

  drawSectionPanel(g, compressorSection, "COMPRESSOR");
  drawSectionPanel(g, outputSection, "OUTPUT");

  // --- Bottom row: SIDECHAIN ---
  auto bottomRow = bounds;
  drawSectionPanel(g, bottomRow, "SIDECHAIN");
}

void OptomotristAudioProcessorEditor::resized() {
  auto bounds = getLocalBounds();
  topBar.setBounds(bounds.removeFromTop(50));

  bounds.reduce(12, 12); // Content padding
  const int sectionGap = 8;
  const int sectionPadding = 8;
  const int titleHeight = 24;

  // --- Top row: COMPRESSOR (with GR inside) | OUTPUT ---
  const int topRowHeight = juce::jlimit(240, 380, (bounds.getHeight() * 2) / 3);
  auto topRow = bounds.removeFromTop(topRowHeight);
  bounds.removeFromTop(sectionGap);

  // Column widths: compressor ~60%, output ~40%
  const int totalW = topRow.getWidth() - sectionGap;
  const int compressorW = totalW * 3 / 5;

  auto compressorSection = topRow.removeFromLeft(compressorW);
  topRow.removeFromLeft(sectionGap);
  auto outputSection = topRow;

  // --- Compressor section: GR meter on top, knobs below, Limit toggle at
  // bottom ---
  {
    auto area = compressorSection.reduced(sectionPadding);
    area.removeFromTop(titleHeight);

    const int vGap = 10;
    const int toggleH = 30;
    const int knobRowH = 120; // fixed height for the knob row
    const int bottomPad = 10;

    // GR meter gets everything above the knobs + toggle + bottom padding
    const int grH =
        area.getHeight() - knobRowH - toggleH - vGap * 2 - bottomPad;

    // GR meter on top — use full section width with 20px margins
    {
      auto grArea = compressorSection;
      grArea.removeFromTop(sectionPadding + titleHeight);
      grArea = grArea.removeFromTop(grH);
      grArea.reduce(20, 0); // 20px horizontal margin
      grMeter.setBounds(grArea);
    }
    area.removeFromTop(grH);
    area.removeFromTop(vGap);

    // Knobs row: Input Drive + Peak Reduction side by side
    auto knobRow = area.removeFromTop(knobRowH);
    area.removeFromTop(vGap);
    {
      const int hGap = 8;
      const int knobW = (knobRow.getWidth() - hGap) / 2;
      inputDriveKnob.setBounds(knobRow.removeFromLeft(knobW));
      knobRow.removeFromLeft(hGap);
      peakReductionKnob.setBounds(knobRow);
    }

    // Limit toggle centred at bottom
    {
      const int toggleW = juce::jmin(80, area.getWidth());
      limitModeToggle.setBounds(area.getCentreX() - toggleW / 2,
                                area.getCentreY() - toggleH / 2, toggleW,
                                toggleH);
    }
  }

  // --- Output section: Gain + Mix stacked ---
  {
    auto area = outputSection.reduced(sectionPadding);
    area.removeFromTop(titleHeight);

    const int vGap = 6;
    const int knobH = (area.getHeight() - vGap) / 2;

    gainKnob.setBounds(area.removeFromTop(knobH));
    area.removeFromTop(vGap);
    mixKnob.setBounds(area);
  }

  // --- Bottom row: Sidechain controls ---
  auto bottomRow = bounds;
  {
    auto area = bottomRow.reduced(sectionPadding);
    area.removeFromTop(titleHeight);

    const int hGap = 8;
    const int numControls = 4;
    const int knobW =
        (area.getWidth() - hGap * (numControls - 1)) / numControls;

    auto scEmphBounds = area.removeFromLeft(knobW);
    area.removeFromLeft(hGap);
    auto scEmphFreqBounds = area.removeFromLeft(knobW);
    area.removeFromLeft(hGap);
    auto scHpfBounds = area.removeFromLeft(knobW);
    area.removeFromLeft(hGap);
    auto t4BiasBounds = area;

    scEmphasisKnob.setBounds(scEmphBounds);
    scEmphasisFreqKnob.setBounds(scEmphFreqBounds);
    scHpfKnob.setBounds(scHpfBounds);
    t4BiasKnob.setBounds(t4BiasBounds);
  }
}
