
Building J from Jsoftware (www.jsoftware.com) source released under GPL
version 3.

*** copyright and license

JSOFTWARE SOURCES refers to all files in this Jsoftware release package
except for file gpl3.txt.

JSOFTWARE SOURCES are: Copyright 1990-2011, Jsoftware Inc.  All rights
reserved.

JSOFTWARE SOURCES are: Licensed under GNU General Public License as
published by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

See gpl3.txt for GNU General Public License version 3. Additional info at
http://www.gnu.org/licenses.

(above also appears in copyright.txt and license.txt)

*** overview

Unpack J source release tar.gz file. Following assumes tar unpack is done
in ~ and creates ~/jgplsrc.

Familiarity with J provides essential background and context for working
with the source.

Development has been primarily in Windows and work on other platforms has
been done with limited resources and limited understanding of normal Unix
practices. The shell scripts, make files, and configuration are eccentric
at best and may need work to fit comfortably in the open source world.

This release is targeted at Unix. Windows VC++ project files are not
included (they could be created by those familiar with Windows
development). Additional source files required for the Windows COM wrapper
for j.dll in jgplsrc/win.

If you are playing with a supported platform or are doing a port to a
'nearby' platform then the current packaging might meet your needs. An
example of a 'nearby' platform would be Linux/ARM as differences are minor
from already supported platforms. Further afield, for example other than
Linux/Mac/Windows, will require more work.

*** folders

jgplsrc - *.c *.h 

jgplsrc/bin - bash scripts

jgplsrc/defs - files for building netdefs.ijs and hostdefs.ijs

jgplsrc/docs - text files

jgplsrc/docs/ioj - 'Implementation of J' by Roger Hui (out of date, but
useful)

jgplsrc/j - minimal J environment to test new new binaries

jgplsrc/test - test scripts to validate binaries

jgplsrc/win - additional source for win com server


*** configuration

bin/jconfig configs for 32/64bit and whether jconsole has line recall.

Configuration is driven largely by Unix uname and jconfig insists on uname
of Linux or Darwin. If building for a different uname, you will have to
edit jconfig and perhaps make changes to j.h, js.h, and other files.

Key platform differences are Unix/Windows, 32/64bits, intel byte
order/non-intel byte order, and XNAN and XINF double bit patterns.

Buildling Linux/Mac on Intel could be fairly smooth.

jconfig as distributed sets 32bit and no line recall. Edit jconfig as
required.

*** touch *.c

The makes are naive and don't handle h file or config changes. You may need
touch to get a clean build.

*** build_jconsole - build jconsole binary

$ cd ~/jgplsrc $ bin/build_jconsole

*** build_libj - build libj.so or libj.dylib binary $ bin/build_libj

If build_jconsole and build_libj succeed, the binaries have been copied to
j/bin and you can start J with:

$ j/bin/jconsole
   i.5

Congratulations if your J runs!

*** build_tsdll

J shared library calls (for example, sockets or memory mapped files) can
require J constants defined from C header files. These values are defined
by netdefs and hostdefs ijs files. Build these with:

$ bin/build_defs

*** build_tsdll

Build tsdll (shared library used to test J calls) with:

$ bin/build_tsdll

*** test suite

A test suite validates a J system. Read test/test.ijs and test/tsu.ijs for
more info.

$ j/bin/jconsole
   load 'test/test.ijs'
   bad=: TEST ddall NB. run all tests
   BAD ddall NB. report tests that failed

TEST displays the script name before it is run. If you crash, the last name
displayed is the script that caused the crash. You can narrow down the
cause by displaying each line in the script as it is run:

$ j/bin/jconsole
   load 'test/test.ijs'
   TESTX SNS 'gintovfl' NB. display and run each line of gintovfl.ijs

Get more info about a BAD script the same way:

A script can fail because of particular random numbers. If rerunning is
clean things are probably OK, but this is an area for caution.  

A script can fail because of a timing sensitvity. For example, comparing
timings of two methods to a threshold. Rerunning may show it sometimes runs
clean and sometimes fails on a timing test. You can ignore timing threshold
failures.

