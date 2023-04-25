#
# Support for send on NT using DDE
# if you source this file, you get replacement versions of the send command
#
# (C) Copyright Hume Integration Software 1994, 1995
# All Rights Reserved
# Licensed Materials - Property of Hume Integration Software, Austin Texas


# WARNING - If you are new to Tcl this file is not typical - it is loaded
#           with escaped special characters and peculiar list/concat operations,
#           because we are mixing execution in our own interpreter with 
#           execution in a remote one.
#           

namespace eval ::dmh {

if { [info commands dmh_dde] == "dmh_dde" } {
 proc winfo_interps {} {
   set result "" 
   foreach server [dmh_dde query] {
       vset $server "service topic"
       if { $topic == "tcl74" } {
           lappend result $service
           }
       }
   return $result
   }
 } 

#
# this send is limited to commands <= 200 bytes or so
# the limit is an undocumented aspect of DDE "item" strings
# It can handle a large reply.
 proc dmh_dde_req_send {interp command args} {
    variable dmh_dde_hconv
    if { ![info exists dmh_dde_hconv($interp)] } {
        if { [catch { set dmh_dde_hconv($interp) [dmh_dde connect $interp tcl74] }] } {
            return -code error "no registered interpreter named \"$interp\""
            }

        set dmh_dde_hconv($interp) [dmh_dde connect $interp tcl74]
        }
    for {set i 0} {$i < 2} {incr i} {
        set rc1 [catch {dmh_dde request $dmh_dde_hconv($interp) [concat $command $args]} reply]
        if { $rc1 } { ;# maybe its a stale connection, try again
            if { [catch { set dmh_dde_hconv($interp) [dmh_dde connect $interp tcl74] }] } {
               unset dmh_dde_hconv($interp)
               return -code error "no registered interpreter named \"$interp\""
               }
            }\
        else break
        }
    if { $rc1 } { error "" }
    vset $reply [list rc data]
    if { $rc == "0" } {return $data }
    error $data
    }

# dde execute can handle a long command string but it cannot
# reply with data - a design limit of DDE
# 
# changing this procedure name breaks interoperability with past versions
 proc dde_execute {interp cmd args} {
    variable dmh_dde_hconv
    if { ![info exists dmh_dde_hconv($interp)] } {
        if { [catch { set dmh_dde_hconv($interp) [dmh_dde connect $interp tcl74] }] } {
            return -code error "no registered interpreter named \"$interp\""
            }
        set dmh_dde_hconv($interp) [dmh_dde connect $interp tcl74]
        }
    for {set i 0} {$i < 2} {incr i} {
        set rc1 [catch {dmh_dde execute $dmh_dde_hconv($interp) [concat $cmd $args]} result]
        if { $rc1 } { ;# maybe its a stale connection, try again
            if { [catch { set dmh_dde_hconv($interp) [dmh_dde connect $interp tcl74] }] } {
               unset dmh_dde_hconv($interp)
               return -code error "no registered interpreter named \"$interp\""
               }
            }\
        else break
        }
    if { $rc1 } { return -code error $result }
    return
    }   



# execute send with a Tcl interp that uses DDE
# we nest DDE executes in order to return data
# It remains to be seen how deep you can nest sends...deep enough to inspect!
# this send can handle long sends
 proc send {interp args} {
     variable dmh_dde_hconv 
     variable dmh_dde_ctr
     if { ![info exists dmh_dde_ctr] } { set dmh_dde_ctr 0 }
     incr dmh_dde_ctr
     set varname ::dmh::dmh_dde_x_$dmh_dde_ctr
     set $varname [list 1 {send failed without a reply interaction}]
     set this_interp [lindex [dmh_dde service] 0]
     set user_cmd $args
     for {set i 0} {$i < 2} {incr i} {
         if { [lindex $user_cmd 0] == "-async" } { set user_cmd [lrange $user_cmd 1 end] ; continue }
         if { [lindex $user_cmd 0] == "-displayof"} { error "-displayof is not supported" }
         break
         }           
     # do a nested evaluation back to our interp!
     set remote_cmd "dde_execute \{$this_interp\} set $varname \[[list mh_eval $user_cmd]\]" 
     set rc [catch {dde_execute $interp $remote_cmd} result]
     if { !$rc } {     
         vset [set $varname] {rc result}
         }
     unset $varname
     if { $rc } { return -code error $result }
     return $result
     }
} ;# namespace
