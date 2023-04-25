# $Header: /usr/cvsroot/gem/host/ei_recipes.tcl,v 1.7 2005/03/25 22:55:46 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_recipes.tcl,v $
# Revision 1.7  2005/03/25 22:55:46  hume
# Added code for the host to respond to equipment initiated process program
# transfers.  Process program transfer actions create StateChange events when
# used with the .NET SecsHost or similar libraries.
#
# Revision 1.6  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.5  2002/09/23 13:44:42  hume
# ei_recipe_dir uses secs_xact reply result instead of lastrmsg - changed to
# support re-entrant secs_xact customization.
#
# Revision 1.4  2002/07/23 14:08:07  hume
# Made small changes to accomodate recipe names with embedded spaces.
#
# Revision 1.3  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  1998/08/10 12:37:25  hume
# Fixed bug in recipe delete.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

# PPExecName delete H->E
# empty list means delete all recipes
#
# returns ACKC7
# 0 ok, 1=not permitted, 4=not found, 5=other err
#
proc ei_recipe_delete {spname PPIDs} {
    # look up the type code for recipes
    set reply [SQL "select value_TSN from ei_variable where\
 spname='$spname' and varID='PPID'"]
    set value_TSN [lindex [lindex [lindex $reply 6] 0] 0]
    if { $value_TSN == "" } { set value_TSN A }
    set msg L
    foreach PPID $PPIDs {
        lappend msg [list $value_TSN $PPID]
        }
    set reply [secs_xact $spname S7F17R $msg]
    if { $reply != "TIMEOUT" } {
        set reply [expr [lindex $reply 1]]
        }
    return $reply
    }


# H->E
proc ei_recipe_dir {spname} {
    global $spname
    set reply [secs_xact $spname S7F19R]
    if { $reply == "TIMEOUT" } { return $reply }
    set list $reply
    if { $list == "L:0" } { return "" }
    set list [lreplace $list 0 0]
    set result ""
    foreach pair $list {
        vset $pair "type value"
        set ${spname}(PPID_TSN) $type
        lappend result $value
        }
    return $result
    }

# H<->E
# return the {L:2 <PPID> <PPBODY>} result of S7F5
# "" is returned on error
proc ei_recipe_get {spname PPID} {
    global $spname
    # look up the type code for recipes
    set reply [SQL "select value_TSN from ei_variable where\
 spname='$spname' and varID='PPID'"]
    set value_TSN [lindex [lindex [lindex $reply 6] 0] 0]
    if { $value_TSN == "" } { set value_TSN A }
    set reply [secs_xact $spname S7F5R [list $value_TSN $PPID]]
    # expect L:2 <ppid> <PPBODY>"
    if { [lindex $reply 0] == "L:2" } {
        return $reply
        }
    return ""
    }


# download a process program to the equipment using S7F3 
# the PPBODY is the complete {type data} item
# but the PPID is only the ID value
# returns
# 0=ok, 1=no permission, 2=length err, 5=other err
proc ei_recipe_put {spname PPID PPBODY} {
    global $spname
    # look up the type code for PPID's
    set reply [SQL "select value_TSN from ei_variable where\
 spname='$spname' and varID='PPID'"]
    set value_TSN [lindex [lindex [lindex $reply 6] 0] 0]
    if { $value_TSN == "" } { set value_TSN A }
    set msg [list L:2 [list $value_TSN $PPID] $PPBODY]
    set len [llength [TSN_to_secs $msg]]
    if { $len > 244 } {
         set reply [SQL "select value_TSN from ei_variable where\
 spname='$spname' and varID='LENGTH'"]
         set LENGTH_TSN [lindex [lindex [lindex $reply 6] 0] 0]
         if { $LENGTH_TSN == "" } { set LENGTH_TSN U4 }

         set reply [secs_xact $spname S7F1R \
 [list L [list $value_TSN $PPID] [list $LENGTH_TSN $len]]]
         # PPGNT
         if { $reply != "B:1 0x00" } {
             return 5
             }
         }
    set reply [secs_xact $spname S7F3R $msg]
    if { $reply != "TIMEOUT" } {
        set reply [expr [lindex $reply 1]]
        if { $reply == 0 } {
            # create a data change that can be seen with a variable trace
            set ${spname}(recipe_download) {}
            set ${spname}(recipe_download) $PPID
            }
        }
    return $reply
    }


#
# received S7F3 equipment initiated upload of a process program (from equipment to host)
#
#   Similar to the equipment version except that we cannot assume ppid is a valid
#   file name.  So we save both the PPID and the PPBODY data in a file.
#
proc ei_pp_receive {spname} {
    global $spname
    set data [set ${spname}(lastrmsg)]
    vset $data {l2 PPID PPBODY}
    if { $l2 != "L:2" || ([llength $PPID] != 2)} {
        if { ([set ${spname}(TRACE)] & 0x03) != 0} {
            set ${spname}(trace) "PP upload error: improper data"
            }
        $spname put S9F7 "B [$spname lastheader]"
        return
        }
    vset $PPID {tPPID ppid}
    if { ![string compare $ppid ""] } {
        if { ([set ${spname}(TRACE)] & 0x03) != 0} {
            set ${spname}(trace) "PP upload error: blank ppid"
            }
        $spname put S9F7 "B [$spname lastheader]"
        return
        }
    set recipe_dir [set ${spname}(recipe_dir)]
    set rc [catch {
        if { ![file isdirectory $recipe_dir] } {
            file mkdir $recipe_dir
            }
        set fname [file join $recipe_dir [ei_ui_ppid_filename $ppid]]
        if { [file exists $fname] } {
            set ${spname}(recipe_delete) {}
            set ${spname}(recipe_delete) $ppid
            }
        set fid [open $fname w]
        fconfigure $fid -translation binary 
        puts -nonewline $fid $data
        close $fid
        } etxt]
    if { $rc } {
        catch {close $fid}
        if { ([set ${spname}(TRACE)] & 0x03) != 0} {
            set ${spname}(trace) "PP upload error: $etxt"
            }
        $spname put S7F4 {B 5}  ;# ACKC7 error
        }\
    else {
        $spname put S7F4 {B 0} 
        if { ([set ${spname}(TRACE)] & 0x03) != 0} {
            set ${spname}(trace) "PP upload success ppid=$ppid file=$fname"
            }
        # create a data change that can be seen with a variable trace
        set ${spname}(recipe_upload) {}
        set ${spname}(recipe_upload) $ppid
        }
    }

#
# received S7F5 from the equipment requesting the download of a process program
# S7F6 reply does not require multiblock inquire/grant
#
proc ei_pp_send spname {
    global $spname
    set PPID [set ${spname}(lastrmsg)]
    # A:x xxxxx
    set ppid [lindex $PPID 1]
    if { ![file isdirectory [set ${spname}(recipe_dir)]] } {
        if { ([set ${spname}(TRACE)] & 0x03) != 0} {
            set ${spname}(trace) "PP download denied - no process program directory"
            }
        $spname put S7F6 L
        return
        }
    set filename [ei_ui_ppid_filename $ppid]
    set pathname [file join [set ${spname}(recipe_dir)] $filename]
    if { ![file exists $pathname] } {
        if { ([set ${spname}(TRACE)] & 0x03) != 0} {
            set ${spname}(trace) "PP download denied - $pathname does not exist"
            }
        $spname put S7F6 L
        return
        }
    vset [ei_pp_read $spname $pathname $PPID] {rc L2REPLY}
    if { $rc != 0 } { 
        if { ([set ${spname}(TRACE)] & 0x03) != 0} {
            set ${spname}(trace) "PP download failure - $rc $L2REPLY"
            }
        $spname put S7F6 L
        return 
        }
    $spname put S7F6 $L2REPLY
    if { ([set ${spname}(TRACE)] & 0x03) != 0} {
        set ${spname}(trace) "PP download success, ppid=$ppid file=$filename"
        }
    # create a data change that can be seen with a variable trace
    set ${spname}(recipe_download) {}
    set ${spname}(recipe_download) $ppid
    }

#
# read a process program from our saved file
# check the PPID for a match of identifier type and value
#
proc ei_pp_read {spname pathname PPID} {
    global $spname
    if { [catch {
        set fid [open $pathname r]
        fconfigure $fid -translation binary 
        set data [read $fid]
        close $fid
        } etxt] } {
        catch {close $fid}
        return [list -10 "File error: $etxt"]
        }
    if { [catch {
        vset $data {l2 filePPID PPBODY}
        }] || ($l2 != "L:2") } {
        return [list -11 "Invalid process program save file"]
        }
    # there is a possibility of mapping more than 1 ppid to the same file
    # so we need to be careful
    if { [string compare $PPID $filePPID] } {
        return [list -14 "Saved PPID \"$filePPID\" does not match requested PPID \"$PPID\""]
        }
    if { ![string compare $PPBODY ""] } {
        return [list -11 "Invalid process program body"]
        }
    # return the format used in S7F6, S7F3
    return [list 0 $data]
    }
