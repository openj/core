cocurrent 'jpacman'
coinsert 'j'

BASELIB=: 'base library'
DATAMASK=: 0
HWNDP=: ''
ISGUI=: 0
ONLINE=: 0
PKGDATA=: 0 7$a:
SECTION=: ,<'All'
SYSNAME=: 'Package Manager'
TIMEOUT=: 60
WWWREV=: REV=: _1
3 : 0''
nc=. '--no-cache'
if. IFUNIX do.
  if. UNAME-:'Darwin' do.
    HTTPCMD=: 'curl -o %O --stderr %L -f -s -S %U'
  else.
    try. nc=. nc #~ 1 e. nc E. shell 'wget --help' catch. nc=. '' end.
    HTTPCMD=: 'wget ',nc,' -O %O -o %L -t %t %U'
  end.
else.
  exe=. '"',(jpath '~tools/ftp/wget.exe'),'"'
  try. nc=. nc #~ 1 e. nc E. shell exe,' --help' catch. nc=. '' end.
  HTTPCMD=: exe,' ',nc,' -O %O -o %L -t %t -T %T %U'
  UNZIP=: '"',(jpath '~tools/zip/unzip.exe'),'" -o -C '
end.
)
setfiles=: 3 : 0
ADDCFG=: jpath '~addons/config/'
makedir ADDCFG
ADDCFGIJS=: ADDCFG,'config.ijs'
JRELEASE=: ({.~i.&'/') 9!:14''
LIBTREE=: readtree''
WWW=: 'http://www.jsoftware.com/jal/',JRELEASE,'/'
LIBVER=: jpath '~system/config/version.txt'
)
destroy=: codestroy
CFGFILES=: <;._2 (0 : 0)
addons.txt
library.txt
release.txt
revision.txt
zips.txt
)
LIBDESC=: 0 : 0
This is the base library of scripts and labs included in the J system.

Reinstalling or upgrading this library will overwrite files in the system subdirectory. Restart J afterwards.

Files outside the system subdirectory, such as profile.ijs, are not changed.
)
cutjal=: ([: (* 4 > +/\) ' ' = ]) <;._1 ]
cutjsp=: ([: (* 5 > +/\) ' ' = ]) <;._1 ]
dquote=: '"'&, @ (,&'"')
fname=: #~ ([: *./\. ~:&'/')
hostcmd=: [: 2!:0 '(' , ] , ' || true)'"_
ischar=: 2 = 3!:0
rnd=: [ * [: <. 0.5 + %~
sep2under=: '/' & (I.@('_' = ])})
termLF=: , (0 < #) # LF -. {:
todel=: ; @: (DEL&, @ (,&(DEL,' ')) each)
tolist=: }. @ ; @: (LF&,@,@":each)
getintro=: ('...' ,~ -&3@[ {. ])^:(<#)
info=: smoutput
getnames=: 3 : 0
  select. L.y
  case. 0 do.                        
    if. +/ BASELIB E. y do.          
      y=. (<BASELIB), cutnames y rplc BASELIB;''
    else.
      y=. cutnames y
    end.
  case. 1 do.
    if. 2 = #$y  do.                 
      y=. {."1 y                     
    else.
      y=. ,y
    end.
  case. do.
    '' return.
  end.
  y
)
curtailcaption=: 3 : 0
  idx=. <_1;~I. 45<#&>{:"1 y
  y=. (45&getintro &.> idx{y) idx}y
)
deltree=: 3 : 0
  try.
    res=. 0< ferase {."1 dirtree y
    *./ res,0<ferase |.dirpath y
  catch. 0 end.
)
fixjal=: 3 : 0
if. 2 > #y do. i.0 5 return. end.
m=. _2 |. (LF,')',LF) E. y
r=. _2 }. each m <;._2 y
x=. r i.&> LF
d=. (x+1) }.each r
r=. x {.each r
r=. 3 {."1 cutjal &> ' ' ,each r
x=. d i.&> LF
c=. x {.each d
d=. (x+1) }.each d
r,.c,.d
)
fixjal2=: 3 : 0
if. 2 > #y do. i.0 2 return. end.
cutjal &> ' ' ,each <;._2 y
)
fixjsp=: 3 : 0
if. 2 > #y do. i.0 5 return. end.
m=. _2 |. (LF,')',LF) E. y
r=. _2 }. each m <;._2 y
x=. r i.&> LF
d=. (x+1) }.each r
r=. x {.each r
r=. ' ' ,each r
(cutjsp &> r),.d
)
fixlib=: 3 : 0
msk=. (<LIBTREE) = 1 {"1 y
if. -. 1 e. msk do. ($0);'';0 return. end.
'ver fln siz'=. 2 4 5 { (msk i.1) { y
ver=. fixver ver
ver;fln;siz
)
fixlibs=: 3 : 0
if. 2 > #y do.
  i.0 6 return.
end.
fls=. <;._2 y
ndx=. fls i.&> ' '
siz=. <&> 0 ". (ndx+1) }.&> fls
fls=. ndx {.each fls
zps=. <;._2 &> fls ,each '_'
pfm=. 3 {"1 zps
msk=. IFUNIX ~: (1 e. 'win'&E.) &> pfm
msk # zps,.fls,.siz
)
fixrev=: 3 : 0
{. _1 ". :: _1: y -. CRLF
)
fixupd=: 3 : 0
_1 ". :: _1: y -. CRLF
)
fixver=: 3 : 0
if. ischar y do.
  y=. y -. CRLF
  y=. 0 ". ' ' (I. y='.') } y
end.
3 {. y
)
fixvers=: 3 : 0
s=. $y
y=. ,y
3 {."1 [ 0 ". s $ ' ' (I. y e. './') } y
)
fmtjal=: 3 : 0
if. 0 = #y do. '' return. end.
r=. (4 {."1 y) ,each "1 '  ',LF2
r=. <@; "1 r
; r ,each ({:"1 y) ,each <')',LF
)
fmtjal2=: 3 : 0
if. 0 = #y do. '' return. end.
; (2 {."1 y) ,each "1 ' ',LF
)
fmtdep=: 3 : 0
}. ; ',' ,each a: -.~ <;._2 y
)
fmtjsp=: 3 : 0
if. 0 = #y do. '' return. end.
r=. (4 {."1 y) ,each "1 '   ',LF
r=. <@; "1 r
; r ,each ({:"1 y) ,each <')',LF
)
fmtlib=: 3 : 0
, 'q<.>,q<.>r<0>3.0,r<0>3.0' 8!:2 y
)
fmtver=: 3 : 0
if. 0=#y do. '' return. end.
if. ischar y do. y return. end.
}. ; '.' ,each ": each y
)
fmtverlib=: 3 : 0
fmtver y
)
fixzips=: 3 : 0
if. 2 > #y do. i.0 5 return. end.
fls=. <;._2 y
ndx=. fls i.&> ' '
siz=. 0 ". (ndx+1) }.&> fls
fls=. ndx {.each fls
zps=. <;._2 &> fls ,each '_'
zps=. zps,.fls,.<&>siz
pfm=. 3 {"1 zps
lnx=. (1 e. 'linux'&E.) &> pfm
mac=. (1 e. 'darwin'&E.) &> pfm
win=. mac < (1 e. 'win'&E.) &> pfm

select. UNAME
case. 'Win' do.
  zps=. win # zps
case. 'Linux' do.
  zps=. lnx # zps
case. 'Darwin' do.
  zps=. (lnx +. mac) # zps
  zps=. zps /: 3 {"1 zps
  zps=. (~: 3 {."1 zps) # zps
end.

bit=. IF64 pick '64';'32'
pfm=. 3 {"1 zps
exc=. (1 e. bit&E.) &> pfm
zps=. zps \: exc
zps=. (~: 3 {."1 zps) # zps
fnm=. 0 {"1 zps
lnm=. 1 {"1 zps
ver=. 2 {"1 zps
pfm=. 3 {"1 zps
fls=. 4 {"1 zps
siz=. 5 {"1 zps
nms=. fnm ,each '/' ,each lnm
pfm=. (pfm i.&> '.') {.each pfm
ndx=. \: # &> pfm
sort ndx { nms,.pfm,.ver,.fls,.siz
)
fwritenew=: 4 : 0
if. x -: fread y do.
  0
else.
  x fwrite y
end.
)
platformparent=: 3 : 0
((< _2 {. y) e. '32';'64') # _2 }. y
)
makedir=: 1!:5 :: 0: @ <
plural=: 4 : 0
y,(1=x)#'s'
)
sizefmt=: 3 : 0
select. +/ y >: 1e3 1e4 1e6 1e7 1e9
case. 0 do.
  (": y), ' byte',(y~:1)#'s'
case. 1 do.
  (": 0.1 rnd y%1e3),' KB'
case. 2 do.
  (": 1 rnd y%1e3),' KB'
case. 3 do.
  (": 0.1 rnd y%1e6),' MB'
case. 4 do.
  (": 1 rnd y%1e6),' MB'
case. do.
  (": 0.1 rnd y%1e9),' GB'
end.
)
shellcmd=: 3 : 0
if. IFUNIX do.
  hostcmd y
else.
  spawn_jtask_ y
end.
)
subdir=: 3 : 0
if. 0=#y do. '' return. end.
a=. 1!:0 y,'*'
if. 0=#a do. '' return. end.
a=. a #~ '-d' -:"1 [ 1 4 {"1 > 4 {"1 a
(<y) ,each ({."1 a) ,each '/'
)
testaccess=: 3 : 0
f=. <jpath'~bin\installer.txt'
d=. 1!:1 f
try.
 1!:55 f
 d 1!:2 f
 1
catch.
 0
end.
)
toupper1=: 3 : 0
if. 0=#y do. '' return. end.
(toupper {. y),tolower }. y
)
unzip=: 3 : 0
'file dir'=. dquote each y
e=. 'Unexpected error'
if. IFUNIX do.
  e=. shellcmd 'tar -xzf ',file,' -C ',dir
else.
   dir=. (_2&}. , '/' -.~ _2&{.) dir
  e=. shellcmd UNZIP,' ',file,' -d ',dir
end.
e
)
zipext=: 3 : 0
y, IFUNIX pick '.zip';'.tar.gz'
)
CHECKADDONSDIR=: 0 : 0
The addons directory does not exist and cannot be created.

It is set to: XX.

You can either create the directory manually, or set a new addons directory in your profile script.
)
CHECKASK=: 0 : 0
Read catalog from the server using Internet connection now?

Otherwise the local catalog is used offline.
)
CHECKONLINE=: 0 : 0
An active Internet connection is needed to install packages.

Continue only if you have an active Internet connection.

OK to continue?
)
CHECKREADSVR=: 0 : 0
An active Internet connection is needed to read the server repository catalog.

Continue only if you have an active Internet connection.

OK to continue?
)
CHECKSTARTUP=: 0 : 0
Setup repository using Internet connection now?

Select No if not connected, to complete setup later. After Setup is done, repository can be used offline with more options in Tools menu and Preferences dialog.
)
checkaccess=: 3 : 0
if. testaccess'' do. 1 return. end.
msg=. 'Unable to run Package Manager, as you do not have access to the installation folder.'
if. IFWIN do.
  msg=. msg,LF2,'To run as Administrator, right-click the J icon, select Run as... and '
  msg=. msg,'then select Adminstrator.'
end.
info msg
0
)
checkaddonsdir=: 3 : 0
d=. jpath '~addons'
if. # 1!:0 d do. 1 return. end.
if. 1!:5 :: 0: <d do.
  log 'Created addons directory: ',d
  1 return.
end.
info CHECKADDONSDIR rplc 'XX';d
0
)
getonline=: 3 : 0
ONLINE=: mbnoyes y
)
getserver=: 3 : 0
'rc p'=. httpgetr (WWW,'revision.txt');2
if. rc do. 0 return. end.
write_lastupdate''
WWWREV=: fixrev p
if. WWWREV = REV do. 1 return. end.
refreshweb''
)
checkonline=: 3 : 0
select. ReadCatalog
case. 0 do.
  if. REV >: 0 do.
    ONLINE=: 0
    log 'Using local copy of catalog. See Preferences to change the setting.'
    1 return.
  end.
  if. 0 = getonline 'Read Catalog from Server';CHECKREADSVR do. 0 return. end.
case. 1 do.
  ONLINE=: 1
case. 2 do.
  if. REV >: 0 do.
    if. 0 = getonline 'Read Catalog from Server';CHECKASK do.
      log 'Using local copy of catalog. See Preferences to change the setting.'
      1 return.
    end.
  else.
    if. 0 = getonline 'Setup Repository';CHECKSTARTUP do. 0 return. end.
  end.
end.
log 'Updating server catalog...'
if. 0 = getserver'' do.
  ONLINE=: 0
  log 'Working offline using local copy of catalog.'
else.
  log 'Done.'
end.
1
)
checkstatus=: 3 : 0
if. 0 e. #LIBS do. '' return. end.
msk=. masklib PKGDATA
ups=. pkgups''
libupm=. 1 e. msk *. ups
msk=. -. msk
addnim=. +/msk *. pkgnew''
addupm=. +/msk *. pkgups''
tot=. +/addnim,addupm,libupm
if. 0 = tot do.
  'All available packages are installed and up to date.' return.
end.
select. 0 < addnim,addupm
case. 0 0 do.
  msg=. 'Addons are up to date.'
case. 0 1 do.
  msg=. 'All addons are installed, ',(":addupm), ' can be updated.'
case. 1 0 do.
  if. addnim = <:#PKGDATA do.
    msg=. 'No addons are installed.'
  else.
    j=. ' addon',('s'#~1<addnim),' are not yet installed.'
    msg=. 'Installed addons are up to date, ',(":addnim),j
  end.
case. 1 1 do.
  j=. (":addupm),' addon',('s'#~1<addupm),' can be updated, '
  msg=. j,(":addnim), ' addon',('s'#~1<addnim),' are not yet installed.'
end.
if. 0 = libupm do.
  msg,LF,'The base library is up to date.'
else.
  msg,LF,'There is a newer version of the base library.'
end.
)

write_lastupdate=: 3 : 0
txt=. ": 6!:0 ''
txt fwrites ADDCFG,'lastupdate.txt'
)
checklastupdate=: 3 : 0
if. _1 -: LASTUPD do.
  res=. 'has never been updated.'
else.
  res=. 'was last updated: ',timestamp LASTUPD
end.
'Local JAL information ',res
)
PACMANCFG=: jpath '~config/pacman.cfg'

readconfig=: 3 : 0
ReadCatalog=: 2
0!:0 :: ] <PACMANCFG
)
httpget=: 3 : 0
'f t'=. 2 {. (boxxopen y),a:
n=. f #~ -. +./\. f e. '=/'
p=. jpath '~temp/',n
q=. jpath '~temp/httpget.log'
t=. ":{.t,3
ferase p;q
fail=. 0
cmd=. HTTPCMD rplc '%O';(dquote p);'%L';(dquote q);'%t';t;'%T';(":TIMEOUT);'%U';f
try.
  e=. shellcmd cmd
catch. fail=. 1 end.
if. fail +. 0 >: fsize p do.
  if. _1-:msg=. freads q do.
    if. 0=#msg=. e do. msg=. 'Unexpected error' end. end.
  log 'Connection failed: ',msg
  info 'Connection failed:',LF2,msg
  r=. 1;msg
  ferase p;q
else.
  r=. 0;p
  ferase q
end.
r
)
httpgetr=: 3 : 0
res=. httpget y
if. 0 = 0 pick res do.
  f=. 1 pick res
  txt=. freads f
  ferase f
  0;txt
end.
)
install=: 3 : 0
dat=. y
'num siz'=. pmview_applycounts dat
many=. 1 < num
msg=. 'Installing ',(":num),' package',many#'s'
msg=. msg,' of ',(many#'total '),'size ',sizefmt siz
log msg
installdo 1 {"1 dat
log 'Done.'
readlocal''
pacman_init 0
)
install_console=: 3 : 0
  if. -. init_console 'server' do. '' return. end.
  pkgs=. getnames y
  if. pkgs -: ,<'all' do. pkgs=. 1 {"1 PKGDATA end.
  pkgs=. pkgs (e. # [) ((pkgnew +. pkgups) # 1&{"1@]) PKGDATA  
  if. 0 = num=. #pkgs do. '' return. end.
  many=. 1 < num
  msg=. 'Installing ',(":num),' package',many#'s'
  log msg
  installdo pkgs
  log 'Done.'
  readlocal''
  pacman_init ''
  checkstatus''
)
upgrade_console=: 3 : 0
  if. -. init_console 'read' do. '' return. end.
  pkgs=. getnames y
  if. (0=#pkgs) +. pkgs -: ,<'all' do. pkgs=. 1{"1 PKGDATA end.
  pkgs=. pkgs (e. # [) (pkgups # 1&{"1@])PKGDATA 
  install_console pkgs
)
installdo=: 3 : 0
msk=. -. y e. <BASELIB
if. 0 e. msk do.
  install_library''
end.
install_addon each msk # y
)
install_addon=: 3 : 0
ndx=. ({."1 ZIPS) i. <y
if. ndx = #ZIPS do. EMPTY return. end.
log 'Downloading ',y,'...'
f=. 3 pick ndx { ZIPS
'rc p'=. httpget WWW,'addons/',f
if. rc do. return. end.
log 'Installing ',y,'...'
msg=. unzip p;jpath'~addons'
ferase p
if. 0>:fsize jpath'~addons/',y,'/manifest.ijs' do.
  log 'Extraction failed: ',msg
  info 'Extraction failed:',LF2,msg
  return.
end.
install_addins y
install_config y
)
install_addins=: 3 :0
fl=. ADDCFG,'addins.txt'
ins=. fixjal2 freads fl
ins=. ins #~ (<y) ~: {."1 ins
ndx=. ({."1 ADDONS) i. <y
ins=. sort ins, 2 {. ndx { ADDONS
(fmtjal2 ins) fwrites fl
)
install_config=: 3 : 0
ADDLABS=: ''
0!:0 :: ] < ADDCFGIJS
install_labs y
write_config''
)
install_labs=: 3 : 0
labs=. dirtree jpath '~addons/',y,'/*.ijt'
if. 0=#labs do. return. end.
pfx=. jpath '~addons/'
labs=. (#pfx) }.each {."1 labs
LABCATEGORY=: ''
0!:0 ::] <jpath '~addons/',y,'/manifest.ijs'
cat=. LABCATEGORY
if. 0 = #cat do.
  cat=. toupper1 (y i. '/') {. y
end.
new=. labs ,each <' ',cat
txt=. sort ~. new,<;._2 ADDLABS
ndx=. 4 + (1 i.~ '.ijt'&E.) &> txt
msk=. fexist &> (<pfx) ,each ndx {.each txt
txt=. msk # txt
ADDLABS=: ; txt ,each LF
)
install_library=: 3 : 0
log 'Downloading base library...'
f=. 1 pick LIB
'rc p'=. httpget WWW,'library/',f
if. rc do. return. end.
log 'Installing base library...'
unzip p;jpath'~system'
ferase p
readlin''
)
write_config=: 3 : 0
txt=. 'NB. Addon configuration',LF2
txt=. txt,'ADDLABS=: 0 : 0',LF,ADDLABS,')',LF
txt fwrites ADDCFGIJS
)
show_console=: 4 : 0
  if. -. init_console 'read' do. '' return. end.
  select. x
  case. 'search' do.
    pkgs=. getnames y
    res=. (pkgsearch pkgs) # 1 2 3 4 {"1 PKGDATA
    res=. curtailcaption res
  case. 'show' do.
    pkgs=. getnames y
    if. pkgs -: ,<'all' do. pkgs=. 1 {"1 PKGDATA end.
    res=. (msk=. pkgshow pkgs) # 5 {"1 PKGDATA
    if. #res do.
      res=. ,((<'== '), &.> msk # 1 {"1 PKGDATA) ,. res      
      res=. (2#LF) joinstring (70&foldtext)&.> res 
    end.
  case. 'showinstalled' do.
    res=. (-.@pkgnew # 1 2 3 4&{"1@])PKGDATA
    res=. curtailcaption res
  case. 'shownotinstalled' do.
    res=. (pkgnew # 1 3 4&{"1@])PKGDATA
    res=. curtailcaption res
  case. 'showupgrade' do.
    res=. (pkgups # 1 2 3 4&{"1@])PKGDATA
    res=. curtailcaption res
  case. 'status' do.
    res=. checklastupdate''
    res=. res,LF,checkstatus''
  end.
  res
)
showfiles_console=: 4 : 0
  if. -. init_console 'read' do. '' return. end.
  pkgs=. getnames y
  pkgs=. pkgs (e. # [) (-.@pkgnew # 1&{"1@]) PKGDATA  
  pkgs=. pkgs -. <BASELIB                             
  if. 0=#pkgs do. '' return. end.
  fn=. (<'~addons/') ,&.> (pkgs) ,&.> <'/',x,(x-:'history'){::'.ijs';'.txt'
  res=. res #~ msk=. (<_1) ~: res=. fread@jpath &.> fn
  if. #res do.
    res=. ,((<'== '), &.> msk#pkgs) ,. res      
    res=. (2#LF) joinstring res
  end.
)
remove_console=: 3 : 0
  if. -. init_console 'edit' do. '' return. end.
  pkgs=. getnames y
  if. pkgs -: ,<'all' do. pkgs=. 1 {"1 PKGDATA end.
  pkgs=. pkgs (e. # [) (-.@pkgnew # 1&{"1@]) PKGDATA  
  pkgs=. pkgs -. <BASELIB 
  if. 0 = num=. #pkgs do. '' return. end.
  many=. 1 < num
  msg=. 'Removing ',(":num),' package',many#'s'
  log msg
  remove_addon each pkgs
  log 'Done.'
  readlocal''
  pacman_init ''
  checkstatus''
)

remove_addon=: 3 : 0
  log 'Removing ',y,'...'
  treepath=. jpath '~addons/',y
  if. ((0 < #@dirtree) *. -.@deltree) treepath do.
    nf=. #dirtree treepath  
    nd=. <: # dirpath treepath 
    nd=. nd + (tolower treepath) e. dirpath jpath '~addons/', '/' taketo y
    msg=. (":nd),' directories and ',(":nf),' files not removed.'
    log 'Remove failed: ',msg
    info 'Remove failed:',LF2,msg
    return.
  end.
  remove_addins y
  remove_config y
)
remove_addins=: 3 :0
  fl=. ADDCFG,'addins.txt'
  ins=. fixjal2 freads fl
  ins=. ins #~ (<y) ~: {."1 ins
  (fmtjal2 ins) fwrites fl
)
remove_config=: 3 : 0
  ADDLABS=: ''
  0!:0 :: ] < ADDCFGIJS
  remove_labs y
  write_config''
)
remove_labs=: 3 : 0
  txt=. <;._2 ADDLABS
  txt=. txt #~ (<jpathsep y) ~: (#y)&{. each txt
  ADDLABS=: ; txt ,each LF
)
LOG=: 1 
LOGMAX=: 100 
log=: 3 : 0
if. LOG do. smoutput y end.
)
logstatus=: 3 : 0
if. ONLINE do.
  log checkstatus''
end.
)
readlin=: 3 : 0
LIN=: 6 1 1 >. fixver freads LIBVER
)
readlocal=: 3 : 0
readlin''
ADDONS=: fixjal freads ADDCFG,'addons.txt'
ADDINS=: fixjal2 freads ADDCFG,'addins.txt'
REV=: fixrev freads ADDCFG,'revision.txt'
LASTUPD=: fixupd freads ADDCFG,'lastupdate.txt'
LIBS=: fixlibs freads ADDCFG,'library.txt'
LIB=: fixlib LIBS
ZIPS=: fixzips freads ADDCFG,'zips.txt'
EMPTY
)
readtree=: 3 : 0
f=. ADDCFG,'tree.txt'
tree=. LF -.~ freads f
if. -. (<tree) e. 'current';'stable' do.
  tree=. 'current'
  writetree tree
end.
tree
)
writetree=: 3 : 0
y fwritenew ADDCFG,'tree.txt'
)
refreshweb=: 3 : 0
if. 0 = refreshjal'' do. 0 return. end.
readlocal''
1
)
refreshaddins=: 3 : 0
ADDLABS=: ''
f=. ADDCFG,'addins.txt'
p=. jpath '~addons/'
sd=. ;subdir each subdir p
if. 0=#sd do.
  '' fwrite f
  write_config'' return.
end.
r=. s=. ''
for_d. sd do.
  mft=. freads (>d),'manifest.ijs'
  if. mft -: _1 do. continue. end.
  VERSION=: ''
  0!:100 mft
  ver=. fmtver fixver VERSION
  n=. }: (#p) }. >d
  n=. '/' (I.n='\') } n
  r=. r,n,' ',ver,LF
  s=. s,d
end.
r fwritenew f
s=. (#p) }.each }: each s
install_labs each s
write_config''
)
refreshjal=: 3 : 0
'rc p'=. httpget WWW,zipext 'jal'
if. rc do. 0 return. end.
unzip p;ADDCFG
ferase p
if. *./ CFGFILES e. {."1 [ 1!:0 ADDCFG,'*' do. 1 return. end.
msg=. 'Could not install the local repository catalog.'
log msg
info msg
0
)
updatejal=: 3 : 0
  log 'Updating server catalog...'
  if. -. init_console 'server' do. '' return. end.
  refreshaddins''
  readlocal''
  pacman_init''
  res=. checklastupdate''
  res,LF,checkstatus''
)
RELIBMSG=: 0 : 0
You are now using the XX base library, and can switch to the YY base library.

This will download the YY version of the base library and overwrite existing files. Addons are not affected.

OK to switch to the YY library?
)
prelib=: 3 : 0
old=. LIBTREE
new=. (('stable';'current') i. <old) pick 'current';'beta'
msg=. RELIBMSG rplc ('XX';'YY'),.old;new
if. 0 = query SYSNAME;msg do.
  info 'Not done.' return.
end.
switchlibrary 1 pick new
)
switchlibrary=: 3 : 0
ferase LIBVER
writetree LIBTREE=: y
refreshjal''
readlocal''
pmview_setpn''
)
masklib=: 3 : 0
(1 {"1 y) = <BASELIB
)
pkglater=: 3 : 0
if. 0=#PKGDATA do. $0 return. end.
loc=. fixvers > 2 {"1 PKGDATA
srv=. fixvers > 3 {"1 PKGDATA
{."1 /:"2 srv ,:"1 loc
)
pkgnew=: 3 : 0
0 = # &> 2 {"1 PKGDATA
)
pkgups=: 3 : 0
(pkgnew'') < pkglater''
)
pkgsearch=: 3 : 0
  +./"1 +./ y E."1&>"(0 _) 1{"1 PKGDATA
)
pkgshow=: 3 : 0
  y e.~ 1{"1 PKGDATA
)
setshowall=: 3 : 0
PKGDATA=: (<y) (<(I.DATAMASK);0) } PKGDATA
)
setshownew=: 3 : 0
ndx=. I. DATAMASK *. pkgnew''
PKGDATA=: (<y) (<ndx;0) } PKGDATA
)
setshowups=: 3 : 0
ndx=. I. DATAMASK *. pkgups''
PKGDATA=: (<y) (<ndx;0) } PKGDATA
)
splitlib=: 3 : 0
if. 0=#y do.
  2 $ <y return.
end.
msk=. masklib y
(msk#y) ; <(-.msk)#y
)
pacman_init=: 3 : 0
dat=. ADDONS #~ ({."1 ADDONS) e. {."1 ZIPS
if. 0=#dat do.
  dat=. i.0 6
else.
  ndx=. ({."1 ADDINS) i. {."1 dat
  ins=. ndx { (1 {"1 ADDINS),<''
  dat=. dat,.<''
  dat=. 0 5 1 3 4 2 {"1 dat
  dat=. ins 1 }"0 1 dat
end.
lib=. 'base library';(fmtver LIN);(fmtver 0 pick LIB);'base library scripts';LIBDESC;''
dat=. dat,lib
dat=. (<0),.dat
PKGDATA=: sort dat
nms=. 1 {"1 PKGDATA
nms=. ~. (nms i.&> '/') {.each nms
SECTION=: 'All';nms
DATAMASK=: (#PKGDATA) $ 1
EMPTY
)
init_console=: 3 : 0
  if. 0=#y do. y=. 'read' end.
  select. y
  fcase. 'edit';'server' do.
    if. -. checkaccess'' do. 0 return. end.
  case. 'read' do.
    readconfig''
    if. -. checkaddonsdir'' do. 0 return. end.
    setfiles''
    readlocal''
    pacman_init ''
    res=. 1
  case. do. res=. 0  
  end.
  if. y -: 'server' do. res=. getserver''  end.
  res
)
jpkg=: 4 : 0
  select. x
  case. 'history';'manifest' do.
    x showfiles_console y
  case. 'install' do.
    install_console y
  case. 'reinstall' do.
    remove_console y
    install_console y
  case. 'remove' do.
    remove_console y
  case. ;:'show search showinstalled shownotinstalled showupgrade status' do.
    x show_console y
  case. 'update'  do.
    updatejal ''
  case. 'upgrade' do.  
    upgrade_console y
  case. do.
    msg=. 'Valid options are:',LF
    msg=. msg,'  history, install, manifest, remove, reinstall, show, search,',LF
    msg=. msg,'  showinstalled, shownotinstalled, showupgrade, status,',LF
    msg,'  update, upgrade'
  end.
)
jpkg_z_=: 3 : 0
  'help' jpkg y
  :
  a=. conew 'jpacman'
  res=. x jpkg__a y
  destroy__a''
  res
)
