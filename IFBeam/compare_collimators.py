import ROOT as RT
import matplotlib.pyplot as plt
import numpy as np
RT.gROOT.SetBatch()
RT.gStyle.SetOptStat(000000)
from argparse import ArgumentParser as ap


def tof(args):
  hs = []
  c = RT.TCanvas('c1', '')
  c.SetTicks()
  colors = [RT.kBlue, RT.kBlack, RT.kRed]
  titles = ['10mm', '20mm', '30mm']
  leg = RT.TLegend(.4, .67, .85, .85)
  fracs = []
  for i in range(3):
    f = RT.TFile.Open(args.i[i], 'open')
    print('Opened', args.i[i])

    t = f.Get('DumpBL_XBTF_Unique')

    t.Draw(f'TF>>h{i}(80, 140, 220)')
    if args.cut is not None:
      fracs.append(1.*t.GetEntries(f'TF < {args.cut}')/t.GetEntries())

    h = RT.gDirectory.Get(f'h{i}')
    hs.append(h)
    h.SetDirectory(0)

  for i in range(3):
    h = hs[i]
    h.SetTitle(';Time of Flight + #delta [ns];Count [a.u.]')
    h.SetBinContent(1, h.GetBinContent(0))
    h.SetBinContent(0, 0.)
    h.SetBinContent(h.GetNbinsX(), h.GetBinContent(h.GetNbinsX()+1))
    h.SetBinContent(h.GetNbinsX()+1, 0.)
    h.SetLineColor(colors[i])
    h.Scale(1./h.GetMaximum())
    h.SetMinimum(0.)
    title = f'{titles[i]}'
    if args.cut is not None: title += f' (< {args.cut:.0f}ns: {fracs[i]*100:.2f}%)'
    leg.AddEntry(h, title, 'l')
    h.SetLineWidth(2)
    h.Draw('hist' if i == 0 else 'same hist')
    c.Update()
    h.SetStats(0)
    f.Close()

  fout = RT.TFile(args.o, 'recreate')
  leg.SetFillStyle(0)
  leg.SetLineWidth(0)
  leg.Draw()
  c.RedrawAxis()
  c.Write()
  c.SaveAs(args.o.replace('root', 'pdf'))
  c.SaveAs(args.o.replace('root', 'png'))
  fout.Close()


def triggers(args):

  means = []
  stds = []
  for i in range(3):
    f = RT.TFile.Open(args.i[i], 'open')
    t = f.Get('DumpBI_XBTF')
    t.Draw("NTimestampCount>>h", "DetName == \"GeneralTrigger\" && NTimestampCount > 0 ")
    h = RT.gDirectory.Get('h')
    means.append(h.GetMean())
    stds.append(h.GetStdDev())
    f.Close()

  x=[1,2,3]
  plt.errorbar([1,2,3], means, yerr=stds, fmt='o')
  plt.xticks(x, ['10', '20', '30'])
  plt.xlabel('Aperture [mm]')
  plt.ylabel('Triggers per spill')
  plt.savefig(args.o)


def momentum(args):
  hs = []
  c = RT.TCanvas('c1', '')
  colors = [RT.kBlue, RT.kBlack, RT.kRed]
  titles = ['10mm', '20mm', '30mm']
  leg = RT.TLegend()
  for i in range(3):
    f = RT.TFile.Open(args.i[i], 'open')
    hs.append(f.Get('PROF/h_Momentum_UNIQ'))
    hs[-1].SetDirectory(0)
    f.Close()
    hs[-1].Rebin(args.rebin)

    hs[-1].Fit('gaus', '0')
    g = hs[-1].GetFunction('gaus')
    mean = g.GetParameter(1)
    stddev = g.GetParameter(2)
    bite = stddev/mean

    hs[-1].Scale(1./hs[-1].GetMaximum())
    hs[-1].GetXaxis().SetRangeUser(*(args.range))
    hs[-1].SetLineColor(colors[i])
    title = f'{titles[i]} p={mean:.2f}, #Deltap/p={bite*100.:.2f}%'
    leg.AddEntry(hs[-1], title, 'l')
    hs[-1].SetLineWidth(2)
    hs[-1].Draw('hist' if i == 0 else 'same hist')
    c.Update()
    hs[-1].SetStats(0)

  fout = RT.TFile(args.o, 'recreate')
  leg.SetFillStyle(0)
  leg.SetLineWidth(0)
  leg.Draw()
  c.RedrawAxis()
  c.Write()
  c.SaveAs(args.o.replace('root', 'pdf'))
  c.SaveAs(args.o.replace('root', 'png'))
  fout.Close()

if __name__ == '__main__':
  parser = ap()
  parser.add_argument('-i', type=str, required=True, nargs=3)
  parser.add_argument('-o', type=str, default='collimators.root')
  parser.add_argument('--range', type=float, nargs=2, default=[0.75, 1.25])
  parser.add_argument('--rebin', type=int, default=2)
  parser.add_argument('--cut', type=float, default=None)
  parser.add_argument('--routine', default='momentum',
                      choices=['momentum', 'triggers', 'tof'])

  args = parser.parse_args()
  routines = {
    'momentum':momentum,
    'triggers':triggers,
    'tof':tof,
  }

  routines[args.routine](args)
