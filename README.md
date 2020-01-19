# vcuMemGetInfo

1. Select NVIDIA GPU driver on https://www.nvidia.com/Download/index.aspx, then download it, assume to be 418.87.00.

2. chmod 755 NVIDIA-Linux-x86_64-418.87.00.run

   ./NVIDIA-Linux-x86_64-418.87.00.run -s

3. mkdir -p /home/gpu

   cd /home/gpu
   
   vi CNN_TensorFlow.py
   
   vi cuMemGetInfo.c
   
   gcc cuMemGetInfo.c -fPIC -shared -o vcuMemGetInfo.so   
   
4. Install docker.

4.1 Docker version >= 19.03 

  docker run -v /home/gpu:/home/gpu --gpus all,capabilities=utilities -it tensorflow/tensorflow:1.13.1-gpu-py3 bash

4.2 Docker version < 19.03

  docker run --device /dev/nvidia0:/dev/nvidia0 --device /dev/nvidiactl:/dev/nvidiactl --device /dev/nvidia-uvm:/dev/nvidia-uvm --device /dev/nvidia-uvm-tools:/dev/nvidia-uvm-tools -v /usr/bin/:/usr/bin -v /usr/lib64:/usr/lib64 -v /home/gpu:/home/gpu -it tensorflow/tensorflow:1.13.1-gpu-py3 bash

5. export LD_PRELOAD=/home/gpu/vcuMemGetInfo.so

6. export GPU_MEMORY=300

7. python CNN_TensorFlow.py
