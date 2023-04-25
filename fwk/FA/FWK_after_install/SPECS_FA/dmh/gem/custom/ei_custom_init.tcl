# $Header: /usr/cvsroot/gem/custom/ei_custom_init.tcl,v 1.3 1999/01/22 19:21:14 hume Exp $
#
# Here is an example of a custom procedure that gets executed
# at the end of the initialization procedure (see ../host/initialize.tcl)
#
# $Log: ei_custom_init.tcl,v $
# Revision 1.3  1999/01/22 19:21:14  hume
# Added provision to correct initial ui.
#
# Revision 1.2  1999/01/20 17:51:34  hume
# Custom varmethod can be used with ANY varclass - changed ProcessState
# text mapping customization to keep ProcessState as variable SV.
#
# Revision 1.1  1999/01/19 16:56:22  hume
# Added example code to map gemsim state numbers to text.
#


#
# We'll install a procedure for the gemsim equipment that will map the
# ProcessState and PreviousProcessState integer values to meaningful
# string values.  You can also install logic like this by manually
# updating the table, and saving the revised data.
# 
# A non-zero return value from ei_custom_init gets reported as an initialization error.
#
proc ei_custom_init {spname} {
    # at this point the ProcessState and PreviousProcessState
    # records are in the ei_variable table
    # change the records only if they match what we expect for
    # the gemsim equipment
    set reply [SQL "update ei_variable set \
 varmethod='gemsim_custom_process_state \$varvalue', value_TSN='A' where \
 spname='$spname' and\
 (varID=800 and varname='PreviousProcessState') or \
 (varID=810 and varname='ProcessState')"]
    if { [string first "//c 0" $reply] >= 0 } {
        # the varmethod update worked
        # This change is not seen if the host_ui is sitting there 
        # showing the state number and no update to ProcessState occurs.
        # So lets explicitly fix that situation
        global $spname
        if { [info exists ${spname}(proc_state)] } {
            set ${spname}(proc_state) [gemsim_custom_process_state [set ${spname}(proc_state)]]
            }
        }
    return 0	;# 0 means no error
    }

# here is our procedure to map state values to text values
# for the gemsim interface.
# if the value is already text, it should not be changed
proc gemsim_custom_process_state {statenum} {
    switch -exact $statenum {
       64 { return INIT }
       65 { return IDLE }
       66 { return SETUP }  
       67 { return EXECUTING }
       68 { return PAUSED }
       default { }
       }
    return $statenum 
    }
