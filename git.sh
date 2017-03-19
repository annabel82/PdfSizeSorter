#!/usr/bin/env bash

if [ ! -f "./commitNo" ] ; then
  var=0

else
  var=`cat ./commitNo`
fi

(( $var + 1 ))

date=`date +%d-%m-%Y:%H:%M`

git add -u && git commit -m Commit-$var-$date && git push
cd /Users/anna/PdfSizeSorter
echo $str $va}
git push
echo "${var}" > ./commitNo

sleep 0



