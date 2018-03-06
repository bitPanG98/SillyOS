A="."

for i in "$A"/**/*.bmp
do
    ../../Scripts/bmp2hex.py -f $i -o font.rs
done
