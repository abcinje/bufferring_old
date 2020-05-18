#!/usr/bin/env bash

SSH=$HOME/.ssh
mkdir -p $SSH

echo "Host *" >> $SSH/config
echo "    ForwardAgent yes" >> $SSH/config
echo "Host *" >> $SSH/config
echo "    StrictHostKeyChecking no" >> $SSH/config

ssh-keygen -t rsa -N "" -f $SSH/id_rsa <<< y
chmod 600 $SSH/id_rsa
cp $SSH/id_rsa.pub $HOME/cloud

cat $HOME/cloud/id_rsa.pub >> $SSH/authorized_keys
