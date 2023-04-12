#!/bin/bash

for i in {1..5}; do
  clear
  cat << EOF | figlet | lolcat -a -d 1
HEREDOC
EOF
  sleep 0.5
done

