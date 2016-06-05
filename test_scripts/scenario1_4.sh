#!/bin/bash
# Let the assessor create a test concept map with name 'scenario1.cmp'

# Load scripts
. ../../testing_cpp_gui_applications_tutorial/scripts/get_dialog_id.sh

# Variables
myexe="../../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper"
mycmp="scenario1_3_result.cmp"

####################################
# Check executable
####################################
if [ -e /$myexe ] # slash is obligatory?
then
  echo $mytestname": FAIL (executable '"$myexe"' not found)"
  exit
fi

####################################
# File must be present
####################################
if [ ! -e $mycmp ]
then
  echo "File '$mycmp'could not be found, line "$LINENO
  exit 1
fi

####################################
# Start application
####################################
$myexe &
sleep 1

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
xdotool windowactivate $id key alt+e sleep 0.2

####################################
# 'Kies een assessment bestand', 
# Open concept map
####################################
id=`get_dialog_id "Kies een assessment bestand"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

xdotool windowactivate $id sleep 0.2 key Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete Delete
xdotool windowactivate $id type $mycmp
xdotool windowactivate $id sleep 0.2 key Return sleep 0.4


####################################
# 'Evalueer concept map', 
# Rate concept map
####################################
id=`get_dialog_id "Evalueer concept map"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate first concept
xdotool windowactivate $id sleep 0.2 key space Up Up F1 sleep 1.0

####################################
# 'Evalueer concept'
# Rate this first concept
####################################
# Note: need $ to distiguish 'Evalueer concept map' from 'Evalueer concept'
id=`get_dialog_id "Evalueer concept$"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate 0-1-2
xdotool windowactivate $id sleep 0.2 key Down Tab sleep 0.2 key Down Down Tab sleep 0.2 key Down Down Down sleep 0.2 key Alt+o sleep 0.2

####################################
# 'Evalueer concept map', 
# Rate concept map
####################################
id=`get_dialog_id "Evalueer concept map"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate first concept its examples
xdotool windowactivate $id sleep 0.2 key F2

####################################
# 'Evalueer voorbeelden'
# Rate this first concept its examples
####################################
id=`get_dialog_id "Evalueer voorbeelden"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate first concept its examples
xdotool windowactivate $id sleep 0.2 key Alt+b sleep 0.2 key Alt+o

####################################
# 'Evalueer concept map', 
# Rate concept map
####################################
id=`get_dialog_id "Evalueer concept map"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate second concept
xdotool windowactivate $id sleep 0.2 key Down F1 sleep 0.5

####################################
# 'Evalueer concept'
# Rate this second concept
####################################
# Note: need $ to distiguish 'Evalueer concept map' from 'Evalueer concept'
id=`get_dialog_id "Evalueer concept$"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate 1-2-0
xdotool windowactivate $id sleep 0.2 key Down Down Tab sleep 0.2 key Down Down Down Tab sleep 0.2 key Down sleep 0.2 key Alt+o sleep 0.2

####################################
# 'Evalueer concept map', 
# Rate concept map
####################################
id=`get_dialog_id "Evalueer concept map"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate second concept its examples
xdotool windowactivate $id sleep 0.2 key F2

####################################
# 'Evalueer voorbeelden'
# Rate this first concept its examples
####################################
id=`get_dialog_id "Evalueer voorbeelden"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate second concept its examples
xdotool windowactivate $id sleep 0.2 key Alt+r sleep 0.2 key Alt+o

####################################
# 'Evalueer concept map', 
# Rate concept map
####################################
id=`get_dialog_id "Evalueer concept map"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate third concept
xdotool windowactivate $id sleep 0.2 key Left F1 sleep 0.5

####################################
# 'Evalueer concept'
# Rate this third concept
####################################
# Note: need $ to distiguish 'Evalueer concept map' from 'Evalueer concept'
id=`get_dialog_id "Evalueer concept$"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate 2-0-1
xdotool windowactivate $id sleep 0.2 key Down Down Down Tab sleep 0.2 key Down Tab sleep 0.2 key Down Down sleep 0.2 key Alt+o sleep 0.2

####################################
# 'Evalueer concept map', 
# Rate concept map
####################################
id=`get_dialog_id "Evalueer concept map"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Rate third concept
xdotool windowactivate $id sleep 0.2 key alt+g

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