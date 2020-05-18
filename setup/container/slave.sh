#!/usr/bin/env bash

apt update && apt install -y openssh-server
echo "PermitRootLogin yes" >> /etc/ssh/sshd_config
systemctl restart ssh

PUBLICKEY="$HOME/cloud/id_rsa.pub"

if [ ! -f $PUBLICKEY ]; then
	echo "$PUBLICKEY: No such file" >&2
	exit 1
fi

mkdir -p $HOME/.ssh
cat $PUBLICKEY >> $HOME/.ssh/authorized_keys
