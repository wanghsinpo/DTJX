#
# (C) Copyright Keysight Technologies, Inc. 2001-2015
# All Rights are reserved.
#
# Copying Or Other Reproduction Of This Program Except For Archival Purposes
# Is Prohibited Without The Prior Written Consent Of Keysight Technologies.
#


############################################################################## 
#
# Desc:  RecipeParser Name Space
#
#        This namespace provides functions called by VGEM that are 
#        platform specific. This parser is installed in the platform
#        specific directory (vgem/tester_type like vgem/specs)
#        and loaded at run-time.
#
#        The functions provide access to the recipe list and the contents
#        of a specific recipe
#
# Change Log:
# PGauthier Nov 1 2002    Initial version
##############################################################################   

namespace eval RecipeParser {

   #variable .....private data section
   
   
   
##############################################################################
# Proc name:  RecipeParser::init 
#
# Desc:     Initializes private variables    
#
# Parameters:
#           none
#
# Return:      
#
# Change Log:
# PGauthier Nov 1 2002    Initial version
##############################################################################   
proc init {} { 

}

##############################################################################
# Proc name:  RecipeParser::getListOfRecipes
#
# Desc:     Returns a list of test recipes
#
# Parameters:
#           recipe_file :  path and recipe file name
#
# Return:   Returns a list of test recipes
#           Returns an empty list if error
#
# Change Log:
# PGauthier Nov 1 2002    Initial version
# PGauthier Jan 7 2003    Updated for new recipe format in SPECS 3.0
##############################################################################   
proc getListOfRecipes { recipe_file } { 

   global VGEM 
   
   set filelist {}
   set fileid [open $recipe_file r]
   
   while { [gets $fileid data] >= 0 } {
   
     set data [string trim $data]
     
     if { [string first "#" $data] != 0 } {
     
        set data [split $data "\t"]
        if { [lindex $data 0] != "" } {
          lappend filelist [lindex $data 0]
        }
     
     }
   
   } 
   
   close $fileid
   return $filelist

}

##############################################################################
# Proc name:  RecipeParser::getRecipeContents
#
# Desc:     Returns a recipe contents
#
# Parameters:
#           recipe_file :  path and recipe file name
#           recipe      :  recipe_id
#
# Return:   Returns a recipe contents
#           Returns an empty list if error
#
# Change Log:
# PGauthier Nov 1 2002    Initial version
# PGauthier Jan 7 2003    Updated for new recipe format in SPECS 3.0
##############################################################################   
proc getRecipeContents { recipe_file recipe_id } { 

   global VGEM 
    
   set fileid [open $recipe_file r]
   
   while { [gets $fileid data] >= 0 } {
   
     set data [string trim $data]
     
     if { [string first "#" $data] != 0 } {
     
        set split_data [split $data "\t"]
        set recipe [lindex $split_data 0]
        
        if {$recipe == $recipe_id} {
          close $fileid
          return $data
        }
     
     }
   
   } 
   
   return ""

}

# end of RecipeParser name space

}
