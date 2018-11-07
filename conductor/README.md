# Conductor

## About

Environment for LED screen control and low latency playback of SDI/BNC input using Decklink devices

## Setup

### GUI

Double click on `install.sh` or run in terminal

```bash
bash install.sh
```

### Terminal

Create the following directories.

```bash
mkdir build
```

### Build

```bash
make
```

### Run

```bash
./conductor.out
```

### Decklink using GStreamer

This is the current basic pipeline in use 
```bash
gst-launch-1.0 -v decklinkvideosrc mode=0 connection=2 timecode-format=6 ! videoconvert ! xvimagesink
```

### Dependencies (Ubuntu)

These are the required dependencies to build and run the GUI application.

```bash
sudo apt install build-essential libgstreamer1.0-dev libgtk-3-dev libwebkit2gtk-4.0-dev libgstreamer-plugins-bad1.0-dev libconfig-dev
```
Blackmagic Decklink Drivers for Linux: [Download](https://www.blackmagicdesign.com/support/family/capture-and-playback)
