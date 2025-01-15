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
			if [ ! -f day$day.exe ] ; then
				g++ -Wl,--stack,999777666 -I../../ day$day.c -o day$day.exe -lmbedcrypto
			fi
			if [ $day != 25 ]; then
				if [ ! -f day$day.2.exe ]; then
					g++ -Wl,--stack,999777666 -I../../ day$day.2.c -o "day$day.2.exe" -lmbedcrypto
				fi
			fi
		fi
		day=$(( day + 1))
	done
	day=1
	year=$((year + 1))
done
cd 2018/day15
gcc -Wl,--stack,999777666 -I../../ day15.c -o "day15.exe" -lmbedcrypto
gcc -Wl,--stack,999777666 -I../../ day15.2.c -o "day15.2.exe" -lmbedcrypto
cd $curdir
cd 2018/day22
gcc -Wl,--stack,999777666 -I../../ day22.2.c -o "day22.2.exe" -lmbedcrypto
cd $curdir
