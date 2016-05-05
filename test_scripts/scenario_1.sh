#!/bin/bash
# Let the assessor create a test concept map

myexe="../../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper"
if [ -e /$myexe ]
then
  echo $mytestname": FAIL (executable '"$myexe"' not found)"
  exit
fi

# Start application
$myexe &
sleep 1

# Main menu, click 'Asessor'
# note: xdotool cannot find the window from its title
# xdotool windowactivate --sync "$(xdotool search --name "Menu voor de ontwikkelaar" | head -n 1)" key alt+1
# Click
xdotool mousemove 451 287 click 1
sleep 1

# Click 'Geef assessment vorm'
xdotool mousemove 634 515 click 1
sleep 1

# Click 'Create one'
xdotool mousemove 315 394 click 1

sleep 2

#xdotool windowactivate --sync "$(xdotool search --name "Kies een assessment bestand" | head -n 1)" key ctrl+a; xdotool windowactivate --sync "$(xdotool search --name "Kies een assessment bestand" | head -n 1)" key KP_Delete; xdotool type --window "$(xdotool search --name "Kies een assessment bestand" | head -n 1)" --delay 1 test.cmp; xdotool windowactivate --sync "$(xdotool search --name "Kies een assessment bestand" | head -n 1)" key KP_Enter







# Notes

# Get mouse position
xdotool getmouselocation
