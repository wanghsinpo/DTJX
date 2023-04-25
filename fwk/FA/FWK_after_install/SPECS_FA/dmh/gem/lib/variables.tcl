# $Header: /usr/cvsroot/gem/lib/variables.tcl,v 1.4 2004/11/05 17:24:02 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: variables.tcl,v $
# Revision 1.4  2004/11/05 17:24:02  hume
# Max variable name length changed from 32 to 256.
#
# Revision 1.3  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  1999/01/22 16:42:18  hume
# Bumped varvalue size to 20,000 to allow larger data items.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
#
#


# table ei_variable
# Configuration and value table for equipment interface "variables"
#
# Your additions to this table will sort nicely in table displays
# if you number your varIDs to be: 
#       1000-1999    - listed first
#    or 9000-9999    - listed last
#
# columns-
#       spname: name of the secsport/hsms connection
#        varID: the SVID, ECID, or DVNAME 
#      varname: the SVNAME, ECNAME, or DVNAME 
#     VFEIname: the name used by VFEI 2.2
#        units: default of "" means pure number without units
#               ref E5-9
#        ECMIN: minimun value if class is ECV
#        ECMAX: maximum value if class is ECV
#        ECDEF: default value if class is ECV
#  description: usage/documentation notes
#     varclass: SV | ECV | DVVAL | SECS_DRVR | VFEI_DRVR
#            SV = Status Variable, always has valid value
#            ECV = Equipment Constant Variable, host can set value
#            DVVAL = Data Value Variable
#            SECS_DRVR = synthesized by the host interface driver logic
#            VFEI_DRVR = synthesized by the VFEI host interface logic
#    value_TSN: TSN format type code for the variable value used by equipment 
#               A VFEI_DRVR value can be VFEI_NTV which indicates that the
#               value is one or more name/type=value items.
#       ID_TSN: TSN format type code for the varID used by the equipment (usually U4)
#    varmethod: Tcl code to compute the current value
#     varvalue: possibly, the current value
#               host usage - the latest value received
#     t_latest: host usage - the YYYYMMDDhhmmsscc timestamp of $value 
#    VFEI_type: host usage - TSN format for the VFEI value representation
# host_managed: host usage - whether to set ECV value on initialize
#  host_setval: host usage - ECV value to set on initialize

proc ei_var_create {spname} {
    global $spname
    #
    if { [set ${spname}(EQUIP)] } {

        SQL "create table ei_variable (\
 spname varchar(32),\
 varID varchar(32),\
 ID_TSN varchar(8), \
 varname varchar(256),\
 description varchar(200), \
 varclass varchar(10),\
 value_TSN varchar(8), \
 varmethod varchar(2000), \
 varvalue varchar(20000), \
 t_latest varchar(16), \
 units varchar(10),\
 ECMIN varchar(32), ECMAX varchar(32), ECDEF varchar(32),\
 primary key(spname,varID))"

        } else { ;# HOST

        SQL "create table ei_variable (\
 spname varchar(32),\
 varID varchar(32),\
 ID_TSN varchar(8), \
 varname varchar(256),\
 VFEIname varchar(256), \
 description varchar(200), \
 varclass varchar(10),\
 value_TSN varchar(8), \
 varmethod varchar(2000), \
 varvalue varchar(20000), \
 host_setval varchar(200),\
 host_managed int, \
 t_latest varchar(16), \
 units varchar(10),\
 ECMIN varchar(32), ECMAX varchar(32), ECDEF varchar(32),\
 primary key(spname,varID))"
        }
    }
