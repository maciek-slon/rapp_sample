#!/bin/bash

BASEPATH=$1
shift
$BASEPATH/bin/let_me_see --base_path $BASEPATH "$@"
