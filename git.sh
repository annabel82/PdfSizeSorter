#!/usr/bin/env bash

if [ ! -f "./commitNo" ] ; then
  var=0

else
  value=`cat ./commitNo`
fi

value=`expr ${var} + 1`

cd /Users/anna/PdfSizeSorter
git add -u && git commit -m 'Commit ${var}' && git push

echo "${var}" > ./commitNo

sleep 2



