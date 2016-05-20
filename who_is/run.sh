#!/bin/bash

BASEPATH=$1
shift
$BASEPATH/bin/who_is --base_path $BASEPATH "$@"
