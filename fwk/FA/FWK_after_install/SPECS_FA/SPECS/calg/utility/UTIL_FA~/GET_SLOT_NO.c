/****** <BEGIN> INCLUDE FILES *********** DON'T EDIT FROM <BEGIN> TO <END> ***/
#include <stdio.h>
#include <stdlib.h>
#include <SPECS.h>
#include <ALGUTIL.h>
#include <TOOLCTRL.h>
#include <CALDB.h>
#include <UTILITY.h>
#include <PROBER.h>
/****** <END>   INCLUDE FILES *********** DON'T EDIT FROM <BEGIN> TO <END> ***/

#define SYS_CLASS     "SYSTEM"

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : GET_SLOT_NO
  Vers : 1
  Desc : Get slot number from lot ID and wafer ID.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Lotid           S    -                                        
  2 Waferid         S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Slotno          I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
GET_SLOT_NO(STRING Lotid,STRING Waferid,INTEGER *Slotno)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

  INTEGER slot_num;

  INTEGER index;
  INTEGER *lot_index;
  STRING  *lot_id;
  STRING  *wafer_id;
  INTEGER *slot_selection;

  STRING  dummy;
  INTEGER type, dim, s1, s2;
  int i;

  /* initialize */
  *Slotno = 0;

  /* total slot number */
  TPLTAGINDEX(SYS_CLASS, "PRB_SLOT_TOTAL_ALL", &index);
  if(index == -1) return;
  TPLGETITAG(SYS_CLASS, index, 0, &slot_num);

  /* lot ID index (TST_SLOT_LOT_INDEX) */
  TPLTAGINDEX(SYS_CLASS, "TST_SLOT_LOT_INDEX", &index);
  if(index == -1) return;
  TPLTAGINFO(SYS_CLASS, index, &dummy, &type, &dim, &s1, &s2);
  lot_index = (INTEGER*)malloc(sizeof(INTEGER) * s1);
  TPLGETIATAG(SYS_CLASS, index, 0, lot_index);

  /* lot ID (TST_LOT_ID) */
  TPLTAGINDEX(SYS_CLASS, "TST_LOT_ID", &index);
  if(index == -1){
    free(lot_index);
    return;
  }
  TPLTAGINFO(SYS_CLASS, index, &dummy, &type, &dim, &s1, &s2);
  lot_id = (STRING*)malloc(sizeof(STRING) * s1);
  TPLGETSATAG(SYS_CLASS, index, 0, lot_id);

  /* wafer ID (TST_SLOT_WAFERID) */
  TPLTAGINDEX(SYS_CLASS, "TST_SLOT_WAFERID", &index);
  if(index == -1){
    free(lot_index);
    free(lot_id);
    return;
  }
  TPLTAGINFO(SYS_CLASS, index, &dummy, &type, &dim, &s1, &s2);
  wafer_id = (STRING*)malloc(sizeof(STRING) * s1);
  TPLGETSATAG(SYS_CLASS, index, 0, wafer_id);

  /* slot selection (TST_SLOT_SELECT) */
  TPLTAGINDEX(SYS_CLASS, "TST_SLOT_SELECT", &index);
  if(index == -1){
    free(lot_index);
    free(lot_id);
    free(wafer_id);
    return;
  }
  TPLTAGINFO(SYS_CLASS, index, &dummy, &type, &dim, &s1, &s2);
  slot_selection = (INTEGER*)malloc(sizeof(INTEGER) * s1);
  TPLGETIATAG(SYS_CLASS, index, 0, slot_selection);

  /* find slot number */
  for(i = 1; i <= slot_num; i++){

    /* skip unselect slot */
    if(slot_selection[i - 1] != 1) continue;

    /* compare lot ID and wafer ID */
    if((strcmp(Lotid, lot_id[lot_index[i - 1] - 1]) == 0) &&
       (strcmp(Waferid, wafer_id[i - 1]) == 0)){
      *Slotno = i;
      break;
    }

  }

  free(lot_index);
  free(lot_id);
  free(wafer_id);
  free(slot_selection);
  return;

/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
