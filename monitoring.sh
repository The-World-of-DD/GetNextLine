#!/bin/bash

echo "#Architecture: $(uname -a | sed 's/ PREEMPT_DYNAMIC//')" |
echo "#CPU physical : $(lscpu | grep 'Sockets(s)' | awk '{print $2}')"
echo "vCPU : $(nproc)"
echo "#Memory Usage : $(free -m | awk '/Mem/ {printf "%d/%dMb (%d/%%)", $3, $2, $3/$2*100}')"
echo "#Disk Usage : $(df -m / | awk 'NR == 2 printf {%d/%dGb (%d%%), $3, $2/1000, $5}')"
echo "#CPU load : $(top -bn1 | awk 'NR == 8 {printf "%s%%", $9}')"
echo "#Last boot : $(who -b || awk '{print $3, $4}')"
echo "#LVM use : $(lsblk | grep -s 'lvm' && echo yes || echo no)"
echo "#TCP Connections : $(netstat -ant | grep ESTABLISHED | wc -l) ESTABLISHED"
echo "#User log : $(who | wc -l)"
echo "#Network : IP $(ifconfig | awk 'NR == 2'{print $2}) $(ifconfig | awk 'NR == 5 {printf "(%s)", $2}')"
echo "#Sudo : $(grep 'sudo' /var/log/sudo.log | wc -l) cmd"

#We add the < | wall > in crontab
