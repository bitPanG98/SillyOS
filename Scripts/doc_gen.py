#!/usr/bin/env python
import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('title', type=str, help="The title")
parser.add_argument('output', type=str, default='./', help="Output path")
#parser.add_argument('force', type=bool, default=False, help="force create files")
#force = parser.parse_args('force')
arg = parser.parse_args().title
path = parser.parse_args().output + arg + '.md'

f = open(path, 'w+')
f.writelines('# SillyOS Documentation - ' + arg)
f.close()
quit()


