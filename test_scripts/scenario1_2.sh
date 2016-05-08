#!/bin/bash
# Let the student work on the concept map

# Load scripts
. ../../testing_cpp_gui_applications_tutorial/scripts/get_dialog_id.sh

# Variables
myexe="../../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper"
mycmp="scenario1.cmp"

####################################
# Check executable
####################################
if [ -e /$myexe ] # slash is obligatory?
then
  echo $mytestname": FAIL (executable '"$myexe"' not found)"
  exit
fi

####################################
# Delete saving file
####################################
if [ ! -e $mycmp ]
then
  echo "File "$mycmp" not found, line "$LINENO
  exit 1
fi

####################################
# Start application
####################################
$myexe &
sleep 1

####################################
# Main menu, choose '1. Student'
####################################
id=`get_dialog_id "Menu voor de ontwikkelaar"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+1 sleep 0.2

####################################
# 'Kies een assessment bestand'
####################################
id=`get_dialog_id "Kies een assessment bestand"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete key Delete
# Type filename
xdotool windowactivate $id type $mycmp
# OK
xdotool windowactivate $id key alt+o sleep 0.1

####################################
# 'Mijn persoonlijke werktheorie, programma voor de student'
# Type your name
####################################
id=`get_dialog_id "Mijn persoonlijke werktheorie, programma voor de student"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id type "John Doe"
# &Begin
xdotool windowactivate $id key alt+b sleep 0.2

####################################
# 'Mijn persoonlijke werktheorie, programma voor de student'
# Beginnen mey &Associeren
####################################
id=`get_dialog_id "Mijn persoonlijke werktheorie, programma voor de student"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
# &Associate
xdotool windowactivate $id key alt+a sleep 0.1



####################################
# 'Associeer- en cluster-scherm'
# Add some associations
####################################
id=`get_dialog_id "Associeer- en cluster-scherm"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
# Text to add
xdotool windowactivate $id type "hard to make up"
# Add 
xdotool windowactivate $id key Tab Return
# Text to add
xdotool windowactivate $id type "concise"
# Add 
xdotool windowactivate $id key Tab Return
# Text to add
xdotool windowactivate $id type "precise"
# Add 
xdotool windowactivate $id key Tab Return
# Text to add
xdotool windowactivate $id type "English"
# Add 
xdotool windowactivate $id key Tab Return
# Text to add
xdotool windowactivate $id type "not too long"
# Add 
xdotool windowactivate $id key Tab Return






