###tar -xvzf ins-2015-2024.tar.gz
#handy for copying over files if you have just unzipped the inp tar file
year=2015
day=1

while [ $year != 2025 ] ; do
	while [ $day != 26 ] ; do

		echo ALL.$year/day$day.c $year/day$day
		cp ALL.$year/day$day.c $year/day$day
		echo ALL.$year/day$day.2.c $year/day$day
		if [ $day != 25 ] ; then
			cp ALL.$year/day$day.2.c $year/day$day
		fi
		day=$(($day+1))
        done
	day=1
        year=$(($year + 1))
done
#what i use to create the input file:
#rm inps1234.tar.gz
#find 20* -name i\*.txt -o -name ex\*.txt | tar -rvf inps1234.tar
#gzip inps1234.tar
