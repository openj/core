NB. integer overflow in +/\
test=: 3 : 0
 yy=: 3$ >IF64{_2147483647;_9223372036854775807
 f=: (3 : '+/y')\
 g=: +/\
 assert. 3(f-:g)yy
 1
)

test''

 4!:55 ;: 'test yy f g'
