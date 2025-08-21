pa=$PWD
echo $pa
cdandcompile()
{
	cd "$pa"
	cd $1
	echo $1
	echo $2
	if [ -f $2 ]; then
		g++ $2 -Wl,--stack,999777666 -o bb
		time ./bb i1.txt
	fi
	cd "$pa"
}
#2015
cdandcompile "2015/day12/" "day12.2.c" 
cdandcompile "2015/day19/" "day19.2.c" 
#2016
cdandcompile "2016/day22/" "day22.2.c" 
#2017
cdandcompile "2017/day16/" "day16.2.c" 
cdandcompile "2017/day18/" "day18.2.c" 
#2018
cdandcompile "2018/day19/" "day19.2.c" 
cdandcompile "2018/day23/" "day23.2.c" 
#2019
cdandcompile "2019/day14/" "day14.2.c" 
cdandcompile "2019/day20/" "day20.2.c" 
cdandcompile "2019/day23/" "day23.2.c" 
#2021
cdandcompile "2021/day12/" "day12.2.c" 
#2022
cdandcompile "2022/day23/" "day23.2.c" 
cdandcompile "2022/day11/" "day11.2.c" 
#2023
cdandcompile "2023/day11/" "day11.2.c" 
cdandcompile "2023/day13/" "day13.2.c" 
cdandcompile "2023/day14/" "day14.2.c" 
cdandcompile "2023/day15/" "day15.2.c" 
cdandcompile "2023/day21/" "day21.2.c" 
cdandcompile "2023/day23/" "day23.2.c" 

#$ stdbuf -e0 -i0 -o 0 sh runem.sh >  var_out.txt 2>&1
