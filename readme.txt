Project Title: Common Classes
Auther: Greg Hornby
==========================================================

Description:

This repository contains C++ code for creating a library of code
that perform commonly useful functionality.   Many of these
functions are ones that I have found to be useful and would
like to share between projects.

I am releasing this library as version 1.0 and the source code
is located in:  ./common_v1.0

The included functions are wrapped in the namespace, CmnClass.
The Makefile has options for installing the library in your
user directory using, 'make installusr' (which assumes that you
already have the directories: ~/include and ~/lib) or to install
it globally on your computer with, 'make installglobal'.

These installs will put copies of files in the following directories:

installusr:
  headers: ~/include/cmnclass.X.Y
  library: ~/lib/cmnclass.X.Y.a

installglobal:
  headers: /usr/local/include/cmnclass.X.Y
  library: /usr/local/lib/cmnclass.X.Y.a


In addition, links will be created to these as simply:
   cmnclass.X or cmnclass.X.a

New versions of the common class library which keep the
same API will increment the Y counter.  That is,
  cmnclass.1.0 => cmnclass.1.1

When/if a rewrite occurs in which the API changes, then X
will be incremented:
  cmnclass.1.0 => cmnclass.2.0


==========================================================

License:

This project was created from code developed on my own time and
also extracted from code developed under DARPA's M3 Program.
The latter requires code to be released under an open-source
license and UCSC's Office for Management of Intellectual Property
has OK'ed the release of such code under the BSD-3 license
(http://opensource.org/licenses/BSD-3-Clause) and the original
code-based this was extracted from is called, "Collaborative
Robotic Design System (CoRDS)".



 
