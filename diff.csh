#---------------------------------------------------------------------------
# Using it to find the differences between old decode output and new decode
#       output.
# ./*** old_path new_path
#---------------------------------------------------------------------------
tmp_path="$HOME/decode_tmp"
old_path=$1
new_path=$2

# cut file header and cdr header

for i in $new_path/*.*
do
    echo $i
    sed '1,6d' $i | awk '{n = split($1, b, ";")}; {for(j = 4; j <= n; j++){
        if(j < n) {printf "%s;", b[j]}
        else {printf "%s\n", $j}
        }
    }' > tmp_path/$i
done

# diff

for i in $old_path/*.*
do
    for j in $tmp_path/*.*
    do
        if [ "${i#.*}" = "${j#.*}" ]
        then diff $i $j
    done
done
