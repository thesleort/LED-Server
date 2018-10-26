#!/bin/sh

# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")
echo $SCRIPTPATH

sleep 1 && wmctrl -r "Progress Status" -b add,above &
( 
    # =================================================================
    echo "# Making backup directory old/" ; sleep 1
    mkdir -p "$SCRIPTPATH/../old/"
    echo "10"

    # =================================================================
    echo "# Copying conductor into old/" ; sleep 1
    cp "$SCRIPTPATH/../conductor.out" "$SCRIPTPATH/../old/"
    echo "25"

    # =================================================================
    echo "# Downloading new version" ; sleep 1
    git pull
    echo "50"
    
    # =================================================================
    echo "# Prepares update" ; sleep 1
    (cd "$SCRIPTPATH/../" &&  make clean)
    echo "60"

    # =================================================================
    echo "# Updating" ; sleep 1
    make 
    echo "100"

    # =================================================================
    echo "# Update complete" ; sleep 1
) | zenity --progress \
  --title="Progress Status" \
  --text="First Task." \
  --percentage=0 \
#  --auto-close \
#  --auto-kill

(( $? != 0 )) && zenity --error --text="Error during update."

exit 0
