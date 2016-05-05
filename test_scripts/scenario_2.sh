#!/bin/bash
# Test if a concept item shows a hand cursor when hovering over it

myexe="../../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper"
if [ -e /$myexe ]
then
  echo $mytestname": FAIL (executable '"$myexe"' not found)"
  exit
fi

# Start application
$myexe &
sleep 1

# Main menu, click 'Student
# note: xdotool cannot find the window from its title
# xdotool windowactivate --sync "$(xdotool search --name "Menu voor de ontwikkelaar" | head -n 1)" key alt+1
# Click
xdotool mousemove 417 261 click 1

sleep 1

xdotool windowactivate --sync "$(xdotool search --name "Kies een assessment bestand" | head -n 1)" key ctrl+a; xdotool windowactivate --sync "$(xdotool search --name "Kies een assessment bestand" | head -n 1)" key KP_Delete; xdotool type --window "$(xdotool search --name "Kies een assessment bestand" | head -n 1)" --delay 1 test.cmp; xdotool windowactivate --sync "$(xdotool search --name "Kies een assessment bestand" | head -n 1)" key KP_Enter







# Notes

# Get mouse position
#xdotool getmouselocation
