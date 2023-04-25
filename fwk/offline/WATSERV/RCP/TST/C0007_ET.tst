#Test	C0007_ET	1	03/09/2022	15:08:23	wat	Description for this Test spec.

$Type: Test
$Name: C0007_ET
$Vers: 1
$Desc: Description for this Test spec.
$Date: 03/09/2022
$Time: 15:08:23
$User: wat
$------------------------------- ----------- -------------------------------------------------------------------- ----------------------- ----------------------------------- -
 BODY                                                                                                                                                                          
                                                                                                                                                                               
 `RE07`::                                                                                                                                                                      
 `VTGM_MVN_PID_4`:               VT          VD=0.1,IDTARG=1E-07*(3/0.6),VGMAX=1.2                                `R[900001]`             Drain=11,Gate=10,Source=12,Bulk=22   
 `IG_MVN_PID_4`:                 IOFF_4T     VG=7                                                                 ,`R[900002]`            Drain=11,Gate=10,Source=12,Bulk=22   
 `VTGM_MVN_PID_5`:               VT          VD=0.1,IDTARG=1E-07*(3/0.6),VGMAX=1.2                                `R[900003]`             Drain=14,Gate=13,Source=15,Bulk=22   
 `IG_MVN_PID_5`:                 IOFF_4T     VG=7                                                                 ,`R[900004]`            Drain=14,Gate=13,Source=15,Bulk=22   
 `VTGM_MVN_PID_6`:               VT          VD=0.1,IDTARG=1E-07*(3/0.6),VGMAX=1.2                                `R[900005]`             Drain=17,Gate=16,Source=18,Bulk=22   
 `IG_MVN_PID_6`:                 IOFF_4T     VG=7                                                                 ,`R[900006]`            Drain=17,Gate=16,Source=18,Bulk=22   
 `RE08`::                                                                                                                                                                      
 `VTGM_MVP_PID_4`:               VT          VD=-0.1,IDTARG=-1E-07*(3.6/0.5),VGMAX=-1.2                           `R[900007]`             Drain=11,Gate=10,Source=12,Bulk=22   
 `IG_MVP_PID_4`:                 IOFF_4T     VG=-7                                                                ,`R[900008]`            Drain=11,Gate=10,Source=12,Bulk=22   
 `VTGM_MVP_PID_5`:               VT          VD=-0.1,IDTARG=-1E-07*(3.6/0.5),VGMAX=-1.2                           `R[900009]`             Drain=14,Gate=13,Source=15,Bulk=22   
 `IG_MVP_PID_5`:                 IOFF_4T     VG=-7                                                                ,`R[900010]`            Drain=14,Gate=13,Source=15,Bulk=22   
 `VTGM_MVP_PID_6`:               VT          VD=-0.1,IDTARG=-1E-07*(3.6/0.5),VGMAX=-1.2                           `R[900011]`             Drain=17,Gate=16,Source=18,Bulk=22   
 `IG_MVP_PID_6`:                 IOFF_4T     VG=-7                                                                ,`R[900012]`            Drain=17,Gate=16,Source=18,Bulk=22   
                                                                                                                                                                               
                                                                                                                                                                               
#`HV01`::                                                                                                                                                                      
#`11000`:                        VTGM_STD    vds=0.1,vg_stop=2,vg_points=101                                      `R[11000]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`HV02`::                                                                                                                                                                      
#`11001`:                        VTGM_STD    vds=-0.1,vg_stop=-2,vg_points=101                                    `R[11001]`              Drain=6,Gate=5,Source=7,Bulk=8       
#`HV03`::                                                                                                                                                                      
#`11002`:                        VTGM_STD    vds=0.1,vg_stop=2,vg_points=101                                      `R[11002]`              Drain=2,Gate=1,Source=3,Bulk=4       
#                                                                                                                                                                              
#`PLK01`::                                                                                                                                                                     
#`VTGM_N18_dio_dum_10_D18`:      VTGM_STD    vds=0.1,vg_stop=1.8,vg_points=101                                    `R[10034]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`VTGM_N18_dio_10_10`:           VTGM_STD    vds=0.1,vg_stop=1.8,vg_points=101                                    `R[10035]`              Drain=9,Source=10,Gate=4,Bulk=5      
#`PLK02`::                                                                                                                                                                     
#`VTGM_P18_dio_dum_10_D18`:      VTGM_STD    vds=-0.1,vg_stop=-1.8,vg_points=101                                  `R[30034]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`VTGM_P18_dio_10_10`:           VTGM_STD    vds=-0.1,vg_stop=-1.8,vg_points=101                                  `R[30035]`              Drain=9,Source=10,Gate=4,Bulk=5      
                                                                                                                                                                               
 `PLK05`::                                                                                                                                                                     
 `VTGM_N50_dio_dum_10_D5`:       VTGM_STD    vds=0.1,vg_stop=2,vg_points=101                                      `R[50029]`              Drain=8,Source=7,Gate=4,Bulk=5       
#`PLK06`::                                                                                                                                                                     
#`VTGM_N50_dio_10_10`:           VTGM_STD    vds=0.1,vg_stop=2,vg_points=101                                      `R[60025]`              Drain=1,Source=2,Gate=6,Bulk=7       
#`PLK03`::                                                                                                                                                                     
#`VTGM_N50_dio_10_D5`:           VTGM_STD    vds=0.1,vg_stop=2,vg_points=101                                      `R[60026]`              Drain=18,Source=17,Gate=14,Bulk=15   
 `PLK08`::                                                                                                                                                                     
 `VTGM_P50_dio_dum_10_D5`:       VTGM_STD    vds=-0.1,vg_stop=-2,vg_points=101                                    `R[80029]`              Drain=18,Source=17,Gate=14,Bulk=15   
#`PLK09`::                                                                                                                                                                     
#`VTGM_P50_dio_10_10`:           VTGM_STD    vds=-0.1,vg_stop=-2,vg_points=101                                    `R[90025]`              Drain=1,Source=2,Gate=6,Bulk=7       
#`PLK05`::                                                                                                                                                                     
#`VTGM_P50_dio_10_D5`:           VTGM_STD    vds=-0.1,vg_stop=-2,vg_points=101                                    `R[90026]`              Drain=10,Source=9,Gate=6,Bulk=7      
                                                                                                                                                                               
 `PLK03`::                                                                                                                                                                     
#`VTLIN_N50_dio_dum_10_D7`:      VT          VD=0.1,IDTARG=1E-07*(10/0.7),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[50001]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`VTSAT_N50_dio_dum_10_D7`:      VT          VD=1.1*5,IDTARG=1E-07*(10/0.7),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002      `R[50002]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`IDL_N50_dio_dum_10_D7`:        IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[50003]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`IDS_N50_dio_dum_10_D7`:        IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[50004]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`ISUB_N50_dio_dum_10_D7`:       ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[50005]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`IOFF_N50_dio_dum_10_D7`:       IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[50006]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`BVDS_N50_dio_dum_10_D7`:       BVDS        VDMAX=80                                                             `R[50007]`              Drain=1,Source=2,Gate=4,Bulk=5       
#`VTLIN_N50_dio_dum_10_D65`:     VT          VD=0.1,IDTARG=1E-07*(10/0.65),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[50008]`              Drain=3,Source=2,Gate=4,Bulk=5       
#`VTSAT_N50_dio_dum_10_D65`:     VT          VD=1.1*5,IDTARG=1E-07*(10/0.65),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002     `R[50009]`              Drain=3,Source=2,Gate=4,Bulk=5       
#`IDL_N50_dio_dum_10_D65`:       IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[50010]`              Drain=3,Source=2,Gate=4,Bulk=5       
#`IDS_N50_dio_dum_10_D65`:       IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[50011]`              Drain=3,Source=2,Gate=4,Bulk=5       
#`ISUB_N50_dio_dum_10_D65`:      ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[50012]`              Drain=3,Source=2,Gate=4,Bulk=5       
#`IOFF_N50_dio_dum_10_D65`:      IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[50013]`              Drain=3,Source=2,Gate=4,Bulk=5       
#`BVDS_N50_dio_dum_10_D65`:      BVDS        VDMAX=80                                                             `R[50014]`              Drain=3,Source=2,Gate=4,Bulk=5       
 `VTLIN_N50_dio_dum_10_D6`:      VT          VD=0.1,IDTARG=1E-07*(10/0.6),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[50015]`              Drain=6,Source=7,Gate=4,Bulk=5       
 `VTSAT_N50_dio_dum_10_D6`:      VT          VD=1.1*5,IDTARG=1E-07*(10/0.6),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002      `R[50016]`              Drain=6,Source=7,Gate=4,Bulk=5       
 `IDL_N50_dio_dum_10_D6`:        IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[50017]`              Drain=6,Source=7,Gate=4,Bulk=5       
 `IDS_N50_dio_dum_10_D6`:        IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[50018]`              Drain=6,Source=7,Gate=4,Bulk=5       
#`ISUB_N50_dio_dum_10_D6`:       ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[50019]`              Drain=6,Source=7,Gate=4,Bulk=5       
 `IOFF_N50_dio_dum_10_D6`:       IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[50020]`              Drain=6,Source=7,Gate=4,Bulk=5       
 `BVDS_N50_dio_dum_10_D6`:       BVDS        VDMAX=80                                                             `R[50021]`              Drain=6,Source=7,Gate=4,Bulk=5       
 `VTLIN_N50_dio_dum_10_D5`:      VT          VD=0.1,IDTARG=1E-07*(10/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[50022]`              Drain=8,Source=7,Gate=4,Bulk=5       
 `VTSAT_N50_dio_dum_10_D5`:      VT          VD=1.1*5,IDTARG=1E-07*(10/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002      `R[50023]`              Drain=8,Source=7,Gate=4,Bulk=5       
 `IDL_N50_dio_dum_10_D5`:        IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[50024]`              Drain=8,Source=7,Gate=4,Bulk=5       
 `IDS_N50_dio_dum_10_D5`:        IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[50025]`              Drain=8,Source=7,Gate=4,Bulk=5       
 `ISUB_N50_dio_dum_10_D5`:       ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.05,UNIT=2                  `R[50026]`              Drain=8,Source=7,Gate=4,Bulk=5       
 `IOFF_N50_dio_dum_10_D5`:       IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[50027]`              Drain=8,Source=7,Gate=4,Bulk=5       
 `BVDS_N50_dio_dum_10_D5`:       BVDS        VDMAX=80                                                             `R[50028]`              Drain=8,Gate=4,Source=7,Bulk=5       
#`VTGM_N50_dio_dum_10_D5`:       vth_gm_std  vds=0.1V,vg_stop=5V,vg_points=101                                    `R[50029]`              drain=8,gate=4,source=7,subst=5      
 `VTLIN_N50_dio_10_10`:          VT          VD=0.1,IDTARG=1E-07*(10/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[60001]`              Drain=9,Source=10,Gate=14,Bulk=15    
 `VTSAT_N50_dio_10_10`:          VT          VD=1.1*5,IDTARG=1E-07*(10/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[60002]`              Drain=9,Source=10,Gate=14,Bulk=15    
 `IDL_N50_dio_10_10`:            IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[60003]`              Drain=9,Source=10,Gate=14,Bulk=15    
 `IDS_N50_dio_10_10`:            IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[60004]`              Drain=9,Source=10,Gate=14,Bulk=15    
#`ISUB_N50_dio_10_10`:           ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[60005]`              Drain=9,Source=10,Gate=14,Bulk=15    
 `IOFF_N50_dio_10_10`:           IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[60006]`              Drain=9,Source=10,Gate=14,Bulk=15    
 `BVDS_N50_dio_10_10`:           BVDS        VDMAX=80                                                             `R[60007]`              Drain=9,Source=10,Gate=14,Bulk=15    
 `VTGM_N50_dio_10_10`:           vth_gm_std  vds=0.1V,vg_stop=2V,vg_points=101                                    `R[60022]`              drain=9,gate=14,source=10,subst=15   
#`VTLIN_N50_dio_10_D7`:          VT          VD=0.1,IDTARG=1E-07*(10/0.7),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[11038]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`VTSAT_N50_dio_10_D7`:          VT          VD=1.1*5,IDTARG=1E-07*(10/0.7),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002      `R[11039]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`IDL_N50_dio_10_D7`:            IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[11040]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`IDS_N50_dio_10_D7`:            IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[11041]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`ISUB_N50_dio_10_D7`:           ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[11042]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`IOFF_N50_dio_10_D7`:           IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[11043]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`BVDS_N50_dio_10_D7`:           BVDS        VDMAX=80                                                             `R[11044]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`VTLIN_N50_dio_10_D65`:         VT          VD=0.1,IDTARG=1E-07*(10/0.65),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[11045]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`VTSAT_N50_dio_10_D65`:         VT          VD=1.1*5,IDTARG=1E-07*(10/0.65),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002     `R[11046]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`IDL_N50_dio_10_D65`:           IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[11047]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`IDS_N50_dio_10_D65`:           IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[11048]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`ISUB_N50_dio_10_D65`:          ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[11049]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`IOFF_N50_dio_10_D65`:          IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[11050]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`BVDS_N50_dio_10_D65`:          BVDS        VDMAX=80                                                             `R[11051]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`VTLIN_N50_dio_10_D6`:          VT          VD=0.1,IDTARG=1E-07*(10/0.6),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[60008]`              Drain=16,Source=17,Gate=14,Bulk=15   
#`VTSAT_N50_dio_10_D6`:          VT          VD=1.1*5,IDTARG=1E-07*(10/0.6),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002      `R[60009]`              Drain=16,Source=17,Gate=14,Bulk=15   
#`IDL_N50_dio_10_D6`:            IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[60010]`              Drain=16,Source=17,Gate=14,Bulk=15   
#`IDS_N50_dio_10_D6`:            IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[60011]`              Drain=16,Source=17,Gate=14,Bulk=15   
#`ISUB_N50_dio_10_D6`:           ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[60012]`              Drain=16,Source=17,Gate=14,Bulk=15   
#`IOFF_N50_dio_10_D6`:           IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[60013]`              Drain=16,Source=17,Gate=14,Bulk=15   
#`BVDS_N50_dio_10_D6`:           BVDS        VDMAX=80                                                             `R[60014]`              Drain=16,Source=17,Gate=14,Bulk=15   
#`VTLIN_N50_dio_10_D5`:          VT          VD=0.1,IDTARG=1E-07*(10/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[60015]`              Drain=18,Source=17,Gate=14,Bulk=15   
#`VTSAT_N50_dio_10_D5`:          VT          VD=1.1*5,IDTARG=1E-07*(10/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002      `R[60016]`              Drain=18,Source=17,Gate=14,Bulk=15   
#`IDL_N50_dio_10_D5`:            IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[60017]`              Drain=18,Source=17,Gate=14,Bulk=15   
#`IDS_N50_dio_10_D5`:            IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[60018]`              Drain=18,Source=17,Gate=14,Bulk=15   
#`ISUB_N50_dio_10_D5`:           ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[60019]`              Drain=18,Source=17,Gate=14,Bulk=15   
#`IOFF_N50_dio_10_D5`:           IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[60020]`              Drain=18,Source=17,Gate=14,Bulk=15   
#`BVDS_N50_dio_10_D5`:           BVDS        VDMAX=80                                                             `R[60021]`              Drain=18,Source=17,Gate=14,Bulk=15   
 `PLK04`::                                                                                                                                                                     
#`VTLIN_P50_dio_dum_10_D7`:      VT          VD=-0.1,IDTARG=-1E-07*(10/0.7),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[80001]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`VTSAT_P50_dio_dum_10_D7`:      VT          VD=-1.1*5,IDTARG=-1E-07*(10/0.7),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002  `R[80002]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`IDL_P50_dio_dum_10_D7`:        IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[80003]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`IDS_P50_dio_dum_10_D7`:        IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[80004]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`ISUB_P50_dio_dum_10_D7`:       ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[80005]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`IOFF_P50_dio_dum_10_D7`:       IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[80006]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`BVDS_P50_dio_dum_10_D7`:       BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[80007]`              Drain=11,Source=12,Gate=14,Bulk=15   
#`VTLIN_P50_dio_dum_10_D65`:     VT          VD=-0.1,IDTARG=-1E-07*(10/0.65),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[80008]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`VTSAT_P50_dio_dum_10_D65`:     VT          VD=-1.1*5,IDTARG=-1E-07*(10/0.65),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002 `R[80009]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`IDL_P50_dio_dum_10_D65`:       IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[80010]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`IDS_P50_dio_dum_10_D65`:       IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[80011]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`ISUB_P50_dio_dum_10_D65`:      ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[80012]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`IOFF_P50_dio_dum_10_D65`:      IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[80013]`              Drain=13,Source=12,Gate=14,Bulk=15   
#`BVDS_P50_dio_dum_10_D65`:      BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[80014]`              Drain=13,Source=12,Gate=14,Bulk=15   
 `VTLIN_P50_dio_dum_10_D6`:      VT          VD=-0.1,IDTARG=-1E-07*(10/0.6),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[80015]`              Drain=16,Source=17,Gate=14,Bulk=15   
 `VTSAT_P50_dio_dum_10_D6`:      VT          VD=-1.1*5,IDTARG=-1E-07*(10/0.6),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002  `R[80016]`              Drain=16,Source=17,Gate=14,Bulk=15   
 `IDL_P50_dio_dum_10_D6`:        IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[80017]`              Drain=16,Source=17,Gate=14,Bulk=15   
 `IDS_P50_dio_dum_10_D6`:        IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[80018]`              Drain=16,Source=17,Gate=14,Bulk=15   
#`ISUB_P50_dio_dum_10_D6`:       ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[80019]`              Drain=16,Source=17,Gate=14,Bulk=15   
 `IOFF_P50_dio_dum_10_D6`:       IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[80020]`              Drain=16,Source=17,Gate=14,Bulk=15   
 `BVDS_P50_dio_dum_10_D6`:       BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[80021]`              Drain=16,Source=17,Gate=14,Bulk=15   
 `VTLIN_P50_dio_dum_10_D5`:      VT          VD=-0.1,IDTARG=-1E-07*(10/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[80022]`              Drain=18,Source=17,Gate=14,Bulk=15   
 `VTSAT_P50_dio_dum_10_D5`:      VT          VD=-1.1*5,IDTARG=-1E-07*(10/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002  `R[80023]`              Drain=18,Source=17,Gate=14,Bulk=15   
 `IDL_P50_dio_dum_10_D5`:        IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[80024]`              Drain=18,Source=17,Gate=14,Bulk=15   
 `IDS_P50_dio_dum_10_D5`:        IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[80025]`              Drain=18,Source=17,Gate=14,Bulk=15   
 `ISUB_P50_dio_dum_10_D5`:       ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.05,UNIT=2               `R[80026]`              Drain=18,Source=17,Gate=14,Bulk=15   
 `IOFF_P50_dio_dum_10_D5`:       IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[80027]`              Drain=18,Source=17,Gate=14,Bulk=15   
 `BVDS_P50_dio_dum_10_D5`:       BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[80028]`              Drain=18,Source=17,Gate=14,Bulk=15   
#`VTGM_P50_dio_dum_10_D5`:       vth_gm_std  vds=-0.1V,vg_stop=-5V,vg_points=101                                  `R[80029]`              drain=18,gate=14,source=17,subst=15  
 `PLK05`::                                                                                                                                                                     
 `VTLIN_P50_dio_10_10`:          VT          VD=-0.1,IDTARG=-1E-07*(10/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[90001]`              Drain=1,Source=2,Gate=6,Bulk=7       
 `VTSAT_P50_dio_10_10`:          VT          VD=-1.1*5,IDTARG=-1E-07*(10/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[90002]`              Drain=1,Source=2,Gate=6,Bulk=7       
 `IDL_P50_dio_10_10`:            IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[90003]`              Drain=1,Source=2,Gate=6,Bulk=7       
 `IDS_P50_dio_10_10`:            IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[90004]`              Drain=1,Source=2,Gate=6,Bulk=7       
#`ISUB_P50_dio_10_10`:           ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[90005]`              Drain=1,Source=2,Gate=6,Bulk=7       
 `IOFF_P50_dio_10_10`:           IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[90006]`              Drain=1,Source=2,Gate=6,Bulk=7       
 `BVDS_P50_dio_10_10`:           BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[90007]`              Drain=1,Source=2,Gate=6,Bulk=7       
 `VTGM_P50_dio_10_10`:           vth_gm_std  vds=-0.1V,vg_stop=-2V,vg_points=101                                  `R[90022]`              drain=1,gate=6,source=2,subst=7      
#`VTLIN_P50_dio_10_D7`:          VT          VD=-0.1,IDTARG=-1E-07*(10/0.7),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[11052]`              Drain=3,Source=4,Gate=6,Bulk=7       
#`VTSAT_P50_dio_10_D7`:          VT          VD=-1.1*5,IDTARG=-1E-07*(10/0.7),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002  `R[11053]`              Drain=3,Source=4,Gate=6,Bulk=7       
#`IDL_P50_dio_10_D7`:            IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[11054]`              Drain=3,Source=4,Gate=6,Bulk=7       
#`IDS_P50_dio_10_D7`:            IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[11055]`              Drain=3,Source=4,Gate=6,Bulk=7       
#`ISUB_P50_dio_10_D7`:           ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[11056]`              Drain=3,Source=4,Gate=6,Bulk=7       
#`IOFF_P50_dio_10_D7`:           IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[11057]`              Drain=3,Source=4,Gate=6,Bulk=7       
#`BVDS_P50_dio_10_D7`:           BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[11058]`              Drain=3,Source=4,Gate=6,Bulk=7       
#`VTLIN_P50_dio_10_D65`:         VT          VD=-0.1,IDTARG=-1E-07*(10/0.65),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[11059]`              Drain=5,Source=4,Gate=6,Bulk=7       
#`VTSAT_P50_dio_10_D65`:         VT          VD=-1.1*5,IDTARG=-1E-07*(10/0.65),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002 `R[11060]`              Drain=5,Source=4,Gate=6,Bulk=7       
#`IDL_P50_dio_10_D65`:           IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[11061]`              Drain=5,Source=4,Gate=6,Bulk=7       
#`IDS_P50_dio_10_D65`:           IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[11062]`              Drain=5,Source=4,Gate=6,Bulk=7       
#`ISUB_P50_dio_10_D65`:          ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[11063]`              Drain=5,Source=4,Gate=6,Bulk=7       
#`IOFF_P50_dio_10_D65`:          IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[11064]`              Drain=5,Source=4,Gate=6,Bulk=7       
#`BVDS_P50_dio_10_D65`:          BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[11065]`              Drain=5,Source=4,Gate=6,Bulk=7       
#`VTLIN_P50_dio_10_D6`:          VT          VD=-0.1,IDTARG=-1E-07*(10/0.6),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[90008]`              Drain=8,Source=9,Gate=6,Bulk=7       
#`VTSAT_P50_dio_10_D6`:          VT          VD=-1.1*5,IDTARG=-1E-07*(10/0.6),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002  `R[90009]`              Drain=8,Source=9,Gate=6,Bulk=7       
#`IDL_P50_dio_10_D6`:            IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[90010]`              Drain=8,Source=9,Gate=6,Bulk=7       
#`IDS_P50_dio_10_D6`:            IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[90011]`              Drain=8,Source=9,Gate=6,Bulk=7       
#`ISUB_P50_dio_10_D6`:           ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[90012]`              Drain=8,Source=9,Gate=6,Bulk=7       
#`IOFF_P50_dio_10_D6`:           IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[90013]`              Drain=8,Source=9,Gate=6,Bulk=7       
#`BVDS_P50_dio_10_D6`:           BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[90014]`              Drain=8,Source=9,Gate=6,Bulk=7       
#`VTLIN_P50_dio_10_D5`:          VT          VD=-0.1,IDTARG=-1E-07*(10/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[90015]`              Drain=10,Source=9,Gate=6,Bulk=7      
#`VTSAT_P50_dio_10_D5`:          VT          VD=-1.1*5,IDTARG=-1E-07*(10/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002  `R[90016]`              Drain=10,Source=9,Gate=6,Bulk=7      
#`IDL_P50_dio_10_D5`:            IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[90017]`              Drain=10,Source=9,Gate=6,Bulk=7      
#`IDS_P50_dio_10_D5`:            IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[90018]`              Drain=10,Source=9,Gate=6,Bulk=7      
#`ISUB_P50_dio_10_D5`:           ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[90019]`              Drain=10,Source=9,Gate=6,Bulk=7      
#`IOFF_P50_dio_10_D5`:           IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[90020]`              Drain=10,Source=9,Gate=6,Bulk=7      
#`BVDS_P50_dio_10_D5`:           BVDS        VDMAX=-80,IDTARG=-1E-06                                              `R[90021]`              Drain=10,Source=9,Gate=6,Bulk=7      
 `PLK06`::                                                                                                                                                                     
 `VTLIN_N50_Nat_dio_10_1D2`:     VT          VD=0.1,IDTARG=1E-07*(10/1.2),VGMIN=-0.5,VGMAX=0.5,VGSTEP=0.002       `R[120001]`             Drain=11,Source=12,Gate=14,Bulk=15   
 `VTSAT_N50_Nat_dio_10_1D2`:     VT          VD=1.1*5,IDTARG=1E-07*(10/1.2),VGMIN=-0.5,VGMAX=0.5,VGSTEP=0.002     `R[120002]`             Drain=11,Source=12,Gate=14,Bulk=15   
#`IDL_N50_Nat_dio_10_1D2`:       IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[120003]`             Drain=11,Source=12,Gate=14,Bulk=15   
 `IDS_N50_Nat_dio_10_1D2`:       IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[120004]`             Drain=11,Source=12,Gate=14,Bulk=15   
 `IOF_N50_Nat_dio_10_1D2`:       IOFF_4T     W=10,VD=1.1*5,VG=-2,VB=-1.5                                          `R[120005]`             Drain=11,Source=12,Gate=14,Bulk=15   
 `BV_N50_Nat_dio_10_1D2`:        BVDS        VG=-0.5,VDMIN=5,VDMAX=25,IDTARG=1E-06*10                             `R[120006]`             Drain=11,Source=12,Gate=14,Bulk=15   
 `VTLIN_N50_Nat_dio_10_1D6`:     VT          VD=0.1,IDTARG=1E-07*(10/1.6),VGMIN=-0.5,VGMAX=0.5,VGSTEP=0.002       `R[120007]`             Drain=13,Source=12,Gate=14,Bulk=15   
 `VTSAT_N50_Nat_dio_10_1D6`:     VT          VD=1.1*5,IDTARG=1E-07*(10/1.6),VGMIN=-0.5,VGMAX=0.5,VGSTEP=0.002     `R[120008]`             Drain=13,Source=12,Gate=14,Bulk=15   
#`IDL_N50_Nat_dio_10_1D6`:       IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[120009]`             Drain=13,Source=12,Gate=14,Bulk=15   
 `IDS_N50_Nat_dio_10_1D6`:       IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[120010]`             Drain=13,Source=12,Gate=14,Bulk=15   
 `IOF_N50_Nat_dio_10_1D6`:       IOFF_4T     W=10,VD=1.1*5,VG=-2,VB=-1.5                                          `R[120011]`             Drain=13,Source=12,Gate=14,Bulk=15   
 `BV_N50_Nat_dio_10_1D6`:        BVDS        VG=-0.5,VDMIN=5,VDMAX=25,IDTARG=1E-06*10                             `R[120012]`             Drain=13,Source=12,Gate=14,Bulk=15   
 `PLK07`::                                                                                                                                                                     
#`VTLIN_N50_Nat_dio_LDD_10_1D2`: VT          VD=0.1,IDTARG=1E-07*(10/1.2),VGMIN=-0.5,VGMAX=0.5,VGSTEP=0.002       `R[10013]`              Drain=6,Source=7,Gate=4,Bulk=5       
#`VTSAT_N50_Nat_dio_LDD_10_1D2`: VT          VD=1.1*5,IDTARG=1E-07*(10/1.2),VGMIN=-0.5,VGMAX=0.5,VGSTEP=0.002     `R[10014]`              Drain=6,Source=7,Gate=4,Bulk=5       
#`IDL_N50_Nat_dio_LDD_10_1D2`:   IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[10015]`              Drain=6,Source=7,Gate=4,Bulk=5       
#`IDS_N50_Nat_dio_LDD_10_1D2`:   IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[10016]`              Drain=6,Source=7,Gate=4,Bulk=5       
#`IOF_N50_Nat_dio_LDD_10_1D2`:   IDSAT       VD=1.1*5,VG=-1,UNIT=1,D=10                                           `R[10017]`              Drain=6,Source=7,Gate=4,Bulk=5       
#`BV_N50_Nat_dio_LDD_10_1D2`:    BVDS        VG=0.5,VDMAX=80,IDTARG=1E-06*10                                      `R[10018]`              Drain=6,Source=7,Gate=4,Bulk=5       
#`VTLIN_N50_Nat_dio_LDD_10_1D6`: VT          VD=0.1,IDTARG=1E-07*(10/1.6),VGMIN=-0.5,VGMAX=0.5,VGSTEP=0.002       `R[10019]`              Drain=8,Source=7,Gate=4,Bulk=5       
#`VTSAT_N50_Nat_dio_LDD_10_1D6`: VT          VD=1.1*5,IDTARG=1E-07*(10/1.6),VGMIN=-0.5,VGMAX=0.5,VGSTEP=0.002     `R[10020]`              Drain=8,Source=7,Gate=4,Bulk=5       
#`IDL_N50_Nat_dio_LDD_10_1D6`:   IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[10021]`              Drain=8,Source=7,Gate=4,Bulk=5       
#`IDS_N50_Nat_dio_LDD_10_1D6`:   IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[10022]`              Drain=8,Source=7,Gate=4,Bulk=5       
#`IOF_N50_Nat_dio_LDD_10_1D6`:   IDSAT       VD=1.1*5,VG=-1,UNIT=1,D=10                                           `R[10023]`              Drain=8,Source=7,Gate=4,Bulk=5       
#`BV_N50_Nat_dio_LDD_10_1D6`:    BVDS        VG=0.5,VDMAX=80,IDTARG=1E-06*10                                      `R[10024]`              Drain=8,Source=7,Gate=4,Bulk=5       
#`LK_N+_PWL_WD22`:               FVSI        VH=1.1*5                                                             `R[140007]`             H=13,L=14                            
#`JCAP_N+_PWL_WD22`:             CAP_TOX     VF=1.1*5,AREA=1,Darea=1,SL=0.045                                     ,`R140008`              H=13,L=14                            
#`R[140008]`:                    DUMMY       Input=R140008*1000                                                   `R[140008]`                                                  
 `BV_N+_PWL_WD22`:               BVOX        VGMIN=5,VGMAX=5*4                                                    `R[140009]`             Gate=13,Bulk=14                      
#`LK_P+_NWL_WD22`:               FVSI        VH=-1.1*5                                                            `R[140010]`             H=15,L=16                            
#`JCAP_P+_NWL_WD22`:             CAP_TOX     VF=-1.1*5,AREA=1,Darea=1,SL=0.045                                    ,`R140011`              H=15,L=16                            
#`R[140011]`:                    DUMMY       Input=R140011*1000                                                   `R[140011]`                                                  
 `BV_P+_NWL_WD22`:               BVOX        VGMIN=5,VGMAX=5*4                                                    `R[140012]`             Gate=16,Bulk=15                      
                                                                                                                                                                               
 `PLK08`::                                                                                                                                                                     
 `RS_N+_SAB_WD42`:               R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[150001]`             H=1,L=2                              
 `RS_N+_SAB_W2`:                 R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[150002]`             H=3,L=2                              
 `RS_P+_SAB_WD42`:               R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[150003]`             H=4,L=5                              
 `RS_P+_SAB_W2`:                 R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[150004]`             H=6,L=5                              
 `RS_NPO_SAB_WD42`:              R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[150005]`             H=8,L=9                              
 `RS_NPO_SAB_W2`:                R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[150006]`             H=10,L=9                             
 `RS_PPO_SAB_WD42`:              R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[160001]`             H=11,L=12                            
 `RS_PPO_SAB_W2`:                R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[160002]`             H=13,L=12                            
 `RS_N+_WD42`:                   R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R160003`               H=14,L=15                            
 `R160003`:                      DUMMY       Input=R160003                                                        `R[160003]`                                                  
 `RS_N+_W2`:                     R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R160004`               H=16,L=15                            
 `1`:                            DUMMY       Input=R160004                                                        `R[160004]`                                                  
 `RS_P+_WD42`:                   R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[160005]`             H=18,L=19                            
 `RS_P+_W2`:                     R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R160006`               H=20,L=19                            
 `2`:                            DUMMY       Input=R160006                                                        `R[160006]`                                                  
 `PLK09`::                                                                                                                                                                     
 `RS_NPO_WD42`:                  R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[170001]`             H=1,L=2                              
 `RS_NPO_W2`:                    R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R170002`               H=3,L=2                              
 `RSFV_NP_2_10`:                 DUMMY       Input=R170002                                                        `R[170002]`                                                  
 `RS_PPO_WD42`:                  R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[170003]`             H=4,L=5                              
 `RS_PPO_W2`:                    R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R170004`               H=6,L=5                              
 `RSFV_PP_2_10`:                 DUMMY       Input=R170004                                                        `R[170004]`                                                  
#`RS_N+_WD42_WOLDD`:             R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[170005]`             H=8,L=9                              
#`RS_N+_W20_WOLDD`:              R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[170006]`             H=10,L=9                             
#`RS_P+_WD42_WOLDD`:             R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[180001]`             H=11,L=12                            
#`RS_P+_W20_WOLDD`:              R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[180002]`             H=13,L=12                            
 `RS_NWL_WD86`:                  R2T_FV      VF=0.1,FLG=1,SQR=10                                                  `R[180005]`             H=18,L=19                            
 `RS_NWL_W2D1`:                  R2T_FV      VF=0.1,FLG=1,SQR=5                                                   `R[180006]`             H=20,L=19                            
 `PLK10`::                                                                                                                                                                     
 `RC_N+WD22_L`:                  R2T_FI      IFORCE=0.0001,FLG=2,COUNT=2376                                       `R190001`               H=1,L=2                              
 `R[190001]`:                    DUMMY       Input=R190001-R160004                                                `R[190001]`                                                  
 `RC_P+WD22_L`:                  R2T_FI      IFORCE=0.0001,FLG=2,COUNT=2376                                       `R190002`               H=4,L=5                              
 `R[190002]`:                    DUMMY       Input=R190002-R160006                                                `R[190002]`                                                  
 `RC_NPOWD22_L`:                 R2T_FI      IFORCE=0.0001,FLG=2,COUNT=2376                                       `R190003`               H=7,L=8                              
 `R[190003]`:                    DUMMY       Input=R190003-R170002                                                `R[190003]`                                                  
 `RC_PPOWD22_L`:                 R2T_FI      IFORCE=0.0001,FLG=2,COUNT=2376                                       `R190004`               H=10,L=11                            
 `R[190004]`:                    DUMMY       Input=R190004-R170004                                                `R[190004]`                                                  
 `RC_N+WD22_L_FV`:               R2T_FI_GNDU IFORCE=0.0001,FLG=2,COUNT=2376                                       `R500001`               H=1,L=2                              
                                 DUMMY       Input=R500001-R160004                                                `R[500001]`                                                  
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
                                                                                                                                                                               
#`PLK11`::                                                                                                                                                                     
#`VT_Nfp_SD42`:                  VT          VD=1.1*5,IDTARG=1E-06,VGMIN=5,VGMAX=4*5                              `R[200007]`             Drain=11,Gate=10,Source=12,Bulk=9    
#`VTSAT_Nfp_SD42`:               VT_DG       IDTARG=1E-06,VGMIN=5,VGMAX=4*5,VGSTEP=0.01                           `R[200008]`             Drain=11,Gate=10,Source=12,Bulk=9    
#`BV_Nfp_SD42`:                  BVDS        VG=1.1*5,VDMIN=5,VDMAX=4*5,IDTARG=1E-06                              `R[200009]`             Drain=11,Gate=10,Source=12,Bulk=9    
#`PLK12`::                                                                                                                                                                     
#`VT_Pfp_SD42`:                  VT          VD=-1.1*5,IDTARG=-1E-06,VGMIN=-5,VGMAX=-4*5                          `R[210007]`             Drain=7,Gate=6,Source=8,Bulk=5       
#`VTSAT_Pfp_SD42`:               VT_DG       IDTARG=1E-06,VGMIN=-5,VGMAX=-4*5,VGSTEP=0.01                         `R[210008]`             Drain=7,Gate=6,Source=8,Bulk=5       
#`BV_Pfp_SD42`:                  BVDS        VG=-1.1*5,VDMIN=-5,VDMAX=-4*5,IDTARG=-1E-06                          `R[210009]`             Drain=7,Gate=6,Source=8,Bulk=5       
#`VT_Nfm_SD42`:                  VT          VD=1.1*5,IDTARG=1E-06,VGMIN=5,VGMAX=4*5                              `R[220001]`             Drain=11,Gate=10,Source=12,Bulk=9    
#`VTSAT_Nfm_SD42`:               VT_DG       IDTARG=1E-06,VGMIN=5,VGMAX=4*5,VGSTEP=0.01                           `R[220002]`             Drain=11,Gate=10,Source=12,Bulk=9    
#`BV_Nfm_SD42`:                  BVDS        VG=1.1*5,VDMIN=5,VDMAX=4*5,IDTARG=1E-06                              `R[220003]`             Drain=11,Gate=10,Source=12,Bulk=9    
#`VT_Pfm_SD42`:                  VT          VD=-1.1*5,IDTARG=-1E-06,VGMIN=-5,VGMAX=-4*5                          `R[220004]`             Drain=15,Gate=14,Source=16,Bulk=13   
#`VTSAT_Pfm_SD42`:               VT_DG       IDTARG=-1E-06,VGMIN=-5,VGMAX=-4*5,VGSTEP=0.01                        `R[220005]`             Drain=15,Gate=14,Source=16,Bulk=13   
#`BV_Pfm_SD42`:                  BVDS        VG=-1.1*5,VDMIN=-5,VDMAX=-4*5,IDTARG=-1E-06                          `R[220006]`             Drain=15,Gate=14,Source=16,Bulk=13   
 `PLK13`::                                                                                                                                                                     
#`BV_N+_N+_SD28`:                BVOX        VGMAX=80                                                             `R[230001]`             Gate=1,Bulk=3                        
 `BV_N+_N+_SD42`:                BVOX        VGMAX=80                                                             `R[230002]`             Gate=4,Bulk=5                        
#`BV_P+_P+_SD28`:                BVOX        VGMAX=80                                                             `R[230003]`             Gate=7,Bulk=8                        
 `BV_P+_P+_SD42`:                BVOX        VGMAX=80                                                             `R[230004]`             Gate=10,Bulk=11                      
 `BV_N+_P+_SD28`:                BVOX        VGMAX=80                                                             `R[240003]`             Gate=20,Bulk=19                      
 `PLK14`::                                                                                                                                                                     
 `BV_N+_P+_SD42`:                BVOX        VGMAX=80                                                             `R[240004]`             Gate=2,Bulk=1                        
 `BV_NWL_NWL_S1D7`:              BVOX        VGMAX=80                                                             `R[250002]`             Gate=7,Bulk=8                        
 `BV_N+_NWL_SD8`:                BVOX        VGMAX=80                                                             `R[250004]`             Gate=13,Bulk=15                      
 `BV_PWL_N+_N+`:                 BVOX        VGMAX=80                                                             `R[260001]`             Gate=19,Bulk=17                      
 `PLK15`::                                                                                                                                                                     
 `BV_NWL_P+_P+`:                 BVOX        VGMAX=80                                                             `R[260002]`             Gate=1,Bulk=2                        
#`BV_N+_P+_SNW`:                 BVOX        VGMAX=80                                                             `R[260003]`             Gate=5,Bulk=6                        
 `BV_N+_P+_NWL`:                 BVOX        VGMAX=80                                                             `R[270001]`             Gate=9,Bulk=10                       
 `BV_NWL_PWL`:                   BVOX        VGMAX=80                                                             `R[270003]`             Gate=20,Bulk=18                      
 `PLK16`::                                                                                                                                                                     
 `RS_ACT_WD22SD28`:              R2T_FV      VF=0.1,FLG=1,SQR=23182                                               `R[280001]`             H=1,L=2                              
 `IBRI_ACT_WD22SD28`:            BVOX        VGMAX=80                                                             `R[280002]`             Gate=4,Bulk=5                        
 `RS_NPO_WD182SD25`:             R2T_FV      VF=0.1,FLG=1,SQR=32777                                               `R[280003]`             H=6,L=7                              
 `IBRI_NPO_WD182SD25`:           BVOX        VGMAX=80                                                             `R[280004]`             Gate=9,Bulk=10                       
 `BV_ME1_WD23SD23`:              BVOX        VGMAX=25                                                             `R[290001]`             Gate=11,Bulk=12                      
 `BV_ME1_WD23SD21`:              BVOX        VGMAX=25                                                             `R[290002]`             Gate=13,Bulk=14                      
#`BV_ME1_WD23SD25`:              BVOX        VGMAX=25                                                             `R[290003]`             Gate=15,Bulk=16                      
#`BV_ME1_WD5SD5`:                BVOX        VGMAX=25                                                             `R[290004]`             Gate=17,Bulk=18                      
 `BV_ME2_WD28SD28`:              BVOX        VGMAX=25                                                             `R[290005]`             Gate=19,Bulk=20                      
 `BV_ME2_WD28SD26`:              BVOX        VGMAX=25                                                             `R[290006]`             Gate=21,Bulk=22                      
#`PLK17`::                                                                                                                                                                     
#`BV_ME2_WD28SD3`:               BVOX        VGMAX=25                                                             `R[300001]`             Gate=1,Bulk=2                        
#`BV_ME2_WD5SD5`:                BVOX        VGMAX=25                                                             `R[300002]`             Gate=3,Bulk=4                        
 `PLK18`::                                                                                                                                                                     
 `BV_MET_W1D8S1D8`:              BVOX        VGMAX=25                                                             `R[320001]`             Gate=1,Bulk=2                        
#`BV_MET_W1D5S1D5`:              BVOX        VGMAX=25                                                             `R[320002]`             Gate=3,Bulk=4                        
#`BV_MET_W1D6S1D6`:              BVOX        VGMAX=25                                                             `R[320003]`             Gate=5,Bulk=6                        
 `BV_MET_W1D7S1D7`:              BVOX        VGMAX=25                                                             `R[320004]`             Gate=7,Bulk=8                        
#`BV_MET_W1D9S1D9`:              BVOX        VGMAX=25                                                             `R[320005]`             Gate=9,Bulk=10                       
#`BV_MET_W20S20`:                BVOX        VGMAX=25                                                             `R[320006]`             Gate=11,Bulk=12                      
 `RS_ME1_WD23SD23`:              R2T_FV      VF=0.1,FLG=1,SQR=22157                                               `R[330001]`             H=13,L=14                            
#`RS_ME1_WD23SD4`:               R2T_FV      VF=0.1,FLG=1,SQR=15627                                               `R[330002]`             H=15,L=16                            
 `RS_ME1_WD46SD4`:               R2T_FV      VF=0.1,FLG=1,SQR=5637                                                `R[330003]`             H=17,L=18                            
 `RS_ME2_WD28SD28`:              R2T_FV      VF=0.1,FLG=1,SQR=14624                                               `R[330004]`             H=19,L=20                            
 `RS_ME2_WD28SD4`:               R2T_FV      VF=0.1,FLG=1,SQR=11039                                               `R[330005]`             H=21,L=22                            
 `PLK19`::                                                                                                                                                                     
#`RS_ME2_WD5SD4`:                R2T_FV      VF=0.1,FLG=1,SQR=5190                                                `R[330006]`             H=1,L=2                              
 `CONTI_TM_1D8_385_READY1`:      R2T_FV      VF=0.1,FLG=1,SQR=385,HOLD=0.1,WAIT_TH=0.1                            `R350001_1`             H=15,L=16                            
 `CONTI_TM_1D8_385_READY2`:      R2T_FV      VF=0.1,FLG=1,SQR=385,HOLD=0.1,WAIT_TH=0.1                            `R350001_2`             H=15,L=16                            
 `CONTI_TM_1D8_385_READY3`:      R2T_FV      VF=0.1,FLG=1,SQR=385,HOLD=0.1,WAIT_TH=0.1                            `R350001_3`             H=15,L=16                            
 `CONTI_TM_1D8_385_READY4`:      R2T_FV      VF=0.1,FLG=1,SQR=385,HOLD=0.1,WAIT_TH=0.1                            `R350001_4`             H=15,L=16                            
 `CONTI_TM_1D8_385`:             R2T_FV      VF=0.1,FLG=1,SQR=385,HOLD=0.1,WAIT_TH=0.1                            `R[350001]`             H=15,L=16                            
 `CONTI_TM_1D8_385_T`:           R2T_FV      VF=0.1,FLG=1,SQR=385,HOLD=0.1,WAIT_TH=0.1                            `R[350011]`             H=15,L=16                            
 `RS_MET_W1D6S1D6`:              R2T_FV      VF=0.1,FLG=1,SQR=497,HOLD=0.1,WAIT_TH=0.1                            `R[350002]`             H=17,L=18                            
#`RS_MET_W2S2`:                  R2T_FV      VF=0.1,FLG=1,SQR=295,HOLD=0.1,WAIT_TH=0.1                            `R[350003]`             H=19,L=20                            
 `RC_VA1_Chain_SD26SD26`:        R2T_FI      FLG=2,COUNT=2664,HOLD=0.1                                            `R[10237]`              H=21,L=22                            
 `PLK20`::                                                                                                                                                                     
#`RC_VAT_Chain_SD6SD36`:         R2T_FI      IFORCE=0.0001,FLG=2,COUNT=2108                                       `R[10239]`              H=3,L=4                              
#`RC_VAT_Chain_S2SD36`:          R2T_FI      IFORCE=0.0001,FLG=2,COUNT=252                                        `R[10240]`              H=5,L=6                              
#`RC_VA1_Chain_SD23SD28`:        R2T_FI      IFORCE=0.0001,FLG=2,COUNT=3784                                       `R[360001]`             H=7,L=8                              
#`RC_VAT_Chain_SD46`:            R2T_FI      IFORCE=0.0001,FLG=2,COUNT=2520                                       `R[360003]`             H=11,L=12                            
 `RC_VAT_Chain_S1D8SD36`:        R2T_FI      IFORCE=0.0001,FLG=2,COUNT=252                                        `R[360004]`             H=13,L=14                            
#`RC_N+SD23`:                    R2T_FI      IFORCE=0.0001,FLG=2,COUNT=6120                                       `R[37001]`              H=15,L=16                            
#`RC_P+SD28`:                    R2T_FI      IFORCE=0.0001,FLG=2,COUNT=6120                                       `R[37002]`              H=18,L=19                            
#`PLK21`::                                                                                                                                                                     
#`RC_NPOSD25`:                   R2T_FI      IFORCE=0.0001,FLG=2,COUNT=6120                                       `R[37003]`              H=1,L=2                              
#`RC_PPOSD25`:                   R2T_FI      IFORCE=0.0001,FLG=2,COUNT=6120                                       `R[37004]`              H=4,L=5                              
 `MO01`::                                                                                                                                                                      
#`VTLIN_N50_10_D4`:              VT          VD=0.1,IDTARG=1E-07*(10/0.4),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20281]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTSAT_N50_10_D4`:              VT          VD=1*5,IDTARG=1E-07*(10/0.4),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20282]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IDL_N50_10_D4`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20283]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IDS_N50_10_D4`:                IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20284]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`ISUB_N50_10_D4`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20285]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IOFF_N50_10_D4`:               IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20286]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`BVDS_N50_10_D4`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20287]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTLIN_N50_10_D45`:             VT          VD=0.1,IDTARG=1E-07*(10/0.45),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[20288]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`VTSAT_N50_10_D45`:             VT          VD=1*5,IDTARG=1E-07*(10/0.45),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[20289]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IDL_N50_10_D45`:               IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20290]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IDS_N50_10_D45`:               IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20291]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`ISUB_N50_10_D45`:              ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20292]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IOFF_N50_10_D45`:              IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20293]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`BVDS_N50_10_D45`:              BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20294]`              Drain=4,Gate=1,Source=5,Bulk=22      
 `VTLIN_N50_10_D5`:              VT          VD=0.1,IDTARG=1E-07*(10/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20295]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`VTSAT_N50_10_D5`:              VT          VD=1*5,IDTARG=1E-07*(10/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20296]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IDL_N50_10_D5`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20297]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IDS_N50_10_D5`:                IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20298]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`ISUB_N50_10_D5`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.05,UNIT=2                  `R[20299]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IOFF_N50_10_D5`:               IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20300]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `BVDS_N50_10_D5`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20301]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`VTLIN_N50_10_D55`:             VT          VD=0.1,IDTARG=1E-07*(10/0.55),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[20302]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`VTSAT_N50_10_D55`:             VT          VD=1*5,IDTARG=1E-07*(10/0.55),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[20303]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IDL_N50_10_D55`:               IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20304]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IDS_N50_10_D55`:               IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20305]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`ISUB_N50_10_D55`:              ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.05,UNIT=2                  `R[20306]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IOFF_N50_10_D55`:              IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20307]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`BVDS_N50_10_D55`:              BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20308]`              Drain=8,Gate=1,Source=9,Bulk=22      
 `VTLIN_N50_10_D6`:              VT          VD=0.1,IDTARG=1E-07*(10/0.6),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20309]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`VTSAT_N50_10_D6`:              VT          VD=1*5,IDTARG=1E-07*(10/0.6),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20310]`              Drain=10,Gate=1,Source=11,Bulk=22    
 `IDL_N50_10_D6`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20311]`              Drain=10,Gate=1,Source=11,Bulk=22    
 `IDS_N50_10_D6`:                IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20312]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`ISUB_N50_10_D6`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20313]`              Drain=10,Gate=1,Source=11,Bulk=22    
 `IOFF_N50_10_D6`:               IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20314]`              Drain=10,Gate=1,Source=11,Bulk=22    
 `BVDS_N50_10_D6`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20315]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`VTLIN_N50_10_D7`:              VT          VD=0.1,IDTARG=1E-07*(10/0.7),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20316]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`VTSAT_N50_10_D7`:              VT          VD=1*5,IDTARG=1E-07*(10/0.7),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20317]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IDL_N50_10_D7`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20318]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IDS_N50_10_D7`:                IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20319]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`ISUB_N50_10_D7`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20320]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IOFF_N50_10_D7`:               IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20321]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`BVDS_N50_10_D7`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20322]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`VTLIN_N50_10_D8`:              VT          VD=0.1,IDTARG=1E-07*(10/0.8),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20323]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`VTSAT_N50_10_D8`:              VT          VD=1*5,IDTARG=1E-07*(10/0.8),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20324]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IDL_N50_10_D8`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20325]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IDS_N50_10_D8`:                IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20326]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`ISUB_N50_10_D8`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20327]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IOFF_N50_10_D8`:               IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20328]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`BVDS_N50_10_D8`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20329]`              Drain=14,Gate=1,Source=15,Bulk=22    
 `VTLIN_N50_10_1`:               VT          VD=0.1,IDTARG=1E-07*(10/1),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002          `R[20330]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`VTSAT_N50_10_1`:               VT          VD=1*5,IDTARG=1E-07*(10/1),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002          `R[20331]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`IDL_N50_10_1`:                 IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20332]`              Drain=16,Gate=1,Source=17,Bulk=22    
 `IDS_N50_10_1`:                 IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20333]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`ISUB_N50_10_1`:                ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20334]`              Drain=16,Gate=1,Source=17,Bulk=22    
 `IOFF_N50_10_1`:                IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20335]`              Drain=16,Gate=1,Source=17,Bulk=22    
 `BVDS_N50_10_1`:                BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20336]`              Drain=16,Gate=1,Source=17,Bulk=22    
 `VTLIN_N50_10_10`:              VT          VD=0.1,IDTARG=1E-07*(10/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[20337]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`VTSAT_N50_10_10`:              VT          VD=1*5,IDTARG=1E-07*(10/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[20338]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `IDL_N50_10_10`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=10                                              `R[20339]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `IDS_N50_10_10`:                IDSAT       VD=5,VG=5,UNIT=2,D=10                                                `R[20340]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`ISUB_N50_10_10`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20341]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `IOFF_N50_10_10`:               IDOFF       VD=1.1*5,UNIT=1,D=10,MODE=1                                          `R[20342]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `BVDS_N50_10_10`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20343]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `VTLIN_N50_1_10`:               VT          VD=0.1,IDTARG=1E-07*(1/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002          `R[20344]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`VTSAT_N50_1_10`:               VT          VD=1*5,IDTARG=1E-07*(1/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002          `R[20345]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `IDL_N50_1_10`:                 IDSAT       VD=0.1,VG=5,UNIT=2,D=1                                               `R[20346]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `IDS_N50_1_10`:                 IDSAT       VD=5,VG=5,UNIT=2,D=1                                                 `R[20347]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`ISUB_N50_1_10`:                ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20348]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `IOFF_N50_1_10`:                IDOFF       VD=1.1*5,UNIT=1,D=1,MODE=1                                           `R[20349]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `BVDS_N50_1_10`:                BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20350]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `MO02`::                                                                                                                                                                      
 `VTLIN_N50_D5_10`:              VT          VD=0.1,IDTARG=1E-07*(0.5/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20386]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTSAT_N50_D5_10`:              VT          VD=1*5,IDTARG=1E-07*(0.5/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20387]`              Drain=2,Gate=1,Source=3,Bulk=22      
 `IDL_N50_D5_10`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=0.5                                             `R[20388]`              Drain=2,Gate=1,Source=3,Bulk=22      
 `IDS_N50_D5_10`:                IDSAT       VD=5,VG=5,UNIT=2,D=0.5                                               `R[20389]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`ISUB_N50_D5_10`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20390]`              Drain=2,Gate=1,Source=3,Bulk=22      
 `IOFF_N50_D5_10`:               IDOFF       VD=1.1*5,UNIT=1,D=0.5,MODE=1                                         `R[20391]`              Drain=2,Gate=1,Source=3,Bulk=22      
 `BVDS_N50_D5_10`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20392]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTLIN_N50_D3_10`:              VT          VD=0.1,IDTARG=1E-07*(0.3/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20379]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`VTSAT_N50_D3_10`:              VT          VD=1*5,IDTARG=1E-07*(0.3/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20380]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IDL_N50_D3_10`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=0.3                                             `R[20381]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IDS_N50_D3_10`:                IDSAT       VD=5,VG=5,UNIT=2,D=0.3                                               `R[20382]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`ISUB_N50_D3_10`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20383]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IOFF_N50_D3_10`:               IDOFF       VD=1.1*5,UNIT=1,D=0.3,MODE=1                                         `R[20384]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`BVDS_N50_D3_10`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20385]`              Drain=4,Gate=1,Source=5,Bulk=22      
 `VTLIN_N50_D22_10`:             VT          VD=0.1,IDTARG=1E-07*(0.22/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[20358]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`VTSAT_N50_D22_10`:             VT          VD=1*5,IDTARG=1E-07*(0.22/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[20359]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IDL_N50_D22_10`:               IDSAT       VD=0.1,VG=5,UNIT=2,D=0.22                                            `R[20360]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IDS_N50_D22_10`:               IDSAT       VD=5,VG=5,UNIT=2,D=0.22                                              `R[20361]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`ISUB_N50_D22_10`:              ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20362]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IOFF_N50_D22_10`:              IDOFF       VD=1.1*5,UNIT=1,D=0.22,MODE=1                                        `R[20363]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `BVDS_N50_D22_10`:              BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20364]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`VTLIN_N50_D2_10`:              VT          VD=0.1,IDTARG=1E-07*(0.2/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20351]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTSAT_N50_D2_10`:              VT          VD=1*5,IDTARG=1E-07*(0.2/10),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002        `R[20352]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IDL_N50_D2_10`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=0.2                                             `R[20353]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IDS_N50_D2_10`:                IDSAT       VD=5,VG=5,UNIT=2,D=0.2                                               `R[20354]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`ISUB_N50_D2_10`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20355]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IOFF_N50_D2_10`:               IDOFF       VD=1.1*5,UNIT=1,D=0.2,MODE=1                                         `R[20356]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`BVDS_N50_D2_10`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20357]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTLIN_N50_5_D5`:               VT          VD=0.1,IDTARG=1E-07*(5/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[11066]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`VTSAT_N50_5_D5`:               VT          VD=1*5,IDTARG=1E-07*(5/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[11067]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IDL_N50_5_D5`:                 IDSAT       VD=0.1,VG=5,UNIT=2,D=5                                               `R[11068]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IDS_N50_5_D5`:                 IDSAT       VD=5,VG=5,UNIT=2,D=5                                                 `R[11069]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`ISUB_N50_5_D5`:                ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[11070]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IOFF_N50_5_D5`:                IDOFF       VD=1.1*5,UNIT=1,D=5,MODE=1                                           `R[11071]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`BVDS_N50_5_D5`:                BVDS        VDMAX=15,IDTARG=1E-06                                                `R[11072]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`VTLIN_N50_3_D5`:               VT          VD=0.1,IDTARG=1E-07*(3/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[11073]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`VTSAT_N50_3_D5`:               VT          VD=1*5,IDTARG=1E-07*(3/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[11074]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IDL_N50_3_D5`:                 IDSAT       VD=0.1,VG=5,UNIT=2,D=3                                               `R[11075]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IDS_N50_3_D5`:                 IDSAT       VD=5,VG=5,UNIT=2,D=3                                                 `R[11076]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`ISUB_N50_3_D5`:                ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[11077]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IOFF_N50_3_D5`:                IDOFF       VD=1.1*5,UNIT=1,D=3,MODE=1                                           `R[11078]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`BVDS_N50_3_D5`:                BVDS        VDMAX=15,IDTARG=1E-06                                                `R[11079]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`VTLIN_N50_1_D5`:               VT          VD=0.1,IDTARG=1E-07*(1/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[20414]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`VTSAT_N50_1_D5`:               VT          VD=1*5,IDTARG=1E-07*(1/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002         `R[20415]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IDL_N50_1_D5`:                 IDSAT       VD=0.1,VG=5,UNIT=2,D=1                                               `R[20416]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IDS_N50_1_D5`:                 IDSAT       VD=5,VG=5,UNIT=2,D=1                                                 `R[20417]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`ISUB_N50_1_D5`:                ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20418]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IOFF_N50_1_D5`:                IDOFF       VD=1.1*5,UNIT=1,D=1,MODE=1                                           `R[20419]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`BVDS_N50_1_D5`:                BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20420]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`VTLIN_N50_D5_D5`:              VT          VD=0.1,IDTARG=1E-07*(0.5/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[11080]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`VTSAT_N50_D5_D5`:              VT          VD=1*5,IDTARG=1E-07*(0.5/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[11081]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`IDL_N50_D5_D5`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=0.5                                             `R[11082]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`IDS_N50_D5_D5`:                IDSAT       VD=5,VG=5,UNIT=2,D=0.5                                               `R[11083]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`ISUB_N50_D5_D5`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[11084]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`IOFF_N50_D5_D5`:               IDOFF       VD=1.1*5,UNIT=1,D=0.5,MODE=1                                         `R[11085]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`BVDS_N50_D5_D5`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[11086]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`VTLIN_N50_D3_D5`:              VT          VD=0.1,IDTARG=1E-07*(0.3/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[11087]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`VTSAT_N50_D3_D5`:              VT          VD=1*5,IDTARG=1E-07*(0.3/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[11088]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`IDL_N50_D3_D5`:                IDSAT       VD=0.1,VG=5,UNIT=2,D=0.3                                             `R[11089]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`IDS_N50_D3_D5`:                IDSAT       VD=5,VG=5,UNIT=2,D=0.3                                               `R[11090]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`ISUB_N50_D3_D5`:               ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[11091]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`IOFF_N50_D3_D5`:               IDOFF       VD=1.1*5,UNIT=1,D=0.3,MODE=1                                         `R[11092]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`BVDS_N50_D3_D5`:               BVDS        VDMAX=15,IDTARG=1E-06                                                `R[11093]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`VTLIN_N50_D22_D5`:             VT          VD=0.1,IDTARG=1E-07*(0.2/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[20393]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`VTSAT_N50_D22_D5`:             VT          VD=1*5,IDTARG=1E-07*(0.2/0.5),VGMIN=0.4,VGMAX=1.2,VGSTEP=0.002       `R[20394]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`IDL_N50_D22_D5`:               IDSAT       VD=0.1,VG=5,UNIT=2,D=0.2                                             `R[20395]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`IDS_N50_D22_D5`:               IDSAT       VD=5,VG=5,UNIT=2,D=0.2                                               `R[20396]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`ISUB_N50_D22_D5`:              ISUBMAX     VD=1.1*5,VGMIN=0.2*5,VGMAX=0.7*5,VGSTEP=0.005,UNIT=2                 `R[20397]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`IOFF_N50_D22_D5`:              IDOFF       VD=1.1*5,UNIT=1,D=0.2,MODE=1                                         `R[20398]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`BVDS_N50_D22_D5`:              BVDS        VDMAX=15,IDTARG=1E-06                                                `R[20399]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `MO03`::                                                                                                                                                                      
#`VTLIN_P50_10_D4`:              VT          VD=-0.1,IDTARG=-1E-07*(10/0.4),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20421]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTSAT_P50_10_D4`:              VT          VD=-1*5,IDTARG=-1E-07*(10/0.4),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20422]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IDL_P50_10_D4`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20423]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IDS_P50_10_D4`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20424]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`ISUB_P50_10_D4`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20425]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`IOFF_P50_10_D4`:               IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20426]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`BVDS_P50_10_D4`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20427]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTLIN_P50_10_D45`:             VT          VD=-0.1,IDTARG=-1E-07*(10/0.45),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[20428]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`VTSAT_P50_10_D45`:             VT          VD=-1*5,IDTARG=-1E-07*(10/0.45),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[20429]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IDL_P50_10_D45`:               IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20430]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IDS_P50_10_D45`:               IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20431]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`ISUB_P50_10_D45`:              ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20432]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IOFF_P50_10_D45`:              IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20433]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`BVDS_P50_10_D45`:              BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20434]`              Drain=4,Gate=1,Source=5,Bulk=22      
 `VTLIN_P50_10_D5`:              VT          VD=-0.1,IDTARG=-1E-07*(10/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20435]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`VTSAT_P50_10_D5`:              VT          VD=-1*5,IDTARG=-1E-07*(10/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20436]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IDL_P50_10_D5`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20437]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IDS_P50_10_D5`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20438]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`ISUB_P50_10_D5`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.05,UNIT=2               `R[20439]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IOFF_P50_10_D5`:               IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20440]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `BVDS_P50_10_D5`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20441]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`VTLIN_P50_10_D55`:             VT          VD=-0.1,IDTARG=-1E-07*(10/0.55),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[20442]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`VTSAT_P50_10_D55`:             VT          VD=-1*5,IDTARG=-1E-07*(10/0.55),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[20443]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IDL_P50_10_D55`:               IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20444]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IDS_P50_10_D55`:               IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20445]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`ISUB_P50_10_D55`:              ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.05,UNIT=2               `R[20446]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IOFF_P50_10_D55`:              IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20447]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`BVDS_P50_10_D55`:              BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20448]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`VTLIN_P50_10_D6`:              VT          VD=-0.1,IDTARG=-1E-07*(10/0.6),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20449]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`VTSAT_P50_10_D6`:              VT          VD=-1*5,IDTARG=-1E-07*(10/0.6),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20450]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IDL_P50_10_D6`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20451]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IDS_P50_10_D6`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20452]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`ISUB_P50_10_D6`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20453]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IOFF_P50_10_D6`:               IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20454]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`BVDS_P50_10_D6`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20455]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`VTLIN_P50_10_D7`:              VT          VD=-0.1,IDTARG=-1E-07*(10/0.7),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20456]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`VTSAT_P50_10_D7`:              VT          VD=-1*5,IDTARG=-1E-07*(10/0.7),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20457]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IDL_P50_10_D7`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20458]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IDS_P50_10_D7`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20459]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`ISUB_P50_10_D7`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20460]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IOFF_P50_10_D7`:               IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20461]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`BVDS_P50_10_D7`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20462]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`VTLIN_P50_10_D8`:              VT          VD=-0.1,IDTARG=-1E-07*(10/0.8),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20463]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`VTSAT_P50_10_D8`:              VT          VD=-1*5,IDTARG=-1E-07*(10/0.8),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20464]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IDL_P50_10_D8`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20465]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IDS_P50_10_D8`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20466]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`ISUB_P50_10_D8`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20467]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IOFF_P50_10_D8`:               IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20468]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`BVDS_P50_10_D8`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20469]`              Drain=14,Gate=1,Source=15,Bulk=22    
 `VTLIN_P50_10_1`:               VT          VD=-0.1,IDTARG=-1E-07*(10/1),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002      `R[20470]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`VTSAT_P50_10_1`:               VT          VD=-1*5,IDTARG=-1E-07*(10/1),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002      `R[20471]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`IDL_P50_10_1`:                 IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20472]`              Drain=16,Gate=1,Source=17,Bulk=22    
 `IDS_P50_10_1`:                 IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20473]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`ISUB_P50_10_1`:                ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20474]`              Drain=16,Gate=1,Source=17,Bulk=22    
 `IOFF_P50_10_1`:                IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20475]`              Drain=16,Gate=1,Source=17,Bulk=22    
 `BVDS_P50_10_1`:                BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20476]`              Drain=16,Gate=1,Source=17,Bulk=22    
 `VTLIN_P50_10_10`:              VT          VD=-0.1,IDTARG=-1E-07*(10/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[20477]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`VTSAT_P50_10_10`:              VT          VD=-1*5,IDTARG=-1E-07*(10/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[20478]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `IDL_P50_10_10`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=10                                            `R[20479]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `IDS_P50_10_10`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=10                                              `R[20480]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`ISUB_P50_10_10`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20481]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `IOFF_P50_10_10`:               IDOFF       VD=-1.1*5,UNIT=1,D=10,MODE=-1                                        `R[20482]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `BVDS_P50_10_10`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20483]`              Drain=18,Gate=1,Source=19,Bulk=22    
 `VTLIN_P50_1_10`:               VT          VD=-0.1,IDTARG=-1E-07*(1/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002      `R[20484]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`VTSAT_P50_1_10`:               VT          VD=-1*5,IDTARG=-1E-07*(1/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002      `R[20485]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `IDL_P50_1_10`:                 IDSAT       VD=-0.1,VG=-5,UNIT=2,D=1                                             `R[20486]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `IDS_P50_1_10`:                 IDSAT       VD=-5,VG=-5,UNIT=2,D=1                                               `R[20487]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`ISUB_P50_1_10`:                ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20488]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `IOFF_P50_1_10`:                IDOFF       VD=-1.1*5,UNIT=1,D=1,MODE=-1                                         `R[20489]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `BVDS_P50_1_10`:                BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20490]`              Drain=20,Gate=1,Source=21,Bulk=22    
 `MO04`::                                                                                                                                                                      
 `VTLIN_P50_D5_10`:              VT          VD=-0.1,IDTARG=-1E-07*(0.5/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20526]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTSAT_P50_D5_10`:              VT          VD=-1*5,IDTARG=-1E-07*(0.5/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20527]`              Drain=2,Gate=1,Source=3,Bulk=22      
 `IDL_P50_D5_10`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=0.5                                           `R[20528]`              Drain=2,Gate=1,Source=3,Bulk=22      
 `IDS_P50_D5_10`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=0.5                                             `R[20529]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`ISUB_P50_D5_10`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20530]`              Drain=2,Gate=1,Source=3,Bulk=22      
 `IOFF_P50_D5_10`:               IDOFF       VD=-1.1*5,UNIT=1,D=0.5,MODE=-1                                       `R[20531]`              Drain=2,Gate=1,Source=3,Bulk=22      
 `BVDS_P50_D5_10`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20532]`              Drain=2,Gate=1,Source=3,Bulk=22      
#`VTLIN_P50_D3_10`:              VT          VD=-0.1,IDTARG=-1E-07*(0.3/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20519]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`VTSAT_P50_D3_10`:              VT          VD=-1*5,IDTARG=-1E-07*(0.3/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20520]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IDL_P50_D3_10`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=0.3                                           `R[20521]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IDS_P50_D3_10`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=0.3                                             `R[20522]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`ISUB_P50_D3_10`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20523]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`IOFF_P50_D3_10`:               IDOFF       VD=-1.1*5,UNIT=1,D=0.3,MODE=-1                                       `R[20524]`              Drain=4,Gate=1,Source=5,Bulk=22      
#`BVDS_P50_D3_10`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20525]`              Drain=4,Gate=1,Source=5,Bulk=22      
 `VTLIN_P50_D22_10`:             VT          VD=-0.1,IDTARG=-1E-07*(0.22/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[20498]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`VTSAT_P50_D22_10`:             VT          VD=-1*5,IDTARG=-1E-07*(0.22/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[20499]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IDL_P50_D22_10`:               IDSAT       VD=-0.1,VG=-5,UNIT=2,D=0.22                                          `R[20500]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IDS_P50_D22_10`:               IDSAT       VD=-5,VG=-5,UNIT=2,D=0.22                                            `R[20501]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`ISUB_P50_D22_10`:              ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20502]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `IOFF_P50_D22_10`:              IDOFF       VD=-1.1*5,UNIT=1,D=0.22,MODE=-1                                      `R[20503]`              Drain=6,Gate=1,Source=7,Bulk=22      
 `BVDS_P50_D22_10`:              BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20504]`              Drain=6,Gate=1,Source=7,Bulk=22      
#`VTLIN_P50_D2_10`:              VT          VD=-0.1,IDTARG=-1E-07*(0.2/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20491]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`VTSAT_P50_D2_10`:              VT          VD=-1*5,IDTARG=-1E-07*(0.2/10),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002    `R[20492]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IDL_P50_D2_10`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=0.2                                           `R[20493]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IDS_P50_D2_10`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=0.2                                             `R[20494]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`ISUB_P50_D2_10`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20495]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`IOFF_P50_D2_10`:               IDOFF       VD=-1.1*5,UNIT=1,D=0.2,MODE=-1                                       `R[20496]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`BVDS_P50_D2_10`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20497]`              Drain=8,Gate=1,Source=9,Bulk=22      
#`VTLIN_P50_5_D5`:               VT          VD=-0.1,IDTARG=-1E-07*(5/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[11094]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`VTSAT_P50_5_D5`:               VT          VD=-1*5,IDTARG=-1E-07*(5/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[11095]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IDL_P50_5_D5`:                 IDSAT       VD=-0.1,VG=-5,UNIT=2,D=5                                             `R[11096]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IDS_P50_5_D5`:                 IDSAT       VD=-5,VG=-5,UNIT=2,D=5                                               `R[11097]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`ISUB_P50_5_D5`:                ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[11098]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`IOFF_P50_5_D5`:                IDOFF       VD=-1.1*5,UNIT=1,D=5,MODE=-1                                         `R[11099]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`BVDS_P50_5_D5`:                BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[11100]`              Drain=10,Gate=1,Source=11,Bulk=22    
#`VTLIN_P50_3_D5`:               VT          VD=-0.1,IDTARG=-1E-07*(3/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[11101]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`VTSAT_P50_3_D5`:               VT          VD=-1*5,IDTARG=-1E-07*(3/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[11102]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IDL_P50_3_D5`:                 IDSAT       VD=-0.1,VG=-5,UNIT=2,D=3                                             `R[11103]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IDS_P50_3_D5`:                 IDSAT       VD=-5,VG=-5,UNIT=2,D=3                                               `R[11104]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`ISUB_P50_3_D5`:                ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[11105]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`IOFF_P50_3_D5`:                IDOFF       VD=-1.1*5,UNIT=1,D=3,MODE=-1                                         `R[11106]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`BVDS_P50_3_D5`:                BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[11107]`              Drain=12,Gate=1,Source=13,Bulk=22    
#`VTLIN_P50_1_D5`:               VT          VD=-0.1,IDTARG=-1E-07*(1/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[20554]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`VTSAT_P50_1_D5`:               VT          VD=-1*5,IDTARG=-1E-07*(1/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002     `R[20555]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IDL_P50_1_D5`:                 IDSAT       VD=-0.1,VG=-5,UNIT=2,D=1                                             `R[20556]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IDS_P50_1_D5`:                 IDSAT       VD=-5,VG=-5,UNIT=2,D=1                                               `R[20557]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`ISUB_P50_1_D5`:                ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20558]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`IOFF_P50_1_D5`:                IDOFF       VD=-1.1*5,UNIT=1,D=1,MODE=-1                                         `R[20559]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`BVDS_P50_1_D5`:                BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20560]`              Drain=14,Gate=1,Source=15,Bulk=22    
#`VTLIN_P50_D5_D5`:              VT          VD=-0.1,IDTARG=-1E-07*(0.5/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[11108]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`VTSAT_P50_D5_D5`:              VT          VD=-1*5,IDTARG=-1E-07*(0.5/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[11109]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`IDL_P50_D5_D5`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=0.5                                           `R[11110]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`IDS_P50_D5_D5`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=0.5                                             `R[11111]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`ISUB_P50_D5_D5`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[11112]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`IOFF_P50_D5_D5`:               IDOFF       VD=-1.1*5,UNIT=1,D=0.5,MODE=-1                                       `R[11113]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`BVDS_P50_D5_D5`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[11114]`              Drain=16,Gate=1,Source=17,Bulk=22    
#`VTLIN_P50_D3_D5`:              VT          VD=-0.1,IDTARG=-1E-07*(0.3/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[11115]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`VTSAT_P50_D3_D5`:              VT          VD=-1*5,IDTARG=-1E-07*(0.3/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[11116]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`IDL_P50_D3_D5`:                IDSAT       VD=-0.1,VG=-5,UNIT=2,D=0.3                                           `R[11117]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`IDS_P50_D3_D5`:                IDSAT       VD=-5,VG=-5,UNIT=2,D=0.3                                             `R[11118]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`ISUB_P50_D3_D5`:               ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[11119]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`IOFF_P50_D3_D5`:               IDOFF       VD=-1.1*5,UNIT=1,D=0.3,MODE=-1                                       `R[10520]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`BVDS_P50_D3_D5`:               BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[10521]`              Drain=18,Gate=1,Source=19,Bulk=22    
#`VTLIN_P50_D22_D5`:             VT          VD=-0.1,IDTARG=-1E-07*(0.2/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[20533]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`VTSAT_P50_D22_D5`:             VT          VD=-1*5,IDTARG=-1E-07*(0.2/0.5),VGMIN=-0.4,VGMAX=-1.2,VGSTEP=0.002   `R[20534]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`IDL_P50_D22_D5`:               IDSAT       VD=-0.1,VG=-5,UNIT=2,D=0.2                                           `R[20535]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`IDS_P50_D22_D5`:               IDSAT       VD=-5,VG=-5,UNIT=2,D=0.2                                             `R[20536]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`ISUB_P50_D22_D5`:              ISUBMAX     VD=-1.1*5,VGMIN=-0.2*5,VGMAX=-0.7*5,VGSTEP=0.005,UNIT=2              `R[20537]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`IOFF_P50_D22_D5`:              IDOFF       VD=-1.1*5,UNIT=1,D=0.2,MODE=-1                                       `R[20538]`              Drain=20,Gate=1,Source=21,Bulk=22    
#`BVDS_P50_D22_D5`:              BVDS        VDMAX=-15,IDTARG=-1E-06                                              `R[20539]`              Drain=20,Gate=1,Source=21,Bulk=22    
                                                                                                                                                                               
 `MO09`::                                                                                                                                                                      
 `CA_ACC_GOXN5_40_80_PWH`:       CAP_TOX     VF=-5,AREA=40*80,Darea=40*80,SL=0.045                                `R[10809]`,`R10810`     H=1,L=2                              
 `TOX_ACC_GOXN5_40_80_PWH`:      DUMMY       Input=R10810*1000                                                    `R[10810]`                                                   
 `CA_INV_GOXN5_40_80_PWH`:       CAP_TOX     VF=5,AREA=40*80,Darea=40*80,SL=0.045                                 `R[10811]`,`R10812`     H=1,L=2                              
 `TOX_INV_GOXN5_40_80_PWH`:      DUMMY       Input=R10812*1000                                                    `R[10812]`                                                   
 `BV_GOXN5_40_80_PWH`:           BVOX        VGMIN=10,VGMAX=20,IGTARG=1E-06                                       `R[10813]`              Gate=1,Bulk=2                        
 `CA_ACC_GOXP5_W40_L80_NWH`:     CAP_TOX     VF=5,AREA=40*80,Darea=40*80,SL=0.045                                 `R[10814]`,`R10815`     H=3,L=4                              
 `TOX_ACC_GOXP5_W40_L80_NWH`:    DUMMY       Input=R10815*1000                                                    `R[10815]`                                                   
 `CA_INV_GOXP5_W40_L80_NWH`:     CAP_TOX     VF=-5,AREA=40*80,Darea=40*80,SL=0.045                                `R[10816]`,`R10817`     H=3,L=4                              
 `TOX_INV_GOXP5_W40_L80_NWH`:    DUMMY       Input=R10817*1000                                                    `R[10817]`                                                   
 `BV_GOXP5_W40_L80_NWH`:         BVOX        VGMIN=-10,VGMAX=-20,IGTARG=-1E-06                                    `R[10818]`              Gate=3,Bulk=4                        
 `CA_ACC_GOXN5_40_80_NWH`:       CAP_TOX     VF=-5,AREA=40*80,Darea=40*80,SL=0.045                                `R[10819]`,`R10820`     H=5,L=6                              
 `TOX_ACC_GOXN5_40_80_NWH`:      DUMMY       Input=R10820*1000                                                    `R[10820]`                                                   
 `CA_INV_GOXN5_40_80_NWH`:       CAP_TOX     VF=5,AREA=40*80,Darea=40*80,SL=0.045                                 `R[10821]`,`R10822`     H=5,L=6                              
 `TOX_INV_GOXN5_40_80_NWH`:      DUMMY       Input=R10822*1000                                                    `R[10822]`                                                   
 `BV_GOXN5_40_80_NWH`:           BVOX        VGMIN=10,VGMAX=20,IGTARG=1E-06                                       `R[10823]`              Gate=5,Bulk=6                        
 `RS_HPO_PWH_1_10`:              R2T_FV      FLG=1,SQR=10                                                         `R[10824]`              L=7,H=8                              
 `RS_HPO_PWH_1_20`:              R2T_FV      FLG=1,SQR=20                                                         `R[10825]`              L=9,H=10                             
 `RS_HPO_PWH_D42_84`:            R2T_FV      FLG=1,SQR=84/0.42                                                    `R[10826]`              L=11,H=12                            
#`RS_NPO_PWH_D3_69D4`:           R2T_FV      FLG=1,SQR=69.4/0.3                                                   `R[10827]`              L=13,H=14                            
 `RS_NPO_PWH_D42_84`:            R2T_FV      FLG=1,SQR=84/0.42                                                    `R[10828]`              L=15,H=16                            
 `RS_PPO_NWH_D42_84`:            R2T_FV      FLG=1,SQR=84/0.42                                                    `R[10829]`              L=17,H=18                            
 `RS_NAA_PWH_D42_84`:            R2T_FV      FLG=1,SQR=84/0.42                                                    `R[10830]`              L=19,H=20                            
 `RS_PAA_NWH_D42_84`:            R2T_FV      FLG=1,SQR=84/0.42                                                    `R[10831]`              L=21,H=22                            
                                                                                                                                                                               
 `HV01`::                                                                                                                                                                      
#`VTLIN_W10_LGD6_HV01_1`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10832]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IDL_W10_LGD6_HV01_1`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10833]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IDS_W10_LGD6_HV01_1`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10834]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IOFF_W10_LGD6_HV01_1`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10835]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`BV_W10_LGD6_HV01_1`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10836]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`VTLIN_W10_LGD7_HV01_2`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10837]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IDL_W10_LGD7_HV01_2`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10838]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IDS_W10_LGD7_HV01_2`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10839]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IOFF_W10_LGD7_HV01_2`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10840]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`BV_W10_LGD7_HV01_2`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10841]`              Drain=5,Gate=4,Source=6,Bulk=9       
 `VTLIN_W10_LGD8_HV01_3`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10842]`              Drain=8,Gate=7,Source=9,Bulk=9       
 `IDL_W10_LGD8_HV01_3`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10843]`              Drain=8,Gate=7,Source=9,Bulk=9       
 `IDS_W10_LGD8_HV01_3`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10844]`              Drain=8,Gate=7,Source=9,Bulk=9       
 `IOFF_W10_LGD8_HV01_3`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10845]`              Drain=8,Gate=7,Source=9,Bulk=9       
 `BV_W10_LGD8_HV01_3`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10846]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`VTLIN_W10_LGD9_HV01_4`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10847]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IDL_W10_LGD9_HV01_4`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10848]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IDS_W10_LGD9_HV01_4`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10849]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IOFF_W10_LGD9_HV01_4`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10850]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`BV_W10_LGD9_HV01_4`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10851]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`VTLIN_W10_LGD6_HV01_5`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10852]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IDL_W10_LGD6_HV01_5`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10853]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IDS_W10_LGD6_HV01_5`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10854]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IOFF_W10_LGD6_HV01_5`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10855]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`BV_W10_LGD6_HV01_5`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10856]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`VTLIN_W10_LGD7_HV01_6`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10857]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IDL_W10_LGD7_HV01_6`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10858]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IDS_W10_LGD7_HV01_6`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10859]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IOFF_W10_LGD7_HV01_6`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10860]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`BV_W10_LGD7_HV01_6`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10861]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`VTLIN_W10_LGD8_HV01_7`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10862]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IDL_W10_LGD8_HV01_7`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10863]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IDS_W10_LGD8_HV01_7`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10864]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IOFF_W10_LGD8_HV01_7`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10865]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`BV_W10_LGD8_HV01_7`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10866]`              Drain=20,Gate=19,Source=21,Bulk=22   
 `HV02`::                                                                                                                                                                      
#`VTLIN_W10_LGD7_HV02_1`:        VT          VD=-0.1,IDTARG=-1E-06,VGMIN=0,VGMAX=-5,VGSTEP=0.025                  `R[10867]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IDL_W10_LGD7_HV02_1`:          IDSAT       VD=-0.1,VG=-5,UNIT=2,D=20                                            `R[10868]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IDS_W10_LGD7_HV02_1`:          IDSAT       VD=-7,VG=-5,UNIT=2,D=20                                              `R[10869]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IOFF_W10_LGD7_HV02_1`:         IDOFF       VD=-1.1*7,UNIT=1,D=20                                                `R[10870]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`BV_W10_LGD7_HV02_1`:           BVDS        VDMAX=-25,IDTARG=-1E-06                                              `R[10871]`              Drain=2,Gate=1,Source=3,Bulk=4       
 `VTLIN_W10_LGD8_HV02_2`:        VT          VD=-0.1,IDTARG=-1E-06,VGMIN=0,VGMAX=-5,VGSTEP=0.025                  `R[10872]`              Drain=6,Gate=5,Source=7,Bulk=8       
 `IDL_W10_LGD8_HV02_2`:          IDSAT       VD=-0.1,VG=-5,UNIT=2,D=20                                            `R[10873]`              Drain=6,Gate=5,Source=7,Bulk=8       
 `IDS_W10_LGD8_HV02_2`:          IDSAT       VD=-7,VG=-5,UNIT=2,D=20                                              `R[10874]`              Drain=6,Gate=5,Source=7,Bulk=8       
 `IOFF_W10_LGD8_HV02_2`:         IDOFF       VD=-1.1*7,UNIT=1,D=20                                                `R[10875]`              Drain=6,Gate=5,Source=7,Bulk=8       
 `BV_W10_LGD8_HV02_2`:           BVDS        VDMAX=-25,IDTARG=-1E-06                                              `R[10876]`              Drain=6,Gate=5,Source=7,Bulk=8       
#`VTLIN_W10_LGD6_HV02_3`:        VT          VD=-0.1,IDTARG=-1E-06,VGMIN=0,VGMAX=-5,VGSTEP=0.025                  `R[10877]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`IDL_W10_LGD6_HV02_3`:          IDSAT       VD=-0.1,VG=-5,UNIT=2,D=20                                            `R[10878]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`IDS_W10_LGD6_HV02_3`:          IDSAT       VD=-7,VG=-5,UNIT=2,D=20                                              `R[10879]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`IOFF_W10_LGD6_HV02_3`:         IDOFF       VD=-1.1*7,UNIT=1,D=20                                                `R[10880]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`BV_W10_LGD6_HV02_3`:           BVDS        VDMAX=-25,IDTARG=-1E-06                                              `R[10881]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`VTLIN_W10_LG1D55_HV02_4`:      VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10882]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`IDL_W10_LG1D55_HV02_4`:        IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10883]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`IDS_W10_LG1D55_HV02_4`:        IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10884]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`IOFF_W10_LG1D55_HV02_4`:       IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10885]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`BV_W10_LG1D55_HV02_4`:         BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10886]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`VTLIN_W10_LG1D55_HV02_5`:      VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10887]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`IDL_W10_LG1D55_HV02_5`:        IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10888]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`IDS_W10_LG1D55_HV02_5`:        IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10889]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`IOFF_W10_LG1D55_HV02_5`:       IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10890]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`BV_W10_LG1D55_HV02_5`:         BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10891]`              Drain=18,Gate=17,Source=19,Bulk=20   
 `HV03`::                                                                                                                                                                      
 `VTLIN_W10_LG1D5_HV03_1`:       VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10892]`              Drain=2,Gate=1,Source=3,Bulk=4       
 `IDL_W10_LG1D5_HV03_1`:         IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10893]`              Drain=2,Gate=1,Source=3,Bulk=4       
 `IDS_W10_LG1D5_HV03_1`:         IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10894]`              Drain=2,Gate=1,Source=3,Bulk=4       
 `IOFF_W10_LG1D5_HV03_1`:        IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10895]`              Drain=2,Gate=1,Source=3,Bulk=4       
 `BV_W10_LG1D5_HV03_1`:          BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10896]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`VTLIN_W10_LG1D5_HV03_2`:       VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10897]`              Drain=6,Gate=5,Source=7,Bulk=8       
#`IDL_W10_LG1D5_HV03_2`:         IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10898]`              Drain=6,Gate=5,Source=7,Bulk=8       
#`IDS_W10_LG1D5_HV03_2`:         IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10899]`              Drain=6,Gate=5,Source=7,Bulk=8       
#`IOFF_W10_LG1D5_HV03_2`:        IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10900]`              Drain=6,Gate=5,Source=7,Bulk=8       
#`BV_W10_LG1D5_HV03_2`:          BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10901]`              Drain=6,Gate=5,Source=7,Bulk=8       
#`VTLIN_W10_LG1D5_HV03_3`:       VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10902]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`IDL_W10_LG1D5_HV03_3`:         IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10903]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`IDS_W10_LG1D5_HV03_3`:         IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10904]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`IOFF_W10_LG1D5_HV03_3`:        IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10905]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`BV_W10_LG1D5_HV03_3`:          BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10906]`              Drain=10,Gate=9,Source=11,Bulk=12    
#`VTLIN_W10_LG1D5_HV03_4`:       VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10907]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`IDL_W10_LG1D5_HV03_4`:         IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10908]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`IDS_W10_LG1D5_HV03_4`:         IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10909]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`IOFF_W10_LG1D5_HV03_4`:        IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10910]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`BV_W10_LG1D5_HV03_4`:          BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10911]`              Drain=14,Gate=13,Source=15,Bulk=16   
#`VTLIN_W10_LG1D4_HV03_5`:       VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10912]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`IDL_W10_LG1D4_HV03_5`:         IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10913]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`IDS_W10_LG1D4_HV03_5`:         IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10914]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`IOFF_W10_LG1D4_HV03_5`:        IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10915]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`BV_W10_LG1D4_HV03_5`:          BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10916]`              Drain=18,Gate=17,Source=19,Bulk=20   
#`HV04`::                                                                                                                                                                      
#`VTLIN_W10_LGD8_HV04_1`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10917]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IDL_W10_LGD8_HV04_1`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10918]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IDS_W10_LGD8_HV04_1`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10919]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IOFF_W10_LGD8_HV04_1`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10920]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`BV_W10_LGD8_HV04_1`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10921]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`VTLIN_W10_LGD8_HV04_2`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10922]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IDL_W10_LGD8_HV04_2`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10923]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IDS_W10_LGD8_HV04_2`:          IDSAT       VD=7,VG=5,UNIT=2,D=20                                                `R[10924]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IOFF_W10_LGD8_HV04_2`:         IDOFF       VD=1.1*7,UNIT=1,D=20                                                 `R[10925]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`BV_W10_LGD8_HV04_2`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10926]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`VTLIN_W10_LGD8_HV04_3`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10927]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`IDL_W10_LGD8_HV04_3`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10928]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`IDS_W10_LGD8_HV04_3`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10929]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`IOFF_W10_LGD8_HV04_3`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10930]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`BV_W10_LGD8_HV04_3`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10931]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`VTLIN_W10_LGD8_HV04_4`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10932]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IDL_W10_LGD8_HV04_4`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10933]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IDS_W10_LGD8_HV04_4`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10934]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IOFF_W10_LGD8_HV04_4`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10935]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`BV_W10_LGD8_HV04_4`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10936]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`VTLIN_W10_LGD8_HV04_5`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10937]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IDL_W10_LGD8_HV04_5`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10938]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IDS_W10_LGD8_HV04_5`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10939]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IOFF_W10_LGD8_HV04_5`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10940]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`BV_W10_LGD8_HV04_5`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10941]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`VTLIN_W10_LGD8_HV04_6`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10942]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IDL_W10_LGD8_HV04_6`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10943]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IDS_W10_LGD8_HV04_6`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10944]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IOFF_W10_LGD8_HV04_6`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10945]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`BV_W10_LGD8_HV04_6`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10946]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`VTLIN_W10_LGD8_HV04_7`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10947]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IDL_W10_LGD8_HV04_7`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10948]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IDS_W10_LGD8_HV04_7`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10949]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IOFF_W10_LGD8_HV04_7`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10950]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`BV_W10_LGD8_HV04_7`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10951]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`HV05`::                                                                                                                                                                      
#`VTLIN_W10_LGD8_HV05_1`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10952]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IDL_W10_LGD8_HV05_1`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10953]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IDS_W10_LGD8_HV05_1`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10954]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`IOFF_W10_LGD8_HV05_1`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10955]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`BV_W10_LGD8_HV05_1`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10956]`              Drain=2,Gate=1,Source=3,Bulk=4       
#`VTLIN_W10_LGD8_HV05_2`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10957]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IDL_W10_LGD8_HV05_2`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10958]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IDS_W10_LGD8_HV05_2`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10959]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`IOFF_W10_LGD8_HV05_2`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10960]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`BV_W10_LGD8_HV05_2`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10961]`              Drain=5,Gate=4,Source=6,Bulk=9       
#`VTLIN_W10_LGD8_HV05_3`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10962]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`IDL_W10_LGD8_HV05_3`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10963]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`IDS_W10_LGD8_HV05_3`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10964]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`IOFF_W10_LGD8_HV05_3`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10965]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`BV_W10_LGD8_HV05_3`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10966]`              Drain=8,Gate=7,Source=9,Bulk=9       
#`VTLIN_W10_LGD8_HV05_4`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10967]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IDL_W10_LGD8_HV05_4`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10968]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IDS_W10_LGD8_HV05_4`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10969]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`IOFF_W10_LGD8_HV05_4`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10970]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`BV_W10_LGD8_HV05_4`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10971]`              Drain=11,Gate=10,Source=12,Bulk=12   
#`VTLIN_W10_LGD8_HV05_5`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10972]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IDL_W10_LGD8_HV05_5`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10973]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IDS_W10_LGD8_HV05_5`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10974]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`IOFF_W10_LGD8_HV05_5`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10975]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`BV_W10_LGD8_HV05_5`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10976]`              Drain=14,Gate=13,Source=15,Bulk=22   
#`VTLIN_W10_LGD8_HV05_6`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10977]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IDL_W10_LGD8_HV05_6`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10978]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IDS_W10_LGD8_HV05_6`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10979]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`IOFF_W10_LGD8_HV05_6`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10980]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`BV_W10_LGD8_HV05_6`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10981]`              Drain=17,Gate=16,Source=18,Bulk=22   
#`VTLIN_W10_LGD8_HV05_7`:        VT          VD=0.1,IDTARG=1E-06,VGMIN=0,VGMAX=5,VGSTEP=0.025                     `R[10982]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IDL_W10_LGD8_HV05_7`:          IDSAT       VD=0.1,VG=5,UNIT=2,D=20                                              `R[10983]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IDS_W10_LGD8_HV05_7`:          IDSAT       VD=12,VG=5,UNIT=2,D=20                                               `R[10984]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`IOFF_W10_LGD8_HV05_7`:         IDOFF       VD=1.1*12,UNIT=1,D=20                                                `R[10985]`              Drain=20,Gate=19,Source=21,Bulk=22   
#`BV_W10_LGD8_HV05_7`:           BVDS        VDMAX=25,IDTARG=1E-06                                                `R[10986]`              Drain=20,Gate=19,Source=21,Bulk=22   
 `DI01`::                                                                                                                                                                      
#`Vbe_VNPN_E10_DI01_1`:          BETAPNP     VCE=5,UNIT=2,IE=1E-7*(10*10),VELIMIT=-2                              ,,`R[10989]`,`R[10987]` B=2,C=3,E=1                          
 `Vbe_VNPN_E10_DI01_1`:          BVOX        VGMAX=-2,VGSTEP=0.05,IGTARG=-1E-05                                   `R10987`                Gate=1,Bulk=2                        
 `10987`:                        ABS         A=R10987                                                             `R[10987]`                                                   
 `VA_VNPN_E10_DI01_1`:           VAPNP       VC1=1,VC2=2,IB=1E-7*(10*10),VBLIM=2                                  ,,`R[10988]`            B=2,C=3,E=1                          
 `HFE_VNPN_E10_DI01_1`:          BETAPNP     VCE=5,UNIT=2,IE=1E-7*(10*10),VELIMIT=2                               ,,`R[10989]`            B=2,C=3,E=1                          
#`R010995`:                      FISV        VHCOMP=100                                                           `R10995`                H=3,L=1                              
 `BVCEO_VNPN_E10_DI01_1`:        BVOX        VGMAX=-25,IGTARG=-1E-05                                              `R10995`                Gate=1,Bulk=3                        
 `10995`:                        ABS         A=R10995                                                             `R[10995]`                                                   
#`R010996`:                      FISV        VHCOMP=100                                                           `R10996`                H=1,L=2                              
 `BVEBO_VNPN_E10_DI01_1`:        BVOX        VGMAX=-25,IGTARG=-1E-05                                              `R10996`                Gate=2,Bulk=1                        
 `10996`:                        ABS         A=R10996                                                             `R[10996]`                                                   
 `Vbe_VPNP_E10_DI01_2`:          BVOX        VGMAX=-2,VGSTEP=0.05,IGTARG=-1E-05                                   `R[10997]`              Gate=5,Bulk=4                        
 `VA_VPNP_E10_DI01_2`:           VAPNP       VC1=-1,VC2=-2,IB=-1E-7*(10*10),VBLIM=-2                              ,,`R[10998]`            B=5,C=6,E=4                          
 `HFE_VPNP_E10_DI01_2`:          BETAPNP     UNIT=2,IE=-1E-7*(10*10),VELIMIT=2                                    ,,`R[10999]`            B=5,C=6,E=4                          
#`R011005`:                      FISV        IH=-1E-06,VHCOMP=-100                                                `R11005`                H=6,L=4                              
 `BVCEO_VPNP_E10_DI01_2`:        BVOX        VGMAX=-25,IGTARG=-1E-05                                              `R[11005]`              Gate=6,Bulk=4                        
#`R011006`:                      FISV        IH=-1E-06,VHCOMP=-100                                                `R11006`                H=4,L=5                              
 `BVEBO_VPNP_E10_DI01_2`:        BVOX        VGMAX=-25,IGTARG=-1E-05                                              `R[11006]`              Gate=4,Bulk=5                        
 `BV_L10_W10_5NP_1_DI01_3`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11007]`              Gate=7,Bulk=8                        
 `BV_L10_W10_5NP_1_DI01_4`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11008]`              Gate=9,Bulk=10                       
 `BV_L10_W10_5NP_1_DI01_5`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11009]`              Gate=11,Bulk=12                      
#`BV_L10_W10_5NP_1_DI01_6`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11010]`              Gate=13,Bulk=14                      
#`BV_L10_W10_5NP_1_DI01_7`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11011]`              Gate=15,Bulk=16                      
#`BV_L10_W10_5NP_1_DI01_8`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11012]`              Gate=17,Bulk=18                      
#`BV_L10_W10_5NP_1_DI01_9`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11013]`              Gate=19,Bulk=20                      
                                                                                                                                                                               
                                                                                                                                                                               
 `DI02`::                                                                                                                                                                      
#`BV1_L5_W5_5NN_1_DI02_1`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11014]`              Gate=1,Bulk=21                       
#`BV2_L5_W5_5NN_1_DI02_1`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11015]`              Gate=1,Drain=2,Source=21,Bulk=22     
#`BV1_L5_W5_5NN_1_DI02_2`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11016]`              Gate=3,Bulk=21                       
#`BV2_L5_W5_5NN_1_DI02_2`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11017]`              Gate=3,Drain=4,Source=21,Bulk=22     
 `BV1_L5_W5_5NN_1_DI02_3`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11018]`              Gate=5,Bulk=21                       
#`BV2_L5_W5_5NN_1_DI02_3`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11019]`              Gate=5,Drain=6,Source=21,Bulk=22     
#`BV1_L5_W5_5NN_1_DI02_4`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11020]`              Gate=7,Bulk=21                       
#`BV2_L5_W5_5NN_1_DI02_4`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11021]`              Gate=7,Drain=8,Source=21,Bulk=22     
#`BV1_L5_W5_5NN_1_DI02_5`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11022]`              Gate=9,Bulk=21                       
#`BV2_L5_W5_5NN_1_DI02_5`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11023]`              Gate=9,Drain=10,Source=21,Bulk=22    
#`BV1_L5_W5_5NN_1_DI02_6`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11024]`              Gate=11,Bulk=21                      
#`BV2_L5_W5_5NN_1_DI02_6`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11025]`              Gate=11,Drain=12,Source=21,Bulk=22   
#`BV1_L5_W5_5NN_1_DI02_7`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11026]`              Gate=13,Bulk=21                      
#`BV2_L5_W5_5NN_1_DI02_7`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11027]`              Gate=13,Drain=14,Source=21,Bulk=22   
#`BV1_L5_W5_5NN_1_DI02_8`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11028]`              Gate=15,Bulk=21                      
#`BV2_L5_W5_5NN_1_DI02_8`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11029]`              Gate=15,Drain=16,Source=21,Bulk=22   
#`BV1_L5_W5_5NN_1_DI02_9`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11030]`              Gate=17,Bulk=21                      
#`BV2_L5_W5_5NN_1_DI02_9`:       BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11031]`              Gate=17,Drain=18,Source=21,Bulk=22   
#`BV1_L5_W5_5NN_1_DI02_10`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11032]`              Gate=19,Bulk=21                      
#`BV2_L5_W5_5NN_1_DI02_10`:      BVOX        VGMAX=60,VGSTEP=0.5,IGTARG=1E-06                                     `R[11033]`              Gate=19,Drain=20,Source=21,Bulk=22   
                                                                                                                                                                               
 `RE01`::                                                                                                                                                                      
 `RCKV_V1_SD26`:                 R4T         IFORCE=0.0001,FLG=1                                                  `R[380447]`             FH=20,FL=21,SH=19,SL=22              
 `RE03`::                                                                                                                                                                      
 `RCFI_NDF_SD22`:                R2T_FI      FLG=1                                                                `R380448`               H=16,L=18                            
 `R[380448]`:                    DUMMY       Input=(R380448-3.71*R160003)/4                                       `R[380448]`                                                  
                                                                                                                                                                               
 `RE06`::                                                                                                                                                                      
 `RCKV_VT_SD36`:                 R4T         IFORCE=0.0001,FLG=1                                                  `R[380449]`             FH=20,FL=21,SH=19,SL=22              
$------------------------------- ----------- -------------------------------------------------------------------- ----------------------- ----------------------------------- -

