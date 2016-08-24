#!/bin/bash
# Let the student work on the concept map
# Assumes BrainweaverDeveloper is already running

# Load scripts
. ../../testing_cpp_gui_applications_tutorial/scripts/get_dialog_id.sh

# Variables
mycmp="issue_11.cmp"
mycmp_result="issue_11_result.cmp"
mypdf_result="issue_11_result.pdf"

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
# Main menu, choose '1. Student'
####################################
id=`get_dialog_id "Menu voor de ontwikkelaar"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id key alt+1 sleep 5.0

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
xdotool windowactivate --sync $id sleep 0.4 key Return sleep 0.6

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
xdotool windowactivate --sync $id key alt+a sleep 0.5

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
xdotool windowactivate --sync $id type "hard to make up"
xdotool sleep 0.2

# Add 
xdotool windowactivate --sync $id key Tab Return
xdotool sleep 0.2

# Text to add
xdotool windowactivate --sync $id type "concise"
xdotool sleep 0.2

# Add 
xdotool windowactivate --sync $id key Tab Return
xdotool sleep 0.2

# Text to add
xdotool windowactivate --sync $id type "precise"
xdotool sleep 0.2

# Add 
xdotool windowactivate --sync $id key Tab Return
xdotool sleep 0.2

# Text to add
xdotool windowactivate --sync $id type "English"
xdotool sleep 0.2

# Add 
xdotool windowactivate --sync $id key Tab Return
xdotool sleep 0.2

# Text to add
xdotool windowactivate --sync $id type "not too long"
xdotool sleep 0.2

# Add 
xdotool windowactivate --sync $id key Tab Return
xdotool sleep 0.2

# Save
xdotool windowactivate --sync $id key alt+s sleep 1

####################################
# 'Sla de clustering op'
####################################
id=`get_dialog_id "Sla de clustering op"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

xdotool windowactivate $id type $mycmp_result 
xdotool windowactivate $id sleep 0.1 key Return sleep 0.3

####################################
# 'Associeer- en cluster-scherm'
# Start concept map
####################################
id=`get_dialog_id "Associeer- en cluster-scherm"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi
xdotool windowactivate $id sleep 0.4 key alt+b sleep 0.8

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

# Create new edge by keyboard and undo its creation
xdotool windowactivate $id sleep 0.3 key space Shift+Left Ctrl+e sleep 0.2 key Ctrl+z sleep 0.2

# Create new edge by mouse

xdotool mousemove 520 650 click 1 sleep 1 mousemove 450 450 sleep 1 click 1

# OLD xdotool mousemove 540 560 click 1 mousemove 450 360 sleep 0.5 click 1

# Click on target node to select it
xdotool sleep 0.5 click 1

# Delete the target node and undo
xdotool key Delete sleep 0.5 key Ctrl+z

# Go to the node, and add head and tail arrow
xdotool key Down Ctrl+h Ctrl+t sleep 0.5

# Modify edge
xdotool key F2 sleep 0.2

####################################
# 'Concept/Relatie bewerken'
####################################
id=`get_dialog_id "Concept/Relatie bewerken"`
if [ -z $id ]
then
  echo "ID not found, line "$LINENO
  exit 1
fi

# OK
xdotool key Alt+o

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

# CRASH
echo "Going to crash the program in 3 seconds..."
xdotool windowactivate $id sleep 3.0 key F9

exit

# Type filename
xdotool windowactivate $id type $mycmp_result
# OK
xdotool windowactivate $id key Escape sleep 0.1 key Return sleep 0.2
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
xdotool windowactivate $id key Return sleep 0.2

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
xdotool windowactivate $id sleep 0.1 key Return sleep 0.1

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
