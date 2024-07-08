import ROOT as RT
from struct import pack, unpack
from array import array
from urllib.parse import quote
import csv
import requests
import yaml
from argparse import ArgumentParser as ap

base_url = 'https://dbdata3vm.fnal.gov:9443/ifbeam/data/data?e=z,pdune&v='
device = 'dip/acc/SPS/Timing/Cycle/StartExtractionEvent:cycleStamp[]'
#time_period = '&t0=-1h&t1=now'

ending = '&f=csv&tz=&action=Show+device'

xbtf_device_base='dip/acc/NORTH/NP04/BI/XTOF/' #XBTF022702:coarse[]
xbpf_device_base='dip/acc/NORTH/NP04/BI/XBPF/' 
xbtf_vars = [
  'coarse[]',
  'frac[]',
  'seconds[]',
  'timestampCount',
]

def get_current(ts, currents):
  found = False

  if ts > currents[-1][0]:
    found = True
    current = currents[-1][1]
    the_ts = currents[-1][0]

  elif ts > currents[0][0]:
    for i in range(1, len(currents)):
      if ts > currents[i-1][0] and ts < currents[i][0]:
        found = True
        current = currents[i-1][1]
        the_ts = currents[i-1][0]
        break
  else:
    print(f'Warning. Using earliest timestamp ({currents[0][0]}) for requested ts {ts}')
    current = currents[0][1]
    the_ts = currents[0][0]



  #if found:
  #  pass
  #  #print(f'Found latest timestamp ({the_ts}) before {ts}')
  #if not found:
  #  raise Exception('Could not find matching timestamp for', ts, 'Earliest is', currents[0][0])
  return current

def get_results(url):
  response = requests.get(url)
  if not response.ok: raise Exception('Response not ok for url\n',url)
  content = response.content.decode('utf-8')
  csv_reader = csv.reader(content.splitlines(), delimiter=',')
  results = [line for line in list(csv_reader) if line[0]!='Event']
  return results

def make_time_period(t0, t1):
  return f'&t0={t0}&t1={t1}'

def parse_xbpf_events_data(data, currents, xbpf):
  #output.timestamp[0] = float(data[2])
  xbpf.timestamp = float(data[2])

  ts_for_current = int(data[2])
  xbpf.current = get_current(ts_for_current, currents)
  #output.current[0] = get_current(ts_for_current, currents)

  for i in range(4, len(data), 10):
    #print(data[i:i+10])
    if len(set(data[i:i+10])) == 1: break
    (tts_lsb, tts_msb, ets_lsb, ets_msb, f0, f1, f2, f3, f4, f5) = data[i:i+10]
    #output.tts_lsb.push_back(int(float(tts_lsb)))
    #output.tts_msb.push_back(int(float(tts_msb)))
    #output.ets_lsb.push_back(int(float(ets_lsb)))
    #output.ets_msb.push_back(int(float(ets_msb)))
    #output.f0.push_back(unpack('I', pack('f', float(f0)))[0])
    #output.f1.push_back(unpack('I', pack('f', float(f1)))[0])
    #output.f2.push_back(unpack('I', pack('f', float(f2)))[0])
    #output.f3.push_back(unpack('I', pack('f', float(f3)))[0])
    #output.f4.push_back(unpack('I', pack('f', float(f4)))[0])
    #output.f5.push_back(unpack('I', pack('f', float(f5)))[0])
    xbpf.tts_lsb.append(int(float(tts_lsb)))
    xbpf.tts_msb.append(int(float(tts_msb)))
    xbpf.ets_lsb.append(int(float(ets_lsb)))
    xbpf.ets_msb.append(int(float(ets_msb)))
    #xbpf.f0.append(int(float(f0)))
    #xbpf.f1.append(int(float(f1)))
    #xbpf.f2.append(int(float(f2)))
    #xbpf.f3.append(int(float(f3)))
    #xbpf.f4.append(int(float(f4)))
    #xbpf.f5.append(int(float(f5)))
    xbpf.f0.append(unpack('I', pack('i', int(float(f0))))[0])
    xbpf.f1.append(unpack('I', pack('i', int(float(f1))))[0])
    xbpf.f2.append(unpack('I', pack('i', int(float(f2))))[0])
    xbpf.f3.append(unpack('I', pack('i', int(float(f3))))[0])
    xbpf.f4.append(unpack('I', pack('i', int(float(f4))))[0])
    xbpf.f5.append(unpack('I', pack('i', int(float(f5))))[0])
  #output.Fill()

class XBPF:
  def __init__(self, label):
    self.timestamp = 0
    self.current = 0
    self.counts_rec = 0
    self.detName = label
    self.detType = "XBPF"
    self.tts_lsb = []
    self.tts_msb = []
    self.ets_lsb = []
    self.ets_msb = []
    self.f0 = []
    self.f1 = []
    self.f2 = []
    self.f3 = []
    self.f4 = []
    self.f5 = []

def get_results_xbpf(xbpf_label, t0, t1, currents, the_buffer):
  print('Getting for', xbpf_label)
  time_period = make_time_period(t0, t1)
  url = f'{base_url}{xbpf_device_base}{xbpf_label}:eventsData[]{time_period}{ending}'
  results = get_results(url)
  print('Got', len(results), 'acqs')

  counts_rec_results = get_results(url.replace('eventsData', 'countsRecords'))
  print(len(counts_rec_results))

  
  for i in range(len(results)):
    xbpf = XBPF(xbpf_label)
    xbpf.counts_rec = int(float(counts_rec_results[i][-1]))
    #output.Clear()
    #output.counts_rec[0] = int(float(counts_rec_results[i][-1]))
    #print(output.counts_rec[0])
    #output.detName.replace(0, RT.std.string.npos, xbpf_label)
    #output.detType.replace(0, RT.std.string.npos, 'XBPF')
    data = results[i]
    parse_xbpf_events_data(data, currents, xbpf)
    the_buffer.all_timestamps.append(xbpf.timestamp)
    the_buffer.xbpfs[xbpf_label][xbpf.timestamp] = xbpf

def parse_timestamp_counts(data):
  return data[2], int(float(data[4]))

def check_timestamps(*timestamps):
  if len(set(timestamps)) != 1:
    raise Exception('Got multiple timestamps',*(list(set(timestamps))))


def get_results_xbtf(xbtf_label, t0, t1, the_buffer, do_gt=False):
  print('Getting for', xbtf_label)
  #time_period = f'&t0={t0}&t1={t1}'
  time_period = make_time_period(t0, t1)
  all_results = dict()


  var = 'frac[]'
  url = f'{base_url}{xbtf_device_base}{xbtf_label}:{var}{time_period}{ending}'
  if do_gt: url = url.replace('XTOF', 'XBTF')

  frac_results = get_results(url)
  #print(len(frac_results))

  url = url.replace('frac', 'coarse')
  coarse_results = get_results(url)
  #print(len(coarse_results))

  url = url.replace('coarse', 'seconds')
  seconds_results = get_results(url)
  #print(len(seconds_results))

  url = url.replace('seconds[]', 'timestampCount')
  ts_count_results = get_results(url)
  #print(len(ts_count_results))

  for i in range(len(frac_results)):
    #output.Clear() 

    frac_ts, frac_data = parse_frac_coarse(frac_results[i])
    coarse_ts, coarse_data = parse_frac_coarse(coarse_results[i])
    seconds_ts, seconds_data = parse_seconds(seconds_results[i])
    counts_ts, counts = parse_timestamp_counts(ts_count_results[i])

    if frac_ts != coarse_ts or coarse_ts != seconds_ts:
      raise Exception('Incorrect ts', i)

    check_timestamps(frac_ts, coarse_ts, seconds_ts, counts_ts)
    xbtf = XBTF(xbtf_label)
    #print(frac_ts)
    #output.timestamp[0] = float(frac_ts)
    xbtf.timestamp = float(frac_ts)
    #print(counts)
    #output.timestampCount[0] = counts
    xbtf.timestampCount = counts
    #print('ts:', int(float(frac_ts)))
    #output.detName.replace(0, RT.std.string.npos, xbtf_label)
    #output.detType.replace(0, RT.std.string.npos, 'XBTF')
    for j in range(len(frac_data)):
      if ((frac_data[j] == coarse_data[j]) and
          (frac_data[j] == seconds_data[j]) and
          (frac_data[j] == 0)): 
        continue
      #output.frac.push_back(frac_data[j])
      #output.coarse.push_back(coarse_data[j])
      #output.seconds.push_back(seconds_data[j])
      xbtf.frac.append(frac_data[j])
      xbtf.coarse.append(coarse_data[j])
      xbtf.seconds.append(seconds_data[j])

    the_buffer.xbtfs[xbtf_label][xbtf.timestamp] = xbtf 
    the_buffer.all_timestamps.append(xbtf.timestamp)
    #print(len(output.frac))
    #print(len(output.coarse))
    #print(len(output.seconds))

    #output.Fill()
class XBTF:
  def __init__(self, label):
    self.detName = label
    self.detType = 'XBTF'
    self.frac = []
    self.coarse = []
    self.seconds = []
    self.timestampCount = 0
    self.timestamp = 0.

def parse_seconds(data):
  #print(data)
  ts = data[2]
  results = []
  for i in range(5, len(data), 2):
    #if data[i] == '0.0': break
    results.append(int(float(data[i])))
  return ts, results 


def parse_frac_coarse(data):
  ts = data[2]
  #print(ts, data[:10])
  results = []
  for d in data[4:]:
    #if d == '0.0': break
    results.append(int(float(d)))
  return ts, results

class MetaOutput:
  def __init__(self, start, end, interval=60):
    self.outputs=[]
    self.start=start
    self.end=end
    self.starts=[]
    self.ends=[]
    self.interval=interval

    t = start
    while t < end:
      self.starts.append(t) 
      self.ends.append(min[(t+interval, end)])
      self.outputs.append(Output(f'eventsData_{t}.root'))

  def find_output(self, ts):
    if ts < self.starts[0] or ts > ends[-1]:
      return None
    for i in range(len(self.starts)):
      if ts < self.ends[i] and ts > self.starts[i]:
        return self.outputs[i]

  def write_all(self):
    for o in self.outputs: o.Write()
  def close_all(self):
    for o in self.outputs: o.Close()
    

class Output:
  def __init__(self, outname):
    self.detName = RT.string()
    self.detType = RT.string()
    self.subscription = RT.string()

    self.coarse = RT.vector('unsigned int')()
    self.frac = RT.vector('unsigned int')()
    self.seconds = RT.vector('unsigned long')()

    self.tts_lsb = RT.vector('unsigned long')()
    self.tts_msb = RT.vector('unsigned long')()
    self.ets_lsb = RT.vector('unsigned long')()
    self.ets_msb = RT.vector('unsigned long')()
    self.f0 = RT.vector('unsigned int')()
    self.f1 = RT.vector('unsigned int')()
    self.f2 = RT.vector('unsigned int')()
    self.f3 = RT.vector('unsigned int')()
    self.f4 = RT.vector('unsigned int')()
    self.f5 = RT.vector('unsigned int')()

    self.fout = RT.TFile(outname, 'recreate')

    self.tree = RT.TTree('eventsData', 'eventsData')

    self.timestamp = array('d', [0])
    self.timestampCount = array('Q', [0])
    self.counts_rec = array('Q', [0])
    self.current = array('d', [0])

    self.tree.Branch('timestamp', self.timestamp, 'timestamp/D')
    self.tree.Branch('current', self.current, 'current/D')
    self.tree.Branch('countsRec', self.counts_rec, 'countsRec/I')
    self.tree.Branch('timestampCount', self.timestampCount, 'timestampCount/I')
    self.tree.Branch('Coarse', self.coarse)
    self.tree.Branch('Seconds', self.seconds)
    self.tree.Branch('Frac', self.frac)
    self.tree.Branch('detName', self.detName)
    self.tree.Branch('subscription', self.subscription)
    self.tree.Branch('detType', self.detType)

    self.tree.Branch('Fibres0', self.f0)
    self.tree.Branch('Fibres1', self.f1)
    self.tree.Branch('Fibres2', self.f2)
    self.tree.Branch('Fibres3', self.f3)
    self.tree.Branch('Fibres4', self.f4)
    self.tree.Branch('Fibres5', self.f5)

    self.tree.Branch('TTS_LSB', self.tts_lsb)
    self.tree.Branch('TTS_MSB', self.tts_msb)
    self.tree.Branch('ETS_LSB', self.ets_lsb)
    self.tree.Branch('ETS_MSB', self.ets_msb)




  def Fill(self):
    self.tree.Fill()

  def Write(self):
    self.tree.Write()
 
  def Close(self):
    self.fout.Close()

  def Clear(self):
    self.coarse.clear()
    self.frac.clear()
    self.seconds.clear()

    #self.detName.clear()
    #self.detType.clear()
    self.f0.clear()
    self.f1.clear()
    self.f2.clear()
    self.f3.clear()
    self.f4.clear()
    self.f5.clear()
    self.tts_lsb.clear()
    self.tts_msb.clear()
    self.ets_lsb.clear()
    self.ets_msb.clear()

    #self.counts_rec = 0

def get_results_mbpl(t0, t1):
  time_period = make_time_period(t0, t1)
  print('Getting magnet current')
  url = f'{base_url}dip/acc/NORTH/NP04/POW/MBPL022699:i_Meas{time_period}{ending}'
  results = get_results(url)
  #print(len(results))
  #return {int(data[-3]):float(data[-1]) for data in results}
  currents = [(int(data[-3]), float(data[-1])) for data in results]
  currents.sort(key=lambda a : a[0])
  return currents


class Buffer:
  def __init__(self):
    self.all_timestamps = []
    self.currents = {}
    self.xbpfs = {
      'XBPF022697':{},
      'XBPF022701':{},
      'XBPF022702':{},
    }
    self.xbtfs = {
       'GeneralTrigger':{},
       'XBTF022687A':{},
       'XBTF022687B':{},
       'XBTF022716A':{},
       'XBTF022716B':{},
    }
  def in_all(self, ts):
    for x in self.xbpfs.values():
      if ts not in x: return False
    for x in self.xbtfs.values():
      if ts not in x: return False
    return True

def fill_xbpf(output, xbpf):
  output.counts_rec[0] = xbpf.counts_rec 
  output.detName.replace(0, RT.std.string.npos, xbpf.detName)
  output.detType.replace(0, RT.std.string.npos, 'XBPF')
  output.current[0] = xbpf.current
  output.timestamp[0] = xbpf.timestamp 
  for i in range(len(xbpf.tts_lsb)): 
    output.tts_lsb.push_back(xbpf.tts_lsb[i])
    output.tts_msb.push_back(xbpf.tts_msb[i])
    output.ets_lsb.push_back(xbpf.ets_lsb[i])
    output.ets_msb.push_back(xbpf.ets_msb[i])
    output.f0.push_back(xbpf.f0[i])
    output.f1.push_back(xbpf.f1[i])
    output.f2.push_back(xbpf.f2[i])
    output.f3.push_back(xbpf.f3[i])
    output.f4.push_back(xbpf.f4[i])
    output.f5.push_back(xbpf.f5[i])

def fill_xbtf(output, xbtf):
  output.timestamp[0] = xbtf.timestamp 
  output.timestampCount[0] = xbtf.timestampCount
  output.detName.replace(0, RT.std.string.npos, xbtf.detName)
  output.detType.replace(0, RT.std.string.npos, 'XBTF')
  for j in range(len(xbtf.frac)):
    output.frac.push_back(xbtf.frac[j])
    output.coarse.push_back(xbtf.coarse[j])
    output.seconds.push_back(xbtf.seconds[j])


if __name__ == '__main__':

  parser = ap()
  parser.add_argument('--start', type=int, default=1718818000)
  parser.add_argument('--end', type=int, default=1718819000)
  parser.add_argument('--interval', type=int, default=1800)
  parser.add_argument('--subinterval', type=int, default=120)
  #parser.add_argument('-o', type=str, default='test.root')
  args = parser.parse_args()

  #make the meta_output

  start = args.start
  while start < args.end:
    #output = Output(f'eventsData_{start}.root')
    end = min([args.end, start + args.interval])
    print('Time region:', start, end)
    currents = get_results_mbpl(start, end)

    the_buffer = Buffer()

    xbpfs = [
      'XBPF022697',
      #'XBPF022698',
      'XBPF022701',
      'XBPF022702',
      #'XBPF022707',
      #'XBPF022708',
      #'XBPF022716',
      #'XBPF022717',
    ]
    for xbpf in xbpfs: #['XBPF022697']:
      get_results_xbpf(xbpf, start, end, currents, the_buffer)

    #print(the_buffer.all_timestamps)
    #print(the_buffer.xbpfs['XBPF022697'])
    #print(len(the_buffer.xbpfs['XBPF022697']))
    #for ts, x in the_buffer.xbpfs['XBPF022697'].items():
    #  print(ts, x.counts_rec, x.current)

    xbtfs = [
      'XBTF022687A',
      'XBTF022687B',
      'XBTF022716A',
      'XBTF022716B',
    ]
    for xbtf in xbtfs:
      get_results_xbtf(xbtf, start, end, the_buffer)
      print(len(the_buffer.xbtfs[xbtf]))
      #for ts, x in the_buffer.xbtfs[xbtf].items():
      #  print(ts, x.timestampCount)
    for xbtf in ['GeneralTrigger']:
      get_results_xbtf(xbtf, start, end, the_buffer, do_gt=True)

    for ts in list(set(the_buffer.all_timestamps)):
      if not the_buffer.in_all(ts): continue
      print('Saving for', ts)
      output = Output(f'eventsData_{int(ts)}.root')
      for x in the_buffer.xbpfs.values():
        output.Clear()
        fill_xbpf(output, x[ts])
        output.Fill()
      for x in the_buffer.xbtfs.values():
        output.Clear()
        fill_xbtf(output, x[ts])
        output.Fill()
      
      output.Write()
      output.Close()
    start += args.interval
