NB. built from project: source\api\sym2ijs\sym2ijs
NB. sym2ijs
NB.
NB. format:
NB.  path sym2ijs name
NB.
NB. e.g.
NB.  '\dev\defs\' sym2ijs 'hostdefs'
NB. see doc at end for details

NB. require 'files strings misc'

NB. =========================================================
include1=: 3 : 0
'#include ', y
)

NB. =========================================================
NB. integer
integer1=: 3 : 0
printf each ;: }. y
)

NB. =========================================================
NB. jcode
jcode1=: 3 : 0
TAB,'puts ("',(2 }. y),'");'
)

NB. =========================================================
printf=: 3 : 0
printf~ y
:
TAB,'printf ("',x,'=: %d\n",(int)',y,');'
)

NB. =========================================================
structure1=: 3 : 0
id=. deb 3 }. 0 pick y
sd=. (7 * 'struct ' -: 7 {. id) }. id
bal=. }. y
msk=. *. /\ ({.&> bal) e. 'f#'
r=. <(sd,'_sz') printf 'sizeof (',id,')'
r=. r, id&structure2 each msk # bal
(< S: 0 r), (-.msk) # bal
)

NB. =========================================================
structure2=: 4 : 0
if. 'f' ~: {. y do. y return. end.
id=. deb 2 }. y
r=. (id,'_off') printf 'offset(',x,',',id,')'
s=. (id,'_sz') printf 'sizeof(((',x,'*)0)->',id,')'
r;s
)


NB. =========================================================
j=. cutopen (0 : 0) rplc '~',TAB
#define offset(r,f) (((char*)&((r*)0)->f)-((char*)((r*)0)))
main(){
~printf ("NB. do not edit -- created by sym2ijs\n\n");
~printf ("cocurrent <'jdefs'\n\n");
)

SYMTXT=: cutopen j rplc '~',TAB

bx=: 3 : 'y#i.#y' NB.!
tolist=: 3 : ';y,each LF' NB.!

NB. =========================================================
NB. [path] sym2ijs name --- '\dev\defs\' sym2ijs 'netdefs'
NB. reads name.sym and creates name.c 
sym2ijs=: 3 : 0
'' sym2ijs y
:
dat=. 'b' fread jpath x,y,'.sym'
dat=. deb each dat
dat=. (';' ~: {.&> dat) # dat

NB. split off includes from main:
ndx=. (+. /\. '<' = {.&> dat) i. 0
hdr=. ndx {. dat
bal=. ndx }. dat
bal=. bal }.~ (bal ~: <'') i. 1

NB. includes:
ndx=. bx Q=:'<' = {.&> hdr
hdr=. (include1 each ndx { hdr) ndx } hdr

NB. structures:
msk=. 1,('t' = {.&> bal) +. (<'st') = 2 {.each bal
bal=. }. < S: 0 msk <@structure1;.1 '';bal

NB. integers:
ndx=. bx 'i' = {.&> bal
bal=. (integer1 each ndx { bal) ndx } bal
bal=. < S: 0 bal

NB. J code:
ndx=. bx 'J' = {.&> bal
bal=. (jcode1 each ndx { bal) ndx } bal
bal=. < S: 0 bal

NB. empties:
ndx=. bx 0 = # &> bal
bal=. (<TAB,'puts("");') ndx } bal

ftr=. <TAB,'exit (0);',LF,'}'
res=. tolist QQ=: hdr,SYMTXT,bal,ftr
res fwrites x,y,'.c'
)

doc=: 0 : 0 
sym2ijs - translate C type and constant declarations into J definitions
target_file sym2ijs source_file
for example: 'hostdefs.c' sym2ijs 'hostdefs.sym'

The original idea and implementation as a shell script and man page were
done by Martin Neitzel. This documentation is based on Martin's man page.

Converts header definitions given in C into equivalent J definitions.  It
expects a compact input format listing the symbols of interest and generates
the corresponding J script defining the same (or closely related) symbols.

There is no need to figure out C header values or offsets manually or
to hardwire those (usually system-dependent) values.

The purpose of this tool is portable J code sticking to APIs as defined in
c header files.

sym2ijs creates an intermediate C language program. This program
is compiled on the target machine and the resulting program, when run,
creates an ijs script with the appropriate J definitions for that target.

The input file most likely starts with the list of the required include files.

The first empty line in the input marks the transition from the header
section to the section with various directives.

Every input line is analyzed according to the character or word at the 
beginning of the line.  No line may be indented. The rest of the line may
employ arbitrary forms of white space. The following input line formats
are recognized:

<filename> - include the specified system header file

"filename" - include the specified local header file.

first emtpy line - switch from global section in the intermediary C program to the
main() function issuing all the print statements for the values. No header files may
be listed after this line. Other empty lines are preserved in the J script output.

i symbol ... - integer-typed symbol(s) defined as a C header constants or C variables.
Corresponding assignments to J symbols will be generated.

t typename - define the (J) symbol typename_sz to have the value of sizeof(typename) .

st  typename - a structure type is introduced, leading to a typename_sz
 
st struct  structtag - a structure type is introduced, leading to a typename_sz.
The struct keyword has to be used where only this type of defintion is used in
the header file.

An st line may be followed by f lines for fields in the structure.

f  fieldname - define fieldname_sz and the offset fieldname_off for a member
of the structure

; comments

C literal C code

J literal J code

# C preprocessor directive - passed to the intermediate C program allowing easy
conditional code.
)