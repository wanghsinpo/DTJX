
4/2005

GEM equipment simulator

The fundamental gem requirements are met.  Hume Integration
separately provides an example reference document that meets
the standard documentation requirements.  For most primary 
messages, the software accepts any of the allowed format 
codes for data items.  Therefore, the need for reference
documentation is lessened.


FUNDAMENTAL GEM REQUIREMENTS      Implemented      Gem Compliant
                                  Yes   No          Yes   No

State Models                       x                 x
Equipment Processing States        x                 x
Host initiated S1 F13,14           x                 x
Event Notification                 x                 x
On-Line Identification             x                 x
Error Messages                     x                 x
Documentation                      x                 x
Control (Operator Initiated)       x                 x

ADDITIONAL CAPABILITIES

Establish Communications           x                 x
Dynamic Event Report Config.       x                 x
Variable Data Collection           x                 x
Trace Data Collection              x                 x
Status Data Collection             x                 x
Alarm Management                   x                 x
Remote Control                     x                 x
Equipment Constants                x                 x
Process Program Management         x                 x
Material Movement                  x                 x
Equipment Terminal Services        x                 x
Clock                              x                 x
Limits Monitoring                       x
Spooling                           x                 x
Control (Host-Initiated)           x                 x

---------------------------------------------------------------

A Note on Error Message Compliance:

The software will not always send a S9F7 when it receives
a non-standard or improper message.  Depending on the
circumstances, a failure reply, or an abort reply, may
be received instead.  In general, the software is
written to not be fussy about the exact types of data
items.  Instead, it works with the values that are 
supplied, usually manipulating them as strings.
An implementor could use the same toolset and write
software that is excrutiatingly fussy about types
and exact compliance.  

A Note on persistent storage:

Some of the data such as report definitions is required
by the standard to be retained in non-volatile storage.
This requirement is met when the software is used from
any of the external language products such as the .NET
SecsPort.  These libraries set an array element value,
ReportsAreSaved, which triggers restore and saving
logic the first time that comm_enable is called.

