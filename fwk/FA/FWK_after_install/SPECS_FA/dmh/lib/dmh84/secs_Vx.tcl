# $Header: /usr/cvsroot/tcllib84/secs_Vx.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2001 Hume Integration Software
# All Rights Reserved
#
# $Log: secs_Vx.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.3  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.2  2001/10/22 19:52:30  hume
# Switch choices needed to be based on hex encoding.
#
# Revision 1.1  2001/10/22 15:56:07  hume
# Added support for SECS variant data items.
#
#
namespace eval ::dmh {

# SECS-II Item type Octal "022" - customizable logic to permit
#      user defined types.
#    Octal 22 when used with 1 length byte is 0x49 or 73

# Some Unicode test characters
# \u00a9 is a copyright mark 
# \u00a3 is English pound currency symbol
# \u00c9 is uppercase E with acute accent
# \u00e7 is c with cedilla as in francais
# \u00e9 is lowercase e with acute accent as in Cafe, as utf-8 it is c3 a9
#     


############################ secs_Vx_to_TSN #####################
############################ secs_Vx_to_TSN #####################
############################ secs_Vx_to_TSN #####################
#
# map SECS variant data into the UTF-8 representation used by
#  the Tcl progamming environment
#
# input string "V[:<size>] b1 b2 [bi]*"
#    b1 b2 ... bsize are the item data including the two type bytes
# If <size> appears it should be equal to the count of bytes, b.
# There should always be two bytes providing the encoding type.
#
# Output string  "V<x>[:<size>] <utf8_string>"
# Data is always represented in Tcl as utf-8.  It gets translated 
# when displayed as GUI text.  
# V<x>  - <x> := uppercase hex codes from the first 2 item data bytes
#       with leading zeroes removed (V1, V2, ..., VFFFF)
# V1 := unicode, V2 := utf-8, V3 = 7 bit ASCII, ...
#
# test cases
# Unicode hello  
# secs_Vx_to_TSN {V:12 0 1 0 104 0 101 0 108 0 108 0 111} -> V1:12 hello
# utf-8 hello
# secs_Vx_to_TSN {V:7 0 2 104 101 108 108 111}  -> V2:7 hello
# ascii hello
# secs_Vx_to_TSN {V 0 2 104 101 108 108 111}  -> V2 hello
#
proc secs_Vx_to_TSN {vcodes} {
    global tcl_platform
    set V [lindex $vcodes 0]
    if { [string first : $V] > 0 } { 
        set size [lindex [split $V :] 1]
        set wantsize 1 
        }\
    else { set wantsize 0 }
    set b1 [lindex $vcodes 1]
    set b2 [lindex $vcodes 2]
    set data [lreplace $vcodes 0 2]
    set x [expr (($b1 & 255)<<8) + ($b2 & 255)]
    set Vx V[format %X $x]
    if { $wantsize } { set Vout ${Vx}:$size }\
    else { set Vout $Vx }
    # build a "string" representation that "encoding convertfrom" can use
    set text {}
    foreach b $data { append text [format %c $b] }
    switch $Vx {
       V0 {error "Variant encoding type 0 is not proper" }
       V1 { ;# Unicode, assume network-byte-ordering == bigendian
           if { $tcl_platform(byteOrder) != "bigEndian" } {
               # network order is bigEndian
               # Tcl converts to/from platform order
               set unitext {}
               set imax [string length $text]
               set j 1
               for {set i 0} {$i < $imax} {incr i 2} {
                   append unitext [string index $text $j] [string index $text $i]
                    incr j 2
                    }
               }\
            else { set unitext $text }
            set text [encoding convertfrom unicode $unitext] 
            }
        V2 { set text [encoding convertfrom utf-8 $text] }
        V3 { set text [encoding convertfrom ascii $text] ;# unmapped chars become '?'}
        V4 { set text [encoding convertfrom iso8859-1 $text] }
        V5 { set text [encoding convertfrom iso8859-11 $text] ;# error encoding not found }
        V6 { set text [encoding convertfrom tis-620 $text] ;# error encoding not found }
        V7 { set text [encoding convertfrom is-13194 $text] ;# error encoding not found }
        V8 { set text [encoding convertfrom shiftjis $text] }
        V9 { set text [encoding convertfrom euc-jp $text] }
        VA { set text [encoding convertfrom euc-kr $text] }
        VB { set text [encoding convertfrom gb1988 $text] }
        VC { set text [encoding convertfrom euc-cn $text] }
        VD { set text [encoding convertfrom big5 $text] }
        VE { set text [encoding convertfrom euc-tw $text] ;# error encoding not found }
     
      default { ;# show as V <list of bytes>
          return $vcodes
          }
      }
    return [list $Vout $text]
    }

############################# TSN_to_secs_Vx ####################
############################# TSN_to_secs_Vx ####################
############################# TSN_to_secs_Vx ####################
#
# return a list of integer codes for a SECS variant data item
#
# Input Cases:
#  V<x>[:<size>] <utf8_string>   ;# <x> specifies the encoding type
#  V[:<size>] <b1> <b2> [<bn>]*  ;# already expressed as a byte stream
#
# Standard Unicode goes over the wire as big endian.  
#
#  V1 "hello" ==   73 12 0 1 0 104 0 101 0 108 0 108 0 111
#  V2 "hello" ==  73 7 0 2 104 101 108 108 111
#  V3 "hello" ==  73 7 0 3 104 101 108 108 111
#
#  cafe, the e is \u00e9,  e with an acute accent
#  V1 "cafe\u00e9" == 73 10 0 1 0 99 0 97 0 102 0 233
#  V2 "cafe\u00e9" == 73 7 0 2 99 97 102 195 169
#  V3 "cafe\u00e9" == 73 6 0 3 99 97 102 63  ;# '?' is substituted
#
proc TSN_to_secs_Vx TSN {
    global tcl_platform
    set maxsize 16777215
    set Vx [set V [string toupper [lindex $TSN 0]]]
    if { [string first : $V] > 0 } {
        foreach {Vx maxsize} [split $V :] {}
        }
    if { $Vx == "V" } { ;#  direct input of "V b1 b2 ... bN" is accepted 
        set icodes [lreplace $TSN 0 0]
        }\
    else {
        set ct [scan $Vx V%x type_code]
        if { $ct != 1 } { error "Cannot determine variant item encoding" }
        set llen [llength $TSN]
        set icodes {}
        lappend icodes [expr {($type_code >> 8) & 255}]
        lappend icodes [expr {$type_code & 255}]

        # assume a single UTF-8 string argument which is converted to
        # the target encoding, no argument is accepted as an empty string
        if { $llen == 1} { set text {}}\
        elseif { $llen == 2} { set text [lindex $TSN 1] }\
        else { error "optional $Vx variant data should be a single list element" }
        set text [lindex $TSN 1]
        # prepare $text as a byte string for the variant data 
        switch $Vx {
            V0 {error "Variant encoding type 0 is not proper" }
            V1 { 
                set unitext [encoding convertto unicode $text] 
                if { $tcl_platform(byteOrder) != "bigEndian" } {
                    # network order is bigEndian
                    # Tcl converts to platform order
                    set imax [string length $unitext]
                    set text {}
                    set j 1
                    for {set i 0} {$i < $imax} {incr i 2} {
                        append text [string index $unitext $j] [string index $unitext $i]
                        incr j 2
                        }
                    }\
                else { set text $unitext }
                }
            V2 { set text [encoding convertto utf-8 $text] }
            V3 { set text [encoding convertto ascii $text] ;# unmapped chars become '?'}
            V4 { set text [encoding convertto iso8859-1 $text] }
            V5 { set text [encoding convertto iso8859-11 $text] ;# error encoding not found }
            V6 { set text [encoding convertto tis-620 $text] ;# error encoding not found }
            V7 { set text [encoding convertto is-13194 $text] ;# error encoding not found }
            V8 { set text [encoding convertto shiftjis $text] }
            V9 { set text [encoding convertto euc-jp $text] }
            VA { set text [encoding convertto euc-kr $text] }
            VB { set text [encoding convertto gb1988 $text] }
            VC { set text [encoding convertto euc-cn $text] }
            VD { set text [encoding convertto big5 $text] }
            VE { set text [encoding convertto euc-tw $text] ;# error encoding not found }
            default { 
                }
           }
        #
        # Once you have called encoding convertto the resulting string is properly
        # setup to iterate using string index.  The data is an intermediate
        # representation and not the binary sequence in the desired codeset.
        # 
        set imax [string length $text]   ;# do not use string bytelength!!!!
        for {set i 0} {$i < $imax} {incr i} {
            set ch [string index $text $i]
            scan $ch %c ich
            lappend icodes $ich ;# lappend icodes [format 0x%02x $ich]
            }
        }

    set ct [llength $icodes]
    if { $ct > $maxsize } { 
        error "Specified optional size is too small for actual variant data" 
        }\
    elseif { $ct < 2 } {
        error "Missing variant encoding type bytes"
        }
    set result {}
    set h0 73   
    if { $ct <= 255 } { 
        lappend result $h0
        lappend result $ct
        }\
    elseif { $ct <= 0xffff } {
        incr h0
        lappend result $h0
        lappend result [expr {($ct >> 8) & 255}]
        lappend result [expr {$ct & 255}]
        }\
    else {
        incr h0 2
        lappend result $h0
        lappend result [expr {($ct >> 16) & 255}]
        lappend result [expr {($ct >> 8) & 255}]
        lappend result [expr {$ct & 255}]
        }
    return [concat $result $icodes]
    }   

} ;# namespace
