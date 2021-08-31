#!usr/bin/python
import ROOT
from ROOT import TMath, TFile, TH1, TH1F, TCanvas, TEfficiency, TGraphAsymmErrors, TF1, TPaveText, TPaveStats, TLegend, TLine, gROOT, gPad, gStyle
#from officialstyle import *
import CMS_lumi, tdrstyle
from array import array


#officialStyle(gStyle)
tdrstyle.setTDRStyle()


#traditional = HistStyle(markerColor=4, markerStyle=24)
#pf = HistStyle(markerColor=2, markerStyle=20)

import optparse
usage = "usage: %prog [options]"
parser = optparse.OptionParser(usage)
# parser.add_option("--lumi"  ,action="store",type="string",dest="lumi",default='1.00')
# parser.add_option("--year"  ,action="store",type="string",dest="year",default='2016')
# parser.add_option("--file1"  ,action="store",type="string",dest="file1",default='16B_500.root')
# parser.add_option("--file2"  ,action="store",type="string",dest="file2",default='16B_900.root')
# parser.add_option("--leg1"  ,action="store",type="string",dest="leg1",default='HLT_PFJet500')
# parser.add_option("--leg2"  ,action="store",type="string",dest="leg2",default='HLT_PFHT900')

(options, args) = parser.parse_args()

#var = options.var

CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Preliminary"
#CMS_lumi.lumi_sqrtS = " fb^{-1}("+options.year+", 13 TeV)"
CMS_lumi.lumi_sqrtS = ""
    




canPt = TCanvas('EffVsPt_'+'_offline','EffVsPt_'+'_offline',600,600)
#f = TH1F('f','f',30,0,1500)
f = TH1F('f','f',50,0,800)
f.GetYaxis().SetRangeUser(0.0,1.2)
f.GetXaxis().SetTitle('Offline PFJet pT (GeV)')
f.GetYaxis().SetTitle('Efficiency')
f.Draw()


inf = TFile.Open("16BCDEF_500.root")
h_all_clone = inf.Get("h_all_clone")
h_all_clone.SetMarkerStyle(8)
h_all_clone.SetMarkerColor(1)
h_all_clone.SetLineColor(1)
h_all_clone.Draw("samePE1")

#inf.Close()

inf2 = TFile("17BCD_500.root")
h_all_clone_2 = inf2.Get("h_all_clone")
h_all_clone_2.SetMarkerStyle(8)
h_all_clone_2.SetMarkerColor(2)
h_all_clone_2.SetLineColor(2)
h_all_clone_2.Draw("samePE1")


inf3 = TFile("18AB_500.root")
h_all_clone_3 = inf3.Get("h_all_clone")
h_all_clone_3.SetMarkerStyle(8)
h_all_clone_3.SetMarkerColor(3)
h_all_clone_3.SetLineColor(3)
h_all_clone_3.Draw("samePE1")


leg = TLegend(0.76,0.15,0.96,0.38)
leg.SetBorderSize(0)
leg.AddEntry(h_all_clone,"HLT_PFJet500 (2016)",'P')
leg.AddEntry(h_all_clone_2,"HLT_PFJet500 (2017)",'P')
leg.AddEntry(h_all_clone_3,"HLT_PFJet500 (2018)",'P')
leg.Draw()




iPeriod = 0

iPos = 11
if( iPos==0 ): CMS_lumi.relPosX = 0.12

CMS_lumi.CMS_lumi(canPt, iPeriod, iPos)

gPad.Update()

canPt.Print("500.png")

'''
16B 5.82
16C: 2.61
16D: 4.29
E 4.07
F 3.14
G 7.65
H 8.70

17B 4.79
C 4.78
D 4.25
E 9.31
F13.54

18A 14.03
B 7.06
C 6.89
D 31.30


HLT_PFHT900
HLT_PFJet500
'''
