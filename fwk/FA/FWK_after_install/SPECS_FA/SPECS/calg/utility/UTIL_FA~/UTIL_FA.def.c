#include <SPECS.h>
#include <SPECS_SYS.h>

/* Definition for algorithm ADD_HEAD_SPACE */

extern void _ADD_HEAD_SPACE(void *, void *);
extern void __ADD_HEAD_SPACE(void *);

static _VARDEF	_ADD_HEAD_SPACE_in[] = {
	{ "Original", "",_TYPES, 0,0,0, "", "" },
	{ "Length", "",_TYPEI, 0,0,0, "", "0" },
};
static _VARDEF	_ADD_HEAD_SPACE_out[] = {
	{ "Modified", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm ADD_TAIL_SPACE */

extern void _ADD_TAIL_SPACE(void *, void *);
extern void __ADD_TAIL_SPACE(void *);

static _VARDEF	_ADD_TAIL_SPACE_in[] = {
	{ "Original", "",_TYPES, 0,0,0, "", "" },
	{ "Length", "",_TYPEI, 0,0,0, "", "0" },
};
static _VARDEF	_ADD_TAIL_SPACE_out[] = {
	{ "Modified", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm ALGPANEL_LAUNCH */

extern void _ALGPANEL_LAUNCH(void *, void *);
extern void __ALGPANEL_LAUNCH(void *);

static _VARDEF	_ALGPANEL_LAUNCH_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "Session ID", "1" },
	{ "Port", "",_TYPES, 0,0,0, "Port ID", "14062" },
	{ "Project", "",_TYPES, 0,0,0, "Project ID", "v" },
	{ "Hostname", "",_TYPES, 0,0,0, "Hostname", "" },
};

/* Definition for algorithm ALGPANEL_START */

extern void _ALGPANEL_START(void *, void *);
extern void __ALGPANEL_START(void *);

static _VARDEF	_ALGPANEL_START_in[] = {
	{ "Mode", "",_TYPEI, 0,0,0, "0:Normal, 1:Disable problibs", "0" },
};

/* Definition for algorithm ALGPANEL_STOP */

extern void _ALGPANEL_STOP(void *, void *);
extern void __ALGPANEL_STOP(void *);


/* Definition for algorithm APPLY_FWKCONF */

extern void _APPLY_FWKCONF(void *, void *);
extern void __APPLY_FWKCONF(void *);

static _VARDEF	_APPLY_FWKCONF_in[] = {
	{ "File", "",_TYPES, 0,0,0, "", "" },
	{ "Type", "",_TYPEI, 0,0,0, "0:All vars, 1:Normal vars only, 2:Special vars only", "0" },
};
static _VARDEF	_APPLY_FWKCONF_out[] = {
	{ "Errno", "",_TYPEI, 0,0,0, "", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm ARRAY_LOOKUP1 */

extern void _ARRAY_LOOKUP1(void *, void *);
extern void __ARRAY_LOOKUP1(void *);

static _VARDEF	_ARRAY_LOOKUP1_in[] = {
	{ "Src", "",_TYPES, 1,256,0, "Source strings", "" },
	{ "Pat", "",_TYPES, 0,0,0, "Pattern string", "" },
};
static _VARDEF	_ARRAY_LOOKUP1_out[] = {
	{ "Pos", "",_TYPEI, 0,0,0, "Position (>0 position, 0 not found)", "0" },
};

/* Definition for algorithm ARRAY_LOOKUP2 */

extern void _ARRAY_LOOKUP2(void *, void *);
extern void __ARRAY_LOOKUP2(void *);

static _VARDEF	_ARRAY_LOOKUP2_in[] = {
	{ "Src", "",_TYPES, 1,256,0, "Source strings", "" },
	{ "Pat", "",_TYPES, 1,256,0, "Pattern strings", "" },
};
static _VARDEF	_ARRAY_LOOKUP2_out[] = {
	{ "Pos", "",_TYPEI, 1,256,0, "Positions of each pattern string (>0, 0 not found)", "" },
};

/* Definition for algorithm ARRAY_LOOKUP3 */

extern void _ARRAY_LOOKUP3(void *, void *);
extern void __ARRAY_LOOKUP3(void *);

static _VARDEF	_ARRAY_LOOKUP3_in[] = {
	{ "Src", "",_TYPES, 1,256,0, "Source strings", "" },
	{ "Pos", "",_TYPEI, 1,256,0, "Positions of strings to extract (>0 position", "" },
};
static _VARDEF	_ARRAY_LOOKUP3_out[] = {
	{ "Sub", "",_TYPES, 1,256,0, "Extracted strings", "" },
};

/* Definition for algorithm ATTRIB_FILE */

extern void _ATTRIB_FILE(void *, void *);
extern void __ATTRIB_FILE(void *);

static _VARDEF	_ATTRIB_FILE_in[] = {
	{ "Filename", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_ATTRIB_FILE_out[] = {
	{ "Permission", "",_TYPES, 0,0,0, "", "" },
	{ "Owner", "",_TYPES, 0,0,0, "", "" },
	{ "Group", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm BEEP */

extern void _BEEP(void *, void *);
extern void __BEEP(void *);

static _VARDEF	_BEEP_in[] = {
	{ "Freq", "Hz",_TYPER, 0,0,0, "Frequency", "2000" },
	{ "Dur", "Sec",_TYPER, 0,0,0, "Duration", "0.1" },
};

/* Definition for algorithm CALL_ERRHANDLER */

extern void _CALL_ERRHANDLER(void *, void *);
extern void __CALL_ERRHANDLER(void *);

static _VARDEF	_CALL_ERRHANDLER_in[] = {
	{ "ErrorNo", "",_TYPES, 0,0,0, "ErrorCode  .ex  \"12-34567\"", "" },
	{ "Message", "",_TYPES, 0,0,0, "Error Message", "" },
	{ "MoreInfo", "",_TYPES, 0,0,0, "More Info", "" },
};
static _VARDEF	_CALL_ERRHANDLER_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm CHECK_DATAFILE */

extern void _CHECK_DATAFILE(void *, void *);
extern void __CHECK_DATAFILE(void *);

static _VARDEF	_CHECK_DATAFILE_in[] = {
	{ "Filename", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_CHECK_DATAFILE_out[] = {
	{ "Valid", "",_TYPEI, 0,0,0, "", "1" },
};

/* Definition for algorithm CHECK_FILE */

extern void _CHECK_FILE(void *, void *);
extern void __CHECK_FILE(void *);

static _VARDEF	_CHECK_FILE_in[] = {
	{ "Testplan", "",_TYPES, 0,0,0, "", "" },
	{ "Limit", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_CHECK_FILE_out[] = {
	{ "Result", "",_TYPEI, 0,0,0, "0: OK 1: File Mismatch: 2: Revision Mismatch", "0" },
};

/* Definition for algorithm CHECK_PASSWD */

extern void _CHECK_PASSWD(void *, void *);
extern void __CHECK_PASSWD(void *);

static _VARDEF	_CHECK_PASSWD_in[] = {
	{ "Name", "",_TYPES, 0,0,0, "", "" },
	{ "Command", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_CHECK_PASSWD_out[] = {
	{ "Result", "",_TYPEI, 0,0,0, "0: Fail 1: OK", "0" },
};

/* Definition for algorithm CHECK_PROBER */

extern void _CHECK_PROBER(void *, void *);
extern void __CHECK_PROBER(void *);

static _VARDEF	_CHECK_PROBER_in[] = {
	{ "Symbol", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_CHECK_PROBER_out[] = {
	{ "Vendor", "",_TYPES, 0,0,0, "", "" },
	{ "Model", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm CHECK_PROFILE */

extern void _CHECK_PROFILE(void *, void *);
extern void __CHECK_PROFILE(void *);

static _VARDEF	_CHECK_PROFILE_out[] = {
	{ "Result", "",_TYPEI, 0,0,0, "0:OK 1:TPL: 2:FWK: 3:MLIB: 4:TLIB: 5:PLIB: 6:ULIB: 7:LIM 8:TCO 9", "0" },
};

/* Definition for algorithm CHECK_SYSCONF */

extern void _CHECK_SYSCONF(void *, void *);
extern void __CHECK_SYSCONF(void *);

static _VARDEF	_CHECK_SYSCONF_out[] = {
	{ "ERRNO", "",_TYPEI, 0,0,0, "", "0" },
	{ "ERRMSG", "",_TYPES, 0,0,0, "", "" },
	{ "SMODE", "",_TYPES, 0,0,0, "", "" },
	{ "OP_LANG", "",_TYPES, 0,0,0, "", "" },
	{ "ADTFORMAT", "",_TYPES, 0,0,0, "", "" },
	{ "CLEARONRETEST", "",_TYPES, 0,0,0, "", "" },
	{ "CLEARONREJECT", "",_TYPES, 0,0,0, "", "" },
	{ "PORTID", "",_TYPES, 0,0,0, "", "" },
	{ "PROJID", "",_TYPES, 0,0,0, "", "" },
	{ "HOSTNAME", "",_TYPES, 0,0,0, "", "" },
	{ "ADTLOGGING", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm CHECK_TIME */

extern void _CHECK_TIME(void *, void *);
extern void __CHECK_TIME(void *);

static _VARDEF	_CHECK_TIME_out[] = {
	{ "Time", "",_TYPER, 0,0,0, "", "0" },
};

/* Definition for algorithm CLOCK */

extern void _CLOCK(void *, void *);
extern void __CLOCK(void *);

static _VARDEF	_CLOCK_in[] = {
	{ "Digit", "",_TYPEI, 0,0,0, "# digits to represent a year", "2" },
};
static _VARDEF	_CLOCK_out[] = {
	{ "Year", "",_TYPEI, 0,0,0, "Year:   YY or YYYY", "0" },
	{ "Month", "",_TYPEI, 0,0,0, "Month:  MM", "0" },
	{ "Day", "",_TYPEI, 0,0,0, "Day:    DD", "0" },
	{ "Hour", "",_TYPEI, 0,0,0, "Hour:   HH", "0" },
	{ "Minute", "",_TYPEI, 0,0,0, "Minute: MM", "0" },
	{ "Second", "",_TYPEI, 0,0,0, "Second: SS", "0" },
	{ "Value", "",_TYPER, 0,0,0, "", "0" },
};

/* Definition for algorithm DATALOG_DIEEND */

extern void _DATALOG_DIEEND(void *, void *);
extern void __DATALOG_DIEEND(void *);

static _VARDEF	_DATALOG_DIEEND_in[] = {
	{ "Filename", "",_TYPES, 0,0,0, "Filename.", "/var/opt/SPECS/log/datalog.log" },
	{ "Mode", "",_TYPEI, 0,0,0, "All(0), Failed only(1)", "0" },
};

/* Definition for algorithm DEL_HEAD_SPACE */

extern void _DEL_HEAD_SPACE(void *, void *);
extern void __DEL_HEAD_SPACE(void *);

static _VARDEF	_DEL_HEAD_SPACE_in[] = {
	{ "Original", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_DEL_HEAD_SPACE_out[] = {
	{ "Modified", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm DEL_NEWLINE */

extern void _DEL_NEWLINE(void *, void *);
extern void __DEL_NEWLINE(void *);

static _VARDEF	_DEL_NEWLINE_in[] = {
	{ "Original", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_DEL_NEWLINE_out[] = {
	{ "Modified", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm DEL_TAIL_SPACE */

extern void _DEL_TAIL_SPACE(void *, void *);
extern void __DEL_TAIL_SPACE(void *);

static _VARDEF	_DEL_TAIL_SPACE_in[] = {
	{ "Original", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_DEL_TAIL_SPACE_out[] = {
	{ "Modified", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm FA_BLDSCR_LIM */

extern void _FA_BLDSCR_LIM(void *, void *);
extern void __FA_BLDSCR_LIM(void *);

static _VARDEF	_FA_BLDSCR_LIM_in[] = {
	{ "Masscr", "",_TYPES, 0,0,0, "Master script file to read", "/opt/SPECS/demo/sample_lim.scr" },
	{ "Fmtscr", "",_TYPES, 0,0,0, "Script file for limformat to write", "/opt/SPECS/demo/lim.scr" },
};
static _VARDEF	_FA_BLDSCR_LIM_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm FA_BLDSCR_TPL */

extern void _FA_BLDSCR_TPL(void *, void *);
extern void __FA_BLDSCR_TPL(void *);

static _VARDEF	_FA_BLDSCR_TPL_in[] = {
	{ "Masscr", "",_TYPES, 0,0,0, "Master script file to read", "/opt/SPECS/demo/sample_tpl.scr" },
	{ "Fmtscr", "",_TYPES, 0,0,0, "Script file for tplformat to write", "/opt/SPECS/demo/tpl.scr" },
};
static _VARDEF	_FA_BLDSCR_TPL_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm FA_CHKRUN_FWK */

extern void _FA_CHKRUN_FWK(void *, void *);
extern void __FA_CHKRUN_FWK(void *);

static _VARDEF	_FA_CHKRUN_FWK_in[] = {
	{ "Name", "",_TYPES, 0,0,0, "Key word of grep", "FA_" },
	{ "Status", "",_TYPES, 0,0,0, "SPECS Status", "running" },
};
static _VARDEF	_FA_CHKRUN_FWK_out[] = {
	{ "numFile", "",_TYPEI, 0,0,0, "The number of process regarding the filename", "0" },
	{ "numRunning", "",_TYPEI, 0,0,0, "The number of running process regarding the filename", "0" },
};

/* Definition for algorithm FA_CHK_FILES */

extern void _FA_CHK_FILES(void *, void *);
extern void __FA_CHK_FILES(void *);

static _VARDEF	_FA_CHK_FILES_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Dir", "",_TYPES, 0,0,0, "Direcory of file", "/opt/SPECS/demo" },
	{ "Filename_rev", "",_TYPES, 0,0,0, "Filename with revision number", "" },
	{ "Suffix", "",_TYPES, 0,0,0, "suffix of Filename", "tpl" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
};
static _VARDEF	_FA_CHK_FILES_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:ERR", "0" },
};

/* Definition for algorithm FA_CHK_FILES2 */

extern void _FA_CHK_FILES2(void *, void *);
extern void __FA_CHK_FILES2(void *);

static _VARDEF	_FA_CHK_FILES2_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Dir", "",_TYPES, 0,0,0, "Direcory of file", "/opt/SPECS/demo" },
	{ "Filename_rev", "",_TYPES, 0,0,0, "Filename with revision number", "" },
	{ "Suffix", "",_TYPES, 0,0,0, "suffix of Filename", "tpl" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
};
static _VARDEF	_FA_CHK_FILES2_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:ERR", "0" },
	{ "File_name", "",_TYPES, 0,0,0, "File name without revision name", "" },
	{ "Full", "",_TYPES, 0,0,0, "", "" },
	{ "Rev", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm FA_CHK_LIBPATH */

extern void _FA_CHK_LIBPATH(void *, void *);
extern void __FA_CHK_LIBPATH(void *);

static _VARDEF	_FA_CHK_LIBPATH_in[] = {
	{ "Orig", "",_TYPES, 0,0,0, "Direcory of file", "" },
};
static _VARDEF	_FA_CHK_LIBPATH_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:ERR", "0" },
	{ "Pathflug", "",_TYPEI, 0,0,0, "0:relativity 1:absolute", "0" },
	{ "Path", "",_TYPES, 0,0,0, "", "" },
	{ "Filename", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm FA_CHK_MEASLIB */

extern void _FA_CHK_MEASLIB(void *, void *);
extern void __FA_CHK_MEASLIB(void *);

static _VARDEF	_FA_CHK_MEASLIB_in[] = {
	{ "Revcont", "",_TYPEI, 0,0,0, "Revision Control Mode", "0" },
	{ "Lib", "",_TYPES, 1,256,0, "Measurement Library File (with Revision)", "" },
	{ "Libnum", "",_TYPEI, 0,0,0, "Number of Measurement Library", "6" },
	{ "Delimiter", "",_TYPES, 0,0,0, "Delimiter between File and Revision", "#" },
};
static _VARDEF	_FA_CHK_MEASLIB_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Error Code", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error Message", "" },
};

/* Definition for algorithm FA_CHK_REV */

extern void _FA_CHK_REV(void *, void *);
extern void __FA_CHK_REV(void *);

static _VARDEF	_FA_CHK_REV_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "Direcory of file", "" },
	{ "Kinds", "",_TYPES, 0,0,0, "MEAS:MeasurementLib TST:Testerlib PRB:Proberlib UTL:Utilitylib D", "MEAS" },
};
static _VARDEF	_FA_CHK_REV_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:ERR", "0" },
	{ "Filename", "",_TYPES, 0,0,0, "", "" },
	{ "Rev", "",_TYPES, 0,0,0, "", "" },
	{ "Path", "",_TYPES, 0,0,0, "", "" },
	{ "BasicPath", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm FA_CHK_REV2 */

extern void _FA_CHK_REV2(void *, void *);
extern void __FA_CHK_REV2(void *);

static _VARDEF	_FA_CHK_REV2_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "Session Number", "" },
	{ "Kinds", "",_TYPES, 0,0,0, "Type of Library", "MEAS" },
	{ "Count", "",_TYPEI, 0,0,0, "Index of Multi-Measurement Library", "0" },
};
static _VARDEF	_FA_CHK_REV2_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Error Code", "0" },
	{ "Filename", "",_TYPES, 0,0,0, "File Name", "" },
	{ "Rev", "",_TYPES, 0,0,0, "Revision", "" },
	{ "Path", "",_TYPES, 0,0,0, "File Name with Directory", "" },
	{ "BasicPath", "",_TYPES, 0,0,0, "Directory", "" },
};

/* Definition for algorithm FA_GETKEY_ITEMS */

extern void _FA_GETKEY_ITEMS(void *, void *);
extern void __FA_GETKEY_ITEMS(void *);

static _VARDEF	_FA_GETKEY_ITEMS_in[] = {
	{ "Key", "",_TYPES, 0,0,0, "Key ID (PPExecName)", "" },
	{ "Filename", "",_TYPES, 0,0,0, "File Name", "/opt/SPECS_FA/fapt/facomcore/recipe.txt" },
};
static _VARDEF	_FA_GETKEY_ITEMS_out[] = {
	{ "Waf", "",_TYPES, 0,0,0, "Wafer spec name", "TAC394.waf" },
	{ "Die", "",_TYPES, 0,0,0, "Die spec name", "TAC394.die" },
	{ "Tst", "",_TYPES, 0,0,0, "Test spec name", "TAC394.tst" },
	{ "Prb", "",_TYPES, 0,0,0, "Probe card spec name", "PRB2X6.prb" },
	{ "Tpl", "",_TYPES, 0,0,0, "Test plan file name", "DEMO.tpl" },
	{ "Lim", "",_TYPES, 0,0,0, "Limit file name", "DEMO.lim" },
	{ "Rcp", "",_TYPES, 0,0,0, "Prober recipe file name", "Recipe" },
	{ "Lot_id", "",_TYPES, 0,0,0, "Lot ID", "Lotid" },
	{ "Product_id", "",_TYPES, 0,0,0, "Product ID", "Product" },
	{ "Process_id", "",_TYPES, 0,0,0, "Process ID", "Process" },
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:Eof -2:No Data -3:No File", "0" },
};

/* Definition for algorithm FA_LIMBLD */

extern void _FA_LIMBLD(void *, void *);
extern void __FA_LIMBLD(void *);

static _VARDEF	_FA_LIMBLD_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
	{ "Tpl_dir", "",_TYPES, 0,0,0, "Testplan file directory", "/opt/SPECS/demo" },
	{ "Lim_dir", "",_TYPES, 0,0,0, "Limit file directory", "/opt/SPECS/demo" },
	{ "Tpl", "",_TYPES, 0,0,0, "Test Plan name to read", "testplan.tpl" },
	{ "Lim", "",_TYPES, 0,0,0, "Limit file name to write", "limitfile.lim" },
};
static _VARDEF	_FA_LIMBLD_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "detailed error message", "" },
};

/* Definition for algorithm FA_LIMBLD2 */

extern void _FA_LIMBLD2(void *, void *);
extern void __FA_LIMBLD2(void *);

static _VARDEF	_FA_LIMBLD2_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
	{ "Tpl_dir", "",_TYPES, 0,0,0, "Testplan file directory", "/opt/SPECS/demo" },
	{ "Lim_dir", "",_TYPES, 0,0,0, "Limit file directory", "/opt/SPECS/demo" },
	{ "Lms_dir", "",_TYPES, 0,0,0, "Limit spec directory", "/opt/SPECS/demo" },
	{ "Tpl", "",_TYPES, 0,0,0, "Test Plan name to read", "testplan.tpl" },
	{ "Lim", "",_TYPES, 0,0,0, "Limit file name to write", "limitfile.lim" },
	{ "Lms", "",_TYPES, 1,256,0, "Limit spec name to write", "" },
};
static _VARDEF	_FA_LIMBLD2_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "detailed error message", "" },
};

/* Definition for algorithm FA_LIMFMT */

extern void _FA_LIMFMT(void *, void *);
extern void __FA_LIMFMT(void *);

static _VARDEF	_FA_LIMFMT_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
	{ "Src_lim_dir", "",_TYPES, 0,0,0, "Temporary file directory", "/opt/SPECS/demo" },
	{ "Script_dir", "",_TYPES, 0,0,0, "Script file directory", "/opt/SPECS/demo" },
	{ "Dst_lim_dir", "",_TYPES, 0,0,0, "New Limitfile file directory", "/opt/SPECS/demo" },
	{ "Src_lim", "",_TYPES, 0,0,0, "Temporay LimitFile to read", "tmpsrc.lim" },
	{ "Script", "",_TYPES, 0,0,0, "Specified script file", "sample_lim.scr" },
	{ "Dst_lim", "",_TYPES, 0,0,0, "Generated LimitFile to write", "tmpdst.lim" },
};
static _VARDEF	_FA_LIMFMT_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm FA_LMP_CLEARLN */

extern void _FA_LMP_CLEARLN(void *, void *);
extern void __FA_LMP_CLEARLN(void *);

static _VARDEF	_FA_LMP_CLEARLN_in[] = {
	{ "LineNth", "",_TYPEI, 0,0,0, "Line number where to erase", "1" },
	{ "EraseMode", "",_TYPEI, 0,0,0, "1:ClearAll,2:ClearValue(Not change Bgc)", "1" },
};
static _VARDEF	_FA_LMP_CLEARLN_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "GEM Reply", "0" },
};

/* Definition for algorithm FA_LMP_DISPINT */

extern void _FA_LMP_DISPINT(void *, void *);
extern void __FA_LMP_DISPINT(void *);

static _VARDEF	_FA_LMP_DISPINT_in[] = {
	{ "LineNth", "",_TYPEI, 0,0,0, "Line number where to display", "1" },
	{ "DispLabel", "",_TYPES, 0,0,0, "Label String (Max 18 Chars)", "" },
	{ "DispValue", "",_TYPEI, 0,0,0, "Value Integer (Max 30 Chars)", "0" },
	{ "DispFgc", "",_TYPES, 0,0,0, "Foreground Color of the Value String", "default" },
	{ "DispBgc", "",_TYPES, 0,0,0, "Background Color of the Value String", "default" },
};
static _VARDEF	_FA_LMP_DISPINT_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "GEM Reply", "0" },
};

/* Definition for algorithm FA_LMP_DISPLINE */

extern void _FA_LMP_DISPLINE(void *, void *);
extern void __FA_LMP_DISPLINE(void *);

static _VARDEF	_FA_LMP_DISPLINE_in[] = {
	{ "LineNth", "",_TYPEI, 0,0,0, "Line number where to display", "1" },
	{ "DispLabel", "",_TYPES, 0,0,0, "Label String (Max 18 Chars)", "" },
	{ "DispStr", "",_TYPES, 0,0,0, "Value String (Max 30 Chars)", "" },
	{ "DispFgc", "",_TYPES, 0,0,0, "Foreground Color of the Value String", "default" },
	{ "DispBgc", "",_TYPES, 0,0,0, "Background Color of the Value String", "default" },
};
static _VARDEF	_FA_LMP_DISPLINE_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "GEM Reply", "0" },
};

/* Definition for algorithm FA_LMP_DISPVAR */

extern void _FA_LMP_DISPVAR(void *, void *);
extern void __FA_LMP_DISPVAR(void *);

static _VARDEF	_FA_LMP_DISPVAR_in[] = {
	{ "LineNth", "",_TYPEI, 0,0,0, "Line number where to display", "1" },
	{ "DispLabel", "",_TYPES, 0,0,0, "Label String (Max 18 Chars)", "" },
	{ "DispVar", "",_TYPEI, 0,0,0, "Variable ID", "0" },
	{ "DispFgc", "",_TYPES, 0,0,0, "Foreground Color of the Value String", "default" },
	{ "DispBgc", "",_TYPES, 0,0,0, "Background Color of the Value String", "default" },
};
static _VARDEF	_FA_LMP_DISPVAR_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "GEM Reply", "0" },
};

/* Definition for algorithm FA_MK_DATANAME */

extern void _FA_MK_DATANAME(void *, void *);
extern void __FA_MK_DATANAME(void *);

static _VARDEF	_FA_MK_DATANAME_in[] = {
	{ "Dir", "",_TYPES, 0,0,0, "Data Directory", "/var/opt/SPECS/data" },
	{ "File", "",_TYPES, 0,0,0, "File Directory", "WAT01" },
	{ "Slot", "",_TYPEI, 0,0,0, "SlotNumber", "1" },
	{ "Adtfmt", "",_TYPES, 0,0,0, "Adt Format", "ad3" },
	{ "Session", "",_TYPES, 0,0,0, "SessionID", "1" },
};
static _VARDEF	_FA_MK_DATANAME_out[] = {
	{ "Datadir", "",_TYPES, 0,0,0, "Data Directory Path", "" },
	{ "Dataname", "",_TYPES, 0,0,0, "Data File Name", "" },
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:Error", "0" },
};

/* Definition for algorithm FA_QUERY_COND */

extern void _FA_QUERY_COND(void *, void *);
extern void __FA_QUERY_COND(void *);

static _VARDEF	_FA_QUERY_COND_in[] = {
	{ "Key", "",_TYPES, 0,0,0, "", "" },
	{ "Level", "",_TYPES, 0,0,0, "", "" },
	{ "Filename", "",_TYPES, 0,0,0, "", "/opt/SPECS/usr/tpl/recipe.rec" },
};
static _VARDEF	_FA_QUERY_COND_out[] = {
	{ "Tco", "",_TYPES, 1,16,0, "", "" },
	{ "Limf", "",_TYPES, 0,0,0, "", "" },
	{ "DieLabel", "",_TYPES, 1,256,0, "", "" },
	{ "DieType", "",_TYPES, 1,256,0, "", "" },
	{ "ModLabel", "",_TYPES, 1,256,0, "", "" },
	{ "Item", "",_TYPES, 1,32,0, "", "" },
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File, 1: Warn", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm FA_QUERY_RCP2 */

extern void _FA_QUERY_RCP2(void *, void *);
extern void __FA_QUERY_RCP2(void *);

static _VARDEF	_FA_QUERY_RCP2_in[] = {
	{ "Key", "",_TYPES, 0,0,0, "", "" },
	{ "Filename", "",_TYPES, 0,0,0, "", "/opt/SPECS/usr/tpl/FA_recipe.rec" },
};
static _VARDEF	_FA_QUERY_RCP2_out[] = {
	{ "Waf", "",_TYPES, 0,0,0, "", "" },
	{ "Die", "",_TYPES, 1,256,0, "", "" },
	{ "Mod", "",_TYPES, 1,256,0, "", "" },
	{ "Tst", "",_TYPES, 1,256,0, "", "" },
	{ "Prb", "",_TYPES, 0,0,0, "", "" },
	{ "Lms", "",_TYPES, 1,256,0, "", "" },
	{ "Tco", "",_TYPES, 1,16,0, "", "" },
	{ "Tpl", "",_TYPES, 0,0,0, "", "" },
	{ "Lim", "",_TYPES, 0,0,0, "", "" },
	{ "Rcp", "",_TYPES, 0,0,0, "", "" },
	{ "Mlb", "",_TYPES, 1,256,0, "", "" },
	{ "Lt_id", "",_TYPES, 0,0,0, "", "" },
	{ "Pt_id", "",_TYPES, 0,0,0, "", "" },
	{ "Ps_id", "",_TYPES, 0,0,0, "", "" },
	{ "Item", "",_TYPES, 1,32,0, "", "" },
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File, 1: Warn", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm FA_QUERY_RECIP */

extern void _FA_QUERY_RECIP(void *, void *);
extern void __FA_QUERY_RECIP(void *);

static _VARDEF	_FA_QUERY_RECIP_in[] = {
	{ "Key", "",_TYPES, 0,0,0, "", "" },
	{ "Filename", "",_TYPES, 0,0,0, "", "/opt/SPECS/usr/tpl/FA_recipe.rec" },
};
static _VARDEF	_FA_QUERY_RECIP_out[] = {
	{ "Waf", "",_TYPES, 0,0,0, "", "" },
	{ "Die", "",_TYPES, 1,256,0, "", "" },
	{ "Mod", "",_TYPES, 1,256,0, "", "" },
	{ "Tst", "",_TYPES, 1,256,0, "", "" },
	{ "Prb", "",_TYPES, 0,0,0, "", "" },
	{ "Lms", "",_TYPES, 1,256,0, "", "" },
	{ "Tco", "",_TYPES, 1,16,0, "", "" },
	{ "Tpl", "",_TYPES, 0,0,0, "", "" },
	{ "Lim", "",_TYPES, 0,0,0, "", "" },
	{ "Rcp", "",_TYPES, 0,0,0, "", "" },
	{ "Lt_id", "",_TYPES, 0,0,0, "", "" },
	{ "Pt_id", "",_TYPES, 0,0,0, "", "" },
	{ "Ps_id", "",_TYPES, 0,0,0, "", "" },
	{ "Item", "",_TYPES, 1,32,0, "", "" },
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File, 1: Warn", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm FA_RCP_EXEC_CMD */

extern void _FA_RCP_EXEC_CMD(void *, void *);
extern void __FA_RCP_EXEC_CMD(void *);

static _VARDEF	_FA_RCP_EXEC_CMD_in[] = {
	{ "Cmd", "",_TYPES, 0,0,0, "", "" },
	{ "Result", "",_TYPES, 0,0,0, "", "/var/tmp/algresult" },
};
static _VARDEF	_FA_RCP_EXEC_CMD_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "Detailed error message", "" },
	{ "Cmd_ret", "",_TYPEI, 0,0,0, "Return value from Command", "0" },
};

/* Definition for algorithm FA_READ_CARD */

extern void _FA_READ_CARD(void *, void *);
extern void __FA_READ_CARD(void *);

static _VARDEF	_FA_READ_CARD_in[] = {
	{ "CardPath", "",_TYPES, 0,0,0, "", "/opt/SPECS_FA/fapt/sample" },
};
static _VARDEF	_FA_READ_CARD_out[] = {
	{ "CardType", "",_TYPES, 0,0,0, "Card Type", "" },
	{ "CardName", "",_TYPES, 0,0,0, "Card Name", "" },
	{ "TotalCount", "",_TYPER, 0,0,0, "Total Touchdown Count", "0" },
	{ "LimitCount", "",_TYPER, 0,0,0, "Limit of Touchdonw Cound", "0" },
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:Error", "0" },
};

/* Definition for algorithm FA_RUNP_CREATE */

extern void _FA_RUNP_CREATE(void *, void *);
extern void __FA_RUNP_CREATE(void *);

static _VARDEF	_FA_RUNP_CREATE_in[] = {
	{ "Meas_dir", "",_TYPES, 0,0,0, "Measurement libraly search directory", "/opt/SPECS/demo" },
	{ "Fwk_dir", "",_TYPES, 0,0,0, "Framework search directory", "/opt/SPECS/usr/fwk" },
	{ "Meas", "",_TYPES, 0,0,0, "", "DEMO.lib" },
	{ "Fwk", "",_TYPES, 0,0,0, "", "FA_TELP12.fwk" },
};
static _VARDEF	_FA_RUNP_CREATE_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm FA_TPLBLD */

extern void _FA_TPLBLD(void *, void *);
extern void __FA_TPLBLD(void *);

static _VARDEF	_FA_TPLBLD_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
	{ "Waf_dir", "",_TYPES, 0,0,0, "Wafer spec search directory", "/opt/SPECS/demo" },
	{ "Prb_dir", "",_TYPES, 0,0,0, "Probe spec search directory", "/opt/SPECS/demo" },
	{ "Die_dir", "",_TYPES, 0,0,0, "Die spec search directory", "/opt/SPECS/demo" },
	{ "Tst_dir", "",_TYPES, 0,0,0, "Test spec search directory", "/opt/SPECS/demo" },
	{ "Tpl_dir", "",_TYPES, 0,0,0, "TestPlan directory", "/opt/SPECS/demo" },
	{ "Waf", "",_TYPES, 0,0,0, "Wafer spec name to read", "TAC394.waf" },
	{ "Prb", "",_TYPES, 0,0,0, "Probe spec name to read", "PRB2X6.prb" },
	{ "Die", "",_TYPES, 1,32,0, "Die spec name to read", "" },
	{ "Tst", "",_TYPES, 1,32,0, "Test spec name to read", "" },
	{ "Tpl", "",_TYPES, 0,0,0, "Test Plan name to write", "newtpl.tpl" },
};
static _VARDEF	_FA_TPLBLD_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "detailed error message", "" },
};

/* Definition for algorithm FA_TPLBLD2 */

extern void _FA_TPLBLD2(void *, void *);
extern void __FA_TPLBLD2(void *);

static _VARDEF	_FA_TPLBLD2_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
	{ "Waf_dir", "",_TYPES, 0,0,0, "Wafer spec search directory", "/opt/SPECS/demo" },
	{ "Prb_dir", "",_TYPES, 0,0,0, "Probe spec search directory", "/opt/SPECS/demo" },
	{ "Die_dir", "",_TYPES, 0,0,0, "Die spec search directory", "/opt/SPECS/demo" },
	{ "Tst_dir", "",_TYPES, 0,0,0, "Test spec search directory", "/opt/SPECS/demo" },
	{ "Mod_dir", "",_TYPES, 0,0,0, "Test spec search directory", "/opt/SPECS/demo" },
	{ "Tpl_dir", "",_TYPES, 0,0,0, "TestPlan directory", "/opt/SPECS/demo" },
	{ "Waf", "",_TYPES, 0,0,0, "Wafer spec name to read", "TAC394.waf" },
	{ "Prb", "",_TYPES, 0,0,0, "Probe spec name to read", "PRB2X6.prb" },
	{ "Die", "",_TYPES, 1,128,0, "Die spec name to read", "" },
	{ "Tst", "",_TYPES, 1,128,0, "Test spec name to read", "" },
	{ "Mod", "",_TYPES, 1,128,0, "Module spec name to read", "" },
	{ "Tpl", "",_TYPES, 0,0,0, "Test Plan name to write", "newtpl.tpl" },
	{ "Meas", "",_TYPES, 0,0,0, "Measurement lib", "" },
	{ "Tester", "",_TYPES, 0,0,0, "Tester lib", "" },
	{ "Prober", "",_TYPES, 0,0,0, "Prober lib", "" },
	{ "Utility", "",_TYPES, 0,0,0, "Utility lib", "" },
	{ "Device", "",_TYPES, 0,0,0, "Device lib", "" },
};
static _VARDEF	_FA_TPLBLD2_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "detailed error message", "" },
};

/* Definition for algorithm FA_TPLBLD3 */

extern void _FA_TPLBLD3(void *, void *);
extern void __FA_TPLBLD3(void *);

static _VARDEF	_FA_TPLBLD3_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
	{ "Waf_dir", "",_TYPES, 0,0,0, "Wafer spec search directory", "/opt/SPECS/demo" },
	{ "Prb_dir", "",_TYPES, 0,0,0, "Probe spec search directory", "/opt/SPECS/demo" },
	{ "Die_dir", "",_TYPES, 0,0,0, "Die spec search directory", "/opt/SPECS/demo" },
	{ "Tst_dir", "",_TYPES, 0,0,0, "Test spec search directory", "/opt/SPECS/demo" },
	{ "Mod_dir", "",_TYPES, 0,0,0, "Test spec search directory", "/opt/SPECS/demo" },
	{ "Tpl_dir", "",_TYPES, 0,0,0, "TestPlan directory", "/opt/SPECS/demo" },
	{ "Waf", "",_TYPES, 0,0,0, "Wafer spec name to read", "TAC394.waf" },
	{ "Prb", "",_TYPES, 0,0,0, "Probe spec name to read", "PRB2X6.prb" },
	{ "Die", "",_TYPES, 1,256,0, "Die spec name to read", "" },
	{ "Tst", "",_TYPES, 1,256,0, "Test spec name to read", "" },
	{ "Mod", "",_TYPES, 1,256,0, "Module spec name to read", "" },
	{ "Tpl", "",_TYPES, 0,0,0, "Test Plan name to write", "newtpl.tpl" },
	{ "Meas", "",_TYPES, 1,256,0, "Measurement lib", "" },
	{ "Tester", "",_TYPES, 0,0,0, "Tester lib", "" },
	{ "Prober", "",_TYPES, 0,0,0, "Prober lib", "" },
	{ "Utility", "",_TYPES, 0,0,0, "Utility lib", "" },
	{ "Device", "",_TYPES, 0,0,0, "Device lib", "" },
};
static _VARDEF	_FA_TPLBLD3_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "detailed error message", "" },
};

/* Definition for algorithm FA_TPLFMT */

extern void _FA_TPLFMT(void *, void *);
extern void __FA_TPLFMT(void *);

static _VARDEF	_FA_TPLFMT_in[] = {
	{ "Rev_flag", "",_TYPEI, 0,0,0, "0:Revision Control not available 1:Revision Control is available", "0" },
	{ "Brk_chr", "",_TYPES, 0,0,0, "Connection char between filename and revision number", "#" },
	{ "Src_tpl_dir", "",_TYPES, 0,0,0, "Temporary file directory", "/opt/SPECS/demo" },
	{ "Script_dir", "",_TYPES, 0,0,0, "Script file directory", "/opt/SPECS/demo" },
	{ "Dst_tpl_dir", "",_TYPES, 0,0,0, "New Testplan file directory", "/opt/SPECS/demo" },
	{ "Src_tpl", "",_TYPES, 0,0,0, "Temporay Testplan File to read", "tmpsrc.tpl" },
	{ "Script", "",_TYPES, 0,0,0, "Specified script file", "sample_tpl.scr" },
	{ "Dst_tpl", "",_TYPES, 0,0,0, "Generated Testplan File to write", "tmpdst.tpl" },
};
static _VARDEF	_FA_TPLFMT_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm FA_TPL_RUN */

extern void _FA_TPL_RUN(void *, void *);
extern void __FA_TPL_RUN(void *);

static _VARDEF	_FA_TPL_RUN_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_FA_TPL_RUN_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Command status", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm FA_TPL_VERIFY */

extern void _FA_TPL_VERIFY(void *, void *);
extern void __FA_TPL_VERIFY(void *);

static _VARDEF	_FA_TPL_VERIFY_in[] = {
	{ "Revcont", "",_TYPEI, 0,0,0, "Revision Control Mode", "0" },
	{ "Revmode", "",_TYPEI, 0,0,0, "Revision Name/Number Option", "0" },
	{ "Lib", "",_TYPES, 1,256,0, "Measurement Library File (with Revision)", "" },
	{ "Libnum", "",_TYPEI, 0,0,0, "Number of Measurement Library", "6" },
	{ "Tco", "",_TYPES, 1,256,0, "Test Plan Constant File (with Revision)", "" },
	{ "Tconum", "",_TYPEI, 0,0,0, "Number of Test Plan Constant", "16" },
	{ "Tpl", "",_TYPES, 0,0,0, "Test Plan File (with Revision)", "" },
	{ "Delimiter", "",_TYPES, 0,0,0, "Delimiter between File and Revision", "#" },
};
static _VARDEF	_FA_TPL_VERIFY_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "Error Code", "0" },
	{ "Error", "",_TYPES, 0,0,0, "Error Message", "" },
};

/* Definition for algorithm FA_UPDATE_CARD */

extern void _FA_UPDATE_CARD(void *, void *);
extern void __FA_UPDATE_CARD(void *);

static _VARDEF	_FA_UPDATE_CARD_in[] = {
	{ "CardPath", "",_TYPES, 0,0,0, "Card File Directory", "/opt/SPECS_FA/fapt/sample" },
	{ "CardName", "",_TYPES, 0,0,0, "Card File Name", "cardfile" },
	{ "TotalCount", "",_TYPER, 0,0,0, "Total Touchdown Count", "255" },
};
static _VARDEF	_FA_UPDATE_CARD_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:Error", "0" },
};

/* Definition for algorithm FA_UPD_VGEMLVAR */

extern void _FA_UPD_VGEMLVAR(void *, void *);
extern void __FA_UPD_VGEMLVAR(void *);

static _VARDEF	_FA_UPD_VGEMLVAR_in[] = {
	{ "SendCEID", "",_TYPEI, 0,0,0, "CEID to Host", "0" },
	{ "VarName", "",_TYPES, 0,0,0, "Variable Name to update", "" },
	{ "VarNum", "",_TYPEI, 0,0,0, "Num of Data", "0" },
	{ "VarData", "",_TYPES, 1,32,0, "New Data List(MAX 32 elements)", "" },
};
static _VARDEF	_FA_UPD_VGEMLVAR_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "GEM Reply", "0" },
};

/* Definition for algorithm FA_UPD_VGEMVAR */

extern void _FA_UPD_VGEMVAR(void *, void *);
extern void __FA_UPD_VGEMVAR(void *);

static _VARDEF	_FA_UPD_VGEMVAR_in[] = {
	{ "SendCEID", "",_TYPEI, 0,0,0, "CEID to Host", "0" },
	{ "VarName", "",_TYPES, 0,0,0, "Variable Name to update", "" },
	{ "VarData", "",_TYPES, 0,0,0, "New Data", "" },
};
static _VARDEF	_FA_UPD_VGEMVAR_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "GEM Reply", "0" },
};

/* Definition for algorithm FA_WAFERDUMP */

extern void _FA_WAFERDUMP(void *, void *);
extern void __FA_WAFERDUMP(void *);

static _VARDEF	_FA_WAFERDUMP_in[] = {
	{ "Dir", "",_TYPES, 0,0,0, "Data Directory", "/var/opt/SPECS/data" },
	{ "File", "",_TYPES, 0,0,0, "File Directory", "WAT01" },
	{ "Slot", "",_TYPEI, 0,0,0, "SlotNumber", "1" },
	{ "Adtfmt", "",_TYPES, 0,0,0, "Adt Format", "ad3" },
	{ "Session", "",_TYPES, 0,0,0, "SessionID", "1" },
};
static _VARDEF	_FA_WAFERDUMP_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:Error", "0" },
};

/* Definition for algorithm FA_WAIT */

extern void _FA_WAIT(void *, void *);
extern void __FA_WAIT(void *);

static _VARDEF	_FA_WAIT_in[] = {
	{ "Time", "",_TYPEI, 0,0,0, "", "1" },
};

/* Definition for algorithm FILE_HWCONFIG */

extern void _FILE_HWCONFIG(void *, void *);
extern void __FILE_HWCONFIG(void *);

static _VARDEF	_FILE_HWCONFIG_in[] = {
	{ "File", "",_TYPES, 0,0,0, "", "" },
	{ "Config", "",_TYPES, 1,50,0, "", "" },
};

/* Definition for algorithm FILE_LOOKUP */

extern void _FILE_LOOKUP(void *, void *);
extern void __FILE_LOOKUP(void *);

static _VARDEF	_FILE_LOOKUP_in[] = {
	{ "Dir", "",_TYPES, 0,0,0, "Search directory name", "" },
	{ "Suffix", "",_TYPES, 0,0,0, "Suffix", "tpl" },
};
static _VARDEF	_FILE_LOOKUP_out[] = {
	{ "Files", "",_TYPES, 1,1024,0, "Found files", "" },
	{ "Count", "",_TYPEI, 0,0,0, "Number of found files", "0" },
	{ "Depth", "",_TYPEI, 0,0,0, "Max directory depth + 1", "0" },
};

/* Definition for algorithm FORMAT_PATH */

extern void _FORMAT_PATH(void *, void *);
extern void __FORMAT_PATH(void *);

static _VARDEF	_FORMAT_PATH_in[] = {
	{ "Original", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_FORMAT_PATH_out[] = {
	{ "Path", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm GEM_GETCMD */

extern void _GEM_GETCMD(void *, void *);
extern void __GEM_GETCMD(void *);

static _VARDEF	_GEM_GETCMD_out[] = {
	{ "Cmd", "",_TYPES, 0,0,0, "Command", "" },
	{ "Rply", "",_TYPES, 0,0,0, "Reply string", "" },
	{ "Parms", "",_TYPES, 1,500,0, "", "" },
};

/* Definition for algorithm GEM_INIT */

extern void _GEM_INIT(void *, void *);
extern void __GEM_INIT(void *);

static _VARDEF	_GEM_INIT_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm GEM_RESPOND_NOK */

extern void _GEM_RESPOND_NOK(void *, void *);
extern void __GEM_RESPOND_NOK(void *);

static _VARDEF	_GEM_RESPOND_NOK_in[] = {
	{ "ReplyMailbox", "",_TYPES, 0,0,0, "", "Reply" },
};
static _VARDEF	_GEM_RESPOND_NOK_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:Error", "0" },
};

/* Definition for algorithm GEM_RESPOND_OK */

extern void _GEM_RESPOND_OK(void *, void *);
extern void __GEM_RESPOND_OK(void *);

static _VARDEF	_GEM_RESPOND_OK_in[] = {
	{ "ReplyMailbox", "",_TYPES, 0,0,0, "", "Reply" },
	{ "Timeout", "",_TYPER, 0,0,0, "", "10" },
};
static _VARDEF	_GEM_RESPOND_OK_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0:OK -1:Error", "0" },
};

/* Definition for algorithm GEM_SENDEVENT */

extern void _GEM_SENDEVENT(void *, void *);
extern void __GEM_SENDEVENT(void *);

static _VARDEF	_GEM_SENDEVENT_in[] = {
	{ "Event", "",_TYPES, 0,0,0, "Event name", "PROBERRCP" },
	{ "Parms", "",_TYPES, 1,500,0, "", "" },
};
static _VARDEF	_GEM_SENDEVENT_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "GEM Reply", "0" },
};

/* Definition for algorithm GET_BRK_MOD */

extern void _GET_BRK_MOD(void *, void *);
extern void __GET_BRK_MOD(void *);

static _VARDEF	_GET_BRK_MOD_in[] = {
	{ "Typeindex", "",_TYPEI, 0,0,0, "Die type index (DIE.TYPENUMBER)", "1" },
	{ "Dieindex", "",_TYPEI, 0,0,0, "Die index in die type (DIE.NUMBER)", "1" },
	{ "Modindex", "",_TYPEI, 0,0,0, "Module index (MODULE.NUMBER)", "1" },
};
static _VARDEF	_GET_BRK_MOD_out[] = {
	{ "Break", "",_TYPEI, 0,0,0, "1: Break, 0: Unbreak, -1: Error", "0" },
};

/* Definition for algorithm GET_DIELABEL */

extern void _GET_DIELABEL(void *, void *);
extern void __GET_DIELABEL(void *);

static _VARDEF	_GET_DIELABEL_out[] = {
	{ "Label", "",_TYPES, 0,0,0, "Die label", "" },
};

/* Definition for algorithm GET_DIETYPE */

extern void _GET_DIETYPE(void *, void *);
extern void __GET_DIETYPE(void *);

static _VARDEF	_GET_DIETYPE_out[] = {
	{ "Type", "",_TYPES, 0,0,0, "Die label", "" },
};

/* Definition for algorithm GET_JDG_DIE */

extern void _GET_JDG_DIE(void *, void *);
extern void __GET_JDG_DIE(void *);

static _VARDEF	_GET_JDG_DIE_in[] = {
	{ "Typeindex", "",_TYPEI, 0,0,0, "Die type index (DIE.TYPENUMBER)", "1" },
	{ "Dieindex", "",_TYPEI, 0,0,0, "Die index in die type (DIE.NUMBER)", "1" },
};
static _VARDEF	_GET_JDG_DIE_out[] = {
	{ "Judge", "",_TYPEI, 0,0,0, "Judgement value.", "1" },
	{ "Offsetx", "",_TYPEI, 0,0,0, "Die X position offset.", "0" },
	{ "Offsety", "",_TYPEI, 0,0,0, "Die Y position offset.", "0" },
};

/* Definition for algorithm GET_LOC_MOD */

extern void _GET_LOC_MOD(void *, void *);
extern void __GET_LOC_MOD(void *);

static _VARDEF	_GET_LOC_MOD_in[] = {
	{ "Typeindex", "",_TYPEI, 0,0,0, "Die type index (DIE.TYPENUMBER). \"0\" is an error case.", "1" },
	{ "Modname", "",_TYPES, 0,0,0, "Module name.", "" },
};
static _VARDEF	_GET_LOC_MOD_out[] = {
	{ "X", "um",_TYPER, 0,0,0, "X Position", "0" },
	{ "Y", "um",_TYPER, 0,0,0, "Y Position", "0" },
	{ "Stat", "",_TYPEI, 0,0,0, "0:No error, -1:Error", "0" },
};

/* Definition for algorithm GET_MODLABEL */

extern void _GET_MODLABEL(void *, void *);
extern void __GET_MODLABEL(void *);

static _VARDEF	_GET_MODLABEL_out[] = {
	{ "Label", "",_TYPES, 0,0,0, "Module label", "" },
};

/* Definition for algorithm GET_NEXT_MOD */

extern void _GET_NEXT_MOD(void *, void *);
extern void __GET_NEXT_MOD(void *);

static _VARDEF	_GET_NEXT_MOD_in[] = {
	{ "Typeindex_c", "",_TYPEI, 0,0,0, "Current type index.", "0" },
	{ "Diex_c", "",_TYPEI, 0,0,0, "Current die x.", "0" },
	{ "Diey_c", "",_TYPEI, 0,0,0, "Current die y.", "0" },
	{ "Modname_c", "",_TYPES, 0,0,0, "Current module name.", "" },
};
static _VARDEF	_GET_NEXT_MOD_out[] = {
	{ "Typeindex", "",_TYPEI, 0,0,0, "Next die type w/ failed module.", "0" },
	{ "Diex", "",_TYPEI, 0,0,0, "Next die x w/ failed module.", "0" },
	{ "Diey", "",_TYPEI, 0,0,0, "Next die y w/ failed module.", "0" },
	{ "Modname", "",_TYPES, 0,0,0, "Next failed module name.", "" },
	{ "Stat", "",_TYPEI, 0,0,0, "0:ok/-1:error", "0" },
};

/* Definition for algorithm GET_PREV_MOD */

extern void _GET_PREV_MOD(void *, void *);
extern void __GET_PREV_MOD(void *);

static _VARDEF	_GET_PREV_MOD_in[] = {
	{ "Typeindex_c", "",_TYPEI, 0,0,0, "Current type index.", "0" },
	{ "Diex_c", "",_TYPEI, 0,0,0, "Current die x.", "0" },
	{ "Diey_c", "",_TYPEI, 0,0,0, "Current die y.", "0" },
	{ "Modname_c", "",_TYPES, 0,0,0, "Current module name.", "" },
};
static _VARDEF	_GET_PREV_MOD_out[] = {
	{ "Typeindex", "",_TYPEI, 0,0,0, "Prev die type w/ failed module.", "0" },
	{ "Diex", "",_TYPEI, 0,0,0, "Prev die x w/ failed module.", "0" },
	{ "Diey", "",_TYPEI, 0,0,0, "Prev die y w/ failed module.", "0" },
	{ "Modname", "",_TYPES, 0,0,0, "Prev failed module name.", "" },
	{ "Stat", "",_TYPEI, 0,0,0, "0:ok/-1:error", "0" },
};

/* Definition for algorithm GET_SLOT_NO */

extern void _GET_SLOT_NO(void *, void *);
extern void __GET_SLOT_NO(void *);

static _VARDEF	_GET_SLOT_NO_in[] = {
	{ "Lotid", "",_TYPES, 0,0,0, "", "" },
	{ "Waferid", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_GET_SLOT_NO_out[] = {
	{ "Slotno", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm GET_VGEMDEFAULT */

extern void _GET_VGEMDEFAULT(void *, void *);
extern void __GET_VGEMDEFAULT(void *);

static _VARDEF	_GET_VGEMDEFAULT_out[] = {
	{ "Rcpmode", "",_TYPES, 0,0,0, "", "" },
	{ "Rcpfilename", "",_TYPES, 0,0,0, "", "" },
	{ "Status", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm G_CV */

extern void _G_CV(void *, void *);
extern void __G_CV(void *);

static _VARDEF	_G_CV_in[] = {
	{ "Vstart", "V",_TYPER, 0,0,0, "Inversion voltage", "-5" },
	{ "Vstop", "V",_TYPER, 0,0,0, "Accumulation voltage", "5" },
	{ "Vstep", "V",_TYPER, 0,0,0, "Step voltage", "0.1" },
	{ "Delay", "sec",_TYPER, 0,0,0, "Step delay time", "0.1" },
	{ "Hold", "sec",_TYPER, 0,0,0, "Hold time", "30" },
};
static _VARDEF	_G_CV_trm[] = {
	{ "H", "",_TYPEI, 0,0,0, "", "0" },
	{ "L", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm G_HFE */

extern void _G_HFE(void *, void *);
extern void __G_HFE(void *);

static _VARDEF	_G_HFE_in[] = {
	{ "Ibestart", "A",_TYPER, 0,0,0, "Base start current", "1E-12" },
	{ "Ibestop", "A",_TYPER, 0,0,0, "Base stop current", "0.0005" },
	{ "Ibestep", "",_TYPEI, 0,0,0, "Base number of steps", "25" },
	{ "Vce", "V",_TYPER, 0,0,0, "Collector voltage", "5" },
};
static _VARDEF	_G_HFE_trm[] = {
	{ "E", "",_TYPEI, 0,0,0, "", "0" },
	{ "B", "",_TYPEI, 0,0,0, "", "0" },
	{ "C", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm G_ICVB */

extern void _G_ICVB(void *, void *);
extern void __G_ICVB(void *);

static _VARDEF	_G_ICVB_in[] = {
	{ "Vbestart", "V",_TYPER, 0,0,0, "Base start voltage", "0" },
	{ "Vbestop", "V",_TYPER, 0,0,0, "Base stop voltage", "1" },
	{ "Vbestep", "V",_TYPER, 0,0,0, "Base step voltage", "0.01" },
};
static _VARDEF	_G_ICVB_trm[] = {
	{ "E", "",_TYPEI, 0,0,0, "", "0" },
	{ "B", "",_TYPEI, 0,0,0, "", "0" },
	{ "C", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm G_ICVC */

extern void _G_ICVC(void *, void *);
extern void __G_ICVC(void *);

static _VARDEF	_G_ICVC_in[] = {
	{ "Vcestart", "V",_TYPER, 0,0,0, "Collector start voltage", "0" },
	{ "Vcestop", "V",_TYPER, 0,0,0, "Collector stop voltage", "5" },
	{ "Vcestep", "V",_TYPER, 0,0,0, "Collector step voltage", "0.1" },
	{ "Ibstart", "A",_TYPER, 0,0,0, "Base start current", "1E-05" },
	{ "Ibstop", "A",_TYPER, 0,0,0, "Base stop current", "5E-05" },
	{ "Ibstep", "A",_TYPER, 0,0,0, "Base step current", "1E-05" },
};
static _VARDEF	_G_ICVC_trm[] = {
	{ "E", "",_TYPEI, 0,0,0, "", "0" },
	{ "B", "",_TYPEI, 0,0,0, "", "0" },
	{ "C", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm G_IDVD */

extern void _G_IDVD(void *, void *);
extern void __G_IDVD(void *);

static _VARDEF	_G_IDVD_in[] = {
	{ "Vdstart", "V",_TYPER, 0,0,0, "Drain start voltage", "0" },
	{ "Vdstop", "V",_TYPER, 0,0,0, "Drain stop voltage", "20" },
	{ "Vdstep", "V",_TYPER, 0,0,0, "Drain step voltage", "0.25" },
	{ "Vgstart", "V",_TYPER, 0,0,0, "Gate start voltage", "3" },
	{ "Vgstop", "V",_TYPER, 0,0,0, "Gate stop voltage", "6" },
	{ "Vgstep", "V",_TYPER, 0,0,0, "Gate step voltage", "1" },
};
static _VARDEF	_G_IDVD_trm[] = {
	{ "S", "",_TYPEI, 0,0,0, "", "0" },
	{ "G", "",_TYPEI, 0,0,0, "Gate terminal", "0" },
	{ "D", "",_TYPEI, 0,0,0, "Drain terminal", "0" },
	{ "Sub", "",_TYPEI, 0,0,0, "Substrate terminal", "0" },
};

/* Definition for algorithm G_IDVG */

extern void _G_IDVG(void *, void *);
extern void __G_IDVG(void *);

static _VARDEF	_G_IDVG_in[] = {
	{ "Vgstart", "V",_TYPER, 0,0,0, "Gate start voltage", "0" },
	{ "Vgstop", "V",_TYPER, 0,0,0, "Gate stop voltage", "5" },
	{ "Vgstep", "V",_TYPER, 0,0,0, "Gate step voltage", "0.05" },
	{ "Vsubstart", "V",_TYPER, 0,0,0, "Substrate start voltage", "0" },
	{ "Vsubstop", "V",_TYPER, 0,0,0, "Substrate stop voltage", "-1.2" },
	{ "Vsubstep", "V",_TYPER, 0,0,0, "Substrate step voltage", "-0.4" },
	{ "Vd", "V",_TYPER, 0,0,0, "Drain voltage", "5" },
};
static _VARDEF	_G_IDVG_trm[] = {
	{ "S", "",_TYPEI, 0,0,0, "", "0" },
	{ "G", "",_TYPEI, 0,0,0, "Gate terminal", "0" },
	{ "D", "",_TYPEI, 0,0,0, "Drain terminal", "0" },
	{ "Sub", "",_TYPEI, 0,0,0, "Substrate terminal", "0" },
};

/* Definition for algorithm IS_CALG */

extern void _IS_CALG(void *, void *);
extern void __IS_CALG(void *);

static _VARDEF	_IS_CALG_out[] = {
	{ "Lang", "",_TYPEI, 0,0,0, "BASIC:0, C:1", "0" },
};

/* Definition for algorithm IS_FIRST */

extern void _IS_FIRST(void *, void *);
extern void __IS_FIRST(void *);

static _VARDEF	_IS_FIRST_out[] = {
	{ "First", "",_TYPEI, 0,0,0, "", "1" },
};

/* Definition for algorithm JDG_DIE */

extern void _JDG_DIE(void *, void *);
extern void __JDG_DIE(void *);

static _VARDEF	_JDG_DIE_in[] = {
	{ "Tgt_yld", "",_TYPEI, 0,0,0, "target parameter yield to be passed", "100" },
	{ "Last", "",_TYPEI, 0,0,0, "all test are finished or not", "0" },
	{ "Critical", "",_TYPEI, 0,0,0, "user flag index as \"critical\" parameter flag.", "0" },
	{ "Ignore", "",_TYPEI, 0,0,0, "user flag index as \"ignored\" parameter flag.", "0" },
};
static _VARDEF	_JDG_DIE_out[] = {
	{ "Jdg", "",_TYPEI, 0,0,0, "0:fail/1:pass/2:unknown", "0" },
	{ "Yld", "",_TYPER, 0,0,0, "parameter yield", "0" },
	{ "Pass_cnt", "",_TYPEI, 0,0,0, "pass count of parameter", "0" },
	{ "Fail_cnt", "",_TYPEI, 0,0,0, "fail count of parameter", "0" },
	{ "Total_cnt", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm JDG_DIE_AT_POS */

extern void _JDG_DIE_AT_POS(void *, void *);
extern void __JDG_DIE_AT_POS(void *);

static _VARDEF	_JDG_DIE_AT_POS_in[] = {
	{ "Die_pos", "",_TYPEI, 0,0,0, "index of die", "0" },
	{ "Tgt_yld", "",_TYPEI, 0,0,0, "target parameter yield to be passed", "100" },
	{ "Last", "",_TYPEI, 0,0,0, "all test are finished or not", "0" },
};
static _VARDEF	_JDG_DIE_AT_POS_out[] = {
	{ "Jdg", "",_TYPEI, 0,0,0, "0:fail/1:pass/2:unknown", "0" },
	{ "Yld", "",_TYPER, 0,0,0, "parameter yield", "0" },
	{ "Pass_cnt", "",_TYPEI, 0,0,0, "pass count of parameter", "0" },
	{ "Fail_cnt", "",_TYPEI, 0,0,0, "fail count of parameter", "0" },
	{ "Total_cnt", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm JDG_DIE_AT_POS2 */

extern void _JDG_DIE_AT_POS2(void *, void *);
extern void __JDG_DIE_AT_POS2(void *);

static _VARDEF	_JDG_DIE_AT_POS2_in[] = {
	{ "Die_pos", "",_TYPEI, 0,0,0, "index of die", "0" },
	{ "Tgt_yld", "",_TYPEI, 0,0,0, "target parameter yield to be passed", "100" },
	{ "Last", "",_TYPEI, 0,0,0, "all test are finished or not", "0" },
	{ "Critical", "",_TYPEI, 0,0,0, "user flag index as \"critical\" parameter flag.", "0" },
	{ "Ignore", "",_TYPEI, 0,0,0, "user flag index as \"ignored\" parameter flag.", "0" },
};
static _VARDEF	_JDG_DIE_AT_POS2_out[] = {
	{ "Jdg", "",_TYPEI, 0,0,0, "0:fail/1:pass/2:unknown", "0" },
	{ "Yld", "",_TYPER, 0,0,0, "parameter yield", "0" },
	{ "Pass_cnt", "",_TYPEI, 0,0,0, "pass count of parameter", "0" },
	{ "Fail_cnt", "",_TYPEI, 0,0,0, "fail count of parameter", "0" },
	{ "Total_cnt", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm JDG_MOD */

extern void _JDG_MOD(void *, void *);
extern void __JDG_MOD(void *);

static _VARDEF	_JDG_MOD_in[] = {
	{ "Ignore", "",_TYPEI, 0,0,0, "user flag index as \"ignored\" parameter flag.", "0" },
};
static _VARDEF	_JDG_MOD_out[] = {
	{ "Jdg", "",_TYPEI, 0,0,0, "0:fail/1:pass/2:unknown", "0" },
	{ "Pass_cnt", "",_TYPEI, 0,0,0, "pass count of item", "0" },
	{ "Fail_cnt", "",_TYPEI, 0,0,0, "fail count of item", "0" },
	{ "Total_cnt", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm JDG_MOD_AT_POS */

extern void _JDG_MOD_AT_POS(void *, void *);
extern void __JDG_MOD_AT_POS(void *);

static _VARDEF	_JDG_MOD_AT_POS_in[] = {
	{ "Die_pos", "",_TYPEI, 0,0,0, "index of die", "0" },
	{ "Mod_pos", "",_TYPEI, 0,0,0, "Index of module", "0" },
	{ "Ignore", "",_TYPEI, 0,0,0, "user flag index as \"ignored\" parameter flag.", "0" },
};
static _VARDEF	_JDG_MOD_AT_POS_out[] = {
	{ "Jdg", "",_TYPEI, 0,0,0, "0:fail/1:pass/2:unknown", "0" },
	{ "Pass_cnt", "",_TYPEI, 0,0,0, "pass count of item", "0" },
	{ "Fail_cnt", "",_TYPEI, 0,0,0, "fail count of item", "0" },
	{ "Total_cnt", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm JDG_WAF_BY_DIE */

extern void _JDG_WAF_BY_DIE(void *, void *);
extern void __JDG_WAF_BY_DIE(void *);

static _VARDEF	_JDG_WAF_BY_DIE_in[] = {
	{ "Tgt_wafyld", "",_TYPEI, 0,0,0, "target parameter yield to be passed", "100" },
	{ "Tgt_dieyld", "",_TYPEI, 0,0,0, "", "100" },
	{ "Last", "",_TYPEI, 0,0,0, "all test are finished or not", "0" },
};
static _VARDEF	_JDG_WAF_BY_DIE_out[] = {
	{ "Jdg", "",_TYPEI, 0,0,0, "0:fail/1:pass/2:unknown", "0" },
	{ "Yld", "",_TYPER, 0,0,0, "die yield", "0" },
	{ "Pass_cnt", "",_TYPEI, 0,0,0, "pass count of die", "0" },
	{ "Fail_cnt", "",_TYPEI, 0,0,0, "fail count of die", "0" },
	{ "Total_cnt", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm JDG_WAF_BY_PARA */

extern void _JDG_WAF_BY_PARA(void *, void *);
extern void __JDG_WAF_BY_PARA(void *);

static _VARDEF	_JDG_WAF_BY_PARA_in[] = {
	{ "Tgt_yld", "",_TYPEI, 0,0,0, "target parameter yield to be passed", "100" },
	{ "Last", "",_TYPEI, 0,0,0, "all test are finished or not", "0" },
	{ "Critical", "",_TYPEI, 0,0,0, "user flag index as \"critical\" parameter flag.", "0" },
	{ "Ignore", "",_TYPEI, 0,0,0, "user flag index as \"ignored\" parameter flag.", "0" },
};
static _VARDEF	_JDG_WAF_BY_PARA_out[] = {
	{ "Jdg", "",_TYPEI, 0,0,0, "0:fail/1:pass/2:unknown", "0" },
	{ "Yld", "",_TYPER, 0,0,0, "parameter yield", "0" },
	{ "Pass_cnt", "",_TYPEI, 0,0,0, "pass count of parameter", "0" },
	{ "Fail_cnt", "",_TYPEI, 0,0,0, "fail count of parameter", "0" },
	{ "Total_cnt", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm LOG_LOT_BEGIN */

extern void _LOG_LOT_BEGIN(void *, void *);
extern void __LOG_LOT_BEGIN(void *);

static _VARDEF	_LOG_LOT_BEGIN_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "", "" },
	{ "Lotid", "",_TYPES, 0,0,0, "", "" },
	{ "Testplan", "",_TYPES, 0,0,0, "", "" },
	{ "Algorithm", "",_TYPES, 0,0,0, "", "" },
	{ "Limitfile", "",_TYPES, 0,0,0, "", "" },
	{ "Operator", "",_TYPES, 0,0,0, "", "" },
	{ "Date", "",_TYPES, 0,0,0, "", "" },
	{ "Time", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm LOG_LOT_END */

extern void _LOG_LOT_END(void *, void *);
extern void __LOG_LOT_END(void *);

static _VARDEF	_LOG_LOT_END_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "", "" },
	{ "State", "",_TYPES, 0,0,0, "", "" },
	{ "Result", "",_TYPEI, 0,0,0, "", "0" },
	{ "Datadir", "",_TYPES, 0,0,0, "", "" },
	{ "Dataname", "",_TYPES, 0,0,0, "", "" },
	{ "Time", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm LOG_PROBER */

extern void _LOG_PROBER(void *, void *);
extern void __LOG_PROBER(void *);

static _VARDEF	_LOG_PROBER_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "", "" },
	{ "Message", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm LOG_SYSTEM */

extern void _LOG_SYSTEM(void *, void *);
extern void __LOG_SYSTEM(void *);

static _VARDEF	_LOG_SYSTEM_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "", "" },
	{ "Message", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm LOG_TIMESTAMP */

extern void _LOG_TIMESTAMP(void *, void *);
extern void __LOG_TIMESTAMP(void *);

static _VARDEF	_LOG_TIMESTAMP_out[] = {
	{ "Timestamp", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm LOG_WAFER_BEGIN */

extern void _LOG_WAFER_BEGIN(void *, void *);
extern void __LOG_WAFER_BEGIN(void *);

static _VARDEF	_LOG_WAFER_BEGIN_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "", "" },
	{ "Waferid", "",_TYPES, 0,0,0, "", "" },
	{ "Time", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm LOG_WAFER_END */

extern void _LOG_WAFER_END(void *, void *);
extern void __LOG_WAFER_END(void *);

static _VARDEF	_LOG_WAFER_END_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "", "" },
	{ "State", "",_TYPES, 0,0,0, "", "" },
	{ "Result", "",_TYPEI, 0,0,0, "", "0" },
	{ "Time", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm MASTER_LOOKUP */

extern void _MASTER_LOOKUP(void *, void *);
extern void __MASTER_LOOKUP(void *);

static _VARDEF	_MASTER_LOOKUP_in[] = {
	{ "File", "",_TYPES, 0,0,0, "Master filename", "" },
	{ "Key", "",_TYPES, 0,0,0, "Key string", "" },
	{ "Fnum", "",_TYPEI, 0,0,0, "Field number, 1 ~ 199", "1" },
};
static _VARDEF	_MASTER_LOOKUP_out[] = {
	{ "Field", "",_TYPES, 0,0,0, "Extracted field", "" },
	{ "Stat", "",_TYPEI, 0,0,0, "0(ok),-1(no key),-2(invalid),-3(no file)", "0" },
};

/* Definition for algorithm MERGE_DATAFILE */

extern void _MERGE_DATAFILE(void *, void *);
extern void __MERGE_DATAFILE(void *);

static _VARDEF	_MERGE_DATAFILE_in[] = {
	{ "Original", "",_TYPES, 0,0,0, "", "" },
	{ "New", "",_TYPES, 0,0,0, "", "" },
	{ "Format", "",_TYPES, 0,0,0, "", "" },
	{ "Numwaf", "",_TYPEI, 0,0,0, "", "0" },
	{ "Waferid", "",_TYPES, 1,50,0, "", "" },
};
static _VARDEF	_MERGE_DATAFILE_out[] = {
	{ "Stat", "",_TYPEI, 0,0,0, "", "0" },
	{ "Error", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm NAME_TMPDATA */

extern void _NAME_TMPDATA(void *, void *);
extern void __NAME_TMPDATA(void *);

static _VARDEF	_NAME_TMPDATA_in[] = {
	{ "Basename", "",_TYPES, 0,0,0, "", "" },
	{ "Session", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_NAME_TMPDATA_out[] = {
	{ "Tmpname", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm PRBCOUNT */

extern void _PRBCOUNT(void *, void *);
extern void __PRBCOUNT(void *);

static _VARDEF	_PRBCOUNT_out[] = {
	{ "Count", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm PRBINFO */

extern void _PRBINFO(void *, void *);
extern void __PRBINFO(void *);

static _VARDEF	_PRBINFO_in[] = {
	{ "Index", "",_TYPEI, 0,0,0, "", "0" },
};
static _VARDEF	_PRBINFO_out[] = {
	{ "Pad", "",_TYPEI, 0,0,0, "", "-1" },
	{ "Pin", "",_TYPEI, 0,0,0, "", "-1" },
};

/* Definition for algorithm PRINT */

extern void _PRINT(void *, void *);
extern void __PRINT(void *);

static _VARDEF	_PRINT_in[] = {
	{ "S", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm PRINT_CHAR */

extern void _PRINT_CHAR(void *, void *);
extern void __PRINT_CHAR(void *);

static _VARDEF	_PRINT_CHAR_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%c" },
	{ "Value", "",_TYPEC, 0,0,0, "Value to convert", " " },
};

/* Definition for algorithm PRINT_INTEGER */

extern void _PRINT_INTEGER(void *, void *);
extern void __PRINT_INTEGER(void *);

static _VARDEF	_PRINT_INTEGER_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%d" },
	{ "Value", "",_TYPEI, 0,0,0, "Value to convert", "0" },
};

/* Definition for algorithm PRINT_REAL */

extern void _PRINT_REAL(void *, void *);
extern void __PRINT_REAL(void *);

static _VARDEF	_PRINT_REAL_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%e" },
	{ "Value", "",_TYPER, 0,0,0, "Value to convert", "0" },
};

/* Definition for algorithm PRINT_STRING */

extern void _PRINT_STRING(void *, void *);
extern void __PRINT_STRING(void *);

static _VARDEF	_PRINT_STRING_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%s" },
	{ "Value", "",_TYPES, 0,0,0, "Value to convert", "" },
};

/* Definition for algorithm QUERY_DIR */

extern void _QUERY_DIR(void *, void *);
extern void __QUERY_DIR(void *);

static _VARDEF	_QUERY_DIR_in[] = {
	{ "Dir", "",_TYPES, 0,0,0, "Opened directory.", "/var/opt/SPECS/data" },
};
static _VARDEF	_QUERY_DIR_out[] = {
	{ "Stat", "",_TYPEI, 0,0,0, "0:ok, -1:not found", "0" },
};

/* Definition for algorithm QUERY_FILE */

extern void _QUERY_FILE(void *, void *);
extern void __QUERY_FILE(void *);

static _VARDEF	_QUERY_FILE_in[] = {
	{ "File", "",_TYPES, 0,0,0, "Opened file.", "" },
};
static _VARDEF	_QUERY_FILE_out[] = {
	{ "Stat", "",_TYPEI, 0,0,0, "0:ok, -1:not found", "0" },
};

/* Definition for algorithm QUERY_GRAPH */

extern void _QUERY_GRAPH(void *, void *);
extern void __QUERY_GRAPH(void *);

static _VARDEF	_QUERY_GRAPH_in[] = {
	{ "Filter", "",_TYPEI, 0,0,0, "Filter item.", "0" },
	{ "Type", "",_TYPEI, 0,0,0, "0:XY, 1:Hist, 2:WaferMap", "0" },
	{ "Unit", "",_TYPEI, 0,0,0, "0:Lot, 1:Wafer, 2:Die", "0" },
	{ "Variable", "",_TYPES, 0,0,0, "Output variable name.", "" },
	{ "Update", "",_TYPEI, 0,0,0, "0:New, 1:Update", "0" },
};

/* Definition for algorithm QUERY_LAUNCH */

extern void _QUERY_LAUNCH(void *, void *);
extern void __QUERY_LAUNCH(void *);

static _VARDEF	_QUERY_LAUNCH_in[] = {
	{ "Session", "",_TYPES, 0,0,0, "Session ID", "1" },
	{ "Port", "",_TYPES, 0,0,0, "Port ID", "14062" },
	{ "Project", "",_TYPES, 0,0,0, "Project ID", "v" },
	{ "Hostname", "",_TYPES, 0,0,0, "Hostname", "" },
};

/* Definition for algorithm QUERY_START */

extern void _QUERY_START(void *, void *);
extern void __QUERY_START(void *);


/* Definition for algorithm QUERY_STOP */

extern void _QUERY_STOP(void *, void *);
extern void __QUERY_STOP(void *);


/* Definition for algorithm QUERY_VIEW */

extern void _QUERY_VIEW(void *, void *);
extern void __QUERY_VIEW(void *);

static _VARDEF	_QUERY_VIEW_in[] = {
	{ "Variable", "",_TYPES, 0,0,0, "Output variable name.", "" },
	{ "Update", "",_TYPEI, 0,0,0, "0:New, 1:Update", "0" },
};

/* Definition for algorithm RCP_CHECK_KEY */

extern void _RCP_CHECK_KEY(void *, void *);
extern void __RCP_CHECK_KEY(void *);

static _VARDEF	_RCP_CHECK_KEY_in[] = {
	{ "Filename", "",_TYPES, 0,0,0, "", "/opt/SPECS/usr/tpl/recipe.rec" },
};
static _VARDEF	_RCP_CHECK_KEY_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Err, -2: No File", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
	{ "Dupkey", "",_TYPES, 0,0,0, "Duplicated key", "" },
};

/* Definition for algorithm RCP_DIETST */

extern void _RCP_DIETST(void *, void *);
extern void __RCP_DIETST(void *);

static _VARDEF	_RCP_DIETST_in[] = {
	{ "Die", "",_TYPES, 1,256,0, "", "" },
	{ "Tst", "",_TYPES, 1,256,0, "", "" },
	{ "Rule", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_RCP_DIETST_out[] = {
	{ "Die_tst", "",_TYPES, 1,256,0, "", "" },
	{ "Status", "",_TYPEI, 0,0,0, "0: Ok", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm RCP_EXEC_CMD */

extern void _RCP_EXEC_CMD(void *, void *);
extern void __RCP_EXEC_CMD(void *);

static _VARDEF	_RCP_EXEC_CMD_in[] = {
	{ "Cmd", "",_TYPES, 0,0,0, "", "" },
	{ "Result", "",_TYPES, 0,0,0, "", "/var/tmp/algresult" },
};
static _VARDEF	_RCP_EXEC_CMD_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "Detailed error message", "" },
	{ "Cmd_ret", "",_TYPEI, 0,0,0, "Return value from Command", "0" },
};

/* Definition for algorithm RCP_LIMBLD */

extern void _RCP_LIMBLD(void *, void *);
extern void __RCP_LIMBLD(void *);

static _VARDEF	_RCP_LIMBLD_in[] = {
	{ "Tpl_dir", "",_TYPES, 0,0,0, "", "/var/opt/SPECS/recipe" },
	{ "Lms_dir", "",_TYPES, 0,0,0, "", "/opt/SPECS/demo" },
	{ "Lim_dir", "",_TYPES, 0,0,0, "", "/var/opt/SPECS/recipe" },
	{ "Tpl", "",_TYPES, 0,0,0, "", "testplan.tpl" },
	{ "Lms", "",_TYPES, 1,256,0, "", "" },
	{ "Lim", "",_TYPES, 0,0,0, "", "limit.lim" },
};
static _VARDEF	_RCP_LIMBLD_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "Detailed error message", "" },
};

/* Definition for algorithm RCP_MK_FILENAME */

extern void _RCP_MK_FILENAME(void *, void *);
extern void __RCP_MK_FILENAME(void *);

static _VARDEF	_RCP_MK_FILENAME_in[] = {
	{ "Dirname", "",_TYPES, 0,0,0, "", "" },
	{ "Filename", "",_TYPES, 0,0,0, "", "" },
	{ "Suffix", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_RCP_MK_FILENAME_out[] = {
	{ "Fullfile", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm RCP_QUERY_RECIP */

extern void _RCP_QUERY_RECIP(void *, void *);
extern void __RCP_QUERY_RECIP(void *);

static _VARDEF	_RCP_QUERY_RECIP_in[] = {
	{ "Key", "",_TYPES, 0,0,0, "", "" },
	{ "Filename", "",_TYPES, 0,0,0, "", "/opt/SPECS/usr/tpl/recipe.rec" },
};
static _VARDEF	_RCP_QUERY_RECIP_out[] = {
	{ "Waf", "",_TYPES, 0,0,0, "", "" },
	{ "Die", "",_TYPES, 1,256,0, "", "" },
	{ "Mod", "",_TYPES, 1,256,0, "", "" },
	{ "Tst", "",_TYPES, 1,256,0, "", "" },
	{ "Prb", "",_TYPES, 0,0,0, "", "" },
	{ "Lms", "",_TYPES, 1,256,0, "", "" },
	{ "Tco", "",_TYPES, 1,16,0, "", "" },
	{ "Mlib", "",_TYPES, 1,6,0, "", "" },
	{ "Item", "",_TYPES, 1,32,0, "", "" },
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File, 1: Warn", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm RCP_REPLACE_WD */

extern void _RCP_REPLACE_WD(void *, void *);
extern void __RCP_REPLACE_WD(void *);

static _VARDEF	_RCP_REPLACE_WD_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "", "$(RCP)_$(SI)" },
	{ "Find_wd", "",_TYPES, 1,5,0, "", "" },
	{ "Replace_wd", "",_TYPES, 1,5,0, "", "" },
};
static _VARDEF	_RCP_REPLACE_WD_out[] = {
	{ "String", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm RCP_SYSCONF */

extern void _RCP_SYSCONF(void *, void *);
extern void __RCP_SYSCONF(void *);

static _VARDEF	_RCP_SYSCONF_in[] = {
	{ "Name", "",_TYPES, 0,0,0, "Parameter name for Recipe Management in sysconf file.", "RCP_TPL" },
};
static _VARDEF	_RCP_SYSCONF_out[] = {
	{ "Value", "",_TYPES, 0,0,0, "Parameter value read from sysconf file.", "" },
	{ "Status", "",_TYPEI, 0,0,0, "0: Ok, -1: Not found, -2: Exec fail", "0" },
};

/* Definition for algorithm RCP_TPLBLD */

extern void _RCP_TPLBLD(void *, void *);
extern void __RCP_TPLBLD(void *);

static _VARDEF	_RCP_TPLBLD_in[] = {
	{ "Waf_dir", "",_TYPES, 0,0,0, "", "/opt/SPECS/demo" },
	{ "Prb_dir", "",_TYPES, 0,0,0, "", "/opt/SPECS/demo" },
	{ "Die_dir", "",_TYPES, 0,0,0, "", "/opt/SPECS/demo" },
	{ "Mod_dir", "",_TYPES, 0,0,0, "", "/opt/SPECS/demo" },
	{ "Tst_dir", "",_TYPES, 0,0,0, "", "/opt/SPECS/demo" },
	{ "Tpl_dir", "",_TYPES, 0,0,0, "", "/var/opt/SPECS/recipe" },
	{ "Waf", "",_TYPES, 0,0,0, "", "" },
	{ "Prb", "",_TYPES, 0,0,0, "", "" },
	{ "Die", "",_TYPES, 1,256,0, "", "" },
	{ "Mod", "",_TYPES, 1,256,0, "", "" },
	{ "Tst", "",_TYPES, 1,256,0, "", "" },
	{ "Mlib", "",_TYPES, 1,6,0, "", "" },
	{ "Tpl", "",_TYPES, 0,0,0, "", "testplan.tpl" },
};
static _VARDEF	_RCP_TPLBLD_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "0: OK, -1: Exec Err, -2: No File", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
	{ "Ndetail", "",_TYPEI, 0,0,0, "# of lines of detail error message", "0" },
	{ "Detail", "",_TYPES, 1,10,0, "Detailed error message", "" },
};

/* Definition for algorithm READ_CHAR */

extern void _READ_CHAR(void *, void *);
extern void __READ_CHAR(void *);

static _VARDEF	_READ_CHAR_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%c" },
	{ "String", "",_TYPES, 0,0,0, "String to read from", "" },
};
static _VARDEF	_READ_CHAR_out[] = {
	{ "Value", "",_TYPEC, 0,0,0, "Read value", " " },
	{ "Stat", "",_TYPEI, 0,0,0, "1(ok), 0(no data), -1(EOF)", "0" },
};

/* Definition for algorithm READ_INTEGER */

extern void _READ_INTEGER(void *, void *);
extern void __READ_INTEGER(void *);

static _VARDEF	_READ_INTEGER_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%d" },
	{ "String", "",_TYPES, 0,0,0, "String to read from", "" },
};
static _VARDEF	_READ_INTEGER_out[] = {
	{ "Value", "",_TYPEI, 0,0,0, "Read value", "0" },
	{ "Stat", "",_TYPEI, 0,0,0, "1(ok), 0(no data), -1(EOF)", "0" },
};

/* Definition for algorithm READ_PROCCOND */

extern void _READ_PROCCOND(void *, void *);
extern void __READ_PROCCOND(void *);

static _VARDEF	_READ_PROCCOND_in[] = {
	{ "Filename", "",_TYPES, 0,0,0, "file name", "" },
};
static _VARDEF	_READ_PROCCOND_out[] = {
	{ "Ret", "",_TYPEI, 0,0,0, "return code", "0" },
	{ "Readnum", "",_TYPEI, 0,0,0, "the number of read condition", "0" },
};

/* Definition for algorithm READ_REAL */

extern void _READ_REAL(void *, void *);
extern void __READ_REAL(void *);

static _VARDEF	_READ_REAL_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%e" },
	{ "String", "",_TYPES, 0,0,0, "String to read from", "" },
};
static _VARDEF	_READ_REAL_out[] = {
	{ "Value", "",_TYPER, 0,0,0, "Read value", "0" },
	{ "Stat", "",_TYPEI, 0,0,0, "1(ok), 0(no data), -1(EOF)", "0" },
};

/* Definition for algorithm READ_STRING */

extern void _READ_STRING(void *, void *);
extern void __READ_STRING(void *);

static _VARDEF	_READ_STRING_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%s" },
	{ "String", "",_TYPES, 0,0,0, "String to read from", "" },
};
static _VARDEF	_READ_STRING_out[] = {
	{ "Value", "",_TYPES, 0,0,0, "Read value", "" },
	{ "Stat", "",_TYPEI, 0,0,0, "1(ok), 0(no data), -1(EOF)", "0" },
};

/* Definition for algorithm SAVE_TMPDATA */

extern void _SAVE_TMPDATA(void *, void *);
extern void __SAVE_TMPDATA(void *);

static _VARDEF	_SAVE_TMPDATA_in[] = {
	{ "Path", "",_TYPES, 0,0,0, "", "" },
	{ "Name", "",_TYPES, 0,0,0, "", "" },
	{ "Format", "",_TYPES, 0,0,0, "", "adt" },
	{ "Session", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_SAVE_TMPDATA_out[] = {
	{ "Stat", "",_TYPEI, 0,0,0, "0: No temporary file exists 1: Save as official file -1: Failed ", "0" },
	{ "Error", "",_TYPES, 0,0,0, "", "" },
	{ "Pubname", "",_TYPES, 0,0,0, "Official name", "" },
};

/* Definition for algorithm SETUSRBIN_LPBGN */

extern void _SETUSRBIN_LPBGN(void *, void *);
extern void __SETUSRBIN_LPBGN(void *);

static _VARDEF	_SETUSRBIN_LPBGN_in[] = {
	{ "Waftgt", "%",_TYPEI, 0,0,0, "Wafer-level yield target.", "0" },
	{ "Lottgt", "%",_TYPEI, 0,0,0, "Lot-level yield target.", "0" },
};

/* Definition for algorithm SET_BRK_MOD */

extern void _SET_BRK_MOD(void *, void *);
extern void __SET_BRK_MOD(void *);

static _VARDEF	_SET_BRK_MOD_in[] = {
	{ "Typeindex", "",_TYPEI, 0,0,0, "Die type index (DIE.TYPENUMBER)", "1" },
	{ "Dieindex", "",_TYPEI, 0,0,0, "Die index in die type (DIE.NUMBER)", "1" },
	{ "Modindex", "",_TYPEI, 0,0,0, "Module index (MODULE.NUMBER)", "1" },
	{ "Break", "",_TYPEI, 0,0,0, "Breakpoint flag.", "1" },
};

/* Definition for algorithm SET_JDG_DIE */

extern void _SET_JDG_DIE(void *, void *);
extern void __SET_JDG_DIE(void *);

static _VARDEF	_SET_JDG_DIE_in[] = {
	{ "Typeindex", "",_TYPEI, 0,0,0, "Die type index (DIE.TYPENUMBER)", "1" },
	{ "Dieindex", "",_TYPEI, 0,0,0, "Die index in die type (DIE.NUMBER)", "1" },
	{ "Judge", "",_TYPEI, 0,0,0, "Judgement value.", "1" },
	{ "Offsetx", "",_TYPEI, 0,0,0, "Die X position offset.", "0" },
	{ "Offsety", "",_TYPEI, 0,0,0, "Die Y position offset.", "0" },
};

/* Definition for algorithm SET_JDG_DIE_ALL */

extern void _SET_JDG_DIE_ALL(void *, void *);
extern void __SET_JDG_DIE_ALL(void *);

static _VARDEF	_SET_JDG_DIE_ALL_in[] = {
	{ "Judge", "",_TYPEI, 0,0,0, " Judgement value", "1" },
	{ "Offsetx", "",_TYPEI, 0,0,0, "Die X position offset.", "0" },
	{ "Offsety", "",_TYPEI, 0,0,0, "Die Y position offset.", "0" },
};

/* Definition for algorithm SET_JDG_DIE_TYP */

extern void _SET_JDG_DIE_TYP(void *, void *);
extern void __SET_JDG_DIE_TYP(void *);

static _VARDEF	_SET_JDG_DIE_TYP_in[] = {
	{ "Typeindex", "",_TYPEI, 0,0,0, "Die type index (DIE.TYPENUMBER)", "1" },
	{ "Judge", "",_TYPEI, 0,0,0, "Judgement value.", "1" },
	{ "Offsetx", "",_TYPEI, 0,0,0, "Die X position offset.", "0" },
	{ "Offsety", "",_TYPEI, 0,0,0, "Die Y position offset.", "0" },
};

/* Definition for algorithm SET_SAMELEN */

extern void _SET_SAMELEN(void *, void *);
extern void __SET_SAMELEN(void *);

static _VARDEF	_SET_SAMELEN_in[] = {
	{ "Original", "",_TYPES, 0,0,0, "", "" },
	{ "Reference", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_SET_SAMELEN_out[] = {
	{ "Modified", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm SET_SAMELEN20 */

extern void _SET_SAMELEN20(void *, void *);
extern void __SET_SAMELEN20(void *);

static _VARDEF	_SET_SAMELEN20_in[] = {
	{ "Original", "",_TYPES, 1,20,0, "", "" },
};
static _VARDEF	_SET_SAMELEN20_out[] = {
	{ "Modified", "",_TYPES, 1,20,0, "", "" },
};

/* Definition for algorithm SET_TAG_CHAR */

extern void _SET_TAG_CHAR(void *, void *);
extern void __SET_TAG_CHAR(void *);

static _VARDEF	_SET_TAG_CHAR_in[] = {
	{ "Name", "",_TYPES, 0,0,0, "", "" },
	{ "Value", "",_TYPEC, 0,0,0, "", " " },
};

/* Definition for algorithm SET_TAG_INTEGER */

extern void _SET_TAG_INTEGER(void *, void *);
extern void __SET_TAG_INTEGER(void *);

static _VARDEF	_SET_TAG_INTEGER_in[] = {
	{ "Name", "",_TYPES, 0,0,0, "", "" },
	{ "Value", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm SET_TAG_REAL */

extern void _SET_TAG_REAL(void *, void *);
extern void __SET_TAG_REAL(void *);

static _VARDEF	_SET_TAG_REAL_in[] = {
	{ "Name", "",_TYPES, 0,0,0, "", "" },
	{ "Value", "",_TYPER, 0,0,0, "", "0" },
};

/* Definition for algorithm SET_TAG_STRING */

extern void _SET_TAG_STRING(void *, void *);
extern void __SET_TAG_STRING(void *);

static _VARDEF	_SET_TAG_STRING_in[] = {
	{ "Name", "",_TYPES, 0,0,0, "", "" },
	{ "Value", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm SIZEOFDISPLAY */

extern void _SIZEOFDISPLAY(void *, void *);
extern void __SIZEOFDISPLAY(void *);

static _VARDEF	_SIZEOFDISPLAY_out[] = {
	{ "Width", "",_TYPEI, 0,0,0, "", "0" },
	{ "Height", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm STATLOG_DIEEND */

extern void _STATLOG_DIEEND(void *, void *);
extern void __STATLOG_DIEEND(void *);

static _VARDEF	_STATLOG_DIEEND_in[] = {
	{ "Filename", "",_TYPES, 0,0,0, "Filename.", "/var/opt/SPECS/log/statlog.log" },
	{ "Mode", "",_TYPEI, 0,0,0, "All(0), Failed only(1)", "0" },
};

/* Definition for algorithm STRING_LOOKUP */

extern void _STRING_LOOKUP(void *, void *);
extern void __STRING_LOOKUP(void *);

static _VARDEF	_STRING_LOOKUP_in[] = {
	{ "Src", "",_TYPES, 0,0,0, "Source string", "" },
	{ "Pat", "",_TYPES, 0,0,0, "Pattern string", "" },
};
static _VARDEF	_STRING_LOOKUP_out[] = {
	{ "Pos", "",_TYPEI, 0,0,0, "Position (>0 position, 0 not found)", "0" },
};

/* Definition for algorithm STRING_SPLIT */

extern void _STRING_SPLIT(void *, void *);
extern void __STRING_SPLIT(void *);

static _VARDEF	_STRING_SPLIT_in[] = {
	{ "Src", "",_TYPES, 0,0,0, "Source string", "" },
	{ "Del", "",_TYPES, 0,0,0, "Delimiter", " " },
};
static _VARDEF	_STRING_SPLIT_out[] = {
	{ "Elem", "",_TYPES, 1,128,0, "Substrings", "" },
	{ "Count", "",_TYPEI, 0,0,0, "Number of substrings", "0" },
};

/* Definition for algorithm STRING_TIME */

extern void _STRING_TIME(void *, void *);
extern void __STRING_TIME(void *);

static _VARDEF	_STRING_TIME_in[] = {
	{ "Time", "",_TYPER, 0,0,0, "", "0" },
};
static _VARDEF	_STRING_TIME_out[] = {
	{ "Symbol", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm TIMEDATE */

extern void _TIMEDATE(void *, void *);
extern void __TIMEDATE(void *);

static _VARDEF	_TIMEDATE_in[] = {
	{ "Digit", "",_TYPEI, 0,0,0, "# digits to represent a year", "2" },
};
static _VARDEF	_TIMEDATE_out[] = {
	{ "Date", "",_TYPES, 0,0,0, "mm/dd/yy or mm/dd/yyyy", "" },
	{ "Time", "",_TYPES, 0,0,0, "hh:mm:ss", "" },
};

/* Definition for algorithm UPDATE_FWKCONF */

extern void _UPDATE_FWKCONF(void *, void *);
extern void __UPDATE_FWKCONF(void *);

static _VARDEF	_UPDATE_FWKCONF_in[] = {
	{ "File", "",_TYPES, 0,0,0, "", "" },
	{ "Type", "",_TYPEI, 0,0,0, "0:All vars, 1:Normal vars only, 2:Special vars only", "0" },
};
static _VARDEF	_UPDATE_FWKCONF_out[] = {
	{ "Errno", "",_TYPEI, 0,0,0, "", "0" },
	{ "Errmsg", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm VERIFY_FILE */

extern void _VERIFY_FILE(void *, void *);
extern void __VERIFY_FILE(void *);

static _VARDEF	_VERIFY_FILE_in[] = {
	{ "Filename", "",_TYPES, 0,0,0, "", "" },
	{ "Type", "",_TYPES, 0,0,0, "", "Normal" },
};
static _VARDEF	_VERIFY_FILE_out[] = {
	{ "Exist", "",_TYPEI, 0,0,0, "", "0" },
	{ "Readable", "",_TYPEI, 0,0,0, "", "0" },
	{ "Writable", "",_TYPEI, 0,0,0, "", "0" },
	{ "Executable", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm WAIT */

extern void _WAIT(void *, void *);
extern void __WAIT(void *);

static _VARDEF	_WAIT_in[] = {
	{ "Wait", "Sec",_TYPER, 0,0,0, "", "1" },
};

/* Definition for algorithm WRITE_CHAR */

extern void _WRITE_CHAR(void *, void *);
extern void __WRITE_CHAR(void *);

static _VARDEF	_WRITE_CHAR_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%c" },
	{ "Value", "",_TYPEC, 0,0,0, "Value to convert", " " },
};
static _VARDEF	_WRITE_CHAR_out[] = {
	{ "String", "",_TYPES, 0,0,0, "Formatted to string", "" },
	{ "Length", "",_TYPEI, 0,0,0, "Length of string", "0" },
};

/* Definition for algorithm WRITE_INTEGER */

extern void _WRITE_INTEGER(void *, void *);
extern void __WRITE_INTEGER(void *);

static _VARDEF	_WRITE_INTEGER_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%d" },
	{ "Value", "",_TYPEI, 0,0,0, "Value to convert", "0" },
};
static _VARDEF	_WRITE_INTEGER_out[] = {
	{ "String", "",_TYPES, 0,0,0, "Formatted to string", "" },
	{ "Length", "",_TYPEI, 0,0,0, "Length of string", "0" },
};

/* Definition for algorithm WRITE_REAL */

extern void _WRITE_REAL(void *, void *);
extern void __WRITE_REAL(void *);

static _VARDEF	_WRITE_REAL_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%e" },
	{ "Value", "",_TYPER, 0,0,0, "Value to convert", "0" },
};
static _VARDEF	_WRITE_REAL_out[] = {
	{ "String", "",_TYPES, 0,0,0, "Formatted to string", "" },
	{ "Length", "",_TYPEI, 0,0,0, "Length of string", "0" },
};

/* Definition for algorithm WRITE_STRING */

extern void _WRITE_STRING(void *, void *);
extern void __WRITE_STRING(void *);

static _VARDEF	_WRITE_STRING_in[] = {
	{ "Format", "",_TYPES, 0,0,0, "Format string", "%s" },
	{ "Value", "",_TYPES, 0,0,0, "Value to convert", "" },
};
static _VARDEF	_WRITE_STRING_out[] = {
	{ "String", "",_TYPES, 0,0,0, "Formatted to string", "" },
	{ "Length", "",_TYPEI, 0,0,0, "Length of string", "0" },
};

/* Definition for algorithm WRITE_WAFER_SUM */

extern void _WRITE_WAFER_SUM(void *, void *);
extern void __WRITE_WAFER_SUM(void *);

static _VARDEF	_WRITE_WAFER_SUM_in[] = {
	{ "Slot", "",_TYPEI, 0,0,0, "", "0" },
	{ "Lot", "",_TYPES, 0,0,0, "", "" },
	{ "Wafer", "",_TYPES, 0,0,0, "", "" },
	{ "Yld_item", "",_TYPER, 0,0,0, "", "0" },
	{ "Yld_die", "",_TYPER, 0,0,0, "", "0" },
	{ "Judge", "",_TYPEI, 0,0,0, "", "0" },
};
static _VARDEF	_WRITE_WAFER_SUM_out[] = {
	{ "Summary", "",_TYPES, 0,0,0, "", "" },
};

/* Definition for algorithm XWUD */

extern void _XWUD(void *, void *);
extern void __XWUD(void *);

static _VARDEF	_XWUD_in[] = {
	{ "File", "",_TYPES, 0,0,0, "xwd dump file (see xwd(1))", "" },
	{ "Xpos", "",_TYPEI, 0,0,0, "X position", "0" },
	{ "Ypos", "",_TYPEI, 0,0,0, "Y position", "0" },
	{ "Noclick", "",_TYPEI, 0,0,0, "1 to ignore mouse click", "1" },
};

/* Definition for algorithm YIELDLOG_WAFEND */

extern void _YIELDLOG_WAFEND(void *, void *);
extern void __YIELDLOG_WAFEND(void *);

static _VARDEF	_YIELDLOG_WAFEND_in[] = {
	{ "Filename", "",_TYPES, 0,0,0, "Filename.", "/var/opt/SPECS/log/yieldlog.log" },
	{ "Dieyield", "%",_TYPEI, 0,0,0, "Die yield target value.", "0" },
};

/* Definition for library UTIL_FA */

static _ALGDEF	_UTIL_FA[] = {
	{ "ADD_HEAD_SPACE",	_ADD_HEAD_SPACE,__ADD_HEAD_SPACE,	2,_ADD_HEAD_SPACE_in,0,NULL,0,NULL,1,_ADD_HEAD_SPACE_out,"Description for this Algorithm spec." },
	{ "ADD_TAIL_SPACE",	_ADD_TAIL_SPACE,__ADD_TAIL_SPACE,	2,_ADD_TAIL_SPACE_in,0,NULL,0,NULL,1,_ADD_TAIL_SPACE_out,"Description for this Algorithm spec." },
	{ "ALGPANEL_LAUNCH",	_ALGPANEL_LAUNCH,__ALGPANEL_LAUNCH,	4,_ALGPANEL_LAUNCH_in,0,NULL,0,NULL,0,NULL,"Execute Algorithm Panel." },
	{ "ALGPANEL_START",	_ALGPANEL_START,__ALGPANEL_START,	1,_ALGPANEL_START_in,0,NULL,0,NULL,0,NULL,"Popdup Algorithm Panel." },
	{ "ALGPANEL_STOP",	_ALGPANEL_STOP,__ALGPANEL_STOP,	0,NULL,0,NULL,0,NULL,0,NULL,"Popdown Algorithm Panel." },
	{ "APPLY_FWKCONF",	_APPLY_FWKCONF,__APPLY_FWKCONF,	2,_APPLY_FWKCONF_in,0,NULL,0,NULL,2,_APPLY_FWKCONF_out,"Read configuration parameter and apply them.\n  SPECS2.5: Added special parameters." },
	{ "ARRAY_LOOKUP1",	_ARRAY_LOOKUP1,__ARRAY_LOOKUP1,	2,_ARRAY_LOOKUP1_in,0,NULL,0,NULL,1,_ARRAY_LOOKUP1_out,"Returns the array index for a specified data element of a STRING array." },
	{ "ARRAY_LOOKUP2",	_ARRAY_LOOKUP2,__ARRAY_LOOKUP2,	2,_ARRAY_LOOKUP2_in,0,NULL,0,NULL,1,_ARRAY_LOOKUP2_out,"Returns the array indices for the specified data elements of a STRING array." },
	{ "ARRAY_LOOKUP3",	_ARRAY_LOOKUP3,__ARRAY_LOOKUP3,	2,_ARRAY_LOOKUP3_in,0,NULL,0,NULL,1,_ARRAY_LOOKUP3_out,"Returns the data elements for the specified indices of a STRING array" },
	{ "ATTRIB_FILE",	_ATTRIB_FILE,__ATTRIB_FILE,	1,_ATTRIB_FILE_in,0,NULL,0,NULL,3,_ATTRIB_FILE_out,"Description for this Algorithm spec." },
	{ "BEEP",	_BEEP,__BEEP,	2,_BEEP_in,0,NULL,0,NULL,0,NULL,"Specifies frquency and duration for the beep, and sounds the beep" },
	{ "CALL_ERRHANDLER",	_CALL_ERRHANDLER,__CALL_ERRHANDLER,	3,_CALL_ERRHANDLER_in,0,NULL,0,NULL,2,_CALL_ERRHANDLER_out,"Error Handler." },
	{ "CHECK_DATAFILE",	_CHECK_DATAFILE,__CHECK_DATAFILE,	1,_CHECK_DATAFILE_in,0,NULL,0,NULL,1,_CHECK_DATAFILE_out,"Description for this Algorithm spec." },
	{ "CHECK_FILE",	_CHECK_FILE,__CHECK_FILE,	2,_CHECK_FILE_in,0,NULL,0,NULL,1,_CHECK_FILE_out,"Description for this Algorithm spec." },
	{ "CHECK_PASSWD",	_CHECK_PASSWD,__CHECK_PASSWD,	2,_CHECK_PASSWD_in,0,NULL,0,NULL,1,_CHECK_PASSWD_out,"Description for this Algorithm spec." },
	{ "CHECK_PROBER",	_CHECK_PROBER,__CHECK_PROBER,	1,_CHECK_PROBER_in,0,NULL,0,NULL,2,_CHECK_PROBER_out,"Description for this Algorithm spec." },
	{ "CHECK_PROFILE",	_CHECK_PROFILE,__CHECK_PROFILE,	0,NULL,0,NULL,0,NULL,1,_CHECK_PROFILE_out,"Description for this Algorithm spec." },
	{ "CHECK_SYSCONF",	_CHECK_SYSCONF,__CHECK_SYSCONF,	0,NULL,0,NULL,0,NULL,11,_CHECK_SYSCONF_out,"Description for this Algorithm spec." },
	{ "CHECK_TIME",	_CHECK_TIME,__CHECK_TIME,	0,NULL,0,NULL,0,NULL,1,_CHECK_TIME_out,"Description for this Algorithm spec." },
	{ "CLOCK",	_CLOCK,__CLOCK,	1,_CLOCK_in,0,NULL,0,NULL,7,_CLOCK_out,"Returns the present date and time" },
	{ "DATALOG_DIEEND",	_DATALOG_DIEEND,__DATALOG_DIEEND,	2,_DATALOG_DIEEND_in,0,NULL,0,NULL,0,NULL,"Logs datas on the specified file. This uses user bin.\n" },
	{ "DEL_HEAD_SPACE",	_DEL_HEAD_SPACE,__DEL_HEAD_SPACE,	1,_DEL_HEAD_SPACE_in,0,NULL,0,NULL,1,_DEL_HEAD_SPACE_out,"Description for this Algorithm spec." },
	{ "DEL_NEWLINE",	_DEL_NEWLINE,__DEL_NEWLINE,	1,_DEL_NEWLINE_in,0,NULL,0,NULL,1,_DEL_NEWLINE_out,"Description for this Algorithm spec." },
	{ "DEL_TAIL_SPACE",	_DEL_TAIL_SPACE,__DEL_TAIL_SPACE,	1,_DEL_TAIL_SPACE_in,0,NULL,0,NULL,1,_DEL_TAIL_SPACE_out,"Description for this Algorithm spec." },
	{ "FA_BLDSCR_LIM",	_FA_BLDSCR_LIM,__FA_BLDSCR_LIM,	2,_FA_BLDSCR_LIM_in,0,NULL,0,NULL,2,_FA_BLDSCR_LIM_out,"This algorithm alters Limit File according to conditions specified by external file.\n" },
	{ "FA_BLDSCR_TPL",	_FA_BLDSCR_TPL,__FA_BLDSCR_TPL,	2,_FA_BLDSCR_TPL_in,0,NULL,0,NULL,2,_FA_BLDSCR_TPL_out,"This algorithm alters Test Plan according to conditions specified by external file." },
	{ "FA_CHKRUN_FWK",	_FA_CHKRUN_FWK,__FA_CHKRUN_FWK,	2,_FA_CHKRUN_FWK_in,0,NULL,0,NULL,2,_FA_CHKRUN_FWK_out,"Description for this Algorithm spec." },
	{ "FA_CHK_FILES",	_FA_CHK_FILES,__FA_CHK_FILES,	5,_FA_CHK_FILES_in,0,NULL,0,NULL,1,_FA_CHK_FILES_out,"Description for this Algorithm spec." },
	{ "FA_CHK_FILES2",	_FA_CHK_FILES2,__FA_CHK_FILES2,	5,_FA_CHK_FILES2_in,0,NULL,0,NULL,4,_FA_CHK_FILES2_out,"Description for this Algorithm spec." },
	{ "FA_CHK_LIBPATH",	_FA_CHK_LIBPATH,__FA_CHK_LIBPATH,	1,_FA_CHK_LIBPATH_in,0,NULL,0,NULL,4,_FA_CHK_LIBPATH_out,"Description for this Algorithm spec." },
	{ "FA_CHK_MEASLIB",	_FA_CHK_MEASLIB,__FA_CHK_MEASLIB,	4,_FA_CHK_MEASLIB_in,0,NULL,0,NULL,2,_FA_CHK_MEASLIB_out,"Check multi-measurement libraris." },
	{ "FA_CHK_REV",	_FA_CHK_REV,__FA_CHK_REV,	2,_FA_CHK_REV_in,0,NULL,0,NULL,5,_FA_CHK_REV_out,"Description for this Algorithm spec." },
	{ "FA_CHK_REV2",	_FA_CHK_REV2,__FA_CHK_REV2,	3,_FA_CHK_REV2_in,0,NULL,0,NULL,5,_FA_CHK_REV2_out,"Get TPL file information." },
	{ "FA_GETKEY_ITEMS",	_FA_GETKEY_ITEMS,__FA_GETKEY_ITEMS,	2,_FA_GETKEY_ITEMS_in,0,NULL,0,NULL,11,_FA_GETKEY_ITEMS_out,"Desc: Get many items in the file from key recipe id. \nDate: '00/Nov/28 Initial revision\nDate: '01/Mar/09 Released  K.N\nDate: '01/Jul/19 Change to Lynx1 by M.N" },
	{ "FA_LIMBLD",	_FA_LIMBLD,__FA_LIMBLD,	6,_FA_LIMBLD_in,0,NULL,0,NULL,4,_FA_LIMBLD_out,"This algorithm generates Limit File dynamically." },
	{ "FA_LIMBLD2",	_FA_LIMBLD2,__FA_LIMBLD2,	8,_FA_LIMBLD2_in,0,NULL,0,NULL,4,_FA_LIMBLD2_out,"This algorithm generates Limit File dynamically.\n2005/09/02 Bugfix Call limbuild/limformat" },
	{ "FA_LIMFMT",	_FA_LIMFMT,__FA_LIMFMT,	8,_FA_LIMFMT_in,0,NULL,0,NULL,2,_FA_LIMFMT_out,"This algorithm alters Limit File according to conditions specified by external file.\n2005/09/02 Bugfix Call limformat" },
	{ "FA_LMP_CLEARLN",	_FA_LMP_CLEARLN,__FA_LMP_CLEARLN,	2,_FA_LMP_CLEARLN_in,0,NULL,0,NULL,1,_FA_LMP_CLEARLN_out,"FA Algorithm: Clear a line of LMP User Value Displayment area." },
	{ "FA_LMP_DISPINT",	_FA_LMP_DISPINT,__FA_LMP_DISPINT,	5,_FA_LMP_DISPINT_in,0,NULL,0,NULL,1,_FA_LMP_DISPINT_out,"FA Algorithm: Display a combination of Label + Value in LMP User Value Displayment area." },
	{ "FA_LMP_DISPLINE",	_FA_LMP_DISPLINE,__FA_LMP_DISPLINE,	5,_FA_LMP_DISPLINE_in,0,NULL,0,NULL,1,_FA_LMP_DISPLINE_out,"FA Algorithm: Display a combination of Label + Value in LMP User Value Displayment area." },
	{ "FA_LMP_DISPVAR",	_FA_LMP_DISPVAR,__FA_LMP_DISPVAR,	5,_FA_LMP_DISPVAR_in,0,NULL,0,NULL,1,_FA_LMP_DISPVAR_out,"FA Algorithm: Display a combination of Label + VGEM VAL in LMP User Value Displayment area." },
	{ "FA_MK_DATANAME",	_FA_MK_DATANAME,__FA_MK_DATANAME,	5,_FA_MK_DATANAME_in,0,NULL,0,NULL,3,_FA_MK_DATANAME_out,"This algorithm generates file name to dump data for a current wafer." },
	{ "FA_QUERY_COND",	_FA_QUERY_COND,__FA_QUERY_COND,	3,_FA_QUERY_COND_in,0,NULL,0,NULL,8,_FA_QUERY_COND_out,"Query recipe items in the recipe file from key recipe id.\n  SPECS3.0: Initial revision." },
	{ "FA_QUERY_RCP2",	_FA_QUERY_RCP2,__FA_QUERY_RCP2,	2,_FA_QUERY_RCP2_in,0,NULL,0,NULL,17,_FA_QUERY_RCP2_out,"Query recipe items in the recipe file from key recipe id.\n  SPECS3.0: Initial revision." },
	{ "FA_QUERY_RECIP",	_FA_QUERY_RECIP,__FA_QUERY_RECIP,	2,_FA_QUERY_RECIP_in,0,NULL,0,NULL,16,_FA_QUERY_RECIP_out,"Query recipe items in the recipe file from key recipe id.\n  SPECS3.0: Initial revision." },
	{ "FA_RCP_EXEC_CMD",	_FA_RCP_EXEC_CMD,__FA_RCP_EXEC_CMD,	2,_FA_RCP_EXEC_CMD_in,0,NULL,0,NULL,5,_FA_RCP_EXEC_CMD_out,"Execute command file and get result file.\n  SPECS3.0: Initial revision." },
	{ "FA_READ_CARD",	_FA_READ_CARD,__FA_READ_CARD,	1,_FA_READ_CARD_in,0,NULL,0,NULL,5,_FA_READ_CARD_out,"Desc: Read name, type, and count in probe card.\nDate: '00/11/27 1st revision\nDate: '01/10/07 Read file and return the parameters." },
	{ "FA_RUNP_CREATE",	_FA_RUNP_CREATE,__FA_RUNP_CREATE,	4,_FA_RUNP_CREATE_in,0,NULL,0,NULL,2,_FA_RUNP_CREATE_out,"Description for this Algorithm spec." },
	{ "FA_TPLBLD",	_FA_TPLBLD,__FA_TPLBLD,	12,_FA_TPLBLD_in,0,NULL,0,NULL,4,_FA_TPLBLD_out,"This algorithm generates Test Plan dynamically." },
	{ "FA_TPLBLD2",	_FA_TPLBLD2,__FA_TPLBLD2,	19,_FA_TPLBLD2_in,0,NULL,0,NULL,4,_FA_TPLBLD2_out,"This algorithm generates Test Plan dynamically." },
	{ "FA_TPLBLD3",	_FA_TPLBLD3,__FA_TPLBLD3,	19,_FA_TPLBLD3_in,0,NULL,0,NULL,4,_FA_TPLBLD3_out,"This algorithm generates Test Plan dynamically." },
	{ "FA_TPLFMT",	_FA_TPLFMT,__FA_TPLFMT,	8,_FA_TPLFMT_in,0,NULL,0,NULL,2,_FA_TPLFMT_out,"This algorithm alters Test Plan according to conditions specified by external file." },
	{ "FA_TPL_RUN",	_FA_TPL_RUN,__FA_TPL_RUN,	1,_FA_TPL_RUN_in,0,NULL,0,NULL,2,_FA_TPL_RUN_out,"Description for this Algorithm spec." },
	{ "FA_TPL_VERIFY",	_FA_TPL_VERIFY,__FA_TPL_VERIFY,	8,_FA_TPL_VERIFY_in,0,NULL,0,NULL,2,_FA_TPL_VERIFY_out,"Validate test plan with multi-measurement libraries and test plan constants." },
	{ "FA_UPDATE_CARD",	_FA_UPDATE_CARD,__FA_UPDATE_CARD,	3,_FA_UPDATE_CARD_in,0,NULL,0,NULL,1,_FA_UPDATE_CARD_out,"FA: Update probecard touchdown counts" },
	{ "FA_UPD_VGEMLVAR",	_FA_UPD_VGEMLVAR,__FA_UPD_VGEMLVAR,	4,_FA_UPD_VGEMLVAR_in,0,NULL,0,NULL,1,_FA_UPD_VGEMLVAR_out,"Update VGEM list type variable" },
	{ "FA_UPD_VGEMVAR",	_FA_UPD_VGEMVAR,__FA_UPD_VGEMVAR,	3,_FA_UPD_VGEMVAR_in,0,NULL,0,NULL,1,_FA_UPD_VGEMVAR_out,"Description for this Algorithm spec." },
	{ "FA_WAFERDUMP",	_FA_WAFERDUMP,__FA_WAFERDUMP,	5,_FA_WAFERDUMP_in,0,NULL,0,NULL,1,_FA_WAFERDUMP_out,"This algorithm generates adtfile to a current wafer." },
	{ "FA_WAIT",	_FA_WAIT,__FA_WAIT,	1,_FA_WAIT_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "FILE_HWCONFIG",	_FILE_HWCONFIG,__FILE_HWCONFIG,	2,_FILE_HWCONFIG_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "FILE_LOOKUP",	_FILE_LOOKUP,__FILE_LOOKUP,	2,_FILE_LOOKUP_in,0,NULL,0,NULL,3,_FILE_LOOKUP_out,"Searches for and returns all the file names (in all directories under a specified directory) that have a specified suffix" },
	{ "FORMAT_PATH",	_FORMAT_PATH,__FORMAT_PATH,	1,_FORMAT_PATH_in,0,NULL,0,NULL,1,_FORMAT_PATH_out,"Description for this Algorithm spec." },
	{ "GEM_GETCMD",	_GEM_GETCMD,__GEM_GETCMD,	0,NULL,0,NULL,0,NULL,3,_GEM_GETCMD_out,"Get all of commands for using this algorirthm." },
	{ "GEM_INIT",	_GEM_INIT,__GEM_INIT,	0,NULL,0,NULL,0,NULL,1,_GEM_INIT_out,"Initialize GEM module" },
	{ "GEM_RESPOND_NOK",	_GEM_RESPOND_NOK,__GEM_RESPOND_NOK,	1,_GEM_RESPOND_NOK_in,0,NULL,0,NULL,1,_GEM_RESPOND_NOK_out,"GEM_RESPOND_NotOK:" },
	{ "GEM_RESPOND_OK",	_GEM_RESPOND_OK,__GEM_RESPOND_OK,	2,_GEM_RESPOND_OK_in,0,NULL,0,NULL,1,_GEM_RESPOND_OK_out,"GEM_RESPOND_OK:" },
	{ "GEM_SENDEVENT",	_GEM_SENDEVENT,__GEM_SENDEVENT,	2,_GEM_SENDEVENT_in,0,NULL,0,NULL,1,_GEM_SENDEVENT_out,"Send all of event for using this algorirthm." },
	{ "GET_BRK_MOD",	_GET_BRK_MOD,__GET_BRK_MOD,	3,_GET_BRK_MOD_in,0,NULL,0,NULL,1,_GET_BRK_MOD_out,"Return breakpoint flag value of specified module.\n  SPECS2.5: Initial revision." },
	{ "GET_DIELABEL",	_GET_DIELABEL,__GET_DIELABEL,	0,NULL,0,NULL,0,NULL,1,_GET_DIELABEL_out,"Description for this Algorithm spec." },
	{ "GET_DIETYPE",	_GET_DIETYPE,__GET_DIETYPE,	0,NULL,0,NULL,0,NULL,1,_GET_DIETYPE_out,"Description for this Algorithm spec." },
	{ "GET_JDG_DIE",	_GET_JDG_DIE,__GET_JDG_DIE,	2,_GET_JDG_DIE_in,0,NULL,0,NULL,3,_GET_JDG_DIE_out,"Return judgement flag value of specified die.\n  SPECS2.5: Initial revision." },
	{ "GET_LOC_MOD",	_GET_LOC_MOD,__GET_LOC_MOD,	2,_GET_LOC_MOD_in,0,NULL,0,NULL,3,_GET_LOC_MOD_out,"Return module position of specified module relative to die.\n  SPECS2.5: Initial revision." },
	{ "GET_MODLABEL",	_GET_MODLABEL,__GET_MODLABEL,	0,NULL,0,NULL,0,NULL,1,_GET_MODLABEL_out,"Description for this Algorithm spec." },
	{ "GET_NEXT_MOD",	_GET_NEXT_MOD,__GET_NEXT_MOD,	4,_GET_NEXT_MOD_in,0,NULL,0,NULL,5,_GET_NEXT_MOD_out,"Search failed module.\n  SPECS2.5: Initial revision." },
	{ "GET_PREV_MOD",	_GET_PREV_MOD,__GET_PREV_MOD,	4,_GET_PREV_MOD_in,0,NULL,0,NULL,5,_GET_PREV_MOD_out,"Search failed module.\n  SPECS2.5: Initial revision." },
	{ "GET_SLOT_NO",	_GET_SLOT_NO,__GET_SLOT_NO,	2,_GET_SLOT_NO_in,0,NULL,0,NULL,1,_GET_SLOT_NO_out,"Get slot number from lot ID and wafer ID." },
	{ "GET_VGEMDEFAULT",	_GET_VGEMDEFAULT,__GET_VGEMDEFAULT,	0,NULL,0,NULL,0,NULL,3,_GET_VGEMDEFAULT_out,"Description for this Algorithm spec." },
	{ "G_CV",	_G_CV,__G_CV,	5,_G_CV_in,0,NULL,2,_G_CV_trm,0,NULL,"Measures the Capacitance-Voltage characteristics (C-V characteristics), and displays the measurement results on a graph" },
	{ "G_HFE",	_G_HFE,__G_HFE,	4,_G_HFE_in,0,NULL,3,_G_HFE_trm,0,NULL,"Measures the bipolar transistor Collector Current-hFE characteristics (Ic-hFE characteristics), and displays the measurement results on a graph" },
	{ "G_ICVB",	_G_ICVB,__G_ICVB,	3,_G_ICVB_in,0,NULL,3,_G_ICVB_trm,0,NULL,"Measures the bipolar transistor Collector Current-Base Voltage characteristics (Ic-Vb characteristics), and displays the measurement results on a graph" },
	{ "G_ICVC",	_G_ICVC,__G_ICVC,	6,_G_ICVC_in,0,NULL,3,_G_ICVC_trm,0,NULL,"Measures the bipolar transistor Collector Current-Collector Voltage characteristics (Ic-Vc characteristics), and displays the measurement results on a graph" },
	{ "G_IDVD",	_G_IDVD,__G_IDVD,	6,_G_IDVD_in,0,NULL,4,_G_IDVD_trm,0,NULL,"Measures the MOSFET Drain Current-Drain Voltage characteristics (Id-Vd characteristics), and displays the measurement results on a graph" },
	{ "G_IDVG",	_G_IDVG,__G_IDVG,	7,_G_IDVG_in,0,NULL,4,_G_IDVG_trm,0,NULL,"Measures the MOSFET Drain Current-Gate Voltage characteristics (Id-Vg characteristics), and displays the measurement results on a graph" },
	{ "IS_CALG",	_IS_CALG,__IS_CALG,	0,NULL,0,NULL,0,NULL,1,_IS_CALG_out,"Check the lang of algorithm" },
	{ "IS_FIRST",	_IS_FIRST,__IS_FIRST,	0,NULL,0,NULL,0,NULL,1,_IS_FIRST_out,"Description for this Algorithm spec." },
	{ "JDG_DIE",	_JDG_DIE,__JDG_DIE,	4,_JDG_DIE_in,0,NULL,0,NULL,5,_JDG_DIE_out,"Judge current die by parameter yield." },
	{ "JDG_DIE_AT_POS",	_JDG_DIE_AT_POS,__JDG_DIE_AT_POS,	3,_JDG_DIE_AT_POS_in,0,NULL,0,NULL,5,_JDG_DIE_AT_POS_out,"Judge specified die by parameter yield." },
	{ "JDG_DIE_AT_POS2",	_JDG_DIE_AT_POS2,__JDG_DIE_AT_POS2,	5,_JDG_DIE_AT_POS2_in,0,NULL,0,NULL,5,_JDG_DIE_AT_POS2_out,"Judge specified die by parameter yield." },
	{ "JDG_MOD",	_JDG_MOD,__JDG_MOD,	1,_JDG_MOD_in,0,NULL,0,NULL,4,_JDG_MOD_out,"Return if current module has failed outputs.\n  SPECS2.5: Initial revision." },
	{ "JDG_MOD_AT_POS",	_JDG_MOD_AT_POS,__JDG_MOD_AT_POS,	3,_JDG_MOD_AT_POS_in,0,NULL,0,NULL,4,_JDG_MOD_AT_POS_out,"Return if specified module has failed outputs.\n  SPECS2.5: Initial revision." },
	{ "JDG_WAF_BY_DIE",	_JDG_WAF_BY_DIE,__JDG_WAF_BY_DIE,	3,_JDG_WAF_BY_DIE_in,0,NULL,0,NULL,5,_JDG_WAF_BY_DIE_out,"Judge current wafer by die yield." },
	{ "JDG_WAF_BY_PARA",	_JDG_WAF_BY_PARA,__JDG_WAF_BY_PARA,	4,_JDG_WAF_BY_PARA_in,0,NULL,0,NULL,5,_JDG_WAF_BY_PARA_out,"Judge current wafer by parameter yield." },
	{ "LOG_LOT_BEGIN",	_LOG_LOT_BEGIN,__LOG_LOT_BEGIN,	8,_LOG_LOT_BEGIN_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "LOG_LOT_END",	_LOG_LOT_END,__LOG_LOT_END,	6,_LOG_LOT_END_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "LOG_PROBER",	_LOG_PROBER,__LOG_PROBER,	2,_LOG_PROBER_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "LOG_SYSTEM",	_LOG_SYSTEM,__LOG_SYSTEM,	2,_LOG_SYSTEM_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "LOG_TIMESTAMP",	_LOG_TIMESTAMP,__LOG_TIMESTAMP,	0,NULL,0,NULL,0,NULL,1,_LOG_TIMESTAMP_out,"Description for this Algorithm spec." },
	{ "LOG_WAFER_BEGIN",	_LOG_WAFER_BEGIN,__LOG_WAFER_BEGIN,	3,_LOG_WAFER_BEGIN_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "LOG_WAFER_END",	_LOG_WAFER_END,__LOG_WAFER_END,	4,_LOG_WAFER_END_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "MASTER_LOOKUP",	_MASTER_LOOKUP,__MASTER_LOOKUP,	3,_MASTER_LOOKUP_in,0,NULL,0,NULL,2,_MASTER_LOOKUP_out,"Returns specified field of specified line in an ASCII data file" },
	{ "MERGE_DATAFILE",	_MERGE_DATAFILE,__MERGE_DATAFILE,	5,_MERGE_DATAFILE_in,0,NULL,0,NULL,2,_MERGE_DATAFILE_out,"Description for this Algorithm spec." },
	{ "NAME_TMPDATA",	_NAME_TMPDATA,__NAME_TMPDATA,	2,_NAME_TMPDATA_in,0,NULL,0,NULL,1,_NAME_TMPDATA_out,"Description for this Algorithm spec." },
	{ "PRBCOUNT",	_PRBCOUNT,__PRBCOUNT,	0,NULL,0,NULL,0,NULL,1,_PRBCOUNT_out,"Return the number of Pins" },
	{ "PRBINFO",	_PRBINFO,__PRBINFO,	1,_PRBINFO_in,0,NULL,0,NULL,2,_PRBINFO_out,"Return pin number and pad number." },
	{ "PRINT",	_PRINT,__PRINT,	1,_PRINT_in,0,NULL,0,NULL,0,NULL,"Prints the specified STRING variable to the present PRINTER IS device" },
	{ "PRINT_CHAR",	_PRINT_CHAR,__PRINT_CHAR,	2,_PRINT_CHAR_in,0,NULL,0,NULL,0,NULL,"Writes a CHARACTER value to a STRING variable, then prints it to the present PRINTER IS device" },
	{ "PRINT_INTEGER",	_PRINT_INTEGER,__PRINT_INTEGER,	2,_PRINT_INTEGER_in,0,NULL,0,NULL,0,NULL,"Writes an INTEGER value to a STRING variable, then prints it to the present PRINTER IS device" },
	{ "PRINT_REAL",	_PRINT_REAL,__PRINT_REAL,	2,_PRINT_REAL_in,0,NULL,0,NULL,0,NULL,"Writes a REAL value to a STRING variable, then prints it to the present PRINTER IS device" },
	{ "PRINT_STRING",	_PRINT_STRING,__PRINT_STRING,	2,_PRINT_STRING_in,0,NULL,0,NULL,0,NULL,"Writes a STRING value to a STRING variable, then prints it to the present PRINTER IS device" },
	{ "QUERY_DIR",	_QUERY_DIR,__QUERY_DIR,	1,_QUERY_DIR_in,0,NULL,0,NULL,1,_QUERY_DIR_out,"Let Quick Query open specified directory.\n  SPECS2.5: Initial revision." },
	{ "QUERY_FILE",	_QUERY_FILE,__QUERY_FILE,	1,_QUERY_FILE_in,0,NULL,0,NULL,1,_QUERY_FILE_out,"Let Quick Query open specified file.\n  SPECS2.5: Initial revision." },
	{ "QUERY_GRAPH",	_QUERY_GRAPH,__QUERY_GRAPH,	5,_QUERY_GRAPH_in,0,NULL,0,NULL,0,NULL,"Let Quick Query open Graph. Must be executed after QUERY_FILE.\n  SPECS2.5: Initial revision." },
	{ "QUERY_LAUNCH",	_QUERY_LAUNCH,__QUERY_LAUNCH,	4,_QUERY_LAUNCH_in,0,NULL,0,NULL,0,NULL,"Start Quick Query." },
	{ "QUERY_START",	_QUERY_START,__QUERY_START,	0,NULL,0,NULL,0,NULL,0,NULL,"Popup Quick Query." },
	{ "QUERY_STOP",	_QUERY_STOP,__QUERY_STOP,	0,NULL,0,NULL,0,NULL,0,NULL,"Popdown Quick Query." },
	{ "QUERY_VIEW",	_QUERY_VIEW,__QUERY_VIEW,	2,_QUERY_VIEW_in,0,NULL,0,NULL,0,NULL,"Let Quick Query open Quick View. Must be executed after QUERY_FILE.\n  SPECS2.5: Initial revision." },
	{ "RCP_CHECK_KEY",	_RCP_CHECK_KEY,__RCP_CHECK_KEY,	1,_RCP_CHECK_KEY_in,0,NULL,0,NULL,3,_RCP_CHECK_KEY_out,"Check if recipe file has duplicate key fields.\n  SPECS3.0: Initial revision." },
	{ "RCP_DIETST",	_RCP_DIETST,__RCP_DIETST,	3,_RCP_DIETST_in,0,NULL,0,NULL,3,_RCP_DIETST_out,"The Algorithm makes a Die Spec-Test Spec list for tplbuild command.\n  SPECS3.0: Initial revision." },
	{ "RCP_EXEC_CMD",	_RCP_EXEC_CMD,__RCP_EXEC_CMD,	2,_RCP_EXEC_CMD_in,0,NULL,0,NULL,5,_RCP_EXEC_CMD_out,"Execute command file and get result file.\n  SPECS3.0: Initial revision." },
	{ "RCP_LIMBLD",	_RCP_LIMBLD,__RCP_LIMBLD,	6,_RCP_LIMBLD_in,0,NULL,0,NULL,4,_RCP_LIMBLD_out,"This algorithm generates Limit File dynamically.\n  SPECS3.0: Initial revision." },
	{ "RCP_MK_FILENAME",	_RCP_MK_FILENAME,__RCP_MK_FILENAME,	3,_RCP_MK_FILENAME_in,0,NULL,0,NULL,1,_RCP_MK_FILENAME_out,"Make file name from directory name and file name.\n  SPECS3.0: Initial revision." },
	{ "RCP_QUERY_RECIP",	_RCP_QUERY_RECIP,__RCP_QUERY_RECIP,	2,_RCP_QUERY_RECIP_in,0,NULL,0,NULL,11,_RCP_QUERY_RECIP_out,"Query recipe items in the recipe file from key recipe id.\n  SPECS3.1: Initial revision." },
	{ "RCP_REPLACE_WD",	_RCP_REPLACE_WD,__RCP_REPLACE_WD,	3,_RCP_REPLACE_WD_in,0,NULL,0,NULL,1,_RCP_REPLACE_WD_out,"Replace keyword in Format String.\n  SPECS3.0: Initial revision." },
	{ "RCP_SYSCONF",	_RCP_SYSCONF,__RCP_SYSCONF,	1,_RCP_SYSCONF_in,0,NULL,0,NULL,2,_RCP_SYSCONF_out,"Read a parameter written in sysconf file.\n  SPECS3.0: Initial revision." },
	{ "RCP_TPLBLD",	_RCP_TPLBLD,__RCP_TPLBLD,	13,_RCP_TPLBLD_in,0,NULL,0,NULL,4,_RCP_TPLBLD_out,"This algorithm generates Test Plan dynamically.\n  SPECS3.1: Initial revision." },
	{ "READ_CHAR",	_READ_CHAR,__READ_CHAR,	2,_READ_CHAR_in,0,NULL,0,NULL,2,_READ_CHAR_out,"Reads a character from a STRING variable, and returns it to a CHARACTER variable" },
	{ "READ_INTEGER",	_READ_INTEGER,__READ_INTEGER,	2,_READ_INTEGER_in,0,NULL,0,NULL,2,_READ_INTEGER_out,"Reads a value from a STRING variable, and returns it to an INTEGER variable" },
	{ "READ_PROCCOND",	_READ_PROCCOND,__READ_PROCCOND,	1,_READ_PROCCOND_in,0,NULL,0,NULL,2,_READ_PROCCOND_out,"Read process condition file." },
	{ "READ_REAL",	_READ_REAL,__READ_REAL,	2,_READ_REAL_in,0,NULL,0,NULL,2,_READ_REAL_out,"Reads a value from a STRING variable, and returns it to a REAL variable" },
	{ "READ_STRING",	_READ_STRING,__READ_STRING,	2,_READ_STRING_in,0,NULL,0,NULL,2,_READ_STRING_out,"Reads string data from a STRING variable, and returns it to another STRING variable" },
	{ "SAVE_TMPDATA",	_SAVE_TMPDATA,__SAVE_TMPDATA,	4,_SAVE_TMPDATA_in,0,NULL,0,NULL,3,_SAVE_TMPDATA_out,"Description for this Algorithm spec." },
	{ "SETUSRBIN_LPBGN",	_SETUSRBIN_LPBGN,__SETUSRBIN_LPBGN,	2,_SETUSRBIN_LPBGN_in,0,NULL,0,NULL,0,NULL,"Initializes \"user bin\" condition.\n" },
	{ "SET_BRK_MOD",	_SET_BRK_MOD,__SET_BRK_MOD,	4,_SET_BRK_MOD_in,0,NULL,0,NULL,0,NULL,"Set judgement flag of specified module.\n  SPECS2.5: Initial revision." },
	{ "SET_JDG_DIE",	_SET_JDG_DIE,__SET_JDG_DIE,	5,_SET_JDG_DIE_in,0,NULL,0,NULL,0,NULL,"Set judgement flag of specified die.\n  SPECS2.5: Initial revision." },
	{ "SET_JDG_DIE_ALL",	_SET_JDG_DIE_ALL,__SET_JDG_DIE_ALL,	3,_SET_JDG_DIE_ALL_in,0,NULL,0,NULL,0,NULL,"Set judgement flag of all dice.\n  SPECS2.5: Initial revision." },
	{ "SET_JDG_DIE_TYP",	_SET_JDG_DIE_TYP,__SET_JDG_DIE_TYP,	4,_SET_JDG_DIE_TYP_in,0,NULL,0,NULL,0,NULL,"Set judgement flag of specified die type.\n  SPECS2.5: Initial revision." },
	{ "SET_SAMELEN",	_SET_SAMELEN,__SET_SAMELEN,	2,_SET_SAMELEN_in,0,NULL,0,NULL,1,_SET_SAMELEN_out,"Description for this Algorithm spec." },
	{ "SET_SAMELEN20",	_SET_SAMELEN20,__SET_SAMELEN20,	1,_SET_SAMELEN20_in,0,NULL,0,NULL,1,_SET_SAMELEN20_out,"Description for this Algorithm spec." },
	{ "SET_TAG_CHAR",	_SET_TAG_CHAR,__SET_TAG_CHAR,	2,_SET_TAG_CHAR_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "SET_TAG_INTEGER",	_SET_TAG_INTEGER,__SET_TAG_INTEGER,	2,_SET_TAG_INTEGER_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "SET_TAG_REAL",	_SET_TAG_REAL,__SET_TAG_REAL,	2,_SET_TAG_REAL_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "SET_TAG_STRING",	_SET_TAG_STRING,__SET_TAG_STRING,	2,_SET_TAG_STRING_in,0,NULL,0,NULL,0,NULL,"Description for this Algorithm spec." },
	{ "SIZEOFDISPLAY",	_SIZEOFDISPLAY,__SIZEOFDISPLAY,	0,NULL,0,NULL,0,NULL,2,_SIZEOFDISPLAY_out,"Description for this Algorithm spec." },
	{ "STATLOG_DIEEND",	_STATLOG_DIEEND,__STATLOG_DIEEND,	2,_STATLOG_DIEEND_in,0,NULL,0,NULL,0,NULL,"logs statistics on the specified file. This users user bin.\n\n" },
	{ "STRING_LOOKUP",	_STRING_LOOKUP,__STRING_LOOKUP,	2,_STRING_LOOKUP_in,0,NULL,0,NULL,1,_STRING_LOOKUP_out,"Returns the position of specified character(s) in a STRING variable" },
	{ "STRING_SPLIT",	_STRING_SPLIT,__STRING_SPLIT,	2,_STRING_SPLIT_in,0,NULL,0,NULL,2,_STRING_SPLIT_out,"Returns data (without separators) from a STRING variable, which contains data separated by data separators" },
	{ "STRING_TIME",	_STRING_TIME,__STRING_TIME,	1,_STRING_TIME_in,0,NULL,0,NULL,1,_STRING_TIME_out,"Description for this Algorithm spec." },
	{ "TIMEDATE",	_TIMEDATE,__TIMEDATE,	1,_TIMEDATE_in,0,NULL,0,NULL,2,_TIMEDATE_out,"Returns the present date and time" },
	{ "UPDATE_FWKCONF",	_UPDATE_FWKCONF,__UPDATE_FWKCONF,	2,_UPDATE_FWKCONF_in,0,NULL,0,NULL,2,_UPDATE_FWKCONF_out,"Store current configuration parameters.\n  SPECS2.5: Added type parameter." },
	{ "VERIFY_FILE",	_VERIFY_FILE,__VERIFY_FILE,	2,_VERIFY_FILE_in,0,NULL,0,NULL,4,_VERIFY_FILE_out,"Description for this Algorithm spec." },
	{ "WAIT",	_WAIT,__WAIT,	1,_WAIT_in,0,NULL,0,NULL,0,NULL,"Waits for the speicifed duration" },
	{ "WRITE_CHAR",	_WRITE_CHAR,__WRITE_CHAR,	2,_WRITE_CHAR_in,0,NULL,0,NULL,2,_WRITE_CHAR_out,"Writes a CHARACTER value to a STRING variable" },
	{ "WRITE_INTEGER",	_WRITE_INTEGER,__WRITE_INTEGER,	2,_WRITE_INTEGER_in,0,NULL,0,NULL,2,_WRITE_INTEGER_out,"Writes an INTEGER value to a STRING variable" },
	{ "WRITE_REAL",	_WRITE_REAL,__WRITE_REAL,	2,_WRITE_REAL_in,0,NULL,0,NULL,2,_WRITE_REAL_out,"Writes a REAL value to a STRING variable" },
	{ "WRITE_STRING",	_WRITE_STRING,__WRITE_STRING,	2,_WRITE_STRING_in,0,NULL,0,NULL,2,_WRITE_STRING_out,"Writes a STRING value to a STRING variable" },
	{ "WRITE_WAFER_SUM",	_WRITE_WAFER_SUM,__WRITE_WAFER_SUM,	6,_WRITE_WAFER_SUM_in,0,NULL,0,NULL,1,_WRITE_WAFER_SUM_out,"Description for this Algorithm spec." },
	{ "XWUD",	_XWUD,__XWUD,	4,_XWUD_in,0,NULL,0,NULL,0,NULL,"Executes the xwud(1) command to display a window image, which is stored in the specified dump file" },
	{ "YIELDLOG_WAFEND",	_YIELDLOG_WAFEND,__YIELDLOG_WAFEND,	2,_YIELDLOG_WAFEND_in,0,NULL,0,NULL,0,NULL,"Logs yield on the specified file. This uses user bin.\n" },
};

_LIBDEF	__UTIL_FA[] = {
	{ sizeof(_UTIL_FA)/sizeof(_ALGDEF), _UTIL_FA }
};

static char *___UTIL_FA[] = {
"@(#)USRFLGS=",
"@(#)USRHDRS=-I/opt/hp4070/include -I/opt/sicl/include",
"@(#)",
"@(#)USRLINK=",
"@(#)USRLIBS=",
"@(#)TSTLINK=-L/opt/hp4070/lib",
"@(#)TSTLIBS=",
"@(#)",
};
