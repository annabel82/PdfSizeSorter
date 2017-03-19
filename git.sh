#!/usr/bin/env bash

if [ ! -f "./commitNo" ] ; then
  var=0

else
  var=`cat ./commitNo`
fi

(( $var + 1 ))

DATE=`date '+%d-%b-%Y_%H:%M'`

git add -u && git commit -m Commit$var_$DATE && git push
cd /Users/anna/PdfSizeSorter
echo $str $va}
git push
echo "${var}" > ./commitNo

sleep 0



