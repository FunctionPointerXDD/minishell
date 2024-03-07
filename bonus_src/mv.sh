suffix="_bonus.c"
for file in *.c; do
mv "$file" "$file$suffix"
done
