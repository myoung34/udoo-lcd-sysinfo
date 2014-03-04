#!/bin/sh
echo "#"
echo "System Stats:"
echo "  OS: "$(cat /etc/issue | sed 's/\\n\|\\l//g') [$(uname -m)]
echo "  Kernel: "$(uname -sr)
echo "  Hostname: " $(hostname -f)
echo "Network Stats:"
echo "  IP Address: " $(hostname -I)
for i in `ifconfig | grep -E '^[a-z]' | awk '{print $1}' | grep -v -E '^lo|usb0'`; do 
  echo "  "[$i] $(sudo ethtool $i | grep 'Link detected:' | sed 's/Link detected/Connected/g') 
done
echo "Current Users:"
who | tail -n+1 | awk '{gsub("\(|\)","",$6); print "  "$1"\n    Connected From: "$6}'
exit 0
