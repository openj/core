18!:4 <'z' NB. start in z

NB. =========================================================
startupconsole=: 3 : 0
f=. jpath '~config/startup_console.ijs'
if. 1!:4 :: 0: <f do.
  18!:4 <'base'
  try.
    load f
  catch.
    smoutput 'An error occurred when loading startup script: ',f
  end.
end.
)

NB. =========================================================
startupide=: 3 : 0
startup=. jpath '~config/startup.ijs'
if. 1!:4 :: 0: <startup do.
  18!:4 <'base'
  try.
    load startup
  catch.
    smoutput 'An error occurred when loading startup script: ',startup
  end.
end.
)

NB. =========================================================
3 : 0''
ndx=. ({."1 SystemFolders_j_) i. <'system'
sys=. '/' ,~ > 1 { ndx { SystemFolders_j_

NB. ---------------------------------------------------------
NB. following assumes Displayload is set in immex, then
NB. the profile loaded. No need for another ijx window
if. 0=4!:0<'Displayload_j_' do.
  Displayload_j_=: 1
  boot=. 3 : ('0!:0 <y[y 1!:2[2') @ jpathsep @ (sys&,)
else.
  Displayload_j_=: 0
  boot=. 3 : '0!:0 <y' @ jpathsep @ (sys&,)
end.

NB. ---------------------------------------------------------
boot 'main/stdlib.ijs'
load '~system/util/scripts.ijs'
load 'regex'
load 'task'
load '~system/util/configure.ijs'
load '~system/main/ctag.ijs'
load '~system/util/jadetag.ijs'
startupide''

NB. ---------------------------------------------------------
NB. JVERSION_z_ (used in about box)
r=. 'Engine: ',9!:14''
r=. r,LF,'Library: ',LF -.~ 1!:1<jpath '~system/config/version.txt'
r=. r,LF,'Platform: ',UNAME,' ',IF64 pick '32';'64'
r=. r,LF,'Installer: ',1!:1 :: ('unknown'"_) <jpath'~bin/installer.txt'
r=. r,LF,'InstallPath: ',jpath '~install'
JVERSION=: toJ r

NB. ---------------------------------------------------------
NB. set break
setbreak 'default'

NB. ---------------------------------------------------------
ndx=. <./ ARGV i. '-jp';'-jprofile'
jsx=. ARGV i. <'-js'
if. ndx < #ARGV do. p=. 2 + ndx else. p=. 1 end.
load__ >{. p }. jsx {. ARGV

if. jsx<#ARGV do.
  ARGVVERB_z_=: 3 : ((>:jsx)}.ARGV) NB. define in z
  ARGVVERB__'' NB. run in base
elseif. ({.ARGV) = <'gtkide',IFWIN#'.exe' do.
  load__'gtkide'
elseif. (}.@(}.~ i:&(IFWIN{'/\')) &.> {.ARGV) = <'gtkide',IFWIN#'.exe' do.
  load__'gtkide'
end.

EMPTY
)

NB. =========================================================
18!:4 <'base' NB. end in base
