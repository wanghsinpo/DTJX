
This directory is for your custom code.  If you need to
revise any of the HIS distributed files, you can copy the
whole file to this directory, revise it, and rebuild the
tclIndex file by executing:

   dmh_wish -notk -tclargs "auto_mkindex . *.tcl" exit

If you type "make" from a command line in this directory,
the "make.bat" or "Makefile" invokes this command.

This directory is added to the auto_path variable of the
Tcl interpreter before the directories that contain the
HIS distributed files.  Your custom procedures will be 
found and used instead of the HIS distributed procedures 
of the same name.

You may wish to create your own directories for specific
types of equipment interfaces.  You can put your shared
procedures in this directory, and put your equipment
specific code in a separate directory that you create
for each kind of equipment.  You either need to keep the
equipment specific code in separate directories, or give 
the equipment specific code unique procedure names.
Look at the ../host/supervisor script for an example
startup script that sets up the auto_path.

An example directory structure:

            equipment_interfaces

         /     /      \           \     \ 
     host     lib     custom      kns   esec


   host - has the HIS provided files from gem/host.

    lib - has the HIS provided files from gem/lib.

 custom - has customer written procedures that
          are used by code in the "kns" and "esec"
          directories.

   kns - Has a script to start ../host/supervisor
         from the kns directory.  Starts a dozen interfaces 
         using a Xyplex terminal server.  
         Has custom procedures for K&S equipment,
         and a valid tclIndex index file.
         The auto_path variable is initialized to 
         have the "kns", "custom", "host", and "lib" 
         directories in that order.

  esec - Has a script to start ../host/supervisor
         from the esec directory.  Has custom
         procedures for Esec equipment.
         The auto_path variable is initialized to 
         have the "esec", "custom", "host", and "lib" 
         directories in that order.

