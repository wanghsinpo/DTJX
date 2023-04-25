
       Remote Client of an Equipment Interface


This utility attaches to a Tcl interpreter that is listening
to a DMH mailbox for Tcl commands.  The utility is able to
create local trace windows for secsport, hsms, or comm 
equipment interfaces.  Also, the utility can launch
the inspect or hubclient programs attached to the
same target application.  In combination, these utilities
let you debug and control your equipment interfaces from any 
seat on your local area network!


Note:  

    The utilities rely on your target application 
listening to a DMH mailbox such as "gemhost_RPC" for
Tcl commands, and another mailbox such as "gemhost_SQL"
for SQL commands.  

For a demonstration example, as outlined below,
start a DMH server process from the command line,
and then start the supervisor process as a 
member of the DMH message group.
When you start the gemhost interface from the 
supervisor window, you can use the ei_client,
possibly from another computer, for debugging.

  rem have gemsim or some other "equipment running"
  C:\usr\local\gem\equip> gemsim     
  rem Start a DMH server running
  cd C:\usr\local\gem\host
  C:\usr\local\gem\host> datahub "set group=gem" eof
  rem start the host side, and use the DMH server
  C:\usr\local\gem\host> supervisor "set MB_GROUP gem"
  rem  from the supervisor window connect to gemsim or
  rem  your equipment with gemhost
  rem now you can succeed with the client
  C:\usr\local\gem\host> cd C:\usr\local\gem\client
  C:\usr\local\gem\host> ei_client gemhost_RPC@gem

----
$Id: README.txt,v 1.3 2004/02/04 16:58:25 hume Exp $
