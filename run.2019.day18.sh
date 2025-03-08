#script to run and then you can ^c the process not the surrounding script
set -xv
trap_ctrlc() {
	echo "ctrlc.pressed (in trap)..\n";
#    kill $pid
#    echo -e "\nkill=$? (0 = success)\n"
#    wait $pid
#    echo "wait=$? (the exit status from the background process)"
#    echo -e "\n\ntrap_ctrlc\n\n"
}

trap trap_ctrlc INT
g++ 2019.day18.2.c -o 2019.day18.2 -Wall
g++ 2019.day18.c -o 2019.day18 -Wall
date
time ./2019.day18 i1.txt
date
time ./2019.day18.2 i1.txt
date

#uploading c and sh 2mora2mora
