#!/bin/bash
# Let the assessor create a test concept map with name 'scenario1.cmp'
# Assumes BrainweaverDeveloper is already running

# Load scripts
. ../../testing_cpp_gui_applications_tutorial/scripts/get_dialog_id_by_title

# Variables
mycmp="scenario1.cmp"

####################################
# Delete save file
####################################
if [ -e $mycmp ]
then
 echo "Warning: file '"$mycmp"' existed, but is now deleted"
  rm $mycmp
fi

####################################
# Main menu, choose '2. Assessor'
####################################
id=`get_dialog_id_by_title "Menu voor de ontwikkelaar"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+2 sleep 0.2

####################################
# 'Mijn persoonlijke werktheorie', choose '&Geef assessment vorm'
####################################
id=`get_dialog_id_by_title "Mijn persoonlijke werktheorie, programma voor de assessor"`
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
id=`get_dialog_id_by_title "Formuleer de focusvraag"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id type --delay 20 "Good focal questions are ..."

xdotool windowactivate $id sleep 0.2 key alt+s sleep 1.0

####################################
# 'Sla het assessment invoer-bestand op', 
# save as scenario_1
####################################
id=`get_dialog_id_by_title "Sla het assessment invoer-bestand op"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id sleep 0.2 type --delay 100  $mycmp
xdotool windowactivate $id sleep 0.2 key Return sleep 1.0

####################################
# 'Mijn persoonlijke werktheorie', choose '&Stoppen'
####################################
id=`get_dialog_id_by_title "Mijn persoonlijke werktheorie, programma voor de assessor"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+s sleep 0.2
