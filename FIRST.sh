### a guide to running...

echo "tar of input-2015-2014.tar.gz takes ~10seconds"
tar -xvzf input-2015-2014.tar.gz
echo "sh specialCopy.sh takes ~1minute"
sh specialCopy.sh
echo "sh specialCompile.sh takes ~11minutes"
sh specialCompile.sh
mv 2019/2019.day25/*.exe 2019/day25/2019.day25.INTERACTIVE.exe
echo "sh runALL.sh takes ~560minutes"
echo "if you ps and kill the big 5:"
echo "		(126min, 35mins, 21mins, 34mins, 4hours)"
echo "it takes ~110minutes"
sh runALL.sh

##creates output.2015, output.2016 etc...
echo "************REPORT:**************************"
echo "un-tar input-2015-2014.tar.gz takes ~10seconds"
echo "sh specialCopy.sh takes ~1minute"
echo "sh specialCompile.sh takes ~11minutes"
echo "sh runALL.sh takes ~560minutes"
echo "if you ps and kill the big 5:"
echo "		(126min, 35mins, 21mins, 34mins, 4hours)"
echo "	it takes ~110minutes"
echo "************REPORT:**************************"

