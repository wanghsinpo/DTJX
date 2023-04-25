#Test	FA300_A	1	04/02/2009	00:00:00	root	Test spec for SPECS-FA demonstration

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

