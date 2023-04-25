#include <SPECS.h>
#include <SPECS_SYS.h>

/* Definition for algorithm PROBER_ABORT */

extern void _PROBER_ABORT(void *, void *);
extern void __PROBER_ABORT(void *);

static _VARDEF	_PROBER_ABORT_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_ABORT_I */

extern void _PROBER_ABORT_I(void *, void *);
extern void __PROBER_ABORT_I(void *);

static _VARDEF	_PROBER_ABORT_I_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_ABORT_S */

extern void _PROBER_ABORT_S(void *, void *);
extern void __PROBER_ABORT_S(void *);

static _VARDEF	_PROBER_ABORT_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_ALIGN */

extern void _PROBER_ALIGN(void *, void *);
extern void __PROBER_ALIGN(void *);

static _VARDEF	_PROBER_ALIGN_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_ALIGN_I */

extern void _PROBER_ALIGN_I(void *, void *);
extern void __PROBER_ALIGN_I(void *);

static _VARDEF	_PROBER_ALIGN_I_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_ALIGN_S */

extern void _PROBER_ALIGN_S(void *, void *);
extern void __PROBER_ALIGN_S(void *);

static _VARDEF	_PROBER_ALIGN_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_CASSINFO */

extern void _PROBER_CASSINFO(void *, void *);
extern void __PROBER_CASSINFO(void *);

static _VARDEF	_PROBER_CASSINFO_out[] = {
	{ "Slotno", "",_TYPEI, 0,0,0, "Wafer slot position", "0" },
	{ "Cassno", "",_TYPEI, 0,0,0, "Cassette number of wafer origine", "0" },
	{ "Wafcount", "",_TYPEI, 0,0,0, "Remaining number of wafers in current cassette", "0" },
	{ "Casscount", "",_TYPEI, 0,0,0, "Remaining number of cassettes", "0" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_CASSMAP */

extern void _PROBER_CASSMAP(void *, void *);
extern void __PROBER_CASSMAP(void *);

static _VARDEF	_PROBER_CASSMAP_out[] = {
	{ "Cassmap", "",_TYPEI, 1,50,0, "Cassette map", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_CHKMOVE */

extern void _PROBER_CHKMOVE(void *, void *);
extern void __PROBER_CHKMOVE(void *);

static _VARDEF	_PROBER_CHKMOVE_in[] = {
	{ "Xdist", "",_TYPER, 0,0,0, "X(R-L) Movement distance in [um]", "0" },
	{ "Ydist", "",_TYPER, 0,0,0, "Y(F-B) Movement distance in [um]", "0" },
};
static _VARDEF	_PROBER_CHKMOVE_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_CLEAN */

extern void _PROBER_CLEAN(void *, void *);
extern void __PROBER_CLEAN(void *);

static _VARDEF	_PROBER_CLEAN_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_CMAPODR */

extern void _PROBER_CMAPODR(void *, void *);
extern void __PROBER_CMAPODR(void *);

static _VARDEF	_PROBER_CMAPODR_in[] = {
	{ "Cassno", "",_TYPES, 0,0,0, "", "1" },
	{ "Slotstat", "",_TYPEI, 1,50,0, "Cassette map to be set. (0:SKIP, 1:UNPROBED)", "" },
};
static _VARDEF	_PROBER_CMAPODR_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_CONFIG */

extern void _PROBER_CONFIG(void *, void *);
extern void __PROBER_CONFIG(void *);

static _VARDEF	_PROBER_CONFIG_in[] = {
	{ "Model", "",_TYPES, 0,0,0, "Prober Model Name", "" },
	{ "Address", "",_TYPEI, 0,0,0, "Prober GPIB Address", "0" },
};
static _VARDEF	_PROBER_CONFIG_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_DOWN */

extern void _PROBER_DOWN(void *, void *);
extern void __PROBER_DOWN(void *);

static _VARDEF	_PROBER_DOWN_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_FLATCOMP */

extern void _PROBER_FLATCOMP(void *, void *);
extern void __PROBER_FLATCOMP(void *);

static _VARDEF	_PROBER_FLATCOMP_in[] = {
	{ "Tpl_OriFla", "",_TYPEI, 0,0,0, "Flat angle defined in TPL", "-1" },
};
static _VARDEF	_PROBER_FLATCOMP_out[] = {
	{ "Prb_OriFla", "",_TYPEI, 0,0,0, "Flat angle defined in prober", "0" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_GETCMAP */

extern void _PROBER_GETCMAP(void *, void *);
extern void __PROBER_GETCMAP(void *);

static _VARDEF	_PROBER_GETCMAP_in[] = {
	{ "Cassno", "",_TYPES, 0,0,0, "", "1" },
};
static _VARDEF	_PROBER_GETCMAP_out[] = {
	{ "Cassmap", "",_TYPEI, 1,50,0, "Cassette map to be set. (0:SKIP, 1:UNPROBED)", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_HOME */

extern void _PROBER_HOME(void *, void *);
extern void __PROBER_HOME(void *);

static _VARDEF	_PROBER_HOME_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_IENTER */

extern void _PROBER_IENTER(void *, void *);
extern void __PROBER_IENTER(void *);

static _VARDEF	_PROBER_IENTER_in[] = {
	{ "Timeout", "",_TYPEI, 0,0,0, "", "0" },
};
static _VARDEF	_PROBER_IENTER_out[] = {
	{ "Dt", "",_TYPES, 0,0,0, "", "" },
	{ "Status", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm PROBER_INITIAL */

extern void _PROBER_INITIAL(void *, void *);
extern void __PROBER_INITIAL(void *);

static _VARDEF	_PROBER_INITIAL_in[] = {
	{ "DieX", "",_TYPER, 0,0,0, "Initial Die X position from wafer origin in um", "0" },
	{ "DieY", "",_TYPER, 0,0,0, "Initial Die Y position from wafer origin in um", "0" },
	{ "ModX", "",_TYPER, 0,0,0, "Initial Module X position from die origin in um", "0" },
	{ "ModY", "",_TYPER, 0,0,0, "Initial Module Y position from die origin in um", "0" },
	{ "StepX", "",_TYPER, 0,0,0, "X index size in um", "0" },
	{ "StepY", "",_TYPER, 0,0,0, "Y index size in um", "0" },
	{ "Coord", "",_TYPEI, 0,0,0, "XY Coordinate System (1..4)", "1" },
};
static _VARDEF	_PROBER_INITIAL_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_INKER */

extern void _PROBER_INKER(void *, void *);
extern void __PROBER_INKER(void *);

static _VARDEF	_PROBER_INKER_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_IOUTPUT */

extern void _PROBER_IOUTPUT(void *, void *);
extern void __PROBER_IOUTPUT(void *);

static _VARDEF	_PROBER_IOUTPUT_in[] = {
	{ "Cmd", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_PROBER_IOUTPUT_out[] = {
	{ "Status", "",_TYPEI, 0,0,0, "", "0" },
};

/* Definition for algorithm PROBER_LOAD */

extern void _PROBER_LOAD(void *, void *);
extern void __PROBER_LOAD(void *);

static _VARDEF	_PROBER_LOAD_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_LOAD_I */

extern void _PROBER_LOAD_I(void *, void *);
extern void __PROBER_LOAD_I(void *);

static _VARDEF	_PROBER_LOAD_I_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_LOAD_S */

extern void _PROBER_LOAD_S(void *, void *);
extern void __PROBER_LOAD_S(void *);

static _VARDEF	_PROBER_LOAD_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_LOG */

extern void _PROBER_LOG(void *, void *);
extern void __PROBER_LOG(void *);

static _VARDEF	_PROBER_LOG_out[] = {
	{ "Logmode", "",_TYPEI, 0,0,0, "GPIB I/O Log mode (0:OFF/1:ON)", "0" },
};

/* Definition for algorithm PROBER_LOGWR */

extern void _PROBER_LOGWR(void *, void *);
extern void __PROBER_LOGWR(void *);

static _VARDEF	_PROBER_LOGWR_in[] = {
	{ "Message", "",_TYPES, 0,0,0, "", "" },
};
static _VARDEF	_PROBER_LOGWR_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_LOTEND */

extern void _PROBER_LOTEND(void *, void *);
extern void __PROBER_LOTEND(void *);

static _VARDEF	_PROBER_LOTEND_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_LOTID */

extern void _PROBER_LOTID(void *, void *);
extern void __PROBER_LOTID(void *);

static _VARDEF	_PROBER_LOTID_out[] = {
	{ "Lotid", "",_TYPES, 0,0,0, "Lot ID currently tested", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_MOVE */

extern void _PROBER_MOVE(void *, void *);
extern void __PROBER_MOVE(void *);

static _VARDEF	_PROBER_MOVE_in[] = {
	{ "DieX", "",_TYPER, 0,0,0, "Die X position from wafer origin in um", "0" },
	{ "DieY", "",_TYPER, 0,0,0, "Die Y position from wafer origin in um", "0" },
	{ "ModX", "",_TYPER, 0,0,0, "Module X position from die origin in um", "0" },
	{ "ModY", "",_TYPER, 0,0,0, "Module Y position from die origin in um", "0" },
};
static _VARDEF	_PROBER_MOVE_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_PAUSE */

extern void _PROBER_PAUSE(void *, void *);
extern void __PROBER_PAUSE(void *);

static _VARDEF	_PROBER_PAUSE_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_PRODID */

extern void _PROBER_PRODID(void *, void *);
extern void __PROBER_PRODID(void *);

static _VARDEF	_PROBER_PRODID_out[] = {
	{ "Prodid", "",_TYPES, 0,0,0, "ID of product tested", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_READ */

extern void _PROBER_READ(void *, void *);
extern void __PROBER_READ(void *);

static _VARDEF	_PROBER_READ_out[] = {
	{ "Ent_val", "",_TYPES, 0,0,0, "String ENTERed from GPIB", "" },
	{ "Status", "",_TYPES, 0,0,0, "Status, \"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_READY */

extern void _PROBER_READY(void *, void *);
extern void __PROBER_READY(void *);

static _VARDEF	_PROBER_READY_in[] = {
	{ "Timeout", "sec",_TYPEI, 0,0,0, "Wait time for SRQ", "300" },
};
static _VARDEF	_PROBER_READY_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_REJECT */

extern void _PROBER_REJECT(void *, void *);
extern void __PROBER_REJECT(void *);

static _VARDEF	_PROBER_REJECT_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\" or \"END\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_RETEST */

extern void _PROBER_RETEST(void *, void *);
extern void __PROBER_RETEST(void *);

static _VARDEF	_PROBER_RETEST_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_RJLOT_I */

extern void _PROBER_RJLOT_I(void *, void *);
extern void __PROBER_RJLOT_I(void *);

static _VARDEF	_PROBER_RJLOT_I_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_RJLOT_S */

extern void _PROBER_RJLOT_S(void *, void *);
extern void __PROBER_RJLOT_S(void *);

static _VARDEF	_PROBER_RJLOT_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_SENDCMD */

extern void _PROBER_SENDCMD(void *, void *);
extern void __PROBER_SENDCMD(void *);

static _VARDEF	_PROBER_SENDCMD_in[] = {
	{ "Command", "",_TYPES, 0,0,0, "GPIB Command to be OUTPUT", "" },
};
static _VARDEF	_PROBER_SENDCMD_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_SETCMAP */

extern void _PROBER_SETCMAP(void *, void *);
extern void __PROBER_SETCMAP(void *);

static _VARDEF	_PROBER_SETCMAP_in[] = {
	{ "Cassno", "",_TYPES, 0,0,0, "", "1" },
	{ "SlotStat", "",_TYPEI, 1,50,0, "Cassette map to be set. (0:SKIP, 1:UNPROBED)", "" },
};
static _VARDEF	_PROBER_SETCMAP_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_SETUP */

extern void _PROBER_SETUP(void *, void *);
extern void __PROBER_SETUP(void *);

static _VARDEF	_PROBER_SETUP_in[] = {
	{ "Drive", "",_TYPES, 0,0,0, "Setup filename", "" },
	{ "Filename", "",_TYPES, 0,0,0, "Setup filename", "" },
};
static _VARDEF	_PROBER_SETUP_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_SLOAD */

extern void _PROBER_SLOAD(void *, void *);
extern void __PROBER_SLOAD(void *);

static _VARDEF	_PROBER_SLOAD_in[] = {
	{ "Cassno", "",_TYPEI, 0,0,0, "1 or 2", "0" },
	{ "Slotno", "",_TYPEI, 0,0,0, "1 to 25", "0" },
};
static _VARDEF	_PROBER_SLOAD_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_SLOAD_I */

extern void _PROBER_SLOAD_I(void *, void *);
extern void __PROBER_SLOAD_I(void *);

static _VARDEF	_PROBER_SLOAD_I_in[] = {
	{ "Cassno", "",_TYPEI, 0,0,0, "1 or 2", "0" },
	{ "Slotno", "",_TYPEI, 0,0,0, "1 to 25", "0" },
};
static _VARDEF	_PROBER_SLOAD_I_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_SLOAD_S */

extern void _PROBER_SLOAD_S(void *, void *);
extern void __PROBER_SLOAD_S(void *);

static _VARDEF	_PROBER_SLOAD_S_in[] = {
	{ "Cassno", "",_TYPEI, 0,0,0, "1 or 2", "0" },
	{ "Slotno", "",_TYPEI, 0,0,0, "1 to 25", "0" },
};
static _VARDEF	_PROBER_SLOAD_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_SRQ */

extern void _PROBER_SRQ(void *, void *);
extern void __PROBER_SRQ(void *);

static _VARDEF	_PROBER_SRQ_in[] = {
	{ "Timeout", "",_TYPEI, 0,0,0, "Timeout in seconds", "5" },
};
static _VARDEF	_PROBER_SRQ_out[] = {
	{ "Statusbyte", "",_TYPEI, 0,0,0, "Status byte", "0" },
};

/* Definition for algorithm PROBER_TEMPMON */

extern void _PROBER_TEMPMON(void *, void *);
extern void __PROBER_TEMPMON(void *);

static _VARDEF	_PROBER_TEMPMON_out[] = {
	{ "Montemp", "",_TYPER, 0,0,0, "Monitor temperature", "0" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_TEMPSET */

extern void _PROBER_TEMPSET(void *, void *);
extern void __PROBER_TEMPSET(void *);

static _VARDEF	_PROBER_TEMPSET_in[] = {
	{ "Settemp", "",_TYPER, 0,0,0, "Set temperature", "0" },
};
static _VARDEF	_PROBER_TEMPSET_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_UNLOAD */

extern void _PROBER_UNLOAD(void *, void *);
extern void __PROBER_UNLOAD(void *);

static _VARDEF	_PROBER_UNLOAD_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_UNLOAD_I */

extern void _PROBER_UNLOAD_I(void *, void *);
extern void __PROBER_UNLOAD_I(void *);

static _VARDEF	_PROBER_UNLOAD_I_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_UNLOAD_S */

extern void _PROBER_UNLOAD_S(void *, void *);
extern void __PROBER_UNLOAD_S(void *);

static _VARDEF	_PROBER_UNLOAD_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_UP */

extern void _PROBER_UP(void *, void *);
extern void __PROBER_UP(void *);

static _VARDEF	_PROBER_UP_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_WAFID */

extern void _PROBER_WAFID(void *, void *);
extern void __PROBER_WAFID(void *);

static _VARDEF	_PROBER_WAFID_out[] = {
	{ "Wafid", "",_TYPES, 0,0,0, "ID of wafer on the chuck", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm PROBER_WRITE */

extern void _PROBER_WRITE(void *, void *);
extern void __PROBER_WRITE(void *);

static _VARDEF	_PROBER_WRITE_in[] = {
	{ "Command", "",_TYPES, 0,0,0, "GPIB command to be output", "" },
};
static _VARDEF	_PROBER_WRITE_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "Status, \"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_ABORT */

extern void _TELP12_ABORT(void *, void *);
extern void __TELP12_ABORT(void *);

static _VARDEF	_TELP12_ABORT_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_ABORT_S */

extern void _TELP12_ABORT_S(void *, void *);
extern void __TELP12_ABORT_S(void *);

static _VARDEF	_TELP12_ABORT_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_ALIGN */

extern void _TELP12_ALIGN(void *, void *);
extern void __TELP12_ALIGN(void *);

static _VARDEF	_TELP12_ALIGN_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_ALIGN_S */

extern void _TELP12_ALIGN_S(void *, void *);
extern void __TELP12_ALIGN_S(void *);

static _VARDEF	_TELP12_ALIGN_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_CASSINFO */

extern void _TELP12_CASSINFO(void *, void *);
extern void __TELP12_CASSINFO(void *);

static _VARDEF	_TELP12_CASSINFO_out[] = {
	{ "Slotno", "",_TYPEI, 0,0,0, "Wafer slot position", "0" },
	{ "Cassno", "",_TYPEI, 0,0,0, "Cassette number of wafer origine", "0" },
	{ "Wafcount", "",_TYPEI, 0,0,0, "Remaining number of wafers in current cassette", "0" },
	{ "Casscount", "",_TYPEI, 0,0,0, "Remaining number of cassettes", "0" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_CASSMAP */

extern void _TELP12_CASSMAP(void *, void *);
extern void __TELP12_CASSMAP(void *);

static _VARDEF	_TELP12_CASSMAP_out[] = {
	{ "Cassmap", "",_TYPEI, 1,50,0, "Cassette map", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_CHKMOVE */

extern void _TELP12_CHKMOVE(void *, void *);
extern void __TELP12_CHKMOVE(void *);

static _VARDEF	_TELP12_CHKMOVE_in[] = {
	{ "Xdist", "",_TYPER, 0,0,0, "X(R-L) Movement distance in [um]", "0" },
	{ "Ydist", "",_TYPER, 0,0,0, "Y(F-B) Movement distance in [um]", "0" },
};
static _VARDEF	_TELP12_CHKMOVE_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_CLEAN */

extern void _TELP12_CLEAN(void *, void *);
extern void __TELP12_CLEAN(void *);

static _VARDEF	_TELP12_CLEAN_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_CMAPODR */

extern void _TELP12_CMAPODR(void *, void *);
extern void __TELP12_CMAPODR(void *);

static _VARDEF	_TELP12_CMAPODR_in[] = {
	{ "Cassno", "",_TYPES, 0,0,0, "", "1" },
	{ "Slotstat", "",_TYPEI, 1,50,0, "Cassette map to be set. (0:SKIP, 1:UNPROBED)", "" },
};
static _VARDEF	_TELP12_CMAPODR_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_DOWN */

extern void _TELP12_DOWN(void *, void *);
extern void __TELP12_DOWN(void *);

static _VARDEF	_TELP12_DOWN_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_FLATCOMP */

extern void _TELP12_FLATCOMP(void *, void *);
extern void __TELP12_FLATCOMP(void *);

static _VARDEF	_TELP12_FLATCOMP_in[] = {
	{ "Tpl_OriFla", "",_TYPEI, 0,0,0, "Flat angle defined in TPL", "-1" },
};
static _VARDEF	_TELP12_FLATCOMP_out[] = {
	{ "Prb_OriFla", "",_TYPEI, 0,0,0, "Flat angle defined in prober", "0" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_GETCMAP */

extern void _TELP12_GETCMAP(void *, void *);
extern void __TELP12_GETCMAP(void *);

static _VARDEF	_TELP12_GETCMAP_in[] = {
	{ "Cassno", "",_TYPES, 0,0,0, "", "1" },
};
static _VARDEF	_TELP12_GETCMAP_out[] = {
	{ "Cassmap", "",_TYPEI, 1,50,0, "Cassette map to be set. (0:SKIP, 1:UNPROBED)", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_HOME */

extern void _TELP12_HOME(void *, void *);
extern void __TELP12_HOME(void *);

static _VARDEF	_TELP12_HOME_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_INITIAL */

extern void _TELP12_INITIAL(void *, void *);
extern void __TELP12_INITIAL(void *);

static _VARDEF	_TELP12_INITIAL_in[] = {
	{ "DieX", "",_TYPER, 0,0,0, "Initial Die X position from wafer origin in um", "0" },
	{ "DieY", "",_TYPER, 0,0,0, "Initial Die Y position from wafer origin in um", "0" },
	{ "ModX", "",_TYPER, 0,0,0, "Initial Module X position from die origin in um", "0" },
	{ "ModY", "",_TYPER, 0,0,0, "Initial Module Y position from die origin in um", "0" },
	{ "StepX", "",_TYPER, 0,0,0, "X index size in um", "0" },
	{ "StepY", "",_TYPER, 0,0,0, "Y index size in um", "0" },
	{ "Coord", "",_TYPEI, 0,0,0, "XY Coordinate System (1..4)", "1" },
};
static _VARDEF	_TELP12_INITIAL_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_INKER */

extern void _TELP12_INKER(void *, void *);
extern void __TELP12_INKER(void *);

static _VARDEF	_TELP12_INKER_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_LOAD */

extern void _TELP12_LOAD(void *, void *);
extern void __TELP12_LOAD(void *);

static _VARDEF	_TELP12_LOAD_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_LOAD_S */

extern void _TELP12_LOAD_S(void *, void *);
extern void __TELP12_LOAD_S(void *);

static _VARDEF	_TELP12_LOAD_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_LOTEND */

extern void _TELP12_LOTEND(void *, void *);
extern void __TELP12_LOTEND(void *);

static _VARDEF	_TELP12_LOTEND_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_LOTID */

extern void _TELP12_LOTID(void *, void *);
extern void __TELP12_LOTID(void *);

static _VARDEF	_TELP12_LOTID_out[] = {
	{ "Lotid", "",_TYPES, 0,0,0, "Lot ID currently tested", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_MOVE */

extern void _TELP12_MOVE(void *, void *);
extern void __TELP12_MOVE(void *);

static _VARDEF	_TELP12_MOVE_in[] = {
	{ "DieX", "",_TYPER, 0,0,0, "Die X position from wafer origin in um", "0" },
	{ "DieY", "",_TYPER, 0,0,0, "Die Y position from wafer origin in um", "0" },
	{ "ModX", "",_TYPER, 0,0,0, "Module X position from die origin in um", "0" },
	{ "ModY", "",_TYPER, 0,0,0, "Module Y position from die origin in um", "0" },
};
static _VARDEF	_TELP12_MOVE_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_PAUSE */

extern void _TELP12_PAUSE(void *, void *);
extern void __TELP12_PAUSE(void *);

static _VARDEF	_TELP12_PAUSE_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_PRODID */

extern void _TELP12_PRODID(void *, void *);
extern void __TELP12_PRODID(void *);

static _VARDEF	_TELP12_PRODID_out[] = {
	{ "Prodid", "",_TYPES, 0,0,0, "Product ID tested", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_READY */

extern void _TELP12_READY(void *, void *);
extern void __TELP12_READY(void *);

static _VARDEF	_TELP12_READY_in[] = {
	{ "Timeout", "sec",_TYPEI, 0,0,0, "Wait time for SRQ", "300" },
};
static _VARDEF	_TELP12_READY_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_REJECT */

extern void _TELP12_REJECT(void *, void *);
extern void __TELP12_REJECT(void *);

static _VARDEF	_TELP12_REJECT_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\" or \"END\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_RETEST */

extern void _TELP12_RETEST(void *, void *);
extern void __TELP12_RETEST(void *);

static _VARDEF	_TELP12_RETEST_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_RJLOT_I */

extern void _TELP12_RJLOT_I(void *, void *);
extern void __TELP12_RJLOT_I(void *);

static _VARDEF	_TELP12_RJLOT_I_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_RJLOT_S */

extern void _TELP12_RJLOT_S(void *, void *);
extern void __TELP12_RJLOT_S(void *);

static _VARDEF	_TELP12_RJLOT_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_SETCMAP */

extern void _TELP12_SETCMAP(void *, void *);
extern void __TELP12_SETCMAP(void *);

static _VARDEF	_TELP12_SETCMAP_in[] = {
	{ "Cassno", "",_TYPES, 0,0,0, "", "1" },
	{ "SlotStat", "",_TYPEI, 1,50,0, "Cassette map to be set. (0:SKIP, 1:UNPROBED)", "" },
};
static _VARDEF	_TELP12_SETCMAP_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_SETUP */

extern void _TELP12_SETUP(void *, void *);
extern void __TELP12_SETUP(void *);

static _VARDEF	_TELP12_SETUP_in[] = {
	{ "Drive", "",_TYPES, 0,0,0, "Setup filename", "" },
	{ "Filename", "",_TYPES, 0,0,0, "Setup filename", "" },
};
static _VARDEF	_TELP12_SETUP_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_SLOAD */

extern void _TELP12_SLOAD(void *, void *);
extern void __TELP12_SLOAD(void *);

static _VARDEF	_TELP12_SLOAD_in[] = {
	{ "Cassno", "",_TYPEI, 0,0,0, "1 or 2", "0" },
	{ "Slotno", "",_TYPEI, 0,0,0, "1 to 25", "0" },
};
static _VARDEF	_TELP12_SLOAD_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_SLOAD_S */

extern void _TELP12_SLOAD_S(void *, void *);
extern void __TELP12_SLOAD_S(void *);

static _VARDEF	_TELP12_SLOAD_S_in[] = {
	{ "Cassno", "",_TYPEI, 0,0,0, "1 or 2", "0" },
	{ "Slotno", "",_TYPEI, 0,0,0, "1 to 25", "0" },
};
static _VARDEF	_TELP12_SLOAD_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_TEMPMON */

extern void _TELP12_TEMPMON(void *, void *);
extern void __TELP12_TEMPMON(void *);

static _VARDEF	_TELP12_TEMPMON_out[] = {
	{ "Montemp", "",_TYPER, 0,0,0, "Monitor temperature", "0" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_TEMPSET */

extern void _TELP12_TEMPSET(void *, void *);
extern void __TELP12_TEMPSET(void *);

static _VARDEF	_TELP12_TEMPSET_in[] = {
	{ "Settemp", "",_TYPER, 0,0,0, "Set temperature", "0" },
};
static _VARDEF	_TELP12_TEMPSET_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_UNLOAD */

extern void _TELP12_UNLOAD(void *, void *);
extern void __TELP12_UNLOAD(void *);

static _VARDEF	_TELP12_UNLOAD_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_UNLOAD_S */

extern void _TELP12_UNLOAD_S(void *, void *);
extern void __TELP12_UNLOAD_S(void *);

static _VARDEF	_TELP12_UNLOAD_S_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_UP */

extern void _TELP12_UP(void *, void *);
extern void __TELP12_UP(void *);

static _VARDEF	_TELP12_UP_out[] = {
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for algorithm TELP12_WAFID */

extern void _TELP12_WAFID(void *, void *);
extern void __TELP12_WAFID(void *);

static _VARDEF	_TELP12_WAFID_out[] = {
	{ "Wafid", "",_TYPES, 0,0,0, "ID of wafer on the chuck", "" },
	{ "Status", "",_TYPES, 0,0,0, "\"OK\" or \"ERROR\"", "" },
	{ "Error", "",_TYPES, 0,0,0, "Error message", "" },
};

/* Definition for library TELP12_FACOM */

static _ALGDEF	_TELP12_FACOM[] = {
	{ "PROBER_ABORT",	_PROBER_ABORT,__PROBER_ABORT,	0,NULL,0,NULL,0,NULL,2,_PROBER_ABORT_out,"Aborts the current lot test" },
	{ "PROBER_ABORT_I",	_PROBER_ABORT_I,__PROBER_ABORT_I,	0,NULL,0,NULL,0,NULL,2,_PROBER_ABORT_I_out,"Aborts the current lot test" },
	{ "PROBER_ABORT_S",	_PROBER_ABORT_S,__PROBER_ABORT_S,	0,NULL,0,NULL,0,NULL,2,_PROBER_ABORT_S_out,"Aborts the current lot test" },
	{ "PROBER_ALIGN",	_PROBER_ALIGN,__PROBER_ALIGN,	0,NULL,0,NULL,0,NULL,2,_PROBER_ALIGN_out,"Aligns wafer and move chuck to the initial position" },
	{ "PROBER_ALIGN_I",	_PROBER_ALIGN_I,__PROBER_ALIGN_I,	0,NULL,0,NULL,0,NULL,2,_PROBER_ALIGN_I_out,"Aligns wafer and move chuck to the initial position" },
	{ "PROBER_ALIGN_S",	_PROBER_ALIGN_S,__PROBER_ALIGN_S,	0,NULL,0,NULL,0,NULL,2,_PROBER_ALIGN_S_out,"Aligns wafer and move chuck to the initial position" },
	{ "PROBER_CASSINFO",	_PROBER_CASSINFO,__PROBER_CASSINFO,	0,NULL,0,NULL,0,NULL,6,_PROBER_CASSINFO_out,"Returns cassette information" },
	{ "PROBER_CASSMAP",	_PROBER_CASSMAP,__PROBER_CASSMAP,	0,NULL,0,NULL,0,NULL,3,_PROBER_CASSMAP_out,"Returns cassette map" },
	{ "PROBER_CHKMOVE",	_PROBER_CHKMOVE,__PROBER_CHKMOVE,	2,_PROBER_CHKMOVE_in,0,NULL,0,NULL,2,_PROBER_CHKMOVE_out,"Moves the chuck by X/Ydist[um] relatively" },
	{ "PROBER_CLEAN",	_PROBER_CLEAN,__PROBER_CLEAN,	0,NULL,0,NULL,0,NULL,2,_PROBER_CLEAN_out,"Executes probe cleaning with cleaning plate" },
	{ "PROBER_CMAPODR",	_PROBER_CMAPODR,__PROBER_CMAPODR,	2,_PROBER_CMAPODR_in,0,NULL,0,NULL,2,_PROBER_CMAPODR_out,"[UPDATE] Set cassette map of the current cassette." },
	{ "PROBER_CONFIG",	_PROBER_CONFIG,__PROBER_CONFIG,	2,_PROBER_CONFIG_in,0,NULL,0,NULL,2,_PROBER_CONFIG_out,"Defines the prober model and GPIB address" },
	{ "PROBER_DOWN",	_PROBER_DOWN,__PROBER_DOWN,	0,NULL,0,NULL,0,NULL,2,_PROBER_DOWN_out,"Lowers the wafer chuck (stage) to disconnect from the probe card" },
	{ "PROBER_FLATCOMP",	_PROBER_FLATCOMP,__PROBER_FLATCOMP,	1,_PROBER_FLATCOMP_in,0,NULL,0,NULL,3,_PROBER_FLATCOMP_out,"Gets prober orientation flat angle and save delta from TPL" },
	{ "PROBER_GETCMAP",	_PROBER_GETCMAP,__PROBER_GETCMAP,	1,_PROBER_GETCMAP_in,0,NULL,0,NULL,3,_PROBER_GETCMAP_out,"[NEW] Get cassette map by using GPIB command \"?CS\" to the prober" },
	{ "PROBER_HOME",	_PROBER_HOME,__PROBER_HOME,	0,NULL,0,NULL,0,NULL,2,_PROBER_HOME_out,"Moves the wafer chuck (stage) to the initial position" },
	{ "PROBER_IENTER",	_PROBER_IENTER,__PROBER_IENTER,	1,_PROBER_IENTER_in,0,NULL,0,NULL,2,_PROBER_IENTER_out,"[NEW] Call PROBER_ENTER or FA_ENTER when OFFLINE case.\nDate:\t['01/06/20] Initial revision" },
	{ "PROBER_INITIAL",	_PROBER_INITIAL,__PROBER_INITIAL,	7,_PROBER_INITIAL_in,0,NULL,0,NULL,2,_PROBER_INITIAL_out,"Defines the initial die/module location" },
	{ "PROBER_INKER",	_PROBER_INKER,__PROBER_INKER,	0,NULL,0,NULL,0,NULL,2,_PROBER_INKER_out,"Drives inker" },
	{ "PROBER_IOUTPUT",	_PROBER_IOUTPUT,__PROBER_IOUTPUT,	1,_PROBER_IOUTPUT_in,0,NULL,0,NULL,1,_PROBER_IOUTPUT_out,"[NEW] Call PROBER_OUTPUT or FA_OUTPUT when OFFLINE case.\nDate:\t['01/06/20] Initial revision" },
	{ "PROBER_LOAD",	_PROBER_LOAD,__PROBER_LOAD,	0,NULL,0,NULL,0,NULL,2,_PROBER_LOAD_out,"[UPDATE] Unloads the present wafer and loads the next wafer from cassette" },
	{ "PROBER_LOAD_I",	_PROBER_LOAD_I,__PROBER_LOAD_I,	0,NULL,0,NULL,0,NULL,2,_PROBER_LOAD_I_out,"[UPDATE] Unloads the present wafer and loads the next wafer from cassette" },
	{ "PROBER_LOAD_S",	_PROBER_LOAD_S,__PROBER_LOAD_S,	0,NULL,0,NULL,0,NULL,2,_PROBER_LOAD_S_out,"[NEW] Unloads the present wafer and loads the next wafer from cassette" },
	{ "PROBER_LOG",	_PROBER_LOG,__PROBER_LOG,	0,NULL,0,NULL,0,NULL,1,_PROBER_LOG_out,"Defines GPIB I/O log mode" },
	{ "PROBER_LOGWR",	_PROBER_LOGWR,__PROBER_LOGWR,	1,_PROBER_LOGWR_in,0,NULL,0,NULL,2,_PROBER_LOGWR_out,"Write Message in /var/opt/SPECS/log/prober.log" },
	{ "PROBER_LOTEND",	_PROBER_LOTEND,__PROBER_LOTEND,	0,NULL,0,NULL,0,NULL,2,_PROBER_LOTEND_out,"[NEW] Finishes lot completely" },
	{ "PROBER_LOTID",	_PROBER_LOTID,__PROBER_LOTID,	0,NULL,0,NULL,0,NULL,3,_PROBER_LOTID_out,"Returns Lot ID currently tested" },
	{ "PROBER_MOVE",	_PROBER_MOVE,__PROBER_MOVE,	4,_PROBER_MOVE_in,0,NULL,0,NULL,2,_PROBER_MOVE_out,"Moves the wafer chuck (stage) to the specified position" },
	{ "PROBER_PAUSE",	_PROBER_PAUSE,__PROBER_PAUSE,	0,NULL,0,NULL,0,NULL,2,_PROBER_PAUSE_out,"Pauses current lot test and turns ON prober light" },
	{ "PROBER_PRODID",	_PROBER_PRODID,__PROBER_PRODID,	0,NULL,0,NULL,0,NULL,3,_PROBER_PRODID_out,"Returns product ID currently tested" },
	{ "PROBER_READ",	_PROBER_READ,__PROBER_READ,	0,NULL,0,NULL,0,NULL,3,_PROBER_READ_out,"Reads GPIB data as string" },
	{ "PROBER_READY",	_PROBER_READY,__PROBER_READY,	1,_PROBER_READY_in,0,NULL,0,NULL,2,_PROBER_READY_out,"Waits for prober ready SRQ" },
	{ "PROBER_REJECT",	_PROBER_REJECT,__PROBER_REJECT,	0,NULL,0,NULL,0,NULL,2,_PROBER_REJECT_out,"[NEW] Rejects wafer to previously defined device" },
	{ "PROBER_RETEST",	_PROBER_RETEST,__PROBER_RETEST,	0,NULL,0,NULL,0,NULL,2,_PROBER_RETEST_out,"[NEW] Retest wafers" },
	{ "PROBER_RJLOT_I",	_PROBER_RJLOT_I,__PROBER_RJLOT_I,	0,NULL,0,NULL,0,NULL,2,_PROBER_RJLOT_I_out,"Aborts the current lot test" },
	{ "PROBER_RJLOT_S",	_PROBER_RJLOT_S,__PROBER_RJLOT_S,	0,NULL,0,NULL,0,NULL,2,_PROBER_RJLOT_S_out,"Aborts the current lot test" },
	{ "PROBER_SENDCMD",	_PROBER_SENDCMD,__PROBER_SENDCMD,	1,_PROBER_SENDCMD_in,0,NULL,0,NULL,2,_PROBER_SENDCMD_out,"[NEW] Call PROBER_OUTPUT or FA_OUTPUT when OFFLINE case.\nDate:\t['01/06/20] Initial revision" },
	{ "PROBER_SETCMAP",	_PROBER_SETCMAP,__PROBER_SETCMAP,	2,_PROBER_SETCMAP_in,0,NULL,0,NULL,2,_PROBER_SETCMAP_out,"[UPDATE] Set cassette map of the current cassette." },
	{ "PROBER_SETUP",	_PROBER_SETUP,__PROBER_SETUP,	2,_PROBER_SETUP_in,0,NULL,0,NULL,2,_PROBER_SETUP_out,"Specifies product file name" },
	{ "PROBER_SLOAD",	_PROBER_SLOAD,__PROBER_SLOAD,	2,_PROBER_SLOAD_in,0,NULL,0,NULL,2,_PROBER_SLOAD_out,"[UPDATE] Loads specified wafer from the specified cassette." },
	{ "PROBER_SLOAD_I",	_PROBER_SLOAD_I,__PROBER_SLOAD_I,	2,_PROBER_SLOAD_I_in,0,NULL,0,NULL,2,_PROBER_SLOAD_I_out,"[UPDATE] Loads specified wafer from the specified cassette." },
	{ "PROBER_SLOAD_S",	_PROBER_SLOAD_S,__PROBER_SLOAD_S,	2,_PROBER_SLOAD_S_in,0,NULL,0,NULL,2,_PROBER_SLOAD_S_out,"[NEW] Loads specified wafer from the specified cassette." },
	{ "PROBER_SRQ",	_PROBER_SRQ,__PROBER_SRQ,	1,_PROBER_SRQ_in,0,NULL,0,NULL,1,_PROBER_SRQ_out,"[UPDATE] Waits until SRQ is asserted" },
	{ "PROBER_TEMPMON",	_PROBER_TEMPMON,__PROBER_TEMPMON,	0,NULL,0,NULL,0,NULL,3,_PROBER_TEMPMON_out,"Returns hot chuck temperature" },
	{ "PROBER_TEMPSET",	_PROBER_TEMPSET,__PROBER_TEMPSET,	1,_PROBER_TEMPSET_in,0,NULL,0,NULL,2,_PROBER_TEMPSET_out,"Sets hot chuck temperature" },
	{ "PROBER_UNLOAD",	_PROBER_UNLOAD,__PROBER_UNLOAD,	0,NULL,0,NULL,0,NULL,2,_PROBER_UNLOAD_out,"Returns all the wafers to the original slot" },
	{ "PROBER_UNLOAD_I",	_PROBER_UNLOAD_I,__PROBER_UNLOAD_I,	0,NULL,0,NULL,0,NULL,2,_PROBER_UNLOAD_I_out,"Returns all the wafers to the original slot" },
	{ "PROBER_UNLOAD_S",	_PROBER_UNLOAD_S,__PROBER_UNLOAD_S,	0,NULL,0,NULL,0,NULL,2,_PROBER_UNLOAD_S_out,"Returns all the wafers to the original slot" },
	{ "PROBER_UP",	_PROBER_UP,__PROBER_UP,	0,NULL,0,NULL,0,NULL,2,_PROBER_UP_out,"Raises the wafer chuck (stage) to contact the probe card" },
	{ "PROBER_WAFID",	_PROBER_WAFID,__PROBER_WAFID,	0,NULL,0,NULL,0,NULL,3,_PROBER_WAFID_out,"Returns wafer ID on the chuck" },
	{ "PROBER_WRITE",	_PROBER_WRITE,__PROBER_WRITE,	1,_PROBER_WRITE_in,0,NULL,0,NULL,2,_PROBER_WRITE_out,"OUTPUTs string as a GPIB Command" },
	{ "TELP12_ABORT",	_TELP12_ABORT,__TELP12_ABORT,	0,NULL,0,NULL,0,NULL,2,_TELP12_ABORT_out,"Aborts the current lot test" },
	{ "TELP12_ABORT_S",	_TELP12_ABORT_S,__TELP12_ABORT_S,	0,NULL,0,NULL,0,NULL,2,_TELP12_ABORT_S_out,"Aborts the current lot test" },
	{ "TELP12_ALIGN",	_TELP12_ALIGN,__TELP12_ALIGN,	0,NULL,0,NULL,0,NULL,2,_TELP12_ALIGN_out,"Aligns wafer and move chuck to the initial position" },
	{ "TELP12_ALIGN_S",	_TELP12_ALIGN_S,__TELP12_ALIGN_S,	0,NULL,0,NULL,0,NULL,2,_TELP12_ALIGN_S_out,"Aligns wafer and move chuck to the initial position" },
	{ "TELP12_CASSINFO",	_TELP12_CASSINFO,__TELP12_CASSINFO,	0,NULL,0,NULL,0,NULL,6,_TELP12_CASSINFO_out,"Returns cassette information" },
	{ "TELP12_CASSMAP",	_TELP12_CASSMAP,__TELP12_CASSMAP,	0,NULL,0,NULL,0,NULL,3,_TELP12_CASSMAP_out,"Returns cassette map" },
	{ "TELP12_CHKMOVE",	_TELP12_CHKMOVE,__TELP12_CHKMOVE,	2,_TELP12_CHKMOVE_in,0,NULL,0,NULL,2,_TELP12_CHKMOVE_out,"Moves the chuck by X/Ydist[um] relatively" },
	{ "TELP12_CLEAN",	_TELP12_CLEAN,__TELP12_CLEAN,	0,NULL,0,NULL,0,NULL,2,_TELP12_CLEAN_out,"Executes probe cleaning with cleaning plate" },
	{ "TELP12_CMAPODR",	_TELP12_CMAPODR,__TELP12_CMAPODR,	2,_TELP12_CMAPODR_in,0,NULL,0,NULL,2,_TELP12_CMAPODR_out,"[UPDATE] Set cassette map of the current cassette." },
	{ "TELP12_DOWN",	_TELP12_DOWN,__TELP12_DOWN,	0,NULL,0,NULL,0,NULL,2,_TELP12_DOWN_out,"Lowers the wafer chuck (stage) to disconnect from the probe card" },
	{ "TELP12_FLATCOMP",	_TELP12_FLATCOMP,__TELP12_FLATCOMP,	1,_TELP12_FLATCOMP_in,0,NULL,0,NULL,3,_TELP12_FLATCOMP_out,"Gets prober orientation flat angle and save delta from TPL" },
	{ "TELP12_GETCMAP",	_TELP12_GETCMAP,__TELP12_GETCMAP,	1,_TELP12_GETCMAP_in,0,NULL,0,NULL,3,_TELP12_GETCMAP_out,"[NEW] Get cassette map by using GPIB command \"?CS\" to the prober" },
	{ "TELP12_HOME",	_TELP12_HOME,__TELP12_HOME,	0,NULL,0,NULL,0,NULL,2,_TELP12_HOME_out,"Moves the wafer chuck (stage) to the initial position" },
	{ "TELP12_INITIAL",	_TELP12_INITIAL,__TELP12_INITIAL,	7,_TELP12_INITIAL_in,0,NULL,0,NULL,2,_TELP12_INITIAL_out,"Defines the initial die/module location" },
	{ "TELP12_INKER",	_TELP12_INKER,__TELP12_INKER,	0,NULL,0,NULL,0,NULL,2,_TELP12_INKER_out,"Drives inker" },
	{ "TELP12_LOAD",	_TELP12_LOAD,__TELP12_LOAD,	0,NULL,0,NULL,0,NULL,2,_TELP12_LOAD_out,"[NEW] Unloads the present wafer and loads the next wafer from cassette" },
	{ "TELP12_LOAD_S",	_TELP12_LOAD_S,__TELP12_LOAD_S,	0,NULL,0,NULL,0,NULL,2,_TELP12_LOAD_S_out,"[NEW] Unloads the present wafer and loads the next wafer from cassette" },
	{ "TELP12_LOTEND",	_TELP12_LOTEND,__TELP12_LOTEND,	0,NULL,0,NULL,0,NULL,2,_TELP12_LOTEND_out,"[NEW] Finishes lot completely" },
	{ "TELP12_LOTID",	_TELP12_LOTID,__TELP12_LOTID,	0,NULL,0,NULL,0,NULL,3,_TELP12_LOTID_out,"Returns Lot ID currently tested" },
	{ "TELP12_MOVE",	_TELP12_MOVE,__TELP12_MOVE,	4,_TELP12_MOVE_in,0,NULL,0,NULL,2,_TELP12_MOVE_out,"Moves the wafer chuck (stage) to the specified position" },
	{ "TELP12_PAUSE",	_TELP12_PAUSE,__TELP12_PAUSE,	0,NULL,0,NULL,0,NULL,2,_TELP12_PAUSE_out,"Pauses current lot test and turns ON prober light" },
	{ "TELP12_PRODID",	_TELP12_PRODID,__TELP12_PRODID,	0,NULL,0,NULL,0,NULL,3,_TELP12_PRODID_out,"Returns product ID currently tested" },
	{ "TELP12_READY",	_TELP12_READY,__TELP12_READY,	1,_TELP12_READY_in,0,NULL,0,NULL,2,_TELP12_READY_out,"Waits for prober ready SRQ" },
	{ "TELP12_REJECT",	_TELP12_REJECT,__TELP12_REJECT,	0,NULL,0,NULL,0,NULL,2,_TELP12_REJECT_out,"[NEW] Rejects wafer to previously defined device" },
	{ "TELP12_RETEST",	_TELP12_RETEST,__TELP12_RETEST,	0,NULL,0,NULL,0,NULL,2,_TELP12_RETEST_out,"[NEW] Retest wafers" },
	{ "TELP12_RJLOT_I",	_TELP12_RJLOT_I,__TELP12_RJLOT_I,	0,NULL,0,NULL,0,NULL,2,_TELP12_RJLOT_I_out,"Unloads the present wafer and loads the next wafer from cassette" },
	{ "TELP12_RJLOT_S",	_TELP12_RJLOT_S,__TELP12_RJLOT_S,	0,NULL,0,NULL,0,NULL,2,_TELP12_RJLOT_S_out,"Unloads the present wafer and loads the next wafer from cassette" },
	{ "TELP12_SETCMAP",	_TELP12_SETCMAP,__TELP12_SETCMAP,	2,_TELP12_SETCMAP_in,0,NULL,0,NULL,2,_TELP12_SETCMAP_out,"[UPDATE] Set cassette map of the current cassette." },
	{ "TELP12_SETUP",	_TELP12_SETUP,__TELP12_SETUP,	2,_TELP12_SETUP_in,0,NULL,0,NULL,2,_TELP12_SETUP_out,"Specifies product file name" },
	{ "TELP12_SLOAD",	_TELP12_SLOAD,__TELP12_SLOAD,	2,_TELP12_SLOAD_in,0,NULL,0,NULL,2,_TELP12_SLOAD_out,"[NEW] Loads specified wafer from the specified cassette." },
	{ "TELP12_SLOAD_S",	_TELP12_SLOAD_S,__TELP12_SLOAD_S,	2,_TELP12_SLOAD_S_in,0,NULL,0,NULL,2,_TELP12_SLOAD_S_out,"[NEW] Loads specified wafer from the specified cassette." },
	{ "TELP12_TEMPMON",	_TELP12_TEMPMON,__TELP12_TEMPMON,	0,NULL,0,NULL,0,NULL,3,_TELP12_TEMPMON_out,"Returns hot chuck temperature" },
	{ "TELP12_TEMPSET",	_TELP12_TEMPSET,__TELP12_TEMPSET,	1,_TELP12_TEMPSET_in,0,NULL,0,NULL,2,_TELP12_TEMPSET_out,"Sets hot chuck temperature" },
	{ "TELP12_UNLOAD",	_TELP12_UNLOAD,__TELP12_UNLOAD,	0,NULL,0,NULL,0,NULL,2,_TELP12_UNLOAD_out,"Returns all the wafers to the original slot" },
	{ "TELP12_UNLOAD_S",	_TELP12_UNLOAD_S,__TELP12_UNLOAD_S,	0,NULL,0,NULL,0,NULL,2,_TELP12_UNLOAD_S_out,"Returns all the wafers to the original slot" },
	{ "TELP12_UP",	_TELP12_UP,__TELP12_UP,	0,NULL,0,NULL,0,NULL,2,_TELP12_UP_out,"Raises the wafer chuck (stage) to contact the probe card" },
	{ "TELP12_WAFID",	_TELP12_WAFID,__TELP12_WAFID,	0,NULL,0,NULL,0,NULL,3,_TELP12_WAFID_out,"Returns wafer ID on the chuck" },
};

_LIBDEF	__TELP12_FACOM[] = {
	{ sizeof(_TELP12_FACOM)/sizeof(_ALGDEF), _TELP12_FACOM }
};

static char *___TELP12_FACOM[] = {
"@(#)USRFLGS=",
"@(#)USRHDRS=-I/opt/hp4070/include -I/opt/sicl/include",
"@(#)",
"@(#)USRLINK=",
"@(#)USRLIBS=",
"@(#)TSTLINK=-L/opt/hp4070/lib",
"@(#)TSTLIBS=",
"@(#)",
};
