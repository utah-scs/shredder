echo "Creating /mnt/huge and mounting as hugetlbfs"
sudo chmod 777 /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
sudo echo 1024 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
sudo chmod 777 /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages
sudo echo 1024 > /sys/devices/system/node/node0/hugepages/hugepages-2048kB/nr_hugepages
sudo mkdir -p /mnt/huge

grep -s '/mnt/huge' /proc/mounts > /dev/null
if [ $? -ne 0 ] ; then
        sudo mount -t hugetlbfs nodev /mnt/huge
fi
