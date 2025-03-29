set -xv
###tar -xvzf ins-2015-2024.tar.gz
#handy for copying over files if you have just unzipped the inp tar file
year=2015
day=1

while [ $year != 2025 ] ; do
	while [ $day != 26 ] ; do
		cp ALL.$year/$year.day$day.c $year/day$day
		cp ALL.$year/$year.day$day.* $year/day$day
		if [ $day != 25 ] ; then
			cp ALL.$year/$year.day$day.2.c $year/day$day
		fi
		day=$(($day+1))
        done
	day=1
        year=$(($year + 1))
done
# cd 2022/day25
# /cygdrive/e/jdk-23.0.2/bin/javac day25snafu.java
# /cygdrive/e/jdk-23.0.2/bin/java  day25snafu
# java class name issue 
cp ALL.2022/2022.day25.snafu.java 2022/day25/day25snafu.java

#what i use to create the input file:
#rm inps1234.tar.gz
#find 20* -name i\*.txt -o -name ex\*.txt | xargs tar -rvf inps1234.tar
#gzip inps1234.tar
#
#
#=======
#
