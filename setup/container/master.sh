#!/usr/bin/env bash

apt update && apt install -y openssh-server
echo "PermitRootLogin yes" >> /etc/ssh/sshd_config
service ssh restart

SSH=$HOME/.ssh
mkdir -p $SSH

echo "Host *" >> $SSH/config
echo "    ForwardAgent yes" >> $SSH/config
echo "Host *" >> $SSH/config
echo "    StrictHostKeyChecking no" >> $SSH/config

ssh-keygen -t rsa -N "" -f $SSH/id_rsa <<< y
chmod 600 $SSH/id_rsa
cp $SSH/id_rsa.pub $HOME/cloud

PUBLICKEY="$SSH/id_rsa.pub"

if [ ! -f $PUBLICKEY ]; then
	echo "$PUBLICKEY: No such file" >&2
	exit 1
fi

cat $PUBLICKEY >> $SSH/authorized_keys
