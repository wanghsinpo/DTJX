# $Header: /usr/cvsroot/gem/equip/eq_recipe.tcl,v 1.10 2005/03/25 22:58:36 hume Exp $
#
# $Log: eq_recipe.tcl,v $
# Revision 1.10  2005/03/25 22:58:36  hume
# Revised to integrate with and support equipment initiated process program
# transfers coming from .NET SecsEquip and similar libraries.
#
# Revision 1.9  2004/11/19 20:19:30  hume
# Added comments on "Process Program" vs "Recipe" usage.  (recipe_delete)
# change on download revised - only see it if file actually is replaced.
#
# Revision 1.8  2004/10/12 13:48:12  hume
# Updated recipe binary transfer logic.
#
# Revision 1.7  2004/09/05 15:13:21  hume
# Made recipe directory configurable, recipe events can be seen by tracing
# recipe_delete, recipe_download and recipe_upload.
#
# Revision 1.6  2004/09/04 23:18:22  hume
# new binary recipe transfer option
#
# Revision 1.5  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.4  2002/08/13 12:18:36  hume
# Needed to return after recipe save file error to avoid 2nd reply send.
#
# Revision 1.3  1999/01/12 22:41:32  hume
# Added spooling functionality.
#
# Revision 1.2  1997/07/01 13:50:04  hume
# Subdirectory "CVS" is listed as a recipe.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
#
#  Recipe or Process Program ?
# 
#  It used to be these terms were not distinguished, and they are
#  still used equivalently in normal conversation.
#  With the introduction of Stream 15, the term recipe has come to
#  mean a process program with additional attributes which is transferred 
#  using Stream 15 commands.  The Stream 7 commands are used with 
#  Process programs which are not required to have the attributes of recipes.
#
#  Our software predates this distinction, so we have procedure names
#  and variable names that improperly use the word recipe when they should
#  refer to process programs.
#
#  We recommend that Equipment providers use the simpler Process Program
#  commands until they have strong reasons to support Stream 15.

# recd S7F19 process program dir request
#
proc eq_recipe_dir spname {
    global $spname
    set dir [set ${spname}(recipe_dir)]
    set list [glob [file join $dir *]]
    set recipes L
    foreach item [lsort $list] {
        if { [file isdirectory $item] } continue   ;# eg CVS
        set recipe [file tail $item]
        lappend recipes [list A $recipe]
        }
    $spname put S7F20 $recipes
    }
 

#
# recd S7F5 PP upload request
#
proc eq_recipe_upload spname {
    global $spname
    set PPID [set ${spname}(lastrmsg)]
    # A:x xxxxx
    set name [lindex $PPID 1]
    vset [eq_ppbody_read $spname $name] {rc PPBODY}
    if { $rc < 0 } { 
        $spname put S7F6 L
        return 
        }
    $spname put S7F6 [list L $PPID $PPBODY]
    # you may want to know about this to update the GUI, create a data change that
    # a subscriber can see
    if { [set ${spname}(recipe_upload)] == $name } {
        set ${spname}(recipe_upload) {}
        }
    set ${spname}(recipe_upload) $name
    }

# read the body of a process program and convert to SECS data
# return [list $rc $PPBODY]
# rc 0 is success
# -10 file error
proc eq_ppbody_read {spname name} {
    global $spname
    set file [file join [set ${spname}(recipe_dir)] $name]
    if { ![file exists $file] } {
        return [list -10 "Upload error: file \"$file\" does not exist"]
        }
    # the following works for binary or text recipes
    if { [catch {
        set fid [open $file r]
        fconfigure $fid -translation binary
        set data [read $fid]
        close $fid
        } etxt] } {
        catch {close $fid}
        return [list -10 "Upload File error: $etxt"]
        }
    # not all hosts can handle binary data sent as type A (ASCII)
    # you should send recipes as type B (binary) if they are not printable ASCII text
    if {[set ${spname}(binary_recipes)]} {
        set PPBODY B
        # append each byte as an integer
        foreach ch [split $data {}] {
            scan $ch %c i
            lappend PPBODY [format %d $i]
            }
        }\
    else {
        # text recipe - one string argument
        set PPBODY [list A $data]
        }
    return [list 0 $PPBODY]
    }

#
# received S7F3 or S7F6 - receive a PP download
# Stream 9 messages are sent if the data format is not proper
# S7F4 reply message is sent if appropriate
# returns [list $rc $msg]
# rc == 0 success
# -10 file system error
# -11 improper data
# -12 denial
proc eq_recipe_download spname  {
    global $spname
    if { [set ${spname}(lastrSFR)] == "S7F3R" } { set sendS7F4 1 }\
    else { 
        # receiving a S7F6 reply 
        # an L:0 reply for S7F6 is expected for refusal or error
        set sendS7F4 0 
        if { [set ${spname}(lastrmsg)] == "L:0" } {
            return {-12 REQUEST_DENIED}
            }
        }
    rset [set ${spname}(lastrmsg)] {L2 {An name} PPBODY}
    if { $L2 != "L:2" } {
        eq_S9_reply $spname 7
        return {-11 IMPROPER_DATA}
        }   
    if {[set ${spname}(binary_recipes)]} {
        # binary data, B:m b1 b2 b3 ... bm
        set data {}
        set type [lindex $PPBODY 0]
        if { [string first "B:" $type] != 0 } {
            eq_S9_reply $spname 7
            return {-11 IMPROPER_DATA}
            }
        set codes [lreplace $PPBODY 0 0]
        # convert 0xhh to byte, add to binary string (represented with utf-8)
        foreach b $codes { 
            set i [expr {$b}]
            append data [format %c $i]
            }
        }\
    else {
        # expect ASCII recipe data
        set type [lindex $PPBODY 0]
        if { [string first "A:" $type] != 0 } {
            eq_S9_reply $spname 7
            return {-11 IMPROPER_DATA}
            }
        rset $PPBODY {Am data}
        }
    # a real application has to validate $data - validation can be deferred until the
    # recipe is loaded for use when it has to be checked anyway
    # or it can be triggered by the (recipe_download) change
    # data subscriber can see that recipe is being deleted and replaced by new download
    if { [set ${spname}(recipe_delete)] == $name } {
        # must pre-clear so data change event is seen
        set ${spname}(recipe_delete) {}
        }
    set pathname [file join [set ${spname}(recipe_dir)] $name]
    if { [file exists $pathname] } { 
        set ${spname}(recipe_delete) $name
        }
    if { [set ${spname}(recipe_download)] == $name } {
        set ${spname}(recipe_download) {}  ;# pre-clear so difference will be seen
        }
    # Tcl converts from utf-8 to binary while writing to the file
    if { [catch {
        set fid [open $pathname w]
        fconfigure $fid -translation binary
        puts -nonewline $fid $data
        close $fid
        } etxt] } {
        # uh-oh file system error
        catch { close $fid }
        if {$sendS7F4} { $spname put S7F4 "B 5" }  ;# error reply
        return [list -10 "Download File error: $etxt"]
        }
    # tell host success
    if {$sendS7F4} { $spname put S7F4 "B 0" }
    # signal to subscriber success of recipe download - he should initiate a verify/validate
    set ${spname}(recipe_download) $name
    return [list 0 $pathname]
    }
        
#
# recd S7F17 recipe delete
# Ln <PPID>
# if n==0 delete all
#  return <ACKC7> 0=ok, 1=permissions, 4=not found
proc eq_recipe_del spname {
    global $spname
    set request [set ${spname}(lastrmsg)]
    set files ""
    if { $request == "L:0" } {
        set files [glob [file join [set ${spname}(recipe_dir)] *]]
        }\
    else {
        foreach item [lreplace $request 0 0] {
            vset $item "typecode name"
            set file [file join [set ${spname}(recipe_dir)] $name]
            if { ![file isfile $file] } {
                $spname put S7F18 "B 4"
                return
                }
            lappend files $file
            }
        }
    set ${spname}(recipe_delete) {}
    foreach file $files {
        if { [file isdirectory $file] } {continue}
        if { [catch {file delete $file}] } {
            $spname put S7F18 "B 1"
            return
            }
        set name [file tail $file]
        set ${spname}(recipe_delete) $name
        }
    $spname put S7F18 "B 0"
    } 
 

