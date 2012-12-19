NB. DLL call ------------------------------------------------------------

load'dll'

3 : 0 ''
if. 0=4!:0<'libtsdll' do. 1[lib=: libtsdll return. end.
t=. >IF64{'32';'64'
s=. >(UNAME-:'Darwin'){'.so';'.dylib'
if. IFUNIX do.
 lib=: 'libtsdll',t,s
else.
 if. IF64 do.
  lib=: 'tsdll.dll'
 else.
  lib=: 'tsdll.dll'
 end.
end.
lib=: lib,' '
1
)

dcd=: 4 : '(lib,x) cd y'

NB. test integer types
a=: 4 u: +/401 402 403
b=: 4 u: 402 403
('&';(,'&');'a';'bc')=   'cbasic c *c c *c' dcd (,'a');'a';'bc'
(a;(,a);(4 u: 401);b)=   'wbasic w *w w *w' dcd (,4 u: 400);(4 u: 401);4 u: 402 403
(9;(,9);2;3 4)=          'sbasic s *s s *s' dcd (,2);2;3 4
(9;(,9);2;1 ic 3 4)=     'sbasic s *s s *s' dcd (,2);2;1 ic 3 4  NB. shorts in chars
(9;(,9);2;3 4)=          'ibasic i *i i *i' dcd (,2);2;3 4
(9;(,.9);2;,.3 4)=       'ibasic i *i i *i' dcd (,.2);2;,.3 4 NB. allow rank>1
(9;(,9);2;3 4)=          'xbasic x *x x *x' dcd (,2);2;3 4
(2;(,2);1;0 1)=          'ibasic i *i i *i' dcd (,1);1;0 1 NB. boolean promotion to int

NB. declaration (left argument) and parameter (right argument) checking
(0 0 -: cder '') *. (9;(,9);2;3 4) -: 'ibasic i *i i *i' dcd (,2);2;3 4  NB. base working example

'limit error'  -: (lib,'ibasic i *i i *i',2300$' '  ) cd etx (,2);2;3 4
'limit error'  -: ((2300$' '),lib,'ibasic i *i i *i') cd etx (,2);2;3 4

(1 0 -: cder '') *. 'domain error' -: ((1200$'x'),' proc i i i') cd etx 2;3
(1 0 -: cder '') *. 'domain error' -: ('xxxx proc i i i'       ) cd etx 2;3
(1 0 -: cder '') *. 'domain error' -: ('xxxx proc i i i'       ) cd etx 2;3

(2 0 -: cder '') *. 'domain error' -: (lib,(1200$'x'),' i i i' ) cd etx 2;3
(2 0 -: cder '') *. 'domain error' -: (lib,'xxxx i i i'        ) cd etx 2;3
(2 0 -: cder '') *. 'domain error' -: (lib,'xxxx i i i'        ) cd etx 2;3

(4 0 -: cder '') *. 'domain error' -: (lib,'ibasic ',400$'i '  ) cd etx 2;3
(4 0 -: cder '') *. 'domain error' -: 'ibasic i *i i *i' dcd etx (,2);2;3 4;'abcd'
(4 0 -: cder '') *. 'domain error' -: 'ibasic i *i i *i' dcd etx (,2);2

(5 0 -: cder '') *. 'domain error' -: 'ibasic I *i i *i' dcd etx (,2);2;3 4
(5 1 -: cder '') *. 'domain error' -: 'ibasic i *I i *i' dcd etx (,2);2;3 4
(5 2 -: cder '') *. 'domain error' -: 'ibasic i *i I *i' dcd etx (,2);2;3 4
(5 3 -: cder '') *. 'domain error' -: 'ibasic i *i i *I' dcd etx (,2);2;3 4

(6 0 -: cder '') *. 'domain error' -: 'ibasic i *i i *i' dcd etx ('abc');2  ;3 4
(6 1 -: cder '') *. 'domain error' -: 'ibasic i *i i *i' dcd etx (,2)   ;4.5;3 4
(6 2 -: cder '') *. 'domain error' -: 'ibasic i *i i *i' dcd etx (,2)   ;2  ;3j4 5

NB. 'rank error' -: 'ibasic i *i i *i' dcd etx ,:(,2);2;3 4
NB. 'rank error' -: 'ibasic i *i i *i' dcd etx ,.(,2);2;3 4

NB. mema memory
add=: mema 2*IF64{4 8
3 4 memw add,0,2,JINT
(9;(,9);2;<<add)=         'xbasic x *x x *x' dcd (,2);2;<<add
0=memf add

NB. l type is same as x on J64 and and error on J32
3 : 0''
if. IF64 do.
 assert. (9;(,9);2;3 4) =  'xbasic l *l l *l' dcd (,2);2;3 4
else.
 assert. 'domain error'-:  'xbasic l *l l *l' dcd etx (,2);2;3 4
 assert. 5 0 -: cder ''  NB. error 5, result/arg declaration 0
end.
)

NB. pointer result
address=. 0{::'pc *c' dcd ''
'test'-:memr address,0,_1
address=. 0{::'pc *' dcd ''
'test'-:memr address,0,_1

NB. d and *d results and *d arg
(6.6;3;1.1 2.2 3.3;,6.6)= 'dipdpd d i *d *d' dcd 3;1.1 2.2 3.3;,1.1
(6.6;3;(,.1.1 2.2 3.3);,.6.6)= 'dipdpd d i *d *d' dcd 3;(,.1.1 2.2 3.3);,.1.1

NB. f and *f results and *f arg - convert in place
NB. 1.5 2.4 3.5 doubles convert exactly to floats
(7.5;3;1.5 2.5 3.5;,7.5)= 'fipfpf f i *f *f' dcd 3;1.5 2.5 3.5;,1.1
(7.5;3;(,.1.5 2.5 3.5);,.7.5)= 'fipfpf f i *f *f' dcd 3;(,.1.5 2.5 3.5);,.1.1
(7.5;3;(1 fc 1.5 2.5 3.5);,7.5)= 'fipfpf f i *f *f' dcd 3;(1 fc 1.5 2.5 3.5);,1.1 NB. shorts in chars
(7.5;3;(,.1 fc 1.5 2.5 3.5);,.7.5)= 'fipfpf f i *f *f' dcd 3;(,.(1 fc 1.5 2.5 3.5));,.1.1 NB. shorts in chars

NB. verify that double to float loses bits
6.6~:         0{::'fipfpf f i *f *f' dcd 3;1.1 2.2 3.3;,1.1

NB. alternate (__cdecl) calling convention
(24;23) -: 'altinci + i i'  dcd 23

NB. *j
(1.6;a)= 'complex d i *j' dcd a=.0;,1.6j2.7
(2.7;a)= 'complex d i *j' dcd a=.1;,1.6j2.7

NB. test f and d results and scalars
(<1.5)= 'f f' dcd ''
(<1.5)= 'd d' dcd ''
(3.3;1.1;2.2    )= 'ddd d d d' dcd 1.1;2.2
(6.6;1.1;2.2;3.3)= 'dddd d d d d' dcd 1.1;2.2;3.3
(4;1.5;2.5)= 'fff f f f' dcd 1.5;2.5
z=:'fd d f d f d *f *d' dcd 1.1;1.2;1.3;1.4;(6.6,6.6);7.7,7.7
(1.1;1.2;1.3;1.4;1.2 1.4)= 1 2 3 4 6{z
0.00001>5.0 1.1 1.3-;0 5{z

(+/>yy)=>{.'dx0 d x d'       dcd yy=:12;12.5
(+/>yy)=>{.'dx1 d d x'       dcd yy=:12.5;12
(+/>yy)=>{.'dx2 d x d x'     dcd yy=:12;12.5;13
(+/>yy)=>{.'dx3 d d x d'     dcd yy=:12.5;12;13.6
(+/>yy)=>{.'dx4 d x d x d'   dcd yy=:12;12.5;13;15.4
(+/>yy)=>{.'dx5 d d x d x'   dcd yy=:12.5;12;13.6;7
(+/>yy)=>{.'dx6 d x d x d x' dcd yy=:12;12.5;13;15.4;9
(+/>yy)=>{.'dx7 d d x d x d' dcd yy=:12.5;12;13.6;7;23.7

td=: 16$'d '
(  +/>yy)=>{.z=:('d1 d ',td) dcd yy=:<"0 [ 1.3*?8#10
(<.+/>yy)=>{.z=:('d2 x ',td) dcd yy=:<"0 [ 1.3*?8#10

td1a=: 18$'d '

3 : 0''
try.
 (+/>yy)=>{.z=:('d1a d ',td1a) dcd yy=:<"0 [ 1.3*?9#10
catch.
 *./IF64,IFUNIX,7 0-:cder''
end.
)

td3=: 32$'d x '
(+/>yy)=>{.z=:('d3 d ',td3) dcd yy=:16$12.3;4
td4=: 32$'d i '
(+/>yy)=>{.z=:('d4 d ',td4) dcd yy=:16$12.3;4

xx=:'d5 d d i d i d i d *d *f *x *i'
(+/;yy)=>{.z=: xx dcd yy=:1.1;2;3.3;4;5.5;6;7.7;2.2 3.3;3.3 4.4;23 24;46 47

tf=: 16$'f '
(<.+/>yy)=<.>{.z=:('f1 f ',tf ) dcd yy=:<"0 [ 1.375*?8#10
(<.+/>yy)=  >{.z=:('f2 x ',tf ) dcd yy=:<"0 [ 1.375*?8#10
tf3=: 32$'f x '
(<.+/>yy)=<.>{.z=:('f3 f ',tf3) dcd yy=:16$12.3;4

NB. test scalar boolean and integer promotion to double
(0;0;0)='ddd d d d' dcd 0;0
(2;1;1)='ddd d d d' dcd 1;1
(5;2;3)='ddd d d d' dcd 2;3
8=3!:0 >'ddd d d d' dcd 2;3

NB. test scalar boolean and integer promotion to float (double then downconverted)
(0;0;0)='fff f f f' dcd 0;0
(2;1;1)='fff f f f' dcd 1;1
(5;2;3)='fff f f f' dcd 2;3
8=3!:0 >'fff f f f' dcd 2;3

NB. test boolean and integer lists promoted to double
'v0 v1 v2 v3 v4 v5'=.(2.2-2.2)+i.6 NB. this works
'v0 v1 v2 v3 v4 v5'=.i.6
(6;0;1;2;3;0 2 4;1 3 5)-:'fd d f d f d *f *d' dcd v0;v1;v2;v3;(3$v4);3$v5

NB. use of > parameter
24        -: 'altinci >+ i i' dcd 23
(>:x)     -: 'altinci >+ i i' dcd ,. x=: 17 ?@$ 1e6
(>:x)     -: 'altinci >+ i i' dcd ,. <"0 x

(+/"1 x)  -: 'ddd > d d d'    dcd x=: 17 2 ?@$ 0
(+/"1 x)  -: 'ddd > d d d'    dcd <"0 x
(+/"1 x)  -: 'ddd > d d d'    dcd x=: 17 2 ?@$ 2
(+/"1 x)  -: 'ddd > d d d'    dcd <"0 x
(+/"1 x)  -: 'ddd > d d d'    dcd x=: 17 2 ?@$ 100
(+/"1 x)  -: 'ddd > d d d'    dcd <"0 x
(+/"1 x)  -: 'ddd > d d d'    dcd x=: (-~0j5)+17 2 ?@$ 0
(+/"1 x)  -: 'ddd > d d d'    dcd <"0 x

(+/"1 x)  -: 'fff > f f f'    dcd x=: 1024 %~ 17 2 ?@$ 1e4
(+/"1 x)  -: 'fff > f f f'    dcd x=: 17 2 ?@$ 2
(+/"1 x)  -: 'fff > f f f'    dcd x=: 17 2 ?@$ 100
(+/"1 x)  -: 'fff > f f f'    dcd x=: (-~0j5)+1024 %~ 17 2 ?@$ 1e4

(+/"1 x) -: 'dx0 > d x d'       dcd x=: 7 2 ?@$ 9 0
(+/"1 x) -: 'dx1 > d d x'       dcd x=: 7 2 ?@$ 0 9
(+/"1 x) -: 'dx2 > d x d x'     dcd x=: 7 3 ?@$ 9 0 9
(+/"1 x) -: 'dx3 > d d x d'     dcd x=: 7 3 ?@$ 0 9 0
(+/"1 x) -: 'dx4 > d x d x d'   dcd x=: 7 4 ?@$ 9 0 9 0
(+/"1 x) -: 'dx5 > d d x d x'   dcd x=: 7 4 ?@$ 0 9 0 9
(+/"1 x) -: 'dx6 > d x d x d x' dcd x=: 7 5 ?@$ 9 0 9 0 9
(+/"1 x) -: 'dx7 > d d x d x d' dcd x=: 7 5 ?@$ 0 9 0 9 0


td=: 16$'d '
(+/"1 x)  -: ('d1 >d ',td) dcd x=: 17 8?@$ 0

(6 0 -: cder '') *. 'domain error' -: 'ddd > d d d' dcd etx 'ab'

NB. space usage

s0=: 7!:0 ''
s1=: 7!:0 ''
yy=: <"0 ] 8 ?.@$ 0
4!:55 ;:'yy'
xx=: lib,'f1 f ',16$'f '
9 = # xx 15!:0 <"0 ]8 ?@$ 0

s0=: 7!:0 ''
9 = # xx 15!:0 <"0 ]8 ?@$ 0
s1=: 7!:0 ''
s0 -: s1

s0=: 7!:0 ''
1 [ 100 (6!:2) 'xx 15!:0 <"0 ]8 ?@$ 0'
s1=: 7!:0 ''
s0 -: s1

s0=: 7!:0 ''
yy=: <"0 ] 8 ?.@$ 0
1 [ 100 (6!:2) 'xx 15!:0 yy'
yy -: <"0 ] 8 ?.@$ 0
4!:55 ;:'yy'
s1=: 7!:0 ''
s0 -: s1


f=: 3 : 0
 if. (9!:12 '') e. 6 do.  NB. do only under Windows
  'ole32.dll CoCreateGuid i *c' 15!:0 y
 else.
  0;16$' '
 end.
)

('';,16) = $&.> x=: f  <16$' '
('';,16) = $&.> x=: f ,<16$' '


NB. 0 procaddress
xbasic_add=: ":>{.'xbasic_add x' dcd ''
(9;(,9);2;3 4) = ('0 ',xbasic_add,' x *x x *x') cd (,2);2;3 4

(2 0 -: cder '') *. 'domain error' -: '0  1e4 x x' cd etx (,2);2;3 4
(2 0 -: cder '') *. 'domain error' -: '0 _1e4 x x' cd etx (,2);2;3 4
(2 0 -: cder '') *. 'domain error' -: '0 abc  x x' cd etx (,2);2;3 4
(2 0 -: cder '') *. 'domain error' -: '0 34aa x x' cd etx (,2);2;3 4

(2 0 -: cder '') *. 'domain error' -: ('0  ',(>IF64{'2333444555';19$'93'),' x x') cd etx (,2);2;3 4
(2 0 -: cder '') *. 'domain error' -: ('0 _',(>IF64{'2333444555';19$'93'),' x x') cd etx (,2);2;3 4

NB. 1 procindex - 0 is objxxx and 1 is objddd
obj_add=:    <>{.'obj_add x' dcd ''
5    = >{.'objxxx x * x x' dcd obj_add;2;3
5.75 = >{.'objddd d * d d' dcd obj_add;2.5;3.25
5    = >{.'1 0 x * x x'     cd obj_add;2;3
5.75 = >{.'1 1 d * d d'     cd obj_add;2.5;3.25

5    = >{.'1 0 x x x x'     cd (>obj_add);2;3
5    = >{.'1 0 x x x x'     cd (>obj_add),2 3
5    = >{.'1 0 x x x x'     cd (>obj_add),2 3+-~0.5

5.75 = >{.'1 1 d x d d'     cd (>obj_add);2.5;3.25
5.75 = >{.'1 1 d x d d'     cd (>obj_add),2.5 3.25
55   = >{.'1 1 d x d d'     cd (>obj_add),22 33

(2 0 -: cder '') *. 'domain error' -: '1 _10000 x * x x'  cd etx obj_add;2;3
(2 0 -: cder '') *. 'domain error' -: '1 1e2    x * x x'  cd etx obj_add;2;3
(2 0 -: cder '') *. 'domain error' -: '1 abc    x * x x'  cd etx obj_add;2;3
(2 0 -: cder '') *. 'domain error' -: '1 34aa   x * x x'  cd etx obj_add;2;3

(2 0 -: cder '') *. 'domain error' -: ('1 ',(>IF64{'2333444555';19$'93'),' x * x x')  cd etx obj_add;2;3

(5 1 -: cder '') *. 'domain error' -: '1 0      x *d x x' cd etx obj_add;2;3
(5 1 -: cder '') *. 'domain error' -: '1 0      x *x x x' cd etx obj_add;2;3
(5 1 -: cder '') *. 'domain error' -: '1 0      x d  x x' cd etx obj_add;2;3
(5 1 -: cder '') *. 'domain error' -: '1 0      x'        cd etx obj_add;2;3

(6 0 -: cder '') *. 'domain error' -: '1 0      x x  x x' cd etx obj_add   ;2  ;3
(6 0 -: cder '') *. 'domain error' -: '1 0      x *  x x' cd etx (>obj_add);2  ;3
(6 0 -: cder '') *. 'domain error' -: '1 0      x *  x x' cd etx (>obj_add),2   3
(6 1 -: cder '') *. 'domain error' -: '1 0      x *  x x' cd etx obj_add   ;'2';3
(6 2 -: cder '') *. 'domain error' -: '1 0      x *  x x' cd etx obj_add   ;2  ;'3'


4!:55 ;:'a add address b dcd f lib obj_add pc s0 s1 td td1a td3 td4 tf tf3'
4!:55 ;:'v0 v1 v2 v3 v4 v5 x xbasic_add xx yy z'


