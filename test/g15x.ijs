NB. 15!: ----------------------------------------------------------------

pc=:(9!:12 '') e. 2 6     NB. works on Windows only

NB. a small memory leak is expected on the next line
2 = {:15!:1 ((15!:8) 10),0 5 4  NB. reference count

require'socket'
require 'dll'         NB. DLL utils


3 : 0''
if. pc do.
 require 'winapi'      NB. API utils
else.
 winset=:1:
end.
1
)

winset 'CREATE_NEW FILE_BEGIN FILE_CURRENT FILE_END GENERIC_READ GENERIC_WRITE'
winset 'OPEN_EXISTING'

cderx     =: 15!:11

Fclose    =: fclose    =: >@{.@('kernel32 CloseHandle i i'             &(15!:0))
Fdelete   =: fdelete   =: >@{.@('kernel32 DeleteFileA i *c'            &(15!:0))
Fdeletedir=: fdeletedir=: >@{.@('kernel32 RemoveDirectoryA i *c'       &(15!:0))
Fcreate   =:              >@{.@('kernel32 CreateFileA i *c i i * i i i'&(15!:0))
Fcreatedir=:              >@{.@('kernel32 CreateDirectoryA i *c *'     &(15!:0))
Fsize     =:              >@{.@('kernel32 GetFileSize i i *i'          &(15!:0))
Fwrite    =:              >@{.@('kernel32 WriteFile i i * i *i *'      &(15!:0))
Fsetptr   =:              >@{.@('kernel32 SetFilePointer i i i *i i'   &(15!:0))
Fcopyto   =:              >@{.@('kernel32 CopyFileA i *c *c i'         &(15!:0))
Fmoveto   =:              >@{.@('kernel32 MoveFileA i *c *c'           &(15!:0))
Fread     =:                    'kernel32 ReadFile i i * i *i *'       &(15!:0)

fcopyto   =: 4 : 'Fcopyto x,y,<0'
fmoveto   =: 4 : 'Fmoveto x,y'
fcreatedir=: 3 : 'Fcreatedir y,<<0'
fsize     =: 3 : 'Fsize y;<<0'
fsetptr   =: 4 : '>{.Fsetptr x;y;(<0);FILE_BEGIN'

fcreate=: 3 : 0   NB. fcreate name
 >{.Fcreate y,(GENERIC_READ+GENERIC_WRITE);0;(<0);CREATE_NEW   ;0;0
)
 
fopen  =: 3 : 0   NB. fopen name
 >{.Fcreate y,(GENERIC_READ+GENERIC_WRITE);0;(<0);OPEN_EXISTING;0;0
)
 
fwrite =: 4 : 0   NB. string fwrite handle
 Fwrite y;x;(#x);(,0);<<0
)

fread  =: 3 : 0   NB. fread handle
 y fsetptr 0
 n=. fsize y
 >2{Fread y;(n#' ');n;(,0);<<0
)

test=: 3 : 0   NB. windows only
if. pc do.
assert. 1 -: fcreatedir <'testtemp'
assert. 0 -: fdelete <'testtemp\non_existent_file'
assert. 2 -: >{.cderx ''

assert. _1 ~: h=: fcreate <'testtemp\test.jnk'

s=: 'boustrophedonic paracletic kerygmatic'
assert. 1 -: s fwrite h

assert. (#s) -: fsize h
assert. s -: fread h

i=: ?#s
t=: 'professors in New England guard the glory that was Greece'
assert. i -: h fsetptr i

assert. 1 -: t fwrite h
assert. (i+#t) -: fsize h
assert. ((i{.s),t) -: fread h
assert. 1 -: fclose h

assert. 1 -: fcreatedir <'testtemp\tempdir'

assert. (<'testtemp\test.jnk') fcopyto <'testtemp\test1.jnk'
assert. _1 ~: h=: fopen <'testtemp\test1.jnk'
assert. ((i{.s),t) -: fread h
assert. 1 -: fclose h

assert. (<'testtemp\test1.jnk') fmoveto <'testtemp\tempdir\test2.jnk'
assert. _1 ~: h=: fopen <'testtemp\tempdir\test2.jnk'
assert. ((i{.s),t) -: fread h
assert. 1 -: fclose h

assert. 1 -: fdelete <'testtemp\test.jnk'

assert. 0 -: fdeletedir <'testtemp\tempdir'
assert. (>{.cderx '') e. 5 145
assert. 1 -: fdelete <'testtemp\tempdir\test2.jnk'
assert. 1 -: fdeletedir <'testtemp\tempdir'
assert. 1 -: fdeletedir <'testtemp'
end.
1
)

test ''

0 -: sdclose_jsocket_ >1{sdsocket_jsocket_''  NB. all systems

t=: 100 ?@$ 1e6
t -:      15!:1 (15!:14 <'t'),0,(*/$t),3!:0 t
t=: 100 4 ?@$ 0
t -: ($t)$15!:1 (15!:14 <'t'),0,(*/$t),3!:0 t

'domain error' -: 15!:6  etx <'test'
'domain error' -: 15!:6  etx ;:'t test'
'domain error' -: 15!:14 etx <'test'
'domain error' -: 15!:14 etx ;:'t test'

'value error'  -: 15!:6  etx <'undefinedname'
'value error'  -: 15!:6  etx ;:'t undefinedname'
'value error'  -: 15!:14 etx <'undefinedname'
'value error'  -: 15!:14 etx ;:'t undefinedname'

4!:55 ;:'CREATE_NEW FILE_BEGIN FILE_CURRENT FILE_END GENERIC_READ '
4!:55 ;:'GENERIC_WRITE OPEN_EXISTING '
4!:55 ;:'Fclose Fcopyto Fcreate Fcreatedir Fdelete Fdeletedir Fmoveto Fread '
4!:55 ;:'Fsetptr Fsize Fwrite '
4!:55 ;:'cderx fclose fcopyto fcreate fcreatedir fdelete fdeletedir fmoveto '
4!:55 ;:'fopen fread fsetptr fsize fwrite '
4!:55 ;:'h i pc s t test'


