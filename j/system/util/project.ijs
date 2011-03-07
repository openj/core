coclass <'jp'
coinsert 'j'
defaultvalue=: 4 : 'if. _1 = 4!:0 <x do. (x)=: y end.'
index=: #@[ (| - =) i.
intersect=: e. # [
matchhead=: [ -: #@[ {. ]
towords=: ;:^:(_1 * 1 = L.)
decomment=: 3 : 0
dat=. <;._2 termLF toJ y
if. 2 > #dat do. y return. end.

com=. ('NB.'&-:)@(3&{.)&> dat
ncm=. com < (1|.0,}.com) +. (0,}._1|.com)
msk=. com +: ncm *. dat=a:
dat=. msk # dat

f=. 'NB.'&E. <: ~:/\@(e.&'''')
g=. #~ *./\@f
; (g each dat) ,each LF
)
ffoldername=: 3 : 0
p=. tofoldername_j_ y
if. '~' ~: {.p do. '';p return. end.
x=. ('/' e. p) + p i. '/'
(x{.p);x}.p
)
fixNB=: 3 : 0
x=. I. 'nb.' E. y
'NB' (0 1 +/~ x) } y
)
getprojfile=: 3 : 0
if. 0=#y do. '' return. end.
p=. remsep projname2path y
if. -. ProjExt -: (-#ProjExt) {. p do.
  p=. remsep p
  'f n'=. fpathname p
  p,'/',n,ProjExt
end.
)
getprojname=: 3 : 0
ProjectName,(0=#ProjectName)#ProjectPath
)
projname2path=: 3 : 0
if. '~'={. y do.
  jpath y
elseif. ('/'={.y) +: </ y i. ':/' do.
  jpath '~',y
elseif. do.
  y
end.
)
projfname=: 3 : 0
if. 0=#y do. '' return. end.
s=. jpathsep y
if. -. '/' e. s do.
  ProjectPath,'/',s
else.
  jpath s
end.
)
projsname=: 3 : 0
if. 0=#ProjectPath do. y return. end.
if. ProjectPath matchhead y do.
  (1+#ProjectPath) }. y
else.
  toprojectfolder y
end.
)
projssource=: 3 : 0
projread''
Source;<projsname each Source
)
PPScript=: jpath '~system/util/pp.ijs'
Project=: ProjectPath=: ProjectName=: ''
direrase=: 3 : 0
if. 0=#y do. return. end.
if. 0=#1!:0 y do. return. end.
if. 0=#d=. dirtreex y do. return. end.
d=. d \: # &> d
m=. ferase d
if. _1 e. m do.
  'Unable to delete: ',towords (m=_1)#d
end.
)
dirsubdirs=: 3 : 0
r=. 1!:0 (termsep jpathsep y),'*'
if. 0=#r do. '' return. end.
{."1 r #~ '-d' -:("1) 1 4{"1 > 4{"1 r
)
dirtreex=: 3 : 0
y=. jpathsep y
p=. (+./\. y = '/') # y
d=. 1!:0 y,('/' = {:y) # '*'
if. 0 = #d do. '' return. end.
a=. > 4 {"1 d
m=. 'd' = 4 {"1 a
f=. (<p) ,each {."1 d
if. 1 e. m do.
  f, ; dirtreex each (m#f) ,each <'/','*'
end.
)
fwritenew=: 4 : 0
dat=. ,x
if. dat -: fread y do. 0 return. end.
dat fwrite y
)
isdir=: 3 : 0
d=. 1!:0 y
if. 1 ~: #d do. 0 return. end.
'd' = 4 { 4 pick ,d
)
projread=: 3 : 0
projclear''
if. 0=#Project do. return. end.
projread1 Project
)
projread1_jp_=: 3 : 0
projclear''
Build=: 'build.ijs'
Run=: 'run.ijs'
Source=: ''
dat=. 'b' freads y
if. dat-:_1 do.
  Build=: projfname Build
  Run=: projfname Run return.
end.
dat=. dat #~ (<'NB.') ~: 3 {.each dat
if. 1 e. '=:' E. ;dat do.
  0!:100 ; dat ,each LF
  Source=: cutLF Source
else.
  Source=: dat
end.
Build=: projfname Build
Run=: projfname Run
Source=: projfname each extsrc each deb each Source -. a:
EMPTY
)
ProjHdr=: fixNB_jp_ 0 : 0
nb.
nb. defines list of source files.
nb. path defaults to project directory.
)
projwritenew=: 3 : 0
r=. 'NB. project: ',(getprojname''),LF,ProjHdr,LF
r fwrites y
)
toprojectfolder=: 3 : 0
if. 0=#y do. '' return. end.
r=. toprojectfolder1 y
if. L. y do. r else. >r end.
)
toprojectfolder1=: 3 : 0
res=. filecase@jpathsep each boxxopen y
rex=. I. '~' ~: {.&> res
if. 0=#rex do. res return. end.
if. #Folder do.
  pid=. termsep jpath '~',Folder
  for_i. rex do.
    nax=. termsep nam=. i pick res
    if. pid matchhead nax do.
      res=. (<'~',Folder,(<:#pid) }. nam) i} res
      rex=. rex -. i
    end.
  end.
end.
if. 0=#rex do. res return. end.
pus=. UserFolders,SystemFolders
pds=. {."1 pus
pps=. termsep each {:"1 pus
ndx=. \: # &> pps
pds=. ndx{pds
pps=. ndx{pps
len=. # &> pps
for_i. rex do.
  nam=. i pick res
  msk=. pps = len {. each <nam,'/'
  if. 1 e. msk do.
    ndx=. ((i. >./) msk # len) { I. msk
    nam=. ('~', > ndx { pds),(<: ndx { len) }. nam
    res=. (<nam) i } res
  end.
end.
res
)
touserfolder=: 3 : 0
p=. toprojectfolder y
if. '~' ~: {.p do. '' return. end.
f=. }. (p i.'/'){.p
p #~ (<f) e. {."1 UserFolders
)
gitcheck=: 3 : 0
0 < # 0 pick gitreadstatus''
)
gitgui=: 3 : 0
if. 0 = #ProjectPath do. 0 return. end.
0 0$gitshell 'git gui &'
)
gitreadstatus=: 3 : 0
if. IFUNIX *: 0 < #ProjectName do. '';'' return. end.
gitshell 'git status'
)
gitshell=: 3 : 0
p=. dquote remsep ProjectPath
if. IFWIN do.
  shell_jtask_ 'cd "',p,'"',LF,y
else.
  unixshell 'cd "',p,'"',LF,y
end.
)
gitstatus=: 3 : 0
if. 3=nc <'textview_z_' do.
  textview 0 pick gitreadstatus ''
end.
EMPTY
)
projclear=: 3 : 0
Build=: Run=: Source=: ''
)
projclose=: 3 : 0
projreset''
)
projinit=: 3 : 0
if. 0-:FolderTree do. setfolder_j_ Folder end.
projopen y,(0=#y) # >{.RecentProjects
)
projopen=: 3 : 0
projreset''
if. 0=#y do. return. end.
Project=: getprojfile y
ProjectPath=: }: 0 pick fpathname Project
projpathfolder ProjectPath
if. #Folder do.
  p=. (#jpath '~',Folder,'/') }. ProjectPath
  ProjectName=: Folder,'/',p
else.
  ProjectName=: ''
end.
projread''
recentproj_add_j_ Project
)
projpathfolder=: 3 : 0
p=. touserfolder y
f=. (p i. '/') {. p
if. ('~'={.f) *: (<}.f) e. {."1 UserFolders do.
  setfolder_j_ ''
else.
  setfolder_j_ }.f
end.
)
projreset=: 3 : 0
projclear''
Project=: ProjectPath=: ProjectName=: ''
)
projrun=: 3 : 0
if. #y do.
  p=. 0 pick fpathname getprojfile y
else.
  p=. ProjectPath,'/'
end.
load ::] p,Run
)
pp_today=: 2 }. [: ": [: <. 100 #. 3 {. 6!:0
pp_stamp=: [: ":@, 'r<0>2.0' (8!:2) _3 {. 6!:0
pp_unstamp=: ':' (2 5}"1) 1 1 0 1 1 0 1 1 (#^:_1"1) _6 {.&> ]
pic=: 4 : 0
'f p'=. fpathname y
path=. remsep f
d=. snapgetpath path
if. d -: 0 do. return. end.
d=. d,'/p',pp_today''
t=. d,'/',p
dat=. x,(pp_stamp''),EAV
if. _1 -: fread t do.
  if. -. pic_inidir d do. 0 return. end.
  old=. fread y
  if. -. _1 -: old do.
    dat=. old,(6#'0'),EAV,dat
  end.
end.
dat fappend t
)
pic_files=: 3 : 0
{."1 [1!:0 (snappath remsep y),'/p','/*',~pp_today''
)
pic_inidir=: 3 : 0
if. #1!:0 y do. 1 return. end.
h=. (y i: 'p') {. y
n=. {."1 [ 1!:0 h,'p*'
if. #n do.
  direrase h,'plast'
  n=. \:~ n -. <'plast'
  if. #n do.
    if. 1<#n do.
      direrase &> (<h) ,each }.n
    end.
    (h,'plast') frename h,0 pick n
  end.
end.
ss_mkdir y
)
pic_list=: 3 : 0
t=. y,(0=#y)#pp_today''
p=. (snappath each fpath each FolderTree) ,each <'/p*'
d=. 1!:0 each p
m=. I. 0 < # &> d
if. 0 = #m do. EMPTY return. end.
p=. ;t&pic_list1 each m
s=. >}."1 p
p=. ({."1 p),<'total'
(>p),.' ',.":s,+/s
)
pic_list1=: 4 : 0
fp=. (snappath fpath y pick FolderTree),'/p',x,'/'
d=. 1!:0 fp,'*'
if. 0=#d do. i. 0 3 return. end.
f=. {."1 d
c=. (EAV+/ .=fread) each (<fp) ,each f
s=. 2{"1 d
m=. (<'/',~y pick FolderIds),each f
m,.c,.s
)
pic_read=: 3 : 0
'f p'=. fpathname y
r=. fread (snappath remsep f),'/p',(pp_today''),'/',p
if. r -: _1 do. '' else. <;._2 r end.
)
pic_readx=: 3 : 0
'f n'=. y
_6 }. n pick pic_read f
)
ss_today=: 's' , 2 }. [: ": [: <. 100 #. 3 {. 6!:0
SnapTrees=: ''
snapfcopy=: 3 : 0
'source dest'=. y
if. IFWIN do.
  0 pick 'kernel32 CopyFileW i *w *w i' cd (uucp source);(uucp dest);0
else.
  if. 0 = fpathcreate fpath dest do. 0 return. end.
  if. _1 -: dat=. fread source do. 0 return. end.
  -. _1 -: dat fwrite dest
end.
)
snapgetpath=: 3 : 0
p=. snappath y
if. 0 = #1!:0 p do.
  if. -. ss_mkdir p do. 0 return. end.
  y fwrite p,'/dir.txt'
end.
p
)
snappath=: 3 : 0
jpath '~snap/.snp/',getsha1_jgtk_ y
)
snapshot=: 3 : 0
if. Snapshots=0 do. return. end.
snapshot1 y;(ss_today'');ProjectPath
)
snapshot_tree=: 3 : 0
if. Snapshots=0 do. return. end.
if. (<Folder_j_) e. SnapTrees do. return. end.
snapshot1 &> (<0;ss_today'') (,<@fpath) each y
empty SnapTrees_jp_=: SnapTrees,<Folder_j_
)
snapshot1=: 3 : 0
'force today path'=. y
p=. snapgetpath path
if. p = 0 do. return. end.
p=. p,'/'
d=. 1!:0 p,'s*'
pfx=. p,today
if. 0=#d do. path ss_make pfx,'001' return. end.
d=. \:~ {."1 d #~ 'd' = 4{"1 > 4{"1 d
last=. 0 pick d
iftoday=. today -: 7 {. last
if. force do.
  if. (p,last) ss_match ProjectPath do.
    ss_info 'Last snapshot matches current project.'
    0 return.
  end.
  if. iftoday do.
    f=. pfx,_3 {. '00',": 1 + 0 ". _3 {. last
  else.
    f=. pfx,'001'
  end.
  path ss_make f
  ss_info 'New snapshot: ',1 pick fpathname f
  
else.
  if. iftoday do. 0 return. end.
  if. (p,last) ss_match path do. 0 return. end.
  path ss_make pfx,'001'
end.
d=. (Snapshots-1) }. d
for_s. d do.
  f=. p,(>s),'/'
  1!:55 f&, each {."1 [ 1!:0 f,'*'
  1!:55 <f
end.

1
)
ss_cleanup=: 3 : 0
if. 1~:#y do.
  r=. ''
  r=. r,'0 = list invalid snapshot directories',LF
  r=. r,'1 = list non-existent projects with snapshots',LF
  r=. r,'100 = remove invalid snapshot directories',LF
  r=. r,'101 = remove snapshots for non-existent projects'
  smoutput r return.
end.
'd r n'=. ss_dirs''
select. y
case. 0 do.
  d #~ n=2
case. 1 do.
  r #~ n=1
case. 100 do.
  ; {. &> rmdir_j_ each d #~ n=2
case. 101 do.
  ; {. &> rmdir_j_ each d #~ n=1
end.
)
ss_dir=: 3 : 0
p=. jpath '~snap/.snp/'
d=. 1!:0 p,'*'
d=. ('d' = 4 {"1 > 4 {"1 d) # {."1 d
d=. (<p) ,each d
d;<(1!:1 :: (''"_))@< each d ,each <'/dir.txt'
)
ss_dirs=: 3 : 0
'd r'=. ss_dir''
s=. /:r
r=. s{r
d=. s{d
m=. 0 < #&> r
n=. 2 * -. m
r=. m#r
p=. (*./\.@:~:&'/' # ]) each r
p=. r ,each '/' ,each p ,each <ProjExt
n=. (-. fexist &> p) (I.m) } n
r=. (tofoldername_j_ each r) (I.m) } (#d) # <''
d;r;n
)
ss_files=: 3 : 0
t=. 1!:0 y,'*'
if. 0=#t do. return. end.
att=. > 4{"1 t
msk=. ('h' = 1{"1 att) +: 'd' = 4{"1 att
t=. /:~ msk # t
if. _1 = 4!:0 <'ss_exclude' do.
  exs=. '.' ,each SnapshotX_j_
  ss_exclude_jp_=: [: +./ exs & ((1 e. E.) &>/)
end.
t #~ -. ss_exclude {."1 t
)
ss_find=: 3 : 0
y=. y,(0=#y)#ProjectPath
'd r'=. ss_dir''
ndx=. r i. <jpath remsep_j_ y
ndx pick d,<'not found: ',y
)
ss_info=: 3 : 0
sminfo 'Snapshot';y
)
ss_list=: 3 : 0
if. 0=#y do. '' return. end.
p=. snappath projname2path y
d=. 1!:0 p,'/s*'
if. #d do.
  d=. d #~ 'd' = 4 {"1 > 4 {"1 d
  \:~ {."1 d
else.
  ''
end.
)
ss_make=: 4 : 0
fm=. x,'/'
to=. y,'/'
if. 0 = ss_mkdir to do. 0 return. end.
f=. {."1 ss_files fm
fm=. (<fm) ,each f
to=. (<to) ,each f
res=. snapfcopy"1 fm ,. to
if. 0 e. res do.
  txt=. 'Unable to copy:',LF2,tolist (res=0)#fm
  ss_info txt
end.
*./ res
)
ss_mkdir=: 3 : 0
if. 0 -: fpathcreate y do.
  if. 1 = # 1!:0 y do. 1 return. end.
  ss_info 'Unable to create snapshot directory: ',y
  0 return.
end.
arw=. 'rw' 0 1 } 1!:7 <y
if. 0 -: arw 1!:7 :: 0: <y do.
  ss_info 'Unable to set read/write attributes for snapshot directory.'
  0 return.
end.
if. -.IFUNIX do.
  ph=. 'h' 1 } 1!:6 <y
  if. 0 -: ph 1!:6 :: 0: <y do.
    ss_info 'Unable to set hidden attribute for snapshot directory.'
  end.
end.

1
)
ss_match=: 4 : 0
x=. termsep x
y=. termsep y
a=. ss_files x
b=. ss_files y
ra=. #a
rb=. #b
if. 0 e. ra,rb do.
  ra = rb return.
end.
fa=. {."1 a
fb=. {."1 b
if. -. fa -: fb do. 0 return. end.
if. -. (2 {"1 a) -: (2 {"1 b) do. 0 return. end.
fx=. x&, each fa
fy=. y&, each fa
(<@(1!:1) fy) -: <@(1!:1) fx
)
ss_removesnaps=: 3 : 0
direrase each snappath each fpath each FolderTree
)
ss_state=: 3 : 0
'd r n'=. ss_dirs''
r=. 'valid existent, valid nonexistent, invalid:',LF
r=. r,":+/ n =/ 0 1 2
)
readprojectsource=: 3 : 0
pn=. ('~'={.y) }. y
f=. getprojfile y
cocurrent 'jptemp'
coinsert 'jp'
ProjectPath=: fpath f
ProjectName=: ''
projread1 f
r=. Source
cocurrent 'jp'
coerase <'jptemp'
r
)
readsource1=: 4 : 0
s=. readprojectsource y
dat=. freads each s
if. (<_1) e. dat do.
  fls=. ; ' ' ,each toprojectfolder each s #~ (<_1) = dat
  sminfo 'Project Manager';'Unable to read:',fls
  _1 return.
end.
dat=. ;dat
if. x do. decomment_jp_ dat end.
)
writesource1=: 4 : 0
'p t'=. y
dat=. x readsource1 p
if. _1 -: dat do. return. end.
dat fwritenew jpath t
EMPTY
)

readsource=: 0&readsource1
readsourcex=: 1&readsource1
writesource=: 0&writesource1
writesourcex=: 1&writesource1
