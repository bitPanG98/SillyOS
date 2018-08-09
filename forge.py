import docker
from docker import errors
import os

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
    print(os.path.abspath(os.curdir))
    remote = DockerRemote()
    remote.execute('make efi_iso')