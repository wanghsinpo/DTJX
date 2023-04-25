# $Header: /usr/cvsroot/tcllib84/mbx_SQL.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# $Log: mbx_SQL.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
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
# Revision 1.1  1998/11/13 14:23:36  hume
# New procedure suggested by Clift Richardson.
#
namespace eval ::dmh {

# Here is a procedure, which can be used to
# process SQL commands received in a mailbox.
#
# mbx_SQL is similar to mbx_RPC - serving SQL through a DMH mailbox becomes a one-liner:
#   mbx whenmsg <boxname> mbx_SQL
#
# Usually the developer chooses a boxname that ends in "_SQL" to indicate its usage.
#
proc mbx_SQL {} {
    variable mbxdest 
    variable mbxmsg 
    variable mbxreply
    mbx whenmsg again
    gs_execute $mbxdest $mbxmsg $mbxreply
    }
} ;# namespace
    
