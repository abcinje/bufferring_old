#!/usr/bin/env bash

FILENAME="id_rsa.pub"

if [ ! -f $FILENAME ]; then
	echo "$FILENAME: No such file" >&2
	exit 1
fi

cat $FILENAME >> $HOME/.ssh/authorized_keys
