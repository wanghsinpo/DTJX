# $Header: /usr/cvsroot/tcllib84/init.tcl,v 1.8 2005/04/05 12:29:37 hume Exp $
#
# $Log: init.tcl,v $
# Revision 1.8  2005/04/05 12:29:37  hume
# Workaround namespace import unexpectedly auto_loading all of ::dmh::*
#
# Revision 1.7  2005/03/22 20:17:42  hume
# Suse Linux 9.2 needed -size on font create of fixed.
#
# Revision 1.6  2003/09/12 16:06:48  hume
# For NT DDE send, call tk appname to register send name.
#
# Revision 1.5  2003/08/19 13:44:22  hume
# Changed Copyright year seen from console to 2003.
#
# Revision 1.4  2002/10/29 22:22:14  hume
# Implemented ::dmh::lset for DMH server's as a smart wrapper to have
# interoperability with pre-84 DMH clients.
#
#
# From previous version with changes for new ::dmh namespace and lset -> vset
#
#


# initialize and supervise dmh package loading

# establish and initialize the dmh namespace
namespace eval ::dmh {
   variable dmh_library [file dirname [info script]]
   variable dmh_version 1.2
   global argv0 auto_path env tcl_interactive tcl_platform tcl_version
   # add to the auto_path
   if { [lsearch -exact $auto_path $dmh_library] < 0 } {
       lappend auto_path $dmh_library
       }

     # initialize compiled commands and license status
     load [file join $dmh::dmh_library \
 [expr {$::tcl_platform(platform) == "unix" ? "lib" : ""}]dmh84[info sharedlibextension]]

   # make public commands available for export
   namespace export autoscale comm \
     dmh \
     dmh_ntp_install dmh_ntp_query dmh_ntp_status \
     dmh_stat_time \
     dp_atclose dp_atexit dp_close\
     dp_hostname dp_MakeRPCClient dp_MakeRPCServer dp_ProcessRPCCommand \
     dp_RDO dp_RPC dp_ShutdownRPC \
     dp_whenidle \
     ei_vartrace ei_vartrace_selection execute\
     gs_execute\
     hexdump hsms hsms_active_reconnect hsms_wait_online\
     hub_fieldtype hub_html_save hub_schema_html_data\
     hub_schema_select hub_select_html_data \
     hub_select_to_csv hub_select_to_html hub_select_to_xml hub_subs_close_all hub_table_count \
     hub_table_csv hub_table_exists hub_table_list hub_table_schema_list\
     hub_table_sub_list hub_tables hub_tables_load_all hub_tables_save_all \
     hub_templates hub_xml_sanitize\
     info_data info_var interval_txt \
     ldelete ltrunc localtime \
     mbx mbx_do_xact mbx_RPC mbx_SQL mbx_timed_get mbx_xact_pat \
     mean mh_anyclientunreceive mh_client_id mh_client_kill \
     mh_clientcheck mh_clientunreceive \
     mh_eval mh_name_to_socket mh_ping_client \
     mh_server_status mh_sw_box_view_data mh_tracemsg \
     mktime \
     rand randnormal range rset \
     secs_to_TSN secsport secs_S2F18 \
     secs_Vx_to_TSN \
     secsport_S9_reply secsport_whenmsg_init\
     SQL stddev substr \
     TSN_to_secs TSN_to_secs_Vx udp vfei_2_array vset wait

     if { [package provide Tk] ne "" } {
         namespace export comm_tracewin dmh_cmd_win dmh_gets dmh_listpick dmh_show_text dmh_sublist \
      dmh_transient dmh_win_shrink \
      fileselect hub_gui_html\
      mh_statuswin mh_tracewin_append \
      odbc_table_win odbc_tabwin odbc_tabwin_refresh \
      secs_replaywin secsport_tracewin
         }

     if { $tcl_platform(platform) == "windows" } { 
         namespace export dde_execute dmh_dde send odbc regset
         }

     # already global: dmh_import dmh_var exec itcl_mkindex tkerror tkerror.tk

     # now do late initialization
     if { $tcl_platform(platform) == "macintosh" } {
         if { ![info exists env(DISPLAY)] } {
            set env(DISPLAY) [::dmh::dp_hostname]:0.0
            }
        # look for hub script etc where dmh program was started
        if { ![info exists env(DMH_BIN)] } {
            set env(DMH_BIN) [pwd]
            }
        # check for 1st time use
        if { [info exist ::dmh::dmh_tmp_license] } {
             after 1 ::dmh::dmh_license
             return
             }
        # on the mac there is no command line support
        # therefore if there is a file "autoexec.tcl" in the pwd
        # execute it after we return from initialization
        if { [file exists autoexec.tcl] } {
            after 1 [list source autoexec.tcl]
            }
        } ;# macintosh
    
    if { $tcl_platform(platform) == "windows" } {
        # offer a unique service name for dde and dde based send
        if { [info exists argv0] } {
            set basename [file rootname [file tail $argv0]]
           }\
        else {
            # imbedded usage - no argv0 ! (service will be executable name)
            set basename {}
            }
        set service_name $basename
        set list ""
        set i 1
        set changed 0
        while {1} {
            dmh_dde init $service_name
            # dde query will block unless all DDE parties are responsive
            # the call is avoided if NO_DDE_QUERY is in the environment
            if { [info exists env(NO_DDE_QUERY)] || $basename == "" } break 
            set list [dmh_dde query]
            set changed 0
            while { [lsearch -exact $list [list $service_name tcl74]] >= 0 } {
                incr i
                set service_name "$basename #$i"
                set changed 1
                }
            if { !$changed } break
            dmh_dde end
            }
        catch { source [file join $dmh_library dmh_dde.tcl] } result
        # we can be inspected by older versions of dmh_inspect if dde_execute and 
        # mh_eval are global commands, we can execute dmh_inspect if send is defined.
        if { ![info exists env(NO_DDE_IMPORT)] } {
            uplevel #0 namespace import -force ::dmh::dde_execute ::dmh::mh_eval ::dmh::send
            }
        if { [info commands console] == "console" } {
            console title $service_name
            # want Motif style paste with middle mouse button
            # the console has its own interpreter 
            # source code review shows existence of "console eval" connand
            # assume Tk 8.4+
            package require Tk 8.4
            tk appname $service_name
            console eval {bind .console <ButtonRelease-2> {
                catch {::tk::ConsoleInsert %W [selection get -displayof %W]}
                break
                } }
            # but you may not have a three button mouse, so we also bind to
            # the right button - button 3 - like Quick-Edit on NT
            console eval {bind .console <ButtonRelease-3> {
                catch {::tk::ConsoleInsert %W [selection get -displayof %W]}
                break
                } }
            # redundant clear screen
            console eval {.menubar.edit add separator}
            console eval {.menubar.edit add command -label "Clear" -underline 1 \
     -command {.console delete 0.0 end ; ::tk::ConsolePrompt}}
            # update the About
            console eval [list proc ::tk::ConsoleAbout {} {
                global tk_patchLevel 
                tk_messageBox -type ok -title "About Tcl/Tk/DMH" -message "Tcl for Windows

Datahub Solution Development Kit
Copyright \251 2005 Hume Integration Software

Tcl [info patchlevel]
Tk $tk_patchLevel
DMH 1.2"
}]
            # add help menu items
            console eval {.menubar.help insert 0 command -label {puts $errorInfo}\
  -command {consoleinterp record {puts $errorInfo}}}
            console eval {.menubar.help insert 1 command -label {HTML documentation}\
  -command {consoleinterp eval {exec cmd.exe /c [file join $env(DMH_BIN) .. html84 index.html] &}}}
            }
        unset i basename service_name list changed
        # create fixed font alias for compatibility
        catch { font create fixed -family Fixedsys -size 9 -slant roman -weight medium}
        } \
    else {
        #  unix
        catch { font create fixed -family fixed -size 10 -slant roman -weight medium}
        # we can be inspected by older versions of dmh_inspect if 
        # mh_eval is a global command
        if { ![info exists env(NO_DDE_IMPORT)] } {
            uplevel #0 namespace import -force ::dmh::mh_eval
            }
        }

    } ;# namespace
