# $Header: /usr/cvsroot/tcllib84/odbc.tcl,v 1.2 2002/10/25 21:38:25 hume Exp $
#
# $Log: odbc.tcl,v $
# Revision 1.2  2002/10/25 21:38:25  hume
# Fixed issues from namespace usage.  Hub GUI script assumes global namespace.
#
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.8  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.7  2001/08/04 13:48:16  hume
# Fix for Oracle system table where select count(*) failed.
#
# Revision 1.6  2001/06/08 13:25:56  hume
# Added F5 and Delete accelerator keys.
#
# Revision 1.5  2000/03/15 14:24:49  hume
# Use console for Tcl if it exists since stdout goes there.
# Fixed table refresh when not connected.
#
# Revision 1.4  2000/03/15 03:33:11  hume
# New consolidated hub and odbc console windows.
#
# Revision 1.3  2000/03/09 20:42:46  hume
# Created an option menu with "Disable Row Counting" option.
#
# Revision 1.2  2000/03/09 20:15:49  hume
# Has NO_SQL_ROW_COUNT environment var usage.
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.2  1999/10/08 15:08:36  hume
# Renamed command window code.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.2  1999/07/08 18:18:43  hume
# Fixes for situation of same table name with multiple owners.
#
# Revision 1.1.1.1  1999/07/02 18:48:37  hume
# Starting point for Tcl 8.1.
#
# Revision 1.6  1999/06/09 22:29:55  hume
# Had an error in error handling code that was rarely executed.
#
# Revision 1.5  1999/06/09 21:39:41  hume
# Fixed minor GUI bugs when using ODBC separately from RxSQLsrv.
#
# Revision 1.4  1999/05/06 21:55:22  hume
# Replaced use of menubuttons to have accelerator keys work on NT.
#
# Revision 1.3  1999/04/16 19:48:57  hume
# Revised table display code to use hub procedures.
#
# Revision 1.2  1997/11/08 22:27:30  hume
# Invokes Tcl console if it exists instead of ECH command window.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.3  1997/06/04 21:39:22  hume
# Fixed bug with rusure dialog.
#
# Revision 1.2  1997/05/31 14:33:24  hume
# Revised use of tk_dialog - created as child of toplevel parent in case root
# window is iconified, it still shows up.  Deleted obsolete tk_MenuBar calls.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
# Revision 1.2  1996/07/26 20:46:38  hume
# Fixed bug where xbm was found.
#
# Revision 1.1  1996/07/20 17:04:48  hume
# Added odbc for NT.
#
# Revision 1.3  1996/07/01 12:38:22  hume
# Changes for Tk 4.0 - shared scrollbar, listbox geometry, middle button paste.
#
# Revision 1.1.1.1  1996/03/28  03:04:59  hume
# First checkin.
#
#
# higher-level code that uses odbc connections
# provides window interface to the database
#
# Licensed Material
# Hume Integration Software, Austin, TX
# Do not copy without permission.
#
namespace eval ::dmh {

#
# create a window that shows tables and offers a menu 
# The menu item "SQL command" requires the RxSQLsrv emulation code
#
proc odbc_tabwin {{w .} {conn sq1} {title ""}} {
   if { $w != "." } {
       catch { destroy $w }
       toplevel $w
       set win $w
       }\
   else {  
       # root window 
       set win ""
       wm protocol $w WM_DELETE_WINDOW [list ::dmh::odbc_tabwin_close $w $conn]
       }
   if { $title == "" } {
       set title "ODBC Database"
       if { [info commands $conn] == $conn } {
           variable gs_database
           if { [info exists gs_database] } {
               append title " $gs_database"
               }\
           else { append title " Connection $conn" }
           }\
       else {
           append title " (Not Connected)"
           }
       }
   wm title $w $title
   #wm iconname $w "ODBC Database"
   #wm iconbitmap $w @/usr/local/bin/table.xbm
   menu $win.menu -tearoff 0 -relief flat
   set m $win.menu.bFile
   $win.menu add cascade -label File -menu $m -underline 0
   menu $m -tearoff 0

   $m add command -label "SQL command..." -underline 0 \
       -command {::dmh::dmh_cmd_win SQL ODBC}
   $m add separator
   $m add command -label "Tcl command..." -underline 0 \
       -command {if {[info commands console] == "console"} {console show} else {::dmh::dmh_cmd_win Tcl ODBC}}
   $m add separator
   $m add command -label "Refresh" -underline 0 -accelerator F5\
       -command [list ::dmh::odbc_tabwin_refresh $win.f.list $conn]
   $m add separator
   $m add command -label "Exit" -underline 0 \
       -command [list ::dmh::odbc_tabwin_close $w $conn]
   
   set m $win.menu.bTable
   set p $win.menu.tabp
   $win.menu add cascade -label Table -menu $m -underline 0
   menu $m -tearoff 0
   menu $p -tearoff 0
   foreach m [list $m $p] {
   $m add command -label "Schema..." -underline 0 \
       -command [list ::dmh::odbc_table_schema $win.f.list $conn]
   $m add separator
   $m add command -label "Data..." -underline 0 \
       -command [list ::dmh::odbc_fastdata $win.f.list $conn]
   $m add separator
   $m add command -label "Insert..." -underline 0 \
       -command [list ::dmh::odbc_table_insert $win.f.list $conn]
   }
   set m $win.menu.bOptions
   $win.menu add cascade -label Options -menu $m -underline 0
   menu $m -tearoff 0
   $m add checkbutton -label "Disable Row Counting" -variable env(NO_SQL_ROW_COUNT)

   $w configure -menu $win.menu 

   frame $win.f
   pack $win.f -side top -expand yes -fill both
   
   scrollbar $win.f.scroll -relief sunken -command "$win.f.list yview"
   listbox $win.f.list -yscroll "$win.f.scroll set" -relief sunken \
       -setgrid 1 -font fixed -selectmode extended
   bind $win.f.list <Button-3> "tk_popup $win.menu.tabp %X %Y"
   $win.f.list configure -height 12 -width 70
   pack $win.f.scroll -side right -fill y
   pack $win.f.list -side left -expand yes -fill both
   bind $w <F5> [list ::dmh::odbc_tabwin_refresh $win.f.list $conn]
   }

proc odbc_tabwin_close {w conn} {
    set win .rusure
    if { $w != "." } { set win ${w}${win} }
    set choice [tk_dialog $win "Confirm Exit"\
 "This action will shutdown the Database connection and exit.  Please confirm." \
  questhead 1 Shutdown Cancel]
    if { $choice == 0 } {
        catch { $conn close }
        exit
        }
    }
    

# refresh display of tables
#
proc odbc_tabwin_refresh {tablelist conn} {
   global env
   if { [info commands $conn] != $conn } {
       tk_dialog .odbc_popup "Table Display Refresh"\
 "Use the SQL connect command to connect to a database before trying\
 to refresh the table list.  The connect command can also
 be used on the command line at program start." info 0 Dismiss
       return
       }
   set data [$conn catalog tables]
   set cols [string tolower [lindex $data 2]]
   set owner_var table_owner
   if { [lsearch -exact $cols $owner_var] < 0 } {
       if { [lsearch -exact $cols table_schem] >= 0 } {
           set owner_var table_schem  ;# IBM DB2 
           }\
       else {
           set owner_var na
           set na {}
           }
       }
       
   set rows [lindex $data 6]
   $tablelist delete 0 end
   $tablelist insert end "Table Name                              Remarks  Row Count"
   $tablelist insert end "----------------------------------------------------------"
     
   foreach row $rows {
       vset $row $cols
       set owner [set $owner_var]
       if { $owner != "" } { set table_name "$owner.$table_name" }
       set line [format "%-39s %s" [list $table_name]\
   [list $remarks]]
        $tablelist insert end $line
        }
   if { [info exists env(NO_SQL_ROW_COUNT)] && $env(NO_SQL_ROW_COUNT) } { } \
   else { odbc_count_refresh $tablelist 2 $conn }
   }

proc odbc_count_refresh {tablelist row conn} {
    set rowmax [expr [$tablelist size] - 1]
    if { $row > $rowmax } return
    set text [$tablelist get $row]
    set table [lindex $text 0]
    # you cannot count Oracle 8.1.7 system table SYS._default_auditing_options_
    # so use catch { }
    if { [catch {$conn "select count(*) from $table"} reply] } { set ct 0 } else {
        set ct [lindex [lindex [lindex $reply 6] 0] 0]
	}
    append text [format " %8s" $ct]
    $tablelist delete $row $row 
    $tablelist insert $row $text
    update idletasks
    incr row
    after 1 [list ::dmh::odbc_count_refresh $tablelist $row $conn]
    }
    

proc odbc_ui_usage {object} {
    tk_dialog .ouu "ODBC Usage" "Select a $object before indicating this action."\
 info 0 Dismiss
    }

# return list of selected tables
proc odbc_tabwin_selection {lb} {
    set indexlist [$lb curselection]
    set tables ""
    foreach i $indexlist {
        if { $i <= 1 } {
            odbc_ui_usage table
            return ""
            }
        lappend tables [lindex [$lb get $i] 0]
        }
    if { $tables == "" } {
        odbc_ui_usage table
        return ""
        }
    return $tables
   }  

proc odbc_table_schema {lb conn} {
   set tables [odbc_tabwin_selection $lb]
   foreach tablename $tables {
       odbc_schema_win $conn $tablename $lb
       }
    }

proc odbc_schema_win {conn table lb} {
    set reply [odbc_schema_reply $conn $table]
    set ct [lindex $reply 4]
    if { $ct == 0 } {
       tk_dialog $lb.pop "Table Schema" "Schema query failed for table $table [lindex $reply 5]"\
 error 0 Dismiss
       return
       }
    odbc_load_hub
    hub_data_w ps $reply
    }

proc odbc_schema_reply {conn table} {
    set reply [$conn schema $table]
    set ct [lindex $reply 4]
    set reply [lreplace $reply 1 1 $table]
    if { $ct != 0 } {
        set reply [lreplace $reply 5 5 $conn]
        }
    return $reply
    }

proc odbc_load_hub {} {
    if { [info commands hub_data_w] != "hub_data_w" } {
        global env 
        if { [info exists env(DMH_BIN)] } { set p $env(DMH_BIN) }\
        else { set p /usr/local/bin }
        # if we are package loaded into 8.X we should still load 8.4 software
		# hub logic assumes global namespace
		set pathname [file join $p hub84]
        namespace eval :: [list source $pathname]
        }
    }
        
# persistent schema ps
proc ::hub_dataps_menu {w table lb lbhead conn helpvar} {
    variable $helpvar
    wm title $w "Table $table Schema"
    wm iconname $w $table
    catch { wm iconbitmap $w @[file_local join $::dmh::dmh_library table.xbm] }
    set m $w.menu.edm
    set p $w.menu.edp
    $w.menu add cascade -label Edit -menu $m -underline 0
    menu $m
    menu $p -tearoff 0
    set ${helpvar}(1) "Refresh the display of schema data"
    set ${helpvar}(2) "Dismiss this window"
    foreach menu [list $m $p] {
    $menu add command -label "Refresh" -underline 0  -command \
 "$w.menu configure -cursor watch ; ::hub_data_w_refresh $w \[::dmh::odbc_schema_reply $conn $table\]"
    $menu add separator
    $menu add command -label "Close" -underline 0  -command "destroy $w"
    }
    }


# this reply is consistent with Sybase
proc ibmdb2_table_schema {tablename {conn SQL}} {
    set tablename [string toupper $tablename]
    if { [string first . $tablename] > 0 } {
        vset [split $tablename .] "tbcreator tbname"
        set where "tbcreator='$tbcreator' and tbname='$tbname'"
        }\
    else {
        set where "tbname='$tablename'"
        }
    set cols "NAME,TYPENAME,LENGTH,LENGTH,SCALE,NULLS,REMARKS"
    set reply [$conn "select $cols from sysibm.syscolumns where $where order by COLNO"]
    set cols "column_name type_name precision length scale nullable remarks"
    set reply [lreplace $reply 2 2 $cols]
    return $reply
    }
 
    

proc odbc_fastdata {lb conn} {
   set tables [odbc_tabwin_selection $lb]
   foreach table $tables { odbc_table_win $conn $table }
   }

proc odbc_table_win {conn tablename} {
    if { [string first . $tablename] > 0 } {
        set table [lindex [split $tablename .] 1]
        }\
    else { set table $tablename }
    set stmt "select * from $tablename"
    set clientdata [list $conn $stmt $tablename]
    set reply [$conn $stmt]
    set reply [lreplace $reply 1 1 $table]
    set reply [lreplace $reply 5 5 $clientdata]
    odbc_load_hub
    hub_data_w pt $reply
    }

# persistent table pt
proc ::hub_datapt_menu {w table lb lbhead cd helpvar} {
    vset $cd "conn stmt tablename"
    set stmt 
    variable $helpvar
    wm title $w "ODBC Table $table Data"
    wm iconname $w $table
    catch { wm iconbitmap $w @[file_local join $::dmh::dmh_library table.xbm] }
    set m $w.menu.edm
    set p $w.menu.edp
    $w.menu add cascade -label Edit -menu $m -underline 0
    menu $m
    menu $p -tearoff 0
    set ${helpvar}(1) "Enter new data row(s) for this table"
    set ${helpvar}(2) "Delete the selected data rows"
    set ${helpvar}(4) "Refresh the displayed data"
    set ${helpvar}(6) "Display the Schema of table $table"
    set ${helpvar}(8) "Dismiss this window"
    foreach menu [list $m $p] {
    $menu add command -label "Insert..." -underline 0  -command [list ::dmh::odbc_insert_dlg $tablename $conn]
    $menu add command -label "Delete..." -underline 0  -accelerator Delete\
 -command [list ::dmh::odbc_tabrow_del $conn $tablename $lb $lbhead]
    $menu add separator
    $menu add command -label "Refresh" -underline 0  -accelerator F5 -command \
 "$w.menu configure -cursor watch ; ::hub_data_w_refresh $w \[[list $conn $stmt]\]"
    $menu add separator
    $menu add command -label "Schema..." -underline 0  -command [list ::dmh::odbc_schema_win $conn $tablename $lb]
    $menu add separator
    $menu add command -label "Close" -underline 0  -command "destroy $w"
    }
    bind $w <F5> "$w.menu configure -cursor watch ; ::hub_data_w_refresh $w \[[list $conn $stmt]\]"
    bind $w <Delete> [list ::dmh::odbc_tabrow_del $conn $tablename $lb $lbhead]
    }

proc odbc_tabrow_del {conn tablename lb lbhead} {
    set ilist [$lb curselection]
    if { $ilist == "" } { 
         hub_usage "Data Row" 1 $lb
         return ""
         }
    if { [string first . $tablename] > 0 } {
        set table [lindex [split $tablename .] 1]
        }\
    else { set table $tablename }
    set reply [$conn schema $tablename]
    if { [lindex $reply 4] == 0 } {
       tk_dialog .pop "Table Insert" "Schema query failed for table $table [lindex $reply 5]"\
 error 0 Dismiss
       return
       }
    set cols [string tolower [lindex $reply 2]]
    set Keys ""
    foreach row [lindex $reply 6] {
        vset $row $cols
        if { $nullable == 0 } { lappend Keys $column_name }
        set type [string tolower $type_name]
        set use_quotes($column_name) 1
        foreach p {int float real deci num} {
            if { [string first $p $type] >= 0 } {
                set use_quotes($column_name) 0
                break
                }
            }
        }
        
    set Cols [$lbhead get 0]
    set where {}
    foreach index $ilist {
        set text [$lb get $index]
        set where_all {}
        set where_key {}
        set i 0
        foreach Col $Cols {
            set value [lindex $text $i]
            incr i
            if { $use_quotes($Col) } {
                regsub -all {\'} $value {''} value
                set value '$value'
                }
            lappend where_all $Col=$value
            if { [lsearch -exact $Keys $Col] >= 0 } {
                lappend where_key $Col=$value
                }
            }
        if { [llength $where_key] > 0 } {
            lappend where [join $where_key { and }]
            }\
        else {
            lappend where [join $where_all { and }]
            }
        }

    set confirm [tk_dialog $lb.usage "Delete Confirmation"  \
 "Please confirm data deletion where:\n([join $where {), 
(}])" questhead 1  "Confirm Deletion" Cancel]
    if { $confirm == 0 } {
        set result ""
        set n [llength $ilist]
        for {set i [expr $n-1]} {$i >= 0} {incr i -1} {
            set w [lindex $where $i]
            set rc [catch {$conn "delete from $tablename where $w"} reply]
            if { $rc } {
                append result "$reply\n"
                }\
            else {
                set index [lindex $ilist $i]
                $lb delete $index $index 
                }
            }
        if { $result != "" } {
             dmh_show_text $result "Deletion ERROR Results"
            }
        }    

     }

   

proc odbc_table_insert {lb conn} {
   set table [lindex [odbc_tabwin_selection $lb] 0]
   if { $table == "" } return
   odbc_insert_dlg $table $conn
   }

proc odbc_insert_dlg {tablename conn} {
   if { [string first . $tablename] > 0 } {
       set table [lindex [split $tablename .] 1]
       }\
   else { set table $tablename }
   set reply [$conn schema $tablename]
   if { [lindex $reply 4] == 0 } {
       tk_dialog $lb.pop "Table Insert" "Schema query failed for table $tablename [lindex $reply 5]"\
 error 0 Dismiss
       return
       }
    
   set mode insert
   set title "Data Insert, Table $tablename"
   set prompt "Press Ok for each row entry."
   set win .${mode}_[join [split $tablename " .$"] _]
   # is the dialog already up ?
   if { [winfo exists $win] } return
   toplevel $win
   wm title $win $title
   wm iconname $win $mode\n$table
   message $win.msg -text $prompt -width 4i 
   pack $win.msg -side top -expand 1 -fill x
   # scan for max label width
   set lblmax 10
   set cols [string tolower [lindex $reply 2]]
   set cnames ""
   foreach row [lindex $reply 6] {
       catch { unset length }
       vset [string tolower $row] $cols
       if { ![info exists length] } {
           if { [info exists column_size] } {
               set length $column_size ;# IBM DB2 (and others?)
               }\
           else { set length 80 }
           }
       # have column_name type_name length]
       lappend cnames $column_name
       set len [string length $column_name]
       if { $len>$lblmax } { set lblmax $len }
       set width [expr $length+1]
       # width only sets the visual size, you can scroll and enter longer text
       if { $width > 80 } { set width 80 }
       frame $win.$column_name -bd 1m
       set width_clause "-width $width"
       entry $win.$column_name.e -relief sunken -width $width
       label $win.$column_name.l -text $column_name -anchor e -width $lblmax
       pack $win.$column_name.l -side left
       pack $win.$column_name.e -side left 
       pack $win.$column_name -side top -fill x
       }
    if { $lblmax > 10 } {
        foreach col $cnames {
            $win.$col.l config -width $lblmax
            }
        }
    frame $win.bot
    button $win.bot.ok -text Ok \
 -command [list ::dmh::odbc_tab_ins_ok $tablename $win $conn]
    button $win.bot.cancel -text Dismiss -command "destroy $win"
    pack $win.bot.ok -side left -expand 1 -fill x
    pack $win.bot.cancel -side right -expand 1 -fill x
    pack $win.bot -side top -fill x
    dmh_win_shrink $win
    }
    


#
# Ok from insert dialog
#
# we let the database code worry about
# improper data or too long data
#
proc odbc_tab_ins_ok {tablename win conn} {
   if { [string first . $tablename] > 0 } {
       set table [lindex [split $tablename .] 1]
       }\
   else { set table $tablename }
   set mode insert 

   set reply [$conn schema $tablename]
   set cols [string tolower [lindex $reply 2]]
   set datalist ""
   set collist ""
   foreach row [lindex $reply 6] {
       vset [string tolower $row] $cols
       # have column_name type_name length]

       set ischar 1
       foreach p {int float real deci num} {
           if { [string first $p $type_name] >= 0 } { 
               set ischar 0
               break
               }
           }
 

       set data [$win.$column_name.e get]

       # ignore empty fields on insert 
       if { $mode == "insert" && [string length $data] <= 0 } continue

       if { $ischar } {
           # character data
           # double imbedded single quotes
           regsub -all ' $data '' data
           # surround by quotes
           set data '$data'
           }
       lappend datalist $data
       lappend collist $column_name
       }
    if { $mode == "insert"} {
      if { [llength $datalist] } {
        set data ""
        foreach dat $datalist {
            append data "$dat,"
            }
        set datalist [string trimright $data , ]
        set collist  [join [split $collist] ","]
        set msg "insert into $tablename ($collist) values ($datalist)"
        set rc [catch {$conn $msg} reply]
        if { $rc == 0 } { 
            set bitmap info 
            if { $reply == "" } { set reply "Insertion completed." }
            }\
        else { set bitmap error }
        tk_dialog $win.ins$table "$table Insertion" "$msg\n\n$reply" $bitmap 0 Ok
        }\
      else {
        tk_dialog $win.ins$table "$table Insertion" "Insertion not performed.  No data was entered." error 0 Ok
        }
      } 
    }
        
} ;# namespace
