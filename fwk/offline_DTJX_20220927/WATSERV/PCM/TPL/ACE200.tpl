#Test Plan	ACE200	1	04/01/1999	09:00:00	specs	Sample Test Plan (medium)
#Library	measure/DEMO	1	01/01/1998	09:00:00	specs	MEAS:Dummy Algorithms
#Library	tester/NOTESTER	1	01/01/1998	09:00:00	specs	TSTR:Dummy Tester Algorithms
#Library	prober/NOPROBER_HPSTD	1	01/01/1998	09:00:00	specs	PRBR:Dummy Prober Algorithms (Enhancement)
#Library	utility/UTILITY	1	01/01/1998	09:00:00	specs	UTIL:Utility Algorithms
#Wafer	CTX804	1	01/01/1998	09:00:00	specs	Wafer spec for ACE200
#Die	VTX640	1	01/01/1998	09:00:00	specs	Die spec for ACE200
#Die	VOX712	1	01/01/1998	09:00:00	specs	Die spec for ACE200
#Die	V9X640	1	01/01/1998	09:00:00	specs	Die spec for ACE200
#Die	V1X640	1	01/01/1998	09:00:00	specs	Die spec for ACE200
#Probe	2X12X2	1	01/01/1998	09:00:00	specs	Probe spec for ACE200
#Test	BAX044	1	01/01/1998	09:00:00	specs	Test spec for ACE200
#Test	BAX081	1	01/01/1998	09:00:00	specs	Test spec for ACE200
#Test	BAX030	1	01/01/1998	09:00:00	specs	Test spec for ACE200
#Test	REX024	1	01/01/1998	09:00:00	specs	Test spec for ACE200
#Test	256MON	1	01/01/1998	09:00:00	specs	Test spec for ACE200
#Test	256MOF	1	01/01/1998	09:00:00	specs	Test spec for ACE200
#Job	SYSTEM	1	01/01/1998	09:00:00	specs	Job spec for ACE200

$Type: Wafer
$Name: CTX804
$Vers: 1
$Desc: Wafer spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$--------- -------------------- ------- -- - -----------------------------------------------------
 ATTRIBUTE                                                                                        
           SIZE=REAL,"mm"       200          Wafer diameter                                       
           STEPX=REAL,"um"      23080        Die step index size                                  
           STEPY=REAL,"um"      19500        Die step index size                                  
           FLAT=INTEGER,"deg"   180          Flat orientation                                     
           ALIGNDIEX=INTEGER    4            Alignment die index position relative to wafer origin
           ALIGNDIEY=INTEGER    3            Alignment die index position relative to wafer origin
           ALIGNMODX=REAL,"um"  11835.0      Alignment module position relative to die origin     
           ALIGNMODY=REAL,"um"  -150.0       Alignment module position relative to die origin     
           OFFSETDIEX=REAL,"um" 11540                                                             
           OFFSETDIEY=REAL,"um" 9750                                                              
           CENTERDIEX=INTEGER   5                                                                 
           CENTERDIEY=INTEGER   6                                                                 
           COORDINATE=INTEGER   1
 BODY                                                                                             
           VTX640               3~6,1                                                             
           VTX640               7~2,2                                                             
           VTX640               1~8,3                                                             
           VTX640               8~1,4                                                             
           VTX640               1~8,5                                                             
           VTX640               8~1,6                                                             
           VTX640               1~8,7                                                             
           VTX640               8~1,8                                                             
           VTX640               2~7,9                                                             
           VTX640               6~3,10
                                                                                                  
           V9X640               2,3     BL                                                        
           V9X640               4,3     BC                                                        
           V9X640               6,3     BR                                                        
           V9X640               6,6     CR                                                        
           V9X640               4,6     CC                                                        
           V9X640               2,6     CL                                                        
           V9X640               2,9     TL                                                        
           V9X640               4,9     TC                                                        
           V9X640               6,9     TR                                                        
                                                                                                  
           V1X640               5,6     C                                                         
                                                                                                  
           VOX712               1,3
           VOX712               2,2
           VOX712               3,1
           VOX712               6,1
           VOX712               7,2
           VOX712               8,3
           VOX712               8,8
           VOX712               7,9
           VOX712               6,10
           VOX712               3,10
           VOX712               2,9
           VOX712               1,8
$--------- -------------------- ------- -- - -----------------------------------------------------

$Type: Die
$Name: VTX640
$Vers: 1
$Desc: Die spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$---- ----------- ----------- - - -
 BODY                              
      `INV`       3750,1450        
      `NWEL`      3750,2900        
      `PWEL`      3750,4350        
      `CON100`    3750,5800        
      `CON500`    3750,7250        
      `ISOA`      7500,14500       
      `ISOB`      7500,15950       
      `ISOC`      7500,17400       
      `ISOD`      7500,18850       
      `2MTL`      15000,1450       
      `NCHMOS`    15000,2900       
      `PCHMOS`    15000,4350       
      `1MTL`      15000,5800       
      `VD`        15000,7250       
      `VO`        15000,8700       
      `VS`        15000,10150      
      `NWELCON`   15000,11600      
      `PWELCON`   15000,13050      
      `LEFF`      18750,1450       
      `WEFF`      18750,2900       
      `SILC`      18750,4350       
      `INA`       18750,5800       
      `IN1A`      18750,7250       
      `IN2A`      18750,8700       
      `INB`       18750,10150      
      `IN1B`      18750,11600      
      `IN2B`      18750,11600      
      `FIN1`      22500,1450       
      `FIN2`      22500,2900       
      `CS14`      22500,4350       
      `CS15`      22500,5800       
      `CS16`      22500,7250       
      `CS17`      22500,8700       
      `NPOLYMT1A` 22500,10150      
      `PPOLYMT1A` 22500,11600      
      `NPOLYMT1B` 22500,13050      
      `PPOLYMT1B` 22500,14500      
      `C01`       7500,1450        
      `C02`       7500,2900        
      `C03`       7500,4350        
      `C04`       7500,5800        
      `CAPH`      7500,7250        
      `CAPL`      7500,8700        
      `ECELL`     7500,10150       
      `RCELL`     7500,13050       
      `WCELL`     7500,15950       
$---- ----------- ----------- - - -

$Type: Die
$Name: VOX712
$Vers: 1
$Desc: Die spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$---- ----------- ----------- - - -
 BODY                              
      `INV`       3750,1450        
      `NWEL`      3750,2900        
      `PWEL`      3750,4350        
      `CON100`    3750,5800        
      `CON500`    3750,7250        
      `ISOA`      7500,14500       
      `ISOB`      7500,15950       
      `ISOC`      7500,17400       
      `ISOD`      7500,18850       
      `2MTL`      15000,1450       
      `NCHMOS`    15000,2900       
      `PCHMOS`    15000,4350       
      `1MTL`      15000,5800       
      `VD`        15000,7250       
      `VO`        15000,8700       
      `VS`        15000,10150      
      `NWELCON`   15000,11600      
      `PWELCON`   15000,13050      
      `LEFF`      18750,1450       
      `WEFF`      18750,2900       
      `SILC`      18750,4350       
      `INA`       18750,5800       
      `IN1A`      18750,7250       
      `IN2A`      18750,8700       
      `INB`       18750,10150      
      `IN1B`      18750,11600      
      `IN2B`      18750,11600      
      `FIN1`      22500,1450       
      `FIN2`      22500,2900       
      `CS14`      22500,4350       
      `CS15`      22500,5800       
      `CS16`      22500,7250       
      `CS17`      22500,8700       
      `NPOLYMT1A` 22500,10150      
      `PPOLYMT1A` 22500,11600      
      `NPOLYMT1B` 22500,13050      
      `PPOLYMT1B` 22500,14500      
      `C01`       7500,1450        
      `C02`       7500,2900        
      `C03`       7500,4350        
      `C04`       7500,5800        
      `CAPH`      7500,7250        
      `CAPL`      7500,8700        
$---- ----------- ----------- - - -

$Type: Die
$Name: V9X640
$Vers: 1
$Desc: Die spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$---- ----------- ----------- - - -
 BODY                              
      `INV`       3750,1450        
      `NWEL`      3750,2900        
      `PWEL`      3750,4350        
      `CON100`    3750,5800        
      `CON500`    3750,7250        
      `ISOA`      7500,14500       
      `ISOB`      7500,15950       
      `ISOC`      7500,17400       
      `ISOD`      7500,18850       
      `2MTL`      15000,1450       
      `NCHMOS`    15000,2900       
      `PCHMOS`    15000,4350       
      `1MTL`      15000,5800       
      `VD`        15000,7250       
      `VO`        15000,8700       
      `VS`        15000,10150      
      `NWELCON`   15000,11600      
      `PWELCON`   15000,13050      
      `LEFF`      18750,1450       
      `WEFF`      18750,2900       
      `SILC`      18750,4350       
      `INA`       18750,5800       
      `IN1A`      18750,7250       
      `IN2A`      18750,8700       
      `INB`       18750,10150      
      `IN1B`      18750,11600      
      `IN2B`      18750,11600      
      `FIN1`      22500,1450       
      `FIN2`      22500,2900       
      `CS14`      22500,4350       
      `CS15`      22500,5800       
      `CS16`      22500,7250       
      `CS17`      22500,8700       
      `NPOLYMT1A` 22500,10150      
      `PPOLYMT1A` 22500,11600      
      `NPOLYMT1B` 22500,13050      
      `PPOLYMT1B` 22500,14500      
      `C01`       7500,1450        
      `C02`       7500,2900        
      `C03`       7500,4350        
      `C04`       7500,5800        
      `CAPH`      7500,7250        
      `CAPL`      7500,8700        
$---- ----------- ----------- - - -

$Type: Die
$Name: V1X640
$Vers: 1
$Desc: Die spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$---- ----------- ----------- - - -
 BODY                              
      `INV`       3750,1450        
      `NWEL`      3750,2900        
      `PWEL`      3750,4350        
      `CON100`    3750,5800        
      `CON500`    3750,7250        
      `ISOA`      7500,14500       
      `ISOB`      7500,15950       
      `ISOC`      7500,17400       
      `ISOD`      7500,18850       
      `2MTL`      15000,1450       
      `NCHMOS`    15000,2900       
      `PCHMOS`    15000,4350       
      `1MTL`      15000,5800       
      `VD`        15000,7250       
      `VO`        15000,8700       
      `VS`        15000,10150      
      `NWELCON`   15000,11600      
      `PWELCON`   15000,13050      
      `LEFF`      18750,1450       
      `WEFF`      18750,2900       
      `SILC`      18750,4350       
      `INA`       18750,5800       
      `IN1A`      18750,7250       
      `IN2A`      18750,8700       
      `INB`       18750,10150      
      `IN1B`      18750,11600      
      `IN2B`      18750,11600      
      `FIN1`      22500,1450       
      `FIN2`      22500,2900       
      `CS14`      22500,4350       
      `CS15`      22500,5800       
      `CS16`      22500,7250       
      `CS17`      22500,8700       
      `NPOLYMT1A` 22500,10150      
      `PPOLYMT1A` 22500,11600      
      `NPOLYMT1B` 22500,13050      
      `PPOLYMT1B` 22500,14500      
      `C01`       7500,1450        
      `C02`       7500,2900        
      `C03`       7500,4350        
      `C04`       7500,5800        
      `CAPH`      7500,7250        
      `CAPL`      7500,8700        
$---- ----------- ----------- - - -

$Type: Probe
$Name: 2X12X2
$Vers: 1
$Desc: Probe spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$---- --- ----- - - -
 BODY                
      PAD 1,4        
      PAD 2,8        
      PAD 3,12       
      PAD 4,16       
      PAD 5,20       
      PAD 6,24       
      PAD 7,28       
      PAD 8,32       
      PAD 9,36       
      PAD 10,40      
      PAD 11,44      
      PAD 12,48      
      PAD -1,49      
$---- --- ----- - - -

$Type: Test
$Name: BAX044
$Vers: 1
$Desc: Test spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$------------------ ------- -------------------------------------------------------------------------- - -------------------------------------------- -
 BODY                                                                                                                                                  
 `INV`::`S0`:       WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=1,F2=2,S1=3,S2=4,Sub=12,Well=11,Chk=-1     
 `S-`:              WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=5,F2=6,S1=3,S2=4,Sub=12,Well=11,Chk=-1     
 `S+`:              WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=7,F2=8,S1=3,S2=4,Sub=12,Well=11,Chk=-1     

 `NWEL`::`R1`:      BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=1,T2=7,Sub=12,Well=11,Chk=-1               
 `R2`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=2,T2=7,Sub=12,Well=11,Chk=-1               
 `R3`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=3,T2=7,Sub=12,Well=11,Chk=-1               
 `R4`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=4,T2=7,Sub=12,Well=11,Chk=-1               
 `R5`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=5,T2=7,Sub=12,Well=11,Chk=-1               
 `R6`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=6,T2=7,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `PWEL`::`R1`:      BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=1,T2=8,Sub=12,Well=11,Chk=-1               
 `R2`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=2,T2=8,Sub=12,Well=11,Chk=-1               
 `R3`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=3,T2=8,Sub=12,Well=11,Chk=-1               
 `R4`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=4,T2=8,Sub=12,Well=11,Chk=-1               
 `R5`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=5,T2=8,Sub=12,Well=11,Chk=-1               
 `R6`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=6,T2=8,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `CON100`::`100`:   BRIDGE  Vbridge=0.5,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=1,T2=2,Sub=12,Well=11,Chk=-1               
 `100_REV`:         BRIDGE  Vbridge=0.5,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=3,T2=4,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `CON500`::`500`:   BRIDGE  Vbridge=0.1,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=1,T2=2,Sub=12,Well=11,Chk=-1               
 `500_REV`:         BRIDGE  Vbridge=0.1,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=3,T2=4,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `ISOA`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOB`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOC`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOD`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
                                                                                                                                                       
 `2MTL`::`0.01`:    LDX=LD  Slope=0.01,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=1,D=2,S=3,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/0.01,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=4,D=5,S=6,B=0,Sub=0,Chk=0                   
 `0.5`:             LDX=LD  Slope=0.50,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=7,D=8,S=9,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/0.5,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"        G=10,D=11,S=12,B=0,Sub=0,Chk=0                
 `1.0`:             LDX=LD  Slope=1.00,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=1,D=2,S=3,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/1.00,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=4,D=5,S=6,B=0,Sub=0,Chk=0                   
 `10.0`:            LDX=LD  Slope=10.0,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=7,D=8,S=9,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/10.0,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=10,D=11,S=12,B=0,Sub=0,Chk=0                
                                                                                                                                                       
 `NCHMOS`::`N1`:    FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=1,D=2,S=3,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=1,D=2,S=3,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=1,D=2,S=3,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=1,D=2,S=3,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=1,D=2,S=3,Sub=0                             
 `N2`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=4,D=5,S=6,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=4,D=5,S=6,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=4,D=5,S=6,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=4,D=5,S=6,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=4,D=5,S=6,Sub=0                             
 `N3`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=7,D=8,S=9,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=7,D=8,S=9,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=7,D=8,S=9,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=7,D=8,S=9,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=7,D=8,S=9,Sub=0                             
 `N4`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=10,D=11,S=12,Sub=0                          
                    LEAKCHK Vg=5                                                                         G=10,D=11,S=12,Sub=0                          
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=10,D=11,S=12,Sub=0                          
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=10,D=11,S=12,Sub=0                          
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=10,D=11,S=12,Sub=0                          
 `PCHMOS`::`P1`:    FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=1,D=2,S=3,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=1,D=2,S=3,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=1,D=2,S=3,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=1,D=2,S=3,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=1,D=2,S=3,Sub=0                             
 `P2`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=4,D=5,S=6,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=4,D=5,S=6,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=4,D=5,S=6,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=4,D=5,S=6,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=4,D=5,S=6,Sub=0                             
 `P3`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=7,D=8,S=9,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=7,D=8,S=9,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=7,D=8,S=9,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=7,D=8,S=9,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=7,D=8,S=9,Sub=0                             
 `P4`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=10,D=11,S=12,Sub=0                          
                    LEAKCHK Vg=5                                                                         G=10,D=11,S=12,Sub=0                          
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=10,D=11,S=12,Sub=0                          
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=10,D=11,S=12,Sub=0                          
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=10,D=11,S=12,Sub=0                          
                                                                                                                                                       
 `1MTL`::`Z+`:      EM      If=0.001,Vlimit=1,Delay=0,L=0,W=0,Ty="N"                                     T1=5,T2=9,Sub=0,Well=0,Chk=0                  
 `Z-`:              EM      If=0.001,Vlimit=1,Delay=0,L=0,W=0,Ty="N"                                     T1=7,T2=11,Sub=0,Well=0,Chk=0                 
                                                                                                                                                       
 `VD`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
 `VO`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
 `VS`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
                                                                                                                                                       
 `NWELCON`::        FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=3,D=4,S=5,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=3,D=4,S=5,Sub=0                             
 `PWELCON`::        FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=3,D=4,S=5,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=3,D=4,S=5,Sub=0                             
                                                                                                                                                       
 `LEFF`::`1`:       VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=2,Sub=0                             
 `2`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=3,Sub=0                             
 `3`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=4,Sub=0                             
 `4`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=5,Sub=0                             
                    DELL    Vd=3,Vg=1,Numdev=2,L1=0,L2=0,L3=0,L4=0,L5=0,L6=0                             G=9,D=1,S1=2,S2=3,S3=4,S4=5,S5=0,S6=0,Sub=0   
 `WEFF`::`1`:       VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=2,Sub=0                             
 `2`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=3,Sub=0                             
 `3`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=4,Sub=0                             
 `4`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=5,Sub=0                             
                    DELW    Vd=3,Vg=1,Numdev=2,W1=0,W2=0,W3=0,W4=0,W5=0,W6=0                             G=9,D=1,S1=2,S2=3,S3=4,S4=5,S5=0,S6=0,Sub=0   
                                                                                                                                                       
 `SILC`::           R       Iforce=1E-06,Vlimit=10,Delay=0                                               H=1,L=12                                      
 `FIN1`::           CSTR    Vf=1,Ilimit=0.001,N=0,Ar=0,Ty="I"                                            T1=1,T2=12,Sub=0,Well=0,Chk=0                 
 `FIN2`::           CSTR    Vf=1,Ilimit=0.001,N=0,Ar=0,Ty="I"                                            T1=1,T2=12,Sub=0,Well=0,Chk=0                 
                                                                                                                                                       
 `CS14`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS15`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS16`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS17`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
                                                                                                                                                       
 `NPOLYMT1A`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="N"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `PPOLYMT1A`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="P"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `NPOLYMT1B`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="N"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `PPOLYMT1B`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="P"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
                                                                                                                                                       
 `C01`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C02`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C03`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C04`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `CAPH`::`H+1`:     CAP     Bias=5.5                                                                     H=1,L=2                                       
 `H-1`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `HL`:              CAP     Bias=5.5                                                                     H=5,L=6                                       
 `CAPL`::`H+1`:     CAP     Bias=5.5                                                                     H=1,L=2                                       
 `H-1`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `HL`:              CAP     Bias=5.5                                                                     H=5,L=6                                       
$------------------ ------- -------------------------------------------------------------------------- - -------------------------------------------- -

$Type: Test
$Name: BAX081
$Vers: 1
$Desc: Test spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$------------------ ------- -------------------------------------------------------------------------- - -------------------------------------------- -
 BODY                                                                                                                                                  
 `INV`::`S0`:       WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=1,F2=2,S1=3,S2=4,Sub=12,Well=11,Chk=-1     
 `S-`:              WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=5,F2=6,S1=3,S2=4,Sub=12,Well=11,Chk=-1     
 `S+`:              WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=7,F2=8,S1=3,S2=4,Sub=12,Well=11,Chk=-1     

 `NWEL`::`R1`:      BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=1,T2=7,Sub=12,Well=11,Chk=-1               
 `R2`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=2,T2=7,Sub=12,Well=11,Chk=-1               
 `R3`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=3,T2=7,Sub=12,Well=11,Chk=-1               
 `R4`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=4,T2=7,Sub=12,Well=11,Chk=-1               
 `R5`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=5,T2=7,Sub=12,Well=11,Chk=-1               
 `R6`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=6,T2=7,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `PWEL`::`R1`:      BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=1,T2=8,Sub=12,Well=11,Chk=-1               
 `R2`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=2,T2=8,Sub=12,Well=11,Chk=-1               
 `R3`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=3,T2=8,Sub=12,Well=11,Chk=-1               
 `R4`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=4,T2=8,Sub=12,Well=11,Chk=-1               
 `R5`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=5,T2=8,Sub=12,Well=11,Chk=-1               
 `R6`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=6,T2=8,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `CON100`::`100`:   BRIDGE  Vbridge=0.5,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=1,T2=2,Sub=12,Well=11,Chk=-1               
 `100_REV`:         BRIDGE  Vbridge=0.5,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=3,T2=4,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `CON500`::`500`:   BRIDGE  Vbridge=0.1,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=1,T2=2,Sub=12,Well=11,Chk=-1               
 `500_REV`:         BRIDGE  Vbridge=0.1,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=3,T2=4,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `ISOA`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOB`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOC`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOD`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
                                                                                                                                                       
 `2MTL`::`0.01`:    LDX=LD  Slope=0.01,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=1,D=2,S=3,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/0.01,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=4,D=5,S=6,B=0,Sub=0,Chk=0                   
 `0.5`:             LDX=LD  Slope=0.50,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=7,D=8,S=9,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/0.5,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"        G=10,D=11,S=12,B=0,Sub=0,Chk=0                
 `1.0`:             LDX=LD  Slope=1.00,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=1,D=2,S=3,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/1.00,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=4,D=5,S=6,B=0,Sub=0,Chk=0                   
 `10.0`:            LDX=LD  Slope=10.0,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=7,D=8,S=9,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/10.0,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=10,D=11,S=12,B=0,Sub=0,Chk=0                
                                                                                                                                                       
 `NCHMOS`::`N1`:    FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=1,D=2,S=3,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=1,D=2,S=3,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=1,D=2,S=3,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=1,D=2,S=3,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=1,D=2,S=3,Sub=0                             
 `N2`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=4,D=5,S=6,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=4,D=5,S=6,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=4,D=5,S=6,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=4,D=5,S=6,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=4,D=5,S=6,Sub=0                             
 `N3`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=7,D=8,S=9,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=7,D=8,S=9,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=7,D=8,S=9,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=7,D=8,S=9,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=7,D=8,S=9,Sub=0                             
 `N4`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=10,D=11,S=12,Sub=0                          
                    LEAKCHK Vg=5                                                                         G=10,D=11,S=12,Sub=0                          
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=10,D=11,S=12,Sub=0                          
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=10,D=11,S=12,Sub=0                          
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=10,D=11,S=12,Sub=0                          
 `PCHMOS`::`P1`:    FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=1,D=2,S=3,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=1,D=2,S=3,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=1,D=2,S=3,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=1,D=2,S=3,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=1,D=2,S=3,Sub=0                             
 `P2`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=4,D=5,S=6,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=4,D=5,S=6,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=4,D=5,S=6,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=4,D=5,S=6,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=4,D=5,S=6,Sub=0                             
 `P3`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=7,D=8,S=9,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=7,D=8,S=9,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=7,D=8,S=9,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=7,D=8,S=9,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=7,D=8,S=9,Sub=0                             
 `P4`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=10,D=11,S=12,Sub=0                          
                    LEAKCHK Vg=5                                                                         G=10,D=11,S=12,Sub=0                          
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=10,D=11,S=12,Sub=0                          
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=10,D=11,S=12,Sub=0                          
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=10,D=11,S=12,Sub=0                          
                                                                                                                                                       
 `1MTL`::`Z+`:      EM      If=0.001,Vlimit=1,Delay=0,L=0,W=0,Ty="N"                                     T1=5,T2=9,Sub=0,Well=0,Chk=0                  
 `Z-`:              EM      If=0.001,Vlimit=1,Delay=0,L=0,W=0,Ty="N"                                     T1=7,T2=11,Sub=0,Well=0,Chk=0                 
                                                                                                                                                       
 `VD`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
 `VO`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
 `VS`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
                                                                                                                                                       
 `NWELCON`::        FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=3,D=4,S=5,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=3,D=4,S=5,Sub=0                             
 `PWELCON`::        FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=3,D=4,S=5,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=3,D=4,S=5,Sub=0                             
                                                                                                                                                       
 `LEFF`::`1`:       VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=2,Sub=0                             
 `2`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=3,Sub=0                             
 `3`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=4,Sub=0                             
 `4`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=5,Sub=0                             
                    DELL    Vd=3,Vg=1,Numdev=2,L1=0,L2=0,L3=0,L4=0,L5=0,L6=0                             G=9,D=1,S1=2,S2=3,S3=4,S4=5,S5=0,S6=0,Sub=0   
 `WEFF`::`1`:       VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=2,Sub=0                             
 `2`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=3,Sub=0                             
 `3`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=4,Sub=0                             
 `4`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=5,Sub=0                             
                    DELW    Vd=3,Vg=1,Numdev=2,W1=0,W2=0,W3=0,W4=0,W5=0,W6=0                             G=9,D=1,S1=2,S2=3,S3=4,S4=5,S5=0,S6=0,Sub=0   
                                                                                                                                                       
 `SILC`::           R       Iforce=1E-06,Vlimit=10,Delay=0                                               H=1,L=12                                      
 `FIN1`::           CSTR    Vf=1,Ilimit=0.001,N=0,Ar=0,Ty="I"                                            T1=1,T2=12,Sub=0,Well=0,Chk=0                 
 `FIN2`::           CSTR    Vf=1,Ilimit=0.001,N=0,Ar=0,Ty="I"                                            T1=1,T2=12,Sub=0,Well=0,Chk=0                 
                                                                                                                                                       
 `CS14`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS15`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS16`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS17`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
                                                                                                                                                       
 `NPOLYMT1A`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="N"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `PPOLYMT1A`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="P"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `NPOLYMT1B`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="N"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `PPOLYMT1B`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="P"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
                                                                                                                                                       
 `C01`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C02`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C03`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C04`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `CAPH`::`H+1`:     CAP     Bias=5.5                                                                     H=1,L=2                                       
 `H-1`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `HL`:              CAP     Bias=5.5                                                                     H=5,L=6                                       
 `CAPL`::`H+1`:     CAP     Bias=5.5                                                                     H=1,L=2                                       
 `H-1`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `HL`:              CAP     Bias=5.5                                                                     H=5,L=6                                       
$------------------ ------- -------------------------------------------------------------------------- - -------------------------------------------- -

$Type: Test
$Name: BAX030
$Vers: 1
$Desc: Test spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$------------------ ------- -------------------------------------------------------------------------- - -------------------------------------------- -
 BODY                                                                                                                                                  
 `INV`::`S0`:       WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=1,F2=2,S1=3,S2=4,Sub=12,Well=11,Chk=-1     
 `S-`:              WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=5,F2=6,S1=3,S2=4,Sub=12,Well=11,Chk=-1     
 `S+`:              WIDTH   Rsheet=0.1,If=1uA,Vlimit=1,W=0,L=0,Ty="N"                                    F1=7,F2=8,S1=3,S2=4,Sub=12,Well=11,Chk=-1     

 `NWEL`::`R1`:      BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=1,T2=7,Sub=12,Well=11,Chk=-1               
 `R2`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=2,T2=7,Sub=12,Well=11,Chk=-1               
 `R3`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=3,T2=7,Sub=12,Well=11,Chk=-1               
 `R4`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=4,T2=7,Sub=12,Well=11,Chk=-1               
 `R5`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=5,T2=7,Sub=12,Well=11,Chk=-1               
 `R6`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="N"                                           T1=6,T2=7,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `PWEL`::`R1`:      BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=1,T2=8,Sub=12,Well=11,Chk=-1               
 `R2`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=2,T2=8,Sub=12,Well=11,Chk=-1               
 `R3`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=3,T2=8,Sub=12,Well=11,Chk=-1               
 `R4`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=4,T2=8,Sub=12,Well=11,Chk=-1               
 `R5`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=5,T2=8,Sub=12,Well=11,Chk=-1               
 `R6`:              BRIDGE  Vbridge=1,Ilimit=1m,L=0,S=0,Ty="P"                                           T1=6,T2=8,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `CON100`::`100`:   BRIDGE  Vbridge=0.5,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=1,T2=2,Sub=12,Well=11,Chk=-1               
 `100_REV`:         BRIDGE  Vbridge=0.5,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=3,T2=4,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `CON500`::`500`:   BRIDGE  Vbridge=0.1,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=1,T2=2,Sub=12,Well=11,Chk=-1               
 `500_REV`:         BRIDGE  Vbridge=0.1,Ilimit=1m,L=0,S=0,Ty="I"                                         T1=3,T2=4,Sub=12,Well=11,Chk=-1               
                                                                                                                                                       
 `ISOA`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOB`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOC`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
 `ISOD`::`M0`:      CAPM    Bias=1.5,Vbias=-1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=1,T2=2,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1   
 `M1`:              CAPM    Bias=1.5,Vbias= 1.5,Vt3=0,Vt4=0,Ep=0,Ar=0,Ed=0,Ty="I"                        T1=9,T2=10,VF1=5,VF2=6,Sub=12,Well=11,Chk=-1  
                                                                                                                                                       
 `2MTL`::`0.01`:    LDX=LD  Slope=0.01,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=1,D=2,S=3,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/0.01,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=4,D=5,S=6,B=0,Sub=0,Chk=0                   
 `0.5`:             LDX=LD  Slope=0.50,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=7,D=8,S=9,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/0.5,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"        G=10,D=11,S=12,B=0,Sub=0,Chk=0                
 `1.0`:             LDX=LD  Slope=1.00,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=1,D=2,S=3,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/1.00,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=4,D=5,S=6,B=0,Sub=0,Chk=0                   
 `10.0`:            LDX=LD  Slope=10.0,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"         G=7,D=8,S=9,B=0,Sub=0,Chk=0                   
                    LDY=LD  Slope=1/10.0,Intercept=2,Variance=0,Corr=0,Oxd=0,Leff=0,W=0,L=0,Ty="N"       G=10,D=11,S=12,B=0,Sub=0,Chk=0                
                                                                                                                                                       
 `NCHMOS`::`N1`:    FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=1,D=2,S=3,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=1,D=2,S=3,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=1,D=2,S=3,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=1,D=2,S=3,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=1,D=2,S=3,Sub=0                             
 `N2`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=4,D=5,S=6,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=4,D=5,S=6,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=4,D=5,S=6,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=4,D=5,S=6,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=4,D=5,S=6,Sub=0                             
 `N3`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=7,D=8,S=9,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=7,D=8,S=9,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=7,D=8,S=9,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=7,D=8,S=9,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=7,D=8,S=9,Sub=0                             
 `N4`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=10,D=11,S=12,Sub=0                          
                    LEAKCHK Vg=5                                                                         G=10,D=11,S=12,Sub=0                          
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="N"        G=10,D=11,S=12,Sub=0                          
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="N"   G=10,D=11,S=12,Sub=0                          
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=10,D=11,S=12,Sub=0                          
 `PCHMOS`::`P1`:    FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=1,D=2,S=3,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=1,D=2,S=3,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=1,D=2,S=3,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=1,D=2,S=3,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=1,D=2,S=3,Sub=0                             
 `P2`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=4,D=5,S=6,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=4,D=5,S=6,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=4,D=5,S=6,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=4,D=5,S=6,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=4,D=5,S=6,Sub=0                             
 `P3`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=7,D=8,S=9,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=7,D=8,S=9,Sub=0                             
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=7,D=8,S=9,Sub=0                             
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=7,D=8,S=9,Sub=0                             
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=7,D=8,S=9,Sub=0                             
 `P4`:              FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=10,D=11,S=12,Sub=0                          
                    LEAKCHK Vg=5                                                                         G=10,D=11,S=12,Sub=0                          
                    VGS3    Vdsf=1,Idref=1E-06,Vgsmin=0,Vgsmax=1,Vbsf=0,Intrange=1,W=0,L=0,Ty="P"        G=10,D=11,S=12,Sub=0                          
                    VTF2    Ids=1E-06,Vds=0,Vgsmin=0,Vgsmax=0,Vgstep=0,Vbs=0,Intrange=1,W=0,L=0,Ty="P"   G=10,D=11,S=12,Sub=0                          
                    IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="P"        G=10,D=11,S=12,Sub=0                          
                                                                                                                                                       
 `1MTL`::`Z+`:      EM      If=0.001,Vlimit=1,Delay=0,L=0,W=0,Ty="N"                                     T1=5,T2=9,Sub=0,Well=0,Chk=0                  
 `Z-`:              EM      If=0.001,Vlimit=1,Delay=0,L=0,W=0,Ty="N"                                     T1=7,T2=11,Sub=0,Well=0,Chk=0                 
                                                                                                                                                       
 `VD`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
 `VO`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
 `VS`::             IVGS    Vdsf=0.1,Vtref=0,Vgsmax=10,Vss=0,Delay=0.05,Intrange=1,W=0,L=0,Ty="N"        G=3,D=4,S=5,B=0,Sub=0,Chk=-1                  
                                                                                                                                                       
 `NWELCON`::        FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=3,D=4,S=5,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=3,D=4,S=5,Sub=0                             
 `PWELCON`::        FETCHK  Vd=1,Vgoff=0,Vgon=1,MaxIdoff=1E-07,MinIdon=1E-05,Integ=1                     G=3,D=4,S=5,Sub=0                             
                    LEAKCHK Vg=5                                                                         G=3,D=4,S=5,Sub=0                             
                                                                                                                                                       
 `LEFF`::`1`:       VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=2,Sub=0                             
 `2`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=3,Sub=0                             
 `3`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=4,Sub=0                             
 `4`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=5,Sub=0                             
                    DELL    Vd=3,Vg=1,Numdev=2,L1=0,L2=0,L3=0,L4=0,L5=0,L6=0                             G=9,D=1,S1=2,S2=3,S3=4,S4=5,S5=0,S6=0,Sub=0   
 `WEFF`::`1`:       VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=2,Sub=0                             
 `2`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=3,Sub=0                             
 `3`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=4,Sub=0                             
 `4`:               VT      Id=1E-06,Vd=3,Vgmin=0,Vgmax=20,Vgstep=1,Integ=1                              G=9,D=1,S=5,Sub=0                             
                    DELW    Vd=3,Vg=1,Numdev=2,W1=0,W2=0,W3=0,W4=0,W5=0,W6=0                             G=9,D=1,S1=2,S2=3,S3=4,S4=5,S5=0,S6=0,Sub=0   
                                                                                                                                                       
 `SILC`::           R       Iforce=1E-06,Vlimit=10,Delay=0                                               H=1,L=12                                      
 `FIN1`::           CSTR    Vf=1,Ilimit=0.001,N=0,Ar=0,Ty="I"                                            T1=1,T2=12,Sub=0,Well=0,Chk=0                 
 `FIN2`::           CSTR    Vf=1,Ilimit=0.001,N=0,Ar=0,Ty="I"                                            T1=1,T2=12,Sub=0,Well=0,Chk=0                 
                                                                                                                                                       
 `CS14`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS15`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS16`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
 `CS17`::`0.5/0.3`: BRIDGE  Vbridge=1,Ilimit=1m,L=0.5,S=0.3,Ty="I"                                       T1=1,T2=2,Sub=0,Well=0,Chk=0                  
 `0.8/1.0`:         BRIDGE  Vbridge=1,Ilimit=1m,L=0.8,S=1.0,Ty="I"                                       T1=3,T2=4,Sub=0,Well=0,Chk=0                  
 `1.0/0.5`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.0,S=0.5,Ty="I"                                       T1=5,T2=6,Sub=0,Well=0,Chk=0                  
 `1.5/0.3`:         BRIDGE  Vbridge=1,Ilimit=1m,L=1.5,S=0.3,Ty="I"                                       T1=7,T2=8,Sub=0,Well=0,Chk=0                  
                                                                                                                                                       
 `NPOLYMT1A`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="N"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `PPOLYMT1A`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="P"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `NPOLYMT1B`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="N"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
 `PPOLYMT1B`::      BRIDGE  Vbridge=3,Ilimit=1E-3,L=0,S=0,Ty="P"                                         T1=1,T2=5,Sub=0,Well=0,Chk=0                  
                                                                                                                                                       
 `C01`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C02`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C03`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `C04`::`100`:      CAP     Bias=5.5                                                                     H=1,L=2                                       
 `110`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `150`:             CAP     Bias=5.5                                                                     H=5,L=6                                       
 `200`:             CAP     Bias=5.5                                                                     H=7,L=8                                       
 `CAPH`::`H+1`:     CAP     Bias=5.5                                                                     H=1,L=2                                       
 `H-1`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `HL`:              CAP     Bias=5.5                                                                     H=5,L=6                                       
 `CAPL`::`H+1`:     CAP     Bias=5.5                                                                     H=1,L=2                                       
 `H-1`:             CAP     Bias=5.5                                                                     H=3,L=4                                       
 `HL`:              CAP     Bias=5.5                                                                     H=5,L=6                                       
$------------------ ------- -------------------------------------------------------------------------- - -------------------------------------------- -

$Type: Test
$Name: REX024
$Vers: 1
$Desc: Test spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$-------------- ------- ------ - ----------------- -
 BODY                                               
 `INA`::`A`:    LEAKCHK Vg=1.4   G=1,D=4,S=2,Sub=0  
 `A+`:          LEAKCHK Vg=1.1   G=1,D=8,S=5,Sub=0  
 `IN1A`::`A/1`: LEAKCHK Vg=1.4   G=1,D=4,S=2,Sub=0  
 `A+/1`:        LEAKCHK Vg=1.1   G=1,D=8,S=5,Sub=0  
 `IN2A`::`A/2`: LEAKCHK Vg=1.4   G=1,D=4,S=2,Sub=0  
 `A+/2`:        LEAKCHK Vg=1.1   G=1,D=8,S=5,Sub=0  
 `INB`::`B`:    LEAKCHK Vg=1.4   G=1,D=4,S=2,Sub=0  
 `B+`:          LEAKCHK Vg=1.1   G=1,D=8,S=5,Sub=0  
 `IN1B`::`B/1`: LEAKCHK Vg=1.4   G=1,D=4,S=2,Sub=0  
 `B+/1`:        LEAKCHK Vg=1.1   G=1,D=8,S=5,Sub=0  
 `IN2B`::`B/2`: LEAKCHK Vg=1.4   G=1,D=4,S=2,Sub=0  
 `B+/2`:        LEAKCHK Vg=1.1   G=1,D=8,S=5,Sub=0  
$-------------- ------- ------ - ----------------- -

$Type: Test
$Name: 256MON
$Vers: 1
$Desc: Test spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$--------- - - - - -----------
 BODY                         
 `ECELL`::                    
#                  Placeholder
 `RCELL`::                    
#                  Placeholder
 `WCELL`::                    
#                  Placeholder
$--------- - - - - -----------

$Type: Test
$Name: 256MOF
$Vers: 1
$Desc: Test spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$--------- - - - - -----------
 BODY                         
 `ECELL`::                    
#                  Placeholder
 `RCELL`::                    
#                  Placeholder
 `WCELL`::                    
#                  Placeholder
$--------- - - - - -----------

$Type: Job
$Name: SYSTEM
$Vers: 1
$Desc: Job spec for ACE200
$Date: 01/01/1998
$Time: 09:00:00
$User: specs
$---- ------------ ------------------------------------------------------------ ------ - -
 BODY                                                                                     
#     Warning:     Don't change any statements between BEGIN_NAVI and END_NAVI.           
#                                                                                         
#     BEGIN_NAVI                                                                          
#     SELECT_WAFER CTX804                                                                 
#     SELECT_PROBE 2X12X2                                                                 
#     DIE_TEST     VTX640                                                       BAX044    
#     DIE_TEST     VTX640                                                       256MON
#     DIE_TEST     VTX640                                                       256MOF
#     DIE_TEST     VOX712                                                       BAX081
#     DIE_TEST     V9X640                                                       BAX030    
#     DIE_TEST     V1X640                                                       REX024    
#     END_NAVI                                                                            
      SELECT       WAFER,"CTX804"                                                         
      SELECT       PROBE,"2X12X2"                                                         
      TEST         "VTX640","BAX044"                                                      
      TEST         "VTX640","256MON"                                                      
      TEST         "VTX640","256MOF"                                                      
      TEST         "VOX712","BAX081"                                                      
      TEST         "V9X640","BAX030"                                                      
      TEST         "V1X640","REX024"                                                      
      LOOP                                                                                
$---- ------------ ------------------------------------------------------------ ------ - -

