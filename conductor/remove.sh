# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")
echo $SCRIPTPATH

sleep 1 && wmctrl -r "Progress Status" -b add,above &
( 
    # =================================================================
    echo "# Cleaning build directory" ; sleep 1
    make clean
    echo "45"

    # =================================================================
    echo "# Removing Conductor icons" ; sleep 1
    rm $HOME/.local/share/applications/conductor.desktop
    echo "55" ; sleep 1
    rm $HOME/.local/share/applications/conductor_updater.desktop
    echo "70" ; sleep 0.5
    echo "# Removing configs"
    echo "85"
    rm -r $HOME/.config/conductor
    echo "75" ; sleep 0.5

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