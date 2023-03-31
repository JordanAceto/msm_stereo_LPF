## PCB design and documentation files

### The system is made up of several printed circuit boards
- `compression_and_distortion` has an NE570 compressor and FET distortion circuit
- `lowpass_filters` contains the voltage controlled lowpass filters
- `envelope_follower` is an analog envelope follower
- `LFO_and_PS` contains a regulated bipolar DC power supply and digital LFO

### Each circuit board has a subdirectory with
- KiCad 6 project files with KiCad
- Documentation needed to build the board in `docs`
- HTML file `index.html` for easy navigation of the documentation files
