count="1960"

g++ -g -Wno-deprecated plot_eff_condor.C -o dummy.exe -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs`
[ -d output ] || mkdir output
[ -d error ] || mkdir error
[ -d log ] || mkdir log

while [ ${count} -lt  3001 ] 
do

cat>Job_${count}.sh<<EOF
#!/bin/bash
export SCRAM_ARCH=slc6_amd64_gcc630
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/cern.ch/user/d/dvats/CMSSW_11_2_0_Patatrack/src/
cmsenv
cd -

./dummy.exe HLT_PFJet500 /eos/home-d/dvats/jet_eff_plots_area/CMSSW_10_2_22/src/JMETriggerAnalysis/NTuplizers/test/crab/18A_ntuples/SingleMuon_18A_${count}.root /eos/home-d/dvats/Run2_JetEff_root_files/for_my_ntuples_2/18A/500/histo_${count}.root
EOF

chmod 755 Job_${count}.sh

cat>condor_${count}<<EOF
universe = vanilla
Executable = Job_${count}.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
transfer_input_files = dummy.exe, Job_${count}.sh
notification = never
Output = output/job_${count}.out
Error = error/job_${count}.error
Log = log/job_${count}.log
+JobFlavour = espresso
getenv = True
Queue 1

EOF

condor_submit condor_${count}

count=$[$count+1]
done

exit 0
