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

#include <string.h>

#define MAX_BUF_LEN        1026     /* 1024 + 1(LF) + 1(NULL) */
#define MAX_ELEMENT_LEN    256      /* 255 + '\0' */
#define MAX_NAME_NUM       10

#define HEADER_IDENTIFIRE  "#lot,"
#define DELIMITER          ','
#define LF                 0x0A

void get_element(char* buf, char** head){

  char* tail;
  char* next;
  int   len;

  /* initialize */
  buf[0] = '\0';
  if(strlen(*head) == 0) return;

  /* find delimiter */
  tail = strchr(*head, DELIMITER);

  /*--------------------------------------------*/
  /* set current element and go to next element */
  /*--------------------------------------------*/
  if(tail != NULL){
    len = tail - *head;
    next = tail + 1;
  }
  else{
    len = strlen(*head);
    next = NULL;
  }
  /* truncate tail of string if string is too long */
  if(len >= MAX_ELEMENT_LEN){ len = MAX_ELEMENT_LEN - 1; }
  /* set */
  strncpy(buf, *head, len);
  buf[len] = '\0';
  /* to next */
  *head = next;

}

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : READ_PROCCOND
  Vers : 1
  Desc : Read process condition file.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Filename        S    -        file name                       

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Ret             I    -        return code                     
  2 Readnum         I    -        the number of read condition    

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
READ_PROCCOND(STRING Filename,INTEGER *Ret,INTEGER *Readnum)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

  INTEGER index;
  STRING  dummy;
  INTEGER type, dim, s1, s2;
  FILE*   fp;
  char    buf[MAX_BUF_LEN];
  char    element_buf[MAX_ELEMENT_LEN];
  char    *head;
  STRING* cond_ptr;       /* buffer for data set */
  int     cond_val_num;   /* the number of condition value */
  STRING* cond_name_ptr;  /* buffer to hold condition name */
  int     cond_name_num;  /* the number of condition name */
  int     cond_no;        /* condition No. (column number) */
  STRING  lot_id, wafer_id;
  INTEGER slot_no;
  int     line_num;

  int     d1, d2;
  int     find_header = 0;
  int     err_flag;
  char*   tmp;

  enum { SLOT_NO = 0,
         LOT_ID,
         WAFER_NO,
         COND_NAME,
         COND_VALUE };

  *Ret = 0;

  /* Ret
      0  : success
      -1 : error (file open)
      -2 : error (file format)
      -3 : error (tag variable size)
      -4 : error (tag variable definition)
   */

  /* check tag variable exists or not */
  TPLTAGINDEX("SYSTEM", "TST_PROCCOND_VAL", &index);
  if(index == -1){
    *Ret = -4;
    return;
  }

  /* tag variable must be type of STRING[5][n]*/
  TPLTAGINFO("SYSTEM", index, &dummy, &type, &dim, &s1, &s2);
  if((type != 3) || (dim != 2) || (s2 != 5)){
    *Ret = -4;
    return;
  }

  /* open process condition file */
  if((fp = fopen(Filename, "r")) == NULL){
    *Ret = -1;
    return;
  }

  /* allocate and initialize buffer */
  cond_ptr = (STRING*)malloc(sizeof(STRING) * s1 * s2);
  for(d2 = 0; d2 < s2; d2++){
    for(d1 = 0; d1 < s1; d1++){
      strcpy(cond_ptr[d2 * s1 + d1], "");
    }
  }
  cond_name_ptr = (STRING*)malloc(sizeof(STRING) * MAX_NAME_NUM);

  /*==============
   * main loop
   *==============*/
  cond_val_num = 0;
  cond_name_num = 0;
  line_num = 0;
  while(fgets(buf, MAX_BUF_LEN, fp)){

    line_num++;

    /* line is too long */
    if(buf[strlen(buf) - 1] != LF){
      *Ret = -2;
      err_flag = 1;
      break;
    }

    /* trim and init */
    buf[strlen(buf) - 1] = '\0';
    head = buf;

    /* skip empty line */
    if(strlen(buf) == 0) continue;

    /* find header line (only 1st) */
    if((find_header == 0) && (strncmp(buf, HEADER_IDENTIFIRE, strlen(HEADER_IDENTIFIRE)) == 0)){
      /* skip 1st and 2nd element */
      get_element(element_buf, &head);
      get_element(element_buf, &head);

      /* read condition names */
      err_flag = 0;
      while(1){

        /* read a name */
        if((head == NULL) || (strlen(head) == 0)) break;
        get_element(element_buf, &head);

        /* check max number of condition */
        if(cond_name_num + 1 > MAX_NAME_NUM){
          *Ret = -2;
          err_flag = 1;
          break;
        }

        /* hold a name*/
        strcpy(cond_name_ptr[cond_name_num], element_buf);
        cond_name_num++;
      }
      if(err_flag == 1) break;

      /* go to next line */
      find_header = 1;
      continue;
    }

    /* skip comment line */
    if(buf[0] == '#') continue;

    /* valid line */
    {
      /* lot ID */
      get_element(element_buf, &head);
      if(strlen(element_buf) == 0){
        *Ret = -2;
        err_flag = 1;
        break;
      }
      strcpy(lot_id, element_buf);

      /* wafer ID */
      get_element(element_buf, &head);
      if(strlen(element_buf) == 0){
        *Ret = -2;
        err_flag = 1;
        break;
      }
      strcpy(wafer_id, element_buf);

      /* find slot number */
      GET_SLOT_NO(lot_id, wafer_id, &slot_no);
      if(slot_no == 0) continue;

      /* condition */
      cond_no = 0;
      err_flag = 0;
      while(1){

        /* read one condition value */
        if((head == NULL) || (strlen(head) == 0)) break;
        get_element(element_buf, &head);

        /* check max number of condition value */
        if(cond_val_num + 1 > s1){
          *Ret = -3;
          err_flag = 1;
          break;
        }

        /* check max number of kind of condition */
        if(cond_no + 1 > cond_name_num){
          *Ret = -2;
          err_flag = 1;
          break;
        }

        /* set value */
        sprintf(cond_ptr[SLOT_NO * s1 + cond_val_num], "%d", slot_no);
        strcpy(cond_ptr[LOT_ID * s1 + cond_val_num], lot_id);
        strcpy(cond_ptr[WAFER_NO * s1 + cond_val_num], wafer_id);
        strcpy(cond_ptr[COND_NAME * s1 + cond_val_num], cond_name_ptr[cond_no]);
        strcpy(cond_ptr[COND_VALUE * s1 + cond_val_num], element_buf);

        /* count up number of condition */
        cond_val_num++;

        /* count up condition number */
        cond_no++;
      }
      if(err_flag == 1) break;
    }
    
  }

  /* set values */
  TPLPUTSATAG("SYSTEM", index, 0, cond_ptr);

  /* set return value */
  if(*Ret == 0){
    *Readnum = cond_val_num;
  }
  else if(*Ret == -2){
    *Readnum = line_num;
  }

  free(cond_ptr);
  free(cond_name_ptr);
  fclose(fp);
  return;

/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
