NB. J profile
NB. JFE sets BINPATH_z_ and ARGV_z_
NB. add your sentences in startup.ijs

systype=. 9!:12''
jpathsep_z_=: '/'&(('\' I.@:= ])}) NB. convert to / separator

NB. create SystemFolders
install=. '${CMAKE_INSTALL_PREFIX}'
bin=.     install,'/bin'
addons=.  '${DATA_INSTALL_PREFIX}','/addons'
system=.  '${DATA_INSTALL_PREFIX}','/system'
tools=.   '${DATA_INSTALL_PREFIX}','/tools'
home=.    >(systype-5){(2!:5'HOME');2!:5'USERPROFILE'

userx=.   '\j',('64-'#~16={:$3!:3[2),'701-user'
user=.    home,userx
break=.   user,'/break'
snap=.    user,'/snap'
temp=.    user,'/temp'
config=.  user,'/config'
ids=. ;:'addons bin break config home install snap system tools temp user'

0!:0 :: ] <jpathsep '${DATA_INSTALL_PREFIX}','/profilex.ijs' NB. override

SystemFolders_j_=: ids,.jpathsep@".&.>ids

md=. 3 : 0 NB. recursive makedir
a=. jpathsep y,'/'
if. -.#1!:0 }:a do.
 for_n. I. a='/' do. 1!:5 :: [ <n{.a end.
end.
)

NB. try to ensure user folders exist
md user,'/projects'
md temp
md break
md config
md snap

NB. boot up J and load startup.ijs if it exists
0!:0 <jpathsep system,'/util/boot.ijs'
