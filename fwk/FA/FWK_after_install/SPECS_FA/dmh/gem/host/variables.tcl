# $Header: /usr/cvsroot/gem/host/variables.tcl,v 1.25 2004/11/19 20:30:46 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2004, Hume Integration Software
# All Rights Reserved
#
# $Log: variables.tcl,v $
# Revision 1.25  2004/11/19 20:30:46  hume
# New ability to use DvvalList variable - a Hume created means to discover
# DVVALs.
#
# Revision 1.24  2004/10/12 15:15:22  hume
# Rearranged the variable initialization logic for better external use.
# (Such as new .NET code).  New provision for AUTO_VIRT_INIT - use virtual
# concepts of VFEI without using VFEI commands.  Variable
# table configuration records are put in place earlier.  Separate procedures
# to refresh Status Variable values and EC values.
#
# Revision 1.23  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.22  2002/09/24 15:56:20  hume
# Updated calls to ei_var_query to explicitly call with a list of names.
# Sets a proper example, and fixes a bug with ei_event_discovery when
# EventsEnabled variable name contains white space.
#
# Revision 1.21  2002/08/27 19:09:11  hume
# The recent VFEIname logic revision needed a tweak.
#
# Revision 1.20  2002/08/14 20:52:54  hume
# Substitution in ei_rcmd was processing backslash sequences and spoiling
# DOS filenames.  Default RCMD_PP-SELECT configuration variable entry
# improperly used quotes around data argument instead of braces, causing
# backslashes to be processed and spoiling DOS filenames.
#
# Revision 1.19  2002/07/23 16:00:06  hume
# Added logic to create unique VFEIname variable names when confronted with
# equipment using the same variable names repeatedly.
#
# Revision 1.18  2002/07/23 14:08:07  hume
# Made small changes to accomodate recipe names with embedded spaces.
#
# Revision 1.17  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.16  2001/05/25 21:37:34  hume
# Backup restoration.
#
# Revision 1.16  2001/02/02 19:44:05  hume
# Revised status variable save logic - can save values that are larger than
# the ei_variable table varvalue field size. (Fixes big EventDescriptions).
#
# Revision 1.15  2001/01/25 01:18:37  hume
# Updated 12/3/00 changes of string handling - string values were being
# returned with extra surrounding braces.
#
# Revision 1.14  2000/12/12 21:38:10  hume
# Changes to keep (control_state) in sync with the equipment. New
# CEID_OFFLINE variable is used to specify the control state offline event.
#
# Revision 1.13  2000/12/04 20:36:22  hume
# Continued last change with Equipment Constant data handling.
#
# Revision 1.12  2000/12/03 15:07:10  hume
# Continued last change with EventDescription handling when used from
# ei_variables_init.
#
# Revision 1.11  2000/12/03 14:28:27  hume
# Fixed parsing bug for data items that are lists or vectors.  Handling of
# EventDescription variable (when defined) works for {L:1 {L:n ...}} format
# or newer format {L:n ...} which is consistent with similar GEM variables.
#
# Revision 1.10  2000/02/16 02:59:02  hume
# Moved variable and event table loading earlier in the initialization.
#
# Revision 1.9  1999/05/27 19:17:35  hume
# Added mapping of the CLOCK status variable format from YYYYMMDDHHMMSScc to
# YYYY-MM-DD HH:MM:SS.cc when the variable record is created.  If the
# older format is wanted, the user can update the varmethod field.
#
# Revision 1.8  1999/04/09 00:25:52  hume
# Added logic to save SV value type in eq_var_query in case S1F3 is bypassed
# or broken.  Similar logic not needed for ECVs since configuration record
# would not exist without knowing type.
#
# Revision 1.7  1999/04/06 18:32:58  hume
# Added startup configuration to disable asking for variable and alarm data
# during initialization to address problem of too much data/too slow a link.
#
# Revision 1.6  1999/01/22 16:43:20  hume
# The host will look for and use the EventDescription variable supplied by
# Hume-based equipment interfaces.
#
# Revision 1.5  1999/01/20 17:51:35  hume
# Custom varmethod can be used with ANY varclass - changed ProcessState
# text mapping customization to keep ProcessState as variable SV.
#
# Revision 1.4  1999/01/14 16:00:20  hume
# Added support for purging or unloading the spool during initialization.
# Also added callout to customer written ei_custom_init during initialization.
#
# Revision 1.3  1997/10/28 02:13:15  hume
# Fixed typo bug in variables.tcl, and make startup version independent.
#
# Revision 1.2  1997/09/30 12:14:41  hume
# Made variable initialization tolerant of non-GEM equipment that may not
# support S1F11, S1F3, S2F29 or S2F13.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

#
# early initialization of variable records that are created by the host
# to hold configuration information
#
proc ei_variables_default spname {
    global $spname

    # class VDV VFEI Driver Variables
    # ref p16 95113016A-TR
    ei_vfei_var_init $spname

    # class SECS_DRVR 
    # implementation configuration items like type codes
    # if these are already in the table, the inserts bounce
    #
    # DO NOT CHANGE THIS CODE - CHANGE THE DATA IN THE TABLE AND SAVE IT
    #    THESE ARE DEFAULTS FOR MISSING VALUES
    foreach pair {{PPID A} {RPTID U4} {DATAID U4} {TRID A} {TOTSMP U4}\
 {REPGSZ U4} {DATALENGTH U4} {LENGTH U4}} {
        vset $pair "id type"
        set stmt  "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod) values (\
 '$spname', '$id', '$id', 'SECS_DRVR',\
 '$type', 'A', 'value_TSN is used for $id TSN type.', 'return \$varvalue')"
        SQL $stmt
        }

    # a configurable record for the event CEID that means the equipment is
    # transitioning to OFF-LINE control
    set stmt  "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varvalue,varmethod) values (\
 '$spname', 'CEID_OFFLINE', 'CEID_OFFLINE', \
 'SECS_DRVR','A', 'A', 'the equipment CEID meaning OFF-LINE control state',\
 '4000', 'return \$varvalue')"
    SQL $stmt

    # the standard is not sufficiently specific on RCMDs
    # DO NOT CHANGE THIS CODE - CHANGE THE DATA IN THE TABLE AND SAVE IT
    #    THESE ARE DEFAULTS FOR MISSING VALUES
    foreach rec {\
 {abort RCMD_ABORT {S2F41R {L:2 {A ABORT} L}}\
 {, optionally with %s for level parameter}}\
 {pause RCMD_PAUSE {S2F41R {L:2 {A PAUSE} L}} {}}\
 {pp-select RCMD_PP-SELECT {S2F41R {L:2 {A PP-SELECT} {L {L:2 {A PPExecName} {A {%s}}}}}}\
 {, with %s for the PPID value}}\
 {resume RCMD_RESUME {S2F41R {L:2 {A RESUME} L}} {}}\
 {stop RCMD_STOP {S2F41R {L:2 {A STOP} L}} {}}\
 } {
        vset $rec "tag id varvalue phrase"
        set stmt  "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varvalue,varmethod) values (\
 '$spname', '$id', '$id', \
 'SECS_DRVR','A', 'A', 'the $tag SECS command$phrase',\
 '$varvalue', 'return \$varvalue')"
        SQL $stmt
        }
       
    # here are flags that makes us do an initialize the first time we
    # see that we are online.  
    # AUTO_VFEI_INIT  - takes precedence and we do a VFEI initialize
    #                   and you get VFEI event reports etc
    # AUTO_VIRT_INIT  - optionally defined by your application 
    #                   uses virtual concepts of VFEI without VFEI commands
    #                   (uses same report configuration as VFEI)
    #                   the .NET host code uses this variable
    # AUTO_SECS_INIT  - if the above are not set and this is,
    #                   we call ei_initialize and you get SQL table data
    #                   
    foreach id {AUTO_VFEI_INIT AUTO_SECS_INIT} {
        set stmt  "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varvalue,varmethod) values (\
 '$spname', '$id', '$id', \
 'SECS_DRVR','TF', 'A', 'Automatically initialize when first online', '1',\
 'return \$varvalue')"
        SQL $stmt
        }

    # here is a variable to hold the result of the AUTO_INIT
    set id AUTO_INIT_RESULT
    set stmt  "insert into ei_variable (spname,varID,varname,VFEIname,\
 varclass, value_TSN,ID_TSN,description,varvalue,varmethod) values (\
 '$spname', '$id', '$id', '$id', 'SECS_DRVR','A', 'A', \
 'Result of executing AUTO_INIT', '','return \$varvalue')"
    SQL $stmt

    # here is a variable to unload or purge the spool during initialization
    set id SPOOL_INIT
    SQL "insert into ei_variable (spname,varID,varname,VFEIname,\
 varclass, value_TSN,ID_TSN,description,varvalue,varmethod) values (\
 '$spname', '$id', '$id', '$id', 'SECS_DRVR','A', 'A', \
 'Set to UNLOAD or PURGE to act on spool during initialize', 'UNLOAD','return \$varvalue')"
    }


# create/refresh our ei_variable table
#
# this is called when the equipment is online
# so we can refresh/create the information
#
proc ei_variables_init spname {
    global $spname
    # create the table if it does not exist
    # no harm if it does exist
    #ei_var_create $spname ;#  done earlier in ei_defaults
    # if we have saved data from the past, load it in
    # if these rows already exists, they do not overwrite existing rows
    # because of uniqueness constraints
    #SQL "include ei_variable.tab" ;#  done earlier in ei_defaults
    
    # class SV, status variables
    set reply ""
 # When the equipment has a huge list of SV's, you just want to
 # query them once, save them, and not ask every initialization...
 if { ![info exists ${spname}(use_s1f11)] || [set ${spname}(use_s1f11)] } {
    set reply [secs_xact $spname S1F11R L]
    if { $reply == "TIMEOUT" } {
        set why [secs_xact_failure $spname]
        if { $why == "BAD_SEND" || $why == "NO_REPLY" } return
        }
    if { $reply != "TIMEOUT" } {
        # expect {L:n {L:3 <SVID> <SVNAME> <UNITS>}}
        set list [lreplace $reply 0 0]
        set SVlist L  ;# we will ask for values in a moment
        foreach L3 $list {
            rset $L3 {l3 {tSVID varID} {An varname} {Am units}} 
            set ID_TSN [lindex [split $tSVID :] 0]
            lappend SVlist [list $ID_TSN $varID]
            if { $varname == "" } { set varname $varID }
            # some equipment uses the same variable names with different 
            # varIDs (eg multiple chamber tool)
            # we want to create unique VFEInames so we embed $varID when needed
            set VFEIname [ei_VFEIname_unique $spname $varID $varname]
            set reply [SQL "insert into ei_variable (spname, varID, varname, varclass,\
 ID_TSN, units, VFEIname) values ('$spname', '$varID', '$varname',\
 'SV', '$ID_TSN', '$units', '$VFEIname')"]
            # if we are creating a new configuration record for CLOCK 
            # change the event report format from YYYYMMDDHHMMSScc to
            # YYYY-MM-DD hh:mm:ss.cc 
            if { ($VFEIname == "CLOCK") && ([string first "//c 0" $reply] >= 0 ) } {
                SQL "update ei_variable set varmethod='ei_clock_reformat \$varvalue'\
 where spname='$spname' and VFEIname='CLOCK'"
                }
            }
        }
    }
 if { (![info exists ${spname}(use_s1f3)] || [set ${spname}(use_s1f3)]) &&\
 ($reply != "TIMEOUT") } {
    if { [info exists SVlist] } { 
        ei_sv_refresh $spname $SVlist
        }\
    else { ei_sv_refresh $spname }
    }
    
    # class ECV equipment constants
    # You may have a huge list of ECVs so you can bypass querying them
    # every time - do it once, and save it.
 set reply ""
 if { ![info exists ${spname}(use_s2f29)] || [set ${spname}(use_s2f29)] } {
    set reply [secs_xact $spname S2F29R L]
    if { $reply == "TIMEOUT" } {
        set why [secs_xact_failure $spname]
        if { $why == "BAD_SEND" || $why == "NO_REPLY" } return
        }
    if { $reply != "TIMEOUT" } {
        set eclist [lreplace $reply 0 0]
        set EClist L  ;# we will ask for values in a moment
        foreach L6 $eclist {
            rset $L6 {l6 {tID varID} {An varname} ECMIN ECMAX ECDEF {Am units}}
            lappend EClist [list $tID $varID]
            set ID_TSN [lindex [split $tID :] 0]
            if { $varname == "" } { set varname $varID }
            set VFEIname [VFEIname $varname]
            set tD [lindex $ECDEF 0]
            set value_TSN [lindex [split $tD :] 0]
            # MIN, MAX, DEF could be lists or vectors - not likely though
            set MIN [lreplace $ECMIN 0 0]
            set MAX [lreplace $ECMAX 0 0]
            set DEF [lreplace $ECDEF 0 0]
            SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,units,ECMIN,ECMAX,ECDEF,VFEIname) values ('$spname',\
 '$varID', '$varname', 'ECV', '$value_TSN', '$ID_TSN', '$units', '$MIN','$MAX',\
 '$DEF','$VFEIname')"
           }
        }
    }
 if { (![info exists ${spname}(use_s2f13)] || [set ${spname}(use_s2f13)]) &&\
 ($reply != "TIMEOUT") } {
    # get the current values
    if { ![info exists EClist] } {
        ei_ecv_refresh $spname $EClist 
        }\
    else {
       ei_ecv_refresh $spname
       }
    }
     
    # we do not have a standard way to know DVVALs 
    # we want them because we can ask for them in reports
    # newer Hume interfaces implement DvvalList SV (introduced November 2004)
    set varvalue [lindex [ei_var_query $spname [list DvvalList] varname 0] 0]
    # the reply of ei_var_query is the type-value TSN expression, remove type L:n
    set varvalue [lreplace $varvalue 0 0]
    # varvalue is now [{L:2 <VID> <DVNAME>}]+ or empty
    foreach record $varvalue {
        rset $record {l2 {idTSN vid} {tn dvname}}
        if { $l2 == "L:2" } {
            set idTSN [lindex [split $idTSN :] 0]
            regsub -all ' $dvname _ dvname
            set VFEIname [VFEIname $dvname]
            set reply [SQL "insert into ei_variable (spname,varID,ID_TSN,varname,VFEIname,\
 varclass) values ('$spname','$vid','$idTSN','$dvname','$VFEIname','DVVAL')"]
            }
        }

    # help out broken configurations 
    SQL "update ei_variable set varmethod='return \$varvalue'\
 where spname='$spname' and varmethod='' and varclass<>'SV' and \
 varclass<>'ECV'"

    # process state meanings - user can install custom procedure
    #   look in ../custom to see example

    # if there is a variable named "EventDescriptions"
    # use it to insert/update the event table but do not overwrite
    # any non-blank descriptions that the user may have edited
    # the variable EventDescriptions is found in certain Hume-based
    # equipment interfaces
    set varvalue [lindex [ei_var_query $spname [list EventDescriptions] varname 0] 0]
    # the reply of ei_var_query is the type-value TSN expression, remove type L:n
    set varvalue [lreplace $varvalue 0 0]
    # varvalue is now [{L:2 <CEID> <description>}]+ or empty
    # or older Hume format, L:n {L:2 <CEID> <description>}
    catch {
        if { [llength $varvalue] == 1 } { ;# remove extra "{L   }" (older format)
            set Ln [lindex $varvalue 0]
            set Ln [lreplace $Ln 0 0]
            }\
        else { set Ln $varvalue }
        foreach pair $Ln {
            rset $pair {l2 {idTSN ceid} {td desc}}
            if { $l2 == "L:2" } {
                set reply [SQL "select description from ei_event where\
 spname='$spname' and CEID='$ceid'"]
                set ct [lindex $reply 4]
                if { $ct == "0" } {  ;# new event discovered
                    set idTSN [lindex [split $idTSN :] 0]
                    SQL "insert into ei_event (spname,CEID,VFEIname,event_class,\
 ID_TSN,description) values ('$spname','$ceid','$ceid','EQ','$idTSN','$desc')"
                    }\
                else {
                    set description [lindex [lindex [lindex $reply 6] 0] 0]
                    # do not change user's existing description
                    if { ![string compare $description ""] } {
                        SQL "update ei_event set description='$desc' where\
 spname='$spname' and CEID='$ceid'"
                        }
                    }
                }
            }
        }
    }

######################## ei_ecv_refresh #############################
######################## ei_ecv_refresh #############################
######################## ei_ecv_refresh #############################
#
# refresh knowledge of ECV values
#
proc ei_ecv_refresh {spname {EClist {}}} {
    global $spname
    if { [llength $EClist] == 0} {
        set reply [SQL "select ID_TSN,varID from ei_variable where\
 spname='$spname' and varclass='ECV'"]
        set EClist [concat L [lindex $reply 6]]
        }
    set reply [secs_xact $spname S2F13R $EClist]
    if { $reply != "TIMEOUT" } {
        set CLOCK [secs_CLOCK $spname]
        set max [llength $reply]
        for {set i 1} {$i < $max} {incr i} {
            set SV [lindex $reply $i]
            set tSV [lindex $SV 0]
            set value_TSN [lindex [split $tSV :] 0]
            if { $value_TSN == "A" } { set vSV [lindex $SV 1] }\
            else { set vSV [lreplace $SV 0 0] }
            set varID [lindex [lindex $EClist $i] 1]
            SQL "update ei_variable set value_TSN='$value_TSN',\
 varvalue='$vSV', t_latest='$CLOCK' where spname='$spname'\
 and varID='$varID'"
            }
        }
    return $reply
    }

######################## ei_sv_refresh ##############################
######################## ei_sv_refresh ##############################
######################## ei_sv_refresh ##############################
#
# refresh knowledge of SV values
#
proc ei_sv_refresh {spname {SVlist {}}} {
    global $spname
    # get the current SV values, which shows us the value type
    if { [llength $SVlist] == 0 } {
        set reply [SQL "select ID_TSN,varID from ei_variable where\
 spname='$spname' and varclass='SV'"]
        set SVlist [concat L [lindex $reply 6]]
        }
    set reply [secs_xact $spname S1F3R $SVlist]
    if { $reply != "TIMEOUT" } {
        set CLOCK [secs_CLOCK $spname]
        set max [llength $reply]
        for {set i 1} {$i < $max} {incr i} {
            set SV [lindex $reply $i]
            set varID [lindex [lindex $SVlist $i] 1]
            ei_varvalue_save $spname $varID $SV $CLOCK
            }
        }
    return $reply
    }

######################## ei_varvalue_save ##########################
######################## ei_varvalue_save ##########################
######################## ei_varvalue_save ##########################
#
# Save the value of a variable when the value might be large.
# Also, common code for the separation of TSN type information from 
# value information, and possibly saving the type information.
# Usually the value is stored in the ei_variable table field varvalue
# but if the value is larger than the field size, we store it
# in the $spname array, and create a method to access it.  The method
# gets more complicated because the variable value is possibly
# changing in size, or the user has customized method or type data.
# The ei_variable record exists for updating because that is where the
# variable ID information came from.
# (Motivated by large values of EventDescriptions).
# This method is called for Status Variables but it could be called
# for other data items such as Equipment Constants.
proc ei_varvalue_save {spname varID SV t_latest} {
    global $spname
    # parse type item and value(s)
    set value_TSN [lindex [split [lindex $SV 0] :] 0]
    if { $value_TSN == "A" } {	;# string values are always a single argument
        set value [lindex $SV 1]
        }\
    else { ;# vector and list data can be N arguments
        set value [lreplace $SV 0 0]
        }
    if { [string bytelength $value] <= [set ${spname}(maxlen_varvalue)] } {
        if { [info exists ${spname}(bigvalue_$varID)] } {
            # value got smaller from being oversize
            unset ${spname}(bigvalue_$varID)
            SQL "update ei_variable set value_TSN='$value_TSN', varvalue='$value', \
 t_latest='$t_latest' where spname='$spname' and varID='$varID'"
            # change varmethod to blank if not customized
            SQL "update ei_variable set varmethod='' where spname='$spname' \
 and varID='$varID' and varmethod='uplevel #0 set ${spname}(bigvalue_$varID)' "
            }\
        else {
            # here is the usual case 
            SQL "update ei_variable set value_TSN='$value_TSN', varvalue='$value', \
  t_latest='$t_latest' where spname='$spname' and varID='$varID'"
            # save type information only if not known - do not change customization
            SQL "update ei_variable set value_TSN='$value_TSN'\
  where spname='$spname' and varID='$varID' and value_TSN='' "
            }
        }\
    else {
        # store the oversize data item 
        set ${spname}(bigvalue_$varID) $value
        SQL "update ei_variable set value_TSN='$value_TSN',\
 varvalue='', varmethod='uplevel #0 set ${spname}(bigvalue_$varID)', \
 t_latest='$t_latest' where spname='$spname'\
 and varID='$varID'"
        }
    }


######################## ei_eqconst_set ######################
######################## ei_eqconst_set ######################
######################## ei_eqconst_set ######################
#
# set equipment constants - S2F15
# can use varID, varname, or VFEIname to identify variables!
# keep our own variable table in sync with the changes
#
# nvlist = {name value} pair list
# return 0 - ok
#        1 - at least 1 var does not exist
#        2 - not now
#        3 - at least 1 var out of range
#       TIMEOUT
proc ei_eqconst_set {spname nvlist fieldname} {
    set cmd L
    set cols {varID ID_TSN value_TSN varclass}
    foreach nv $nvlist {
        vset $nv "name value"
        set reply [SQL "select [join $cols ,] from ei_variable\
 where spname='$spname' and $fieldname='$name' "]
        set row [lindex [lindex $reply 6] 0]
        vset $row $cols
        if { $varclass != "ECV" } { return 1 }
        # revised for possible lists or vectors
        if { [string match A* $value_TSN] } {
            set ECV [list $value_TSN $value]
            }\
        else {
            set ECV $value_TSN
            foreach v $value { lappend ECV $v }
            }
        lappend cmd [list L:2 "$ID_TSN $varID" $ECV]
        }
    set reply [secs_xact $spname S2F15R $cmd]
    if { $reply == "TIMEOUT" } { return $reply }
    # expect <EAC>
    set rc [lindex $reply 1]
    set rc [expr $rc]	;# 0x00 -> 0
    # update our table representation
    if { $rc == "0" } {
        set CLOCK [secs_CLOCK $spname]
        foreach nv $nvlist {
            vset $nv "name value"
            SQL "update ei_variable set varvalue='$value', t_latest='$CLOCK'\
 where spname='$spname' and $fieldname='$name'"
            }
        }
        
    return $rc
    }

########################## ei_var_query #########################
########################## ei_var_query #########################
########################## ei_var_query #########################
#
# Query and return current values of a list of variables.
# Each item in the returned list is a TSN type value pair.
# An empty item means the item does not exist or does not
# currently have a valid value.
# You can use varID, varname, or VFEIname to identify variables!
# We keep our own variable table in sync with the current values.
#
proc ei_var_query {spname namelist fieldname {update 1}} {
    global $spname
    # first update our table by class of items
    # then just query values from our table
    # first check equipment constants
    if { $update } {
        set reply [SQL "select ID_TSN, varID from ei_variable\
 where spname='$spname' and varclass='ECV' and\
 ($fieldname='[join $namelist "' or $fieldname='"]')"]
        set rows [lindex $reply 6]
        if {$rows != ""} { 
            set reply [secs_xact $spname S2F13R "L $rows"]
            if { $reply == "TIMEOUT" } { return $reply }
            if { $reply != "L:0" } {
                set vlist [lreplace $reply 0 0]
                set max [llength $vlist]
                set t_latest [secs_CLOCK $spname]
                for {set i 0} {$i < $max} {incr i} {
                    set row [lindex $rows $i]
                    vset $row "ID_TSN varID"
                    set value [lindex $vlist $i]
                    # discard leading type item
                    if { [string match A* [lindex $value 0]] } {
                        set value [lindex $value 1] }\
                    else { set value [lreplace $value 0 0] }
                    SQL "update ei_variable set varvalue='$value',\
 t_latest='$t_latest' where spname='$spname' and varID='$varID'"
                    # value_TSN for ECV is discovered with the name so
                    # we are safe in assuming that it is known, and not
                    # trying to save it here.
                    }
                }
            }
        # now check status variables
        set reply [SQL "select ID_TSN, varID from ei_variable\
 where spname='$spname' and varclass='SV' and\
 ($fieldname='[join $namelist "' or $fieldname='"]')"]
        set rows [lindex $reply 6]
        if { $rows != ""} {
            set reply [secs_xact $spname S1F3R "L $rows"]
            if { $reply == "TIMEOUT" } { return $reply }
            if { $reply != "L:0" } {
                set vlist [lreplace $reply 0 0]
                set max [llength $vlist]
                set t_latest [secs_CLOCK $spname]
                for {set i 0} {$i < $max} {incr i} {
                    set row [lindex $rows $i]
                    vset $row "ID_TSN varID"
                    set SV [lindex $vlist $i]
                    ei_varvalue_save $spname $varID $SV $t_latest
                    }
                }
            }
        }

    # now walk the request, pulling together the values
    set notfound 0
    set cols "varclass value_TSN varmethod varvalue"
    set result ""
    foreach name $namelist {
        set reply [SQL "select [join $cols ,] from ei_variable\
 where spname='$spname' and $fieldname='$name'"]
        set row [lindex [lindex $reply 6] 0]
        vset $row $cols
        if { $row == "" || $value_TSN == "" } { 
            lappend result {} 
            continue
            }
        # 1/20/99 change - can install varmethod on any varclass
        #                  such as number to text mapping for SV
        if { [string compare $varmethod {}] } {
            # execute non-blank varmethod
            # driver supplies or maps value by configured code in varmethod
            # return code 2 from "return" is ok
            if { [catch $varmethod value]  == 1 } {
                set value "varmethod error - $value"
                }
            }\
        else { 
            # usual case for ECV or SV where varmethod is blank
            set value $varvalue 
            }
        # revised to correct handling of vectors and lists
        if { [string match A* $value_TSN] } { set record [list $value_TSN $value] }\
        else {
            set record $value_TSN
            # if value is not a proper list an error will propagate
            # should only happen to a developer who creates a faulty varmethod
            foreach val $value { lappend record $val }
            }
        lappend result $record
        }
    return $result
    }

        
################## ei_eqconst_managed_set ####################
################## ei_eqconst_managed_set ####################
################## ei_eqconst_managed_set ####################
#
# set ECVs to table value where host_managed
#
proc ei_eqconst_managed_set {spname} {
    set reply [SQL "select varID, host_setval from ei_variable\
 where spname='$spname' and varclass='ECV' and host_managed=1"]
    set nvlist [lindex $reply 6]
    if { [llength $nvlist] == 0 } { return 0 }
    return [ei_eqconst_set $spname $nvlist varID]
    }



################### ei_VFEIname_unique #######################
################### ei_VFEIname_unique #######################
################### ei_VFEIname_unique #######################
#
# see ../lib/VFEIname.tcl for proc VFEIname
#
# When assigning VFEInames to newly discovered Status Variables,
# there are cases where the equipment uses the same variable names
# with different integer IDs.  We want to have unique VFEInames
# so if necessary, we concatenate the unique SVID code.
#
# return value - the existing VFEIname or a new unique value.
# When assigning a name for a newly discovered variable, 
# if we find that the varname is not unique, and thus the default
# VFEIname is not unique, we will possibly update the existing
# row(s) that have the same name.
#
proc ei_VFEIname_unique {spname varID varname} {
   # if an entry already exists, return the existing VFEIname
   set reply [SQL "select VFEIname from ei_variable where\
 spname='$spname' and varID='$varID'"]
   if { [lindex $reply 4] == 1 } { return [lindex [lindex [lindex \
 $reply 6] 0] 0] }
   # if there is no conflict with existing data, use the usual mapping
   set reply [SQL "select varID, VFEIname from ei_variable where\
 spname='$spname' and varname='$varname'"]
   if { [lindex $reply 4] == 0 } { return [VFEIname $varname] }
   # Here we have more than 1 variable with the same name.
   # We possibly change an existing VFEIname to be more specific.
   # This happens only during variable discovery, so there should not
   # be existing report definitions, etc, that are messed-up.
   foreach row [lindex $reply 6] {
       vset $row {vid vfeiname}
       set exname [ei_VFEIname_ex $varname $vid]
       if { $exname != $vfeiname } {
           # changing an existing variable
           set ureply [SQL "update ei_variable set VFEIname='$exname' where \
 spname='$spname' and varID='$vid'"]
           }
       }
    # return a more specific name for the new record
    return [ei_VFEIname_ex $varname $varID]
    }

#
# an extended VFEIname that combines the variable ID code
#
proc ei_VFEIname_ex {varname vid {maxlen 32}} {
    set root [VFEIname $varname]
    set full ${root}_${vid}
    if { [string length $full] > $maxlen } {
        # truncate the left part, and have the $vid part be the last characters
        set vidlen [string length $vid]
        if { $vidlen > $maxlen } { error "Variable ID length, $vidlen, is > maximum $maxlen" }
        set iroot [expr {$maxlen - $vidlen-2}]
        set full [string range $root 0 $iroot]_${vid}
        }
    return $full
    }
    
