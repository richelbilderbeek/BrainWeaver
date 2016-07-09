#!/bin/bash
# Let the assessor create a test concept map with name 'scenario1.cmp'

# Load scripts
. ../../testing_cpp_gui_applications_tutorial/scripts/get_dialog_id.sh

# Variables
myexe="../../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper"
mycmp="scenario2.cmp"

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
if [ -e $mycmp ]
then
 echo "Warning: file '"$mycmp"' existed, but is now deleted"
  rm $mycmp
fi
if [ -e $mycmp ]
then
  echo "File could not be deleted, line "$LINENO
  exit 1
fi

####################################
# Start application
####################################
#$myexe &
#sleep 1

####################################
# Main menu, choose '2. Assessor'
####################################
id=`get_dialog_id "Menu voor de ontwikkelaar"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+2 sleep 0.2

####################################
# 'Mijn persoonlijke werktheorie', choose '&Geef assessment vorm'
####################################
id=`get_dialog_id "Mijn persoonlijke werktheorie, programma voor de assessor"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+g sleep 0.2

####################################
# 'Formuleer de focusvraag', 
# type a focal question
####################################
id=`get_dialog_id "Formuleer de focusvraag"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id type "Good focal questions are ..."

####################################
# 'Formuleer de focusvraag', 
# save
####################################
id=`get_dialog_id "Formuleer de focusvraag"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id sleep 0.2 key alt+s sleep 0.3

####################################
# 'Sla het assessment invoer-bestand op', 
# save as scenario_1
####################################
id=`get_dialog_id "Sla het assessment invoer-bestand op"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id sleep 0.2 type $mycmp
xdotool windowactivate $id sleep 0.2 key Return sleep 0.2

####################################
# 'Mijn persoonlijke werktheorie', choose '&Stoppen'
####################################
id=`get_dialog_id "Mijn persoonlijke werktheorie, programma voor de assessor"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+s sleep 0.2

####################################
# Checking saved file
####################################
if [ ! -e $mycmp ]
then
  echo "File should have been created, line "$LINENO
  exit 1
fi

####################################
# Main menu, close
####################################
id=`get_dialog_id "Menu voor de ontwikkelaar"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+F4


echo "File '"$mycmp"' is created successfully"