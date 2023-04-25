# $Header: /usr/cvsroot/tcllib84/hub_templates.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# (C) Copyright Hume Integration Software, 2001
# All Rights Reserved
# Licensed Materials - Property of Hume Integration Software
#
# $Log: hub_templates.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.2  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.1  2001/05/25 22:41:12  hume
# Backup restoration.
#
# Revision 1.2  2001/04/16 21:55:46  hume
# Tweaked insert format.
#
# Revision 1.1  2001/04/05 12:44:23  hume
# Added hub_templates procedure.
#
# 
namespace eval ::dmh {

proc hub_templates {table {format tcl}} {
    set schemalist [hub_table_schema_list $table]
    # col datatype keynum
    set colnames {}
    set coltypes {}
    set values {}
    set create "create table $table ("
    set insert "insert into $table ("
    set update "update $table set"
    set wherelist {}
    foreach row $schemalist {
         vset $row "colname datatype key"
         lappend colnames $colname
         if { [string first varchar $datatype] >= 0 } { set value '\$$colname' }\
         else {set value \$$colname }
         if { $key != {} } {
            set keys($key) $colname
            lappend wherelist $colname=$value
            }\
         else {
            append update " $colname=$value,"
            }
         append create "$colname $datatype,"
         append insert " $colname,"
         lappend values $value 
         }
 
   set insert "[string trimright $insert ,]) values ([join $values {, }])"
   
   if { [info exists keys(1)] } {
       append create "primary key($keys(1),"
       for {set i 2} {$i > 0} {incr i} {
           if { [info exists keys($i)] } {
               append create [set keys($i)],
               }\
           else break
           }
       set create [string trimright $create ,]
       append create ))
       }\
   else { set create [string trimright $create ,]) }
   if { $wherelist != {}} { set whereclause "where [join $wherelist { and }]" }\
   else { 
       set firstcol [lindex $colnames 0]
       set whereclause "where $firstcol ='\$$firstcol'"
       }
   set delete "delete from $table $whereclause" 
   set update "[string trimright $update ,] $whereclause" 
   set select "select * from $table $whereclause"
   if { $format == "tcl" } {
       foreach var {create insert update delete select} { set $var "SQL \"[set $var]\"" }
       set colnames "set cols {$colnames}"
       set select "set reply \[$select]\n\
set cols \[lindex \$reply 2\]\n\
foreach row \[lindex \$reply 6\] {\n\
    \tvset \$row \$cols\n\
    \t# now each field is a local variable\n\
    \t}\n"
    
       return [list $create $insert $update $delete $select $colnames]
       }
   return [list $create $insert $update $delete $select]
   }
    # dmh_show_text \n[join [hub_templates $table sql] \n\n]\n\n "SQL Statement Templates"
    # dmh_show_text \n[join [hub_templates $table tcl] \n\n]\n\n "Tcl Statement Templates"
         
} ;# namespace
