#!/bin/bash

BASEPATH=$1
shift
$BASEPATH/bin/cloud --base_path $BASEPATH "$@"
