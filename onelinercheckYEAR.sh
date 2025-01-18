year=$1
day=1;
while [ $day != 26 ]; do
	if [ -f $year/day$day/day$day.exe ] ; then
		year/day$day/day$day.exe $year/day$day/i1.txt
	fi 
	if [ -f $year/day$day/day$day.2.exe ] ; then
		$year/day$day/day$day.2.exe $year/day$day/i1.txt
	fi 
	day=$(($day+1));
done
