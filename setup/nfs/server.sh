#!/usr/bin/env bash

sudo apt install -y nfs-kernel-server

mkdir $HOME/cloud
sudo bash -c "echo $HOME/cloud *\(rw,sync,no_root_squash,no_subtree_check\) >> /etc/exports"
sudo exportfs -a
