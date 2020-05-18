#!/usr/bin/env bash

SSH=$HOME/.ssh

echo "Host *" >> $SSH/config
echo "    ForwardAgent yes" >> $SSH/config
echo "Host *" >> $SSH/config
echo "    StrictHostKeyChecking no" >> $SSH/config

ssh-keygen -t rsa -f $SSH/id_rsa <<< y
chmod 600 $SSH/id_rsa
cp $SSH/id_rsa.pub $HOME/cloud
