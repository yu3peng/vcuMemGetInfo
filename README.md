# vcuMemGetInfo

1. gcc cuMemGetInfo.c -fPIC -shared -o vcuMemGetInfo.so

2. export LD_PRELOAD=/xxx/vcuMemGetInfo.so

3. export GPU_MEMORY = 300

4. python CNN_TensorFlow.py
