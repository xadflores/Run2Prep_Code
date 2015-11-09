#!/bin/bash
#To run the centrality calibration and plotting!

#----Variable Definition and Replacement
#r is the amount offline cent. to overlap, ie  1% of 200 = 2
#r={0,0,0,0,0,0,0,0,0,0} 
r={0,0,0,0,0,2,2,2,2,2} 
sed -i -e 's/const int deltaC.*;/const int deltaC[10] = '${r}';/g' centralityCommon.h

#m , 0=Data, 1=MC
m=0
sed -i -e 's/int isMC = .*;/int isMC = '${m}';/g' centralityCommon.h

#mkdir Plots #uncomment if you don't have this directory

#-----MC or Data files
if [ $m = 1 ]; then
	Type=(MC)
	InputType=(${Type})
	InputHiForest=("root://cms-xrd-global.cern.ch///store/group/phys_heavyions/chflores/HydjetMB5020_750_75X_mcRun2_HeavyIon_v1_RealisticHICollisions2011_STARTHI50_mc_L1_HLT_HIFOREST_skim2.root")
else
	Type=(RD)
	InputType=(${Type})
	InputHiForest=("root://cms-xrd-global.cern.ch///store/group/phys_heavyions/chflores/HIMinBiasUPC_HIForest_all.root")
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
