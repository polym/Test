#---------------------------------------------------------------------------
# Using it to find the differences between old decode output and new decode
#       output.
# ./*** old_path new_path
#---------------------------------------------------------------------------
tmp_path="$HOME/mohb/decode_tmp"
old_path=$1
new_path=$2

echo "debug"
cat $HOME/mohb/info | grep $old_path | wc -l
echo "end"

if [ `cat $HOME/mohb/info | grep $old_path | wc -l` -eq 0 ]
then
    echo "old_path: $old_path" >> info
    echo "new_path: $new_path" >> info
    echo ""     >> info
    echo "" >> info
fi

rm $tmp_path/*
# cut file header and cdr header

for i in $new_path/*.*
do
    echo $i
    file=${i##*/}
    sed '1,6d' $i | awk '{n = split($1, b, ";")}; {for(j = 3; j <= n; j++){
        if(j < n) {printf "%s;", b[j]}
        else {printf "%s\n", $j}
        }
    }' > $tmp_path/$file
    done

# diff

for i in $old_path/*.*
do
    for j in $tmp_path/*.*
    do
        if [ "${i##*/}" = "${j##*/}" ]
        then
            logname=${i##*/}
            echo "$i <-> $j"
            diff $i $j >> $HOME/mohb/log/${logname}.log
        fi
    done
done
