% This file defines TEX <string_primary> to return the picture
% resulting from running the string through tex.  It is slow,
% but more general than the standard btex..etex construction

vardef TEX primary s =
  write "btex "&s&" etex" to "mptextmp.mp";
  write EOF to "mptextmp.mp";
  scantokens "input mptextmp"
enddef;
