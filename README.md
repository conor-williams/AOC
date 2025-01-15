<h3>Notes: c.w.</h3>
<br>
<h3>Update (11::14-01-25):</h3><br>
   <pre>
	o all day 1's for every year working well, except:
		-- 2016 Day 11
	   	-- 2018 Day 21
		-- 2019 Day 18
		-- <s>2022 Day 22</s>
	   	-- 2023 Day 22
	o all years days 1--10 working well, except:
		-- 2017 Day 7.2
		-- <s>2018 Day 7 1&2</s>
	   	-- 2022 Day 9.2
	</pre>
<hr>
<br>
	<hr>
 	<h2>Update (08-01-25):</h2>
  	<pre>
	o all years days 1--10 working well, (except 2017 Day7.2 and 2018 Day 7 1&2)
 	o now looking at all day1's 1->25 for every year
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
<li>one will only work with gcc</li>
<li>expand the stack if errors compiling or linking: --Wl,--stack,999777666 </li>
<li>if crashes or "segmentation falit" expand/widen the stack (it means: more memory needed or many hi depth of recursion) </li>
<li>-I. to the compiler when using bigint (after copying into this dir, the .h files) </li>
<li>dayX.c is part1 of day X </li>
<li>dayX.2.c is part2 of day X </li>
<li>others are scribbles.. or partials/solns which may not have worked </li>
<li>a couple need md5 (for cygwin: install <b>mbedtls</b> development (-> libmbedcrypto.a in /lib)) (gcc -lmbedcrypto dayX.c -Wall ) </li>
<li>you will find dot or heato or sfdp in package graphviz for python (python and graphviz are in cygwin packages) </li>
<li> <h2>TODO:</h2></li>
<s><li>FIXED: a couple need the dictionary of words (for cygwin: install <b>words</b>) </li></s>
<s><li>FIXED: a couple <s>missing dayX.c and have</s> dayX.2.c (<b><i>todo in 2025</b></i>) </li></s>
<s><li>FIXED: a couple need the input sorted externally first or else they crash: sort file.1 > file.2: (will do internal sort -- (<i><b>todo in 2025</b></i>)) </li></s>
<li>add widen stack check in specific c files; maybe a simple malloc with a free and a note (<i><b>todo in 2025</b></i>) </li>
<li>a couple where there was mental arithmetic after the output was generated by c/c++ file, mostly detect of cycles (auto detect cycles (<b><i>todo in 2025</i></b>)) </li>
<li>there are a couple that take overnight... (there is usually a manual way (diagram gen) to get the answer) they need optimisation -- (<b><i>todo in 2025</b></i>) </li>
<li>there are around 40 that have not been completed -- (<b><i>todo in 2025</b></i>) </li>
<li>a couple were done without c/c++ -- mostly using sed, awk, du and unix commands scripts -- will upload (<b><i>todo in 2025</i></b>) </li>
<li></li>
	
 <li>kudos to <i><b>Eric Wastl & co.</b></i></li>
</ul>
<br>
<address><b>conor.williams@gmail.com</b></address><br>
<font size=1><i>last updated</i>: <b>11/01/2025</b></font>
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
