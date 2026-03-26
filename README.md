# Optomotrist

LA-2A-style optical compressor emulator.

[![Build](https://github.com/SeedyROM/optomotrist/actions/workflows/build.yml/badge.svg)](https://github.com/SeedyROM/optomotrist/actions/workflows/build.yml)

<img width="760" height="618" alt="Screenshot 2026-03-26 at 12 12 31 AM" src="https://github.com/user-attachments/assets/a137e44d-4645-4a0e-a8ed-0b3dfe05b1ee" />

<br />
<br />

Optomotrist is a stereo optical compressor plugin modeled after the LA-2A, built around a T4 opto cell emulation with program-dependent attack/release, a soft-knee gain computer, sidechain filtering with adjustable HPF and HF emphasis, and a 12AX7-style triode saturation stage. It includes authentic front-panel controls (Input Drive, Peak Reduction, Gain, Mix, Limit/Compress) and back-panel "screw" trims (SC Emphasis, SC HPF, T4 Bias). The DSP is written in [Faust](https://faust.grame.fr/) and the UI is built with [JUCE](https://juce.com/).

The T4 cell model uses a charge accumulator to track compression history, producing the real LA-2A's characteristic behavior where release time lengthens with sustained gain reduction — the CdS photoresistor "memory" effect.

## Platforms & Formats

| Platform | Architectures | Formats |
|---|---|---|
| macOS | Universal (arm64 + x86_64) | VST3, AU, Standalone |
| macOS Legacy | x86_64 (10.13+) | VST3, AU, Standalone |
| Windows | x86_64 | VST3, Standalone |
| Linux | x86_64 | VST3, Standalone |

## Downloads

Grab the latest build from [GitHub Releases](https://github.com/SeedyROM/optomotrist/releases). CI builds run on every push to `main` and pull request. When a `v*` tag is pushed, a draft release is created automatically with per-platform zips (macOS Universal, macOS Legacy, Windows, Linux).

## Building

Requires CMake 3.22+ and a C++17 compiler. JUCE is fetched automatically during configure.

```bash
cmake -B build -G Ninja
cmake --build build --config Release
```

See [docs/building.md](docs/building.md) for platform-specific prerequisites, CMake options, and the `just` task runner.

## Faust DSP

The compressor DSP lives in `dsp/optomotrist.dsp`. A codegen script compiles the Faust source to C++ and generates a bridge layer that maps Faust parameters to JUCE's `AudioProcessorValueTreeState`. The generated files are committed to git, so you don't need Faust installed for normal builds; Faust is only required when you intentionally regenerate the DSP outputs.

See [docs/faust-codegen.md](docs/faust-codegen.md) for details on the codegen pipeline and how to modify the DSP.

## License

[AGPLv3](LICENSE)
