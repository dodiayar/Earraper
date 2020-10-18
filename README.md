# Earraper
![CMake](https://github.com/dodiayar/Earraper/workflows/CMake/badge.svg)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/2e97e24d37ec498fb4df204b1bcd4d45)](https://www.codacy.com/gh/dodiayar/Earraper/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=dodiayar/Earraper&amp;utm_campaign=Badge_Grade)

This app simply boosts your microphone so it sounds like earrape. You might want to use a software like Virtual Audio Cable to send the output to an input device.

## Download
You can find the downloads in the [Release](https://github.com/dodiayar/Earraper/releases) section or you can build it yourself by downloading the source code.

## Usage
You can simply run the binary file and press Enter to boost your microphone. Pressing Enter again will stop boosting your microphone. There are also some options you can change:

 - **boost:** The boost level
 - **playback**: The playback device
 - **recording**: The recording device

For example you can run the app like this:

    Earraper --boost=60 --playback=1 --recording=2

## Dependencies

This project depends on [Miniaudio](https://github.com/mackron/miniaudio), [Rang](https://github.com/agauniyal/rang) and [Flags](https://github.com/sailormoon/flags) libraries.
