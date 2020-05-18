# Cluster Setup

### 0. Download git repository
```
$ sudo apt update && sudo apt install git
$ git clone https://github.com/abcinje/bufferring.git
$ cd bufferring/setup/
```

## Host

### 1. Install NVIDIA driver and docker, and configure ssh
```
$ ./common.sh
```

### 2. Re-login
_Note: From now on, instances can be logged in using port 2222, not 22._

### 3-1. Configure NFS (server)
```
$ nfs/server.sh
```

### 3-2. Configure NFS (client)
```
$ nfs/client.sh <server_ip>
```

### 4. Download and run docker image
```
$ docker pull <docker_image>
$ docker run --gpus all -it --network=host -v $HOME/cloud:/root/cloud <docker_image>
```

## Container

### 0. Download git repository
```
# cd
# apt update && apt install git
# git clone https://github.com/abcinje/bufferring.git
# cd bufferring/setup/
```

### 1-1. Configure ssh (master)
```
# container/master.sh
```

### 1-2. Configure ssh (slave)
```
# container/slave.sh
```
