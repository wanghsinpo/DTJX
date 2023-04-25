# $Header: /usr/cvsroot/tcllib84/hub.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# $Log: hub.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.6  2002/04/07 20:01:09  hume
# Rearranged CSV code to have hub_select_to_csv usage.
#
# Revision 1.5  2001/12/04 15:00:12  hume
# Changed CSV newline conversion to \n instead of escaped newline.
#
# Revision 1.4  2001/07/14 02:22:28  hume
# Added hub_table_csv
#
# Revision 1.3  2001/05/25 22:41:12  hume
# Backup restoration.
#
# Revision 1.3  2001/03/16 15:48:59  hume
# hub_tables_load_all - fixed trailing quote in pattern.
#
# Revision 1.2  2000/04/25 15:58:50  hume
# fixes for tablenames and column names > 31 max characters
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.1.1.1  1999/07/02 18:48:37  hume
# Starting point for Tcl 8.1.
#
# Revision 1.2  1997/10/09 12:45:52  hume
# Added changes for double-click table display.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.1  1997/06/16 11:01:10  hume
# Moved generic hub procedures into library for use with any executable.
#
namespace eval ::dmh {

##################### PUBLIC/LEGACY PROCEDURES ##############################
#
# These procedures were originally part of the hubxx script.
# Here they are in the library because they can be useful for
# any executable.
# These are procedures that do not involve a UI.  The hubxx script
# still has the UI procedures.


#
# return list of {columnname datatype key}
#
proc hub_table_schema_list {tab} {
   set list [lreplace [execute "dump schema $tab"] 0 2]
   # return empty for non-existent table
   if { $list == "" } { return "" }
   set list [lreplace $list end end]
   set result ""
   foreach line $list {
       vset $line "name type key"
       lappend result [list $name $type $key]
       }
   return $result
   }


#
# return list of {table rowct subct}
#
proc hub_table_list {} {
    set list [lreplace [execute "dump table"] 0 1]
    set list [lreplace $list end end]
    set result ""
    foreach line $list {
        vset $line "tab rowct x c u p subct"
        lappend result [list $tab $rowct $subct]
        }
    return $result
    }

#
# return count of rows for table, "" if does not exist
# new with dmh80
#
proc hub_table_count {Tab} {
    set tab [string tolower $Tab]
    set list [lreplace [execute "dump table"] 0 1]
    set list [string tolower [lreplace $list end end]]
    foreach line $list {
        vset $line "table rowct x c u p subct"
        if { $tab == $table } { return $rowct }
        }
    return ""
    }

# 
# return a CSV representation of a Tcl Reply Format selection result
# CSV - only data containing , needs quoting and thus escaping imbedded quotes
# Excel will reinterpret leading zeros and dates even when surrounded with quotes
#
proc hub_select_to_csv {reply {do_header 1}} {
    set result {}
    foreach {token table cols keys ct err rows} $reply {}
    if { $do_header } { lappend results [join $cols ,] }
    set ctcols [llength $cols]
    foreach row $rows {
        set values {}
        set j 0
        # convert newlines to \n - most CSV software does not expect data to span lines.
        regsub -all \n $row \\n row
        foreach col $cols {
            set v [lindex $row $j]
            incr j
            # quotes not needed except if data contains comma
            #  strings like "022" have 0 stripped and dates are re-interpreted no matter what
            if { [string first , $v] >= 0 } { 
                # imbedded quotes are doubled
                regsub -all \\\" $v \"\" v
                append values \"$v\"
                }\
            else { append values $v }
            if { $j < $ctcols } {append values , }
            }
        lappend results $values
        }
    return $results
    }

# Write table data as CSV file
# return ct of rows written
# new with Tcl 8.3.3
proc hub_table_csv {table {pathname {}} {cols *} {where {}} } {
    if { $pathname == {} } { set pathname ${table}.csv }
    set fid [open $pathname w]
    set reply [hub_select_to_csv [SQL "select [join $cols ,] from $table $where"]]
    puts $fid [join $reply \n]
    close $fid
    set line_ct [llength $reply]
    incr line_ct -1 ;# header line
    return $line_ct  ;# count of data rows written
    }

#
# save all tables
#   new with dmh40
#
proc hub_tables_save_all {} {
    set result ""
    foreach tab [hub_tables] {
        lappend result [execute "write over $tab"]
        }
    return $result
    }


#
# return list of table names
#  new with dmh40
#
proc hub_tables {} {
    set tablist ""
    foreach row [hub_table_list] {
        lappend tablist [lindex $row 0]
        }
    return $tablist
    }


#
# load all tab files in the current directory
# any existing tables of same name are dropped first
#   new with dmh40
#
proc hub_tables_load_all {} {
    set result ""
    foreach tabfile [glob -nocomplain *.tab] {
        set tab [file rootname [file tail $tabfile]]
        lappend result [execute "read over $tab"]
        }
    return $result
    }


#
# table existence check
#  new with dmh40
# only 1st 31 chars are significant
proc hub_table_exists Tab {
    set tab [string range [string tolower $Tab] 0 30]
    set tlist [string tolower [hub_tables]]
    if { [lsearch -exact $tlist $tab] >= 0 } { return 1 }
    return 0
    }


# for one or more tables, return list of subscriptions
# {table subname open_stmt}
#
proc hub_table_sub_list {table_list} {
   set result ""
   foreach table $table_list {
       set text [execute "dump sub $table"]
       set ct 0
       foreach line $text {
           if { [string first //c $line] == 0 } break
           incr ct
           if { $ct == 1 } continue
           vset $line "subname open_stmt"
           if { $open_stmt == "" } continue   ;# NONE {}
           lappend result [list $table $subname $open_stmt]
           }
       }
    return $result
    }


# close all subscriptions
# the SEMATECH hub would spit out delete notifications at exit
# so you had to close the subs to avoid having subscribers see deletes
#
proc hub_subs_close_all {} {
    foreach table [hub_tables] {
        set slist [hub_table_sub_list $table]
        foreach rec $slist {
            vset $rec "tab sub"
            execute "close sub $sub to $tab"
            }
        }
    }


#
# return the datatype of a field using a Schema List
#   returned from hub_table_schema_list
# only 1st 31 chars are significant
#
proc hub_fieldtype {Col Schema} {
     set col [string range [string tolower $Col] 0 30]
     set i [lsearch -regexp [string tolower $Schema] ^$col\ ]
     return [lindex [lindex $Schema $i] 1]
     }

} ;# namespace
