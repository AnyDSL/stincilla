DIRS=$(find * -maxdepth 3 -type d -name "*"| sort -n)
path=`pwd`

space="$(printf "%34s")"
echo -e "TEST $space II ALUTs Regs  Logic RAM DSP   Freq" > $path/results.data

x=1
for i in $DIRS; do
  test -d "$i/gaussian_debug" || continue
    name="$( printf "%-35s" $i )"
    RES=$($path/extract.sh $i/gaussian_debug asd | grep -v II); echo -e "$name \t $RES" >> $path/results.data
  let x=$x+1
done
