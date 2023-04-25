# $Header: /usr/cvsroot/tcllib84/itcl_mkindex.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# $Log: itcl_mkindex.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
#
#
# GLOBAL NAMESPACE
#
# thank you Christian Krone, SQL Datenbanksysteme GmbH
# christian.krone@NO-SPAM.softwareag.com
# for this itcl indexing fix
#
proc itcl_mkindex {dir args} {
    package require Itcl
    set found 0
    foreach hook $auto_mkindex_parser::initCommands {
        switch -- [lindex $hook 1] {
           class { set found 1 ; break }
           itcl::class {
              eval auto_mkindex_parser::command class [lrange $hook 2 end]
              set found 1 ; break
              }
           }
        }
    if { !$found } { error "class not defined in auto.tcl" }
    eval auto_mkindex $dir $args
    }

