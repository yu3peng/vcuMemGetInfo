# vcuMemGetInfo

1) 依据实际情况，在 https://www.nvidia.com/Download/index.aspx 上选择驱动版本, 假设为 418.87.00.

2) 在主机上安装 GPU 驱动

```shell
chmod 755 NVIDIA-Linux-x86_64-418.87.00.run

./NVIDIA-Linux-x86_64-418.87.00.run -s
```

3) 按以下方式获得 vcuMemGetInfo.so 文件

```shell
mkdir -p /home/gpu

cd /home/gpu

git clone https://github.com/yu3peng/vcuMemGetInfo.git
   
cd vcuMemGetInfo
   
gcc cuMemGetInfo.c -fPIC -shared -o vcuMemGetInfo.so   
```

4) 安装 docker

5) 运行使用 GPU 的容器

5.1) Docker version >= 19.03 

docker 19.03 于 2019 年 7 月正式发布，[增加了对 --gpus 选项的支持，在 docker 里面想读取 nvidia 显卡再也不需要额外的安装 nvidia-docker[(https://www.jianshu.com/p/32ad4f448fe5)

```shell
docker run -v /home/gpu:/home/gpu --gpus all,capabilities=utilities -it tensorflow/tensorflow:1.13.1-gpu-py3 bash
```

5.2) Docker version < 19.03

19.03 以下的 docker 版本，需要安装 nvidia-docker，如果直接采用 docker，可以按照以下方式执行：

###########################################################################################

docker run --device /dev/nvidia0:/dev/nvidia0 --device /dev/nvidiactl:/dev/nvidiactl --device /dev/nvidia-uvm:/dev/nvidia-uvm --device /dev/nvidia-uvm-tools:/dev/nvidia-uvm-tools -v /usr/bin/nvidia-driver-file*:/usr/bin/nvidia-driver-file* -v /usr/lib64/nvidia-driver-file*:/usr/lib/nvidia-driver-file* -v /home/gpu:/home/gpu -it tensorflow/tensorflow:1.13.1-gpu-py3 bash

###########################################################################################

1. 查看 usr/bin 目录下 GPU 相关文件，获得 GPU 驱动安装的时间：XXXX-XX-XX XX:XX，按照以下方式获得 `usr_bin-nvidia-driver` 文件

```shell
ls /usr/bin -l --time-style=long-iso | grep "XXXX-XX-XX XX:XX" | awk '{print $8}' > usr_bin-nvidia-driver
```

2. 查看 /usr/lib64 目录下 GPU 相关文件，获得 GPU 驱动安装的时间：XXXX-XX-XX XX:XX，按照以下方式获得 `usr_lib64-nvidia-driver` 文件

```shell
ls /usr/lib64 -l --time-style=long-iso | grep "XXXX-XX-XX XX:XX" | awk '{print $8}' > usr_lib64-nvidia-driver
```

3. 通过以下方式获得容器启动 `container_driver.sh` 文件

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

6) 在容器中运行业务文件

```shell
cd /home/gpu/vcuMemGetInfo

export LD_PRELOAD=/home/gpu/vcuMemGetInfo.so

export GPU_MEMORY=300

python CNN_TensorFlow.py
```

7) 在主机上使用 `nvidia-smi` 查看 GPU 使用情况

8) 参考:
    1. [一种vGPU方案：控制GPU内存使用上限](https://blog.spider.im/post/control-gpu-memory/)
    2. [训练神经网络的简单例子（TensorFlow平台下Python实现）](https://blog.csdn.net/Jaster_wisdom/article/details/78018653)
    3. [GPU 共享三：井水不犯河水](https://zw0610.github.io/notes-cn/gpu-sharing-3.html)
