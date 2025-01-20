set -xv
dir=$PWD
year=2015
while [ $year != 2025 ]; do
	cd $dir
	cd ALL.$year
	cp * /cygdrive/d/GitHub/AOC/ALL.$year;
	year=$((year+1))
done

cd $dir
