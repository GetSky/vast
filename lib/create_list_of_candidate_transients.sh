#!/usr/bin/env bash

#################################
# Set the safe locale that should be available on any POSIX system
LC_ALL=C
LANGUAGE=C
export LANGUAGE LC_ALL
#################################

lib/transient_list
if [ $? -ne 0 ];then
 echo "ERROR running lib/transient_list" 1>&2
 exit 1
fi

if [ ! -f vast_image_details.log ];then
 echo "ERROR: cannot find vast_image_details.log" 1>&2
 exit 1
fi

NUMBER_OF_GOOD_IMAGES=`grep -v 'status=ERROR' vast_image_details.log | wc -l`

if [ $NUMBER_OF_GOOD_IMAGES -eq 4 ];then
 lib/find_flares >> candidates-flares.lst
 if [ $? -ne 0 ];then
  echo "ERROR running lib/transient_list" 1>&2
  exit 1
 fi
 while read A B ;do echo $A `cat $A | wc -l` `tail -n1 $A | awk '{printf "%s %8.3f %8.3f  ",$7,$4,$5}'` `head -n1 $A | awk '{printf "%s %8.3f %8.3f  ",$7,$4,$5}'` ;done < candidates-flares.lst >> candidates-transients.lst
fi 

if [ $NUMBER_OF_GOOD_IMAGES -eq 4 ];then
 echo -n 'Transient candidates found: ' >> vast_summary.log 
 if [ -f candidates-transients.lst ];then 
  cat candidates-transients.lst | wc -l >> vast_summary.log 
 else 
  echo '0' >> vast_summary.log
 fi
fi

