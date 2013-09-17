path1=$1
path2=$2
echo $path1
echo $path2
for i in $path1/*.*
do
    for j in $path2/*.*
    do
        if [ "${j#*.}" = "${i#*.}" ]
        then   diff $i $j
        fi
    done
done
