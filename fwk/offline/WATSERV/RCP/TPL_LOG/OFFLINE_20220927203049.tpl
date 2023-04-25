#Test Plan	fileC80qqH	1	09/27/2022	20:30:39	wat	
#Library	measure/GTA_FAB5	1	02/07/2022	19:49:50	wat	GTA Fab5 WAT Algorithm Library. Created by AKT XXHN at 2019/11/4.
#Library	tester/A4070	1	09/01/2000	09:00:00	specs	TSTR:4070/4080 Tester Algorithms
#Library	prober/TELP8_HPSTD	1	09/01/2000	09:00:00	specs	PRBR:TELP8 Prober Algorithms (Enhancement)
#Library	utility/UTILITY	1	12/21/2018	12:32:37	wat	UTIL:Utility Algorithms
#Wafer	C0007	1 /WATSERV/RCP/WAF/C0007	10/22/2020	10:26:39	wat	Description for this Wafer spec.
#Die	C0007	1 /WATSERV/RCP/DIE/C0007	12/30/2020	16:25:29	wat	Description for this Die spec.
#Probe	IC26W	1 /WATSERV/RCP/PRB/IC26W	09/08/2020	11:13:15	wat	Description for this Probe spec.
#Test	C0007_ET_20220720	1 /WATSERV/RCP/TST/C0007_ET_20220720	07/20/2022	17:02:42	wat	Description for this Test spec.
#Job	SYSTEM	SPECS_built	09/27/2022	20:30:39	wat	Description for this Job spec.

$Type: Wafer
$Name: C0007
$Vers: 1 /WATSERV/RCP/WAF/C0007
$Desc: Description for this Wafer spec.
$Date: 10/22/2020
$Time: 10:26:39
$User: wat
$--------- ------------------- ------------- - - -----------------------------------------------------
 ATTRIBUTE                                                                                            
           SIZE=REAL,"mm"      200.000000        Wafer diameter                                       
           STEPX=REAL,"um"     25297.000000      Die step index size                                  
           STEPY=REAL,"um"     32089.000000      Die step index size                                  
           FLAT=INTEGER,"deg"  180               Flat orientation                                     
           ALIGNDIEX=INTEGER   0                 Alignment die index position relative to wafer origin
           ALIGNDIEY=INTEGER   0                 Alignment die index position relative to wafer origin
           ALIGNMODX=REAL,"um" 0.000000          Alignment module position relative to die origin     
           ALIGNMODY=REAL,"um" 0.000000          Alignment module position relative to die origin     
           CENTERDIEX=INTEGER  0                 Index of die nearest to center of wafer              
           CENTERDIEY=INTEGER  0                 Index of die nearest to center of wafer              
           OFFSETDIEX=REAL     -12000.000000     Offset of die center from die coordinate origin      
           OFFSETDIEY=REAL     10000.000000      Offset of die center from die coordinate origin      
           COORDINATE=INTEGER  1                 Die index coordinate                                 
           WAFERSHAPE=INTEGER  1                                                                      
 BODY                                                                                                 
           `C0007`             0,2                                                                    
           `C0007`             -2,0                                                                   
           `C0007`             0,-2                                                                   
           `C0007`             3,0                                                                    
           `C0007`             0,0                                                                    
$--------- ------------------- ------------- - - -----------------------------------------------------

$Type: Die
$Name: C0007
$Vers: 1 /WATSERV/RCP/DIE/C0007
$Desc: Description for this Die spec.
$Date: 12/30/2020
$Time: 16:25:29
$User: wat
$---- ------- ----------- - - -
 BODY                          
      `PLK01` 0,0              
      `PLK02` 3500,0           
      `PLK03` 7000,0           
      `PLK04` 10500,0          
      `PLK05` 14000,0          
      `PLK06` 17500,0          
      `PLK07` 0,-1146          
      `PLK08` 3500,-1146       
      `PLK09` 7000,-1146       
      `PLK10` 10500,-1146      
      `PLK11` 14000,-1146      
      `PLK12` 17500,-1146      
      `PLK13` 0,-2292          
      `PLK14` 3500,-2292       
      `PLK15` 7000,-2292       
      `PLK16` 10500,-2292      
      `PLK17` 14000,-2292      
      `PLK18` 17500,-2292      
      `PLK19` 0,-3438          
      `PLK20` 3500,-3438       
      `PLK21` 7000,-3438       
      `MO01`  17515,-4584      
      `MO02`  15,-5730         
      `MO03`  3515,-5730       
      `MO04`  7015,-5730       
      `MO05`  10515,-5730      
      `MO06`  14015,-5730      
      `MO07`  17515,-5730      
      `MO08`  15,-6876         
      `MO09`  3515,-6876       
      `HV01`  7015,-6876       
      `HV02`  10515,-6876      
      `HV03`  14015,-6876      
      `HV04`  17515,-6876      
      `HV05`  15,-8022         
      `DI01`  3515,-8022       
      `DI02`  7015,-8022       
      `RE01`  10515,-3438      
      `RE02`  14015,-3438      
      `RE03`  17515,-3438      
      `RE04`  15,-4584         
      `RE05`  3515,-4584       
      `RE06`  7015,-4584       
      `RE07`  10515,-4584      
      `RE08`  14015,-4584      
$---- ------- ----------- - - -

$Type: Probe
$Name: IC26W
$Vers: 1 /WATSERV/RCP/PRB/IC26W
$Desc: Description for this Probe spec.
$Date: 09/08/2020
$Time: 11:13:15
$User: wat
$---- --- ----- - - -
 BODY                
      PAD 1,30       
      PAD 2,31       
      PAD 3,32       
      PAD 4,33       
      PAD 5,34       
      PAD 6,35       
      PAD 7,36       
      PAD 8,37       
      PAD 9,38       
      PAD 10,39      
      PAD 11,40      
      PAD 12,41      
      PAD 13,42      
      PAD 14,7       
      PAD 15,8       
      PAD 16,9       
      PAD 17,10      
      PAD 18,11      
      PAD 19,12      
      PAD 20,13      
      PAD 21,14      
      PAD 22,15      
      PAD 23,16      
      PAD 24,17      
      PAD 25,18      
      PAD 26,19      
$---- --- ----- - - -

$Type: Test
$Name: C0007_ET_20220720
$Vers: 1 /WATSERV/RCP/TST/C0007_ET_20220720
$Desc: Description for this Test spec.
$Date: 07/20/2022
$Time: 17:02:42
$User: wat
$---- - - - - -
 BODY          
$---- - - - - -

$Type: Job
$Name: SYSTEM
$Vers: SPECS_built
$Desc: Description for this Job spec.
$Date: 09/27/2022
$Time: 20:30:39
$User: wat
$---- ------------ ------------------------------------------------------------ ----------------- - -
 BODY                                                                                                
#     Warning:     Don't change any statements between BEGIN_NAVI and END_NAVI.                      
#                                                                                                    
#     BEGIN_NAVI                                                                                     
#     SELECT_WAFER C0007                                                                             
#     SELECT_PROBE IC26W                                                                             
#     SELECT_DIE   C0007                                                                             
#     SELECT_TEST  C0007_ET_20220720                                                                 
#     DIE_TEST     C0007                                                        C0007_ET_20220720    
#     END_NAVI                                                                                       
      SELECT       WAFER,"C0007"                                                                     
      SELECT       PROBE,"IC26W"                                                                     
      TEST         "C0007","C0007_ET_20220720"                                                       
      LOOP                                                                                           
$---- ------------ ------------------------------------------------------------ ----------------- - -

