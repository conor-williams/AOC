<p><b>Notes: <i>c.w.</i></b></p>
<ul>
<li>g++ if "using namespace std" </li>
<li>either if no "using namespace std" </li>
<li>expand the stack if errors compiling or linking: --Wl,--stack,999777666 </li>
<li>-I. to the compiler when using bigint </li>
<li>if crashes or "segmentation falit" expand/widen the stack </li>
<li>add widen stack check in specific c files; maybe a simple malloc with a free and a note (<i><b>todo in 2025</b></i></li>
<s><li>a couple need the input sorted externally first or else they crash: sort file.1 > file.2: (will do internal sort -- (<i><b>todo in 2025</b></i>)) </li></s>
<li>dayX.c is part1 of day X </li>
<li>dayX.2.c is part2 of day X </li>
<li>others are scribbles.. or partials/solns which may not have worked </li>
<li>there are a couple that take overnight... they need optimisation -- (<b><i>todo in 2025</b></i>) </li>
<li>there are around 40 that have not been completed -- (<b><i>todo in 2025</b></i>) </li>
<li>a couple were done without c/c++ -- mostly using sed, awk, du and unix commands scripts -- will upload (<b><i>todo in 2025</i></b>) </li>
<li>a couple where there was mental arithmetic after the output was generated by c/c++ file, mostly detect of cycles (auto detect cycles (<b><i>todo in 2025</i></b>)) </li>
<li>a couple <s>missing dayX.c and have</s> dayX.2.c (<b><i>todo in 2025</b></i>) </li>
<li>a couple need md5 (for cygwin: install <b>mbedtls</b> development (-> libmbedcrypto.a in /lib)) (gcc -lmbedcrypto dayX.c -Wall ) </li>
<li>a couple need the dictionary of words (for cygwin: install <b>words</b></li>
<li>kudos to <i><b>Eric Wastl & co.</b></i></li>
</ul>
<br>
<address><b>conor.williams@gmail.com</b></address><br>
<font size=1><i>last updated</i>: <b>03/01/2025</b></font>
<br><br>

<h3>Table of years/days of days which need optimizations or work (todo: ongoing):</h3>
<table> 
	<tr><td><b><i>2015</i></b></td><td>day10</td><td>day12&nbsp;&nbsp;&nbsp;</td><td>day19.2&nbsp;&nbsp;&nbsp;</td><td>day20&nbsp;&nbsp;&nbsp;</td><td>day24&nbsp;&nbsp;&nbsp;</td></tr>
	<tr><td><b>2016</b></td><td><s>day2 x 2</s></td></td><td>day9.2</td><td>day11 x 2 </td><td>day20.2</td><td>day22.2</td><td>day23.2</td></tr>
	<tr><td><b>2017</b></td><td>todo</td></tr>
	<tr><td><b>2018</b></td><td>todo</td></tr>
	<tr><td><b>2019</b></td><td>todo</td></tr>
	<tr><td><b>2020</b></td><td>todo</td></tr>
	<tr><td><b>2021</b></td><td>todo</td></tr>
	<tr><td><b>2022</b></td><td>todo</td></tr>
	<tr><td><b>2023</b></td><td>todo</td></tr>
	<tr><td><b><i>2024</i></b></td><td>day22.2</td></tr>
</table>
