# MissionControl
Repo for the Mission Control software used by Cosmic Research in its launchments.

You will need an Arduino Uno, running the [RadioReceiver](https://github.com/CosmicResearch/RadioReceiver) software, with a RFM69 transceiver connected via USB to your computer; and a RaspberryPi running our [GuidanceComputer](https://github.com/CosmicResearch/GuidanceComputer) software with the same transceiver connected.

This software will show you all the data sent by the RaspberryPi and, if you have a GPS connected, the location in a map.

We use this for our rockets launchments, but you can use it for whatever you want, like a drone or a boat.

##Build instructions
```
git clone https://github.com/CosmicResearch/MissionControl.git
cd MissionControl
qmake
make
```
## License

Copyright 2017, Associació Cosmic Research.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
