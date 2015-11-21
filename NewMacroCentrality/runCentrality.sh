#!/bin/bash
#To run the centrality calibration and plotting!

#----Variable Definition and Replacement
echo -n "Please enter version type ie v0 can be nominal: "
read ResType

#r is the amount offline cent. to overlap, ie  1% of 200 = 2, 
#These overlaps are per boundary left/right side so 1 is 2 overall width of overlap. 
echo -n "Please enter offline cent. overlaps in ie nominal format {0,0,0,0,0,0,0,0,0,0}: "
read r 
sed -i -e 's/const int deltaC.*;/const int deltaC[10] = '${r}';/g' centralityCommon.h

#m , 0=Data, 1=MC
echo -n "Input type of sample 1 for MC, 0 for RD: "
read m
sed -i -e 's/int isMC = .*;/int isMC = '${m}';/g' centralityCommon.h

#--check directory
if [ ! -d Plots ]; then
	mkdir Plots
fi


#-----MC or Data files
if [ $m = 1 ]; then
	Type=(MC)
	InputType=(${Type}_${ResType})
	InputHiForest=("root://cms-xrd-global.cern.ch///store/group/phys_heavyions/chflores/Foresting_RunPrep2015/HydjetMB5020_750_75X_mcRun2_HeavyIon_v1_RealisticHICollisions2011_STARTHI50_mc_L1_HLT_HIFOREST_skim2.root")
else
	Type=(RD)
	InputType=(${Type}_${ResType})
	InputHiForest=("root://cms-xrd-global.cern.ch///store/group/phys_heavyions/chflores/Foresting_RunPrep2015/HIMinBiasUPC_HIForest_all.root")
fi

#----Compiling and running code
	g++ centralityCalibration_${Type}.C $(root-config --cflags --libs) -Werror -Wall -Wextra -O2 -o centralityCalibration_${Type}.exe || exit 1
	g++ plotCentrality.C $(root-config --cflags --libs) -Werror -Wall -Wextra -O2 -o plotCentrality.exe || exit 1

	for cases in 0
	do
	  OutputFile="${InputType[cases]}_CentralityCalibration.root"
	  ./centralityCalibration_${Type}.exe "${InputHiForest[cases]}" "$OutputFile" || exit 1
	  ./plotCentrality.exe "${InputType[cases]}" || exit 1
	done
