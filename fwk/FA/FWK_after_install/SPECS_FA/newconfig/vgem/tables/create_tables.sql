SQL "create table alarm_log (\
spname varchar(32)\
,clock varchar(16)\
,ALID varchar(20)\
,is_set int\
,ALTX varchar(256)\
,primary key(spname,clock,ALID)\
 )"

SQL "create table alarms (\
 spname varchar(32)\
,ALID int\
,eqname varchar(32)\
,eqALID varchar(20)\
,idTSN varchar(8)\
,setCEID int\
,clearCEID int\
,category int\
,isEnabled int\
,isSet int\
,ALTX varchar(256)\
,primary key(spname,ALID) )"

SQL "create table attribute_defaults (\
 objType varchar(32)\
,attributeName varchar(32)\
,defaultValue varchar(200)\
,attributeMethod varchar(100)\
,datatype varchar(8)\
,order int\
,description varchar(200)\
,dataLength int\
,hostAccess int\
,public int\
,primary key (objType,attributeName)\
 )"

SQL "create table event_reports (\
spname varchar(32)\
,CEID varchar(32)\
,RPTID varchar(32)\
,primary key(spname,CEID,RPTID)\
 )"

SQL "create table events (\
spname varchar(32)\
,CEID varchar(32)\
,eqname varchar(32)\
,eqCEID varchar(32)\
,idTSN varchar(4)\
,isReported int\
,name varchar(144)\
,description varchar(2000)\
,primary key(spname,CEID)\
 )"

SQL "create table LMP_configuration (\
paramname varchar(80)\
,paramvalue int\
 )"

SQL "create table LMP_port_variables (\
PortVarOrder int\
,PortVarLabel varchar(80)\
,PortVarSV varchar(32)\
,PortVarClear int\
,primary key(PortVarSV)\
 )"


SQL "create table object_attributes (\
 objType  varchar(32)\
,objID    varchar(128)\
,attributeName varchar(32)\
,attributeValue varchar(10000)\
,primary key (objType, objID, attributeName)\
 )"

SQL "create table objects (\
 objType varchar(32)\
,objID varchar(128)\
,primary key (objType, objID)\
 )"


SQL "create table object_types (\
 objType varchar(32)\
,primary key (objType)\
 )"

SQL "create table parameters (\
triggerType varchar(32)\
,command varchar(32)\
,order int\
,pname varchar(32)\
,required int\
,varProgram varchar(36)\
,proberPname varchar(32)\
,proberRequired int\
,primary key(triggerType,command,order)\
 )"

SQL "create table prober_command_verify (\
commandType varchar(32)\
,commandName varchar(32)\
,order int\
,VID varchar(32)\
,validVals varchar(64)\
,checkAll varchar(1)\
,primary key(commandType,commandName,order)\
 )"

SQL "create table reports (\
spname varchar(32)\
,RPTID varchar(32)\
,VIDs varchar(1000)\
,description varchar(32)\
,eqRPTID varchar(32)\
,primary key(spname,RPTID)\
 )"

SQL "create table slotmap (\
status varchar(1)\
,color varchar(20)\
,description varchar(32)\
,category varchar(10)\
,primary key(status)\
)"

SQL "create table spool_data (\
spname varchar(32)\
,ts varchar(26)\
,sequence int\
,sfr varchar(10)\
,data varchar(100000),primary key(spname,ts)\
 )"

SQL "create table state_enumerations (\
type varchar(32)\
,state varchar(32)\
,stateNumber int\
,parentState varchar(32)\
,stateDefinition varchar(2000)\
,primary key(type,state)\
 )"

SQL "create table streams_functions (\
 message varchar(6)\
,description varchar(32)\
,onlineProc	varchar(32)\
,offlineProc	varchar(32)\
,xactStatus     varchar(10)\
,timeoutProc	varchar(32)\
,returnProc	varchar(32)\
,returnData	varchar(64000)\
,primary key(message)\
 )"

SQL "create table transition_events (\
type varchar(32)\
,currentState varchar(32)\
,stateModel varchar(32)\
,message varchar(32)\
,order int\
,CEID varchar(32)\
,primary key(type,currentState,stateModel,message,order)\
 )"

SQL "create table transitions (\
type varchar(32)\
,message varchar(32)\
,stateModel varchar(32)\
,currentState varchar(32)\
,newState varchar(32)\
,preFunction varchar(32)\
,postState varchar(32)\
,primary key(type,message,stateModel,currentState)\
 )"

SQL "create table trigger_states (\
triggerType  	varchar(32)\
,triggerValue	varchar(32)\
,stateModel	varchar(32)\
,order		int\
,preProc	varchar(128)\
,postProc	varchar(128)\
,errorPreProc	varchar(128)\
,errorPostProc	varchar(128)\
,validationFlag varchar(1)\
,primary key (triggerType, triggerValue,stateModel)\
 )"

SQL "create table triggers (\
triggerType  	varchar(64)\
,triggerValue	varchar(64)\
,buttonOrder		int\
,verifyProc	varchar(128)\
,preProc	varchar(128)\
,postUpdate	varchar(128)\
,postProc	varchar(128)\
,errorPreProc	varchar(128)\
,errorPostUpdate varchar(128)\
,errorPostProc	varchar(128)\
,validationFlag varchar(1)\
,testerCommand  varchar(64)\
,proberCommand  varchar(64)\
,changeFlag     varchar(1)\
,pcLength       int\
,primary key (triggerType, triggerValue)\
 )"

SQL "create table variables (\
spname varchar(32)\
,varID varchar(32)\
,eqname varchar(32)\
,eqvarID varchar(32)\
,idTSN varchar(8)\
,varname varchar(32)\
,description varchar(200)\
,varclass varchar(10)\
,valueTSN varchar(8)\
,varmethod varchar(2000)\
,varvalue varchar(20000)\
,tLatest varchar(16)\
,units varchar(10)\
,ECMIN varchar(32)\
,ECMAX varchar(32)\
,ECDEF varchar(32)\
,eqVarname varchar(32)\
,primary key(spname,varID)\
 )"

SQL "create table prober_eventforward_data (\
spname varchar(32)\
,CEID varchar(32)\
,Label varchar(32)\
,VIDs varchar(1000)\
,primary key(spname,CEID,Label)\
 )"

SQL "create table handle_prober_alarms (\
 spname varchar(32)\
,ALID int\
,category int\
,primary key(spname,ALID) )"

