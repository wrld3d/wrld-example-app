#!/bin/bash

curl https://bootstrap.pypa.io/ez_setup.py | python
easy_install pip==1.4.1
pip install --user --upgrade -r pip_requirements
easy_install lib/deps/Pillow-3.1.1.win32-py2.7.exe
