
START="${START:-1}"
END="${END:-10}"
echo "Running Test from folder ./tests and from START=${START} to END=${END}... "
if [[ $WITHTIME = "TRUE" ]]; then
   echo "-------------------------------"
fi
for i in $(seq $START $END)
do
   echo "testing " + $i 
   if [[ $WITHTIME = "TRUE" ]]
   then
      time ./bin/main < tests/$i.in > /tmp/a
      echo "-------------------------------"
   else  
      ./bin/main < tests/$i.in > /tmp/a
   fi
   diff -wb /tmp/a tests/$i.out
done