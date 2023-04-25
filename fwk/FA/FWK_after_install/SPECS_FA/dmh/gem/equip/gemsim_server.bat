goto EndOfComments

$Header: /usr/cvsroot/gem/equip/gemsim_server.bat,v 1.2 2000/08/24 13:29:30 hume Exp $

An example of using the GEM Equipment Interface as a background process, 
and have it also act as a DMH message system server. The "GEMSIM"
process listens for command messages, performs the commands, and 
sends reply messages to the message system client(s).  In a simple
deployment there may be one client that is both the GUI and
controller.  In more complex deployments, there may be one or
more GUI clients, and a separate equipment controller client.

                    DMH
   [ GUI(s) ] <-----------------> ["GEMSIM Demon"   ]   SECS
        |              DMH        [  GEM Interface  ] <---------->  [HOST]
   [ Controller ] <-------------> [  DMH Server     ] (HSMS/RS232)
        |                       
   [ Equipment ]

                  Typical Deployment


The GUI and Controller can use the DMH message system to 
communicate as well.  There is often an existing interprocess
communication mechanism already in use by the equipment manufacturer.

Your client program can exec this bat file in background, wait a few seconds,
and connect to the DMH group "EQUIP".  Then, messages can be exchanged as
required using DMH commands.  When shutting down, send the "exit" command to 
the gemsim_SQL or gemsim_RPC mailbox.

An alternative is to keep this process running, and independently attach to
it.  You could install this process to start at system boot.



In addition to command and reply interactions initiated by the
GUI and/or controller, the GEMSIM process sends DMH message system
commands to certain mailboxes as a result of messages received from
the host that require attention, such as Remote Commands (RCMD's),
or parameter changes.

DMH Message System groupname:  "EQUIP" (set on command line)

  Mailboxes that the GEMSIM process listens for commands at:
    (Names based on the example use of "gemsim" SECS interface name)

   gemsim_SQL  -  used for SQL commands (see Datahub documentation)

                  Examples with comments:
                  # use "eval" to evaluate Tcl (eg., define an alarm)
                  "eval eq_alarm_add gemsim 1000 {Software Test Alarm}"
                  # the usual commands are standard SQL (eg., set alarm)
                  "update ei_alarm set is_set=1 where ALID=1000 and spname='gemsim'"
                  # tell the GEMSIM to shutdown
                  "exit"
               
   gemsim_RPC  -  used for Tcl commands - reply message is 
                  <return_code> <result_string>

                  #example Tcl commands with comments
                  # define an alarm type
                  "eq_alarm_add gemsim 1001 {Software Test Alarm 1001}"
                  # report an event (4047 == CEID of processing started)
                  eq_gem_event gemsim 4047  
                  # use "SQL" to access tables (clear an alarm)
                  "SQL {update ei_alarm set is_set=0 where ALID=1000 and spname='gemsim'}"
            
   Note in the above that you can access all of the SQL or Tcl functionality
   from either choice of mailboxes.  Both are provided because 

       (1) The _SQL mailbox can be used by the hub83client program in addition
           to your program(s).
       (2) The _RPC mailbox can be used by the dmh83_inspect program in addition
           to your program(s).
       (3) You can avoid a level of imbedded quotes or braces by sending SQL statements 
           to the _SQL mailbox box.  

   The GEMSIM process expects your program(s) to be listening at the following 
   mailboxes to support interaction with the Gem Host:

   gemsim_RCMD  - Remote Commands (with arguments) are sent to this mailbox.
        The command messages are of the form:
        <command> [{<argname> <argvalue>}]+
        You define what RCMDs are supported- examples:
                ABORT
                PAUSE
                RESUME
                PP-SELECT {PPExecName <ppexecname>}
                START
                STOP
        Hint - convert the sender's commands to a single alphabetic case and
               accept either case, or mixed case commands.
        A reply is expected within 10 seconds.
        The expected reply messages are:
           "0"  meaning ok - command performed
           "1"  meaning invalid command
           "2"  meaning cannot do it in current state
           "3 [{<subscript> <errcode>}]+"  meaning bad argument parameter(s)
                <subscript> := 0 based offset in parameter list
                <errcode> := { 1 | 2 }   1 == bad name, 2 == bad value
               Example- "3 {1 2}" means the 2nd argument was given an
                        invalid value.
           "4"  meaning ok - will do command asynchronously
         

   gemsim_PARAMETER - host initiated parameter updates (S2F16) are sent 
          to this mailbox.  The command messages are of the form:
          set <varname> <new_value>
          The new values have already been verified against the configured
          limits, and a success acknowledgement has already been sent to the
          host. (No reply is expected to the DMH message.)


   gemsim_ERROR - If your program fails to send proper reply data, error messages
          are sent to the _ERROR mailbox.

   gemsim_ALERT - Operator Alerts are sent to the _ALERT mailbox

   gemsim_TERMINAL - Stream 10 Terminal services are sent to the _TERMINAL mailbox
          Possible messages are:
          "DISPLAY <TEXT>"   
              <TEXT> :=  S10F3 TEXT or the concatenation of S10F5 TEXTs using linefeeds 
 


The implemented functionality is a demonstration/starting point.  You also want
to have the ei_variable table "wired" so that for changing data, the host gets the
correct values when/if they are tied to event reports.  This can be done by
replacing the varmethod entry to a procedure that queries for the current value,
typically using DMH message communication.  Another alternative, and the best one
for infrequently changed data, is to explicitly update the value in the ei_variable
table when the value is changed at the controller.  The DMH can pass hundreds of messages
a second so do not be overly concerned with the overhead.


Use dmh83_inspect and hub83client to interact with gemsim running in background:

     On NT:  "dmh83_inspect"  ( File/Select Local Interpreter)

     On Unix or NT: "dmh83_inspect gemsim_RPC@EQUIP

                    "hub83client gemsim_SQL@EQUIP" 





----------------------------------------------------------------------------------
Command Line

  The arguments to eq_server_init below specify the SECS interface name as "gemsim"
  and the DMH groupname as "EQUIP".
  We execute additional batch file argments so you can specify RS-232 or HSMS
  the same way it is done for the gemsim application script.
  We use the after command to get the initialization sequence right-
   -tclargs comes first so PORT argument is ahead of gemsim script
   next,-f gemsim, gemsim script is included and SECS interface is created
         also auto_path is setup
   subsequently because of after, eq_server_init executes for DMH initialization

Example of overriding PORT: (see Applications/SECS-GEM EI documentation)
    gemsim_server "set PORT COM1"
    

:EndOfComments
start dmh_wish -notk -tclargs %1 %2 %3 %4 "after 1 {eq_server_init gemsim EQUIP}" -f gemsim
