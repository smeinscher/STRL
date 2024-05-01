#!/bin/bash
echo "$(date)" >> line_count_history.txt;
find ./ -type f \( -iname \*.h -o -iname \*.cpp \) -not -path "./framework/external/*" -not -path "./framework/tst/external/*" -not -path "./cmake-build-debug/*" -not -path "./cmake-build-release/*" |
  xargs sed '/^\s*#/d;/^\s*$/d' |
  grep -v "^\s*//" |
  sed -r ':a; s%(.*)/\*.*\*/%\1%; ta; /\/\*/ !b; N; ba' |
  wc -l >> line_count_history.txt;
tail -n 2 line_count_history.txt;

