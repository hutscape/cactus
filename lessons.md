# Lessons Learnt

> Good practices to continue for future projects

- Always buy electronics modules for `V1.0` *Make it work, make it right, make it better*
- Ensure main BOM components are available from vendors before schematic or layout
- Do a power tree analysis starting with power source before the schematic design
- Test out paper mockups for mechanical dimensions
- Do a mechanical consideration before laying out the footprint
- Check pin, pitch, manufacturer part number, function before buying BOM parts
- Design a power on/off switch to start/stop using the battery
- Leave out the module's on-board LED as a possible separate indicator E.g. Not linking `GPIO02` to `EN` for the shift register
- Ensure the mechanical housing has an opening above any environmental sensors E.g humidity, UV index, air pressure
