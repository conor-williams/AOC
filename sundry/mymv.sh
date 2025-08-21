set -xv
dir=$PWD
year=2017

while [ $year != 2025 ] ; do
	cd $dir
	cd ALL.$year;
	ls
	for i in *; do mv $i $year.$i; done

	year=$(( year + 1))
done
cd $dir
