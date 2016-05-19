#!/bin/bash

BASEPATH=$1
shift
$BASEPATH/bin/whats_this --base_path $BASEPATH "$@"
