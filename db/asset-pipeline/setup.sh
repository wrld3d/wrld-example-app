#!/bin/bash

pip install -U pip
pip install --user --upgrade -r pip_requirements

if [ $? -ne 0 ] ; then 
  echo "Failed to install/upgrade pip packages" >&2
  exit 1
fi