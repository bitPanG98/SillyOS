#!/usr/bin/python3
import os
import argparse

p = argparse.ArgumentParser()
p.add_argument('-f', nargs='?', type=str)
p.add_argument('-o', nargs='?', type=str)

in_file = open(p.parse_args().f, 'rb')

in_buff = in_file.read()

in_file.close()

#check ID
if in_buff[0] != 0x42 or in_buff[1] != 0x4d:
    print('Invalid .BMP file!')
    quit()

file_size = int.from_bytes(in_buff[2:5], byteorder='little')
data_offset = int.from_bytes(in_buff[0xa:0xd], byteorder='little')

width = int.from_bytes(in_buff[0x12:0x15], byteorder='little')
height = int.from_bytes(in_buff[0x16:0x19], byteorder='little')

bpp = int.from_bytes(in_buff[0x1c:0x1c+1], byteorder='little')
data_size = int.from_bytes(in_buff[0x22:0x25], byteorder='little')

# print('# File Size: ', file_size)
# print('# Pixel array offset: ', data_offset)
# print('# Pixel array size: ', data_size)
# print('# Width: ', width, 'px')
# print('# Height: ', height, 'px')
# print('# BPP: ', bpp)

data = in_buff[data_offset:data_offset+data_size]

out_file = open(p.parse_args().o, 'a') 
out_file.writelines('// '+ p.parse_args().f + '\n')
out_file.write('{')
j = []
for y in range(height):
    temp = 0
    for x in range(width):
        if data[y*width + x] == 0xff or data[y*width + x] == 0x15:
            temp += pow(2, x)
    j.insert(0, hex(temp))
for c in str(j):
    if not (c == '[' or c == ']' or c == "'"):
        out_file.write(c)
out_file.write("},\n")
out_file.close()
