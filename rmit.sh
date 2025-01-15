set -xv
day=11
year=2015

while [ $year != 2024 ]; do
	while [ $day != 26 ]; do
		echo $year/day$day/day$day.2.exe
		#rm $year/day$day/day$day.2
		#rm $year/day$day/day$day.exe
		rm $year/day$day/day$day.2.exe
		##rm $year/day$day/day$day.2.exe
		
		day=$(($day + 1))
	done
	day=11
	year=$(($year+1))
done
