# (C) Copyright Agilent Technologies, Inc. 2001.
# All Rights are reserved.
#
# Copying Or Other Reproduction Of This Program Except For Archival Purposes
# Is Prohibited Without The Prior Written Consent Of Agilent Technologies.
#

# This file is for TEL specific enumerations 


##############################################################################
# Proc name:  substrateEnumToString
#
# Desc:       returns the String equivalent for the given attribute and enum
#             for the substrate object
#
# Parameters:
#   Attribute     Specified attribute
#   enum          numeric enum value
#
# Return:         String representing enum on success
#	              "" upon failure to translate enum
##############################################################################

proc substrateEnumToString {Attribute enum } {
    
    switch $Attribute {
	MaterialStatus {
            switch $enum {
		1 { return STATUS_1 }
		2 { return STATUS_2 }
		3 { return STATUS_3 }    
		4 { return STATUS_4 }
            }
	} 
	SubstProcState {
            switch $enum {
		1 { return "NEEDS PROCESSING" }
		2 { return "IN PROCESS" }
		3 { return PROCESSED }    
		4 { return ABORTED }
		5 { return STOPPED }
		6 { return REJECTED }
            }
	} 
	SubstState {
            switch $enum {
		1 { return  "AT SOURCE"}
		2 { return  "AT WORK"}
		3 { return  "AT DESTINATION"}    
            }
	} 
	SubstType {
            switch $enum {
		1 { return  WAFER }
		2 { return  "FLAT PANEL"}
		3 { return  CD}    
		4 { return  MASK}
            }
	} 
	SubstUsage {
            switch $enum {
		1 { return  PRODUCT}
		2 { return  TEST}
		3 { return  FILLER}    
		4 { return  CLEANING}
            }
	} 
    }
    return ""
}


##############################################################################
# Proc name:  substrateStringToEnum
#
# Desc:       returns the enum equivalent for the given attribute and string
#             for the substrate object
#
# Parameters:
#   Attribute     Specified attribute
#   enum          numeric enum value
#
# Return:         enum representing string on success
#	              0 upon failure to translate enum
##############################################################################

proc substrateStringToEnum {Attribute strn } {
    
    switch $Attribute {
	MaterialStatus {
            switch $strn {
		STATUS_1     {return 1}
		STATUS_2     {return 2}
		STATUS_3     {return 3}    
		STATUS_4     {return 4}
            }
	}
	
	SubstProcState {
            switch $strn {
		"NEEDS PROCESSING"  {return 1}  
		"IN PROCESS"        {return 2}
		PROCESSED           {return 3}   
		ABORTED             {return 4}  
		STOPPED             {return 5}  
		REJECTED            {return 6}  
            }
	}

	SubstState {
            switch $strn {
		"AT SOURCE"         {return 1}
		"AT WORK"           {return 2}
		"AT DESTINATION"    {return 3}    
            }
	}
	
	SubstType {
            switch $strn {
		WAFER           {return 1}
		"FLAT PANEL"    {return 2}
		CD              {return 3}    
		MASK            {return 4}
            }
	}
	
	SubstUsage {
            switch $strn {
		PRODUCT     {return 1}
		TEST        {return 2}
		FILLER      {return 3}    
		CLEANING    {return 4}
            }
	}
    }

    return ""
}


##############################################################################
# Proc name:  substrateLocEnumToString
#
# Desc:       returns the String equivalent for the given attribute and enum
#             for the substrateLoc object
#
# Parameters:
#   Attribute     Specified attribute
#   enum          numeric enum value
#
# Return:         String representing enum on success
#	              "" upon failure to translate enum
##############################################################################

proc substrateEnumToString {Attribute enum } {
    
    switch $Attribute {
	SubstLocState {
            switch $enum {
		1 { return UNOCCUPIED }
		2 { return OCCUPIED }
            }
	} 
    }
    return ""
}


##############################################################################
# Proc name:  substrateLocStringToEnum
#
# Desc:       returns the enum equivalent for the given attribute and string
#             for the substrateLoc object
#
# Parameters:
#   Attribute     Specified attribute
#   enum          numeric enum value
#
# Return:         enum representing string on success
#	              0 upon failure to translate enum
##############################################################################

proc substrateStringToEnum {Attribute strn } {
    
    switch $Attribute {
	SubstLocState {
            switch $strn {
		UNOCCUPIED     {return 1}
		OCCUPIED       {return 2}
            }
	}
    }

    return ""
}
