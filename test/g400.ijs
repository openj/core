NB. #y ------------------------------------------------------------------

tally =: {.@(,&1)@$
f     =: # -: tally

0 -: #''
0 -: #$0

1 -: #0
1 -: #'a'
1 -: #4
1 -: #3.5
1 -: #123j_45
1 -: #<'abc'

NB. Boolean
f (?5$4)$0
0 -: #0 5$0

NB. literal
f (?5$4)$'abc'
0 -: #0 5$'abc'

NB. integer
f (?5$4)$34
0 -: #0 5$34

NB. floating point
f (?5$4)$3.14
0 -: #0 5$3.14

NB. complex
f (?5$4)$3j4
0 -: #0 5$3j4

NB. boxed
f (?5$4)$<'asdf'
0 -: #0 5$<'asdf'

(3!:0 ]10x) -: 3!:0 # 10 20 30x
(3!:0 ]10x) -: 3!:0 # 5 % 10 20 30x


NB. x#y -----------------------------------------------------------------

copy =: ; @ (<@($ ,:)"_1)
f    =: # -: copy

3       (# -: copy) 'a'
3       (# -: copy) 'abcd'
1 2 3 4 (# -: copy) 'a'
1 2 3 4 (# -: copy) 'abcd'

0       (# -: copy) 12
0       (# -: copy) 21 13 14 15
0       (# -: copy) ?3 4 5$1e4
0 0 0 0 (# -: copy) 12
0 0 0 0 (# -: copy) 21 13 14 15

1       (# -: copy) 12
1       (# -: copy) 21 13 14 15
1       (# -: copy) ?3 4 5$1e4
1 1 1 1 (# -: copy) 12
1 1 1 1 (# -: copy) 21 13 14 15

m=: o.?4 5$100
3       (# -: copy) m
1 2 0 3 (# -: copy) m
0 2 3 0 (# -: copy) m

(3#x) -: (3.5-0.5)#x=:'asdf'

NB. NaN related tests
(2#_1e6 _1e6)    -: _1e6 _1e6 _1e6 _1e6
(3 2$_834524)    -: 1 0 1 0 1 # 5 2$_834524
(3 8$240 255{a.) -: 1 0 1 0 1 # 5 8$240 255{a.

'domain error' -: 'abc'   # etx 3 4 5
'domain error' -: 1 2 _3  # etx 3 4 5
'domain error' -: (2;3;4) # etx 'abc'
'domain error' -: 2 3.4   # etx i.2 3
'domain error' -: 3.4     # etx i.2 3
'domain error' -: 2 3j4.5 # etx i.2 3
'domain error' -: 3j4.5   # etx i.2 3

'length error' -: (,2)    # etx 4 5 6
'length error' -: 2 3     # etx 4 5 6
'length error' -: 2 3 4   # etx i.2 5
'length error' -: 4 5 6 7 # etx i.0

(<2 1e9 2e9 # etx 'abc') e. 'limit error';'out of memory'


NB. b#"r x  -------------------------------------------------------------

f1=: 3 : 0
 n=: y
 assert. (b=: ?n$2) (# -: copy) xx=: ?n$2
 assert. (b=: ?n$2) (# -: copy) xx=: a.{~?n$#a.
 assert. (b=: ?n$2) (# -: copy) xx=: a.{~?(n,7)$#a.
 assert. (b=: ?n$2) (# -: copy) xx=: ?n$1e9
 assert. (b=: ?n$2) (# -: copy) xx=: o.?n$1e9
 assert. (b=: ?n$2) (# -: copy) xx=: j./?(2,n)$1e9
 assert. (b=: ?n$2) (# -: copy) xx=: <"0 ?n$1e9
 assert. (b=: ?n$2) (# -: copy) xx=:    ?   n $100000x
 assert. (b=: ?n$2) (# -: copy) xx=: % /?(2,n)$100000x
 1
)

f1"0 ]100 101 102 103

f2=: 3 : 0
 n=: y
 assert. (b=: ?n$2) (#"1 -: copy"1) xx=: ?(3,n)$2
 assert. (b=: ?n$2) (#"1 -: copy"1) xx=: a.{~?(3,n)$#a.
 assert. (b=: ?n$2) (#"2 -: copy"2) xx=: a.{~?(3,n,7)$#a.
 assert. (b=: ?n$2) (#"1 -: copy"1) xx=: ?(3,n)$1e9
 assert. (b=: ?n$2) (#"1 -: copy"1) xx=: o.?(3,n)$1e9
 assert. (b=: ?n$2) (#"1 -: copy"1) xx=: j./?(2 3,n)$1e9
 assert. (b=: ?n$2) (#"1 -: copy"1) xx=: <"0 ?(3,n)$1e9
 assert. (b=: ?n$2) (#"1 -: copy"1) xx=:     ?(3,n) $100000x
 assert. (b=: ?n$2) (#"1 -: copy"1) xx=: % /?(2 3,n)$100000x
 1
)

f2"0 ]100 101 102 103

f3=: 4 : 0
 n=: x
 c=: y
 assert. (b=: ?n$2) (# -: copy) xx=: a.{~?(n,c)$#a.
 1
)

100 101 102 103 104 f3"0/ i.21

f4=: 4 : 0
 n=: x
 c=: y
 assert. (b=: ?n$2) (# -: copy) xx=: a{~?(n,c)$#a=: 0 1 255{a.
 1
)

100 101 102 103 104 f4"0/ i.21

''        -: (0$0) # ''
(i.3 0 5) -: (0$0) #"2 i.3 0 5

'length error' -: 1 0 1 #   etx i.4
'length error' -: 1 0 1 #"2 etx i. 4 5 6


NB. x#y, complex x ------------------------------------------------------

'aa    b'        -: 2j4 1 # 'ab'
3 3 0 0 0 0 4    -: 2j4 1 # 3 4

'aa    a'        -: 2j4 1 # 'a'
(2 4 2 4#'a b ') -: 2j4 #'ab'
'aa    '         -: 2j4 # 'a'

(1 0 2 4# ,/x,:"1[0) -: 1 2j4 # x=: i.2 3

f=: 4 : 'x#y'

x (f"1 -: #"1) y=: ?3 4 9$100 [ x=: j./?2 9$5
x (f"2 -: #"2) y=: ?3 9 4$100


NB. x#!.f y -------------------------------------------------------------

'aa____b'        -: 2j4 1 #!.'_' 'ab'
3 3 9 9 9 9 4    -: 2j4 1 #!.9[  3 4

'aa____a'        -: 2j4 1 #!.'_' 'a'
(2 4 2 4#'a_b_') -: 2j4   #!.'_' 'ab'
'aa____'         -: 2j4   #!.'_' 'a'

(1 0 2 4# ,/x,:"1[3j4) -: 1 2j4 #!.3j4 x=:i.2 3

'domain error' -: 9 3j1  #!.'a'  etx 4
'domain error' -: 1 2j3  #!.'a'  etx 'b';'c'
'domain error' -: 3j4    #!.4    etx 'sui generis'
'domain error' -: 5 3j5 4#!.4    etx ;:'Cogito, ergo'
'domain error' -: 1j7    #!.(<4) etx 'eleemosynary'
'domain error' -: 9 3j4  #!.(<4) etx i.2 3


NB. x#"r y --------------------------------------------------------------

f=: 4 : 'x#y'

1 0 2 (#"0 -: f"0) x=:?3 3 3 3$1e5
1 0 2 (#"1 -: f"1) x
1 0 2 (#"2 -: f"2) x
1 0 2 (#"3 -: f"3) x
1 0 2 (#"4 -: f"4) x

1 0 1 (#"0 -: f"0) x=:?3 3 3 3$1e5
1 0 1 (#"1 -: f"1) x
1 0 1 (#"2 -: f"2) x
1 0 1 (#"3 -: f"3) x
1 0 1 (#"4 -: f"4) x

0 (#"0 -: f"0) x=:?3 3 3 3$1e5
0 (#"1 -: f"1) x
0 (#"2 -: f"2) x
0 (#"3 -: f"3) x
0 (#"4 -: f"4) x

1 (#"0 -: f"0) x=:?3 3 3 3$1e5
1 (#"1 -: f"1) x
1 (#"2 -: f"2) x
1 (#"3 -: f"3) x
1 (#"4 -: f"4) x

2 (#"0 -: f"0) x=:?3 3 3 3$1e5
2 (#"1 -: f"1) x
2 (#"2 -: f"2) x
2 (#"3 -: f"3) x
2 (#"4 -: f"4) x

1 0 2 (#"0 -: f"0) x=:o.?1e6
1 0 2 (#"1 -: f"1) x

3 (#"0 -: f"0) x=:4 4 4$'antidisestablishmentarianism'
3 (#"1 -: f"1) x
3 (#"2 -: f"2) x
3 (#"3 -: f"3) x

(?5 2$10) (#    -: f"1 _) x=:2 5$;:'When eras die their legacies are left to strange police'
(?5 2$10) (#"_1 -: f"_1 ) y=:5 2$;:'Professors in New England guard the glory that was Greece'

1j2 3j4 0j5 (#"0 0 -: f"0 0) x=:(?3 3 3$3){;:'chirality paronomasiac onomatopoeia'
1j2 3j4 0j5 (#"0 1 -: f"0 1) x
1j2 3j4 0j5 (#"0 2 -: f"0 2) x
1j2 3j4 0j5 (#"0 3 -: f"0 3) x
1j2 3j4 0j5 (#"1 0 -: f"1 0) x
1j2 3j4 0j5 (#"1 1 -: f"1 1) x
1j2 3j4 0j5 (#"1 2 -: f"1 2) x
1j2 3j4 0j5 (#"1 3 -: f"1 3) x

(i.0 8  ) -: 3 1 4   #"1 i.0 3
(i.0 0 7) -: (i.0 5) #   5 7$'sesquipedalian'

(i.1e9     0) -: 1e4#   i.1e5   0
(i.1e9 2e4 0) -: 1e4#"2 i.1e9 2 0


4!:55 ;:'a b c copy f f1 f2 f3 f4 g m n tally x xx y '


