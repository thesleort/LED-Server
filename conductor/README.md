# Conductor

## About

Environment for LED screen control and low latency playback of SDI/BNC input using Decklink devices

## Setup

### GUI

Double click on `install.sh` or run in terminal

```bash
./install.sh
```

### Terminal

### Build

```bash
make
```

### Run

```bash
./conductor.out
```

### Configuration

Settings will be saved in `$HOME/.config/conductor/conductor.cfg`. All settings, but one, can currently be set using the GUI. The input device / decklink recorder, has to be set in the config, as there
is currently no way of setting that in the GUI. By default the input device is set to 0.

### Decklink using GStreamer

This is the current basic pipeline in use.
Device number may have to be changed depending on your setup. `connection=1` is for SDI input and `connection=2` is for HDMI input.

```bash
gst-launch-1.0 decklinkvideosrc device-number=1 mode=0 connection=2 ! tee name=t ! queue ! videoconvert ! xvimagesink sync=false t. ! queue ! videoconvert ! xvimagesink sync=false
```
Test output to Decklink Monitor
```bash
gst-launch-1.0 videotestsrc ! decklinkvideosink
```

### Dependencies (Ubuntu)

These are the required dependencies to build and run the GUI application.

```bash
sudo apt install build-essential libgstreamer1.0-dev libgtk-3-dev libwebkit2gtk-4.0-dev libgstreamer-plugins-bad1.0-dev libconfig-dev
```
Blackmagic Decklink Drivers for Linux: [Download](https://www.blackmagicdesign.com/support/family/capture-and-playback)

## Remove

```bash
./remove.sh
```