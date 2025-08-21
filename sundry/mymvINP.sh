set -xv
dir=$PWD
year=2015
day=1
while [ $year != 2025 ] ; do
	while [ $day != 26 ]; do
		cd $dir
		cd $year
		cd day$day
		for i in *.txt; do mv $i $year.day$day.$i; done
		day=$((day+1));
	done
	day=1
	year=$(( year + 1))
done
cd $dir
