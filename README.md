# vcuMemGetInfo

1. Select NVIDIA GPU driver on https://www.nvidia.com/Download/index.aspx, then install it on your machine.

2. mkdir -p /home/gpu

   cd /home/gpu
   
   vi cuMemGetInfo.c
   
   vi CNN_TensorFlow.py
   
3. Install docker.

3. docker run --device /dev/nvidia0:/dev/nvidia0 --device /dev/nvidiactl:/dev/nvidiactl --device /dev/nvidia-uvm:/dev/nvidia-uvm --device /dev/nvidia-uvm-tools:/dev/nvidia-uvm-tools -v /usr/bin/:/usr/bin -v /usr/lib64:/usr/lib64 -v /home/gpu:/home/gpu -it tensorflow/tensorflow:1.13.1-gpu-py3 bash

4. cd /home/gpu
   
   gcc cuMemGetInfo.c -fPIC -shared -o vcuMemGetInfo.so

6. export LD_PRELOAD=/home/gpu/vcuMemGetInfo.so

7. export GPU_MEMORY=300

8. python CNN_TensorFlow.py
