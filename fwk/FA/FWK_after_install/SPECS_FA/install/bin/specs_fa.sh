#!/bin/bash

USER=$1
GROUP=$2
HMDIR=$3
LSBRELEASE=/usr/bin/lsb_release
RHEL_REL=`${LSBRELEASE} -rs | sed 's/\..*//'`
RESDIR=/opt/SPECS_FA/sys/resource/

add_icon_gnome()
{
    launcher=$1
    entry=$2

    # Reset SPECS_FA Button
    gconftool-2 --recursive-list /apps/panel/objects | grep $launcher > /dev/null
    if [ $? -ne 0 ]; then
          #
          # create schema object  (use print_launcher's schema)
          #
          for schema in $(gconftool-2 --all-entries /schemas/apps/panel/default_profiles/medium/objects/print_launcher | awk -F '=' '{print $1}'); do
              gconftool-2 --apply-schema /schemas/apps/panel/default_profiles/medium/objects/print_launcher/$schema /apps/panel/objects/$launcher/$schema
          done

          #
          # set preference key
          #
          gconftool-2 --type string --set /apps/panel/objects/$launcher/action_type lock
          gconftool-2 --type string --set /apps/panel/objects/$launcher/launcher_location $entry
          gconftool-2 --type bool --set /apps/panel/objects/$launcher/locked true
          gconftool-2 --type string --set /apps/panel/objects/$launcher/object_type launcher-object
          gconftool-2 --type bool --set /apps/panel/objects/$launcher/panel_right_stick true
          gconftool-2 --type int --set /apps/panel/objects/$launcher/position 2
          gconftool-2 --type string --set /apps/panel/objects/$launcher/toplevel_id top_panel
          gconftool-2 --type bool --set /apps/panel/objects/$launcher/use_custom_icon false
          gconftool-2 --type bool --set /apps/panel/objects/$launcher/use_menu_path false
    fi

    gconftool-2 --get /apps/panel/general/object_id_list | grep $launcher > /dev/null
    if [ $? -ne 0 ]; then
        object_list=$(gconftool-2 --get /apps/panel/general/object_id_list | sed -e "s|]|,$launcher]|")

        gconftool-2 --type list --list-type string --set /apps/panel/general/object_id_list $object_list
    fi
}

array_contains()
{
    eval ref=\"\${$1[@]}\"
    array=(${ref})
    seek=$2
    for element in "${array}"; do
        if [ "$element" == "$seek" ]; then
            return 1
        fi
    done
    return 0
}

restart_gnomeshell()
{
    if [ $RHEL_REL -ge 8 ]; then
        busctl --user call org.gnome.Shell /org/gnome/Shell org.gnome.Shell Eval s 'Meta.restart("Restarting...")' &> /dev/null
    else
        /usr/bin/gnome-shell --replace &> /dev/null &
    fi
}

# for GNOME 3.x
add_icon_gnome3()
{
    # add SPECS icon
    #   OS >= RHEL7
    EXTENSIONPATH=".local/share/gnome-shell/extensions/specs_fa@keysight.com"
    /usr/bin/install -d $HMDIR/$EXTENSIONPATH
    /usr/bin/install -o $USER -g $GROUP \
                     $RESDIR/home/$EXTENSIONPATH/extension.js  \
                     $RESDIR/home/$EXTENSIONPATH/metadata.json \
                     $HMDIR/$EXTENSIONPATH
    extensions=($(gsettings get org.gnome.shell enabled-extensions|gawk '{print gensub(/(.*)\[(.*)\](.*)/,"\\2",1)}' |gawk '{gsub(","," ");print $0;}'))
    array_contains extensions \'specs_fa@keysight.com\'
    if [ $? -eq 0 ]; then
        extensions=("${extensions[@]}" \'specs_fa@keysight.com\')
        extstr="[$(IFS=,; echo "${extensions[*]}")]"
        /usr/bin/gsettings set org.gnome.shell enabled-extensions "${extstr}"
        restart_gnomeshell
    fi
}

if [ $RHEL_REL -ge 7 ] ; then
    add_icon_gnome3
else
    add_icon_gnome "SPECS-FA-E_launcher" "file:///opt/SPECS_FA/sys/resource/home/.gconf/specsfa_e.desktop"
    add_icon_gnome "SPECS-FA-S_launcher" "file:///opt/SPECS_FA/sys/resource/home/.gconf/specsfa_s.desktop"
fi
