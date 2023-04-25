
namespace eval ::dmh {

# map a groupname to a socket number
# changing to a better hash fn would break compatibility
proc mh_name_to_socket port {
    set sum 0
    set len [string length $port]
    for {set i 0} {$i < $len} {incr i} {
        set ch [string index $port $i]
        scan $ch %c ich
        set sum [expr {$sum+$ich}]
        }
    return [expr {5001 + ($sum % 27000)} ]
    }

}
