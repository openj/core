NB. utilities for J GPL source release test
NB. assumes J GPL source folder is current directory
NB. see test/tsu.ijs for additional info

testpath=: jpath (1!:43''),'/test/' NB. 1!:43 current directory
load testpath,'tsu.ijs'

9!:11[6         NB. ensure default print precision
9!:21[1e8       NB. limit error rather than long memory thrash (g400)
threshold=: 0]0.1 NB. timer threshold failures less likely
3 : 0''
if. ((<UNAME) e. 'Linux';'Android') *. 1 e. '/sdcard' E. 1!:43'' do.
  libtsdll=: ' ',~(BINPATH),'/libtsdll.so'
else.
  libtsdll=: jpath ' ',~(1!:43''),>IFWIN{'/tsdll.dll';~'/libtsdll.',>(UNAME-:'Darwin'){'so';'dylib'
end.
)

LOGFILE=: 2     NB. log to console (2) or file (jpath'~temp/log.log')
LOGIT=: 3 : 'y[(>y)1!:2<LOGFILE'
SNS=: 3 : '(<testpath),each(;:y),each<''.ijs''' NB. script names
BAD=: 3 : '>(-.bad)#y'

TEST=:   (13 : '0!:3  LOGIT y')"0
TESTX=:  (13 : '0!:2 LOGIT y')"0

3 : 0''
if. ('Android'-:UNAME) do.
  if. 0= 'libc.so isatty > i i'&(15!:0) 0 do.
    ddall=: ddall -. SNS 'gstack'   NB. gstack always crashed in Android jconsoleapp
  end.
end.
)

NB. bad=: TEST ddall
NB. BAD ddall

NB. TESTX SNS 'g120' NB. see g120 details

NB. TESTX SNS 'g120 gintovfl' NB. see g120 gintovfl details

NB. ddt=: ddall -. SNS 'g120 gintovfl' NB. remove crashers
NB. bad=: TEST ddt
NB. BAD ddt
ddt=: ddall -. SNS 'gstack' NB. remove crashers
