SQL "create table alarms (\
 spname varchar(32)\
,ALID int\
,idTSN varchar(8)\
,setCEID int\
,clearCEID int\
,category int\
,isEnabled int\
,isSet int\
,ALTX varchar(40)\
,primary key(spname,ALID) )"

SQL "create table commands (\
 spname varchar(32)\
,command varchar(32)\
,isProcessing int\
,primary key(spname,command)\
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
,idTSN varchar(4)\
,isReported int\
,class varchar(32)\
,name varchar(32)\
,description varchar(2000)\
,primary key(spname,CEID)\
 )"

SQL "create table parameters (\
 spname varchar(32)\
,command varchar(32)\
,pname varchar(32)\
,varname varchar(32)\
,varmethod varchar(2000)\
,required int\
,description varchar(200)\
,primary key(spname,command,pname)\
 )"

SQL "create table reports (\
 spname varchar(32)\
,RPTID varchar(32)\
,VIDs varchar(1000)\
,primary key(spname,RPTID)\
 )"

SQL "create table spool_data (\
 spname varchar(32)\
,ts varchar(26)\
,sequence int\
,sfr varchar(10)\
,data varchar(100000),primary key(spname,ts)\
 )"

SQL "create table variables (\
 spname varchar(32)\
,varID varchar(32)\
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
,primary key(spname,varID)\
 )"
 
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
,primary key (objType,attributeName)\
 )"

SQL "create table object_attributes (\
 objType  varchar(32)\
,objID    varchar(32)\
,attributeName varchar(32)\
,attributeValue varchar(10000)\
,primary key (objType, objID, attributeName)\
 )"

SQL "create table objects (\
 objType varchar(32)\
,objID varchar(32)\
,primary key (objType, objID)\
 )"


SQL "create table object_types (\
 objType varchar(32)\
,primary key (objType)\
 )"




