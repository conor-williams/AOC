set -xv
#handy compile...
#before::
##tar -xvzf ../ins-2015-2024.tar.gz
##sh specialCopy.sh
day=1
year=2015
curdir=$PWD
echo $curdir
while [ $year != 2025 ];  do
	while [ $day != 26 ]; do
		if [ -d $curdir/$year/day$day ]; then
			cd $curdir/$year/day$day
			g++ -Wl,--stack,999777666 day$day.c -o day$day
			g++ -Wl,--stack,999777666 day$day.2.c -o day$day.2
		fi
		day=$(( day + 1))
	done
	day=1
	year=$((year + 1))
done
