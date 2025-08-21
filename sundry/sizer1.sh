#echo 'for i in *; do if [ -d "$i" ]; then du -hs "$i"; fi; done' >> sizer.sh

for i in *;
do
	if [ -d "$i" ]; then
		du -hs "$i";
	fi;
done
