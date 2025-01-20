echo "generates a diagam of system of components - specific to 2023 day25"
if [ @$1 = @ ]; then
	echo "give a file name"
	exit;
fi

if [ ! -f $1 ]; then
	echo "[ $1 ] not a valid file"
	exit;
else
	echo "valid file $1"
fi

echo "graph graph3 {" > tmp1.txt
sed 's/: / /' $1 |  sed 's/ / -- /g'  >> tmp1.txt
echo \} >> tmp1.txt
touch out.svg



rm outDOT.svg
touch outDOT.svg
dot -Tsvg tmp1.txt -o outDOT.svg -Kneato
ls -l outDOT.svg
cp outDOT.svg /cygdrive/c/Users/conor.williams/Desktop/ut1.svg
echo "press.."
read



rm outNEATO.svg
touch outNEATO.svg
neato -Tsvg tmp1.txt -o outNEATO.svg
ls -l outNEATO.svg
cp outNEATO.svg /cygdrive/c/Users/conor.williams/Desktop/ut2.svg
echo "press.."
read



rm outSFDP.svg
touch outSFDP.svg
sfdp -Tsvg tmp1.txt -o outSFDP.svg
ls -l outSFDP.svg
cp outSFDP.svg /cygdrive/c/Users/conor.williams/Desktop/ut3.svg

### in the end quite manual once you know; 
#	sum == axb x Cin         
#       cout = a.b + cin.(axb)  (note the first and last are correct (ignore them.. )
### start around 2 or 3 and get a system going eg... first line xor second line xor, x before y for the xor and y before x for the and)
### eg: (watch what matches up... fcs is on the second line of the previos etc... jdb is on the 3rd line... (its all repetive...) enjoy!!
#-----z07
#swp XOR fcs -> z07
#x07 XOR y07 -> fcs
#y07 AND x07 -> btb
#mcs OR jwh -> swp
#vrh AND wts -> mcs
#----- z08 --
#kpt XOR prr -> z08
#x08 XOR y08 -> prr
#y08 AND x08 -> mkj
#jdb OR btb -> kpt
#fcs AND swp -> jdb

### handy awk if ordering has changed and you want to do a diff
### 1544   awk '{print $1 " " $2 " " $3 " " $5; print $3 " " $2 " " $1 " " $5}' fil6 > fil6.6
### diff i1.txt i1.mod.txt  
### :g /^--.*$/d 
#### also, look for abberations in the generated graph as u go -- has some pointers
