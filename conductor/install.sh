#!/bin/bash

# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")
echo $SCRIPTPATH

sleep 1 && wmctrl -r "Progress Status" -b add,above &
( 
    # =================================================================
    echo "# Building conductor" ; sleep 1
    make
    echo "45"

    # =================================================================
    echo "# Adding icons" ; sleep 1
    echo "[Desktop Entry]
Version=0.2
Name=Conductor 
StartupWMClass=Conductor.out
Comment=LED Screen controller
Exec=$SCRIPTPATH/conductor.out
Icon=$SCRIPTPATH/res/conductor_logo.svg
Path=$SCRIPTPATH
Terminal=false
Type=Application
Categories=Utility;Development;
    " > conductor.desktop
    echo "55" ; sleep 1
    echo "
    [Desktop Entry]
    Version=1.0
    Name=Conductor Updater
    Comment=Conductor auto updater
    Exec=bash $SCRIPTPATH/misc/autoupdate.sh
    Icon=$SCRIPTPATH/res/conductor_update_logo.svg
    Path=$SCRIPTPATH
    Terminal=false
    Type=Application
    Categories=Utility;Development;
    " > conductor_updater.desktop
    echo "65" ; sleep 0.5
    chmod +x conductor.desktop
    echo "70"
    mv conductor.desktop $HOME/.local/share/applications
    echo "75" ; sleep 0.5
    chmod +x conductor_updater.desktop
    echo "80"
    mv conductor_updater.desktop $HOME/.local/share/applications

    echo "100"
    # =================================================================
    echo "# Update complete" ; sleep 1
) | zenity --progress \
  --title="Conductor Installer" \
  --text="First Task." \
  --percentage=0 \
  --width=300 \
  --height=100
#  --auto-close \
#  --auto-kill

(( $? != 0 )) && zenity --error --text="Error during update."

exit 0
