year=2015

while [ $year != 2025 ]; do
	sh onelinercheckYEAR.sh $year 2>&1 | tee output.$year 2>&1
	year=$((year+1))
done
