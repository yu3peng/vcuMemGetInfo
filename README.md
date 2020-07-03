# vcuMemGetInfo

1) Select NVIDIA GPU driver on https://www.nvidia.com/Download/index.aspx, then download it, assume to be 418.87.00.

2) Install GPU driver in host

```shell
chmod 755 NVIDIA-Linux-x86_64-418.87.00.run

./NVIDIA-Linux-x86_64-418.87.00.run -s
```

3) Prepare vcuMemGetInfo.so and business file in host

```shell
mkdir -p /home/gpu

cd /home/gpu
   
vi CNN_TensorFlow.py
   
vi cuMemGetInfo.c
   
gcc cuMemGetInfo.c -fPIC -shared -o vcuMemGetInfo.so   
```

[CNN_TensorFlow.py](./CNN_TensorFlow.py)

[cuMemGetInfo.c](./cuMemGetInfo.c)

4) Install docker.

5) Run container with GPU

5.1) Docker version >= 19.03 

```shell
docker run -v /home/gpu:/home/gpu --gpus all,capabilities=utilities -it tensorflow/tensorflow:1.13.1-gpu-py3 bash
```

5.2) Docker version < 19.03

###########################################################################################

docker run --device /dev/nvidia0:/dev/nvidia0 --device /dev/nvidiactl:/dev/nvidiactl --device /dev/nvidia-uvm:/dev/nvidia-uvm --device /dev/nvidia-uvm-tools:/dev/nvidia-uvm-tools -v /usr/bin/nvidia-driver-file*:/usr/binnvidia-driver-file* -v /usr/lib64/nvidia-driver-file*:/usr/lib/nvidia-driver-file* -v /home/gpu:/home/gpu -it tensorflow/tensorflow:1.13.1-gpu-py3 bash

###########################################################################################

Get install driver file name in /usr/bin with this shell command (change XXXX-XX-XX XX:XX with the time of installing driver)

```shell
ls /usr/bin -l --time-style=long-iso | grep "XXXX-XX-XX XX:XX" | awk '{print $8}' > usr_bin-nvidia-driver
```

Get install driver file name in /usr/lib64 with this shell command (change XXXX-XX-XX XX:XX with the time of installing driver)

```shell
ls /usr/lib64 -l --time-style=long-iso | grep "XXXX-XX-XX XX:XX" | awk '{print $8}' > usr_lib64-nvidia-driver
```

Make run_container.sh like:

```shell
#!/bin/bash

echo "docker run --device /dev/nvidia0:/dev/nvidia0 --device /dev/nvidiactl:/dev/nvidiactl --device /dev/nvidia-uvm:/dev/nvidia-uvm --device /dev/nvidia-uvm-tools:/dev/nvidia-uvm-tools"" \\" > container_driver.sh

usr_lib64=""
for line in `cat usr_lib64-nvidia-driver`
do
    usr_lib64="$usr_lib64 -v /usr/lib64/$line:/usr/lib/$line"
done
echo $usr_lib64" \\" >> container_driver.sh

usr_bin=""
for line in `cat usr_bin-nvidia-driver`
do
    usr_bin="$usr_bin -v /usr/bin/$line:/usr/bin/$line"
done
echo $usr_bin" \\" >> container_driver.sh

echo " -v /home/gpu:/home/gpu -it tensorflow/tensorflow:1.13.1-gpu-py3 bash" >> container_driver.sh

chmod 755 container_driver.sh
./container_driver.sh
```

```shell
chmod 755 run_container.sh
./run_container.sh
```

6) Run business in container

```shell
cd /home/gpu

export LD_PRELOAD=/home/gpu/vcuMemGetInfo.so

export GPU_MEMORY=300

python CNN_TensorFlow.py
```

7) Watch nvidia-smi in host

8) FYI:
    1. [一种vGPU方案：控制GPU内存使用上限](https://blog.spider.im/post/control-gpu-memory/)
    2. [训练神经网络的简单例子（TensorFlow平台下Python实现）](https://blog.csdn.net/Jaster_wisdom/article/details/78018653)
    3. [GPU 共享三：井水不犯河水](https://zw0610.github.io/notes-cn/gpu-sharing-3.html)
