#!/bin/bash
# Let the assessor create a test concept map with name 'scenario1.cmp'

# Load scripts
. ../../testing_cpp_gui_applications_tutorial/scripts/get_dialog_id.sh

# Variables
myexe="../../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper"
mycmp="scenario1_3_result.cmp"
mypdf="scenario1_4_result.pdf"

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
# PDF file must be absent
####################################
if [ -e $mypdf ]
then
  echo "File '$mypdf'present, now deleted, line "$LINENO
  rm $mypdf
fi

if [ -e $mypdf ]
then
  echo "File '$mypdf' could not be deleted, line "$LINENO
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
xdotool windowactivate $id sleep 0.2 key alt+g sleep 0.2

####################################
# 'De kentallen'
# Summary statistics
####################################
id=`get_dialog_id "De kentallen"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Enter assessor name
xdotool windowactivate $id sleep 0.2 type "Jane Doe" 
# Export to PDF
xdotool windowactivate $id sleep 0.2 key Alt+e sleep 0.2

####################################
# 'Preview van PDF'
# Print preview
####################################
id=`get_dialog_id "Preview van PDF"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Save PDF
xdotool windowactivate $id sleep 0.2 key Alt+s sleep 0.2

####################################
# 'Exporteer document naar PDF'
# Save PDF
####################################
id=`get_dialog_id "Exporteer document naar PDF"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Type PDF filename
xdotool windowactivate $id sleep 0.2 type $mypdf
# OK
xdotool windowactivate $id sleep 0.2 key Alt+o sleep 0.2

### Checking

if [ ! -e $mypdf ]
then
  echo "File '$mypdf' not found, line "$LINENO
  exit 1
fi

### Quitting


####################################
# 'Preview van PDF'
# Print preview
####################################
id=`get_dialog_id "Preview van PDF"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Quit
xdotool windowactivate $id sleep 0.2 key Alt+F4 sleep 0.1


####################################
# 'De kentallen'
# Quit from summary statistics
####################################
id=`get_dialog_id "De kentallen"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Enter assessor name
xdotool windowactivate $id sleep 0.2 key Alt+F4

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
xdotool windowactivate $id sleep 0.2 key Alt+F4

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
# Main menu, close
####################################
id=`get_dialog_id "Menu voor de ontwikkelaar"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+F4


echo "File '"$mypdf"' is created successfully"