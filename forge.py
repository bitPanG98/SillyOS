#!/usr/bin/python3
import docker
from docker import errors
import os
from argparse import ArgumentParser

IMAGE_ID = 'sillyos-dev:latest'

VOLUME_LIST = {
    os.path.abspath(os.curdir) : {
        'bind':'/workspace',
        'mode':'rw'
        }
    }

class DockerRemote:
    def __init__(self):
        self.client = docker.from_env()
        #if container not found
        try:
            print('Container not found, creating new container...')
            self.container = self.client.containers.run(IMAGE_ID, detach=False)
        except errors.ImageNotFound:
            print('Image not found, roll one...')
            print('Go get a coffee, it\'ll take a long time...')
            try:
                self.client.images.build(tag=IMAGE_ID, path='.')
                self.client.containers.prune()
            except:
                RuntimeError('Cannot build image', IMAGE_ID, '!')
            else:
                RuntimeError('Cannot create new container!')
        print('Container created.')

    def execute(self, cmd):
        self.container = self.client.containers.run(IMAGE_ID, cmd, detach=True, volumes=VOLUME_LIST)
        #print out the logs
        for line in self.container.logs(stdout=True, stderr=True, stream=True):
            print(line.strip().decode('utf-8'))
        

if __name__ == '__main__':
    
    print("       ,")
    print("      /(  ___________")
    print("     |  >:===========`")
    print("      )(")
    print("      \"\"")
    print("       T")
    print("   ====|==========")
    print("   ////v//////////")
    print("   ===============")
    print("=== SillyOS Forge ===")
    print("")

    ap = ArgumentParser(prog='forge.py', description='Build system for SillyOS')
    ap.add_argument('-iso', action='store_true', help='Build EFI ISO image')
    ap.add_argument('-clean', action='store_true', help='Cleaning workspace')
    ap.add_argument('-kernel', action='store_true', help='Build kernal')
    ap.add_argument('-boot', action='store_true', help='Build boot loader')

    args = ap.parse_args()
    remote = DockerRemote()

    if args.iso:
        print("Task: EFI ISO")
        remote.execute('make -s efi_iso')
    elif args.clean:
        print("Task: Clean")
        remote.execute('make -s clean')
    elif args.kernel:
        print("Task: Kernel")
        remote.execute('make -s kernel')
    elif args.bootloader:
        print("Task: Bootloader")
        remote.execute('make -s bootloader')