
#
# the wm transient command in Tk 8.3 for Windows NT
# can create hidden modal dialog windows if the parent
# is iconic or withdrawn - this is a workaround
#
namespace eval ::dmh {
proc dmh_transient {w parent} {
    set state [wm state $parent]
    if { $state != "withdrawn" && $state != "iconic" } {
        wm transient $w $parent
        }
    }
}
    
