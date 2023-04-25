# $Header: /usr/cvsroot/tcllib84/hub_html.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# Procedures to write Hub data or schema as HTML or XML
#
# Licensed and Supported Software
# (C)Copyright 2001 Hume Integration Software
# All Rights Reserved
#
# $Log: hub_html.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.2  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.1  2001/10/20 19:28:30  hume
# Added HTML and XML output of SQL table data and schema data.
#
#

package require dmh
namespace eval ::dmh {

############################# hub_html_save ##########################
############################# hub_html_save ##########################
############################# hub_html_save ##########################
#
#
# Write SQL data and/or schema as 1 or many documents.
# The contents option includes a title, and contents with hyperlinks.
# The schema option will only work for HUB tables.
#
proc hub_html_save {{one_doc 1} {data 1} {schema 1} {contents 1}\
 {schema_description 0} {tablelist *} {pathname_or_dir {}}} {
    if { $pathname_or_dir == {}} {
        if { $one_doc } {
            set dir [pwd]
            set filename snapshot[localtime 5]_[localtime 3].html
            set pathname [file join $dir $filename]
            }\
        else {
            set dir [pwd]
            }
        }\
    else {
        if { $one_doc } { set pathname $pathname_or_dir }\
        else { set dir $pathname_or_dir }
        }
    if { $tablelist == "*" } { set tablelist [hub_tables] }
    if { $contents } { set targets 1 }\
    else { set targets 0 }
    set pathnames {}
    if { $one_doc } {
        set title "HUB Snapshot At [localtime 9]"
        lappend pathnames $pathname
        set fid [open $pathname w]
        puts $fid "<html><head><title>$title</title></head>
 <body>"
        puts $fid "<H1>$title</H1>"
        if { $contents } {
            puts $fid "<H2>Table of Contents</H2>\n<DIR>"
            foreach table $tablelist {
                puts -nonewline $fid "<p><b>Table $table</b> &nbsp;"
                if { $schema } {
                    puts -nonewline $fid "<A href=\"#$table Schema\">Schema</A> &nbsp;"
                    }
                if { $data } {
                    puts -nonewline $fid "<A href=\"#$table\">Data</A>"
                    }
                puts $fid "</b></p>"
                }
            puts $fid "</DIR>\n<HR>"
            set contents 0
            }
        }
    foreach table $tablelist {
        if { !$one_doc } {
            set filename ${table}.html
            set pathname [file join $dir $filename]
            lappend pathnames $pathname
            set fid [open $pathname w]
            set title "Table $table At [localtime 9]"
            puts $fid "<html><head><title>$title</title></head>
 <body>"
            puts $fid "<H1>$title</H1>"
            }
        if { $contents } {
            puts $fid "<H2>Table of Contents</H2>\n<DIR>"
                puts -nonewline $fid "<p><b>Table $table</b> &nbsp;"
                if { $schema } {
                    puts -nonewline $fid "<A href=\"#$table Schema\">Schema</A> &nbsp;"
                    }
                if { $data } {
                    puts -nonewline $fid "<A href=\"#$table\">Data</A>"
                    }
                puts $fid "</b></p>"
            puts $fid "</DIR>\n<HR>" 
            }
        puts $fid "<HR><h2>Table $table</h2>"
        if { $schema } {
            if { $targets } { puts $fid "<A NAME=\"$table Schema\">&nbsp;</A>" }
            puts $fid "<h3>Table $table Schema</h3>"
            hub_schema_html_data $table $schema_description $fid
            }
        if { $data } {
            if { $targets } { puts $fid "<A NAME=\"$table\">&nbsp;</A>" }
            puts $fid "<h3>Table $table Data</h3>"
            hub_select_html_data $table $fid
            }
        puts $fid "<p></p>"
        if { !$one_doc } { 
            puts $fid "</body></html>"
            close $fid 
            }
        }
    if { $one_doc } { 
        puts $fid "</body></html>"
        close $fid 
        }
    return [list $pathnames [llength $tablelist]]
    }

############################# hub_schema_select ######################
############################# hub_schema_select ######################
############################# hub_schema_select ######################
#
# Provide the schema of a table as if it is a selection result,
# but we are including spaces and mixed case which you would not get
# from an ordinary table selection.
# Set Description argument to 1 to obtain a blank Description column
# which may be desired for creating HTML documention.
#
proc hub_schema_select {table {Description 0}} {
    set tablename "${table} Schema"
    set cols {{Column Name} Key Type}
    if { $Description } { lappend cols Description }
    set keys {{Column Name}}
    set rows {}
    set ct 0
    foreach row [hub_table_schema_list $table] {
        vset $row {col type key} 
        if { $Description } {
            lappend rows [list $col $key $type {}]
            }\
        else {
            lappend rows [list $col $key $type]
            }
        incr ct
        }
    return [list select $tablename $cols $keys $ct {} $rows]
    }

############################# hub_schema_html_data ###################
############################# hub_schema_html_data ###################
############################# hub_schema_html_data ###################
# 
# Obtain the schema of a HUB table as a selection result.
# Convert the data to HTML.
# If passed the handle to an open file, write to the file
# else return the HTML data as the result.
# Set Description argument to 1 to obtain a blank Description column
# which may be desired for creating HTML documention.  
#
proc hub_schema_html_data {table {Description 0} {fid {}}} {
    set reply [hub_schema_select $table $Description]
    if { $Description } { set empty_string &nbsp; }\
    else { set empty_string {}}
    set html [hub_select_to_html $reply $empty_string]
    if { $fid != {}} {
        puts $fid $html
        return {}
        }
    return $html
    }

############################# hub_select_html_data ###################
############################# hub_select_html_data ###################
############################# hub_select_html_data ###################
#
# Select data from a table. (Either the HUB or SQLsrv)
# Convert the data to HTML.
# If passed the handle to an open file, write to the file
# else return the HTML data as the result.
#
proc hub_select_html_data {table {fid {}} {cols *} {where {}}} {
    set reply [SQL "select [join $cols ,] from $table $where"]
    # ODBC does not return the tablename like the hub does
    set reply [lreplace $reply 1 1 $table]
    set html [hub_select_to_html $reply]
    if { $fid != {} } {
        puts $fid $html
        return {}
        }
    return $html
    }

############################# hub_select_to_html #####################
############################# hub_select_to_html #####################
############################# hub_select_to_html #####################
#
# Convert a Hub or ODBC selection result to HTML.
# The HTML result is also proper XML.
# This format uses the table rendering tags of HTML and displays
# properly in a browser.
#
# You may want to set the empty_string argument to &nbsp; to have
# empty table cells displayed as recessed.
#
proc hub_select_to_html {selection {empty_string {}}} {
    vset $selection {notice table cols keys count err rows types} 
    set rows [hub_xml_sanitize $rows]
    append html "<table id=\"$table\" border=\"1\"><tr> "
    foreach col $cols {
        append html <th>$col</th>
        }
    append html </tr>\n
    foreach row $rows {
        append html <tr>
        foreach item $row {
            if { [string compare $item {}] } { append html <td>${item}</td> }\
            else { append html <td>${empty_string}</td> }
            }
        append html </tr>\n
        }
    append html </table>
    return $html
    }

############################# hub_select_to_xml ######################
############################# hub_select_to_xml ######################
############################# hub_select_to_xml ######################
#
# Convert a Tcl Reply Format result to XML.
# The input format is from a selection, or a subscription notification.
# The tags make no sense to a browser, so this format is intended for
# XML parsing software.
#
proc hub_select_to_xml {reply {header 1}} {
    vset $reply {notice table cols keys count err rows types}
    set rows [hub_xml_sanitize $rows]
    if { $header } {
        append result {<?xml version="1.0" encoding="UTF-8"?>} \n
        }
    append result "<selection>
 <notification>$notice</notification>
 <tablename>$table</tablename>
 <columns>
   <column>[join $cols {</column><column>}]</column></columns>
 <keys>
   <key>[join $keys {</key><key>}]</key></keys>
 <count>$count</count>
 <errorInfo>$err</errorInfo>
 <rows>\n"
    foreach row $rows {
        append result "  <row>"
        set i 0
        foreach col $cols {
            append result "<$col>[lindex $row $i]</$col>"
            incr i
            }
        append result </row>\n
        }
    append result " </rows>\n"
    # odbc selection includes type data
    if { [llength $types] > 0 } {
        append result " <types>
   <type>[join $types {</type><type>}]</type></types>\n"
        }
    append result "</selection>"
    return $result
    }

############################# hub_xml_sanitize #######################
############################# hub_xml_sanitize #######################
############################# hub_xml_sanitize #######################
# substitute for characters that are not supposed to be found in proper
# HTML/XML data.
# You have to substitute for & first, or you ruin the other 
# substitutions.
proc hub_xml_sanitize reply {
    foreach {symbol subst} {& {\&amp;} < {\&lt;} > {\&gt;} \" {\&quot;}} {
        regsub -all $symbol $reply $subst reply
        }
    return $reply
    }

} ;# namespace
