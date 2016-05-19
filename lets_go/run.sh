#!/bin/bash

BASEPATH=$1
shift
$BASEPATH/bin/lets_go --base_path $BASEPATH "$@"
