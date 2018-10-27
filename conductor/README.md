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