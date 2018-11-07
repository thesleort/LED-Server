#!/bin/sh

# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")
echo $SCRIPTPATH

sleep 1 && wmctrl -r "Conductor Updater" -b add,above &
( 
    # =================================================================
    echo "# Making backup directory old/" ; sleep 1
    mkdir -p "$SCRIPTPATH/../old/"
    echo "10"

    # =================================================================
    echo "# Copying conductor into $SCRIPTPATH/old/" ; sleep 1
    cp "$SCRIPTPATH/../conductor.out" "$SCRIPTPATH/../old/"
    echo "25"

    # =================================================================
    echo "# Downloading new version" ; sleep 1
    (cd "$SCRIPTPATH/../" && git pull)
    echo "50"
    
    # =================================================================
    echo "# Preparing update" ; sleep 1
    (cd "$SCRIPTPATH/../" &&  make clean)
    echo "60"

    # =================================================================
    echo "# Updating" ; sleep 1
    (cd "$SCRIPTPATH/../" &&  make )
    echo "100"

    # =================================================================
    echo "# Update complete" ; sleep 1
) | zenity --progress \
  --title="Conductor Updater" \
  --text="Updating" \
  --percentage=0 \
  --width=300 \
  --height=100
#  --auto-close \
#  --auto-kill

(( $? != 0 )) && zenity --error --text="Error during update."

exit 0
