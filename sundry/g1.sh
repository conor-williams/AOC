curdir=$PWD
year=2024
while [ $year != 2025 ]; do
	cd ALL.$year
	echo year is $year
	year2=2015
	while [ $year2 != 2025 ]; do
		if [ $year2 != $year ]; then
			grep $year2 day*.c | grep -i day
		fi
		year2=$((year2+1))
	done
	cd $curdir
	year=$((year+1))
done
