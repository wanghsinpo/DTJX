# $Header: /usr/cvsroot/gem/lib/vset.tcl,v 1.1 2002/11/04 20:25:33 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2002 Hume Integration Software
# All Rights Reserved
#
# $Log: vset.tcl,v $
# Revision 1.1  2002/11/04 20:25:33  hume
# Added to gem/lib so updated gem files can be used with older DMH83 files.
#
#
#

#
#  Tcl 8.4+ has a new core command "lset"
#  The Hume "lset" command is being migrated to "vset" so you can
#  use the new core command along with the Hume command.
#
# If your interpreter loads this file, it is because you do not
# have "vset" built-in.  You must be running Tcl 8.3 or earlier.
# Therefore you do have the original Hume lset command.
#
# This definition is here to fool the indexing logic:
proc vset {data names} { return [lset $data $names] }

# better performance is obtained using alias
rename vset {}
interp alias {} vset {} lset
