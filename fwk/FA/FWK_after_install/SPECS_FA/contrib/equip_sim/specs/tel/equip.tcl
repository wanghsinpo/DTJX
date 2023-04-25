
proc eq_custom_online {spname} {
}


proc initPersistentObjects {} {

set locList [list UpperTransferArm LowerTransferArm SubChuck MainChuck SingleWaferLoadTray ]

    foreach location $locList {
        instantiateSubstLoc $location [list [list ObjType SubstLoc] [list SubstLocState 1] [list SubstID Unknown] [list ObjID $location]]
        }
}
