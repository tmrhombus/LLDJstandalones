##lifetime="ctauS1"
ntags=1
name="ctauS1_nt1"
c_al=(0.05 0.1 0.15)
c_ip=(0.84 1.2 0.7)
c_ta=(-1.86 -2.0 -2.22)
touch temp.txt
touch temp2.txt
touch temp4.txt
touch $name.txt
rm taggerResults/$name.txt
for i in {0..2}
do
   for j in {0..2}
   do
      for k in {0..2}
      do
         echo ${c_ip[i]} ${c_ta[j]} ${c_al[k]}>>temp2.txt
         root -l -b -q "tagger.C(${c_ip[i]},${c_ta[j]}, ${c_al[k]}, $ntags)" >>temp.txt
      done
   done
done
awk '($1 !="Processing"){print}' temp.txt> temp3.txt
sed -i '/^$/d' temp3.txt
paste  temp2.txt temp3.txt >>temp4.txt
awk 'BEGIN {printf("%-8s %-8s %-8s %-12s %-12s %-12s %-16s %-16s %-16s %-16s \n", "c_ip", "c_ta", "c_al", "Nsig", "Nbkg","S/sqrt(S+B)","S/sqrt(S+B+0.1B)","S/sqrt(S+B+0.5B)","S/sqrt(S+B+1.0B)","S/sqrt(S+B+2.0B)")}{printf("%-8.2f %-8.2f %-8.2f %-12.6f %-12.6f %-12.6f %-16.6f %-16.6f %-16.6f %-16.6f \n", $1, $2, $3, $5, $7, $5/sqrt($5 +$7),  $5/sqrt($5 +$7 +0.1*$7),  $5/sqrt($5 +$7 +0.5*$7), $5/sqrt($5 +$7 +1.0*$7), $5/sqrt($5 +$7 +2.0*$7) )}' temp4.txt >$name.txt
mv $name.txt taggerResults/

rm temp.txt
rm temp2.txt
rm temp3.txt
rm temp4.txt


##1 nt 1
##c_al=(0.05 0.1 0.15)
##c_ip=(0.84 1.2 0.7)
##c_ta=(-1.86 -2.0 -2.22)
##1 nt2
##c_al=(0.1 0.2 0.15)
##c_ip=(0.72 1.0 0.5)
##c_ta=(-2.22 -1.9 -1.65)

##10 nt 1
##c_al=(0.06 0.1 0.2)
##c_ip=(1.5 1.0 1.75)
##c_ta=(-1.5 -1.0 -2.0)
##10 nt 2
##c_al=(0.09 0.15 0.2)
##c_ip=(1.26 1.65 1.0)
##c_ta=(-1.5 -1.0 -1.8)

##100 nt 1
##c_al=(0.06 0.10 0.20)
##c_ip=(1.62 0.5 2.10)
##c_ta=(-1.44 -2.0 -0.75)
##100 nt 2
##c_al=(0.10 0.20 0.35)
##c_ip=(0.0 1.2 1.62)
##c_ta=(-1.2 -1.5 -2.0)

##1000 nt 1
##c_al=(0.12 0.7 0.2)
##c_ip=(1.68 1.4 1.2)
##c_ta=(-1.44 -1.6 -1.2)
##1000 nt2
##c_al=(0.12 0.7 0.2)
##c_ip=(1.44 1.25 -0.6)
##c_ta=(-2.76 -1.6 -2.2)
