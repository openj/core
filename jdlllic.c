/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/* encode/decode routines - license keys and ijl                           */
#if defined _WIN32 && !OPENJ
#include "..\jsrc\j.h"
#else
#include "j.h"
#endif

F1(jtlock1){ASSERT(0,EVDOMAIN);} /* no encode */

F2(jtlock2){ASSERT(0,EVDOMAIN);} /* no decode */

F2(jtunlock2){R w;} /* leave alone */
