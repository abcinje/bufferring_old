#!/usr/bin/env bash

sudo apt install -y nfs-common

mkdir -p $HOME/cloud
if [ $# -lt 1 ]; then
	echo "Usage: $0 <server_ip>" >&2
	exit 1
fi
echo "***Warning: NFS mount may fail due to the inbound rules of the server***"
sudo mount -t nfs $1:$HOME/cloud $HOME/cloud
