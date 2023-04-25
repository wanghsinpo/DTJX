
        Configurable GEM Equipment Interface Application
        ------------------------------------------------

 Features:

    Data driven framework uses SQL tables and minimal custom
      code.   No custom code needed for true GEM equipment.

    Supports HSMS, SECS-I, or SECS-I on TCP/IP Terminal Servers, 
      on Windows NT, or any POSIX system.

    Integrates into factory using DMH message system:
   
      Accepts all VFEI 2.1 commands in <name>_VFEI mailbox.
      Accepts SQL commands in <name>_SQL for remote data access.
      Accepts Tcl commands in <name>_RPC for remote inspect.
      Sends asynchronous VFEI messages to a configured mailbox.

    Easily integrates to databases, CORBA, etc, using
      datahub table subscriptions.

    SECS Variable, Event, and Item type discovery features 
      minimize your configuration effort.

    Comprehensive graphical user interface:

      Equipment Control & Characterization UI
      SECS Tracing and Diagnostic UI
      Database Table Management UI

    Accommodates custom coding to make older equipment
      look like GEM to the factory system
       
      Can add driver synthesized variables to the ei_variable table
      Can synthesize events from alarms or other inputs
      Simple scripting API for custom SECS messages and logic

    Can queue, save, and reload messages for the factory
      system when it is offline.

------------------------------------------------------------

Steps in Building an Equipment Interface

  *  You may wish to copy your existing *.tab files to a 
     backup directory if you have already built an interface.

     mkdir bak
     mv *.tab bak

  *  Start the supervisor application by typing its name on
     the command prompt or by using the NT Start menu.

     supervisor

     If you are connecting to a DMH message system server,
     you may wish to indicate a DMH message group on the
     command line, as in:

     datahub eof
     supervisor "set MB_GROUP mbx"

  *  Use the "New..." button to create an interface startup.
     You will need to specify the connection parameters.

  *  Use the "Start" button to start your interface running. 

     Now you will see a "Host Equipment Interface Window".
     The comments to follow refer to this window.

  *  Use the "Initialize" or "Data Refresh" buttons to 
     capture data items, and alarms.
  
  *  Press the "Enable All Events" and then work with the
     equipment and have it report the events you care about.

  *  Edit the ei_event table using the datahub GUI to indicate 
     the VFEInames of your events.  Be sure to save the table.

  *  Edit the ei_variable table to indicate the VFEInames of
     your variables.

  *  Edit the ei_variable table to specify your remote commands.

  *  Use the UI to create event reports.  Press the Save button.

  *  Enable/Disable alarms to your liking and press the Save 
     button.

  *  You probably want to leave in place the automatic initialization
     that occurs when first online.  The initialization creates 
     the reports that you have configured, and enables or disables
     alarms as you have configured them.

  *  Don't forget to save your startup configuration using the
     "Save Tables" button on the supervisor window.  You can
     configure your equipment interfaces to start when the
     supervisor program is started.

  You're done!   The default configuration is feeding your VFEI
  event report messages, alarm messages, and trace data, to
  mailbox "equipbox" in the DMH message group specified on the
  command line.  

===================================================================
Building non-GEM or Custom Interfaces

  You can support multiple pieces of equipment, of different types
  in one process.  Please review the HTML documentation on the
  GEM Supervisor Application.

  To install unique Tcl code, we suggest you create your own 
  directory or use the "custom" directory which is provided for 
  this purpose.  If you need to replace any of the 
  provided procedures because of non-GEM behavior or unique
  requirements, copy the whole file into your custom directory,
  and revise it.  Write any new Tcl procedures that you need,
  also in your custom directory.  Whenever you change the
  procedures in your directory, rebuild the tclIndex file by
  executing the command:

     dmh_wish -notk -tclargs "auto_mkindex . *.tcl" exit

  This will help the Tcl interpreter to find your custom
  code first, using the global variable auto_path which
  specifies the search order for loading new procedures.

