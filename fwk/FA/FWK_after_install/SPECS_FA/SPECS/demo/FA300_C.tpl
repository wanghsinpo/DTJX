#Test Plan	FA300_C	1	04/02/2009	00:00:00	root	SPECS-FA demonstration test plan ( multi points )
#Library	measure/DEMO	1	04/02/2009	00:00:00	root	MEAS:Dummy Algorithms
#Library	tester/A4070	1	04/02/2009	00:00:00	root	TSTR:Keysight 4070/4080 Tester Algorithms
#Library	prober/NOPROBER_HPSTD	1	04/02/2009	00:00:00	root	PRBR:Dummy Prober Algorithms (Enhanced)
#Library	utility/UTILITY	1	04/02/2009	00:00:00	root	UTIL:Utility Algorithms
#Wafer	FA300_C	1	04/02/2009	00:00:00	root	Wafer Spec of SPECS-FA demonstration
#Die	FA300_A	1	04/02/2009	00:00:00	root	Description for this Die spec.
#Probe	FA300_A	1	04/02/2009	00:00:00	root	Description for this Probe spec.
#Test	FA300_A	1	04/02/2009	00:00:00	root	Test spec for SPECS-FA demonstration
#Job	SYSTEM	1	04/02/2009	00:00:00	root	Description for this Job spec.

$Type: Wafer
$Name: FA300_C
$Vers: 1
$Desc: Wafer Spec of SPECS-FA demonstration
$Date: 04/02/2009
$Time: 00:00:00
$User: root
$--------- ------------------- ------------ - - -
 ATTRIBUTE                                       
           SIZE=REAL,"mm"      300.000000        
           STEPX=REAL,"um"     19788.000000      
           STEPY=REAL,"um"     19790.000000      
           FLAT=INTEGER,"deg"  180               
           ALIGNDIEX=INTEGER   -2                
           ALIGNDIEY=INTEGER   3                 
           ALIGNMODX=REAL,"um" 17775.000000      
           ALIGNMODY=REAL,"um" 19150.000000      
           CENTERDIEX=INTEGER  0                 
           CENTERDIEY=INTEGER  0                 
           OFFSETDIEX=REAL     9894.000000       
           OFFSETDIEY=REAL     9895.000000       
           COORDINATE=INTEGER  1                 
           WAFERSHAPE=INTEGER  0                 
 BODY                                            
           `FA300_A`           -3,2              
           `FA300_A`           -2,2              
           `FA300_A`           -1,2              
           `FA300_A`           0,2               
           `FA300_A`           1,2               
           `FA300_A`           2,2               
           `FA300_A`           2,1               
           `FA300_A`           1,1               
           `FA300_A`           0,1               
           `FA300_A`           -1,1              
           `FA300_A`           -2,1              
           `FA300_A`           -3,1              
           `FA300_A`           -3,0              
           `FA300_A`           -2,0              
           `FA300_A`           -1,0              
           `FA300_A`           0,0               
           `FA300_A`           1,0               
           `FA300_A`           2,0               
           `FA300_A`           2,-1              
           `FA300_A`           1,-1              
           `FA300_A`           0,-1              
           `FA300_A`           -1,-1             
           `FA300_A`           -2,-1             
           `FA300_A`           -3,-1             
           `FA300_A`           -3,-2             
           `FA300_A`           -2,-2             
           `FA300_A`           -1,-2             
           `FA300_A`           0,-2              
           `FA300_A`           1,-2              
           `FA300_A`           2,-2              
           `FA300_A`           2,-3              
           `FA300_A`           1,-3              
           `FA300_A`           0,-3              
           `FA300_A`           -1,-3             
           `FA300_A`           -2,-3             
           `FA300_A`           -3,-3             
$--------- ------------------- ------------ - - -

$Type: Die
$Name: FA300_A
$Vers: 1
$Desc: Description for this Die spec.
$Date: 04/02/2009
$Time: 00:00:00
$User: root
$---- ---- ------- - - -------
 BODY                         
      `RX` 0,19150     TR07MOD
$---- ---- ------- - - -------

$Type: Probe
$Name: FA300_A
$Vers: 1
$Desc: Description for this Probe spec.
$Date: 04/02/2009
$Time: 00:00:00
$User: prober
$---- --- ----- - - -
 BODY                
      PAD 1,26       
      PAD 2,24       
      PAD 3,28       
      PAD 4,22       
      PAD 5,30       
      PAD 6,20       
      PAD 7,32       
      PAD 8,18       
      PAD 9,34       
      PAD 10,16      
      PAD 11,36      
      PAD 12,14      
      PAD 13,38      
      PAD 14,12      
      PAD 15,40      
      PAD 16,10      
      PAD 17,42      
      PAD 18,8       
      PAD 19,44      
      PAD 20,6       
      PAD 21,46      
      PAD 22,4       
      PAD 23,48      
      PAD 24,2       
$---- --- ----- - - -

$Type: Test
$Name: FA300_A
$Vers: 1
$Desc: Test spec for SPECS-FA demonstration
$Date: 04/02/2009
$Time: 00:00:00
$User: root
$--------- - -------------------------------- --------------- ------- ------------------------
 BODY                                                                                         
 RX::R1:   R Iforce=0.1,Vlimit=0.2,Delay=0    `P[1]`=0.8~1.2  H=1,L=2 Force 0.1mA to 1 ohm    
 RX::R10:  R Iforce=0.01,Vlimit=0.2,Delay=0   `P[2]`=8~12     H=3,L=4 Force 0.01mA to 10 ohm  
 RX::R100: R Iforce=0.001,Vlimit=0.2,Delay=0  `P[3]`=80~120   H=5,L=6 Force 0.001mA to 100 ohm
 RX::R1K:  R Iforce=0.0001,Vlimit=0.2,Delay=0 `P[4]`=800~1200 H=7,L=8 Force 0.0001mA to 1K ohm
$--------- - -------------------------------- --------------- ------- ------------------------

$Type: Job
$Name: SYSTEM
$Vers: 1
$Desc: Description for this Job spec.
$Date: 04/02/2009
$Time: 00:00:00
$User: root
$-------- ------------ ------------------------------------------------------------ ------- - ---------------------------------------------------------------------
 BODY                                                                                                                                                              
#         Warning:     Don't change any statements between BEGIN_NAVI and END_NAVI.                                                                                
#                                                                                                                                                                  
#         BEGIN_NAVI                                                                                                                                               
#         SELECT_WAFER FA300_C                                                                                                                                     
#         SELECT_PROBE FA300_A                                                                                                                                     
#         SELECT_DIE   FA300_A                                                                                                                                     
#         SELECT_TEST  FA300_A                                                                                                                                     
#         DIE_TEST     FA300_A                                                      FA300_A                                                                        
#         END_NAVI                                                                                                                                                 
          SELECT       WAFER,"FA300_C"                                                                                                                             
          SELECT       PROBE,"FA300_A"                                                                                                                             
          TEST         "FA300_A","FA300_A"                                                                                                                         
          LOOP                                                                                                                                                     
$-------- ------------ ------------------------------------------------------------ ------- - ---------------------------------------------------------------------

