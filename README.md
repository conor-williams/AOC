o sh FIRST.sh
o ps and kill are your friend

<h2>Notes (this README is a .html file (drag and drop into a browser)) lu:29-01-2025</h2>
<address><b>conor.williams@gmail.com</b></address><br>
<h3>Update (11::20-01-25):</h3>
<pre>
	o length of filename getting you down? use ln and stop getting down (e.g.):
	         ln -s 2020.day20.i1.txt i1.txt
	o run "sh FIRST.sh" -- it does everything for you
	o added year and day to input file names and year to c files (no code change just renaming of files)
	o dup2 needed an fflush -- now no debug -- sorry
	o if the file is not present, it has not been coded
	o all <s>day</s>Part 1's for every year working well, except:
		-- 2016 Day 11,1
	   	-- 2018 Day 21.1
		-- 2019 Day 18 part1
		-- <s>2022 Day 22.1</s>
	   	-- <s>2023 Day 22.1</s>
	o all years days 1--10 Part 1&2 working well, except:
		-- 2017 Day 7.2
		-- <s>2018 Day 7 1&2</s>
	   	-- 2022 Day 9.2
	o Timer has been added (an automatic kill, if you will) to the slow ones so they don't run too long
	        (but you might not get the answer)
		(timer length can be changed in code before a compile) TimerSet(Xseconds);
     <s>o looking now to tidy part2's (11-24) of every year (16-01-2025) </s>
	o Result of Tidy every year <s>but</s> including 2024:
	conor.williams@DESKTOP-MM5HH8I AOC-main
$ cat lool.txt
	2015
2015&sol;day12&sol;day12.2.c:   printf("broken\n"); exit(0);
2015&sol;day19&sol;day19.2.c:   printf("broken\n"); exit(0);
        2016
2016&sol;day22&sol;day22.2.c:   printf("broken..\n"); exit(0);
        2017
2017&sol;day16&sol;day16.2.c:   printf("broken...\n"); exit(0);
2017&sol;day18&sol;day18.2.c:   printf("broken...\n"); exit(0);
        2018
2018&sol;day19&sol;day19.2.c:   printf("broken\n"); exit(0);
2018&sol;day23&sol;day23.2.c:   printf("broken\n"); exit(0);
        2019
2019&sol;day14&sol;day14.2.c:   printf("broken\n"); exit(0);
<s>2019&sol;day20&sol;day20.2.c:   printf("broken\n"); exit(0);</s>
2019&sol;day23&sol;day23.2.c:   printf("broken\n"); exit(0);
        2021
<s>2021&sol;day12&sol;day12.2.c:   printf("broken...\n"); exit(0);</s>
        2022
2022&sol;day23&sol;day23.2.c:   printf("broken\n"); exit(0);
2022&sol;day11&sol;day11.2.c:   printf("broken\n"); exit(0);
        2023
2023&sol;day11&sol;day11.2.c:   print("broken..\n"); exit(0);
2023&sol;day13&sol;day13.2.c:   printf("broken...\n"); exit(0);
2023&sol;day14&sol;day14.2.c:   printf("broken...\n"); exit(0);
<s>2023&sol;day15&sol;day15.2.c:   printf("broken...\n"); exit(0);</s>
2023&sol;day21&sol;day21.2.c:   printf("broken...\n"); exit(0);
2023&sol;day23&sol;day23.2.c:   printf("broken...\n"); exit(0);
</pre>
<h3>Note: (of course you may already know this)</h3>     
<br>if you are not interested in waiting for one to finish
<br>and you want the system to continue, then use 
<br>ps and kill (in cygwin, ps,  and maybe ps -ef or ps -aux in linux) eg.:
               <hr>
	       <pre>	       
% ps
      PID    PPID    PGID     WINPID   TTY         UID    STIME COMMAND
     5695       1    5695        940  ?         197610 01:04:07 /usr/bin/mintty
     5702    5696    5702       5272  pty0      197610 01:04:11 /usr/bin/ps
     1807    1806    1807       1424  pty1      197610 20:31:54 /usr/bin/bash
     5696    5695    5696       4276  pty0      197610 01:04:08 /usr/bin/bash
     5688    5686    5668       9356  pty1      197610 01:00:09 /usr/bin/tee
     1806       1    1806       9416  ?         197610 20:31:53 /usr/bin/mintty
     5687    5686    5668       8968  pty1      197610 01:00:09 /usr/bin/sh
     5668    1807    5668       8744  pty1      197610 01:00:01 /usr/bin/sh
     5686    5668    5668       1792  pty1      197610 01:00:09 /usr/bin/sh
     5691    5687    5668      11772  pty1      197610 01:00:22 /cygdrive/c/Users/conor.williams/Desktop/AOC-main/2016/day14/day14.2
% kill -9 5691
	       
     (that kills off the slow day14 for example)
</pre>
	<hr>
 	<h2>Update (08-01-25):</h2>
  	<pre>
	o all years days 1--10 Parts 1&2 working well, (except 2017 Day7.2 and 2018 Day 7 1&2)
 	o now looking at all <s>day</s>Part1's 1->25 for every year
  	o part 2's which were broken next
   	o part 2's unfinished after that 
	</pre>
	<hr>
<br>
<hr>
	Update: apologies, some of my files got overwritten causing me to upload ones that gave the wrong answers (find and cp overwrite!!):
rectified soon (update: nearly rectified...) (late december 2024)

<hr>
<ul>
<li>g++ if "using namespace std" </li>
<li>either gcc or g++, if no "using namespace std" </li>
<li>there are 3 which only work with gcc</li>
<li>expand the stack if errors compiling or linking: --Wl,--stack,999777666 </li>
<li>if crashes or "segmentation fault" expand/widen the stack (it means: more memory needed or high depth of recursion) </li>
<li>-I. to the compiler when using bigint (after copying into this dir, the .h files) </li>
<li>dayX.c is part1 of day X </li>
<li>dayX.2.c is part2 of day X </li>
<li>others are scribbles.. or partials/solns which may not have worked </li>
<li>a couple need md5 (for cygwin: install <b>mbedtls</b> development (-> libmbedcrypto.a in /lib)) (gcc -lmbedcrypto dayX.c -Wall ) </li>
<li>you will find dot or neato or sfdp in package graphviz for python (python and graphviz are cygwin packages called python and graphviz) </li>
<li> <h2>TODO:</h2></li>
<s><li>FIXED: a couple need the dictionary of words (for cygwin: install <b>words</b>) </li></s>
<s><li>FIXED: a couple <s>missing dayX.c and have</s> dayX.2.c (<b><i>todo in 2025</b></i>) </li></s>
<s><li>FIXED: a couple need the input sorted externally first or else they crash: sort file.1 > file.2: (will do internal sort -- (<i><b>todo in 2025</b></i>)) </li></s>
<li>add widen stack check in specific c files; maybe a simple malloc with a free and a note (<i><b>todo in 2025</b></i>) </li>
<li>a couple where there was mental arithmetic after the output was generated by c/c++ file, mostly detect of cycles (auto detect cycles (<b><i>todo in 2025</i></b>)) </li>
<li>there are a couple that take overnight... (there is usually a manual way (diagram gen) to get the answer) they need optimisation -Temporary FIX: Mark the Length of time it takes at the start of c file- (<b><i>todo in 2025</b></i>) </li>
<li>there are around 40 that have not been completed -- (<b><i>todo in 2025</b></i>) </li>
<li>a couple were done without c/c++ -- mostly using sed, awk, du and unix commands scripts and 1 java -- will upload (<b><i>todo in 2025</i></b>) </li>
<li></li>
	
 <li>kudos to <i><b>Eric Wastl & co.</b></i></li>
</ul>
<br>
<address><b>conor.williams@gmail.com</b></address><br>

<br><br>
<hr>
<h3>Table of years/days of days which need optimizations or work (todo: ongoing):</h3>
<table> 
	<tr><td><b>2015</b></td><td>day10</td><td>day12</td><td>day19.2</td><td>day20</td><td>day24</td></tr>
	<tr><td><b>2016</b></td><td><s>day2 x 2 </s></td></td><td>day9.2</td><td>day11 x 2 </td><td>day20.2</td><td>day22.2</td><td>day23.2</td></tr>
	<tr><td><b>2017</b></td><td>day7.2</td></td><td>day11.2</td><td>day16.2</td><td>day17.2</td><td>day18.2</td><td>day20.2</td></tr>
	<tr><td><b>2018</b></td><td>day3</td><td>day5</td><td>day7</td><td>day9.2</td><td>day11.2</td><td>day15</td><td>day19.2</td><td>day21</td><td>day22.2</td><td>day23.2</td></tr>
	<tr><td><b>2019</b></td><td>day12.2</td><td>day3.2</td><td>day14.2</td><td>day17.2</td><td>day18</td></tr>
	<tr><td><b>2020</b></td><td>day10.2</td><td>day12.2</td><td>day13.2</td><td>day14.2</td><td>day15.2</td><td>day16.2</td><td>day17.2</td><td>day18.2</td><td>day19.2</td><td>day20.2</td>
				<td>day21.2</td><td>day22.2</td><td>day23.2</td><td>day24.2</td></tr>
	<tr><td><b>2021</b></td><td>day11.2</td><td>day12.2</td><td>day14.2</td><td>day15.2</td><td>day16.2</td><td>day18.2</td>
				<td>day21.2</td><td>day22.2</td><td>day23</td><td>day24</td></tr>
	<tr><td><b>2022</b></td><td>day9.2</td><td>day13.2</td><td>day15.2</td><td>day17.2</td><td>day18.2</td><td>day21.2</td>
				<td>day22.2</td><td>day25.1 (java)</td></tr>
	<tr><td><b>2023</b></td><td><s>day1</s></td><td>day2</td><td>day5</td><td>day7</td><td>day8.2</td><td>day9</td><td>day10.2</td><td>day11.2</td><td>day12.2</td><td>day13.2</td>
				<td>day14.2</td><td>day15</td><td>day17</td><td>day21</td></tr>
	<tr><td><b><i>2024</i></b></td><td>day22.2</td></tr>
</table>

<h2>Split of the above table into three tables: broken, slow, not yet attempted</h2>
<h2>Broken</h2>
<table> 
	<tr><td><b>2015</b></td><td>day12</td><td>day19.2</td></tr>
	<tr><td><b>2016</b></td><td>day 11</td></tr>
	<tr><td><b>2017</b></td><td>day7.2</td></td><td>day11</td><td>day20.2</td></tr>
	<tr><td><b>2018</b></td><td>day7</td><td>day9.2</td><td>day15</td><td>day21</td><td>day22.2</td><td>day23.2</td></tr>
	<tr><td><b>2019</b></td><td>day17.2</td><td>day18</td></tr>
	<tr><td><b>2020</b></td><td></td></tr>
	<tr><td><b>2021</b></td><td></td></tr>
	<tr><td><b>2022</b></td><td>day25.1(written in java)</td></tr>
	<tr><td><b>2023</b></td><td><s>day1</s></td><td>day2</td><td>day5</td><td>day7</td><td>day9</td><td>day10.2</td><td>day11.2</td><td>day12.2</td><td>day13.2</td>
				<td>day15</td><td>day17</td><td>day21</td></tr>
	<tr><td><b><i>2024</i></b></td><td></td></tr>
</table>
<hr>
<h2>Slow</h2>
<table> 
	<tr><td><b>2015</b></td><td>day10</td><td>day20</td><td>day24</td></tr>
	<tr><td><b>2016</b></td><td><s>day2 x 2 </s></td></td><td>day9.2</td><td>day20.2</td><td>day22.2</td><td>day23.2</td></tr>
	<tr><td><b>2017</b></td><td>day16.2</td><td>day17.2</td><td>day18.2</td></tr>
	<tr><td><b>2018</b></td><td>day3</td><td>day5</td><td>day11.2</td><td>day19.2</td><td>day21</td></tr>
	<tr><td><b>2019</b></td><td>day12.2</td><td>day3.2</td><td>day14.2</td></tr>
	<tr><td><b>2020</b></td><td></td></tr>
	<tr><td><b>2021</b></td><td>day23</td><td>day24</td></tr>
	<tr><td><b>2022</b></td><td>day11,2</td><td>day16.2</td><td>day19.2</td><td>day23.2</td></tr>
	<tr><td><b>2023</b></td><td>day8.2</td><td>day14.2</td></tr>
	<tr><td><b>2024</b></td><td>day22.2</td></tr>
</table>
<hr>
<h2>Not attempted Yet</h2>
<table> 
	<tr><td><b>2015</b></td><td>FIN</td></tr>
	<tr><td><b>2016</b></td><td>FIN</td></tr>
	<tr><td><b>2017</b></td><td>FIN</td></tr>
	<tr><td><b>2018</b></td><td>FIN</td></tr>
	<tr><td><b>2019</b></td><td>FIN</td></tr>
	<tr><td><b>2020</b></td><td>day10.2</td><td>day12.2</td><td>day13.2</td><td>day14.2</td><td>day15.2</td><td>day16.2</td><td>day17.2</td><td>day18.2</td><td>day19.2</td><td>day20.2</td>
				<td>day21.2</td><td>day22.2</td><td>day23.2</td><td>day24.2</td></tr>
	<tr><td><b>2021</b></td><td>day11.2</td><td>day12.2</td><td>day14.2</td><td>day15.2</td><td>day16.2</td><td>day18.2</td>
				<td>day21.2</td><td>day22.2</td><td>day23</td><td>day24</td></tr>
	<tr><td><b>2022</b></td><td>day9.2</td><td>day13.2</td><td>day15.2</td><td>day17.2</td><td>day18.2</td><td>day21.2</td>
				<td>day22.2</td><td>day25.1 (java)</td></tr>
	<tr><td><b>2023</b></td><td>day12.2</td></tr>
	<tr><td><b>2024</b></td><td>FIN</td></tr>
</table>
