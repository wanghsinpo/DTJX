# $Header: /usr/cvsroot/gem/host/superwin.tcl,v 1.11 2004/09/28 13:39:22 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1998, 2004 Hume Integration Software
# All Rights Reserved
#
# Host Interface Supervisor User Interface
#
# $Log: superwin.tcl,v $
# Revision 1.11  2004/09/28 13:39:22  hume
# The recipe upload directory is configurable and defaults to separate sub-
# directories for each connection name.
#
# Revision 1.10  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.9  2002/08/06 21:25:28  hume
# Added checkboxes to disable S1F17 and S2F31 during the initialization flow.
#
# Revision 1.8  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.7  2000/10/10 21:00:09  hume
# Added PASSIVE HSMS option for supervisor and gemhost/supervisor command lines.
#
# Revision 1.6  1999/04/06 18:32:58  hume
# Added startup configuration to disable asking for variable and alarm data
# during initialization to address problem of too much data/too slow a link.
#
# Revision 1.5  1998/11/17 13:21:22  hume
# Converted while 1 to while {1} for better runtime performance.
#
# Revision 1.4  1998/01/30 02:31:49  hume
# Set the icon name to Supervisor.
#
# Revision 1.3  1998/01/29 23:26:21  hume
# Tweaked packing and listbox size.
#
# Revision 1.2  1998/01/29 16:31:23  hume
# Added safer exit.
#
# Revision 1.1  1998/01/29 16:20:20  hume
# Added supervisor application.
#

# Supervisor window
proc ei_superwin_create {} {
    global ei_super_status
    set w .supr
catch {destroy $w} ;# development mode
    if { [winfo exists $w] } {
        wm deiconify $w
        raise $w
        return $w
        }

    toplevel $w
    wm title $w "Equipment Interface Supervisor"
    wm iconname $w Supervisor
    message $w.m -aspect 800 -text "Select an interface or set of interfaces, and\
 then choose your action.  Interfaces that are configured for \"auto_start\"\
 are started when the supervisor script is started."
    pack $w.m -side top -expand 0 -fill x
    frame $w.f
    pack $w.f -side top -expand 1 -fill both
    scrollbar $w.f.sy -command "$w.f.lb yview"
    scrollbar $w.f.sx -command "$w.f.lb xview" -orient horizontal
    listbox $w.f.lb -yscrollcommand "$w.f.sy set" \
        -xscrollcommand "$w.f.sx set" -selectmode extended -height 8
    pack $w.f.sy -side right -expand 0 -fill y
    pack $w.f.sx -side bottom -expand 0 -fill x
    pack $w.f.lb -side top -expand 1 -fill both
    
    label $w.status -textvariable ei_super_status -anchor w
    pack $w.status -side top -expand 0 -fill x -padx 1m
   
    label $w.c -text "Startup Configuration" -anchor w
    pack $w.c -side top -expand 0 -fill x

    frame $w.fc 
    pack $w.fc -side top -expand 0 -fill x
    set ct 0
    foreach rec [list {New...  ei_super_new}\
 {Edit... ei_super_edit} {Copy... ei_super_copy} {Delete... ei_super_ui_del}] {
        vset $rec "txt cmd"
        button $w.fc.b$ct -text $txt -command "$cmd $w.f.lb" 
        pack $w.fc.b$ct -side left -padx 2m -ipadx 1m 
        incr ct
        }
    label $w.la -text "Equipment Interface Actions" -anchor w
    pack $w.la -side top -expand 0 -fill x
    frame $w.fe
    pack $w.fe -side top -expand 0 -fill x
    foreach rec [list {Start ei_super_ui_start}\
 {Stop ei_super_ui_stop} {{Raise Windows} ei_super_ui_raise}] {
        vset $rec "txt cmd"
        button $w.fe.b$ct -text $txt -command "$cmd $w.f.lb"
        pack $w.fe.b$ct -side left -padx 2m -ipadx 1m
        incr ct
        }
    label $w.ls -text "Supervisor Actions" -anchor w
    pack $w.ls -side top -expand 0 -fill x
    frame $w.fs
    pack $w.fs -side top -expand 0 -fill x
    foreach rec [list [list {Save Tables} "ei_super_save $w.f.lb"]\
 [list {Reconnect VFEI Output} "ei_super_vf_out $w.f.lb"]\
 {Refresh ei_superwin_refresh}\
 [list Exit "ei_superwin_exit $w.f.lb"]] {
        vset $rec "txt cmd"
        button $w.fs.b$ct -text $txt -command $cmd
        pack $w.fs.b$ct -side left -padx 2m -ipadx 1m
        incr ct
        }
    }

#
# refresh EI list in supervisor window
#
proc ei_superwin_refresh {{lb .supr.f.lb}} {
    set now [localtime 9]
    set reply [SQL "select spname from ei_startup"]
    set cols [lindex $reply 2]
    foreach row [lindex $reply 6] {
        vset $row $cols
        global $spname
        if { ![info exists ${spname}(state)] } {
            set text "Not Started ($now)"
            }\
        else {
            set text "Connection state: [set ${spname}(state)]"
            set ct [lindex [SQL "select spname from ei_vfei_output\
 where spname='$spname'"] 4]
            if { $ct != "0" } {
                append text " $ct unsent VFEI messages at $now"
                }
            }
        SQL "update ei_startup set status='$text' where spname='$spname'"
        }
    if { $lb != "" && [winfo exists $lb] } {
        $lb delete 0 end
        set reply [SQL "select spname,status,port from ei_startup"]
        foreach row [lindex $reply 6] {
            $lb insert end $row
            }
        }
    global ei_super_status
    set ei_super_status "List refreshed at $now"
    }
            
proc ei_super_ui_usage {lb plural} {
   if { $plural } { set p "one or more interfaces" }\
   else {set p "an interface"}
   tk_dialog $lb.popup "Supervisor Usage" \
 "Select $p before indicating this action." info 0 Dismiss
   }
        
proc ei_super_ui_start {lb} {
    set list [$lb curselection] 
    if { $list == "" } { ei_super_ui_usage $lb 1 ; return }
    set names ""
    foreach index $list {
        set text [$lb get $index]
        lappend names [lindex $text 0]
        }
    set where "where spname='[join $names {' or spname='}]'"
    ei_super_start $where
    ei_superwin_refresh $lb
    }

#
# copy selected interfaces
#
proc ei_super_copy {lb} {
    set dmh_gets_var [dmh_var dmh_gets button]
    set list [$lb curselection] 
    if { $list == "" } { ei_super_ui_usage $lb 1 ; return }
    set names ""
    foreach index $list {
        set text [$lb get $index]
        lappend names [lindex $text 0]
        }
    foreach name $names {
        set newname ""
        while {1} {
            set newname [dmh_gets "Copy EI" "Enter a new name\
 for a copy of the $name EI:" $newname {[A-Za-z_][-A-Za-z_0-9]*}]
            set newname [string trim $newname]
            if { [set $dmh_gets_var] == "Cancel" } return 
            set txt [ei_is_spname_ok $newname]
            if { $txt == "" } {
                vset [ei_copy_ei $name $newname] "ct newct"
                tk_dialog $lb.popup "Copy EI" "Copied $name to $newname -\
 $newct out of $ct table rows were inserted." info 0 Dismiss
                break
                }
            if { $txt != "" } {
                set pik [tk_dialog $lb.popup "Copy EI"\
 $txt error 1 Cancel Revise]
                if { $pik == 0 } return
                }
            }
        }
    ei_superwin_refresh $lb
    hub_table_refresh
    }

#
# copy the data of an EI to another name
#
proc ei_copy_ei {name newname} {
    set ct [set newct 0]
    foreach table [hub_tables] {
        if { ![string match ei_* $table] } continue
        if { [string match *_log $table] } continue
        if { $table == "ei_vfei_output" } continue
        vset [ei_copy_ei_table $table $name $newname] "ci ni"
        incr ct $ci
        incr newct $ni
        }
    return [list $ct $newct]
    }

#
# copy rows in table for spname==$name to $newname
#
proc ei_copy_ei_table {table name newname} {
    set schema [hub_table_schema_list $table]
    foreach rec $schema {
        vset $rec "colname type"
        if { [string first char $type] >= 0 } { set quotes($colname) 1 }\
        else { set quotes($colname) 0 }
        }
    set reply [SQL "select * from $table where spname='$name'"]
    set cols [lindex $reply 2]
    set ct [lindex $reply 4]
    set rows [lindex $reply 6]
    set newct 0
    foreach row $rows {
        vset $row $cols
        set vals ""
        foreach colname $cols {
             if { $colname == "spname" } {
                 set _value $newname
                 }\
             else {
                 set _value [set $colname]
                 }
             if { $quotes($colname) } {
                 regsub -all ' $_value '' _value
                 set _value '$_value'
                 }
             append vals ,$_value
             }
        set vals [string trimleft $vals ,]
        set reply [SQL "insert into $table ([join $cols ,]) values ($vals)"]
        if { [string first "//c 0" $reply] >= 0 } { incr newct }
        }
    return [list $ct $newct]
    }



#
# Stop selected interfaces
#
proc ei_super_ui_stop {lb} {
    global ei_super_status
    set list [$lb curselection] 
    if { $list == "" } { ei_super_ui_usage $lb 1 ; return }
    set names ""
    foreach index $list {
        set text [$lb get $index]
        lappend names [lindex $text 0]
        }
    set pik [tk_dialog $lb.popup "Stop Confirmation"\
 "Please confirm that you want to shutdown the following\
 equipment interfaces: $names" warning 0 Cancel "Perform Stop"]
    if { $pik == "1" } {
        ei_super_stop $names
        }
    ei_superwin_refresh $lb
    set ei_super_status "$names stopped"
    }

#
# Raise or recreate the windows of an interface
#
proc ei_super_ui_raise {lb} {
    set list [$lb curselection] 
    if { $list == "" } { ei_super_ui_usage $lb 1 ; return }
    set names ""
    foreach index $list {
        set text [$lb get $index]
        lappend names [lindex $text 0]
        }
    foreach name $names {
        if { [info commands $name] != $name } continue
        if { [info globals $name] != $name } continue
        catch { ei_ui $name }
        catch { $name tracewin }
        }
    }
    
#
# create a new interface
#
proc ei_super_new lb {
    ei_super_editor $lb {}
    }

#
# edit selected interfaces
#
proc ei_super_edit lb {
    set list [$lb curselection] 
    if { $list == "" } { ei_super_ui_usage $lb 1 ; return }
    set names ""
    foreach index $list {
        set text [$lb get $index]
        lappend names [lindex $text 0]
        }
    foreach name $names {
        ei_super_editor $lb $name
        }
    }

# delete selected interfaces
proc ei_super_ui_del lb {
    set list [$lb curselection] 
    if { $list == "" } { ei_super_ui_usage $lb 1 ; return }
    set names ""
    foreach index $list {
        set text [$lb get $index]
        lappend names [lindex $text 0]
        }
    set pik [tk_dialog $lb.popup "Delete Confirmation"\
 "The delete action deletes ALL of the equipment interface data\
 including event definitions, report definitions, variables, and the\
 startup record.  Please confirm that you wish to delete the following\
 equipment interfaces: $names" warning 0 Cancel "Perform Deletion"]
    if { $pik == "1" } {
        ei_super_delete $names
        ei_superwin_refresh $lb
        hub_table_refresh
        }
    }

#
# create or edit an interface startup configuration
#
proc ei_super_editor {lb name} {
    set array ei_sc_$name
    global $array
    set w .$array
    if { [winfo exists $w] } {
        wm deiconify $w ; raise $w ; return }
    toplevel $w
    if { $name == "" } {
        set new 1
        set title "EI Startup Configuration - New"
        }\
    else { 
        set new 0
        set title "EI Startup Configuration - $name" 
        }
    wm title $w $title
    # fetch data to be updated (New will be empty strings)
    set reply [SQL "select * from ei_startup where spname='$name'"]
    set cols [lindex $reply 2]
    vset [lindex [lindex $reply 6] 0] $cols
    foreach f $cols { set ${array}($f) [set $f] }
    set ${array}(new) $new
    if { $new } { 
        set ${array}(BAUD) 9600
        set ${array}(DEVID) 0
        set ${array}(hsms_PROTOCOL) 0
        set ${array}(hsms_passive) 0
        set ${array}(MULT) 1
        set ${array}(auto_start) 1
        set ${array}(use_s1f3) 1
        set ${array}(use_s1f11) 1
        set ${array}(use_s1f13) 1
        set ${array}(use_s1f17) 1
        set ${array}(use_s2f13) 1
        set ${array}(use_s2f29) 1
        set ${array}(use_s2f31) 1
        set ${array}(use_s5f5) 1
        set ${array}(use_s5f7) 1
        set ${array}(post_startup_code) {}
        set ${array}(recipe_dir) {}
        }

    frame $w.f  
    pack $w.f -side top -expand 0 -fill x -padx 1m
    label $w.f.l -text "Interface Name:" -anchor e -width 20
    if $new {
        entry $w.f.e -relief sunken -width 20 \
 -textvariable ${array}(spname)
        }\
    else {
        label $w.f.e -relief sunken -width 20 \
 -textvariable ${array}(spname) -anchor w
        }
    pack $w.f.l $w.f.e -side left -fill both -padx 1m -pady 1m

    frame $w.d
    pack $w.d -side top -fill x -padx 1m
    label $w.d.l -text "Device ID:" -anchor e -width 20
    entry $w.d.e -width 6 -textvariable ${array}(DEVID)
    pack $w.d.l $w.d.e -side left -padx 1m

    checkbutton $w.as -text "Automatically Start when Supervisor starts"\
 -variable ${array}(auto_start) -anchor w
    checkbutton $w.mult -text "Equipment can handle multiple active SECS commands"\
 -variable ${array}(MULT) -anchor w
    pack $w.as $w.mult -side top -padx 8m -fill x

    label $w.ic -text "Initialization Customization" -anchor w
    pack $w.ic -side top -fill x -padx 2m
    checkbutton $w.u1_13 -text "Use S1F13 to establish communications (GEM Standard)"\
 -variable ${array}(use_s1f13) -anchor w
    checkbutton $w.u1_11 -text "Use S1F11 to determine Status Variables"\
 -variable ${array}(use_s1f11) -anchor w
    checkbutton $w.u1_3 -text "Use S1F3 to query Status Variable values"\
 -variable ${array}(use_s1f3) -anchor w
    checkbutton $w.u1_17 -text "Use S1F17 to request Online Control State"\
 -variable ${array}(use_s1f17) -anchor w
    checkbutton $w.u2_29 -text "Use S2F29 to determine Equipment Constants"\
 -variable ${array}(use_s2f29) -anchor w
    checkbutton $w.u2_13 -text "Use S2F13 to query Equipment Constant values"\
 -variable ${array}(use_s2f13) -anchor w
    checkbutton $w.u2_31 -text "Use S2F31 to synchronize the Equipment Clock"\
 -variable ${array}(use_s2f31) -anchor w
    checkbutton $w.u5_5 -text "Use S5F5 to determine Alarm types"\
 -variable ${array}(use_s5f5) -anchor w
    checkbutton $w.u5_7 -text "Use S5F7 to determine enabled Alarms"\
 -variable ${array}(use_s5f7) -anchor w
    pack $w.u1_13 $w.u1_11 $w.u1_3 $w.u1_17 $w.u2_29 $w.u2_13 $w.u2_31 $w.u5_5 $w.u5_7\
  -side top -padx 8m -fill x
    
    label $w.cc -text "Choose a connection type below:" -anchor w
    pack $w.cc -side top -fill x -padx 2m

    frame $w.ft
    pack $w.ft -side top -expand 0 -fill x
    frame $w.ft.l 
    frame $w.ft.r
    pack $w.ft.l $w.ft.r -side left -expand 1 -fill both
    set ct 0
    foreach rec {{{HSMS Standard} 1995}\
 {{HSMS 1993 draft} 1993}\
 {{SECS-I TCP/IP Terminal Server} TS}\
 {{SECS-I serial RS232 device} 0}} {
        vset $rec "txt val"
        radiobutton $w.ft.l.b$ct -text $txt -variable ${array}(type)\
  -value $val -anchor w
        pack $w.ft.l.b$ct -side top -fill x -padx 8m
        incr ct
        }
    foreach rec {{{Host or IP Addr:} host} {{TCP/IP port:} socket}} {
        vset $rec "txt sub"
        frame $w.ft.r.f$ct
        pack $w.ft.r.f$ct -side top -pady 1m -padx 2m
        label $w.ft.r.f$ct.l -text $txt -anchor e -width 20
        entry $w.ft.r.f$ct.e -relief sunken -textvariable ${array}($sub)
        pack $w.ft.r.f$ct.l $w.ft.r.f$ct.e -side left
        incr ct
        }
    # hsms_passive checkbutton - default is not checked
        frame $w.ft.r.f$ct
        pack $w.ft.r.f$ct -side top -pady 1m -padx 2m
        label $w.ft.r.f$ct.l -text "HSMS Passive Mode (Active is default):" -anchor e -width 32
        checkbutton $w.ft.r.f$ct.cb -relief flat -variable ${array}(hsms_passive)
        pack $w.ft.r.f$ct.l $w.ft.r.f$ct.cb -side left
        incr ct
    foreach rec {{{RS232 device:} device} {{Baud rate:} BAUD}} {
        vset $rec "txt sub" 
        frame $w.ft.l.f$ct
        pack $w.ft.l.f$ct -side top 
        label $w.ft.l.f$ct.l -text $txt -anchor e -width 20
        entry $w.ft.l.f$ct.e -relief sunken -textvariable ${array}($sub)
        pack $w.ft.l.f$ct.l $w.ft.l.f$ct.e -side left
        incr ct
        }

    label $w.rdl -anchor w \
 -text "Non-default Recipe Upload/Download Directory (use Unix style slashes):"
    pack $w.rdl -side top -expand 1 -fill x -pady 1m -padx 2m
    frame $w.rd
    pack $w.rd -side top -expand 1 -fill x
    entry $w.rd.e -textvariable ${array}(recipe_dir) -width 80
    pack $w.rd.e -side left -pady 1m -padx 2m

    label $w.pscl -anchor w \
 -text "Optional Post Startup Code (eg., \"set ${name}(T3) 70000\"):"
    pack $w.pscl -side top -expand 1 -fill x -pady 1m -padx 2m
    frame $w.psc 
    pack $w.psc -side top -expand 1 -fill x
    entry $w.psc.e -textvariable ${array}(post_startup_code) -width 80
    pack $w.psc.e -side left -pady 1m -padx 2m

    frame $w.bot
    pack $w.bot -side top
    button $w.bot.ok -text Ok -command "ei_super_edit_ok $array $w $lb"
    button $w.bot.can -text Cancel -command "destroy $w ; unset $array"
    wm protocol $w WM_DELETE_WINDOW "destroy $w; unset $array"
    pack $w.bot.ok $w.bot.can -side left -padx 12m -ipadx 2m -pady 1m

    # map table data to dialog fields
    if { [string first : [set ${array}(port)]] >= 0 } {
        set ${array}(device) ""
        vset [split [set ${array}(port)] :] "${array}(host) ${array}(socket)"
        if { [set ${array}(hsms_PROTOCOL)] == "0" } {
            set ${array}(type) TS
            }\
        else {
            set ${array}(type) 0
            }
        }\
    else {
        # no colon, but port may be a local socket if its an integer 
        if { [set ${array}(hsms_PROTOCOL)] != "0" } {
            # HSMS on local socket
            set ${array}(socket) [set ${array}(port)]
            }\
        else {
            # serial or Terminal server
            set fm ""
            regexp \[0-9\] [set ${array}(port)] fm
            if { $fm == [set ${array}(port)] } {
                  # its an integer port (or blank)
                  set ${array}(socket) [set ${array}(port)]
                  }\
            else {
                # its a serial device
                set ${array}(device) [set ${array}(port)]
                }
            }
        set ${array}(type) 0
        }
    if { [set ${array}(hsms_PROTOCOL)] == "1993" ||\
         [set ${array}(hsms_PROTOCOL)] == "1995" } {
        set ${array}(type) [set ${array}(hsms_PROTOCOL)]
        }
    }

#
# validate new EI name
#
proc ei_is_spname_ok spname {
    set fullmatch ""
    set txt ""
    regexp \[A-Za-z_\]\[-0-9A-Za-z_\]* $spname fullmatch
    if { ![string compare $spname ""] || $fullmatch != $spname } {
        set txt "The Interface Name should start with a letter and
 consist only of letters, numbers, dashes, and underscores."
        }\
    elseif { [info commands $spname] == $spname ||
        [info globals $spname] == $spname } {
        set txt "The Interface Name is already in use as a Tcl\
 command name or global data item."
        }
    return $txt
    }

    
#
# Ok button pressed on edit or create of startup configuration
#
proc ei_super_edit_ok {array w lb} {
    global $array
    foreach f {spname socket host device BAUD DEVID new type} {
        set $f [set ${array}($f) [string trim [set ${array}($f)]]]
        }
    if { $new } {
        set txt [ei_is_spname_ok $spname]
        if { $txt != "" } {
            tk_dialog $w.popup "EI Create" $txt error 0 Dismiss
            return
            }
        }
    if { $type == "1995" || $type == "1993" || $type == "TS" } {
        set fullmatch ""
        set txt ""
        regexp \[0-9\]+ $socket fullmatch
        if { ([string compare $socket ""]==0) || $fullmatch != $socket } { 
            set txt "The TCP/IP port is missing or not a proper integer"
            }
        if { [llength $host] != 0 && [llength $host] != 1 } {
            set txt "The Host or IP Addr is not proper."
            }\
        elseif { [string first . $host] > 0 } {
            regexp \[\\.0-9\]+ $host fullmatch
            if { $fullmatch != $host || [llength [split $host .]] != 4 } {
                set txt "The IP Address is not proper."
                }
            }
        if { $txt != "" } {
            tk_dialog $w.popup "EI Configuration" $txt error 0 Dismiss
            return
            }
        }
    set fullmatch ""
    regexp \[0-9\]+ $DEVID fullmatch
    if { ([string compare $DEVID ""]==0) || $fullmatch != $DEVID } { 
        set txt "The Device ID is missing or not a proper integer"
        tk_dialog $w.popup "EI Configuration" $txt error 0 Dismiss
        }

    # checking is not comprehensive
    # RS232 device - blank is ok (default)
    # Host - blank is ok

    if { $type == "TS" } { 
        set hsms_PROTOCOL 0 
        }\
    else { set hsms_PROTOCOL $type }
    if { $type == 0 } {
        set port $device
        }\
    else {
        if { [string compare $host ""] } {
            set port $host:$socket
            }\
        else {
            set port $socket
            }
        }
    foreach f {post_startup_code recipe_dir} {
       regsub -all ' [set ${array}($f)] '' $f
       }
    if { $new } {
        SQL "insert into ei_startup (\
 spname,port,auto_start,DEVID,hsms_PROTOCOL,BAUD,MULT,post_startup_code,\
 use_s1f13,use_s1f11,use_s1f3,use_s2f13,use_s2f29,use_s5f5,use_s5f7,hsms_passive,\
 use_s1f17,use_s2f31, recipe_dir)\
 values ('$spname','$port',[set ${array}(auto_start)],$DEVID,$hsms_PROTOCOL,\
 $BAUD,[set ${array}(MULT)],'$post_startup_code',\
 [set ${array}(use_s1f13)],[set ${array}(use_s1f11)],[set ${array}(use_s1f3)],\
 [set ${array}(use_s2f13)],[set ${array}(use_s2f29)],[set ${array}(use_s5f5)],\
 [set ${array}(use_s5f7)],[set ${array}(hsms_passive)],[set ${array}(use_s1f17)],\
 [set ${array}(use_s2f31)], '$recipe_dir')"
        }\
    else {
        SQL "update ei_startup set port='$port',\
 auto_start=[set ${array}(auto_start)],\
 DEVID=$DEVID,\
 hsms_PROTOCOL=$hsms_PROTOCOL,\
 BAUD=$BAUD,\
 MULT=[set ${array}(MULT)],\
 use_s1f3=[set ${array}(use_s1f3)],\
 use_s1f11=[set ${array}(use_s1f11)],\
 use_s1f13=[set ${array}(use_s1f13)],\
 use_s2f13=[set ${array}(use_s2f13)],\
 use_s2f29=[set ${array}(use_s2f29)],\
 use_s5f5=[set ${array}(use_s5f5)],\
 use_s5f7=[set ${array}(use_s5f7)],\
 use_s1f17=[set ${array}(use_s1f17)],\
 use_s2f31=[set ${array}(use_s2f31)],\
 hsms_passive=[set ${array}(hsms_passive)],\
 post_startup_code='$post_startup_code', \
 recipe_dir='$recipe_dir' where\
 spname='$spname'"
        }
    destroy $w
    catch {unset $array}
    ei_superwin_refresh $lb
    }


    
#
# Save Tables action
#
proc ei_super_save lb {
    catch {
       wm deiconify .
       raise .
       hub_table_refresh
       }
    set pik [tk_dialog $lb.popup "Table Save"\
 "You can choose to save ALL of your EI table\
 files with the data you have in memory now, or just\
 save the startup table.  When you perform a save, it\
 overwrites the previous save.  

 DO NOT SAVE ALL of the\
 EI tables unless you have started an interface, or\
 otherwise know that your previous data has been\
 loaded into memory." warning 1 Cancel "Save Startup Table"\
 "Overwrite ALL EI Tables"]
    if { $pik == 0 } return
    if { $pik == 1 } {
        hub_save ei_startup 
        return
        }
    if { $pik == 2 } {
        set tabs ""
        foreach table [hub_tables] {
            if { [string match ei_* $table] } { 
                lappend tabs $table
                }
            }
        hub_save $tabs
        }
    }


#
# Reconnect VFEI output action
#
proc ei_super_vf_out lb {
    set rc [ei_super_dmh_connect]
    if { $rc == "-1" } {
        tk_dialog $lb.popup "Reconnect VFEI Output"\
 "The DMH server is not available. Try again later." error 0 Dismiss
        return
        }
    if { $rc == "-2" } {
        tk_dialog $lb.popup "Reconnect VFEI Output"\
 "This action is used to reconnect to a DMH message system group.\
 You have not set the variable MB_GROUP to run the application\
 as a client of a DMH server." info 0 Dismiss
        return
        }
    set ct [lindex [SQL "select spname from ei_vfei_output"] 4]
    if { $ct == 0 } {
        tk_dialog $lb.popup "Reconnect VFEI Output"\
 "The message system connection is present and your ei_vfei_output\
 table is empty - you're in good shape." info 0 Dismiss
        return
        }
    # need to re-open VFEI output subs 
    # the SYNC option causes the existing data to be sent
    if { $rc != 1 } {
        set pik [tk_dialog $lb.popup "Reconnect VFEI Output"\
 "You already have a healthy message system connection.\
 The reconnect action is for fixing a broken connection and\
 should not be repeated." warning 0 Cancel "Do it anyway"]
        if { $pik == "0" } return
        }
    foreach sub [hub_table_sub_list ei_vfei_output] {
        vset $sub "t name stmt"
        if { $name == "ei_vfei_send" } {
            SQL "close sub ei_vfei_send to ei_vfei_output"
            SQL $stmt
            tk_dialog $lb.popup "Reconnect VFEI Output"\
 "Your queued VFEI messages have been sent." info 0 Dimiss
            }
        }
    }


proc ei_superwin_exit lb {
    set pik [tk_dialog $lb.popup "Confirm Shutdown"\
 "Exiting will shutdown all your equipment interfaces\
 and discard your in-memory database.  

 Choose exit only if you do not have data that needs saving,\
 and you intend to shutdown." warning 0 Cancel Exit]
    if { $pik == 0 } return
    exit
    }
