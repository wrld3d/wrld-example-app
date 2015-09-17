#!/bin/bash

curl https://bitbucket.org/pypa/setuptools/raw/bootstrap/ez_setup.py | python
easy_install pip==1.4.1
pip install --user --upgrade -r pip_requirements
easy_install lib/deps/PIL-1.1.7.win32-py2.7.exe




