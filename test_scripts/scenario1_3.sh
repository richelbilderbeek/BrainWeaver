#!/bin/bash
# Let the student work on the concept map

# Load scripts
. ../../testing_cpp_gui_applications_tutorial/scripts/get_dialog_id.sh

# Variables
myexe="../../build-BrainweaverDeveloper-Desktop-Debug/BrainweaverDeveloper"
mycmp="scenario1.cmp"
mycmp_result="scenario1_result.cmp"
mypdf_result="scenario1_result.pdf"

####################################
# Check executable
####################################
if [ -e /$myexe ] # slash is obligatory?
then
  echo $mytestname": FAIL (executable '"$myexe"' not found)"
  exit
fi

####################################
# Input file must be present
####################################
if [ ! -e $mycmp ]
then
  echo "File "$mycmp" not found, line "$LINENO
  exit 1
fi

####################################
# Delete .cmp result file
####################################
if [ -e $mycmp_result ]
then
  echo "File "$mycmp_result" found, deleting it"
  rm $mycmp_result
fi

if [ -e $mycmp_result ]
then
  echo "File "$mycmp_result" could not be deleted"
  exit 1
fi

####################################
# Delete .pdf result file
####################################
if [ -e $mypdf_result ]
then
  echo "File "$mypdf_result" found, deleting it"
  rm $mypdf_result
fi

if [ -e $mypdf_result ]
then
  echo "File "$mypdf_result" could not be deleted"
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
xdotool windowactivate $id key alt+1 sleep 0.3

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
xdotool windowactivate $id key alt+o sleep 0.5

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
xdotool windowactivate $id key alt+b sleep 0.3

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
xdotool windowactivate $id key alt+a sleep 0.5

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
xdotool windowactivate $id type "that one I spent a year on"
# Add 
xdotool windowactivate $id key Tab Return
# Text to add
xdotool windowactivate $id type "precise"
# Add 
xdotool windowactivate $id key Tab Return
# Text to add
xdotool windowactivate $id type "not vague"
# Add 
xdotool windowactivate $id key Tab Return
# Text to add
xdotool windowactivate $id type "not too long"
# Add 
xdotool windowactivate $id key Tab Return

# Go to widget
xdotool windowactivate $id key Shift+Tab sleep 0.2 key Down Right Down Right Alt+b sleep 1.0

####################################
# 'Construeer een concept map-scherm'
# Save concept map
####################################
id=`get_dialog_id "Construeer een concept map-scherm"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Move to an item with an example and edit
# xdotool windowactivate $id key space
xdotool windowactivate $id key space sleep 0.1 key Up sleep 0.1 key Up F2



exit 

# Type filename
xdotool windowactivate $id type $mycmp_result
# OK
xdotool windowactivate $id key Escape sleep 0.1 key alt+o sleep 0.2
# Export
xdotool windowactivate $id key alt+e sleep 0.3

####################################
# 'Preview van PDF'
# Save exported PDF
####################################
id=`get_dialog_id "Preview van PDF"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Save ('&Opslaan')
xdotool windowactivate $id key alt+o sleep 0.2

####################################
# 'Exporteer document naar PDF'
# Exported PDF
####################################
id=`get_dialog_id "Exporteer document naar PDF"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# Save ('&Opslaan')
xdotool windowactivate $id type $mypdf_result
# OK
xdotool windowactivate $id sleep 0.1 key alt+o sleep 0.1

####################################
#
#
#         Close everything
#
#
####################################


####################################
# 'Preview van PDF'
# Close
####################################
id=`get_dialog_id "Preview van PDF"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id sleep 0.1 key alt+F4 sleep 0.1

####################################
# 'Construeer een concept map-scherm'
# Close
####################################
id=`get_dialog_id "Construeer een concept map-scherm"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

xdotool windowactivate $id sleep 0.1 key alt+F4 sleep 0.1

####################################
# 'Associeer- en cluster-scherm'
# Close
####################################
id=`get_dialog_id "Associeer- en cluster-scherm"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

xdotool windowactivate $id sleep 0.1 key alt+F4 sleep 0.1

####################################
# 'Mijn persoonlijke werktheorie, programma voor de student'
# Close
####################################
id=`get_dialog_id "Mijn persoonlijke werktheorie, programma voor de student"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

xdotool windowactivate $id sleep 0.1 key alt+F4 sleep 0.1

####################################
# 'Mijn persoonlijke werktheorie, programma voor de student'
# Close
####################################
id=`get_dialog_id "Mijn persoonlijke werktheorie, programma voor de student"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

xdotool windowactivate $id sleep 0.1 key alt+F4 sleep 0.1


####################################
# Main menu
# Close
####################################
id=`get_dialog_id "Menu voor de ontwikkelaar"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

xdotool windowactivate $id sleep 0.1 key alt+F4 sleep 0.1





####################################
# Check results
####################################


if [ ! -e $mycmp_result ]
then
  echo "File "$mycmp_result" could not be found"
  exit 1
fi

if [ ! -e $mypdf_result ]
then
  echo "File "$mypdf_result" could not be found"
  exit 1
fi
